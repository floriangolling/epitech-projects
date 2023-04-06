import createReaction from "../services/reactions/create";
import createService from "../services/createService";
import createAction from "../services/actions/create";
import { User, Component } from "../database/models";
import { IService } from "../services/interfaces";

export async function setupServices() {
    return new Promise( async (resolve, reject) => {
        try {
            let Users = await User.findAll();
            for (const user of Users) {
                const Components = await Component.findAll({where: {UserId: user.id}});
                for (const component of Components) {
                    if (globalThis.RunningServices.length === 0 || globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceReactionName).length === 0) {
                        try {
                            let ser = await createService({serviceName: component.serviceReactionName}, user)
                            globalThis.RunningServices.push({
                                id: user.id,
                                service: ser
                            })                    
                        } catch (error) {
                            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                        }
                    }
                    if (globalThis.RunningServices.length === 0 || globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceActionName).length === 0) {
                        try {
                            let ser = await createService({serviceName: component.serviceActionName}, user)
                            globalThis.RunningServices.push({
                                id: user.id,
                                service: ser
                            })
                        } catch (error) {
                            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                        }
                    } else {
                    }              
                }
            }
            Users = await User.findAll();
            for (const user of Users) {
                const Components = await Component.findAll({where: {UserId: user.id}});
                for (const component of Components) {
                    if (globalThis.RunningServices.length === 0 || globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceReactionName).length === 0 || globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceActionName).length === 0 ) {
                        continue;
                    }
                    const serviceReaction : IService = globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceReactionName)[0].service;
                    const serviceAction : IService = globalThis.RunningServices.filter(elem => elem.id === user.id && elem.service.name === component.serviceActionName)[0].service;
                    if (!serviceAction || !serviceAction) {
                        console.log('\x1b[31m%s\x1b[0m', '[ERROR] A service couldnt be loaded.')
                        continue;
                    }
                    serviceAction.user_id = user.id;
                    serviceReaction.user_id = user.id;
                    if (serviceReaction.reactions.filter(elem => elem.id === component.id).length !== 0 || serviceAction.actions.filter(elem => elem.id === component.id).length !== 0) {
                        continue;
                    }
                    const reaction = await createReaction({ reactionName: component.reactionName }) as any;
                    const action = await createAction({ actionName: component.actionName }) as any;
                    if (!action || !reaction) {
                        console.log('\x1b[31m%s\x1b[0m', '[ERROR] An action/reaction couldnt be loaded.')
                        continue;
                    }
                    action._userId = user.id;
                    reaction._userId = user.id;
                    action.id = component.id;
                    reaction.id = component.id;
                    reaction.client = serviceReaction.client;
                    serviceReaction.addReactions(reaction);
                    action.client = serviceAction.client;
                    serviceAction.addAction(action);
                    action.reaction = reaction;
                    action.listen();
                }
            }
            resolve(null);
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            reject(error);
        }
    })
}

export async function stopService(serviceName: string, userId: number) {
    try {
        for (const ser of globalThis.RunningServices) {
            ser.service.state = false;
            if (ser.id == userId && ser.service.name === serviceName) {
                for (const compo of ser.service.actions) {
                    compo.state = false;
                }
                for (const compo of ser.service.reactions) {
                    compo.state = false;
                }
            }
        }
        globalThis.RunningServices = globalThis.RunningServices.filter(elem => elem.service.name != serviceName && elem.id == userId);
        const user = await User.findOne({where: {id: userId }});
        if (!user) {
            return;
        }
        let fields = user.oauths;
        fields[serviceName].refresh_token = null;
        await user.changed('oauths', true);
        await user.save();
        console.log('\x1b[31m%s %s\x1b[0m', '[OK]', `Service stopped ${serviceName} for user ${userId}`);
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
    }
}

export async function removeComponent(userId : number, componentId: number) {
    return new Promise(async (resolve, reject) => {
        try {
            for (const service of globalThis.RunningServices) {
                if (service.id === userId) {
                    for (const comp of service.service.reactions) {
                        if (comp.id === componentId)
                            comp.state = false;
                    }
                    for (const comp of service.service.actions) {
                        if (comp.id === componentId)
                            comp.state = false;
                    }
                }
            }
            console.log('\x1b[32m%s\x1b[0m', `[OK] Widget removed for user ${userId}`);
            resolve(null);
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            reject(error);
        }
    })
}