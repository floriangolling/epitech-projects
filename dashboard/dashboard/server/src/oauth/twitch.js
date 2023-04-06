const oauthInterface            = require('./interface');
const jwt                       = require('jsonwebtoken')
const config                    = require('../config');
const User                      = require('../database/models/user')
const axios                     = require('axios');
const { default: TwitchApi }    = require('node-twitch');

class twitchoauthService extends oauthInterface {
    async setRefreshToken(req, res, next) {
        const {code, scope} = req.query;
        try {
            const token = req.headers.authorization.replace("Bearer ", "");
            if (!token || token === null || token === "null") {
                return await this.loginCreateAccount(req, res, next);
            }
            const decoded = jwt.verify(token, config.JWT_SECRET);
            const user = await User.findOne({ where: {id: decoded.user_id }})
    
            const request = await axios.post(`https://id.twitch.tv/oauth2/token?client_id=${config.TWITCH_CLIENT_ID}&client_secret=${config.TWITCH_SECRET}&code=${code}&grant_type=authorization_code&redirect_uri=${config.TWITCH_REDIRECT_URI}`)
            const {access_token, refresh_token, scope} = request.data;
            if (!user) {
                return res.status(404).send({
                    error: "not found"
                })
            }
            let fields = user.oauths;
            fields.twitch = {};
            fields['twitch'] = {
                refresh_token,
                loggedWith: true
            }
            user.oauths = fields;
            await user.changed('oauths', true);
            await user.save();
            res.status(201).send({
                message: "Account linked to twitch."
            });
        } catch (error) {
            console.log(error);
            res.status(500).send({error});
        }
    }

    async loginCreateAccount(req, res, next) {
        const {code, scope} = req.query;
        try {
            const request = await axios.post(`https://id.twitch.tv/oauth2/token?client_id=${config.TWITCH_CLIENT_ID}&client_secret=${config.TWITCH_SECRET}&code=${code}&grant_type=authorization_code&redirect_uri=${config.TWITCH_REDIRECT_URI}`)
            const {access_token, refresh_token, scope} = request.data;
            const client = new TwitchApi({
                client_id: config.TWITCH_CLIENT_ID,
                client_secret: config.TWITCH_SECRET,
                redirect_uri: config.TWITCH_REDIRECT_URI,
                access_token: access_token,
                scopes: ['user_read'],
            })
            const user = await client.getCurrentUser();
            const userDB = await User.findOne({where: {email: user.email.toLowerCase() }});
            if (!userDB) {
                const newUser = await User.create({username: user.login, email: user.email.toLowerCase(), password: null, admin: false, confirmed: true});
                let fields = newUser.oauths;
                fields.twitch = {};
                fields['twitch'] = {
                    refresh_token,
                    loggedWith: true
                }
                newUser.oauths = fields;
                await newUser.changed('oauths', true);
                await newUser.save();
                const token = jwt.sign({
                    user_id : newUser.id,
                    email: user.email
                }, config.JWT_SECRET)
                return res.status(200).send(token)
            } else if (userDB.oauths.twitch && userDB.oauths.twitch.loggedWith === true) {
                const token = jwt.sign({
                    user_id : userDB.id,
                    email: userDB.email
                }, config.JWT_SECRET)
                return res.status(200).send(token)                
            } else {
                return res.status(409).send({
                    message: "your email is already used and not with oauth"
                })
            }
        } catch (error) {
            console.log(error);
            res.status(500).send({error});
        }
    }
}

const twitchOauth = new twitchoauthService("twitch", `https://id.twitch.tv/oauth2/authorize?response_type=code&redirect_uri=${config.TWITCH_REDIRECT_URI}&scope=user_read&client_id=${config.TWITCH_CLIENT_ID}`);

module.exports = twitchOauth;