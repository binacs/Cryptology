package cryptofunc

type Func interface {
	Encrypt(src string) string
	Decrypt(src string) string
}
