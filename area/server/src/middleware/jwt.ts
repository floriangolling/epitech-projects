import {Request, Response, NextFunction } from 'express';
import User from '../database/models/user';
import config from '../config';
import jwt from 'jsonwebtoken';

export default async function(req: Request, res: Response, next: NextFunction) {
    try {
        const token = req.headers.authorization.replace("Bearer ", "");
        const decoded = jwt.verify(token, config.JWT_SECRET);
        const user = await User.findOne({where: {id: decoded.user_id }})
        if (!user) {
            return res.status(404).send({
                message: 'User not found !'
            })
        }
        req.userData = decoded;
        next();
        } catch (error) {
            return res.status(403).send({message: 'Unauthorized'});
    }
}