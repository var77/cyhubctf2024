#!/bin/bash
set -e

docker build . --build-arg FLAG='cyhub{fake_flag}' -t fdftw
docker run --restart on-failure --name fdftw -d -p1337:1337 fdftw
