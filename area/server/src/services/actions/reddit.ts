import {stopService} from '../../controllers/service';
import { IActions } from "../interfaces";
import { CronJob } from 'cron';
import axios from 'axios';

export class HotActionReddit extends IActions {
    async listen(params: any) {
        this.lastData = null as any;
        let job = new CronJob('*/10 * * * * *', async () => {
            try {
                if (this.state === false)
                    return;
                const request = await axios.get('https://oauth.reddit.com/hot', {
                    headers: {
                        'User-Agent': 'Sample app',
                        'Authorization': `Bearer ${this.client}`
                    }
                })
                if (this.lastData && this.lastData != request.data.data.children) {
                    let data = [] as any;
                    for (const f of request.data.data.children) {
                        if (!(this.lastData.find((element: any) => element.data.title === f.data.title))) {
                            data.push(f);
                        }
                    }
                    for (const f of data) {
                        this.reaction.params.response = 'New hot reddit ! title: ' + f.data.title;
                        this.reaction.params.repoName = f.data.title;
                        this.reaction.trigger();                    
                    }
                    this.lastData = request.data.data.children;
                } else {
                    this.lastData = request.data.data.children;
                }
            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                }
        }, null, true, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Reddit hot action listening.`);
    }
}

export class BestActionReaction extends IActions {
    async listen(params: any) {
        this.lastData = null as any;
        let job = new CronJob('*/10 * * * * *', async () => {
            try {
                if (this.state === false)
                    return;
                const request = await axios.get('https://oauth.reddit.com/best', {
                    headers: {
                        'User-Agent': 'Sample app',
                        'Authorization': `Bearer ${this.client}`
                    }
                })
                if (this.lastData && this.lastData != request.data.data.children) {
                    let data = [] as any;
                    for (const f of request.data.data.children) {
                        if (!(this.lastData.find((element: any) => element.data.title === f.data.title))) {
                            data.push(f);
                        }
                    }
                    for (const f of data) {
                        this.reaction.params.response = 'New best reddit ! title: ' + f.data.title;
                        this.reaction.params.repoName = f.data.title;
                        this.reaction.trigger();                    
                    }
                    this.lastData = request.data.data.children
                } else {
                    this.lastData = request.data.data.children;
                }
            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            }
        }, null, true, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Reddit best action listening.`);
    }
}

const firstAction = new BestActionReaction("BestList", "there is a new best post", "reddit");

const secondAction = new HotActionReddit("HotBest", "there is a new hot post", "reddit");

export default [
    firstAction,
    secondAction
]