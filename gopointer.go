package main

import ( 
	"fmt"
)

type ptr uintptr

type gopointer[C any,G any] interface {
	generate()C
	assoc(goland G)C
	ref(cland C)G
	free(cland C)
}

type abstract_map_gopointer[C comparable, G any] struct {
	m map[C]G
}

var ptr0 = uintptr(0)

func generatePointer()ptr {
	ptr0++
	return ptr(ptr0)
}

type map_gopointer[C ptr, G any] struct {
	abstract_map_gopointer[C, G]
	generate func()C
}

type gp[G any] map_gopointer[ptr, G]

func (gp gp[G]) assoc(goland G)ptr {
	c := gp.generate()
	// c := generatePointer()
	gp.m[c] = goland
	return c
}

func (gp abstract_map_gopointer[C,G]) ref(cland C)G {
	return gp.m[cland]
}

func (gp abstract_map_gopointer[C,G]) free(cland C) {
	delete(gp.m, cland)
}


// testing

type testStruct struct {
	a int
	b string
}

type testStructCtr gp[testStruct]


func main() {
	mapGp := gp[testStruct]{}
	mapGp.m = make(map[ptr]testStruct)
	mapGp.generate = generatePointer

	var ts1 = testStruct{1, "test"}
	var ts2 = testStruct{2, "test2"}
	var c1 = mapGp.assoc(ts1)
	var c2 =  mapGp.assoc(ts2)
	fmt.Println(mapGp.ref(c1))
	fmt.Println(mapGp.ref(c2))
}
