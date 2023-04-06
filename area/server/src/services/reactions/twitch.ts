import {stopService} from '../../controllers/service';
import { IReactions } from "../interfaces";

export class chatReaction extends IReactions {
    async trigger() {
        try {
            if (this.state === false)
                return;
            this.params.channel = this.client.currentNick;
            if (this.params.channel && this.params.channel[0] == '#')
                await this.client.say(this.params.channel, this.params.response);
            else
                await this.client.say('#' + this.params.channel, this.params.response);
        } catch (error) {
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            stopService(this.serviceName, this._userId);
        }
    }
}

const chatAnswer = new chatReaction("Chat", "says a message according the action on your channel", "twitch");

export default [
    chatAnswer,
]