FROM node:14

WORKDIR /app

COPY package.json ./

COPY package-lock.json ./

COPY . ./

RUN npm install

EXPOSE 8081

RUN npm run build

CMD ["node", "server.js"]