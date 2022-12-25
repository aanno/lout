
#ifndef ENUMS_HEADER_H
#define ENUMS_HEADER_H

/*@::object types@************************************************************/
/*                                                                           */
/*  OBJECT, TOKEN AND OTHER TYPES inhabiting type(x) and predefined(x)       */
/*                                                                           */
/*  Key letters in the adjacent comment indicate where the tag is legal:     */
/*                                                                           */
/*    t  a token type, pushed on token stack                                 */
/*    o  an object type (returned by reduce(), inserted by Manifest)         */
/*    i  an index type (a child of a galley header other than an object)     */
/*    s  a predefined symbol (some symbol table entry has this predefined()) */
/*    n  an indefinite object i.e. one which is ignored in catenation ops    */
/*                                                                           */
/*****************************************************************************/

typedef enum objtyp_t {
    LINK_E = 0,       /*        a link between objects      0 */
    GAP_OBJ_E,        /*  o     a gap object               */
    CLOSURE_E,        /* to  n  a closure of a symbol      */
    UNDER_REC_E,      /*  o  n  record of underlining      */
    PAGE_LABEL_E,     /* to sn  @PageLabel                 */
    NULL_CLOS_E,      /* to sn  @Null                      */
    CROSS_E,          /* to sn  && (a cross reference obj) */
    FORCE_CROSS_E,    /* to sn  &&& (a forcing cross ref.) */
    LINK_DEST_NULL_E, /* to sn  @LinkDest (null version)   */
    HEAD_E,           /*  o  n  a galley header            */
    SPLIT_E,          /*  o     @Split                     10 */
    PAR_E,            /*  o     a parameter of a closure   */
    WORD_E,           /*  o     a word                     */
    QWORD_E,          /*  o     a word (was quoted in i/p) */
    HSPANNER_E,       /*  o     a horizontal spanner       */
    VSPANNER_E,       /*  o     a vertical spanner         */
    ROW_THR_E,        /*  o     a row thread               */
    COL_THR_E,        /*  o     a column thread            */
    ACAT_E,           /* to s   a sequence of &-ed objs    */
    HCAT_E,           /* to s   a sequence of |-ed objs    */
    VCAT_E,           /* to s   a sequence of /-ed objs    20 */
    BEGIN_HEADER_E,   /* to s   @BeginHeaderComponent      */
    END_HEADER_E,     /* to s   @EndHeaderComponent        */
    SET_HEADER_E,     /* to s   @SetHeaderComponent        */
    CLEAR_HEADER_E,   /* to s   @ClearHeaderComponent      */
    ONE_COL_E,        /* to s   @OneCol                    */
    ONE_ROW_E,        /* to s   @OneRow                    */
    WIDE_E,           /* to s   @Wide                      */
    HIGH_E,           /* to s   @High                      */
    HSHIFT_E,         /* to s   @HShift                    */
    VSHIFT_E,         /* to s   @VShift                    30 */
    HMIRROR_E,        /* to s   @HScale                    */
    VMIRROR_E,        /* to s   @VScale                    */
    HSCALE_E,         /* to s   @HScale                    */
    VSCALE_E,         /* to s   @VScale                    */
    HCOVER_E,         /* to s   @HCover                    */
    VCOVER_E,         /* to s   @VCover                    */
    SCALE_E,          /* to s   @Scale                     */
    KERN_SHRINK_E,    /* to s   @KernShrink                */
    HCONTRACT_E,      /* to s   @HContract                 */
    VCONTRACT_E,      /* to s   @VContract                 40 */
    HLIMITED_E,       /* to s   @HLimited                  */
    VLIMITED_E,       /* to s   @VLimited                  */
    HEXPAND_E,        /* to s   @HExpand                   */
    VEXPAND_E,        /* to s   @VExpand                   */
    START_HSPAN_E,    /* to s   @StartHSpan                */
    START_VSPAN_E,    /* to s   @StartVSpan                */
    START_HVSPAN_E,   /* to s   @StartHVSpan               */
    HSPAN_E,          /* to s   @HSpan                     */
    VSPAN_E,          /* to s   @VSpan                     */
    PADJUST_E,        /* to s   @PAdjust                   50 */
    HADJUST_E,        /* to s   @HAdjust                   */
    VADJUST_E,        /* to s   @VAdjust                   */
    ROTATE_E,         /* to s   @Rotate                    */
    BACKGROUND_E,     /* to s   @Background                */
    CASE_E,           /* to s   @Case                      */
    VERBATIM_E,       /* to s   @Verbatim                  */
    RAW_VERBATIM_E,   /* to s   @RawVerbatim               */
    YIELD_E,          /* to s   @Yield                     */
    BACKEND_E,        /* to s   @BackEnd                   */
    FILTERED_E,       /* to s   filtered object (no name)  60 */
    XCHAR_E,          /* to s   @Char                      */
    FONT_E,           /* to s   @Font                      */
    SPACE_E,          /* to s   @Space                     */
    YUNIT_E,          /* to s   @YUnit                     */
    ZUNIT_E,          /* to s   @ZUnit                     */
    SET_CONTEXT_E,    /* to s   @SetContext                */
    GET_CONTEXT_E,    /* to s   @GetContext                */
    BREAK_E,          /* to s   @Break                     */
    UNDERLINE_E,      /* to s   @Underline                 */
    UNDERLINE_COLOUR_E, /* to s   @SetUnderlineColour      70   */
    COLOUR_E,         /* to s   @SetColour and @SetColor   */
    TEXTURE_E,        /* to s   @SetTexture                */
    OUTLINE_E,        /* to s   @Outline                   */
    LANGUAGE_E,       /* to s   @Language                  */
    CURR_LANG_E,      /* to s   @CurrLang                  */
    CURR_FAMILY_E,    /* to s   @CurrFamily                */
    CURR_FACE_E,      /* to s   @CurrFace                  */
    CURR_YUNIT_E,     /* to s   @CurrYUnit                 */
    CURR_ZUNIT_E,     /* to s   @CurrZUnit                 */
    COMMON_E,         /* to s   @Common                    80 */
    RUMP_E,           /* to s   @Rump                      */
    MELD_E,           /* to s   @Meld                      */
    INSERT_E,         /* to s   @Insert                    */
    ONE_OF_E,         /* to s   @OneOf                     */
    NEXT_E,           /* to s   @Next                      */
    PLUS_E,           /* to s   @Plus                      */
    MINUS_E,          /* to s   @Minus                     */
    ENV_OBJ_E,        /* to s   object with envt (no name) */
    ENV_E,            /* to s   @LEnv                      */
    ENVA_E,           /* to s   @LEnvA                     90 */
    ENVB_E,           /* to s   @LEnvB                     */
    ENVC_E,           /* to s   @LEnvC                     */
    ENVD_E,           /* to s   @LEnvD                     */
    CENV_E,           /* to s   @LCEnv                     */
    CLOS_E,           /* to s   @LClos                     */
    LVIS_E,           /* to s   @LVis                      */
    LUSE_E,           /* to s   @LUse                      */
    LEO_E,            /* to s   @LEO                       */
    OPEN_E,           /* to s   @Open                      */
    TAGGED_E,         /* to s   @Tagged                   100 */
    INCGRAPHIC_E,     /* to s   @IncludeGraphic            */
    SINCGRAPHIC_E,    /* to s   @SysIncludeGraphic         */
    PLAIN_GRAPHIC_E,  /* to s   @PlainGraphic              */
    GRAPHIC_E,        /* to s   @Graphic                   */
    LINK_SOURCE_E,    /* to s   @LinkSource                */
    LINK_DEST_E,      /* to s   @LinkDest                  */
    LINK_URL_E,       /* to s   @URLLink                   */
    TSPACE_E,         /* t      a space token, parser only */
    TJUXTA_E,         /* t      a juxta token, parser only */
    LBR_E,            /* t  s   left brace token          110 */
    RBR_E,            /* t  s   right brace token          */
    BEGIN_E,          /* t  s   @Begin token               */
    END_E,            /* t  s   @End token                 */
    USE_E,            /* t  s   @Use                       */
    NOT_REVEALED_E,   /* t  s   @NotRevealed               */
    GSTUB_NONE_E,     /* t      a galley stub, no rpar     */
    GSTUB_INT_E,      /* t      galley stub internal rpar  */
    GSTUB_EXT_E,      /* t      galley stub external rpar  */
    UNEXPECTED_EOF_E, /* t      unexpected end of file     */
    INCLUDE_E,        /*    s   @Include                  120 */
    SYS_INCLUDE_E,    /*    s   @SysInclude                */
    PREPEND_E,        /*    s   @Prepend                   */
    SYS_PREPEND_E,    /*    s   @SysPrepend                */
    INCG_REPEATED_E,  /*    s   @IncludeGraphicRepeated    */
    SINCG_REPEATED_E, /*    s   @SysIncludeGraphicRepeated */
    DATABASE_E,       /*    s   @Database                  */
    SYS_DATABASE_E,   /*    s   @SysDatabase               */
    DEAD_E,           /*   i    a dead galley              */
    UNATTACHED_E,     /*   i    an inner, unsized galley   */
    RECEPTIVE_E,      /*   i    a receptive object index  130 */
    RECEIVING_E,      /*   i    a receiving object index   */
    RECURSIVE_E,      /*   i    a recursive definite obj.  */
    PRECEDES_E,       /*   i    an ordering extern constraint     */
    FOLLOWS_E,        /*   i    other end of ordering c.   */
    CROSS_LIT_E,      /*   i    literal word cross-ref     */
    CROSS_FOLL_E,     /*   i    following type cross-ref   */
    CROSS_FOLL_OR_PREC_E, /*   i    follorprec type cross-ref  */
    GALL_FOLL_E,      /*   i    galley with &&following    */
    GALL_FOLL_OR_PREC_E,  /*   i    galley with &&following    */
    CROSS_TARG_E,     /*   i    value of cross-ref        140 */
    GALL_TARG_E,      /*   i    target of these galleys    */
    GALL_PREC_E,      /*   i    galley with &&preceding    */
    CROSS_PREC_E,     /*   i    preceding type cross-ref   */
    PAGE_LABEL_IND_E, /*   i    index of PAGE_LABEL        */
    SCALE_IND_E,      /*   i    index of auto SCALE        */
    COVER_IND_E,      /*   i    index of HCOVER or VCOVER  */
    EXPAND_IND_E,     /*   i    index of HEXPAND or VEXPD  */
    THREAD_E,         /*        a sequence of threads      */
    CROSS_SYM_E,      /*        cross-ref info             */
    CR_ROOT_E,        /*        RootCross                 150 */
    MACRO_E,          /*        a macro symbol             */
    LOCAL_E,          /*        a local symbol             */
    LPAR_E,           /*        a left parameter           */
    NPAR_E,           /*        a named parameter          */
    RPAR_E,           /*        a right parameter          */
    EXT_GALL_E,       /*        an external galley         */
    CR_LIST_E,        /*        a list of cross references */
    SCOPE_SNAPSHOT_E, /*        a scope snapshot	     */
    DISPOSED_E,       /* 159        a disposed record     159     */
} OBJTYPE_T;

