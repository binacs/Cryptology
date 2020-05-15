FROM golang:1.14-alpine AS binacsGoBuild

# ENV GO111MODULE=on

COPY . /src

RUN apk add --no-cache make && go env -w GOPROXY=https://goproxy.cn \
    && cd /src \
    && make

FROM alpine

COPY --from=binacsGoBuild /src/bin/fs /usr/sbin/fs

EXPOSE 8888
