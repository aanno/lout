// #include "externs.h"
#include "lout.h"

const FULL_CHAR* const LOUT_VERSION    = AsciiToFull("Basser Lout Version 3.42 (Dec 2020)");
const FULL_CHAR* const CROSS_DB        = AsciiToFull("lout");
const FULL_CHAR* const SOURCE_SUFFIX   = AsciiToFull(".lt");
const FULL_CHAR* const INDEX_SUFFIX    = AsciiToFull(".li");
const FULL_CHAR* const NEW_INDEX_SUFFIX    = AsciiToFull(".lix");
const FULL_CHAR* const DATA_SUFFIX     = AsciiToFull(".ld");
const FULL_CHAR* const NEW_DATA_SUFFIX = AsciiToFull("x");
const FULL_CHAR* const HYPH_SUFFIX     = AsciiToFull(".lh");
const FULL_CHAR* const HYPH_PACKED_SUFFIX  = AsciiToFull(".lp");
const FULL_CHAR* const FILTER_IN       = AsciiToFull("louti");
const FULL_CHAR* const FILTER_OUT      = AsciiToFull("lout");
const FULL_CHAR* const FILTER_ERR      = AsciiToFull("lout.err");

#if OS_UNIX
const char* const READ_FILE = "r";
const char* const WRITE_FILE = "w";
const char* const APPEND_FILE = "a";
const FULL_CHAR* const STR_NEWLINE = AsciiToFull("\n");
const FULL_CHAR* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps '%s' '%s'";
const char* const CONVERT_COM = "convert '%s' 'eps2:%s'";
const char* const LOUT_EPS = "lout.eps";
#else
#if OS_DOS
const char* const READ_FILE = "rb";
const char* const WRITE_FILE = "wb";
const char* const APPEND_FILE = "ab";
const FULL_CHAR* const STR_NEWLINE = AsciiToFull("\r\n");
const FULL_CHAR* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps %s %s";
const char* const CONVERT_COM = "convert %s eps2:%s";
const char* const LOUT_EPS = "lout.eps";
#else
#if OS_MAC
const char* const READ_FILE = "r";
const char* const WRITE_FILE = "w";
const char* const APPEND_FILE = "a";
const FULL_CHAR* const STR_NEWLINE = AsciiToFull("\r");
const FULL_CHAR* const STR_DIR = AsciiToFull("/");
const char* const UNCOMPRESS_COM = "gunzip -c %s > %s";
const char* const PDFTOPS_COM = "pdftops -eps %s %s";
const char* const CONVERT_COM = "convert %s eps2:%s";
const char* const LOUT_EPS = "lout.eps";
#else
If you're compiling this, you've got the wrong settings in the makefile!
#endif
#endif
#endif

