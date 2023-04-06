import {stopService} from '../../controllers/service';
const { request } = require("@octokit/request");
import { IActions } from "../interfaces";
import { CronJob } from 'cron';

export class IssueAction extends IActions {
    async listen(params: any) { 
        this.lastData = null as any;
        let job = new CronJob('*/10 * * * * *', async () => {
            try {
                if (this.state === false)
                    return;
                const requestWithAuth = request.defaults({
                    headers: {
                        authorization: 'token ' + this.client
                    }
                })
                let newData = await requestWithAuth('GET /issues');
                if (this.lastData && this.lastData.length != newData.data.length) {
                    let data = [] as any;
                    for (const f of newData.data) {
                        if (!(this.lastData.find((element: any) => element.id === f.id))) {
                            data.push(f)
                        }
                    }
                    for (const f of data) {
                        this.reaction.params.response = 'Your issues has changed, have a check ! title: ' + f.title;
                        this.reaction.params.repoName = f.title;
                        this.reaction.trigger();
                    }
                    this.lastData = newData.data;
                } else {
                    this.lastData = newData.data;
                }
            } catch (error) {
                stopService(this.serviceName, this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            }
        }, null, true, '')
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Github Issue action listening.`);
    }
}

export class FollowAction extends IActions {
    private _followers: any;
    async listen(params: any) { 
        this.lastData = null;
        this._followers = null as Array<any>;
        let job = new CronJob('*/10 * * * * *', async () => {
            try {
                if (this.state === false)
                    return;
                const requestWithAuth = request.defaults({
                    headers: {
                        authorization: "token " + this.client,
                    },
                });
                const follower = await requestWithAuth('GET /user/followers')
                const newData = await requestWithAuth('GET /user')
                if (this.lastData && this._followers) {
                    if (this.lastData.followers < newData.data.followers) {
                        let data = [] as any;
                        for (const f of follower.data) {
                            if (!(this._followers.find((elem: any) => elem.login == f.login))) {
                                data.push(f);
                            }
                        }
                        for (const f of data) {
                            this.reaction.params.response = 'New follower numbers: ' + newData.data.followers + ' followers name: ' + f.login;
                            this.reaction.params.repoName = f.login;
                            this.lastData = newData.data;
                            this._followers = follower.data;
                            this.reaction.trigger();
                        }
                    }
                } else if (!this.lastData || !this._followers) {
                    this._followers = follower.data;
                    this.lastData = newData.data;
                }
            } catch (error) {
                stopService('github', this._userId);
                console.log('\x1b[31m%s %s\x1b[0m', '[ERROR]', error);
            }
        }, null, true, '');
        job.start();
        console.log('\x1b[32m%s\x1b[0m', `[OK] Github Follow action listening.`);
    }
}


const issue = new IssueAction("IssueAction", "a new issue is detected on your account", "github");
const follow = new FollowAction("FollowAction", "your number of follower changes", "github");

export default [
    issue,
    follow
]