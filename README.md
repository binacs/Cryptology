# Cryptology

REBUILD in 2020:  **As an example of serverless**.

## Quick Start

```shell
$ git clone https://github.com/BinacsLee/Cryptology.git

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

### Env

For MacOS:

```shell
brew install grpcurl
```

In Go code:

```go
import "google.golang.org/grpc/reflection"

reflection.Register(grpcServer)
```

### grpcurl

Query service list:

```shell
$ grpcurl -plaintext  localhost:8888 list
binacs_api_cryptofunc.CryptoFunc
grpc.reflection.v1alpha.ServerReflection
```


Query service functions:

```shell
$ grpcurl -plaintext  localhost:8888 list binacs_api_cryptofunc.CryptoFunc
binacs_api_cryptofunc.CryptoFunc.Decrypt
binacs_api_cryptofunc.CryptoFunc.Encrypt
```


More information:

```shell
$ grpcurl -plaintext  localhost:8888 describe binacs_api_cryptofunc.CryptoFunc
binacs_api_cryptofunc.CryptoFunc is a service:
service CryptoFunc {
  rpc Decrypt ( .binacs_api_cryptofunc.DecryptReq ) returns ( .binacs_api_cryptofunc.DecryptResp );
  rpc Encrypt ( .binacs_api_cryptofunc.EncryptReq ) returns ( .binacs_api_cryptofunc.EncryptResp );
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
$ grpcurl -plaintext -d '{"src":"grpcurlTest"}' localhost:8888 binacs_api_cryptofunc.CryptoFunc/Encrypt
{
  "res": "Z3JwY3VybFRlc3Q="
}
```

```shell
$ grpcurl -plaintext -d '{"src":"Z3JwY3VybFRlc3Q="}' localhost:8888 binacs_api_cryptofunc.CryptoFunc/Decrypt
{
  "res": "grpcurlTest"
}
```

