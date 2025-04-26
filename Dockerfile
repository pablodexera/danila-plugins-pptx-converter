FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    cmake make g++ curl wget unzip git libboost-all-dev libmicrohttpd-dev libssl-dev fontconfig libjsoncpp-dev && \
    apt-get clean

WORKDIR /app

COPY . .

RUN cmake . && make

EXPOSE 8080

CMD ["./convert-pptx-api"]