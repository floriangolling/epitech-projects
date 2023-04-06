import express, { Request, Response } from 'express';
import Services from '../services'

const aboutRouter = express.Router();

aboutRouter.get('/', (req: Request, res: Response) => {
    try {
        return res.status(200).send({
            client: {
                host: req.ip
            },
            server: {
                current_time: new Date().getTime(),
                services: Services.map(service => ({
                    name: service.name,
                    actions: service.actions,
                    reactions: service.reactions
                }))
            }
        })
    } catch (error) {
        return res.status(500).send({
            message: error
        })
    }
});

export default aboutRouter;