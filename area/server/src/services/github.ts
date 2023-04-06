import { stopService } from '../controllers/service';
import { GithubReaction } from './reactions';
import { githubActions } from './actions';
import { IService } from './interfaces';

export class GithubService extends IService {
    async setup(param: any) {
        return new Promise(async (resolve, reject) => {
            try {
                if (!param || !param.refresh_token) {
                    reject('No refresh token for github')
                    stopService('github', this.user_id);
                }
                else {
                    this.client = param.refresh_token;
                    console.log('\x1b[32m%s\x1b[0m', `[OK] Github service UP.`);
                    resolve(null);
                }
              } catch (error) {
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                reject(error)
              }
        })
    }
}

const githubService = new GithubService('github');

for (const action of githubActions) {
    githubService.addAction(action);
}

for (const reaction of GithubReaction) {
    githubService.addReactions(reaction);
}

export default githubService;