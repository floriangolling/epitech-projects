import {stopService} from '../../controllers/service';
import { IActions } from "../interfaces";

export class chatAction extends IActions {
    lastMessage = null as any;
    async listen(params: any) {
        try {
            this.client.onDisconnect((manually: any, reason: any) => {
                stopService(this.serviceName, this._userId);
            })
            this.client.onMessage((channel: any, user: any, message: string) => {
                if (this.state === false || (this.lastData && message == this.lastData))
                    return;
                this.reaction.params.channel = channel;
                this.reaction.params.response =  `${user} said : ${message}`
                if (message.split(' ')[0] == '!github')
                    this.reaction.params.repoName = message.split(' ')[1];
                else if (message.split(' ')[0] == '!trello')
                    this.reaction.params.repoName = message.split(' ')[1];
                else if (message.split(' ')[0] == '!reddit')
                    this.reaction.params.repoName = message.split(' ')[1];
                else
                    this.reaction.params.repoName = null;
                this.lastMessage = this.reaction.params.repName;
                this.reaction.trigger();
            })
            console.log('\x1b[32m%s\x1b[0m', `[OK] Twitch chat action listening.`);
        } catch (error) {
            stopService(this.serviceName, this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

export class subAction extends IActions {
    async listen(params: any) {
        try {
            this.client.onDisconnect((manually: any, reason: any) => {
                stopService(this.serviceName, this._userId);
            })
            this.client.onSub((channel: any, user: any) => {
                if (this.state === false)
                    return;
                this.reaction.params.response = `${user} just subsribed thanks you >_<!`
                this.reaction.params.repoName = user;
                this.reaction.params.channel = channel;
                this.reaction.trigger();
            });
            console.log('\x1b[32m%s\x1b[0m', `[OK] Twitch sub action listening.`);
        } catch (error) {
            stopService(this.serviceName, this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

const sub = new subAction("SubAction", "you subscribe on a channel", "twitch");
const chat = new chatAction("ChatReaction", "someone post a message on your channel","twitch");

export default [
    chat,
    sub
]