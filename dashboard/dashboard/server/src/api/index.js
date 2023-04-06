const serviceRouter = require('./service');
const express       = require('express');
const apiRouter     = express.Router();
const middlewareJWT = require('./jwt')
const swagger       = require('../swagger');
const swaggerUi     = require('swagger-ui-express');
const widgetRouter  = require('./widget');
const userRouter    = require('./user');

apiRouter.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swagger));
apiRouter.use(middlewareJWT);
apiRouter.use('/user', userRouter);
apiRouter.use('/service', serviceRouter);
apiRouter.use('/widget', widgetRouter);

module.exports = apiRouter;