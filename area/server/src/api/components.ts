import {setupServices, removeComponent} from '../controllers/service';
import {Router, Request, Response, NextFunction} from 'express';
import { runningComponent } from '../types/component';
import { Component, User } from "../database/models";
import MiddlewareJwt from '../middleware/jwt';
import allServices from '../services/index';

const componentRouter = Router();

componentRouter.use(MiddlewareJwt);

function findComponentDescription(serviceActionName: string, serviceReactionName: string, actionName: string, reactionName: string) {
    let description = "If ";
    for (const service of allServices) {
        if (service.name === serviceActionName) {
            for (const action of service.actions) {
                if (action.name === actionName)
                    description += action.description;
            }
        }
    }
    for (const service of allServices) {
        if (service.name === serviceReactionName) {
            for (const reaction of service.reactions) {
                if (reaction.name === reactionName) {
                    description += ' then ' + reaction.description;
                }
            }
        }
    }
    return description;
}

function findComponentGlobalState(userId: number, serviceName: string) {
    if (globalThis.RunningServices.find((element) => element.id === userId && element.service.name === serviceName))
        return true;
    return false;
}

componentRouter.get('/', async (req: Request, res: Response, next: NextFunction) => {
    try {
        let components = await Component.findAll({where: { UserId: req.userData.user_id }})
        let componentsFormated = [] as Array<runningComponent>;
        for (const service of globalThis.RunningServices) {
            if (service.id === req.userData.user_id) {
                if (service.service) {
                    for (const cmp of service.service.actions) {
                        for (let comp of components) {
                            if (cmp.id == comp.id) {
                                let state = cmp.state;
                                if (findComponentGlobalState(req.userData.user_id, comp.serviceReactionName) === false)
                                    state = false;
                                const desc = findComponentDescription(comp.serviceActionName, comp.serviceReactionName, comp.actionName, comp.reactionName);
                                componentsFormated.push({
                                    id: comp.id,
                                    state: state,
                                    actionName: comp.actionName,
                                    reactionName: comp.reactionName,
                                    serviceActionName: comp.serviceActionName,
                                    serviceReactionName: comp.serviceReactionName,
                                    description: desc
                                })
                            }
                        }
                    }
                }
            }
        }
        for (const comp of components) {
            if (!componentsFormated.find((element: runningComponent) => element.id === comp.id)) {
                const desc = findComponentDescription(comp.serviceActionName, comp.serviceReactionName, comp.actionName, comp.reactionName);
                componentsFormated.push({
                    id: comp.id,
                    state: false,
                    actionName: comp.actionName,
                    reactionName: comp.reactionName,
                    serviceActionName: comp.serviceActionName,
                    serviceReactionName: comp.serviceReactionName,
                    description: desc
                })
            }
        }
        return res.status(200).send({
            data: componentsFormated
        })
    } catch (error) {
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
})

componentRouter.post('/', async (req: Request, res: Response, next: NextFunction) => {
    try {
        const {serviceReactionName, serviceActionName, actionName, reactionName} = req.body;
        if (!serviceActionName || !serviceReactionName || !actionName || !reactionName) {
            return res.status(404).send({
                message: 'Bad request !'
            })
        }
        const newComponent = await Component.create({
            reactionName,
            serviceActionName,
            serviceReactionName,
            actionName,
            UserId: req.userData.user_id
        })
        res.status(200).send({
            message: 'Component created !'
        })
        try {
            await setupServices();
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    } catch (error) {
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
})

componentRouter.delete('/:id', async (req: Request, res: Response) => {
    try {
        const user = await User.findOne({where: {id: req.userData.user_id }});
        if (!user) {
            return res.status(404).send({
                message: 'User not found'
            })
        }
        const component = await Component.findOne({where: { id: req.params.id, UserId: user.id }})
        if (!component)
            return res.status(401).send({
                message: 'Component not found'
            })
        const deletedWidget = await component.destroy();
        await component.save();
        res.status(200).send({
            message: deletedWidget
        })
        try {
            await removeComponent(user.id, parseInt(req.params.id, 10));
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
})

export default componentRouter;