package main

import (
	"testing"
)

func TestGapT(t *testing.T) {
	var mapGp = NewGp[Gap_t]()
	// var mapGp *Gp[testStruct] = &Gp[testStruct]{}
	// mapGp.m = make(map[Ptr]testStruct)
	// mapGp.generate = GeneratePointer

	ts1 := Gap_t{}
	ts1.ojoin = true
	ts1.omark = true
	ts1.onobreak = true
	ts1.ounits = 5
	ts1.omode = 7
	ts1.owidth = 101202

	ts2 := Gap_t{}
	// end struct setup

	var c1 GAP = mapGp.assoc(ts1)
	var c2 GAP = mapGp.assoc(ts2)
	
	defer mapGp.free(c1, c2)

	GapCopy(c2, c1);

	t1 := mapGp.ref(c1)
	t.Log(t1)
	t2 := mapGp.ref(c2)
	t.Log(t2)
}
