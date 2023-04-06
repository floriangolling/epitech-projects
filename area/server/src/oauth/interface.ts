import { Request, Response, NextFunction } from 'express';

export default class IOAuthService {
    serviceName: string;
    oauthLink: string;
    canCreate: boolean;
    constructor(_serviceName: string, _oauthLink: string, _canCreate: boolean) {
        this.serviceName = _serviceName;
        this.oauthLink = _oauthLink;
        this.canCreate = _canCreate
    }

    async setRefreshToken(req: Request, res: Response, next: NextFunction, verifier: any, tokenSecret: any, token: any): Promise<any> {
        throw new Error("not implemented, please extends this interface and set this function according to your service oauth");
    }

    async loginCreateAccount(req: Request, res: Response, next: NextFunction, verifier: any, tokenSecret: any, token: any): Promise<any>{
        throw new Error("not implemented, please extends this interface and set this function according to your service oauth");        
    }
}