#include "externs.h"

const FULL_CHAR *const LOUT_VERSION    = AsciiToFull("Basser Lout Version 3.42 (Dec 2020)");
const FULL_CHAR *const CROSS_DB        = AsciiToFull("lout");
const FULL_CHAR *const SOURCE_SUFFIX   = AsciiToFull(".lt");
const FULL_CHAR *const INDEX_SUFFIX    = AsciiToFull(".li");
const FULL_CHAR *const NEW_INDEX_SUFFIX    = AsciiToFull(".lix");
const FULL_CHAR *const DATA_SUFFIX     = AsciiToFull(".ld");
const FULL_CHAR *const NEW_DATA_SUFFIX = AsciiToFull("x");
const FULL_CHAR *const HYPH_SUFFIX     = AsciiToFull(".lh");
const FULL_CHAR *const HYPH_PACKED_SUFFIX  = AsciiToFull(".lp");
const FULL_CHAR *const FILTER_IN       = AsciiToFull("louti");
const FULL_CHAR *const FILTER_OUT      = AsciiToFull("lout");
const FULL_CHAR *const FILTER_ERR      = AsciiToFull("lout.err");

#if OS_UNIX
const char* const READ_FILE = "r";
const char* const WRITE_FILE = "w";
const char* const APPEND_FILE = "a";
const char* const STR_NEWLINE = AsciiToFull("\n");
const char* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps '%s' '%s'";
const char* const CONVERT_COM = "convert '%s' 'eps2:%s'";
const char* const LOUT_EPS = "lout.eps";
#else
#if OS_DOS
const char* const READ_FILE = "rb";
const char* const WRITE_FILE = "wb";
const char* const APPEND_FILE = "ab";
const char* const STR_NEWLINE = AsciiToFull("\r\n");
const char* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps %s %s";
const char* const CONVERT_COM = "convert %s eps2:%s";
const char* const LOUT_EPS = "lout.eps";
#else
#if OS_MAC
const char* const READ_FILE = "r";
const char* const WRITE_FILE = "w";
const char* const APPEND_FILE = "a";
const char* const STR_NEWLINE = AsciiToFull("\r");
const char* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps %s %s";
const char* const CONVERT_COM = "convert %s eps2:%s";
const char* const LOUT_EPS = "lout.eps";
#else
If you're compiling this, you've got the wrong settings in the makefile!
#endif
#endif
#endif

