#!/bin/bash
set -e

docker build . --build-arg FLAG='cyhub{fake_flag}' -t protocol_xxx
docker run -p1337:1337 --restart on-failure -d protocol_xxx
