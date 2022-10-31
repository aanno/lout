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
