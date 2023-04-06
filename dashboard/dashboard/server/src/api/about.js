const express       = require('express');
const Services      = require('../services')
const aboutRouter   = express.Router();

/**
 * @swagger
 * /about.json:
 *  get:
 *     tags: [Infos]
 *     description: get JSON file about
 *     responses:
 *       '200':
 *          description: JSON of our service
 *          schema:
 *              properties:
 *                  message:
 *                      type: string
 *       '500':
 *          description: An error has occurred while trying to find the JSON
 */

aboutRouter.get('/about.json', async (req, res, next) => {
    try {
        let json = {
            client: {
                host: ""
            },
            server: {
                current_time: 0,
                services: []
            }
        };
        json.client = {
            host: req.ip
        }
        for (let service of Services) {
            let obj = {
                properties: service.properties,
                widgets: service.widgets
            };
            json.server.services.push(obj);
        }
        json.server.current_time = new Date().getTime();
        res.status(200).send(json);
    } catch (error) {
        console.log(error);
        res.status(500).send(error);
    }
})

module.exports = aboutRouter;