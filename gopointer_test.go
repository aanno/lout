package main

import (
	"testing"
)

type testStruct struct {
	a int
	b string
}

type testStructCptr = *Gp[testStruct]

func TestSimple(t *testing.T) {
	var mapGp testStructCptr = NewGp[testStruct]()
	// var mapGp *Gp[testStruct] = &Gp[testStruct]{}
	// mapGp.m = make(map[Ptr]testStruct)
	// mapGp.generate = GeneratePointer

	ts1 := testStruct{1, "test"}
	ts2 := testStruct{2, "test2"}
	c1 := mapGp.assoc(&ts1)
	c2 := mapGp.assoc(&ts2)

	defer mapGp.free(c1, c2)

	t1 := mapGp.ref(c1)
	t.Log(t1)
	t2 := mapGp.ref(c2)
	t.Log(t2)
}
