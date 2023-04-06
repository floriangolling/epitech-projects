import { Sequelize } from 'sequelize'
import * as Models from './models'
import config from '../config';

export async function connectToDatabase(postgres: Sequelize) {
    return new Promise(async (resolve, reject) => {
        try {

            for (const model of Object.values(Models))
                model.definition(postgres);
            for (const model of Object.values(Models))
                model.associate();         

            await postgres.authenticate();
            if (config.ERASE_DB == "true")
                await postgres.sync({ force: true });
            else
                await postgres.sync({ force: false });   
            console.log('\x1b[32m%s\x1b[0m' ,'[OK] Connection has been established succesfully.');
            resolve(undefined);
        } catch (error) {
            console.log('\x1b[31m%s\x1b[0m', '[ERROR] Unable to connect to the database: \n');
            console.log('\x1b[31m%s\x1b[0m', error);
            reject (error);
        }
    })
}