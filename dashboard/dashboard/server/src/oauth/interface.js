class OAuthService {
    constructor(ServiceName, oauthLink) {
        this.ServiceName = ServiceName;
        this.oauthLink = oauthLink;
    }
    async setRefreshToken(req, res, next) {
        throw new Error("not implemented, please extends this interface and set this function according to your service oauth");
    }

    async loginCreateAccount(req, res, next) {
        throw new Error("not implemented, please extends this interface and set this function according to your service oauth");
    }
}

module.exports = OAuthService;