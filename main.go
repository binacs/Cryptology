package main

import (
	"context"
	"flag"
	"log"
	"net"

	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"

	pb "github.com/BinacsLee/server/api/crypto"

	"github.com/BinacsLee/Cryptology/cryptofunc"
)

var fs *funcServer

var algo, port string

func init() {
	fs = &funcServer{}
	flag.StringVar(&algo, "algo", "BASE64", "Crypto function name")
	flag.StringVar(&port, "port", ":8888", "GRPC bind port")
}

type funcServer struct {
	f cryptofunc.Func
}

func (s *funcServer) CryptoEncrypt(ctx context.Context, req *pb.CryptoEncryptReq) (*pb.CryptoEncryptResp, error) {
	return &pb.CryptoEncryptResp{
		Data: &pb.CryptoEncryptResObj{
			EncryptText: s.f.CryptoEncrypt(req.GetPlainText()),
		},
	}, nil
}

func (s *funcServer) CryptoDecrypt(ctx context.Context, req *pb.CryptoDecryptReq) (*pb.CryptoDecryptResp, error) {
	return &pb.CryptoDecryptResp{
		Data: &pb.CryptoDecryptResObj{
			PlainText: s.f.CryptoDecrypt(req.GetEncryptText()),
		},
	}, nil
}

func main() {
	flag.Parse()
	switch algo {
	case "BASE64":
		fs.f = &cryptofunc.Base64{}
	case "AES":
		fs.f = &cryptofunc.Aes{}
	case "DES":
		fs.f = &cryptofunc.Des{}
	default:
		log.Fatalln("error algo type")
		return
	}

	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalln("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterCryptoServer(s, fs)

	reflection.Register(s)
	if err := s.Serve(lis); err != nil {
		log.Fatalln("failed to serve: %v", err)
	}
}
