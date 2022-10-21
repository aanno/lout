package main


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
import "unsafe"

func main() {
	cs := C.CString("Hello from stdio")
	C.myprint(cs)
	C.free(unsafe.Pointer(cs))
}

