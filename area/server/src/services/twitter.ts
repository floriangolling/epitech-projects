import { IService } from "./interfaces";
import { twitterActions } from "./actions";
import { twitterReaction } from "./reactions";
import { stopService } from '../controllers/service';

export class TwitterService extends IService {
    async setup(param: any) {
        return new Promise(async (resolve: any, reject: any) => {
            try {
                if (!param || !param.refresh_token) {
                    stopService('twitter', this.user_id);
                    reject('No refresh token')
                }
                this.client = param.refresh_token;
                console.log('\x1b[32m%s\x1b[0m', `[OK] Twitter service UP.`);
                resolve (null);
            } catch (error) {
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                reject(error);
            }
        })
    }
}

const twitterService = new TwitterService("twitter");

for (const action of twitterActions) {
    twitterService.addAction(action);
}

for (const reaction of twitterReaction) {
    twitterService.addReactions(reaction);
}

export default twitterService;