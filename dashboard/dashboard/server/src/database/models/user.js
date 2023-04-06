const Sequelize = require('sequelize');
const Widget    = require('./widget');

class User extends Sequelize.Model {
    static definition(sequelize) {
        User.init({
            username: {
                type: Sequelize.DataTypes.STRING,
                allowNull: false
            },
            email: {
                type: Sequelize.DataTypes.STRING,
                allowNull: false
            },
            password: {
                type: Sequelize.DataTypes.STRING,
                allowNull: true,
                defaultValue: null
            },
            admin: {
                type: Sequelize.BOOLEAN,
                allowNull: false,
                defaultValue: false
            },
            confirmed: {
                defaultValue: false,
                type: Sequelize.BOOLEAN
            },
            oauths: {
                type: Sequelize.DataTypes.JSON,
                defaultValue: {}

            }
        }, {
            sequelize,
            tableName: "user"
        });
    }

    static associate() {
        User.hasMany(Widget, { onDelete: 'cascade', hooks: true});
    }
}

module.exports = User;