typedef struct objtype { OBJTYPE_T objtype; } OBJTYPE;

// 0 where OBJTYPE is not relevant (tp)
extern const OBJTYPE DUMMY;
#define DUMMY_E LINK_E
// 1 where OBJTYPE is not relevant (tp)
extern const OBJTYPE DUMMY1;
#define DUMMY1_E GAP_OBJ_E
// 2 where OBJTYPE is not relevant (tp)
extern const OBJTYPE DUMMY2;
#define DUMMY2_E CLOSURE_E

extern const OBJTYPE LINK;
extern const OBJTYPE GAP_OBJ;
extern const OBJTYPE CLOSURE;
extern const OBJTYPE UNDER_REC;
extern const OBJTYPE PAGE_LABEL;
extern const OBJTYPE NULL_CLOS;
extern const OBJTYPE CROSS;
extern const OBJTYPE FORCE_CROSS;
extern const OBJTYPE LINK_DEST_NULL;
extern const OBJTYPE HEAD;
extern const OBJTYPE SPLIT;
extern const OBJTYPE PAR;
extern const OBJTYPE WORD;
extern const OBJTYPE QWORD;
extern const OBJTYPE HSPANNER;
extern const OBJTYPE VSPANNER;
extern const OBJTYPE ROW_THR;
extern const OBJTYPE COL_THR;
extern const OBJTYPE ACAT;
extern const OBJTYPE HCAT;
extern const OBJTYPE VCAT;
extern const OBJTYPE BEGIN_HEADER;
extern const OBJTYPE END_HEADER;
extern const OBJTYPE SET_HEADER;
extern const OBJTYPE CLEAR_HEADER;
extern const OBJTYPE ONE_COL;
extern const OBJTYPE ONE_ROW;
extern const OBJTYPE WIDE;
extern const OBJTYPE HIGH;
extern const OBJTYPE HSHIFT;
extern const OBJTYPE VSHIFT;
extern const OBJTYPE HMIRROR;
extern const OBJTYPE VMIRROR;
extern const OBJTYPE HSCALE;
extern const OBJTYPE VSCALE;
extern const OBJTYPE HCOVER;
extern const OBJTYPE VCOVER;
extern const OBJTYPE SCALE;
extern const OBJTYPE KERN_SHRINK;
extern const OBJTYPE HCONTRACT;
extern const OBJTYPE VCONTRACT;
extern const OBJTYPE HLIMITED;
extern const OBJTYPE VLIMITED;
extern const OBJTYPE HEXPAND;
extern const OBJTYPE VEXPAND;
extern const OBJTYPE START_HSPAN;
extern const OBJTYPE START_VSPAN;
extern const OBJTYPE START_HVSPAN;
extern const OBJTYPE HSPAN;
extern const OBJTYPE VSPAN;
extern const OBJTYPE PADJUST;
extern const OBJTYPE HADJUST;
extern const OBJTYPE VADJUST;
extern const OBJTYPE ROTATE;
extern const OBJTYPE BACKGROUND;
extern const OBJTYPE CASE;
extern const OBJTYPE VERBATIM;
extern const OBJTYPE RAW_VERBATIM;
extern const OBJTYPE YIELD;
extern const OBJTYPE BACKEND;
extern const OBJTYPE FILTERED;
extern const OBJTYPE XCHAR;
extern const OBJTYPE FONT;
extern const OBJTYPE SPACE;
extern const OBJTYPE YUNIT;
extern const OBJTYPE ZUNIT;
extern const OBJTYPE SET_CONTEXT;
extern const OBJTYPE GET_CONTEXT;
extern const OBJTYPE BREAK;
extern const OBJTYPE UNDERLINE;
extern const OBJTYPE UNDERLINE_COLOUR;
extern const OBJTYPE COLOUR;
extern const OBJTYPE TEXTURE;
extern const OBJTYPE OUTLINE;
extern const OBJTYPE LANGUAGE;
extern const OBJTYPE CURR_LANG;
extern const OBJTYPE CURR_FAMILY;
extern const OBJTYPE CURR_FACE;
extern const OBJTYPE CURR_YUNIT;
extern const OBJTYPE CURR_ZUNIT;
extern const OBJTYPE COMMON;
extern const OBJTYPE RUMP;
extern const OBJTYPE MELD;
extern const OBJTYPE INSERT;
extern const OBJTYPE ONE_OF;
extern const OBJTYPE NEXT;
extern const OBJTYPE PLUS;
extern const OBJTYPE MINUS;
extern const OBJTYPE ENV_OBJ;
extern const OBJTYPE ENV;
extern const OBJTYPE ENVA;
extern const OBJTYPE ENVB;
extern const OBJTYPE ENVC;
extern const OBJTYPE ENVD;
extern const OBJTYPE CENV;
extern const OBJTYPE CLOS;
extern const OBJTYPE LVIS;
extern const OBJTYPE LUSE;
extern const OBJTYPE LEO;
extern const OBJTYPE OPEN;
extern const OBJTYPE TAGGED;
extern const OBJTYPE INCGRAPHIC;
extern const OBJTYPE SINCGRAPHIC;
extern const OBJTYPE PLAIN_GRAPHIC;
extern const OBJTYPE GRAPHIC;
extern const OBJTYPE LINK_SOURCE;
extern const OBJTYPE LINK_DEST;
extern const OBJTYPE LINK_URL;
extern const OBJTYPE TSPACE;
extern const OBJTYPE TJUXTA;
extern const OBJTYPE LBR;
extern const OBJTYPE RBR;
extern const OBJTYPE BEGIN;
extern const OBJTYPE END;
extern const OBJTYPE USE;
extern const OBJTYPE NOT_REVEALED;
extern const OBJTYPE GSTUB_NONE;
extern const OBJTYPE GSTUB_INT;
extern const OBJTYPE GSTUB_EXT;
extern const OBJTYPE UNEXPECTED_EOF;
extern const OBJTYPE INCLUDE;
extern const OBJTYPE SYS_INCLUDE;
extern const OBJTYPE PREPEND;
extern const OBJTYPE SYS_PREPEND;
extern const OBJTYPE INCG_REPEATED;
extern const OBJTYPE SINCG_REPEATED;
extern const OBJTYPE DATABASE;
extern const OBJTYPE SYS_DATABASE;
extern const OBJTYPE DEAD;
extern const OBJTYPE UNATTACHED;
extern const OBJTYPE RECEPTIVE;
extern const OBJTYPE RECEIVING;
extern const OBJTYPE RECURSIVE;
extern const OBJTYPE PRECEDES;
extern const OBJTYPE FOLLOWS;
extern const OBJTYPE CROSS_LIT;
extern const OBJTYPE CROSS_FOLL;
extern const OBJTYPE CROSS_FOLL_OR_PREC;
extern const OBJTYPE GALL_FOLL;
extern const OBJTYPE GALL_FOLL_OR_PREC;
extern const OBJTYPE CROSS_TARG;
extern const OBJTYPE GALL_TARG;
extern const OBJTYPE GALL_PREC;
extern const OBJTYPE CROSS_PREC;
extern const OBJTYPE PAGE_LABEL_IND;
extern const OBJTYPE SCALE_IND;
extern const OBJTYPE COVER_IND;
extern const OBJTYPE EXPAND_IND;
extern const OBJTYPE THREAD;
extern const OBJTYPE CROSS_SYM;
extern const OBJTYPE CR_ROOT;
extern const OBJTYPE MACRO;
extern const OBJTYPE LOCAL;
extern const OBJTYPE LPAR;
extern const OBJTYPE NPAR;
extern const OBJTYPE RPAR;
extern const OBJTYPE EXT_GALL;
extern const OBJTYPE CR_LIST;
extern const OBJTYPE SCOPE_SNAPSHOT;
extern const OBJTYPE DISPOSED;

