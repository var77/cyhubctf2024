#!/bin/bash
set -e

docker build . --build-arg FLAG='cyhub{fake_flag}' -t pg_lo
docker run -p 8080:8080 -p 2222:22 --restart on-failure --name pg_lo -d -e POSTGRES_PASSWORD='g3DTa4Dhfjth22aJ4u' -e APP_USER_PASSWORD='4KxNjFcVAU_cXv_Wy2X8' pg_lo
