package main

import (
)

type Ptr uintptr

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

func GeneratePointer()Ptr {
	ptr0++
	return Ptr(ptr0)
}

type map_gopointer[C Ptr, G any] struct {
	abstract_map_gopointer[C, G]
	generate func()C
}

type Gp[G any] map_gopointer[Ptr, G]

func (gp Gp[G]) assoc(goland G)Ptr {
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

func NewGp[G any]()*Gp[G] {
	result := &Gp[G]{}
	result.m = make(map[Ptr]G)
	result.generate = GeneratePointer
	return result
} 


// testing

/*
type testStruct struct {
	a int
	b string
}

type testStructCtr gp[testStruct]

func main() {
	var mapGp *gp[testStruct] = NewGp[testStruct]()
	// var mapGp *gp[testStruct] = &gp[testStruct]{}
	mapGp.m = make(map[Ptr]testStruct)
	mapGp.generate = GeneratePointer

	var ts1 = testStruct{1, "test"}
	var ts2 = testStruct{2, "test2"}
	var c1 = mapGp.assoc(ts1)
	var c2 =  mapGp.assoc(ts2)
	fmt.Println(mapGp.ref(c1))
	fmt.Println(mapGp.ref(c2))
}
*/
