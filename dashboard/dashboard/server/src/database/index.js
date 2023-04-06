async function init(postgres) {
    try {
        await postgres.authenticate();
        await postgres.sync({force: false});
        console.log('Connection has been established succesfully.');
    } catch (error) {
        console.log('Unable to connect to the database: \n');
        console.log('\x1b[31m%s\x1b[0m', error);
        throw error;
    }
};

module.exports = {
    init
}