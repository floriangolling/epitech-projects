class Widget {
    constructor(name, description, paramName, paramType) {
        this.properties = {
            name: "",
            description: "",
            params: {
                name: "",
                type: "",
            }
        };
        this.properties.name = name;
        this.properties.description = description;
        this.properties.params.name = paramName;
        this.properties.params.type = paramType;
    }
    callThisWidget() {
        return {}
    }
}

class Service {
    constructor(ServiceName, logoRoute) {
        this.properties = {
            name: "",
            logoRoute: "",
        };
        this.properties.name = ServiceName;
        this.properties.logoRoute = logoRoute;
        this.widgets = []
        this.client = null;
    }

    addWidget(widget) {
        this.widgets.push(widget);
    }

    setClient(client) {
        this.client = client
    }

    getClient() {
        return (this.client)
    }
}

module.exports = {
    Service,
    Widget
}