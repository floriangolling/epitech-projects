import {stopService} from '../../controllers/service';
import { IActions } from "../interfaces";
import config from '../../config';
import { CronJob } from 'cron';
import axios from 'axios'

export class FirstAction extends IActions {
    _trelloUser = null as any;

    async listen(params: any) {
        this.lastData = null as any;

        let job = new CronJob('*/10 * * * * *', async () => {
            if (this.state === false)
                return;
                try {
                    if (!this._trelloUser) {
                        const request = await axios.get(`https://api.trello.com/1/members/me?key=${config.TRELLO_TOKEN}&token=${this.client}`)
                        this._trelloUser = request.data.id;
                    }
                    const requestBoards = await axios.get(`https://api.trello.com/1/members/${this._trelloUser}/boards?key=${config.TRELLO_TOKEN}&token=${this.client}`);
                    if (this.lastData && this.lastData != requestBoards.data) {
                        let data = [] as any;
                        for (const f of requestBoards.data) {
                            if (!(this.lastData.find((element: any) => element.name == f.name))) {
                                data.push(f);
                            }
                        }
                        for (const f of data) {
                            this.reaction.params.response = 'Your trello boards changed, have a look ! name: ' + f.name;
                            this.reaction.params.repoName = f.name;
                            this.reaction.trigger();
                        }
                        this.lastData = requestBoards.data;
                    } else {
                        this.lastData = requestBoards.data;
                    }
            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            }
        }, null, true, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Trello board action listening.`);
    }
}

export class SecondAction extends IActions {
    _trelloUser = null as any;

    async listen(params: any) {
        this.lastData = null as any;

        let job = new CronJob('*/10 * * * * *', async () => {
            if (this.state === false)
                return;
                try {
                    if (!this._trelloUser) {
                        const request = await axios.get(`https://api.trello.com/1/members/me?key=${config.TRELLO_TOKEN}&token=${this.client}`)
                        this._trelloUser = request.data.id;
                    }
                    const requestBoards = await axios.get(`https://api.trello.com/1/members/${this._trelloUser}/boardBackgrounds?key=${config.TRELLO_TOKEN}&token=${this.client}`);
                    if (this.lastData && this.lastData.length < requestBoards.data.length) {
                        let data = [] as any;
                        for (const f of requestBoards.data) {
                            if (!(this.lastData.find((element: any) => element.id === f.id))) {
                                data.push(f);
                            }
                        }
                        for (const f of data) {
                            this.reaction.params.response = 'New trello custom backgrounds changed, have a look ! id: ' + f.id;
                            this.reaction.params.repoName = f.id;
                            this.reaction.trigger();
                        }
                        this.lastData = requestBoards.data;
                    } else {
                        this.lastData = requestBoards.data;
                    }
            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            }
        }, null, true, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Trello background action listening.`);
    }
}

const firstAction = new FirstAction("BoardChanges", "there is an update on your boards", "trello");

const secondAction = new SecondAction("CustomBackground", "one of your background is updated", "trello");

export default [
    firstAction,
    secondAction
]