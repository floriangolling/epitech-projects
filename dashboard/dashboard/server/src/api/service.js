const Services      = require('../services/');
const express       = require('express');
const serviceRouter = express.Router();

/**
 * @swagger
 * /api/service:
 *  get:
 *     tags: [Services]
 *     description: used to get all services
 *     responses:
 *       '200':
 *          description: You successfully get all services.
 *          schema:
 *              properties:
 *                  services:
 *                      type: array
 *       '500':
 *          description: An error occured while retrieving the services
 */

serviceRouter.get('/', async (req, res) => {
    try {
       let response = [];

        for (let service of Services) {
            let obj = {
                properties: service.properties,
                widgets: service.widgets
            };
            response.push(obj);
        }
        res.status(200).send(response);
    } catch (error) {
        res.status(500).send({"message": "an error as occured", error});
    }
});

module.exports = serviceRouter;