/* gap modes occupying mode(x) */
typedef enum space_mode_t {
    NO_MODE_E = 0,    /* for error detection: no mode      */
    EDGE_MODE_E,      /* edge-to-edge spacing              */
    HYPH_MODE_E,      /* edge-to-edge with hyphenation     */
    MARK_MODE_E,      /* mark-to-mark spacing              */
    OVER_MODE_E,      /* overstrike spacing                */
    KERN_MODE_E,      /* kerning spacing                   */
    TAB_MODE_E,       /* tabulation spacing                */
    ADD_HYPH_E        /* 7  temp value used by FillObject     */
} SPACE_MODE_T;

typedef struct space_mode { SPACE_MODE_T spacemode; } SPACE_MODE;

extern const SPACE_MODE NO_MODE;
extern const SPACE_MODE EDGE_MODE;
extern const SPACE_MODE HYPH_MODE;
extern const SPACE_MODE MARK_MODE;
extern const SPACE_MODE OVER_MODE;
extern const SPACE_MODE KERN_MODE;
extern const SPACE_MODE TAB_MODE;
extern const SPACE_MODE ADD_HYPH;

/* hyph_style(style) options                                                 */
// #define	HYPH_UNDEF	     0		/* hyphenation option undefined      */
// #define	HYPH_OFF	     1		/* hyphenation off                   */
// #define	HYPH_ON		     2		/* hyphenation on                    */

