FROM postgres:17

ARG FLAG="cyhub{f4k3_Fl4G}"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y openssh-server supervisor nodejs npm

RUN mkdir /web && cd /web && \
    npm init -y && \
    npm install express pg


RUN mkdir -p /var/run/sshd
    
RUN sed -i '/^#PubkeyAuthentication yes/c\PubkeyAuthentication yes' /etc/ssh/sshd_config && \
    sed -i '/^#AuthorizedKeysFile/c\AuthorizedKeysFile /var/lib/postgresql/.ssh/authorized_keys' /etc/ssh/sshd_config && \
    sed -i '/^#PasswordAuthentication yes/c\PasswordAuthentication no' /etc/ssh/sshd_config && \
    mkdir -p /var/lib/postgresql/.ssh && \
    chown postgres:postgres -R /var/lib/postgresql/.ssh && \
    chmod 700 /var/lib/postgresql && \
    chmod 700 /var/lib/postgresql/.ssh


COPY /init/init.sh /docker-entrypoint-initdb.d/init.sh
COPY init/init.sql /

COPY images /images

RUN echo $FLAG > /flag.txt

COPY web /web

COPY supervisord.conf /etc/supervisor/supervisord.conf

RUN chown postgres:postgres /flag.txt /init.sql
RUN chown -R postgres:postgres /images

EXPOSE 8080 22

CMD ["/usr/bin/supervisord"]
