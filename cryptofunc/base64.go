package cryptofunc

import (
	"encoding/base64"
	"log"
)

type Base64 struct {
}

func (b *Base64) Encrypt(src string) string {
	dst := base64.StdEncoding.EncodeToString([]byte(src))
	return dst
}

func (b *Base64) Decrypt(src string) string {
	dst, err := base64.StdEncoding.DecodeString(src)
	if err != nil {
		log.Fatalln(err)
	}
	return string(dst)
}
