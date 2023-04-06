const express       = require('express');
const authRouter    = express.Router();
const oauthServices = require('../oauth/index')

/**
 * @swagger
 * /oauths:
 *  get:
 *     tags: [Oauths]
 *     description: use to get all active oauths
 *     responses:
 *       '200':
 *          description: you sucessfully get all oauths
 *          schema:
 *              properties:
 *                  oauths:
 *                      type: array
 *       '500':
 *          description: An error has occurred while trying to get oauths
 */

authRouter.get('/oauths', async (req, res, next) => {
    try {
        let oauths = [];
        for (const service of oauthServices) {
            oauths.push(service.ServiceName.toLowerCase())
        }
        res.status(200).send(oauths);
    } catch (error) {
        res.status(500).send(error);
    }
})

/**
 * @swagger
 * /auth/link/:id:
 *  get:
 *     tags: [Oauths]
 *     description: used to get the auth link according to the id
 *     parameters:
 *        - name: oauth's name
 *          description: required parameters to get your oauth link
 *          in: path
 *          required: true
 *          schema:
 *              properties:
 *                  id:
 *                      type: string
 *     responses:
 *       '200':
 *          description: You successfully get oauth link
 *          schema:
 *              properties:
 *                  link:
 *                      type: string
 *       '500':
 *          description: An error has occurred while trying to get your oauth link
 */

authRouter.get('/auth/link/:id', (req, res) => {
    for (const service of oauthServices) {
        if (service.ServiceName === req.params.id) {
            return res.status(200).send(service.oauthLink)
        }
    }
    return res.status(500).send({
        error: "this oauth service does not exist"
    })
});

/**
 * @swagger
 * /auth/callback/:id:
 *  get:
 *     tags: [Oauths]
 *     description: get your acces_token according to the oauth id
 *     parameters:
 *        - name: oauth's name
 *          description: required parameters to get your oauth link
 *          in: path
 *          required: true
 *          schema:
 *              properties:
 *                  id:
 *                      type: string
 *     responses:
 *       '201':
 *          description: You successfully linked your account !
 *       '404':
 *          description: User not found
 *       '500':
 *          description: An error has occurred while trying to get your access_token
 */

authRouter.get('/auth/callback/:id', async (req, res, next) => {
    for (const service of oauthServices) {
        if (service.ServiceName === req.params.id) {
            return await service.setRefreshToken(req, res, next);
        }
    }
    return res.status(500).send({
        error: "this oauth service does not exist"
    })  
})

module.exports = authRouter;