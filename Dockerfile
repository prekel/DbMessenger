FROM ubuntu:20.04 as build
RUN apt-get update -y
RUN apt-get install -y build-essential libecpg-dev
COPY "*.c" ./
COPY "*.h" ./
COPY "Makefile" ./
RUN make

FROM ubuntu:20.04
RUN apt-get update -y
RUN apt-get install -y libecpg6
COPY --from=build DbMessenger .
