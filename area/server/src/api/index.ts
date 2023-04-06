import componentRouter from "./components";
import serviceRouter from "./services";
import {Router} from 'express';

const apiRouter = Router();

apiRouter.use('/service', serviceRouter);
apiRouter.use('/component', componentRouter);

export default apiRouter;