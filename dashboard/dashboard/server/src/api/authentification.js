const express                   = require("express");
const User                      = require("../database/models/user");
const bcrypt                    = require("bcrypt");
const config                    = require("../config");
const jwt                       = require("jsonwebtoken");
const authentificationRouter    = express.Router();
const sendmail                  = require('sendmail')()
/**
 * @swagger
 * /login:
 *  post:
 *     description: used to login using your account
 *     tags: [Authentification]
 *     parameters:
 *        - name: login parameters
 *          description: required parameters to login
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  email:
 *                      type: string
 *                  password:
 *                      type: string
 *     responses:
 *       '200':
 *          description: You successfully logged in !
 *          schema:
 *              properties:
 *                  token:
 *                      type: string
 *       '404':
 *          description: This user has not been found
 *       '500':
 *          description: An error has occurred while trying to login
 *       '400':
 *          description: All inputs are not filled / invalid credentials
 */

authentificationRouter.post("/login", async (req, res, next) => {
    try {
        const {email, password} = req.body;
        if (!(email && password)) {
            return res.status(400).send({
                error : "All input is required"
            })
        }
        const user = await User.findOne({
            where : {
                email: email.toLowerCase()
            }
        })
        if (!user) {
            return res.status(404).send({
                error : "User not found"
            })
        }
        if (user.confirmed === false)
            return res.status(403).send({
                error: "Unauthorized"
            })
        if (await bcrypt.compareSync(password, user.password)) {
            const token = jwt.sign({
                user_id : user.id,
                email
            }, config.JWT_SECRET, { expiresIn: '1h' })
            return res.status(200).send(token);
        }
        return res.status(400).send({
            error : "Invalid credentials"
        })
    } catch (err) {
        console.log(err);
        res.status(500).send({
            error : err
        })
    }
});

/**
 * @swagger
 * /register:
 *  post:
 *     description: used to create your account
 *     tags: [Authentification]
 *     parameters:
 *        - name: register parameters
 *          description: required parameters to create an account
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  email:
 *                      type: string
 *                  password:
 *                      type: string
 *                  username:
 *                      type: string
 *     responses:
 *       '201':
 *          description: You successfully created your account !
 *          schema:
 *              properties:
 *                  message:
 *                      type: string
 *       '409':
 *          description: This email is already in use
 *       '500':
 *          description: An error has occurred while trying to login
 *       '400':
 *          description: All inputs are not filled / invalid credentials
 */

authentificationRouter.post("/register", async (req, res, next) => {
    try {
        const { email, password, username } = req.body;
        if (!(email && password && username)) {
            return res.status(400).send({
                error : "All input is required"
            })
        }
        const user = await User.findOne({
            where : {
                email: email.toLowerCase()
            }
        })
        if (user) {
            return res.status(409).send({
                error : "email already in use"
            })
        }
        const hashedPassword = await bcrypt.hashSync(password, 10);
        const newUser = await User.create({
            username,
            email: email.toLowerCase(),
            password : hashedPassword
        })
        const token = jwt.sign({ user_id : newUser.id}, config.JWT_EMAIL_SECRET, { expiresIn: '1h' });
        await sendmail({
            from: 'dashboardepitecheu@gmail.com',
            to: email,
            subject: 'Confirm your account Dashboard EPITECH',
            html: `Please confirm your email by clicking on this link ! : ${config.PROTOCOL}${config.HOST}:${config.PORT}/confirm?token=${token}`
        })
        return res.status(201).send({
            message : "User created"
        })
    } catch (err) {
        console.log(err)
        res.status(500).send({
            error : err
        })
    }
})

/**
 * @swagger
 * /confirmToken:
 *  get:
 *     description: used to confirm your account
 *     tags: [Authentification]
 *     parameters:
 *        - name: confirmation token
 *          description: required parameters to create your account
 *          in: query
 *          required: true
 *          schema:
 *              properties:
 *                  token:
 *                      type: string
 *     responses:
 *       '200':
 *          description: You successfully confirmed your account !
 *       '404':
 *          description: User not found
 *       '500':
 *          description: An error has occurred while trying to confirm your token
 */

authentificationRouter.get('/confirmToken', async (req, res, next) => {
    try {
        const decoded = jwt.verify(req.query.token, config.JWT_EMAIL_SECRET);
        const user = await User.findOne({where: {id: decoded.user_id }})
        if (!user)
            return res.status(404).send(error);
        await user.set({
            confirmed: true
        })
        await user.save()
        return res.status(200).send({});
    } catch (error) {
        console.log(error)
        res.status(403).send({
            error: "Unauthorized"
        });
    }
});

/**
 * @swagger
 * /forgot:
 *  post:
 *     tags: [Authentification]
 *     description: used to reset your password (get the link)
 *     parameters:
 *        - name: register parameters
 *          description: required parameters to ask a link to get your passwodr back
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  email:
 *                      type: string
 *     responses:
 *       '404':
 *          description: User not found
 *       '403':
 *          description: no password
 *       '500':
 *          description: An error has occurred while trying to send mail
 *       '200':
 *          description: mail sent
 */

authentificationRouter.post('/forgot', async (req, res, next) => {
    try {
        const {email} = req.body;
        if (!email) {
            return res.status(403).send({
                message: "all input required"
            })
        }
        const user = await User.findOne({where: {email: email}});
        if (!user) {
            return res.status(404).send({
                message: "user not found"
            })
        }
        const token = jwt.sign({ user_id : user.id}, config.JWT_EMAIL_SECRET, { expiresIn: '1h' });
        await sendmail({
            from: 'dashboardepitecheu@gmail.com',
            to: email,
            subject: 'change your password Dashboard EPITECH',
            html: `Please change your password by clicking on this link ! : ${config.PROTOCOL}${config.HOST}:${config.PORT}/reset?token=${token}`
        })
        res.status(200).send({
            message: "mail sent"
        })
    } catch (error) {
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /resetPassword:
 *  post:
 *     tags: [Authentification]
 *     description: used to reset your password
 *     parameters:
 *        - name: register parameters
 *          description: required parameters to change your password
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  token:
 *                      type: string
 *                  password:
 *                      type: string
 *     responses:
 *       '404':
 *          description: User not found
 *       '403':
 *          description: token not valid or password
 *       '500':
 *          description: An error has occurred while trying to change the password
 *       '200':
 *          description: Password changed
 */

authentificationRouter.post('/resetPassword', async (req, res, next) => {
    try {
        const {password, token} = req.body;
        if (!password || !token) {
            return res.status(403).send({
                message: "no token or no new password"
            })
        }
        const decoded = jwt.verify(token, config.JWT_EMAIL_SECRET);
        const user = await User.findOne({where: {id: decoded.user_id }})
        if (!user)
            return res.status(404).send(error);
        const hashedPassword = await bcrypt.hashSync(password, 10);
        await user.set({
            password: hashedPassword
        })
        await user.save()
        return res.status(200).send({});
    } catch (error) {
        console.log(error)
        res.status(403).send({
            error: "Unauthorized"
        });
    }
});

module.exports = authentificationRouter;