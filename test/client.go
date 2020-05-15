package main

import (
	"flag"
	"log"

	"golang.org/x/net/context"
	"google.golang.org/grpc"

	pb "github.com/BinacsLee/Cryptology/api/cryptofunc"
)

var data, host, port string

func init() {
	//flag.StringVar(&algo, "algo", "BASE64", "Crypto function name")
	flag.StringVar(&data, "data", "clientTest", "Function input, plain-text")
	flag.StringVar(&host, "host", "localhost", "Host location")
	flag.StringVar(&port, "port", ":8888", "GRPC bind port")
}

func main() {
	flag.Parse()
	conn, err := grpc.Dial(host+port, grpc.WithInsecure())
	if err != nil {
		log.Fatalln("Dial", err)
	}
	defer conn.Close()

	client := pb.NewCryptoFuncClient(conn)

	req1 := &pb.EncryptReq{
		Src: data,
	}
	resp := doEncrypt(client, req1)

	req2 := &pb.DecryptReq{
		Src: resp,
	}
	rstr := doDecrypt(client, req2)

	log.Println("PlainText:", data)
	log.Println("Encrypted:", resp)
	log.Println("Decrypted:", rstr)
}

func doEncrypt(client pb.CryptoFuncClient, req *pb.EncryptReq) string {
	resp, err := client.Encrypt(context.Background(), req)
	if err != nil {
		log.Fatalln("doEncrypt", err)
	}
	return resp.GetRes()
}

func doDecrypt(client pb.CryptoFuncClient, req *pb.DecryptReq) string {
	resp, err := client.Decrypt(context.Background(), req)
	if err != nil {
		log.Fatalln("doEncrypt", err)
	}
	return resp.GetRes()
}
