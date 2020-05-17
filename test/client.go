package main

import (
	"flag"
	"fmt"
	"log"

	"golang.org/x/net/context"
	"google.golang.org/grpc"

	pb "github.com/BinacsLee/Cryptology/api/cryptofunc"
)

var data, host, port string
var client pb.CryptoFuncClient

func init() {
	//flag.StringVar(&algo, "algo", "BASE64", "Crypto function name")
	flag.StringVar(&data, "data", "clientTest", "Function input, plain-text")
	flag.StringVar(&host, "host", "localhost", "Host location")
	flag.StringVar(&port, "port", ":8888", "GRPC bind port")
}

func main() {
	flag.Parse()
	log.Println("GRPC client created, waiting for connection")
	conn, err := grpc.Dial(host+port, grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalln("Dial", err)
	}
	defer conn.Close()

	client = pb.NewCryptoFuncClient(conn)
	log.Println("Initial Test ...")
	doTest(data)
	log.Println("Initial Test Succeed.")
	for {
		fmt.Println("========> Please enter the data you want to test")
		fmt.Scanln(&data)
		doTest(data)
	}
}

func doTest(data string) {
	req1 := &pb.EncryptReq{
		Src: data,
	}
	resp := doEncrypt(req1)

	req2 := &pb.DecryptReq{
		Src: resp,
	}
	rstr := doDecrypt(req2)

	log.Println("PlainText:", data)
	log.Println("Encrypted:", resp)
	log.Println("Decrypted:", rstr)
}

func doEncrypt(req *pb.EncryptReq) string {
	resp, err := client.Encrypt(context.Background(), req)
	if err != nil {
		log.Fatalln("doEncrypt", err)
	}
	return resp.GetRes()
}

func doDecrypt(req *pb.DecryptReq) string {
	resp, err := client.Decrypt(context.Background(), req)
	if err != nil {
		log.Fatalln("doEncrypt", err)
	}
	return resp.GetRes()
}
