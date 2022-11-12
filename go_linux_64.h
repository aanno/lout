// Defines needed for cgo for includes
// Derived from what is set in makefile to build
// 
// try:
// go tool cgo --dynimport liblout.so --dynlinker main.go
// readelf -s liblout.so

#define OS_UNIX   1 
#define OS_DOS    0
#define OS_MAC    0
#define DB_FIX    0
#define USE_STAT  1
#define SAFE_DFT  0
#define COLLATE   1
#define LIB_DIR   "/usr/local/share/lout-3.42/lib"
#define FONT_DIR  "font"
#define MAPS_DIR  "maps"
#define INCL_DIR  "include"
#define DATA_DIR  "data"
#define HYPH_DIR  "hyph"
#define LOCALE_DIR  "locale"
#define CHAR_IN   1
#define CHAR_OUT  0
#define DLOCALE_ON  1
#define ASSERT_ON 1
// #define DEBUG_ON  1
#define PDF_COMPRESSION 1