typedef enum hyph_style_t {
    HYPH_UNDEF_E = 0,
    HYPH_OFF_E,
    HYPH_ON_E
} HYPH_STYLE_T;

typedef struct hyph_style { HYPH_STYLE_T hyphstyle; } HYPH_STYLE;

extern const HYPH_STYLE HYPH_UNDEF;
extern const HYPH_STYLE HYPH_OFF;
extern const HYPH_STYLE HYPH_ON;

/* fill_style(style) options                                                 */
// #define	FILL_UNDEF	     0		/* fill option undefined             */
// #define	FILL_OFF	     1		/* no filling of lines               */
// #define	FILL_ON		     2		/* fill lines with text              */

typedef enum fill_style_t {
    FILL_UNDEF_E = 0,
    FILL_OFF_E,
    FILL_ON_E,
} FILL_STYLE_T;

typedef struct fill_style { FILL_STYLE_T fillstyle; } FILL_STYLE;

extern const FILL_STYLE FILL_UNDEF;
extern const FILL_STYLE FILL_OFF;
extern const FILL_STYLE FILL_ON;

/* underline(obj) options                                                    */
// #define	UNDER_UNDEF	     0		/* underline undefined               */
// #define	UNDER_OFF	     1		/* no underlining	             */
// #define	UNDER_ON	     2		/* underline this                    */

