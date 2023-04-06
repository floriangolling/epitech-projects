module.exports = {
    devServer: {
      open: process.platform === 'darwin',
      host: 'localhost',
      port: 8081,
      https: false,
      hotOnly: false,
    },
  }