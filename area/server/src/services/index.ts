import { IService } from "./interfaces";
import twitchService from './twitch';
import githubService from "./github";
import trelloService from "./trello";
import redditService from "./reddit";
import twitterService from "./twitter";

export default [
    twitterService,
    redditService,
    trelloService,
    twitchService,
    githubService
] as Array<IService>