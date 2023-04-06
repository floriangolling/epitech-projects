import { DataTypes, Model, Sequelize } from 'sequelize';

export default class Component extends Model {
    public static definition(sequelize: Sequelize) {
        Component.init({
            serviceReactionName: {
                type: DataTypes.STRING,
                allowNull: false
            },
            serviceActionName: {
                type: DataTypes.STRING,
                allowNull: false
            },
            actionName: {
                type: DataTypes.STRING,
                allowNull: false
            },
            reactionName: {
                allowNull: false,
                type: DataTypes.STRING,
            }
        }, {
            tableName: 'component',
            sequelize,
        });
    }

    public static associate() {
        return;
    }

    public state?: boolean;
    public actionName!: string;
    public reactionName!: string;
    public serviceReactionName!: string;
    public serviceActionName!: string;
    public UserId!: number;
    public id!: number;
    public createdAt!: Date;
    public updatedAt!: Date;
};