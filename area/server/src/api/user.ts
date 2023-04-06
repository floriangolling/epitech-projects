import express, { NextFunction, Request, Response, Router } from 'express';
import { stopService } from '../controllers/service';
import jwtmiddleware from '../middleware/jwt';
import User from '../database/models/user';
import bcrypt from 'bcrypt';

const userRouter = Router();

userRouter.get('/me', jwtmiddleware, async (req: Request, res: Response) => {
    try {
        let authsConnected = [] as any;
        const user = await User.findOne({where: {id: req.userData.user_id}});
        if (!user) {
            return res.status(404).send({
                message: 'User not found !'
            })
        }
        if (user.oauths) {
            for (const auth in user.oauths) {
                if (user.oauths[auth].refresh_token) {
                    authsConnected.push(auth);
                }
            }
            return res.status(200).send({
                oauths: authsConnected,
                username: user.username
            })
        } else {
            return res.status(200).send({
                oauths: authsConnected,
                username: user.username
            })
        }
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: 'Internal server error'
        })
    }
})

userRouter.put('/password', jwtmiddleware ,async(req: Request, res: Response, next: NextFunction) => {
    try {

        const {password} = req.body;
        if (!password)
            return res.status(400).send({
                message: 'Password required'
            })
        const user = await User.findOne({ where: { id: req.userData.user_id }});
        if (!user) {
            return res.status(404).send({
                message: 'User not found'
            })
        }
        const hashedPassword = await bcrypt.hashSync(password, 10);
        await user.set({
            password: hashedPassword
        })
        await user.save();
        return res.status(200).send({
            message: 'Your password is changed gros bg'
        })
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: 'Internal error server'
        })
    }
});

userRouter.put('/disconnect/:id', jwtmiddleware, async (req: Request, res: Response, next: NextFunction) => {
    try {
        stopService(req.params.id, req.userData.user_id);
        return res.status(200).send({
            message: 'Disconnected'
        })
    } catch (error) {
        console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        return res.status(500).send({
            message: error
        })
    }
})

export default userRouter;