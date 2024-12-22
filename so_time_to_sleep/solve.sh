#!/bin/bash
set -e

docker build . -t time_to_sleep
docker run --rm time_to_sleep make solve
