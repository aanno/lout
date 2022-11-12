
EXE_TARGETS := \
	example

all: $(EXE_TARGETS) clout
.PHONY: all

%.h: %.go
	go tool cgo -exportheader $*.h $*.go

clout:
	$(MAKE) -C clout

main: *.go
	go build .

clean:
	rm -f a.out *.o *.a lout main

example: *.go
	go build

run:
	go run .

test:
	go test

clean:
	rm -rf a.out *.o *.a *.so example _obj $(EXE_TARGETS)

format:
	clang-format -style=file -i *.c

.PHONY: clean format
