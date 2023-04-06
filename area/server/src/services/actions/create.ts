import { TwitterFollowerAction, TwitterFollowingAction } from './twitter';
import { BestActionReaction, HotActionReddit} from './reddit';
import { IssueAction, FollowAction } from './github';
import { FirstAction, SecondAction } from './trello';
import { chatAction, subAction } from "./twitch";

async function createAction(params: any) {
    return new Promise((resolve: any, reject: any) => {
        switch (params.actionName) {
            case 'SubAction':
                let action1 = new subAction("SubAction", "you subscribe on a channel", "twitch");
                action1.state = true;
                resolve (action1);
                break;
            case 'ChatReaction':
                let action2 = new chatAction("ChatReaction", "someone post a message on your channel"," twitch");
                action2.state = true;
                resolve (action2);
                break;
            case 'IssueAction':
                let action3 = new IssueAction("IssueAction", "a new issue is detected on your account", "github");
                action3.state = true;
                resolve (action3);
                break;
            case 'FollowAction':
                let action4 = new FollowAction("FollowAction", "your number of follower changes", "github");
                action4.state = true;
                resolve (action4);
                break;
            case 'newFollowerTw':
                let action5 = new TwitterFollowerAction("newFollowerTw", "a new person follows you on twitter", "twitter");
                action5.state = true;
                resolve (action5);
                break;
            case 'newFollowingTw':
                let action6 = new TwitterFollowingAction("newFollowingTw", "a new person on twitter", "twitter");
                action6.state = true;
                resolve (action6);
                break;
            case 'HotBest':
                let action7 = new HotActionReddit("HotBest", "there is a new hot post", "reddit");
                action7.state = true;
                resolve (action7);
                break;
            case 'BestList':
                let action8 = new BestActionReaction("BestList", "there is a new best post", "reddit");
                action8.state = true;
                resolve (action8);
                break;
            case 'BoardChanges':
                let action9 = new FirstAction("BoardChanges", "there is an update on your boards", "trello");
                action9.state = true;
                resolve (action9);
                break;
            case 'CustomBackground':
                let action10 = new SecondAction("CustomBackground", "one of your background is updated", "trello");
                action10.state = true;
                resolve (action10);
                break;
            default:
                resolve (null);
                break;
        }
    })
}

export default createAction;