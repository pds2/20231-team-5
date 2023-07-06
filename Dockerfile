FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y curl && \
    apt-get install -y libcurl4-openssl-dev && \
    apt-get install -y make && \
    apt-get install -y g++

COPY . /app
WORKDIR /app

RUN chmod a+x compile_run.sh
RUN chmod a+x compile_test.sh