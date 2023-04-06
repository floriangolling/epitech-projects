const path          = require('path');
const Config        = require('./config');
const swaggerJSDoc  = require('swagger-jsdoc');

const server = Config.HOST + ':' + Config.PORT;

const swaggerOptions = {
    swaggerDefinition: {
        info: {
            title: 'Dashboard',
            description: 'Dashboard API Swagger'
        },
        servers: [server]
    },
    apis: [
        path.join(__dirname, 'api', 'service.js'),
        path.join(__dirname, 'api', 'authentification.js'),
        path.join(__dirname, 'api', 'widget.js'),
        path.join(__dirname, 'api', 'about.js'),
        path.join(__dirname, 'api', 'user.js'),
        path.join(__dirname, 'api', 'OauthRouter.js'),
        path.join(__dirname, 'database', 'models', 'swagger-models.js')
    ]
}

const swaggerdocs = swaggerJSDoc(swaggerOptions);

module.exports = swaggerdocs;