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
	"os"
	"unsafe"
)



func main3() {
	// TODO:
	// adhere to LOCALE, run_num, runs_to_do, LIB_DIR

	argc := len(os.Args)
	cargs := make([]C.char, argc, argc)
	for i, v := range os.Args {
		cargs[i] = C.CString(v)
	}

	lib_dir := "/usr/local/share/lout-3.42/lib"
	runs_to_do := -1
	run_num := 1

	// C.run(C.Arargc, argv, run_num, &runs_to_do, C.CString(lib_dir))
}

func main2() {
	cs := C.CString("Hello from stdio")
	C.myprint(cs)
	C.free(unsafe.Pointer(cs))

	C.PrintUsage(C.stdout)
}
