const Sequelize = require('sequelize');

class Widget extends Sequelize.Model {
    static definition(sequelize) {
        Widget.init({
            serviceName: {
                type: Sequelize.DataTypes.STRING,
                allowNull: false
            },
            widgetName: {
                type: Sequelize.DataTypes.STRING,
                allowNull: false
            },
            param: {
                type: Sequelize.DataTypes.STRING,
                allowNull: false
            },
            x: {
                type: Sequelize.DataTypes.INTEGER,
                allowNull: false,
            },
            y: {
                type: Sequelize.DataTypes.INTEGER,
                allowNull: false,
            },
            refreshTime: {
                type: Sequelize.INTEGER,
                allowNull: false
            }
        }, {
            sequelize,
            tableName: "widget"
        });
    }

    static associate() {

    }
}

module.exports = Widget;