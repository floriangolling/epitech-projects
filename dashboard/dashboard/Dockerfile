FROM node:10

WORKDIR /app

COPY ./server/package*.json ./server/

WORKDIR /app/server

RUN npm install

WORKDIR /app

COPY ./server /app/server/

COPY ./client/package*.json ./client/

WORKDIR /app/client

RUN npm install

WORKDIR /app

COPY ./client /app/client/

WORKDIR /app/client/

RUN npm run build

WORKDIR /app/server

EXPOSE 8080

CMD [ "npm", "run", "start"]