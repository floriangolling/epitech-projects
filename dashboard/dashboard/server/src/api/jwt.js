const jwt       = require("jsonwebtoken");
const secret    = require("../config")
const User      = require('../database/models/user');

module.exports = async (req, res, next) => {
    try {
        const token = req.headers.authorization.replace("Bearer ", "");
        const decoded = jwt.verify(token, secret.JWT_SECRET);
        const user = await User.findOne({where: {id: decoded.user_id }})
        if (!user)
            return res.status(404).send({error: "User not found"})
        if (user.confirmed === false)
            return res.status(403).send({error: "Email not confirmed"})
        req.userData = decoded;
        next();
    } catch (err) {
        return res.status(403).send({
            error: "Unauthorized"
        });
    }
};