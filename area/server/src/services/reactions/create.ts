import { TwitterReaction } from './twitter'
import { RedditReaction } from './reddit';
import { TrelloReaction } from './trello';
import { chatReaction } from "./twitch";
import { RepoReaction } from './github';

async function createReaction(params: any) {
    return new Promise((resolve: any, reject: any) => {
        switch (params.reactionName) {
            case 'Chat':
                let reaction1 = new chatReaction("Chat", "says a message according the action on your channel", "twitch");
                reaction1.state = true;
                resolve (reaction1);
                break;
            case 'RepoReaction':
                let reaction2 = new RepoReaction("RepoReaction", "create a repository according to the action (!github nameOfRepo for chatReaction)", "github");
                reaction2.state = true;
                resolve (reaction2);
                break;
            case 'postTweet':
                let reaction3 = new TwitterReaction("postTweet", "post a tweet according to the action", "twitter")
                reaction3.state = true;
                resolve (reaction3);
                break;
            case 'RedditPost':
                let reaction4 = new RedditReaction("RedditPost", "post a reddit on the Area subreddit according to the action (!reddit nameOfReddit for chatReaction)", "reddit");
                reaction4.state = true;
                resolve (reaction4);
                break;
            case 'BoardCreation':
                let reaction5 = new TrelloReaction("BoardCreation", "create a board according the action (!trello nameOfBoard for chatReaction)", "trello");
                reaction5.state = true;
                resolve (reaction5);
            default:
                resolve (null)
                break;
        }
    })
}

export default createReaction;
