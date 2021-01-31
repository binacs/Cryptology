package cryptofunc

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"encoding/base64"
	"log"
)

type Aes struct{}

var aesKey []byte

func init() {
	aesKey = []byte("BINACSwithKIKIfo")
}

func aesPadding(src []byte, blockSize int) []byte {
	padNum := blockSize - len(src)%blockSize
	pad := bytes.Repeat([]byte{byte(padNum)}, padNum)
	return append(src, pad...)
}

func aesUnpadding(src []byte) []byte {
	n := len(src)
	unPadNum := int(src[n-1])
	return src[:n-unPadNum]
}

func (a *Aes) CryptoEncrypt(src string) string {
	srcb := []byte(src)
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		log.Fatalln(err)
		return src
	}
	srcb = aesPadding(srcb, block.BlockSize())
	blockMode := cipher.NewCBCEncrypter(block, aesKey)
	blockMode.CryptBlocks(srcb, srcb)
	return base64.StdEncoding.EncodeToString(srcb)
}

func (a *Aes) CryptoDecrypt(src string) string {
	crypted, _ := base64.StdEncoding.DecodeString(src)
	srcb := crypted
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		log.Fatalln(err)
	}
	blockMode := cipher.NewCBCDecrypter(block, aesKey)
	blockMode.CryptBlocks(srcb, srcb)
	srcb = aesUnpadding(srcb)
	return string(srcb)
}
