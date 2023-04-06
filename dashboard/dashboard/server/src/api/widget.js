const express       = require('express');
const Widget        = require('../database/models/widget');
const widgetRouter  = express.Router();
const Services      = require('../services');
const { User }      = require('../database/models');

/**
 * @swagger
 * /api/widget:
 *  post:
 *     description: Use to create a new widget
 *     tags: [Widget]
 *     parameters:
 *        - name: widget parameters
 *          description: all widgets param
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  x:
 *                      type: string
 *                  y:
 *                      type: string
 *                  param:
 *                      type: string
 *                  widgetName:
 *                      type: string
 *                  serviceName:
 *                      type: string
 *     responses:
 *       '400':
 *          description: No inputs
 *       '500':
 *          description: An error has occurred
 *       '200':
 *          description: Widget created
 */

widgetRouter.post('/', async (req, res, next) => {
    try {
        const {x, y, param, widgetName, serviceName} = req.body;
        if (!(x != undefined && y != undefined && param && widgetName && serviceName)) {
            return res.status(400).send({
                error: "All input is required"
            });
        }
        const newWidget = await Widget.create({x, y, widgetName, serviceName, refreshTime: 15, param, UserId: req.userData.user_id });
        res.status(200).send(newWidget);
    } catch (error) {
        console.log(error)
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /api/widget:
 *  get:
 *     description: used to get all your widgets using header autho
 *     tags: [Widget]
 *     responses:
 *       '200':
 *          description: You successfully received all your widgets !
 *       '500':
 *          description: An error has occurred
 */

widgetRouter.get('/', async (req, res, next) => {
    try {
        const widget = await Widget.findAll({where: {UserId: req.userData.user_id }});
        res.status(200).send(widget);
    } catch (error) {
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /api/widget/:id:
 *  put:
 *     description: Use to modify your widget
 *     tags: [Widget]
 *     parameters:
 *        - name: widget'id
 *          in: path
 *          required: true
 *          schema:
 *              properties:
 *                  id: integer
 *        - name: widget parameters
 *          description: all widgets param
 *          in: body
 *          required: true
 *          schema:
 *              properties:
 *                  x:
 *                      type: string
 *                  y:
 *                      type: string
 *                  param:
 *                      type: string
 *                  widgetName:
 *                      type: string
 *                  serviceName:
 *                      type: string
 *     responses:
 *       '400':
 *          description: No inputs
 *       '404'
 *          description: Widget not found
 *       '500':
 *          description: An error has occurred
 *       '200':
 *          description: Widget saved
 */

widgetRouter.put('/:id', async (req, res, next) => {
    try {
        const {refreshTime, parameter, x, y} = req.body
        if (!refreshTime && !parameter && !x && !y) {
            return res.status(400).send({
                error: "all input is required"
            })
        }
        if (refreshTime != undefined && refreshTime <= 0) {
            return res.status(400).send({
                error: "refresh time must be greater than 0"
            })            
        }
        const widget = await Widget.findOne({where: {id: req.params.id }});
        if (!widget) {
            return res.status(404).send({
                error: "widget not found"
            })
        }
        if (refreshTime) {
            await widget.set({ refreshTime: refreshTime })
        }
        if (parameter) {
            await widget.set({ param: parameter })
        }
        if (x) {
            await widget.set({ x })
        }
        if (y) {
            await widget.set({ y })
        }
        await widget.save();
        res.status(200).send({
            message: "widget saved !"
        })
    } catch (error) {
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /api/widget/:id
 *  delete:
 *     description: used to delete a widget
 *     tags: [Widget]
 *     parameters:
 *        - name: id's widget
 *          description: used to find the widget
 *          in: path
 *          required: true
 *          schema:
 *              properties:
 *                  id:
 *                      type: integer
 *     responses:
 *       '200':
 *          description: Widget deleted
 *       '404':
 *          description: widget's deleted
 *       '500':
 *          description: An error has occurred
 *       '403':
 *          description: Unauthorized
 */

widgetRouter.delete('/:id', async (req, res, next) => {
    try {
        const widget = await Widget.findOne({where: {id: req.params.id }});
        if (!widget) {
            return res.status(404).send({
                error: "widget not found"
            })
        }
        if (req.userData.user_id === widget.UserId) {
            const deletedWidget = await widget.destroy();
            widget.save();
            return res.status(200).send(deletedWidget);
        } else {
            return res.status(403).send({
                error: "permissions required"
            })
        }
    } catch (error) {
        console.log(error);
        res.status(500).send(error);
    }
});

/**
 * @swagger
 * /api/widget/:id:
 *  get:
 *     description: use to get a specifig widget's information
 *     tags: [Widget]
 *     parameters:
 *        - name: widget's id
 *          description: required parameters find the widget
 *          in: path
 *          required: true
 *          schema:
 *              properties:
 *                  id:
 *                      type: string
 *     responses:
 *       '200':
 *          description: You successfully retrieved the widget's data
 *       '404':
 *          description: Widget not found
 *       '500':
 *          description: An error has occurred
 */

widgetRouter.get('/:id', async (req, res, next) => {
    try {
        const widget = await Widget.findOne({where: {id: req.params.id}});
        let widgetInterface = {};
        let serInterface = {};
        if (!widget) {
            return res.status(404).send({
                error: "widget not found"
            })
        }
        for (let ser of Services) {
            for (let wid of ser.widgets) {
                if (widget.widgetName === wid.properties.name) {
                    widgetInterface = wid;
                    serInterface = ser;
                    break;
                }
            }
        }
        const user = await User.findOne({where: {id: req.userData.user_id}});
        let response;
        if (user.oauths && user.oauths[serInterface.properties.name.toLowerCase()])
            response = await widgetInterface.callThisWidget(serInterface.getClient(), widget.param, user.oauths[serInterface.properties.name.toLowerCase()].refresh_token);
        else
            response = await widgetInterface.callThisWidget(serInterface.getClient(), widget.param, "");
        res.status(200).send(response);
    } catch (error) {
        console.log(error)
        res.status(500).send(error);
    }
});

module.exports = widgetRouter;