typedef enum under_t {
    UNDER_UNDEF_E = 0,
    UNDER_OFF_E,
    UNDER_ON_E
} UNDER_T;

typedef struct under { UNDER_T underline; } UNDER;

extern const UNDER UNDER_UNDEF;
extern const UNDER UNDER_OFF;
extern const UNDER UNDER_ON;

/* space_style(style) options                                                */
// #define	SPACE_LOUT	     0		/* interpret white space Lout's way  */
// #define	SPACE_COMPRESS	     1		/* compress multiple white spaces    */
// #define	SPACE_SEPARATE	     2		/* compress an separate              */
// #define	SPACE_TROFF	     3		/* interpret white space troff's way */
// #define	SPACE_TEX	     4		/* interpret white space TeX's way   */

typedef enum space_style_t {
    SPACE_LOUT_E = 0,
    SPACE_COMPRESS_E,
    SPACE_SEPARATE_E,
    SPACE_TROFF_E,
    SPACE_TEX_E
} SPACE_STYLE_T;

typedef struct space_style { SPACE_STYLE_T spacestyle; } SPACE_STYLE;

extern const SPACE_STYLE SPACE_LOUT;
extern const SPACE_STYLE SPACE_COMPRESS;
extern const SPACE_STYLE SPACE_SEPARATE;
extern const SPACE_STYLE SPACE_TROFF;
extern const SPACE_STYLE SPACE_TEX;

