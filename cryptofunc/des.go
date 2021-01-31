package cryptofunc

import (
	"bytes"
	"crypto/cipher"
	"crypto/des"
	"encoding/base64"
)

type Des struct{}

var desKey []byte

func init() {
	desKey = []byte("BinacsKI")
}

func (d *Des) CryptoEncrypt(src string) string {
	block, _ := des.NewCipher(desKey)
	srcd := PKCS5Padding([]byte(src), block.BlockSize())
	blockMode := cipher.NewCBCEncrypter(block, desKey)
	crypted := make([]byte, len(srcd))
	blockMode.CryptBlocks(crypted, srcd)
	return base64.StdEncoding.EncodeToString(crypted)
}

func (d *Des) CryptoDecrypt(src string) string {
	crypted, _ := base64.StdEncoding.DecodeString(src)
	block, _ := des.NewCipher(desKey)
	blockMode := cipher.NewCBCDecrypter(block, desKey)
	origData := make([]byte, len(crypted))
	blockMode.CryptBlocks(origData, crypted)
	origData = PKCS5UnPadding(origData)
	return string(origData)
}

func PKCS5Padding(src []byte, blockSize int) []byte {
	padding := blockSize - len(src)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(src, padtext...)
}

func PKCS5UnPadding(src []byte) []byte {
	length := len(src)
	unpadding := int(src[length-1])
	return src[:(length - unpadding)]
}
