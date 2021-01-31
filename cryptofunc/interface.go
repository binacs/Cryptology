package cryptofunc

type Func interface {
	CryptoEncrypt(src string) string
	CryptoDecrypt(src string) string
}