/* display_style(style) options                                              */
// #define	DISPLAY_UNDEF	     0		/* display option undefined          */
// #define	DISPLAY_ADJUST	     1		/* adjust lines (except last)        */
// #define	DISPLAY_OUTDENT	     2		/* outdent lines (except first)      */
// #define	DISPLAY_ORAGGED	     3		/* outdent but don't adjust          */
// #define	DISPLAY_LEFT	     4		/* left-justify lines, no adjust     */
// #define	DISPLAY_CENTRE	     5		/* centre lines, no adjust           */
// #define	DISPLAY_RIGHT	     6		/* right-justify lines, no adjust    */
// #define	DO_ADJUST	     7		/* placed in ACATs when adjust need  */

typedef enum display_style_t {
    DISPLAY_UNDEF_E = 0,
    DISPLAY_ADJUST_E,
    DISPLAY_OUTDENT_E,
    DISPLAY_ORAGGED_E,
    DISPLAY_LEFT_E,
    DISPLAY_CENTRE_E,
    DISPLAY_RIGHT_E,
    DO_ADJUST_E
} DISPLAY_STYLE_T;

typedef struct display_style { DISPLAY_STYLE_T displaystyle; } DISPLAY_STYLE;

extern const DISPLAY_STYLE DISPLAY_UNDEF;
extern const DISPLAY_STYLE DISPLAY_ADJUST;
extern const DISPLAY_STYLE DISPLAY_OUTDENT;
extern const DISPLAY_STYLE DISPLAY_ORAGGED;
extern const DISPLAY_STYLE DISPLAY_LEFT;
extern const DISPLAY_STYLE DISPLAY_CENTRE;
extern const DISPLAY_STYLE DISPLAY_RIGHT;
extern const DISPLAY_STYLE DO_ADJUST;

/* small_caps(style) options                                                 */
// #define	SMALL_CAPS_OFF	     0		/* don't want small capitals         */
// #define	SMALL_CAPS_ON	     1		/* small capitals                    */

typedef enum smallcaps_t {
    SMALL_CAPS_OFF_E = 0,
    SMALL_CAPS_ON_E
} SMALLCAPS_T;

typedef struct smallcaps { SMALLCAPS_T smallcaps; } SMALLCAPS;

extern const SMALLCAPS SMALL_CAPS_OFF;
extern const SMALLCAPS SMALL_CAPS_ON;

/* file types */
// #define	SOURCE_FILE	     0		/* input file from command line      */
// #define	INCLUDE_FILE	     1		/* @Include file                     */
// #define	DATABASE_FILE	     2		/* database file                     */
// #define	INDEX_FILE	     3		/* database index file               */
// #define	FONT_FILE	     4		/* font file                         */
// #define	PREPEND_FILE	     5		/* PostScript prologue file          */
// #define	HYPH_FILE	     6		/* hyphenation file                  */
// #define	HYPH_PACKED_FILE     7		/* packed hyphenation file           */
// #define	MAPPING_FILE	     8		/* character mapping file            */
// #define	FILTER_FILE	     9		/* filter output file                */

typedef enum file_type_t {
    SOURCE_FILE_E = 0,
    INCLUDE_FILE_E,
    DATABASE_FILE_E,
    INDEX_FILE_E,
    FONT_FILE_E,
    PREPEND_FILE_E,
    HYPH_FILE_E,
    HYPH_PACKED_FILE_E,
    MAPPING_FILE_E,
    FILTER_FILE_E
} FILE_TYPE_T;

#define	MAX_TYPES_E	    (FILTER_FILE_E + 1)		/* number of file types              */

typedef struct file_type { FILE_TYPE_T filetype; } FILE_TYPE;

