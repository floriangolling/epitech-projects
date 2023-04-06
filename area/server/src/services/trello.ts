import { stopService } from '../controllers/service';
import { trelloReaction } from './reactions';
import { trelloActions } from './actions';
import { IService } from './interfaces';

export class TrelloService extends IService {
    async setup(param: any) {
        return new Promise(async (resolve, reject) => {
            try {
                if (!param || !param.refresh_token) {
                    stopService('trello', this.user_id);
                    reject('No refresh token')
                }
                else {
                    this.client = param.refresh_token;
                    console.log('\x1b[32m%s\x1b[0m', `[OK] Trello service UP.`);
                    resolve(null);
                }
              } catch (error) {
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                stopService('trello', this.user_id);
                reject(error)
              }
        })
    }
}

const trelloService = new TrelloService('trello');

for (const action of trelloActions) {
    trelloService.addAction(action);
}

for (const reaction of trelloReaction) {
    trelloService.addReactions(reaction);
}

export default trelloService;