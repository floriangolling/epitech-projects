import { stopService } from '../controllers/service';
import { redditReaction } from "./reactions";
import { redditActions } from "./actions";
import { IService } from "./interfaces";
import Config from '../config';
import axios from 'axios';

export class RedditService extends IService {
    async setup(param: any) {
        return new Promise(async (resolve: any, reject: any) => {
            try {
                if (!param || !param.refresh_token) {
                    stopService('reddit', this.user_id);
                    reject('No refresh token')
                }
                const credentials = Buffer.from(`${Config.REDDIT_CLIENT_ID}:${Config.REDDIT_CLIENT_SECRET}`).toString("base64")
                const config = {
                    headers: {
                        'User-Agent': 'Sample app',
                        Authorization: 'Basic ' + credentials
                    }
                }
                const params = new URLSearchParams();
                params.append('refresh_token', param.refresh_token);
                params.append('grant_type', 'refresh_token');
                const request = await axios.post('https://www.reddit.com/api/v1/access_token', params, config);
                const { access_token } = request.data;
                this.client = access_token;
                console.log('\x1b[32m%s\x1b[0m', `[OK] Reddit service UP.`);
                resolve (null);
            } catch (error) {
                stopService('reddit', this.user_id);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                reject(error);
            }
        })
    }
}

const redditService = new RedditService("reddit");

for (const action of redditActions) {
    redditService.addAction(action);
}

for (const reaction of redditReaction) {
    redditService.addReactions(reaction);
}

export default redditService;