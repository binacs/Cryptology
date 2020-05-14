package main

import (
	"flag"
	"net"
	"context"
	"log"

	"google.golang.org/grpc"
	"github.com/BinacsLee/Cryptology/cryptofunc"
	pb "github.com/BinacsLee/Cryptology/api/cryptofunc"
)

type funcServer struct {
	f cryptofunc.Func
}

func (s *funcServer) Encrypt(ctx context.Context, req *pb.EncryptReq) (*pb.EncryptResp, error) {
	return &pb.EncryptResp{
		Res: s.f.Encrypt(req.GetSrc()),
	}, nil
}

func (s *funcServer) Decrypt(ctx context.Context, req *pb.DecryptReq) (*pb.DecryptResp, error) {
	return &pb.DecryptResp{
		Res: s.f.Decrypt(req.GetSrc()),
	}, nil
}

var fs *funcServer

var algo, port string

func init() {
	fs = &funcServer{}
	flag.StringVar(&algo, "algo", "BASE64", "Crypto function name")
	flag.StringVar(&port, "port", ":8888", "GRPC bind port")
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
	pb.RegisterCryptoFuncServer(s, fs)
	if err := s.Serve(lis); err != nil {
		log.Fatalln("failed to serve: %v", err)
	}
}
