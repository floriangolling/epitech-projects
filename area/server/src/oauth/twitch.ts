import { Request, Response, NextFunction } from 'express';
import { setupServices } from "../controllers/service";
import { User } from "../database/models";
import IOAuthService from "./interface";
import TwitchApi from 'node-twitch';
import jwt from 'jsonwebtoken';
import config from '../config';
import axios from 'axios';


class twitchOauth extends IOAuthService {
    async setRefreshToken(req: Request, res: Response, next: NextFunction) {
        const {code} = req.query;
        try {
            let token = null;
            if (req.headers.authorization)
                token = req.headers.authorization.replace("Bearer ", "");
            if (!token || token === null || token === "null")
                return await this.loginCreateAccount(req, res, next);

            const decoded = jwt.verify(token, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})
            const request = await axios.post(`https://id.twitch.tv/oauth2/token?client_id=${config.TWITCH_CLIENT_ID}&client_secret=${config.TWITCH_CLIENT_SECRET}&code=${code}&grant_type=authorization_code&redirect_uri=${config.TWITCH_REDIRECT_URI}`)
            const {access_token, refresh_token} = request.data;
            const client = new TwitchApi({
                client_id: config.TWITCH_CLIENT_ID,
                client_secret: config.TWITCH_CLIENT_SECRET,
                redirect_uri: config.TWITCH_REDIRECT_URI,
                access_token: access_token,
                scopes: ['user:read:email', 'chat:edit'] as any,
            })
            const userInfos = await client.getCurrentUser();
            if (!user) {
                return res.status(404).send({
                    error: "not found"
                })
            }
            let fields = user.oauths;
            fields.twitch = {};
            fields['twitch'] = {
                refresh_token,
                loggedWith: true,
                username: userInfos.display_name
            }
            user.oauths = fields;
            await user.changed('oauths', true);
            await user.save();
            res.status(200).send({
                message: "Account linked to twitch."
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
            const request = await axios.post(`https://id.twitch.tv/oauth2/token?client_id=${config.TWITCH_CLIENT_ID}&client_secret=${config.TWITCH_CLIENT_SECRET}&code=${code}&grant_type=authorization_code&redirect_uri=${config.TWITCH_REDIRECT_URI}&scope=chat:read chat:edit`)
            const {access_token, refresh_token} = request.data;
            const client = new TwitchApi({
                client_id: config.TWITCH_CLIENT_ID,
                client_secret: config.TWITCH_CLIENT_SECRET,
                redirect_uri: config.TWITCH_REDIRECT_URI,
                access_token: access_token,
                scopes: ['user:read:email', 'chat:edit'] as any,
            })
            const user = await client.getCurrentUser();
            const userDB = await User.findOne({where: {email: user.email.toLowerCase() }});
            if (!userDB) {
                const newUser = await User.create({username: user.login, email: user.email.toLowerCase(), password: null, admin: false, confirmed: true});
                let fields = newUser.oauths;
                fields.twitch = {};
                fields['twitch'] = {
                    refresh_token,
                    loggedWith: true,
                    username: user.display_name
                }
                newUser.oauths = fields;
                await newUser.changed('oauths', true);
                await newUser.save();
                const token = jwt.sign({
                    user_id : newUser.id,
                    email: user.email
                }, config.JWT_SECRET)
                res.status(200).send({token})
                return await setupServices();
            } else if (userDB.oauths.twitch && userDB.oauths.twitch.loggedWith === true) {
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

const twitch = new twitchOauth("twitch", `https://id.twitch.tv/oauth2/authorize?response_type=code&redirect_uri=${config.TWITCH_REDIRECT_URI}&scope=user_read chat:read chat:edit&client_id=${config.TWITCH_CLIENT_ID}`, true);

export default twitch;