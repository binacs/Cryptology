FROM golang:1.15-alpine AS binacsGoBuild

COPY . /src

RUN apk add --no-cache make && \
    \
    cd /src && \
    \
    make

FROM alpine

COPY --from=binacsGoBuild /src/bin/fs /usr/sbin/fs