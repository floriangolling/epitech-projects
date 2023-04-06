import { DataTypes, Model, Sequelize } from 'sequelize';
import Component from './component';

export default class User extends Model {
    public static definition(sequelize: Sequelize) {
        User.init({
            username: {
                type: DataTypes.STRING,
                allowNull: false,
                unique: true
            },
            password: {
                type: DataTypes.STRING,
                allowNull: true
            },
            email: {
                type: DataTypes.STRING,
                allowNull: false
            },
            oauths: {
                type: DataTypes.JSON,
                defaultValue: {}
            }

        }, {
            tableName: 'user',
            sequelize,
        });
    }

    public static associate() {
        User.hasMany(Component, { onDelete: 'cascade'} );
    }

    public email!: string;
    public oauths!: any;
    public password!: string;
    public username!: string;
    public id!: number;
    public createdAt!: Date;
    public updatedAt!: Date;
};