const char* const STR_EMPTY = AsciiToFull("");
const char* const STR_QUOTE = AsciiToFull("\"");
const char* const STR_ESCAPE = AsciiToFull("\\");
const char* const STR_COMMENT = AsciiToFull("#");
const char* const STR_SPACE = AsciiToFull(" ");
const char* const STR_FORMFEED = AsciiToFull("\f");
const char* const STR_TAB = AsciiToFull("\t");
const char* const STR_LETTERS_LOWER = AsciiToFull("abcdefghijklmnopqrstuvwxyz");
const char* const STR_LETTERS_UPPER = AsciiToFull("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const char* const STR_LETTERS_SYMSTART = AsciiToFull("@");
const char* const STR_LETTERS_UNDERSCORE = AsciiToFull("_");

#if CHAR_IN==0
const char* const STR_LETTERS_EXTRA0 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA1 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA2 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA3 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA4 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA5 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA6 = AsciiToFull("");
const char* const STR_LETTERS_EXTRA7 = AsciiToFull("");
#else
const char* const STR_LETTERS_EXTRA0 = AsciiToFull("\300\301\302\303\304\305\306\307");
const char* const STR_LETTERS_EXTRA1 = AsciiToFull("\310\311\312\313\314\315\316\317");
const char* const STR_LETTERS_EXTRA2 = AsciiToFull("\320\321\322\323\324\325\326");
const char* const STR_LETTERS_EXTRA3 = AsciiToFull("\330\331\332\333\334\335\336\337");
const char* const STR_LETTERS_EXTRA4 = AsciiToFull("\340\341\342\343\344\345\346\347");
const char* const STR_LETTERS_EXTRA5 = AsciiToFull("\350\351\352\353\354\355\356\357");
const char* const STR_LETTERS_EXTRA6 = AsciiToFull("\360\361\362\363\364\365\366");
const char* const STR_LETTERS_EXTRA7 = AsciiToFull("\370\371\372\373\374\375\376\377");
#endif

const char* const STR_STDIN = AsciiToFull("-");
const char* const STR_STDOUT = AsciiToFull("-");
const char* const STR_HYPHEN = AsciiToFull("-");
const char* const STR_EPS = AsciiToFull("EPS");
const char* const STR_POSTSCRIPT = AsciiToFull("PostScript");
const char* const STR_PLAINTEXT = AsciiToFull("PlainText");
const char* const STR_PDF = AsciiToFull("PDF");
const char* const STR_ELSE = AsciiToFull("else");
const char* const STR_NOCROSS = AsciiToFull("??");
const char* const STR_BADKEY = AsciiToFull("badkey");
const char* const STR_NONE = AsciiToFull("none");
const char* const STR_NOCHAR = AsciiToFull("-none-");
const char* const STR_ZERO = AsciiToFull("0");
const char* const STR_PS_SPACENAME = AsciiToFull("space");
const char* const STR_FONT_RECODE = AsciiToFull("Recode");
const char* const STR_FONT_NORECODE = AsciiToFull("NoRecode");
const char* const STR_COLOUR_NOCHANGE = AsciiToFull("nochange");
const char* const STR_TEXTURE_NOCHANGE = AsciiToFull("nochange");

const char* const STR_BREAK_HYPHEN = AsciiToFull("hyphen");
const char* const STR_BREAK_NOHYPHEN = AsciiToFull("nohyphen");
const char* const STR_BREAK_ADJUST = AsciiToFull("adjust");
const char* const STR_BREAK_OUTDENT = AsciiToFull("outdent");
const char* const STR_BREAK_RAGGED = AsciiToFull("ragged");
const char* const STR_BREAK_CRAGGED = AsciiToFull("cragged");
const char* const STR_BREAK_RRAGGED = AsciiToFull("rragged");
const char* const STR_BREAK_ORAGGED = AsciiToFull("oragged");
const char* const STR_BREAK_LINES = AsciiToFull("lines");
const char* const STR_BREAK_CLINES = AsciiToFull("clines");
const char* const STR_BREAK_RLINES = AsciiToFull("rlines");
const char* const STR_BREAK_OLINES = AsciiToFull("olines");
const char* const STR_BREAK_SCALE = AsciiToFull("blanklinescale");
const char* const STR_BREAK_NOFIRST = AsciiToFull("unbreakablefirst");
const char* const STR_BREAK_FIRST = AsciiToFull("breakablefirst");
const char* const STR_BREAK_NOLAST = AsciiToFull("unbreakablelast");
const char* const STR_BREAK_LAST = AsciiToFull("breakablelast");
const char* const STR_BREAK_SETOUTDENT = AsciiToFull("setoutdent");
const char* const STR_BREAK_MARGINKERNING = AsciiToFull("marginkerning");
const char* const STR_BREAK_NOMARGINKERNING = AsciiToFull("nomarginkerning");

const char* const STR_SPACE_LOUT = AsciiToFull("lout");
const char* const STR_SPACE_COMPRESS = AsciiToFull("compress");
const char* const STR_SPACE_SEPARATE = AsciiToFull("separate");
const char* const STR_SPACE_TROFF = AsciiToFull("troff");
const char* const STR_SPACE_TEX = AsciiToFull("tex");

const char* const STR_SMALL_CAPS_ON = AsciiToFull("smallcaps");
const char* const STR_SMALL_CAPS_OFF = AsciiToFull("nosmallcaps");
const char* const STR_SMALL_CAPS_SET = AsciiToFull("setsmallcaps");
const char* const STR_BASELINE_MARK = AsciiToFull("baselinemark");
const char* const STR_LIG = AsciiToFull("lig");
const char* const STR_NOLIG = AsciiToFull("nolig");
const char* const STR_XHEIGHT2_MARK = AsciiToFull("xheight2mark");
const char* const STR_NOSTRUT = AsciiToFull("nostrut");
const char* const STR_STRUT = AsciiToFull("strut");

const char* const STR_GAP_RJUSTIFY = AsciiToFull("1rt");
const char* const STR_GAP_ZERO_HYPH = AsciiToFull("0ch");

const char* const STR_SCALE_DOWN = AsciiToFull("downifneeded");

