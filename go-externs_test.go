package main

import (
	"testing"
)

func TestGapT(t *testing.T) {
	// We MUST use the global MapGap
	// var mapGp = NewGp[Gap_t]()

	ts1 := Gap_t{}
	ts1.ojoin = true
	ts1.omark = true
	ts1.onobreak = true
	ts1.ounits = 5
	ts1.omode = 7
	ts1.owidth = 101202

	ts2 := Gap_t{}
	// end struct setup

	var c1 GAP = MapGap.assoc(&ts1)
	var c2 GAP = MapGap.assoc(&ts2)

	GapCopy(c2, c1)

	t1 := MapGap.ptr(c1)
	t.Log(*t1)
	t2 := MapGap.ptr(c2)
	t.Log(*t2)

	if !GapEqual(c1, c2) {
		t.Errorf("1 expected %v == %v", *t1, *t2)
	}

	t3 := MapGap.ref(c2)
	c3 := MapGap.assoc(&t3)
	(*t2).ounits = 3
	if GapEqual(c2, c3) {
		t.Errorf("2 expected %v != %v", *t2, t3)
	}
	t3.ounits = 3
	if !GapEqual(c2, c3) {
		t.Errorf("3 expected %v == %v", *t2, t3)
	}

	defer MapGap.free(c1, c2, c3)
}
