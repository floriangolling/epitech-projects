const express       = require('express');
const User          = require('../database/models/user');
const Widget        = require('../database/models/widget');
const userRouter    = express.Router();
const bcrypt        = require('bcrypt');


/**
 * @swagger
 * /api/user:
 *  get:
 *     tags: [User]
 *     description: used to receive the user's informations.
 *     responses:
 *       '200':
 *          description: You received your info as JSON
 *       '404':
 *          description: User not found
 *       '500':
 *          description: An error has occurred
 */

userRouter.get('/', async (req, res, next) => {
    try {
        const user = await User.findOne({ where: {id: req.userData.user_id }})
        if (!user)
            res.status(404).send({
                error: "user not found"
            })
        else {
            const widgets = await Widget.findAll({where: { UserId: req.userData.user_id }})
            let canDisconnectOauth;
            if (!user.password)
                canDisconnectOauth = false
            else
                canDisconnectOauth = true
            res.status(200).send({id: user.id, username: user.username, email: user.email, numberOfWidgets: widgets.length, twitchToken: user.twitchToken, oauths: user.oauths, canDisconnectOauth });
        }
    } catch (error) {
        console.log(error);
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /api/user/:id:
 *  put:
 *     tags: [User]
 *     description: Use to change your password / username / Oauths methods
 *     parameters:
 *        - name: user's id
 *          in: path
 *          require: true
 *          schema:
 *              properties:
 *                  id:
 *                      type: integer
 *        - name: user parameters
 *          description: all inputs u can change
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  password:
 *                      type: string
 *                  username:
 *                      type: string
 *                  auth:
 *                      type: string
 *     responses:
 *       '404':
 *          description: User not found
 *       '403':
 *          description: No inputs
 *       '500':
 *          description: An error has occurred while trying to change user's infos
 *       '200':
 *          description: user's infos are saved
 */

userRouter.put('/:id', async (req, res, next) => {
    try {
        const {password, username, auth} = req.body
        if (!password && !username && !auth) {
            return res.status(400).send({
                error: "all input is required"
            })
        }
        const user = await User.findOne({ where: {id: req.userData.user_id }})
        if (!user)
            res.status(404).send({
                error: "user not found"
            })
        else {
            if (password) {
                const hashedPassword = await bcrypt.hashSync(password, 10);
                await user.set({
                    password: hashedPassword
                })
            }
            if (username) {
                user.set({
                    username
                })
            }
            if (auth && user.oauths[auth]) {
                user.oauths[auth] = {};
                await user.changed('oauths', true);
            }
            await user.save();
        }
        res.status(200).send({
            message: "user successfuly changed"
        })
    } catch (error) {
        console.log(error);
        res.status(500).send(error)
    }
})

module.exports = userRouter;