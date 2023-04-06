class IActions {
    constructor(name: string, description: string, serviceName: string) {
        this.name = name;
        this.description = description;
        this.serviceName = serviceName;
    };
    id: number;
    name: string;
    serviceName: string;
    description: string;
    reaction: IReactions;
    client: any;
    state: boolean;
    lastData: any;
    _userId: number;
    listen(params: any) { return };
}

class IReactions {
    constructor(name: string, description: string, serviceName: string) {
        this.name = name;
        this.description = description;
        this.serviceName = serviceName;
    };
    state: boolean;
    id: number;
    _userId: number;
    name: string;
    description: string;
    action: IActions;
    client: any;
    params: any = {};
    serviceName: string;
    trigger() { return };
}

class IService {
    constructor(name: string) { this.name = name };
    name: string;
    client: any;
    actions = [] as Array<IActions>;
    state: boolean;
    reactions = [] as Array<IReactions>;
    user_id: number;
    addAction(action: IActions) { this.actions.push(action) };
    addReactions(reaction: IReactions) { this.reactions.push(reaction) };
    setup(params: any) { return };
};

type RunningSer = {
    id: number;
    service: IService;
}

export {
    IActions,
    IReactions,
    IService,
    RunningSer
}