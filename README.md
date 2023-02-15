# Cryptology

REBUILD in 2020:  **As an example of serverless**.

## Quick Start

```shell
$ git clone https://github.com/binacs/Cryptology.git

$ cd Cryptology

$ make
rm -rf bin
go build -o bin/fs .

$ ./start.sh
```



## Usage

### Make

See `Makefile` please.

### Command Line flags

```shell
--algo # "Crypto function name", `BASE64/AES/DES`, `BASE64` default
--port # "GRPC bind port", `:8888` default
```



## Test

### 1. grpcurl

#### Env

For MacOS:

```shell
brew install grpcurl
```

In Go code:

```go
import "google.golang.org/grpc/reflection"

reflection.Register(grpcServer)
```

#### example

Query service list:

```shell
$ grpcurl -plaintext  localhost:8888 list
binacs_api_cryptofunc.CryptoFunc
grpc.reflection.v1alpha.ServerReflection
```


Query service functions:

```shell
$ grpcurl -plaintext  localhost:8888 list binacs_api_cryptofunc.CryptoFunc
binacs_api_cryptofunc.CryptoFunc.CryptoDecrypt
binacs_api_cryptofunc.CryptoFunc.CryptoEncrypt
```


More information:

```shell
$ grpcurl -plaintext  localhost:8888 describe binacs_api_cryptofunc.CryptoFunc
binacs_api_cryptofunc.CryptoFunc is a service:
service CryptoFunc {
  rpc CryptoDecrypt ( .binacs_api_cryptofunc.DecryptReq ) returns ( .binacs_api_cryptofunc.DecryptResp );
  rpc CryptoEncrypt ( .binacs_api_cryptofunc.EncryptReq ) returns ( .binacs_api_cryptofunc.EncryptResp );
}
```


Query the type of 'EncryptReq' :

```shell
$ grpcurl -plaintext  localhost:8888 describe binacs_api_cryptofunc.EncryptReq
binacs_api_cryptofunc.EncryptReq is a message:
message EncryptReq {
  string src = 1;
}
```


Do service call:

```shell
$ grpcurl -plaintext -d '{"src":"grpcurlTest"}' localhost:8888 binacs_api_cryptofunc.CryptoFunc/CryptoEncrypt
{
  "res": "Z3JwY3VybFRlc3Q="
}
```

```shell
$ grpcurl -plaintext -d '{"src":"Z3JwY3VybFRlc3Q="}' localhost:8888 binacs_api_cryptofunc.CryptoFunc/CryptoDecrypt
{
  "res": "grpcurlTest"
}
```

### 2. grpc-client

A terminal:

```shell
$ ./bin/fs --algo=BASE64 --port=localhost:8888
```

Another terminal:

```shell
$ go run test/client.go --data=clientTest --host=localhost --port=:8888
2020/05/15 09:08:30 PlainText: clientTest
2020/05/15 09:08:30 Encrypted: Y2xpZW50VGVzdA==
2020/05/15 09:08:30 Decrypted: clientTest
```

