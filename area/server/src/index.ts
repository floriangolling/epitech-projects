import { setupServices } from './controllers/service';
import sequelizeInstance from './database/postgres';
import { connectToDatabase } from './database';
import aboutRouter from './api/about';
import bodyParser from 'body-parser';
import userRouter from './api/user';
import authRouter from './api/auth';
import apiRouter from './api/';
import express from 'express';
import config from './config';
import cors from 'cors';

// Creating the back-end app.

const app = express();

// Middlewares

app.use(cors());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Routers

app.use('/about.json', aboutRouter);
app.use(authRouter);
app.use(userRouter);
app.use('/api', apiRouter);

// Launching and connect to database.

connectToDatabase(sequelizeInstance).then(() => {
    globalThis.RunningServices = [];
    app.listen(config.PORT, async () => {
        try {
            await setupServices();
            console.log('\x1b[32m%s\x1b[0m', `[OK] Area running on ${config.HOST}:${config.PORT}.`);
        } catch (error) {
            throw new Error(`[ERROR] Error trying to setup services.\n ${error}`);
        }
    });
}).catch((error) => {
    console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
});