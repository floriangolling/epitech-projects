FROM node:14

WORKDIR /app

COPY package.json ./

COPY package-lock.json ./

COPY tsconfig.json ./

COPY . ./

RUN npm install

EXPOSE 8080

CMD ["npm", "run", "start"]