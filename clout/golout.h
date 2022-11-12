#include <stddef.h>

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef size_t GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
#ifdef _MSC_VER
#include <complex.h>
typedef _Fcomplex GoComplex64;
typedef _Dcomplex GoComplex128;
#else
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;
#endif

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
// typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
// typedef struct { void *t; void *v; } GoInterface;
// typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif

extern GoUintptr newGap();
extern void freeGap(GoUintptr gap);
extern void SetGap(GoUintptr x, GoUint8 xnobreak, GoUint8 xmark, GoUint8 xjoin, GoUint8 xunits, GoUint8 xmode, GoInt32 xwidth);
extern void GapCopy(GoUintptr x, GoUintptr y);
extern GoUint8 GapEqual(GoUintptr x, GoUintptr y);

/*
#define	nobreak(x)	(x)->onobreak
#define	mark(x)		(x)->omark
#define	join(x)		(x)->ojoin
#define	units(x)	(x)->ounits
#define	mode(x)		(x)->omode
#define	width(x)	(x)->owidth
*/
extern GoUint8 nobreak(GoUintptr x);
extern GoUint8 mark(GoUintptr x);
extern GoUint8 join(GoUintptr x);
extern GoUint8 units(GoUintptr x);
extern GoUint8 mode(GoUintptr x);
extern GoInt32 width(GoUintptr x);
extern void setNobreak(GoUintptr x, GoUint8 nobreak);
extern void setMark(GoUintptr x, GoUint8 mark);
extern void setJoin(GoUintptr x, GoUint8 join);
extern void setUnits(GoUintptr x, GoUint8 units);
extern void setMode(GoUintptr x, GoUint8 mode);
extern void setWidth(GoUintptr x, GoInt32 width);

#ifdef __cplusplus
}
#endif
