
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

typedef enum objtyp {
    LINK = 0,       /*        a link between objects      0 */
    GAP_OBJ,        /*  o     a gap object               */
    CLOSURE,        /* to  n  a closure of a symbol      */
    UNDER_REC,      /*  o  n  record of underlining      */
    PAGE_LABEL,     /* to sn  @PageLabel                 */
    NULL_CLOS,      /* to sn  @Null                      */
    CROSS,          /* to sn  && (a cross reference obj) */
    FORCE_CROSS,    /* to sn  &&& (a forcing cross ref.) */
    LINK_DEST_NULL, /* to sn  @LinkDest (null version)   */
    HEAD,           /*  o  n  a galley header            */
    SPLIT,          /*  o     @Split                     10 */
    PAR,            /*  o     a parameter of a closure   */
    WORD,           /*  o     a word                     */
    QWORD,          /*  o     a word (was quoted in i/p) */
    HSPANNER,       /*  o     a horizontal spanner       */
    VSPANNER,       /*  o     a vertical spanner         */
    ROW_THR,        /*  o     a row thread               */
    COL_THR,        /*  o     a column thread            */
    ACAT,           /* to s   a sequence of &-ed objs    */
    HCAT,           /* to s   a sequence of |-ed objs    */
    VCAT,           /* to s   a sequence of /-ed objs    20 */
    BEGIN_HEADER,   /* to s   @BeginHeaderComponent      */
    END_HEADER,     /* to s   @EndHeaderComponent        */
    SET_HEADER,     /* to s   @SetHeaderComponent        */
    CLEAR_HEADER,   /* to s   @ClearHeaderComponent      */
    ONE_COL,        /* to s   @OneCol                    */
    ONE_ROW,        /* to s   @OneRow                    */
    WIDE,           /* to s   @Wide                      */
    HIGH,           /* to s   @High                      */
    HSHIFT,         /* to s   @HShift                    */
    VSHIFT,         /* to s   @VShift                    30 */
    HMIRROR,        /* to s   @HScale                    */
    VMIRROR,        /* to s   @VScale                    */
    HSCALE,         /* to s   @HScale                    */
    VSCALE,         /* to s   @VScale                    */
    HCOVER,         /* to s   @HCover                    */
    VCOVER,         /* to s   @VCover                    */
    SCALE,          /* to s   @Scale                     */
    KERN_SHRINK,    /* to s   @KernShrink                */
    HCONTRACT,      /* to s   @HContract                 */
    VCONTRACT,      /* to s   @VContract                 40 */
    HLIMITED,       /* to s   @HLimited                  */
    VLIMITED,       /* to s   @VLimited                  */
    HEXPAND,        /* to s   @HExpand                   */
    VEXPAND,        /* to s   @VExpand                   */
    START_HSPAN,    /* to s   @StartHSpan                */
    START_VSPAN,    /* to s   @StartVSpan                */
    START_HVSPAN,   /* to s   @StartHVSpan               */
    HSPAN,          /* to s   @HSpan                     */
    VSPAN,          /* to s   @VSpan                     */
    PADJUST,        /* to s   @PAdjust                   50 */
    HADJUST,        /* to s   @HAdjust                   */
    VADJUST,        /* to s   @VAdjust                   */
    ROTATE,         /* to s   @Rotate                    */
    BACKGROUND,     /* to s   @Background                */
    CASE,           /* to s   @Case                      */
    VERBATIM,       /* to s   @Verbatim                  */
    RAW_VERBATIM,   /* to s   @RawVerbatim               */
    YIELD,          /* to s   @Yield                     */
    BACKEND,        /* to s   @BackEnd                   */
    FILTERED,       /* to s   filtered object (no name)  60 */
    XCHAR,          /* to s   @Char                      */
    FONT,           /* to s   @Font                      */
    SPACE,          /* to s   @Space                     */
    YUNIT,          /* to s   @YUnit                     */
    ZUNIT,          /* to s   @ZUnit                     */
    SET_CONTEXT,    /* to s   @SetContext                */
    GET_CONTEXT,    /* to s   @GetContext                */
    BREAK,          /* to s   @Break                     */
    UNDERLINE,      /* to s   @Underline                 */
    UNDERLINE_COLOUR, /* to s   @SetUnderlineColour      70   */
    COLOUR,         /* to s   @SetColour and @SetColor   */
    TEXTURE,        /* to s   @SetTexture                */
    OUTLINE,        /* to s   @Outline                   */
    LANGUAGE,       /* to s   @Language                  */
    CURR_LANG,      /* to s   @CurrLang                  */
    CURR_FAMILY,    /* to s   @CurrFamily                */
    CURR_FACE,      /* to s   @CurrFace                  */
    CURR_YUNIT,     /* to s   @CurrYUnit                 */
    CURR_ZUNIT,     /* to s   @CurrZUnit                 */
    COMMON,         /* to s   @Common                    80 */
    RUMP,           /* to s   @Rump                      */
    MELD,           /* to s   @Meld                      */
    INSERT,         /* to s   @Insert                    */
    ONE_OF,         /* to s   @OneOf                     */
    NEXT,           /* to s   @Next                      */
    PLUS,           /* to s   @Plus                      */
    MINUS,          /* to s   @Minus                     */
    ENV_OBJ,        /* to s   object with envt (no name) */
    ENV,            /* to s   @LEnv                      */
    ENVA,           /* to s   @LEnvA                     90 */
    ENVB,           /* to s   @LEnvB                     */
    ENVC,           /* to s   @LEnvC                     */
    ENVD,           /* to s   @LEnvD                     */
    CENV,           /* to s   @LCEnv                     */
    CLOS,           /* to s   @LClos                     */
    LVIS,           /* to s   @LVis                      */
    LUSE,           /* to s   @LUse                      */
    LEO,            /* to s   @LEO                       */
    OPEN,           /* to s   @Open                      */
    TAGGED,         /* to s   @Tagged                   100 */
    INCGRAPHIC,     /* to s   @IncludeGraphic            */
    SINCGRAPHIC,    /* to s   @SysIncludeGraphic         */
    PLAIN_GRAPHIC,  /* to s   @PlainGraphic              */
    GRAPHIC,        /* to s   @Graphic                   */
    LINK_SOURCE,    /* to s   @LinkSource                */
    LINK_DEST,      /* to s   @LinkDest                  */
    LINK_URL,       /* to s   @URLLink                   */
    TSPACE,         /* t      a space token, parser only */
    TJUXTA,         /* t      a juxta token, parser only */
    LBR,            /* t  s   left brace token          110 */
    RBR,            /* t  s   right brace token          */
    BEGIN,          /* t  s   @Begin token               */
    END,            /* t  s   @End token                 */
    USE,            /* t  s   @Use                       */
    NOT_REVEALED,   /* t  s   @NotRevealed               */
    GSTUB_NONE,     /* t      a galley stub, no rpar     */
    GSTUB_INT,      /* t      galley stub internal rpar  */
    GSTUB_EXT,      /* t      galley stub external rpar  */
    UNEXPECTED_EOF, /* t      unexpected end of file     */
    INCLUDE,        /*    s   @Include                  120 */
    SYS_INCLUDE,    /*    s   @SysInclude                */
    PREPEND,        /*    s   @Prepend                   */
    SYS_PREPEND,    /*    s   @SysPrepend                */
    INCG_REPEATED,  /*    s   @IncludeGraphicRepeated    */
    SINCG_REPEATED, /*    s   @SysIncludeGraphicRepeated */
    DATABASE,       /*    s   @Database                  */
    SYS_DATABASE,   /*    s   @SysDatabase               */
    DEAD,           /*   i    a dead galley              */
    UNATTACHED,     /*   i    an inner, unsized galley   */
    RECEPTIVE,      /*   i    a receptive object index  130 */
    RECEIVING,      /*   i    a receiving object index   */
    RECURSIVE,      /*   i    a recursive definite obj.  */
    PRECEDES,       /*   i    an ordering constraint     */
    FOLLOWS,        /*   i    other end of ordering c.   */
    CROSS_LIT,      /*   i    literal word cross-ref     */
    CROSS_FOLL,     /*   i    following type cross-ref   */
    CROSS_FOLL_OR_PREC, /*   i    follorprec type cross-ref  */
    GALL_FOLL,      /*   i    galley with &&following    */
    GALL_FOLL_OR_PREC,  /*   i    galley with &&following    */
    CROSS_TARG,     /*   i    value of cross-ref        140 */
    GALL_TARG,      /*   i    target of these galleys    */
    GALL_PREC,      /*   i    galley with &&preceding    */
    CROSS_PREC,     /*   i    preceding type cross-ref   */
    PAGE_LABEL_IND, /*   i    index of PAGE_LABEL        */
    SCALE_IND,      /*   i    index of auto SCALE        */
    COVER_IND,      /*   i    index of HCOVER or VCOVER  */
    EXPAND_IND,     /*   i    index of HEXPAND or VEXPD  */
    THREAD,         /*        a sequence of threads      */
    CROSS_SYM,      /*        cross-ref info             */
    CR_ROOT,        /*        RootCross                 150 */
    MACRO,          /*        a macro symbol             */
    LOCAL,          /*        a local symbol             */
    LPAR,           /*        a left parameter           */
    NPAR,           /*        a named parameter          */
    RPAR,           /*        a right parameter          */
    EXT_GALL,       /*        an external galley         */
    CR_LIST,        /*        a list of cross references */
    SCOPE_SNAPSHOT, /*        a scope snapshot	     */
    DISPOSED,       /* 159        a disposed record     159     */
} OBJTYPE;

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
