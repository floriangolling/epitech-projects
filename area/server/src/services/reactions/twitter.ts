import {stopService} from '../../controllers/service';
import { IReactions } from "../interfaces";
import axios from 'axios';

export class TwitterReaction extends IReactions {
    async trigger() {
        if (this.state === false)
            return;
        try {
            await axios.post('https://api.twitter.com/2/tweets', {
                text: this.params.response
            }, {
                headers: {
                    Authorization: `Bearer ${this.client}`
                }
            })
        } catch (error) {
            if (error.response && error.response.status && error.response.status === 403)
                stopService('twitter', this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

const twitterReaction = new TwitterReaction("postTweet", "post a tweet according to the action", "twitter");

export default [
    twitterReaction
]