extern const FILE_TYPE SOURCE_FILE;
extern const FILE_TYPE INCLUDE_FILE;
extern const FILE_TYPE DATABASE_FILE;
extern const FILE_TYPE INDEX_FILE;
extern const FILE_TYPE FONT_FILE;
extern const FILE_TYPE PREPEND_FILE;
extern const FILE_TYPE HYPH_FILE;
extern const FILE_TYPE HYPH_PACKED_FILE;
extern const FILE_TYPE MAPPING_FILE;
extern const FILE_TYPE FILTER_FILE;

/* path types (i.e. sequences of directories for file searching) */
// #define	SOURCE_PATH	     0		/* path to search for source files   */
// #define	INCLUDE_PATH	     1		/* path for @Include files           */
// #define	SYSINCLUDE_PATH	     2		/* path for @SysInclude files        */
// #define	DATABASE_PATH	     3		/* path for @Database files          */
// #define	SYSDATABASE_PATH     4		/* path for @SysDatabase files       */
// #define	FONT_PATH	     5		/* path for font metrics (AFM) files */
// #define	HYPH_PATH	     6		/* path for hyphenation files        */
// #define	MAPPING_PATH	     7		/* path for mapping (LCM) files      */

typedef enum path_type_t {
    SOURCE_PATH_E = 0,
    INCLUDE_PATH_E,
    SYSINCLUDE_PATH_E,
    DATABASE_PATH_E,
    SYSDATABASE_PATH_E,
    FONT_PATH_E,
    HYPH_PATH_E,
    MAPPING_PATH_E
} PATH_TYPE_T;

#define	MAX_PATHS_E	     (MAPPING_PATH_E + 1)		/* number of mapping paths           */

typedef struct path_type { PATH_TYPE_T pathtype; } PATH_TYPE;

extern const PATH_TYPE SOURCE_PATH;
extern const PATH_TYPE INCLUDE_PATH;
extern const PATH_TYPE SYSINCLUDE_PATH;
extern const PATH_TYPE DATABASE_PATH;
extern const PATH_TYPE SYSDATABASE_PATH;
extern const PATH_TYPE FONT_PATH;
extern const PATH_TYPE HYPH_PATH;
extern const PATH_TYPE MAPPING_PATH;

/* units of measurement */
// #define	NO_UNIT		     0		/* no unit - for error detection     */
// #define	FIXED_UNIT	     1		/* inches, cm, points, ems, y, z     */
// #define	FRAME_UNIT	     2		/* b unit (frame widths)             */
// #define	AVAIL_UNIT	     3		/* r unit (available spaces)         */
// #define	DEG_UNIT	     4		/* d unit (degrees)                  */
// #define	NEXT_UNIT	     5		/* w unit (inners)                   */

typedef enum unit_t {
    NO_UNIT_E = 0,
    FIXED_UNIT_E,
    FRAME_UNIT_E,
    AVAIL_UNIT_E,
    DEG_UNIT_E,
    NEXT_UNIT_E
} UNIT_T;

typedef struct unit { UNIT_T unit; } UNIT;

extern const UNIT NO_UNIT;
extern const UNIT FIXED_UNIT;
extern const UNIT FRAME_UNIT;
extern const UNIT AVAIL_UNIT;
extern const UNIT DEG_UNIT;
extern const UNIT NEXT_UNIT;

/* back ends */
// #define POSTSCRIPT           0		/* PostScript back end               */
// #define	PDF		     1		/* PDF back end			     */
// #define	PLAINTEXT	     2		/* plain text back end               */

typedef enum backend_t {
    POSTSCRIPT_E = 0,
    PDF_E,
    PLAINTEXT_E
} BACKEND_T;

typedef struct backend_te { BACKEND_T backend; } BACKEND_TE;

extern const BACKEND_TE POSTSCRIPT;
extern const BACKEND_TE PDF;
extern const BACKEND_TE PLAINTEXT;

/* status values returned by AttachGalley() */
// #define	ATTACH_KILLED	     0
// #define	ATTACH_INPUT	     1
// #define	ATTACH_NOTARGET	     2
// #define	ATTACH_SUSPEND	     3
// #define	ATTACH_NULL	     4
// #define	ATTACH_ACCEPT	     5

typedef enum attach_t {
    ATTACH_KILLED_E = 0,
    ATTACH_INPUT_E,
    ATTACH_NOTARGET_E,
    ATTACH_SUSPEND_E,
    ATTACH_NULL_E,
    ATTACH_ACCEPT_E
} ATTACH_T;

typedef struct attach { ATTACH_T attach; } ATTACH;