const FULL_CHAR* const STR_EMPTY = AsciiToFull("");
const FULL_CHAR* const STR_QUOTE = AsciiToFull("\"");
const FULL_CHAR* const STR_ESCAPE = AsciiToFull("\\");
const FULL_CHAR* const STR_COMMENT = AsciiToFull("#");
const FULL_CHAR* const STR_SPACE = AsciiToFull(" ");
const FULL_CHAR* const STR_FORMFEED = AsciiToFull("\f");
const FULL_CHAR* const STR_TAB = AsciiToFull("\t");
const FULL_CHAR* const STR_LETTERS_LOWER = AsciiToFull("abcdefghijklmnopqrstuvwxyz");
const FULL_CHAR* const STR_LETTERS_UPPER = AsciiToFull("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const FULL_CHAR* const STR_LETTERS_SYMSTART = AsciiToFull("@");
const FULL_CHAR* const STR_LETTERS_UNDERSCORE = AsciiToFull("_");

#if CHAR_IN==0
const FULL_CHAR* const STR_LETTERS_EXTRA0 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA1 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA2 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA3 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA4 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA5 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA6 = AsciiToFull("");
const FULL_CHAR* const STR_LETTERS_EXTRA7 = AsciiToFull("");
#else
const FULL_CHAR* const STR_LETTERS_EXTRA0 = AsciiToFull("\300\301\302\303\304\305\306\307");
const FULL_CHAR* const STR_LETTERS_EXTRA1 = AsciiToFull("\310\311\312\313\314\315\316\317");
const FULL_CHAR* const STR_LETTERS_EXTRA2 = AsciiToFull("\320\321\322\323\324\325\326");
const FULL_CHAR* const STR_LETTERS_EXTRA3 = AsciiToFull("\330\331\332\333\334\335\336\337");
const FULL_CHAR* const STR_LETTERS_EXTRA4 = AsciiToFull("\340\341\342\343\344\345\346\347");
const FULL_CHAR* const STR_LETTERS_EXTRA5 = AsciiToFull("\350\351\352\353\354\355\356\357");
const FULL_CHAR* const STR_LETTERS_EXTRA6 = AsciiToFull("\360\361\362\363\364\365\366");
const FULL_CHAR* const STR_LETTERS_EXTRA7 = AsciiToFull("\370\371\372\373\374\375\376\377");
#endif

const FULL_CHAR* const STR_STDIN = AsciiToFull("-");
const FULL_CHAR* const STR_STDOUT = AsciiToFull("-");
const FULL_CHAR* const STR_HYPHEN = AsciiToFull("-");
const FULL_CHAR* const STR_EPS = AsciiToFull("EPS");
const FULL_CHAR* const STR_POSTSCRIPT = AsciiToFull("PostScript");
const FULL_CHAR* const STR_PLAINTEXT = AsciiToFull("PlainText");
const FULL_CHAR* const STR_PDF = AsciiToFull("PDF");
const FULL_CHAR* const STR_ELSE = AsciiToFull("else");
const FULL_CHAR* const STR_NOCROSS = AsciiToFull("??");
const FULL_CHAR* const STR_BADKEY = AsciiToFull("badkey");
const FULL_CHAR* const STR_NONE = AsciiToFull("none");
const FULL_CHAR* const STR_NOCHAR = AsciiToFull("-none-");
const FULL_CHAR* const STR_ZERO = AsciiToFull("0");
const FULL_CHAR* const STR_PS_SPACENAME = AsciiToFull("space");
const FULL_CHAR* const STR_FONT_RECODE = AsciiToFull("Recode");
const FULL_CHAR* const STR_FONT_NORECODE = AsciiToFull("NoRecode");
const FULL_CHAR* const STR_COLOUR_NOCHANGE = AsciiToFull("nochange");
const FULL_CHAR* const STR_TEXTURE_NOCHANGE = AsciiToFull("nochange");

const FULL_CHAR* const STR_BREAK_HYPHEN = AsciiToFull("hyphen");
const FULL_CHAR* const STR_BREAK_NOHYPHEN = AsciiToFull("nohyphen");
const FULL_CHAR* const STR_BREAK_ADJUST = AsciiToFull("adjust");
const FULL_CHAR* const STR_BREAK_OUTDENT = AsciiToFull("outdent");
const FULL_CHAR* const STR_BREAK_RAGGED = AsciiToFull("ragged");
const FULL_CHAR* const STR_BREAK_CRAGGED = AsciiToFull("cragged");
const FULL_CHAR* const STR_BREAK_RRAGGED = AsciiToFull("rragged");
const FULL_CHAR* const STR_BREAK_ORAGGED = AsciiToFull("oragged");
const FULL_CHAR* const STR_BREAK_LINES = AsciiToFull("lines");
const FULL_CHAR* const STR_BREAK_CLINES = AsciiToFull("clines");
const FULL_CHAR* const STR_BREAK_RLINES = AsciiToFull("rlines");
const FULL_CHAR* const STR_BREAK_OLINES = AsciiToFull("olines");
const FULL_CHAR* const STR_BREAK_SCALE = AsciiToFull("blanklinescale");
const FULL_CHAR* const STR_BREAK_NOFIRST = AsciiToFull("unbreakablefirst");
const FULL_CHAR* const STR_BREAK_FIRST = AsciiToFull("breakablefirst");
const FULL_CHAR* const STR_BREAK_NOLAST = AsciiToFull("unbreakablelast");
const FULL_CHAR* const STR_BREAK_LAST = AsciiToFull("breakablelast");
const FULL_CHAR* const STR_BREAK_SETOUTDENT = AsciiToFull("setoutdent");
const FULL_CHAR* const STR_BREAK_MARGINKERNING = AsciiToFull("marginkerning");
const FULL_CHAR* const STR_BREAK_NOMARGINKERNING = AsciiToFull("nomarginkerning");

const FULL_CHAR* const STR_SPACE_LOUT = AsciiToFull("lout");
const FULL_CHAR* const STR_SPACE_COMPRESS = AsciiToFull("compress");
const FULL_CHAR* const STR_SPACE_SEPARATE = AsciiToFull("separate");
const FULL_CHAR* const STR_SPACE_TROFF = AsciiToFull("troff");
const FULL_CHAR* const STR_SPACE_TEX = AsciiToFull("tex");

const FULL_CHAR* const STR_SMALL_CAPS_ON = AsciiToFull("smallcaps");
const FULL_CHAR* const STR_SMALL_CAPS_OFF = AsciiToFull("nosmallcaps");
const FULL_CHAR* const STR_SMALL_CAPS_SET = AsciiToFull("setsmallcaps");
const FULL_CHAR* const STR_BASELINE_MARK = AsciiToFull("baselinemark");
const FULL_CHAR* const STR_LIG = AsciiToFull("lig");
const FULL_CHAR* const STR_NOLIG = AsciiToFull("nolig");
const FULL_CHAR* const STR_XHEIGHT2_MARK = AsciiToFull("xheight2mark");
const FULL_CHAR* const STR_NOSTRUT = AsciiToFull("nostrut");
const FULL_CHAR* const STR_STRUT = AsciiToFull("strut");

const FULL_CHAR* const STR_GAP_RJUSTIFY = AsciiToFull("1rt");
const FULL_CHAR* const STR_GAP_ZERO_HYPH = AsciiToFull("0ch");

const FULL_CHAR* const STR_SCALE_DOWN = AsciiToFull("downifneeded");

/*@::Keywords@****************************************************************/
/*                                                                           */
/*  Keywords.                                                                */
/*                                                                           */
/*****************************************************************************/

const FULL_CHAR* const KW_START = AsciiToFull("\\Start");
const FULL_CHAR* const KW_PRINT = AsciiToFull("\\Print");
const FULL_CHAR* const KW_OPTGALL = AsciiToFull("@OptGall");
const FULL_CHAR* const KW_DEF = AsciiToFull("def");
const FULL_CHAR* const KW_FONTDEF = AsciiToFull("@FontDef");
const FULL_CHAR* const KW_FAMILY = AsciiToFull("@Family");
const FULL_CHAR* const KW_FACE = AsciiToFull("@Face");
const FULL_CHAR* const KW_NAME = AsciiToFull("@Name");
const FULL_CHAR* const KW_METRICS = AsciiToFull("@Metrics");
const FULL_CHAR* const KW_EXTRA_METRICS = AsciiToFull("@ExtraMetrics");
const FULL_CHAR* const KW_MAPPING = AsciiToFull("@Mapping");
const FULL_CHAR* const KW_RECODE = AsciiToFull("@Recode");
const FULL_CHAR* const KW_LANGDEF = AsciiToFull("langdef");
const FULL_CHAR* const KW_FORCE = AsciiToFull("force");
const FULL_CHAR* const KW_HORIZ = AsciiToFull("horizontally");
const FULL_CHAR* const KW_INTO = AsciiToFull("into");
const FULL_CHAR* const KW_EXTEND = AsciiToFull("extend");
const FULL_CHAR* const KW_IMPORT = AsciiToFull("import");
const FULL_CHAR* const KW_EXPORT = AsciiToFull("export");
const FULL_CHAR* const KW_PRECEDENCE = AsciiToFull("precedence");
const FULL_CHAR* const KW_ASSOC = AsciiToFull("associativity");
const FULL_CHAR* const KW_LEFT = AsciiToFull("left");
const FULL_CHAR* const KW_RIGHT = AsciiToFull("right");
const FULL_CHAR* const KW_BODY = AsciiToFull("body");
const FULL_CHAR* const KW_FILTER = AsciiToFull("@Filter");
const FULL_CHAR* const KW_FILTERIN = AsciiToFull("@FilterIn");
const FULL_CHAR* const KW_FILTEROUT = AsciiToFull("@FilterOut");
const FULL_CHAR* const KW_FILTERERR = AsciiToFull("@FilterErr");
const FULL_CHAR* const KW_MACRO = AsciiToFull("macro");
const FULL_CHAR* const KW_NAMED = AsciiToFull("named");
const FULL_CHAR* const KW_COMPULSORY = AsciiToFull("compulsory");
const FULL_CHAR* const KW_COMMON = AsciiToFull("@Common");
const FULL_CHAR* const KW_RUMP = AsciiToFull("@Rump");
const FULL_CHAR* const KW_MELD = AsciiToFull("@Meld");
const FULL_CHAR* const KW_INSERT = AsciiToFull("@Insert");
const FULL_CHAR* const KW_ONE_OF = AsciiToFull("@OneOf");
const FULL_CHAR* const KW_NEXT = AsciiToFull("@Next");
const FULL_CHAR* const KW_PLUS = AsciiToFull("@Plus");
const FULL_CHAR* const KW_MINUS = AsciiToFull("@Minus");
const FULL_CHAR* const KW_WIDE = AsciiToFull("@Wide");
const FULL_CHAR* const KW_HIGH = AsciiToFull("@High");
const FULL_CHAR* const KW_HSHIFT = AsciiToFull("@HShift");
const FULL_CHAR* const KW_VSHIFT = AsciiToFull("@VShift");
const FULL_CHAR* const KW_BEGIN_HEADER = AsciiToFull("@BeginHeaderComponent");
const FULL_CHAR* const KW_END_HEADER = AsciiToFull("@EndHeaderComponent");
const FULL_CHAR* const KW_SET_HEADER = AsciiToFull("@SetHeaderComponent");
const FULL_CHAR* const KW_CLEAR_HEADER = AsciiToFull("@ClearHeaderComponent");
const FULL_CHAR* const KW_ONE_COL = AsciiToFull("@OneCol");
const FULL_CHAR* const KW_ONE_ROW = AsciiToFull("@OneRow");
const FULL_CHAR* const KW_HMIRROR = AsciiToFull("@HMirror");
const FULL_CHAR* const KW_VMIRROR = AsciiToFull("@VMirror");
const FULL_CHAR* const KW_HSCALE = AsciiToFull("@HScale");
const FULL_CHAR* const KW_VSCALE = AsciiToFull("@VScale");
const FULL_CHAR* const KW_HCOVER = AsciiToFull("@HCover");
const FULL_CHAR* const KW_VCOVER = AsciiToFull("@VCover");
const FULL_CHAR* const KW_SCALE = AsciiToFull("@Scale");
const FULL_CHAR* const KW_KERN_SHRINK = AsciiToFull("@KernShrink");
const FULL_CHAR* const KW_HCONTRACT = AsciiToFull("@HContract");
const FULL_CHAR* const KW_VCONTRACT = AsciiToFull("@VContract");
const FULL_CHAR* const KW_HLIMITED = AsciiToFull("@HLimited");
const FULL_CHAR* const KW_VLIMITED = AsciiToFull("@VLimited");
const FULL_CHAR* const KW_HEXPAND = AsciiToFull("@HExpand");
const FULL_CHAR* const KW_VEXPAND = AsciiToFull("@VExpand");
const FULL_CHAR* const KW_STARTHVSPAN = AsciiToFull("@StartHVSpan");
const FULL_CHAR* const KW_STARTHSPAN = AsciiToFull("@StartHSpan");
const FULL_CHAR* const KW_STARTVSPAN = AsciiToFull("@StartVSpan");
const FULL_CHAR* const KW_HSPAN = AsciiToFull("@HSpan");
const FULL_CHAR* const KW_VSPAN = AsciiToFull("@VSpan");
const FULL_CHAR* const KW_PADJUST = AsciiToFull("@PAdjust");
const FULL_CHAR* const KW_HADJUST = AsciiToFull("@HAdjust");
const FULL_CHAR* const KW_VADJUST = AsciiToFull("@VAdjust");
const FULL_CHAR* const KW_ROTATE = AsciiToFull("@Rotate");
const FULL_CHAR* const KW_BACKGROUND = AsciiToFull("@Background");
const FULL_CHAR* const KW_INCGRAPHIC = AsciiToFull("@IncludeGraphic");
const FULL_CHAR* const KW_SINCGRAPHIC = AsciiToFull("@SysIncludeGraphic");
const FULL_CHAR* const KW_GRAPHIC = AsciiToFull("@Graphic");
const FULL_CHAR* const KW_LINK_SOURCE = AsciiToFull("@LinkSource");
const FULL_CHAR* const KW_LINK_DEST = AsciiToFull("@LinkDest");
const FULL_CHAR* const KW_LINK_URL = AsciiToFull("@URLLink");
const FULL_CHAR* const KW_PLAINGRAPHIC = AsciiToFull("@PlainGraphic");
const FULL_CHAR* const KW_VERBATIM = AsciiToFull("@Verbatim");
const FULL_CHAR* const KW_RAWVERBATIM = AsciiToFull("@RawVerbatim");
const FULL_CHAR* const KW_CASE = AsciiToFull("@Case");
const FULL_CHAR* const KW_YIELD = AsciiToFull("@Yield");
const FULL_CHAR* const KW_BACKEND = AsciiToFull("@BackEnd");
const FULL_CHAR* const KW_XCHAR = AsciiToFull("@Char");
const FULL_CHAR* const KW_FONT = AsciiToFull("@Font");
const FULL_CHAR* const KW_SPACE = AsciiToFull("@Space");
const FULL_CHAR* const KW_YUNIT = AsciiToFull("@YUnit");
const FULL_CHAR* const KW_ZUNIT = AsciiToFull("@ZUnit");
const FULL_CHAR* const KW_BREAK = AsciiToFull("@Break");
const FULL_CHAR* const KW_UNDERLINE = AsciiToFull("@Underline");
const FULL_CHAR* const KW_COLOUR = AsciiToFull("@SetColour");
const FULL_CHAR* const KW_COLOR = AsciiToFull("@SetColor");
const FULL_CHAR* const KW_UNDERLINE_COLOUR = AsciiToFull("@SetUnderlineColour");
const FULL_CHAR* const KW_UNDERLINE_COLOR = AsciiToFull("@SetUnderlineColor");
const FULL_CHAR* const KW_TEXTURE = AsciiToFull("@SetTexture");
const FULL_CHAR* const KW_OUTLINE = AsciiToFull("@Outline");
const FULL_CHAR* const KW_LANGUAGE = AsciiToFull("@Language");
const FULL_CHAR* const KW_CURR_LANG = AsciiToFull("@CurrLang");
const FULL_CHAR* const KW_CURR_FAMILY = AsciiToFull("@CurrFamily");
const FULL_CHAR* const KW_CURR_FACE = AsciiToFull("@CurrFace");
const FULL_CHAR* const KW_CURR_YUNIT = AsciiToFull("@CurrYUnit");
const FULL_CHAR* const KW_CURR_ZUNIT = AsciiToFull("@CurrZUnit");
const FULL_CHAR* const KW_ENV = AsciiToFull("@LEnv");
const FULL_CHAR* const KW_ENVA = AsciiToFull("@@A");
const FULL_CHAR* const KW_ENVB = AsciiToFull("@@B");
const FULL_CHAR* const KW_ENVC = AsciiToFull("@@C");
const FULL_CHAR* const KW_ENVD = AsciiToFull("@@D");
const FULL_CHAR* const KW_CENV = AsciiToFull("@@E");
const FULL_CHAR* const KW_CLOS = AsciiToFull("@LClos");
const FULL_CHAR* const KW_LVIS = AsciiToFull("@@V");
const FULL_CHAR* const KW_LUSE = AsciiToFull("@LUse");
const FULL_CHAR* const KW_LEO = AsciiToFull("@LEO");
const FULL_CHAR* const KW_OPEN = AsciiToFull("@Open");
const FULL_CHAR* const KW_USE = AsciiToFull("@Use");
const FULL_CHAR* const KW_NOT_REVEALED = AsciiToFull("@NotRevealed");
const FULL_CHAR* const KW_TAGGED = AsciiToFull("@Tagged");
const FULL_CHAR* const KW_DATABASE = AsciiToFull("@Database");
const FULL_CHAR* const KW_SYSDATABASE = AsciiToFull("@SysDatabase");
const FULL_CHAR* const KW_INCLUDE = AsciiToFull("@Include");
const FULL_CHAR* const KW_SYSINCLUDE = AsciiToFull("@SysInclude");
const FULL_CHAR* const KW_INCG_REPEATED = AsciiToFull("@IncludeGraphicRepeated");
const FULL_CHAR* const KW_SINCG_REPEATED = AsciiToFull("@SysIncludeGraphicRepeated");
const FULL_CHAR* const KW_PREPEND = AsciiToFull("@PrependGraphic");
const FULL_CHAR* const KW_SYSPREPEND = AsciiToFull("@SysPrependGraphic");
const FULL_CHAR* const KW_TARGET = AsciiToFull("@Target");
const FULL_CHAR* const KW_FOLLOWING = AsciiToFull("following");
const FULL_CHAR* const KW_PRECEDING = AsciiToFull("preceding");
const FULL_CHAR* const KW_FOLL_OR_PREC = AsciiToFull("foll_or_prec");
const FULL_CHAR* const KW_NOW = AsciiToFull("now");
const FULL_CHAR* const KW_NULL = AsciiToFull("@Null");
const FULL_CHAR* const KW_PAGE_LABEL = AsciiToFull("@PageLabel");
const FULL_CHAR* const KW_GALLEY = AsciiToFull("@Galley");
const FULL_CHAR* const KW_FORCE_GALLEY = AsciiToFull("@ForceGalley");
const FULL_CHAR* const KW_INPUT = AsciiToFull("@LInput");
const FULL_CHAR* const KW_SPLIT = AsciiToFull("@Split");
const FULL_CHAR* const KW_TAG = AsciiToFull("@Tag");
const FULL_CHAR* const KW_KEY = AsciiToFull("@Key");
const FULL_CHAR* const KW_OPTIMIZE = AsciiToFull("@Optimize");
const FULL_CHAR* const KW_MERGE = AsciiToFull("@Merge");
const FULL_CHAR* const KW_ENCLOSE = AsciiToFull("@Enclose");
const FULL_CHAR* const KW_CROSS = AsciiToFull("&&");
const FULL_CHAR* const KW_FORCE_CROSS = AsciiToFull("&&&");
const FULL_CHAR* const KW_LBR = AsciiToFull("{");
const FULL_CHAR* const KW_RBR = AsciiToFull("}");
const FULL_CHAR* const KW_BEGIN = AsciiToFull("@Begin");
const FULL_CHAR* const KW_END = AsciiToFull("@End");
const FULL_CHAR* const KW_VCAT_NN = AsciiToFull("//");
const FULL_CHAR* const KW_VCAT_MN = AsciiToFull("^//");
const FULL_CHAR* const KW_VCAT_NJ = AsciiToFull("/");
const FULL_CHAR* const KW_VCAT_MJ = AsciiToFull("^/");
const FULL_CHAR* const KW_HCAT_NN = AsciiToFull("||");
const FULL_CHAR* const KW_HCAT_MN = AsciiToFull("^||");
const FULL_CHAR* const KW_HCAT_NJ = AsciiToFull("|");
const FULL_CHAR* const KW_HCAT_MJ = AsciiToFull("^|");
const FULL_CHAR* const KW_ACAT_NJ = AsciiToFull("&");
const FULL_CHAR* const KW_ACAT_MJ = AsciiToFull("^&");
const FULL_CHAR* const KW_MOMENT = AsciiToFull("@Moment");
const FULL_CHAR* const KW_SECOND = AsciiToFull("@Second");
const FULL_CHAR* const KW_MINUTE = AsciiToFull("@Minute");
const FULL_CHAR* const KW_HOUR = AsciiToFull("@Hour");
const FULL_CHAR* const KW_DAY = AsciiToFull("@Day");
const FULL_CHAR* const KW_MONTH = AsciiToFull("@Month");
const FULL_CHAR* const KW_YEAR = AsciiToFull("@Year");
const FULL_CHAR* const KW_CENTURY = AsciiToFull("@Century");
const FULL_CHAR* const KW_WEEKDAY = AsciiToFull("@WeekDay");
const FULL_CHAR* const KW_YEARDAY = AsciiToFull("@YearDay");
const FULL_CHAR* const KW_DAYLIGHTSAVING = AsciiToFull("@DaylightSaving");
const FULL_CHAR* const KW_SET_CONTEXT = AsciiToFull("@SetContext");
const FULL_CHAR* const KW_GET_CONTEXT = AsciiToFull("@GetContext");

// OBJECT typesafe enum
// 0 where OBJTYPE is not relevant (tp)
const OBJTYPE DUMMY = {LINK_E};
// 1 where OBJTYPE is not relevant (tp)
const OBJTYPE DUMMY1 = {GAP_OBJ_E};
// 2 where OBJTYPE is not relevant (tp)
const OBJTYPE DUMMY2 = {CLOSURE_E};

const OBJTYPE LINK = {LINK_E};
const OBJTYPE GAP_OBJ = {GAP_OBJ_E};
const OBJTYPE CLOSURE = {CLOSURE_E};
const OBJTYPE UNDER_REC = {UNDER_REC_E};
const OBJTYPE PAGE_LABEL = {PAGE_LABEL_E};
const OBJTYPE NULL_CLOS = {NULL_CLOS_E};
const OBJTYPE CROSS = {CROSS_E};
const OBJTYPE FORCE_CROSS = {FORCE_CROSS_E};
const OBJTYPE LINK_DEST_NULL = {LINK_DEST_NULL_E};
const OBJTYPE HEAD = {HEAD_E};
const OBJTYPE SPLIT = {SPLIT_E};
const OBJTYPE PAR = {PAR_E};
const OBJTYPE WORD = {WORD_E};
const OBJTYPE QWORD = {QWORD_E};
const OBJTYPE HSPANNER = {HSPANNER_E};
const OBJTYPE VSPANNER = {VSPANNER_E};
const OBJTYPE ROW_THR = {ROW_THR_E};
const OBJTYPE COL_THR = {COL_THR_E};
const OBJTYPE ACAT = {ACAT_E};
const OBJTYPE HCAT = {HCAT_E};
const OBJTYPE VCAT = {VCAT_E};
const OBJTYPE BEGIN_HEADER = {BEGIN_HEADER_E};
const OBJTYPE END_HEADER = {END_HEADER_E};
const OBJTYPE SET_HEADER = {SET_HEADER_E};
const OBJTYPE CLEAR_HEADER = {CLEAR_HEADER_E};
const OBJTYPE ONE_COL = {ONE_COL_E};
const OBJTYPE ONE_ROW = {ONE_ROW_E};
const OBJTYPE WIDE = {WIDE_E};
const OBJTYPE HIGH = {HIGH_E};
const OBJTYPE HSHIFT = {HSHIFT_E};
const OBJTYPE VSHIFT = {VSHIFT_E};
const OBJTYPE HMIRROR = {HMIRROR_E};
const OBJTYPE VMIRROR = {VMIRROR_E};
const OBJTYPE HSCALE = {HSCALE_E};
const OBJTYPE VSCALE = {VSCALE_E};
const OBJTYPE HCOVER = {HCOVER_E};
const OBJTYPE VCOVER = {VCOVER_E};
const OBJTYPE SCALE = {SCALE_E};
const OBJTYPE KERN_SHRINK = {KERN_SHRINK_E};
const OBJTYPE HCONTRACT = {HCONTRACT_E};
const OBJTYPE VCONTRACT = {VCONTRACT_E};
const OBJTYPE HLIMITED = {HLIMITED_E};
const OBJTYPE VLIMITED = {VLIMITED_E};
const OBJTYPE HEXPAND = {HEXPAND_E};
const OBJTYPE VEXPAND = {VEXPAND_E};
const OBJTYPE START_HSPAN = {START_HSPAN_E};
const OBJTYPE START_VSPAN = {START_VSPAN_E};
const OBJTYPE START_HVSPAN = {START_HVSPAN_E};
const OBJTYPE HSPAN = {HSPAN_E};
const OBJTYPE VSPAN = {VSPAN_E};
const OBJTYPE PADJUST = {PADJUST_E};
const OBJTYPE HADJUST = {HADJUST_E};
const OBJTYPE VADJUST = {VADJUST_E};
const OBJTYPE ROTATE = {ROTATE_E};
const OBJTYPE BACKGROUND = {BACKGROUND_E};
const OBJTYPE CASE = {CASE_E};
const OBJTYPE VERBATIM = {VERBATIM_E};
const OBJTYPE RAW_VERBATIM = {RAW_VERBATIM_E};
const OBJTYPE YIELD = {YIELD_E};
const OBJTYPE BACKEND = {BACKEND_E};
const OBJTYPE FILTERED = {FILTERED_E};
const OBJTYPE XCHAR = {XCHAR_E};
const OBJTYPE FONT = {FONT_E};
const OBJTYPE SPACE = {SPACE_E};
const OBJTYPE YUNIT = {YUNIT_E};
const OBJTYPE ZUNIT = {ZUNIT_E};
const OBJTYPE SET_CONTEXT = {SET_CONTEXT_E};
const OBJTYPE GET_CONTEXT = {GET_CONTEXT_E};
const OBJTYPE BREAK = {BREAK_E};
const OBJTYPE UNDERLINE = {UNDERLINE_E};
const OBJTYPE UNDERLINE_COLOUR = {UNDERLINE_COLOUR_E};
const OBJTYPE COLOUR = {COLOUR_E};
const OBJTYPE TEXTURE = {TEXTURE_E};
const OBJTYPE OUTLINE = {OUTLINE_E};
const OBJTYPE LANGUAGE = {LANGUAGE_E};
const OBJTYPE CURR_LANG = {CURR_LANG_E};
const OBJTYPE CURR_FAMILY = {CURR_FAMILY_E};
const OBJTYPE CURR_FACE = {CURR_FACE_E};
const OBJTYPE CURR_YUNIT = {CURR_YUNIT_E};
const OBJTYPE CURR_ZUNIT = {CURR_ZUNIT_E};
const OBJTYPE COMMON = {COMMON_E};
const OBJTYPE RUMP = {RUMP_E};
const OBJTYPE MELD = {MELD_E};
const OBJTYPE INSERT = {INSERT_E};
const OBJTYPE ONE_OF = {ONE_OF_E};
const OBJTYPE NEXT = {NEXT_E};
const OBJTYPE PLUS = {PLUS_E};
const OBJTYPE MINUS = {MINUS_E};
const OBJTYPE ENV_OBJ = {ENV_OBJ_E};
const OBJTYPE ENV = {ENV_E};
const OBJTYPE ENVA = {ENVA_E};
const OBJTYPE ENVB = {ENVB_E};
const OBJTYPE ENVC = {ENVC_E};
const OBJTYPE ENVD = {ENVD_E};
const OBJTYPE CENV = {CENV_E};
const OBJTYPE CLOS = {CLOS_E};
const OBJTYPE LVIS = {LVIS_E};
const OBJTYPE LUSE = {LUSE_E};
const OBJTYPE LEO = {LEO_E};
const OBJTYPE OPEN = {OPEN_E};
const OBJTYPE TAGGED = {TAGGED_E};
const OBJTYPE INCGRAPHIC = {INCGRAPHIC_E};
const OBJTYPE SINCGRAPHIC = {SINCGRAPHIC_E};
const OBJTYPE PLAIN_GRAPHIC = {PLAIN_GRAPHIC_E};
const OBJTYPE GRAPHIC = {GRAPHIC_E};
const OBJTYPE LINK_SOURCE = {LINK_SOURCE_E};
const OBJTYPE LINK_DEST = {LINK_DEST_E};
const OBJTYPE LINK_URL = {LINK_URL_E};
const OBJTYPE TSPACE = {TSPACE_E};
const OBJTYPE TJUXTA = {TJUXTA_E};
const OBJTYPE LBR = {LBR_E};
const OBJTYPE RBR = {RBR_E};
const OBJTYPE BEGIN = {BEGIN_E};
const OBJTYPE END = {END_E};
const OBJTYPE USE = {USE_E};
const OBJTYPE NOT_REVEALED = {NOT_REVEALED_E};
const OBJTYPE GSTUB_NONE = {GSTUB_NONE_E};
const OBJTYPE GSTUB_INT = {GSTUB_INT_E};
const OBJTYPE GSTUB_EXT = {GSTUB_EXT_E};
const OBJTYPE UNEXPECTED_EOF = {UNEXPECTED_EOF_E};
const OBJTYPE INCLUDE = {INCLUDE_E};
const OBJTYPE SYS_INCLUDE = {SYS_INCLUDE_E};
const OBJTYPE PREPEND = {PREPEND_E};
const OBJTYPE SYS_PREPEND = {SYS_PREPEND_E};
const OBJTYPE INCG_REPEATED = {INCG_REPEATED_E};
const OBJTYPE SINCG_REPEATED = {SINCG_REPEATED_E};
const OBJTYPE DATABASE = {DATABASE_E};
const OBJTYPE SYS_DATABASE = {SYS_DATABASE_E};
const OBJTYPE DEAD = {DEAD_E};
const OBJTYPE UNATTACHED = {UNATTACHED_E};
const OBJTYPE RECEPTIVE = {RECEPTIVE_E};
const OBJTYPE RECEIVING = {RECEIVING_E};
const OBJTYPE RECURSIVE = {RECURSIVE_E};
const OBJTYPE PRECEDES = {PRECEDES_E};
const OBJTYPE FOLLOWS = {FOLLOWS_E};
const OBJTYPE CROSS_LIT = {CROSS_LIT_E};
const OBJTYPE CROSS_FOLL = {CROSS_FOLL_E};
const OBJTYPE CROSS_FOLL_OR_PREC = {CROSS_FOLL_OR_PREC_E};
const OBJTYPE GALL_FOLL = {GALL_FOLL_E};
const OBJTYPE GALL_FOLL_OR_PREC = {GALL_FOLL_OR_PREC_E};
const OBJTYPE CROSS_TARG = {CROSS_TARG_E};
const OBJTYPE GALL_TARG = {GALL_TARG_E};
const OBJTYPE GALL_PREC = {GALL_PREC_E};
const OBJTYPE CROSS_PREC = {CROSS_PREC_E};
const OBJTYPE PAGE_LABEL_IND = {PAGE_LABEL_IND_E};
const OBJTYPE SCALE_IND = {SCALE_IND_E};
const OBJTYPE COVER_IND = {COVER_IND_E};
const OBJTYPE EXPAND_IND = {EXPAND_IND_E};
const OBJTYPE THREAD = {THREAD_E};
const OBJTYPE CROSS_SYM = {CROSS_SYM_E};
const OBJTYPE CR_ROOT = {CR_ROOT_E};
const OBJTYPE MACRO = {MACRO_E};
const OBJTYPE LOCAL = {LOCAL_E};
const OBJTYPE LPAR = {LPAR_E};
const OBJTYPE NPAR = {NPAR_E};
const OBJTYPE RPAR = {RPAR_E};
const OBJTYPE EXT_GALL = {EXT_GALL_E};
const OBJTYPE CR_LIST = {CR_LIST_E};
const OBJTYPE SCOPE_SNAPSHOT = {SCOPE_SNAPSHOT_E};
const OBJTYPE DISPOSED = {DISPOSED_E};

// SPACE_MODE typesafe enum

const SPACE_MODE NO_MODE = {NO_MODE_E};
const SPACE_MODE EDGE_MODE = {EDGE_MODE_E};
const SPACE_MODE HYPH_MODE = {HYPH_MODE_E};
const SPACE_MODE MARK_MODE = {MARK_MODE_E};
const SPACE_MODE OVER_MODE = {OVER_MODE_E};
const SPACE_MODE KERN_MODE = {KERN_MODE_E};
const SPACE_MODE TAB_MODE = {TAB_MODE_E};
const SPACE_MODE ADD_HYPH = {ADD_HYPH_E};

// HYPH_STYLE typesafe enum

const HYPH_STYLE HYPH_UNDEF = {HYPH_UNDEF_E};
const HYPH_STYLE HYPH_OFF = {HYPH_OFF_E};
const HYPH_STYLE HYPH_ON = {HYPH_ON_E};

// FILL_STYLE typesafe enum

const FILL_STYLE FILL_UNDEF = {FILL_UNDEF_E};
const FILL_STYLE FILL_OFF = {FILL_OFF_E};
const FILL_STYLE FILL_ON= {FILL_ON_E};

// UNDERLINE typesafe enum

const UNDER UNDER_UNDEF = {UNDER_UNDEF_E};
const UNDER UNDER_OFF = {UNDER_OFF_E};
const UNDER UNDER_ON = {UNDER_ON_E};

// SPACE_STYLE typesafe enum

const SPACE_STYLE SPACE_LOUT = {SPACE_LOUT_E};
const SPACE_STYLE SPACE_COMPRESS = {SPACE_COMPRESS_E};
const SPACE_STYLE SPACE_SEPARATE = {SPACE_SEPARATE_E};
const SPACE_STYLE SPACE_TROFF = {SPACE_TROFF_E};
const SPACE_STYLE SPACE_TEX = {SPACE_TEX_E};

// DISPLAY_STYLE typesafe enum

const DISPLAY_STYLE DISPLAY_UNDEF = {DISPLAY_UNDEF_E};
const DISPLAY_STYLE DISPLAY_ADJUST = {DISPLAY_ADJUST_E};
const DISPLAY_STYLE DISPLAY_OUTDENT = {DISPLAY_OUTDENT_E};
const DISPLAY_STYLE DISPLAY_ORAGGED = {DISPLAY_OUTDENT_E};
const DISPLAY_STYLE DISPLAY_LEFT = {DISPLAY_LEFT_E};
const DISPLAY_STYLE DISPLAY_CENTRE = {DISPLAY_CENTRE_E};
const DISPLAY_STYLE DISPLAY_RIGHT = {DISPLAY_RIGHT_E};
const DISPLAY_STYLE DO_ADJUST = {DO_ADJUST_E};

// SMALLCAPS typesafe enum

const SMALLCAPS SMALL_CAPS_OFF = {SMALL_CAPS_OFF_E};
const SMALLCAPS SMALL_CAPS_ON = {SMALL_CAPS_ON_E};

// FILE_TYPE typesafe enum

const FILE_TYPE SOURCE_FILE = {SOURCE_FILE_E};
const FILE_TYPE INCLUDE_FILE = {INCLUDE_FILE_E};
const FILE_TYPE DATABASE_FILE = {DATABASE_FILE_E};
const FILE_TYPE INDEX_FILE = {INDEX_FILE_E};
const FILE_TYPE FONT_FILE = {FONT_FILE_E};
const FILE_TYPE PREPEND_FILE = {PREPEND_FILE_E};
const FILE_TYPE HYPH_FILE = {HYPH_FILE_E};
const FILE_TYPE HYPH_PACKED_FILE = {HYPH_PACKED_FILE_E};
const FILE_TYPE MAPPING_FILE = {MAPPING_FILE_E};
const FILE_TYPE FILTER_FILE = {FILTER_FILE_E};

// PATH_TYPE typesafe enum

const PATH_TYPE SOURCE_PATH = {SOURCE_PATH_E};
const PATH_TYPE INCLUDE_PATH = {INCLUDE_PATH_E};
const PATH_TYPE SYSINCLUDE_PATH = {SYSINCLUDE_PATH_E};
const PATH_TYPE DATABASE_PATH = {DATABASE_PATH_E};
const PATH_TYPE SYSDATABASE_PATH = {SYSDATABASE_PATH_E};
const PATH_TYPE FONT_PATH = {FONT_PATH_E};
const PATH_TYPE HYPH_PATH = {HYPH_PATH_E};
const PATH_TYPE MAPPING_PATH = {MAPPING_PATH_E};


// UNIT typesafe enum

const UNIT NO_UNIT = {NO_UNIT_E};
const UNIT FIXED_UNIT = {FIXED_UNIT_E};
const UNIT FRAME_UNIT = {FRAME_UNIT_E};
const UNIT AVAIL_UNIT = {AVAIL_UNIT_E};
const UNIT DEG_UNIT = {DEG_UNIT_E};
const UNIT NEXT_UNIT = {NEXT_UNIT_E};

// BACKEND_TE typesafe enum

const BACKEND_TE POSTSCRIPT = {POSTSCRIPT_E};
const BACKEND_TE PDF = {PDF_E};
const BACKEND_TE PLAINTEXT = {PLAINTEXT_E};

// ATTACH typesafe enum

const ATTACH ATTACH_KILLED = {ATTACH_NOTARGET_E};
const ATTACH ATTACH_INPUT = {ATTACH_INPUT_E};
const ATTACH ATTACH_NOTARGET = {ATTACH_NOTARGET_E};
const ATTACH ATTACH_SUSPEND = {ATTACH_SUSPEND_E};
const ATTACH ATTACH_NULL = {ATTACH_NULL_E};
const ATTACH ATTACH_ACCEPT = {ATTACH_ACCEPT_E};

// TIDY_TE typesafe enum

const TIDY_TE ACAT_TIDY = {ACAT_TIDY_E};
const TIDY_TE WORD_TIDY = {WORD_TIDY_E};
const TIDY_TE PARA_TIDY = {PARA_TIDY_E};

// MEM_TE typesafe enum

const MEM_TE MEM_BINARY = {MEM_BINARY_E};
const MEM_TE MEM_OBJECTS = {MEM_OBJECTS_E};
const MEM_TE MEM_FONTS = {MEM_FONTS_E};
const MEM_TE MEM_LEX = {MEM_LEX_E};
const MEM_TE MEM_FILES = {MEM_FILES_E};
const MEM_TE MEM_CROSSREF = {MEM_CROSSREF_E};
const MEM_TE MEM_PAGES = {MEM_PAGES_E};
const MEM_TE MEM_DBCHECK = {MEM_DBCHECK_E};
const MEM_TE MEM_DB = {MEM_DB_E};
const MEM_TE MEM_HYPH_PATS = {MEM_HYPH_PATS_E};
const MEM_TE MEM_CMAPS = {MEM_CMAPS_E};
const MEM_TE MEM_COLOUR_TAB = {MEM_COLOUR_TAB_E};
const MEM_TE MEM_TEXTURE_TAB = {MEM_TEXTURE_TAB_E};
const MEM_TE MEM_LANG_TAB = {MEM_LANG_TAB_E};

// MAP_TE typesafe enum

const MAP_TE MAP_UPPERCASE = {MAP_UPPERCASE_E};
const MAP_TE MAP_LOWERCASE = {MAP_LOWERCASE_E};
const MAP_TE MAP_UNACCENTED = {MAP_UNACCENTED_E};
const MAP_TE MAP_ACCENT = {MAP_ACCENT_E};

void initObject(OBJECT x, OBJTYPE typ) {
  // OBJTYPEs with gap (x->os5.ogap)
  // if (!gap(x)) {
    if (sameObjType(typ, GAP_OBJ) || sameObjType(typ, TSPACE) || sameObjType(typ, TJUXTA)) {
      GAP* g;
      // slow
      g = calloc(1L, zz_lengths[GAP_OBJ_E]);
      gap(x) = g;
    } 
  // }
  // OBJTYPEs with save_style (x->os2.ou4.osave_style)
  if (sameObjType(typ, CLOSURE) || sameObjType(typ, NULL_CLOS) || sameObjType(typ, ACAT) || sameObjType(typ, HCAT) || sameObjType(typ, VCAT) || sameObjType(typ, HSHIFT) || sameObjType(typ, VSHIFT) ||
      sameObjType(typ, INCGRAPHIC) || sameObjType(typ, SINCGRAPHIC) || sameObjType(typ, GRAPHIC) || sameObjType(typ, PLAIN_GRAPHIC) || 
      sameObjType(typ, LINK_DEST) || sameObjType(typ, LINK_SOURCE) || sameObjType(typ, LINK_URL) ||
      sameObjType(typ, BEGIN_HEADER) || sameObjType(typ, SET_HEADER)) {
    initStyle(&save_style(x));
  }
}
