/**
 * @swagger
 * securityDefinitions:
 *  JWT:
 *      type: apiKey
 *      name: authorization
 *      in: header
 * definitions:
 *  User:
 *    properties:
 *      id:
 *        type: integer
 *        description: the auto generated ID
 *      username:
 *        type: string
 *        description: the user's username
 *      email:
 *        type: string
 *        description: the user's email.
 *      password:
 *        type: string
 *        description: the user's password
 *      admin:
 *        type: boolean
 *        description: is the user admin
 *      createdAt:
 *        type: string
 *        description: This ticket's creation time
 *      updatedAt:
 *        type: string
 *        description: This ticket's creation time
 *    required:
 *      - email
 *      - username
 *      - password
 *
 */

/**
 * @swagger
 * definitions:
 *  Widget:
 *    properties:
 *      id:
 *        type: integer
 *        description: the auto generated ID
 *      serviceName:
 *        type: string
 *        description: the widget's service name
 *      WidgetName:
 *        type: string
 *        description: the widget's name
 *      x:
 *        type: integer
 *        description: the widget's x position
 *      y:
 *        type: integer
 *        description: the widget's y position
 *      param:
 *        type: string
 *        description: the widget's parameter
 *      createdAt:
 *        type: string
 *        description: This widget's creation time
 *      updatedAt:
 *        type: string
 *        description: This widget's update time
 *    required:
 *      - serviceName
 *      - widgetName
 *      - x
 *      - y
 *      - param
 *
 */