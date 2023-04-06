import { Request, Response, NextFunction } from 'express';
import { setupServices } from "../controllers/service";
import { User } from "../database/models";
import IOAuthService from "./interface";
import jwt from 'jsonwebtoken';
import config from '../config';
import axios from 'axios';

class redditOauth extends IOAuthService {
    async setRefreshToken(req: Request, res: Response, next: NextFunction) {
        const {code, scope, state} = req.query;
        try {
            let token = null;
            if (req.headers.authorization)
                token = req.headers.authorization.replace("Bearer ", "");
            if (!token || token === null || token === "null")
                return res.status(403).send({message: 'Unauthorized'});
            const decoded = jwt.verify(token, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})

            const params = new URLSearchParams();
            params.append('grant_type', "authorization_code");
            params.append('redirect_uri', config.REDDIT_REDIRECT_URI);
            params.append('state', state.toString());
            params.append('code', code.toString());
            const credentials = Buffer.from(`${config.REDDIT_CLIENT_ID}:${config.REDDIT_CLIENT_SECRET}`).toString("base64")
            const request = await axios.post('https://www.reddit.com/api/v1/access_token', params, {
                headers: {
                    'User-Agent': 'Sample app',
                    Authorization: 'Basic ' + credentials
                }
            });
            const {refresh_token} = request.data;
            if (!user) {
                return res.status(404).send({
                    error: "not found"
                })
            }
            let fields = user.oauths;
            fields.reddit = {};
            fields['reddit'] = {
                refresh_token,
                loggedWith: true,
            }
            user.oauths = fields;
            await user.changed('oauths', true);
            await user.save();
            res.status(200).send({
                message: "Account linked to reddit."
            });
            return await setupServices();
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            return res.status(500).send({error});
        }        
    }

    async loginCreateAccount(req: Request, res: Response, next: NextFunction) {
        const {code, scope, state} = req.query;
        try {
            const params = new URLSearchParams();
            params.append('grant_type', "authorization_code");
            params.append('redirect_uri', config.REDDIT_REDIRECT_URI);
            params.append('state', state.toString());
            params.append('code', code.toString());
            const credentials = Buffer.from(`${config.REDDIT_CLIENT_ID}:${config.REDDIT_CLIENT_SECRET}`).toString("base64")
            const request = await axios.post('https://www.reddit.com/api/v1/access_token', params, {
                headers: {
                    'User-Agent': 'Sample app',
                    Authorization: 'Basic ' + credentials
                }
            });
            const {access_token, refresh_token} = request.data;
            const userRequest = await axios.get('https://oauth.reddit.com/api/v1/me', {
                headers: {
                    Authorization: `Bearer ${access_token}`,
                    'User-Agent': 'Sample app'
                }
            })
            const userDB = await User.findOne({where: {username: userRequest.data.name }});
            if (!userDB) {
                const newUser = await User.create({username: userRequest.data.name, email: "", password: null, admin: false, confirmed: true});
                let fields = newUser.oauths;
                fields.reddit = {};
                fields['reddit'] = {
                    refresh_token,
                    loggedWith: true,
                    username: userRequest.data.name
                }
                newUser.oauths = fields;
                await newUser.changed('oauths', true);
                await newUser.save();
                const token = jwt.sign({
                    user_id : newUser.id,
                    email: ""
                }, config.JWT_SECRET)
                res.status(200).send({token})
                return await setupServices();
            } else if (userDB.oauths.reddit && userDB.oauths.reddit.loggedWith === true) {
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

const reddit = new redditOauth("reddit", `https://www.reddit.com/api/v1/authorize?client_id=${config.REDDIT_CLIENT_ID}&redirect_uri=${config.REDDIT_REDIRECT_URI}&duration=permanent&scope=read,identity,account,subscribe,submit&state=${config.REDDIT_STATE}&response_type=code`, false);

export default reddit;