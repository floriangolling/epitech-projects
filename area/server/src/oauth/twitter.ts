import { Request, Response, NextFunction } from 'express';
import { setupServices } from "../controllers/service";
import { User } from "../database/models";
import IOAuthService from "./interface";
import config from '../config';
import jwt from 'jsonwebtoken';
import axios from 'axios';

class twitterOauth extends IOAuthService {
    async setRefreshToken(req: Request, res: Response, next: NextFunction) {
        const {code, scope} = req.query;
        try {
            let token = null;
            if (req.headers.authorization)
                token = req.headers.authorization.replace("Bearer ", "");
            if (!token || token === null || token === "null")
                return res.status(403).send({message: 'Unauthorized'});

            const decoded = jwt.verify(token, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})

            const params = new URLSearchParams();
            params.append('code', code.toString());
            params.append('client_id', config.TWITTER_CLIENT_ID);
            params.append('redirect_uri', config.TWITTER_REDIRECT_URI);
            params.append('state', "state");
            params.append('grant_type', 'authorization_code')
            params.append('code_verifier', "challenge");
            
            if (!user) {
                return res.status(404).send({
                    error: "not found"
                })
            }
            const credentials = Buffer.from(`${config.TWITTER_CLIENT_ID}:${config.TWITTER_CLIENT_SECRET}`).toString("base64")
            const request = await axios.post(`https://api.twitter.com/2/oauth2/token`, params, {
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                    'Authorization': 'Basic ' + credentials
                }
            })
            const {access_token} = request.data;

            let fields = user.oauths;
            fields.twitter = {};
            fields['twitter'] = {
                refresh_token: access_token,
                loggedWith: true,
            }
            user.oauths = fields;
            await user.changed('oauths', true);
            await user.save();
            res.status(200).send({
                message: "Account linked to twitter."
            });
            return await setupServices();
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            return res.status(500).send({error});
        }        
    }

    async loginCreateAccount(req: Request, res: Response, next: NextFunction) {
        const {code} = req.query;
        try {
            const params = new URLSearchParams();

            params.append('code', code.toString());
            params.append('client_id', config.TWITTER_CLIENT_ID);
            params.append('redirect_uri', config.TWITTER_REDIRECT_URI);
            params.append('state', "state");
            params.append('grant_type', 'authorization_code')
            params.append('code_verifier', "challenge");

            const request = await axios.post(`https://api.twitter.com/2/oauth2/token`, params, {
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                }
            })
            const {access_token, refresh_token} = request.data;
            const userRequest = await axios.get('https://api.twitter.com/2/users/me', {
                headers: {
                    Authorization: `Bearer ${access_token}`
                }
            })

            const userDB = await User.findOne({where: {username: userRequest.data.data.username }});
            if (!userDB) {
                const newUser = await User.create({username: userRequest.data.data.username, email: "", password: null, admin: false, confirmed: true});
                let fields = newUser.oauths;
                fields.twitter = {};
                fields['twitter'] = {
                    refresh_token,
                    loggedWith: true,
                    username: userRequest.data.data.name
                }
                newUser.oauths = fields;
                await newUser.changed('oauths', true);
                await newUser.save();
                const token = jwt.sign({
                    user_id : newUser.id,
                    email: userRequest.data.data.username
                }, config.JWT_SECRET)
                res.status(200).send({token})
                return await setupServices();
            } else if (userDB.oauths.twitter && userDB.oauths.twitter.loggedWith === true) {
                const token = jwt.sign({
                    user_id : userDB.id,
                    email: userDB.email
                }, config.JWT_SECRET)
                res.status(200).send({token})                
                return await setupServices();
            } else {
                return res.status(409).send({
                    message: "your email is already used and not with oauth"
                })
            }
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            res.status(500).send({error});
        }
    }
}

const twitter = new twitterOauth("twitter", `https://twitter.com/i/oauth2/authorize?response_type=code&client_id=${config.TWITTER_CLIENT_ID}&redirect_uri=${config.TWITTER_REDIRECT_URI}&scope=tweet.write%20tweet.read%20users.read%20follows.read%20offline.access&state=state&code_challenge=challenge&code_challenge_method=plain`, false);

export default twitter;