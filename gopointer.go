package main

import ( 
	"fmt"
	"unsafe"
)

type gopointer[C any,G any] interface {
	generate()C
	assoc(goland G)C
	ref(cland C)G
	free(cland C)
}

type abstract_map_gopointer[C comparable, G any] struct {
	m map[C]G
}

func generatePointer()unsafe.Pointer {
	return nil
}

type map_gopointer[C unsafe.Pointer, G any] struct {
	abstract_map_gopointer[C, G]
	generate func()C
}

type gp[G any] map_gopointer[unsafe.Pointer, G]

func (gp gp[G]) assoc(goland G)unsafe.Pointer {
	c := gp.generate()
	// c := generatePointer()
	gp.m[c] = goland
	return c
}

/*
func assoc[G any](gp gp[G], goland G)unsafe.Pointer {
	c := gp.generate()
	// c := generatePointer()
	gp.m[c] = goland
	return c
}
*/

func (gp abstract_map_gopointer[C,G]) ref(cland C)G {
	return gp.m[cland]
}

func (gp abstract_map_gopointer[C,G]) free(cland C) {
	delete(gp.m, cland)
}


