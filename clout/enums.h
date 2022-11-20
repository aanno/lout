
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
    PRECEDES_E,       /*   i    an ordering constraint     */
    FOLLOWS_E,        /*   i    other end of ordering c.   */
    CROSS_LIT_E,      /*   i    literal word cross-ref     */
    CROSS_FOLL_E,     /*   i    following type cross-ref   */
    CROSS_FOLL_OR_PREC_E, /*   i    follorprec type cross-ref  */
    GALL_FOLL_E,      /*   i    galley with &&following    */
    GALL_FOLL_OR_PREC_E,  /*   i    galley with &&following    */
    CROSS_EARG_E,     /*   i    value of cross-ref        140 */
    GALL_EARG_E,      /*   i    target of these galleys    */
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
#define DUMMY ((OBJTYPE) {LINK_E})
#define DUMMY_E LINK_E

#define LINK ((OBJTYPE) {LINK_E})
#define GAP_OBJ ((OBJTYPE) {GAP_OBJ_E})
#define CLOSURE ((OBJTYPE) {CLOSURE_E})
#define UNDER_REC ((OBJTYPE) {UNDER_REC_E})
#define PAGE_LABEL ((OBJTYPE) {PAGE_LABEL_E})
#define NULL_CLOS ((OBJTYPE) {NULL_CLOS_E})
#define CROSS ((OBJTYPE) {CROSS_E})
#define FORCE_CROSS ((OBJTYPE) {FORCE_CROSS_E})
#define LINK_DEST_NULL ((OBJTYPE) {LINK_DEST_NULL_E})
#define HEAD ((OBJTYPE) {HEAD_E})
#define SPLIT ((OBJTYPE) {SPLIT_E})
#define PAR ((OBJTYPE) {PAR_E})
#define WORD ((OBJTYPE) {WORD_E})
#define QWORD ((OBJTYPE) {QWORD_E})
#define HSPANNER ((OBJTYPE) {HSPANNER_E})
#define VSPANNER ((OBJTYPE) {VSPANNER_E})
#define ROW_THR ((OBJTYPE) {ROW_THR_E})
#define COL_THR ((OBJTYPE) {COL_THR_E})
#define ACAT ((OBJTYPE) {ACAT_E})
#define HCAT ((OBJTYPE) {HCAT_E})
#define VCAT ((OBJTYPE) {VCAT_E})
#define BEGIN_HEADER ((OBJTYPE) {BEGIN_HEADER_E})
#define END_HEADER ((OBJTYPE) {END_HEADER_E})
#define SET_HEADER ((OBJTYPE) {SET_HEADER_E})
#define CLEAR_HEADER ((OBJTYPE) {CLEAR_HEADER_E})
#define ONE_COL ((OBJTYPE) {ONE_COL_E})
#define ONE_ROW ((OBJTYPE) {ONE_ROW_E})
#define WIDE ((OBJTYPE) {WIDE_E})
#define HIGH ((OBJTYPE) {HIGH_E})
#define HSHIFT ((OBJTYPE) {HSHIFT_E})
#define VSHIFT ((OBJTYPE) {VSHIFT_E})
#define HMIRROR ((OBJTYPE) {HMIRROR_E})
#define VMIRROR ((OBJTYPE) {VMIRROR_E})
#define HSCALE ((OBJTYPE) {HSCALE_E})
#define VSCALE ((OBJTYPE) {VSCALE_E})
#define HCOVER ((OBJTYPE) {HCOVER_E})
#define VCOVER ((OBJTYPE) {VCOVER_E})
#define SCALE ((OBJTYPE) {SCALE_E})
#define KERN_SHRINK ((OBJTYPE) {KERN_SHRINK_E})
#define HCONTRACT ((OBJTYPE) {HCONTRACT_E})
#define VCONTRACT ((OBJTYPE) {VCONTRACT_E})
#define HLIMITED ((OBJTYPE) {HLIMITED_E})
#define VLIMITED ((OBJTYPE) {VLIMITED_E})
#define HEXPAND ((OBJTYPE) {HEXPAND_E})
#define VEXPAND ((OBJTYPE) {VEXPAND_E})
#define START_HSPAN ((OBJTYPE) {START_HSPAN_E})
#define START_VSPAN ((OBJTYPE) {START_VSPAN_E})
#define START_HVSPAN ((OBJTYPE) {START_HVSPAN_E})
#define HSPAN ((OBJTYPE) {HSPAN_E})
#define VSPAN ((OBJTYPE) {VSPAN_E})
#define PADJUST ((OBJTYPE) {PADJUST_E})
#define HADJUST ((OBJTYPE) {HADJUST_E})
#define VADJUST ((OBJTYPE) {VADJUST_E})
#define ROTATE ((OBJTYPE) {ROTATE_E})
#define BACKGROUND ((OBJTYPE) {BACKGROUND_E})
#define CASE ((OBJTYPE) {CASE_E})
#define VERBATIM ((OBJTYPE) {VERBATIM_E})
#define RAW_VERBATIM ((OBJTYPE) {RAW_VERBATIM_E})
#define YIELD ((OBJTYPE) {YIELD_E})
#define BACKEND ((OBJTYPE) {BACKEND_E})
#define FILTERED ((OBJTYPE) {FILTERED_E})
#define XCHAR ((OBJTYPE) {XCHAR_E})
#define FONT ((OBJTYPE) {FONT_E})
#define SPACE ((OBJTYPE) {SPACE_E})
#define YUNIT ((OBJTYPE) {YUNIT_E})
#define ZUNIT ((OBJTYPE) {ZUNIT_E})
#define SET_CONTEXT ((OBJTYPE) {SET_CONTEXT_E})
#define GET_CONTEXT ((OBJTYPE) {GET_CONTEXT_E})
#define BREAK ((OBJTYPE) {BREAK_E})
#define UNDERLINE ((OBJTYPE) {UNDERLINE_E})
#define UNDERLINE_COLOUR ((OBJTYPE) {UNDERLINE_COLOUR_E})
#define COLOUR ((OBJTYPE) {COLOUR_E})
#define TEXTURE ((OBJTYPE) {TEXTURE_E})
#define OUTLINE ((OBJTYPE) {OUTLINE_E})
#define LANGUAGE ((OBJTYPE) {LANGUAGE_E})
#define CURR_LANG ((OBJTYPE) {CURR_LANG_E})
#define CURR_FAMILY ((OBJTYPE) {CURR_FAMILY_E})
#define CURR_FACE ((OBJTYPE) {CURR_FACE_E})
#define CURR_YUNIT ((OBJTYPE) {CURR_YUNIT_E})
#define CURR_ZUNIT ((OBJTYPE) {CURR_ZUNIT_E})
#define COMMON ((OBJTYPE) {COMMON_E})
#define RUMP ((OBJTYPE) {RUMP_E})
#define MELD ((OBJTYPE) {MELD_E})
#define INSERT ((OBJTYPE) {INSERT_E})
#define ONE_OF ((OBJTYPE) {ONE_OF_E})
#define NEXT ((OBJTYPE) {NEXT_E})
#define PLUS ((OBJTYPE) {PLUS_E})
#define MINUS ((OBJTYPE) {MINUS_E})
#define ENV_OBJ ((OBJTYPE) {ENV_OBJ_E})
#define ENV ((OBJTYPE) {ENV_E})
#define ENVA ((OBJTYPE) {ENVA_E})
#define ENVB ((OBJTYPE) {ENVB_E})
#define ENVC ((OBJTYPE) {ENVC_E})
#define ENVD ((OBJTYPE) {ENVD_E})
#define CENV ((OBJTYPE) {CENV_E})
#define CLOS ((OBJTYPE) {CLOS_E})
#define LVIS ((OBJTYPE) {LVIS_E})
#define LUSE ((OBJTYPE) {LUSE_E})
#define LEO ((OBJTYPE) {LEO_E})
#define OPEN ((OBJTYPE) {OPEN_E})
#define TAGGED ((OBJTYPE) {TAGGED_E})
#define INCGRAPHIC ((OBJTYPE) {INCGRAPHIC_E})
#define SINCGRAPHIC ((OBJTYPE) {SINCGRAPHIC_E})
#define PLAIN_GRAPHIC ((OBJTYPE) {PLAIN_GRAPHIC_E})
#define GRAPHIC ((OBJTYPE) {GRAPHIC_E})
#define LINK_SOURCE ((OBJTYPE) {LINK_SOURCE_E})
#define LINK_DEST ((OBJTYPE) {LINK_DEST_E})
#define LINK_URL ((OBJTYPE) {LINK_URL_E})
#define TSPACE ((OBJTYPE) {TSPACE_E})
#define TJUXTA ((OBJTYPE) {TJUXTA_E})
#define LBR ((OBJTYPE) {LBR_E})
#define RBR ((OBJTYPE) {RBR_E})
#define BEGIN ((OBJTYPE) {BEGIN_E})
#define END ((OBJTYPE) {END_E})
#define USE ((OBJTYPE) {USE_E})
#define NOT_REVEALED ((OBJTYPE) {NOT_REVEALED_E})
#define GSTUB_NONE ((OBJTYPE) {GSTUB_NONE_E})
#define GSTUB_INT ((OBJTYPE) {GSTUB_INT_E})
#define GSTUB_EXT ((OBJTYPE) {GSTUB_EXT_E})
#define UNEXPECTED_EOF ((OBJTYPE) {UNEXPECTED_EOF_E})
#define INCLUDE ((OBJTYPE) {INCLUDE_E})
#define SYS_INCLUDE ((OBJTYPE) {SYS_INCLUDE_E})
#define PREPEND ((OBJTYPE) {PREPEND_E})
#define SYS_PREPEND ((OBJTYPE) {SYS_PREPEND_E})
#define INCG_REPEATED ((OBJTYPE) {INCG_REPEATED_E})
#define SINCG_REPEATED ((OBJTYPE) {SINCG_REPEATED_E})
#define DATABASE ((OBJTYPE) {DATABASE_E})
#define SYS_DATABASE ((OBJTYPE) {SYS_DATABASE_E})
#define DEAD ((OBJTYPE) {DEAD_E})
#define UNATTACHED ((OBJTYPE) {UNATTACHED_E})
#define RECEPTIVE ((OBJTYPE) {RECEPTIVE_E})
#define RECEIVING ((OBJTYPE) {RECEIVING_E})
#define RECURSIVE ((OBJTYPE) {RECURSIVE_E})
#define PRECEDES ((OBJTYPE) {PRECEDES_E})
#define FOLLOWS ((OBJTYPE) {FOLLOWS_E})
#define CROSS_LIT ((OBJTYPE) {CROSS_LIT_E})
#define CROSS_FOLL ((OBJTYPE) {CROSS_FOLL_E})
#define CROSS_FOLL_OR_PREC ((OBJTYPE) {CROSS_FOLL_OR_PREC_E})
#define GALL_FOLL ((OBJTYPE) {GALL_FOLL_E})
#define GALL_FOLL_OR_PREC ((OBJTYPE) {GALL_FOLL_OR_PREC_E})
#define CROSSARG ((OBJTYPE) {CROSSARG_E})
#define GALLARG ((OBJTYPE) {GALLARG_E})
#define GALL_PREC ((OBJTYPE) {GALL_PREC_E})
#define CROSS_PREC ((OBJTYPE) {CROSS_PREC_E})
#define PAGE_LABEL_IND ((OBJTYPE) {PAGE_LABEL_IND_E})
#define SCALE_IND ((OBJTYPE) {SCALE_IND_E})
#define COVER_IND ((OBJTYPE) {COVER_IND_E})
#define EXPAND_IND ((OBJTYPE) {EXPAND_IND_E})
#define THREAD ((OBJTYPE) {THREAD_E})
#define CROSS_SYM ((OBJTYPE) {CROSS_SYM_E})
#define CR_ROOT ((OBJTYPE) {CR_ROOT_E})
#define MACRO ((OBJTYPE) {MACRO_E})
#define LOCAL ((OBJTYPE) {LOCAL_E})
#define LPAR ((OBJTYPE) {LPAR_E})
#define NPAR ((OBJTYPE) {NPAR_E})
#define RPAR ((OBJTYPE) {RPAR_E})
#define EXT_GALL ((OBJTYPE) {EXT_GALL_E})
#define CR_LIST ((OBJTYPE) {CR_LIST_E})
#define SCOPE_SNAPSHOT ((OBJTYPE) {SCOPE_SNAPSHOT_E})
#define DISPOSED ((OBJTYPE) {DISPOSED_E})

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
