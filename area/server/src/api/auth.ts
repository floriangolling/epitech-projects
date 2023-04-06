import express, { NextFunction, Request, Response } from 'express';
import {oauthTrelloClass} from '../oauth/trello';
import User from '../database/models/user';
import * as OAuthServices from '../oauth';
import jwt from 'jsonwebtoken';
import config from '../config';
import bcrypt from 'bcrypt';
import url from 'url';

const oauths_secrets = {} as any;

const authRouter = express.Router();

authRouter.get('/oauths', async (req: Request, res: Response, next: NextFunction) => {
    try {
        let oauths = [];
        for (const service of Object.values(OAuthServices)) {
            oauths.push(service.serviceName.toLocaleLowerCase());
        }
        res.status(200).send({oauths});
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: error
        })
    }
});

authRouter.get('/oauths/create', async(req: Request, res: Response, next: NextFunction) => {
    try {
        let oauths = [];
        for (const service of Object.values(OAuthServices)) {
            if (service.canCreate === true)
                oauths.push(service.serviceName.toLocaleLowerCase());
        }
        res.status(200).send({oauths});
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: error
        })
    }
})

authRouter.get('/auth/link/:id', (req: Request, res: Response, next: NextFunction) => {
    try {
        for (const service of Object.values(OAuthServices)) {
            if (service.serviceName === req.params.id) {
                if (req.params.id === 'trello') {
                    return oauthTrelloClass.getOAuthRequestToken(function(error, token, tokenSecret, results){
                        oauths_secrets[token] = tokenSecret;
                        return res.send({message: `${config.TRELLO_AUTHORIZE_URL}?oauth_token=${token}&name=${config.TRELLO_APPNAME}&scope=${config.TRELLO_SCOPE}&expiration=${config.TRELLO_EXPIRATION}`});
                      });
                } else if (req.params.id !== 'trello') {
                    return res.status(200).send({
                        message: service.oauthLink
                    });
                }
            }
        }
        return res.status(404).send({
            message: 'Oauth not found.'
        })
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: error
        })
    }
});

authRouter.get('/auth/callback/:id', async (req: Request, res: Response, next: NextFunction) => {
    try {
        for (const service of Object.values(OAuthServices)) {
            if (service.serviceName === req.params.id) {
                if (req.params.id == 'trello') {
                    const query = url.parse(req.url, true).query;
                    const token = query.oauth_token as string;
                    const tokenSecret = oauths_secrets[token];
                    const verifier = query.oauth_verifier;
                    return await service.setRefreshToken(req, res, next, verifier, tokenSecret, token);
                } else {
                    return await service.setRefreshToken(req, res, next, null, null, null);
                }
            }
        }        
        return res.status(404).send({
            message: 'Oauth not found.'
        })        
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: error
        })
    }
})

authRouter.post('/login', async (req: Request, res: Response) => {
    try {
        const {username, password} = req.body;
        if (!username || !password)
            return res.status(400).send({
                message: 'Bad request'
            })
        const user = await User.findOne({where: {username}});
        if (!user) {
            return res.status(404).send({
                message: 'User not found !'
            })
        }
        if (await bcrypt.compareSync(password, user.password)) {
            const token = jwt.sign({
                user_id : user.id,
                email: user.email
            }, config.JWT_SECRET, { expiresIn: '1h' })
            return res.status(200).send({token});
        } else {
            return res.status(400).send({
                message: 'Bad credentials !'
            })
        }
    } catch (error) {
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
});

authRouter.post('/register', async (req: Request, res: Response) => {
    try {
        const {username, password} = req.body;
        if (!username || !password)
            return res.status(400).send({
                message: 'Bad request'
            })
        const user = await User.findOne({where: {username}});
        if (user) {
            return res.status(401).send({
                message: 'User already exist, cannot created account'
            })
        }
        const hashedPassword = await bcrypt.hashSync(password, 10);
        const newUser = await User.create({username, email: "", password: hashedPassword, admin: false, confirmed: true});
        return res.status(200).send({
            message: 'User created !'
        })
    } catch (error) {
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
});

export default authRouter;