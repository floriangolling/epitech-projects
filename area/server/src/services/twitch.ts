import { stopService } from '../controllers/service';
import { StaticAuthProvider } from '@twurple/auth';
import { twitchReaction } from './reactions';
import { ChatClient } from '@twurple/chat';
import { twitchActions } from './actions';
import { IService } from './interfaces';
import Config from '../config';
import axios from 'axios'

export class TwitchService extends IService {
    async setup(param: any) {
        return new Promise(async (resolve, reject) => {
            try {
                if (!param || !param.channel || !param.refresh_token) {
                    stopService('twitch', this.user_id);
                    reject('No refresh token!')
                }
                else {
                    const params = new URLSearchParams();
                    const config = {
                        headers: {
                        'Content-type': 'application/x-www-form-urlencoded',
                        },
                    };
                    params.append('grant_type', 'refresh_token');
                    params.append('client_id', Config.TWITCH_CLIENT_ID);
                    params.append('client_secret', Config.TWITCH_CLIENT_SECRET);
                    params.append('refresh_token', param.refresh_token);
                    params.append('scope', 'chat:read chat:edit')
                    const request = await axios.post(
                        'https://id.twitch.tv/oauth2/token',
                        params,
                        config,
                    );
                    const authProvider = new StaticAuthProvider(Config.TWITCH_CLIENT_ID, request.data.access_token);
                    const chatClient = new ChatClient({ authProvider, channels: [param.channel] });
                    await chatClient.connect();  
                    this.client = chatClient;
                    console.log('\x1b[32m%s\x1b[0m', `[OK] Twitch service UP.`);
                    resolve(null);
                }
              } catch (error) {
                stopService('twitch', this.user_id);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                reject(error)
              }
        })
    }
}

const twitchService = new TwitchService('twitch');

for (const action of twitchActions) {
    twitchService.addAction(action);
}

for (const reaction of twitchReaction) {
    twitchService.addReactions(reaction);
}

export default twitchService;