import User from "../database/models/user";
import { TwitterService } from './twitter';
import { TwitchService } from "./twitch";
import { GithubService } from './github';
import { TrelloService } from './trello';
import { RedditService } from './reddit';
import { IService } from "./interfaces";

async function createService(params: any, user: User): Promise<IService> {
    return new Promise(async (resolve, reject) => {
        try {
        let client = null;
        switch (params.serviceName) {
            case 'twitch':
                if (!user || !user.oauths || !user.oauths.twitch || !user.oauths.twitch.refresh_token || !user.oauths.twitch.username) {
                    reject('No refresh token for twitch');
                    break;
                }
                client = new TwitchService('twitch');
                await client.setup({ refresh_token: user.oauths.twitch.refresh_token, channel: user.oauths.twitch.username });
                client.state = true;
                break;
            case 'github':
                if (!user || !user.oauths || !user.oauths.github || !user.oauths.github.refresh_token) {
                    reject('No refresh token for github');
                    break;
                }
                client = new GithubService('github');
                await client.setup({ refresh_token: user.oauths.github.refresh_token})
                client.state = true;
                break;
            case 'trello':
                if (!user || !user.oauths || !user.oauths.trello || !user.oauths.trello.refresh_token) {
                    reject('No refresh token for trello')
                    break;
                }
                client = new TrelloService('trello');
                await client.setup({ refresh_token: user.oauths.trello.refresh_token });
                client.state = true;
                break;
            case 'twitter':
                if (!user || !user.oauths || !user.oauths.twitter || !user.oauths.twitter.refresh_token) {
                    reject('No refresh token for twitter');
                    break;
                }
                client = new TwitterService('twitter');
                client.setup({ refresh_token: user.oauths.twitter.refresh_token });
                client.state = true;
                break;
            case 'reddit':
                if (!user || !user.oauths || !user.oauths.reddit || !user.oauths.reddit.refresh_token) {
                    reject('No refresh token for reddit');
                    break;
                }
                client = new RedditService('reddit');
                await client.setup({ refresh_token: user.oauths.reddit.refresh_token });
                client.state = true;
                break;
            default:
                break;
        }
        resolve(client);
    } catch (error) {
        reject (error);
    }})
}

export default createService;