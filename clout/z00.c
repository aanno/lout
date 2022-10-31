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

