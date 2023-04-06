import { Sequelize } from 'sequelize';
import config from '../config';

const sequelize = new Sequelize(`postgres://${config.DB_USER}:${config.DB_PASSWORD}@${config.DB_HOST}:${config.DB_PORT}/${config.DB_NAME}`, {
    logging: false
});

export default sequelize;