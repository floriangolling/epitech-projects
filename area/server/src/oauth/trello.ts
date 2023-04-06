import { Request, Response, NextFunction } from 'express';
import { setupServices } from "../controllers/service";
import { User } from "../database/models";
import IOAuthService from "./interface";
import config from '../config';
import jwt from 'jsonwebtoken';
import {OAuth} from 'oauth';

export const oauthTrelloClass = new OAuth(config.TRELLO_REQUEST_URL, config.TRELLO_ACCESS_URL, config.TRELLO_TOKEN, config.TRELLO_SECRET, "1.0A", config.TRELLO_LOGINCALLBACK, "HMAC-SHA1");

class trelloOauth extends IOAuthService {
    async setRefreshToken(req: Request, res: Response, next: NextFunction, verifier: any, tokenSecret: any, token: any) {
        try {
            let tokenBearer = null;
            if (req.headers.authorization)
                tokenBearer = req.headers.authorization.replace("Bearer ", "");
            if (!tokenBearer || tokenBearer === null || tokenBearer === "null")
                return res.status(403).send({message: 'Unauthorized'});
            const decoded = jwt.verify(tokenBearer, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})

            oauthTrelloClass.getOAuthAccessToken(token, tokenSecret, verifier, async function(error, accessToken, accessTokenSecret, results){
                if (!user) {
                    return res.status(404).send({
                        error: "not found"
                    })
                }
                oauthTrelloClass.getProtectedResource("https://api.trello.com/1/members/me", "GET", accessToken, accessTokenSecret, async (error, data: any, response) => {
                    let jsonData = JSON.parse(data);
                    let fields = user.oauths;
                    fields.trello = {};
                    fields['trello'] = {
                        refresh_token: accessToken,
                        loggedWith: true,
                        username: jsonData.id
                    }
                    user.oauths = fields;
                    await user.changed('oauths', true);
                    await user.save();
                    res.status(200).send({
                        message: "Account linked to trello."
                    });
                    return await setupServices();
                });
            })
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            return res.status(500).send({error});
        }        
    }

    async loginCreateAccount(req: Request, res: Response, next: NextFunction, verifier: any, tokenSecret: any, token: any) {
        try {
            oauthTrelloClass.getOAuthAccessToken(token, tokenSecret, verifier, async (error, accessToken, accessTokenSecret, results) => {
                oauthTrelloClass.getProtectedResource("https://api.trello.com/1/members/me", "GET", accessToken, accessTokenSecret, async (error, data: any, response) => {
                    const jsonData = JSON.parse(data);
                    const userDB = await User.findOne({where: {username: jsonData.username }});
                    if (!userDB) {
                        const newUser = await User.create({username: jsonData.username, email: "", password: null, admin: false, confirmed: true});
                        let fields = newUser.oauths;
                        fields.trello = {};
                        fields['trello'] = {
                            refresh_token: accessToken,
                            loggedWith: true,
                            username: jsonData.username
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
                    } else if (userDB.oauths.trello && userDB.oauths.trello.loggedWith === true) {
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
                })
            });
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            res.status(500).send({error});
        }
    }
}

const trello = new trelloOauth("trello", `redirect_is_different_there`, false);

export default trello;