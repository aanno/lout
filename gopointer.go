package main

import (
	"fmt"
)

type Ptr = uintptr

type gopointer[C any, G any] interface {
	generate() C
	assoc(goland G) C
	ptr(cland C) *G
	ref(cland C) G
	free(clands ...C)
}

type abstract_map_gopointer[C comparable, G any] struct {
	m map[C]*G
}

var ptr0 = uintptr(0)

func GeneratePointer() Ptr {
	ptr0++
	return Ptr(ptr0)
}

type map_gopointer[C Ptr, G any] struct {
	abstract_map_gopointer[C, G]
	generate func() C
}

type Gp[G any] map_gopointer[Ptr, G]

func (gp Gp[G]) assoc(goland *G) Ptr {
	c := gp.generate()
	// c := generatePointer()
	gp.abstract_map_gopointer.m[c] = goland
	// fmt.Println("assoc", gp.abstract_map_gopointer.m)
	return c
}

func (gp Gp[G]) ref(cland Ptr) G {
	// fmt.Println("ref", gp.abstract_map_gopointer.m)
	result, prs := gp.abstract_map_gopointer.m[cland]
	if !prs {
		fmt.Println("cland", cland, "not presend in", gp.abstract_map_gopointer.m)
		panic(cland)
	}
	return *result
}

func (gp Gp[G]) ptr(cland Ptr) *G {
	// fmt.Println("ptr", gp.abstract_map_gopointer.m)
	result, prs := gp.abstract_map_gopointer.m[cland]
	if !prs {
		return nil
	}
	return result
}

func (gp Gp[G]) free(clands ...Ptr) {
	for _, cland := range clands {
		delete(gp.abstract_map_gopointer.m, cland)
	}
}

func NewGp[G any]() *Gp[G] {
	amg := abstract_map_gopointer[Ptr, G]{
		m: make(map[Ptr]*G),
	}
	result := &Gp[G]{
		abstract_map_gopointer: amg,
		generate:               GeneratePointer,
	}
	return result
}
