package main

// #include "go_linux_64.h"
// #include "./externs.h"
//
import "C"
import (
	"unsafe"
)

type OBJECT = unsafe.Pointer
type FULL_LENGTH = int32
type FONT_NUM = uint16
type COLOUR_NUM = uint16
type TEXTURE_NUM = uint16
type LANGUAGE_NUM = uint32

/*@::GAP, STYLE@**************************************************************/
/*                                                                           */
/*  typedef GAP - what separates one object from another.                    */
/*                                                                           */
/*****************************************************************************/

type Gap_t struct {
	owidth   FULL_LENGTH /* width of the gap                  */
	onobreak bool        /* TRUE if this gap is unbreakable   */
	omark    bool        /* TRUE if this gap is marked        */
	ojoin    bool        /* TRUE if joins exist across gap    */
	ounits   uint8       /* :3 units of measurement: fixed, etc  */
	omode    uint8       /* :3 spacing mode: edge-to-edge, etc   */
}

// type GAP = gap_t
type GAP = uintptr

/* A key-value pair.  */
type Context_t struct {
	okey   *OBJECT  /* name of a context variable        */
	ovalue *OBJECT  /* associated value		     */
	oenv   *OBJECT  /* environment for this value        */
	ostyle *Style_t /* style for this value              */
}

type Style_t struct {
	oline_gap         Gap_t        /* separation between lines          */
	ospace_gap        Gap_t        /* separation induced by white space */
	oyunit            FULL_LENGTH  /* value of y unit of measurement    */
	ozunit            FULL_LENGTH  /* value of z unit of measurement    */
	ooutdent_len      FULL_LENGTH  /* amount to outdent in outdent style*/
	osmallcaps_len    FULL_LENGTH  /* size of small capitals            */
	ofont             FONT_NUM     /* current font                      */
	ocolour           COLOUR_NUM   /* current colour		     */
	ounderline_colour COLOUR_NUM   /* current underline colour	     */
	otexture          TEXTURE_NUM  /* current texture		     */
	oblanklinescale   uint16       /* scale factor for blank lines      */
	olanguage         LANGUAGE_NUM /* :6 current language		     */
	ovadjust          bool         /* :1 @VAdjust in effect                */
	ohadjust          bool         /* :1 @HAdjust in effect                */
	opadjust          bool         /* :1 @PAdjust in effect                */
	osmall_caps       bool         /* :1 small capitals                    */
	ospace_style      uint8        /* :3 space style: lout, troff, tex, .. */
	ohyph_style       uint8        /* :2 hyphenation off or on             */
	ofill_style       uint8        /* :2 fill lines with text off/on       */
	odisplay_style    uint8        /* :3 display lines adjusted, ragged... */
	ooutline          bool         /* :2 TRUE if outlining words           */
	onobreakfirst     bool         /* :1 no break after first line of para */
	onobreaklast      bool         /* :1 no break after last line of para  */
	obaselinemark     bool         /* :1 baseline char metrics             */
	ostrut            bool         /* :1 strut char metrics                */
	oligatures        bool         /* :1 use ligatures                     */
	omarginkerning    bool         /* :1 perform margin kerning            */
	ocontext          Context_t    /* context stack		     */
}

//export SetGapOnGoRef
func SetGapOnGoRef(x GAP, xnobreak bool, xmark bool, xjoin bool,
	xunits uint8, xmode uint8, xwidth FULL_LENGTH) {

}

//export GapCopyOnGoRef
func GapCopyOnGoRef(x, y GAP) {

}

//export GapEqualOnRef
func GapEqualOnRef(x, y GAP) bool {
	return false
}
