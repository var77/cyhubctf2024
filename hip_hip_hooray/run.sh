#!/bin/bash
set -e

docker build . --build-arg FLAG='cyhub{fake_flag}' -t hip_hip_hooray
docker run -p1337:1337 --restart on-failure -d hip_hip_hooray
