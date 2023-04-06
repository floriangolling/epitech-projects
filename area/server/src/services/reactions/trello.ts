import {stopService} from '../../controllers/service';
import { IReactions } from "../interfaces";
import config from '../../config';
import axios from 'axios';

export class TrelloReaction extends IReactions {
    async trigger() {
        if (this.state === false)
            return;
        try {
            if (this.params.repoName) {
                await axios.post(`https://api.trello.com/1/boards/?name=${this.params.repoName}`, {
                    key: config.TRELLO_TOKEN,
                    token: this.client,
                })
            }
        } catch (error) {
            if (error.response && error.response.status && error.response.status === 403)
                stopService(this.serviceName, this._userId);
            console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
        }
    }
}

const trelloReaction = new TrelloReaction("BoardCreation", "create a board according the action (!trello nameOfBoard for chatReaction)", "trello");

export default [
    trelloReaction
]