import { Request, Response, NextFunction } from 'express';
import { setupServices } from "../controllers/service";
import { User } from "../database/models";
import IOAuthService from "./interface";
import Querystring from 'query-string';
import { Octokit } from 'octokit';
import jwt from 'jsonwebtoken';
import config from '../config';
import axios from 'axios';

class GithubOauth extends IOAuthService {
    async setRefreshToken(req: Request, res: Response, next: NextFunction) {
        try {
            let token = null;
            if (req.headers.authorization)
                token = req.headers.authorization.replace("Bearer ", "");
            if (!token || token === null || token === "null") {
                return await this.loginCreateAccount(req, res, next);
            }

            const decoded = jwt.verify(token, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})
            const url = req.protocol + '://' + req.get('host') + req.originalUrl;
            const urlParams = (new URL(url)).searchParams;
            const code = urlParams.get('code');
            const state = urlParams.get('state');
            const params = new URLSearchParams();

            params.append('code', code);
            params.append('client_secret', config.GITHUB_CLIENT_SECRET);
            params.append('client_id', config.GITHUB_CLIENT_ID);
            params.append('redirect_uri', config.GITHUB_REDIRECT_URI);
            params.append('state', state);

            const request = await axios.post('https://github.com/login/oauth/access_token', params);
            const { access_token } = Querystring.parse(request.data);
            if (!user) {
                return res.status(404).send({
                    error: "not found"
                })
            }
            let fields = user.oauths;
            fields.github = {};
            fields['github'] = {
                refresh_token: access_token,
                loggedWith: true,
            }
            user.oauths = fields;
            await user.changed('oauths', true);
            await user.save();
            res.status(200).send({
                message: "Account linked to github."
            });
            return await setupServices();
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            return res.status(500).send({error});
        }        
    }

    async loginCreateAccount(req: Request, res: Response, next: NextFunction) {
        try {
            const url = req.protocol + '://' + req.get('host') + req.originalUrl;
            const urlParams = (new URL(url)).searchParams;
            const code = urlParams.get('code');
            const state = urlParams.get('state');
            const params = new URLSearchParams();

            params.append('code', code);
            params.append('client_secret', config.GITHUB_CLIENT_SECRET);
            params.append('client_id', config.GITHUB_CLIENT_ID);
            params.append('redirect_uri', config.GITHUB_REDIRECT_URI);
            params.append('state', state);

            const request = await axios.post('https://github.com/login/oauth/access_token', params);
            const {refresh_token, access_token } = Querystring.parse(request.data);
            const octokit = new Octokit({ auth: access_token });
            const userRequest = await octokit.request('GET /user') as any;
            const emailRequest = await octokit.request('GET /user/emails');
            const userDB = await User.findOne({where: {email: emailRequest.data[0].email.toLowerCase() }});
            if (!userDB) {
                const newUser = await User.create({username: userRequest.data.login, email: emailRequest.data[0].email.toLowerCase(), password: null, admin: false, confirmed: true});
                let fields = newUser.oauths;
                fields.github = {};
                fields['github'] = {
                    refresh_token: access_token,
                    loggedWith: true,
                    username: userRequest.data.login
                }
                newUser.oauths = fields;
                await newUser.changed('oauths', true);
                await newUser.save();
                const token = jwt.sign({
                    user_id : newUser.id,
                    email: emailRequest.data[0].email
                }, config.JWT_SECRET)
                res.status(200).send({token})
                return await setupServices();
            } else if (userDB.oauths.github && userDB.oauths.github.loggedWith === true) {
                let fields = userDB.oauths;
                fields.github.refresh_token = access_token;
                userDB.oauths = fields;
                await userDB.changed('oauths', true);
                await userDB.save();
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

const github = new GithubOauth("github", `https://github.com/login/oauth/authorize?client_id=${config.GITHUB_CLIENT_ID}&redirect_uri=${config.GITHUB_REDIRECT_URI}&state=${config.GITHUB_STATE}&scope=repo%20user:email%20user`, true);
export default github;