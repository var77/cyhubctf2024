FROM debian:12

WORKDIR /challenge

COPY main.c /challenge
COPY solution.c /challenge
COPY Makefile /challenge

RUN apt update -qq && apt install build-essential -y
RUN make
