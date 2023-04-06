import {stopService} from '../../controllers/service';
import { IActions } from "../interfaces";
import { CronJob } from 'cron';
import axios from 'axios';

export class TwitterFollowerAction extends IActions {
    public userId: number;

    async listen(params: any) {
        this.lastData = null as any;
        this.userId = null;

        let job = new CronJob('*/2 * * * *', async() => {
            if (this.state === false)
                return;
            try {
                const requestUser = await axios.get('https://api.twitter.com/2/users/me', {
                    headers: {
                        authorization: 'Bearer ' + this.client
                    }
                })
                this.userId = requestUser.data.data.id;
                if (!this.userId)
                    return;
                const requestData = await axios.get('https://api.twitter.com/2/users/' + this.userId + '/followers?max_results=1000', {
                    headers: {
                        authorization: 'Bearer ' + this.client
                    }
                })
                if (this.lastData && this.lastData.length < requestData.data.data.length) {
                    let data = [] as any;
                    for (const f of requestData.data.data) {
                        if (!(this.lastData.find((element: any) => element.id === f.id))) {
                            data.push(f);
                        }
                    }
                    for (const f of data) {
                        this.reaction.params.response = 'New follower on twitter: ' + f.username;
                        this.reaction.params.repoName = f.username;
                        this.reaction.trigger();
                    }
                    this.lastData = requestData.data.data;
                } else {
                    this.lastData = requestData.data.data;
                }

            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                return;
            }
        }, null, null, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Twitter follower action listening.`);
    }
}

export class TwitterFollowingAction extends IActions {
    public userId: number;

    async listen(params: any) {
        this.lastData = null as any;
        this.userId = null;
        let job = new CronJob('*/2 * * * *', async() => {
            if (this.state === false)
                return;
            try {
                const requestUser = await axios.get('https://api.twitter.com/2/users/me', {
                    headers: {
                        authorization: 'Bearer ' + this.client
                    }
                })
                this.userId = requestUser.data.data.id;
                if (!this.userId)
                    return;
                const requestData = await axios.get('https://api.twitter.com/2/users/' + this.userId + '/following?max_results=1000', {
                    headers: {
                        authorization: 'Bearer ' + this.client
                    }
                })
                
                if (this.lastData && this.lastData.length < requestData.data.data.length) {
                    let data = [] as any;
                    for (const f of requestData.data.data) {
                        if (!(this.lastData.find((element: any) => element.id === f.id))) {
                            data.push(f);
                        }
                    }
                    for (const f of data) {
                        this.reaction.params.response = 'You follow a new person on twitter: ' + f.username;
                        this.reaction.params.repoName = f.username;
                        this.reaction.trigger();
                    }
                    this.lastData = requestData.data.data;
                } else {
                    this.lastData = requestData.data.data;
                }
            } catch (error) {
                if (error.response && error.response.status && error.response.status === 403)
                    stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
                return;
            }
        }, null, null, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Twitter following action listening.`);
    }
}

const firstAction = new TwitterFollowerAction("newFollowerTw", "a new person follows you on twitter", "twitter");

const secondAction = new TwitterFollowingAction("newFollowingTw", "you follow a new person on twitter", "twitter");

export default [
    firstAction,
    secondAction
]