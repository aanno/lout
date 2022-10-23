package main

// #cgo LDFLAGS: -lz -lm -L. -llout
//
// #include <stdio.h>
// #include <stdlib.h>
//
// #include "go_linux_64.h"
// #include "externs.h"
//
// static void myprint(char* s) {
//   printf("%s\n", s);
// }
//
import "C"
import (
	"bytes"
	"fmt"
	"os"
	"unsafe"
)

func main() {
	total_len := 0
	// argc := len(os.Args)
	for _, v := range os.Args {
		// add 1 for space
		total_len += len(v) + 1
	}
	var all_in_one bytes.Buffer
	for _, v := range os.Args {
		all_in_one.WriteString(v)
		all_in_one.WriteString(" ")
	}
	args := all_in_one.String()
	fmt.Println("args in go: " + args)
	cs := C.CString(args)
	C.main1(cs)
	C.free(unsafe.Pointer(cs))
}

func main2() {
	cs := C.CString("Hello from stdio")
	C.myprint(cs)
	C.free(unsafe.Pointer(cs))

	C.PrintUsage(C.stdout)
}