extern const ATTACH ATTACH_KILLED;
extern const ATTACH ATTACH_INPUT;
extern const ATTACH ATTACH_NOTARGET;
extern const ATTACH ATTACH_SUSPEND;
extern const ATTACH ATTACH_NULL;
extern const ATTACH ATTACH_ACCEPT;

/* kinds of tidying up accepted by ReplaceWithTidy */
// #define	ACAT_TIDY	     0
// #define	WORD_TIDY	     1
// #define	PARA_TIDY	     2

typedef enum tidy_t {
    ACAT_TIDY_E = 0,
    WORD_TIDY_E,
    PARA_TIDY_E
} TIDY_T;

typedef struct tidy_te { TIDY_T tidy; } TIDY_TE;

extern const TIDY_TE ACAT_TIDY;
extern const TIDY_TE WORD_TIDY;
extern const TIDY_TE PARA_TIDY;

/* types of memory usage, used to debug memory consumption */
// #define	MEM_BINARY	     0		/* the executable binary	     */
// #define	MEM_OBJECTS	     1		/* objects currently in free list    */
// #define	MEM_FONTS	     2		/* fonts                             */
// #define	MEM_LEX		     3		/* lexical analyser file buffers     */
// #define	MEM_FILES	     4		/* table of file names               */
// #define	MEM_CROSSREF	     5		/* table of file names               */
// #define	MEM_PAGES	     6		/* page grids (-p only)              */
// #define	MEM_DBCHECK	     7		/* database checks                   */
// #define	MEM_DB	             8		/* in_memory database                */
// #define	MEM_HYPH_PATS	     9		/* hyphenation patterns              */
// #define	MEM_CMAPS	    10		/* character maps                    */
// #define	MEM_COLOUR_TAB	    11		/* colour table                      */
// #define	MEM_TEXTURE_TAB	    12		/* texture table                     */
// #define	MEM_LANG_TAB	    13		/* language table                    */
// #define	MEM_USAGE_MAX	    14		/* number of memory usage types      */

typedef enum mem_t {
    MEM_BINARY_E = 0,
    MEM_OBJECTS_E,
    MEM_FONTS_E,
    MEM_LEX_E,
    MEM_FILES_E,
    MEM_CROSSREF_E,
    MEM_PAGES_E,
    MEM_DBCHECK_E,
    MEM_DB_E,
    MEM_HYPH_PATS_E,
    MEM_CMAPS_E,
    MEM_COLOUR_TAB_E,
    MEM_TEXTURE_TAB_E,
    MEM_LANG_TAB_E
} MEM_T;

#define MEM_USAGE_MAX_E (MEM_LANG_TAB_E + 1)

typedef struct mem_te { MEM_T mem; } MEM_TE;

extern const MEM_TE MEM_BINARY;
extern const MEM_TE MEM_OBJECTS;
extern const MEM_TE MEM_FONTS;
extern const MEM_TE MEM_LEX;
extern const MEM_TE MEM_FILES;
extern const MEM_TE MEM_CROSSREF;
extern const MEM_TE MEM_PAGES;
extern const MEM_TE MEM_DBCHECK;
extern const MEM_TE MEM_DB;
extern const MEM_TE MEM_HYPH_PATS;
extern const MEM_TE MEM_CMAPS;
extern const MEM_TE MEM_COLOUR_TAB;
extern const MEM_TE MEM_TEXTURE_TAB;
extern const MEM_TE MEM_LANG_TAB;

/*@::MAP_VEC@*****************************************************************/
/*                                                                           */
/*  typedef MAP_VEC - information about character mappings.  Really private  */
/*  to z38.c but (for efficiency) shared with z37.c and z24.c                */
/*                                                                           */
/*****************************************************************************/

#define MAX_CHASH       353             /* size of hash table                */
// #define MAP_UPPERCASE     0             /* the map to upper case             */
// #define MAP_LOWERCASE     1             /* the map to lower case             */
// #define MAP_UNACCENTED    2             /* the map to unaccented             */
// #define MAP_ACCENT        3             /* the map to the accent character   */

typedef enum map_t {
    MAP_UPPERCASE_E = 0,
    MAP_LOWERCASE_E,
    MAP_UNACCENTED_E,
    MAP_ACCENT_E,
} MAP_T;

#define MAPS              (MAP_ACCENT_E + 1)             /* the number of maps in each file   */

typedef struct map_te { MAP_T map; } MAP_TE;

extern const MAP_TE MAP_UPPERCASE;
extern const MAP_TE MAP_LOWERCASE;
extern const MAP_TE MAP_UNACCENTED;
extern const MAP_TE MAP_ACCENT;

#endif
