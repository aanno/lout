
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
typedef enum space_mode {
    NO_MODE = 0,    /* for error detection: no mode      */
    EDGE_MODE,      /* edge-to-edge spacing              */
    HYPH_MODE,      /* edge-to-edge with hyphenation     */
    MARK_MODE,      /* mark-to-mark spacing              */
    OVER_MODE,      /* overstrike spacing                */
    KERN_MODE,      /* kerning spacing                   */
    TAB_MODE,       /* tabulation spacing                */
    ADD_HYPH        /* 7  temp value used by FillObject     */
} SPACE_MODE;

#endif
