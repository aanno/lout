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
	abstract_map_gopointer
	generate func()unsafe.Pointer
}

func (gp map_gopointer[C,G]) assoc(goland G)C {
	c := gp.generate()
	gp.m[c] = goland
	return c
}

func (gp abstract_map_gopointer[C,G]) ref(cland C)G {
	return gp.m[cland]
}

func (gp abstract_map_gopointer[C,G]) free(cland C) {
	delete(gp.m, cland)
}


