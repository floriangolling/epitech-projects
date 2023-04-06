FROM cirrusci/flutter
   
WORKDIR /app

COPY . ./

RUN flutter doctor -v

CMD ["./build.sh"]