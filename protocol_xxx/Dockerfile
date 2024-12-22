FROM debian:12
ARG FLAG="cyhub{f4k3_Fl4G}"
ENV FLAG=$FLAG

WORKDIR /challenge

RUN apt update -qq && apt install build-essential -y

COPY main.c Makefile /challenge

RUN make

EXPOSE 1337
CMD ["/challenge/chal"]
