default: clean build

clean:
	rm -rf bin

build:
	go build -o bin/fs .