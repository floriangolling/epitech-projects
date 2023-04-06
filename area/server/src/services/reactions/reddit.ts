import {stopService} from '../../controllers/service';
import { IReactions } from "../interfaces";
import axios from 'axios';

export class RedditReaction extends IReactions {
    async trigger() {
        try {
            if (this.state === false)
                return;
            if (this.params.repoName && this.params.response) {
                const params = new URLSearchParams();
                params.append('title', this.params.repoName);
                params.append('text', this.params.response);
                params.append('sr', 'r/areaepitech2022');
                params.append('kind', 'self');
                await axios.post('https://oauth.reddit.com/api/submit', params , {
                    headers: {
                        'Authorization': `Bearer ${this.client}`,
                        'content-type': 'application/x-www-form-urlencoded',
                    }
                })
            }
        } catch (error) {
            if (error.response && error.response.status && error.response.status === 403)
                stopService(this.serviceName, this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

const redditReaction = new RedditReaction("RedditPost", "post a reddit on the Area subreddit according to the action (!reddit nameOfReddit for chatReaction)", "reddit");

export default [
    redditReaction
]