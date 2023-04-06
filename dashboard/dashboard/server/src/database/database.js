const Sequelize = require('sequelize').Sequelize
const Models    = require('./models/');
const config    = require('../config');

const sequelize = new Sequelize(`postgres://${config.DB_USER}:${config.DB_PASSWORD}@${config.DB_HOST}:${config.DB_PORT}/${config.DB_NAME}`);

for (let model of Object.values(Models)) {
    model.definition(sequelize);
}

for (let model of Object.values(Models)) {
    model.associate();
}

module.exports = sequelize