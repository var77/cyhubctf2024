FROM debian:12

ARG FLAG="cyhub{f4k3_Fl4G}"

WORKDIR /challenge

RUN apt update -qq && apt install build-essential socat -y

RUN echo "do you know basic math?" > "note.txt"
RUN echo $FLAG > "flag.txt"

COPY main.c Makefile /challenge

RUN make

EXPOSE 1337
CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/challenge/chal"]
