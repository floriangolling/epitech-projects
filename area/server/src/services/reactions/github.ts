import {stopService} from '../../controllers/service';
const { request } = require("@octokit/request");
import { IReactions } from "../interfaces";

export class RepoReaction extends IReactions {
    async trigger() {
        try {
            if (this.state === false)
                return;
            if (this.params.repoName) {
                const requestWithAuth = request.defaults({
                    headers: {
                      authorization: "token " + this.client,
                    },
                  });
                await requestWithAuth('POST /user/repos', {
                    name: this.params.repoName,
                })
            }
        } catch (error) {
            stopService(this.serviceName, this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

const repo = new RepoReaction("RepoReaction", "create a repository according to the action (!github nameOfRepo for chatReaction)", "github");

export default [
    repo
]