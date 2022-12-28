/*@z26.c:Echo Service:BeginString()@******************************************/
/*                                                                           */
/*  THE LOUT DOCUMENT FORMATTING SYSTEM (VERSION 3.42)                       */
/*  COPYRIGHT (C) 1991, 2008 Jeffrey H. Kingston                             */
/*                                                                           */
/*  Jeffrey H. Kingston (jeff@it.usyd.edu.au)                                */
/*  School of Information Technologies                                       */
/*  The University of Sydney 2006                                            */
/*  AUSTRALIA                                                                */
/*                                                                           */
/*  This program is free software; you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation; either Version 3, or (at your option)      */
/*  any later version.                                                       */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program; if not, write to the Free Software              */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston MA 02111-1307 USA   */
/*                                                                           */
/*  FILE:         z26.c                                                      */
/*  MODULE:       Echo Service                                               */
/*  EXTERNS:      BeginString(), AppendString(), EndString(),                */
/*                EchoLength(), Image()                                      */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"

#if DEBUG_ON
#define	MULTI	  7			/* max no of simultaneous calls      */

static	FULL_CHAR buff[MULTI][2*MAX_BUFF];/* buffers for strings       */
static	int	curr = 1;		/* current buffer in use             */
static	int	bp;			/* next free space in buff[curr]     */
static	BOOLEAN2	instring = FALSE;	/* TRUE while making a string        */


/*****************************************************************************/
/*                                                                           */
/*  BeginString(void)                                                        */
/*                                                                           */
/*  Locate a clear buffer into which debug output may be accumulated.        */
/*                                                                           */
/*****************************************************************************/

void BeginString(void)
{ assert(!instring, "BeginString: currently in string");
  instring = TRUE;  curr = (curr + 1) % MULTI;
  assert( 0 <= curr && curr < MULTI, "BeginString: curr!" );
  StringCopy(buff[curr], "");  bp = 0;
}


/*@::AppendString(), EndString(), EchoLength()@*******************************/
/*                                                                           */
/*  AppendString(str, p1, p2, p3, p4, p5, p6)                                */
/*                                                                           */
/*  Sprintf str to the current buffer, if space is available there.          */
/*                                                                           */
/*****************************************************************************/

void AppendString(const FULL_CHAR *str)
{ int len;
  assert(instring, "AppendString: no current string");
  assert( 0 <= curr && curr < MULTI, "BeginString: curr!" );
  if( bp == MAX_BUFF ) return;		/* no space, do nothing */

  len = StringLength(str);
  if( len + bp >= MAX_BUFF )
  { StringCopy( &buff[curr][MAX_BUFF/2], AsciiToFull(" ... <too long>") );
    bp = MAX_BUFF;
  }
  else
  { StringCopy(&buff[curr][bp], str);
    while( buff[curr][bp] != '\0' )  bp++;
    if( bp >= MAX_BUFF )  Error(26, 1, "AppendString abort", INTERN, no_fpos);
  }
} /* end AppendString */


/*****************************************************************************/
/*                                                                           */
/*  FULL_CHAR *EndString(void)                                               */
/*                                                                           */
/*  Return the string constructed by previous AppendString operations.       */
/*                                                                           */
/*****************************************************************************/

FULL_CHAR *EndString(void)
{ assert(instring, "EndString: no string");
  assert( 0 <= curr && curr < MULTI, "BeginString: curr!" );
  instring = FALSE;
  return buff[curr];
} /* end Endstring */
#endif

/*****************************************************************************/
/*                                                                           */
/*  SetLengthDim(int dim)                                                    */
/*                                                                           */
/*  Set dimension for echoing lengths.                                       */
/*                                                                           */
/*****************************************************************************/

static CR_TE length_dim = {COLM_E} /*COLM*/;

void SetLengthDim(CR_TE dim)
{
  length_dim = dim;
}

/*****************************************************************************/
/*                                                                           */
/*  FULL_CHAR *EchoLength(len)                                               */
/*                                                                           */
/*  Echo a length.                                                           */
/*                                                                           */
/*****************************************************************************/

FULL_CHAR *EchoLength(int len)
{ static FULL_CHAR buff[8][20];
  static int i = 0;
  i = (i + 1) % 8;
  if( len == MAX_FULL_LENGTH )
    sprintf( (char *) buff[i], "%s", "INF");
  else
    BackEnd->PrintLength(buff[i], len, ROWM);
  return buff[i];
} /* end EchoLength */


/*@::Image()@*****************************************************************/
/*                                                                           */
/*  FULL_CHAR *Image(c)                                                      */
/*                                                                           */
/*  Returns the string value of type c.                                      */
/*                                                                           */
/*****************************************************************************/

const FULL_CHAR *Image(OBJTYPE c)
{ static FULL_CHAR b[20];
  switch(c.objtype)
  {

    case LINK_E:			return  AsciiToFull("link");

    case SPLIT_E:			return  AsciiToFull("split");
    case HEAD_E:			return  AsciiToFull("head");
    case PAR_E:			return  AsciiToFull("par");
    case WORD_E:			return  AsciiToFull("word");
    case QWORD_E:			return  AsciiToFull("qword");
    case GAP_OBJ_E:		return  AsciiToFull("gap_obj");
    case ROW_THR_E:		return  AsciiToFull("row_thr");
    case COL_THR_E:		return  AsciiToFull("col_thr");
    case CLOSURE_E:		return  AsciiToFull("closure");
    case NULL_CLOS_E:		return  KW_NULL;
    case PAGE_LABEL_E:		return  KW_PAGE_LABEL;
    case CROSS_E:			return  KW_CROSS;
    case FORCE_CROSS_E:		return  KW_FORCE_CROSS;
    case BEGIN_HEADER_E:		return  KW_BEGIN_HEADER;
    case END_HEADER_E:		return  KW_END_HEADER;
    case SET_HEADER_E:		return  KW_SET_HEADER;
    case CLEAR_HEADER_E:		return  KW_CLEAR_HEADER;
    case ONE_COL_E:		return  KW_ONE_COL;
    case ONE_ROW_E:		return  KW_ONE_ROW;
    case WIDE_E:			return  KW_WIDE;
    case HIGH_E:			return  KW_HIGH;
    case HSHIFT_E:		return  KW_HSHIFT;
    case VSHIFT_E:		return  KW_VSHIFT;
    case HMIRROR_E:		return  KW_HMIRROR;
    case VMIRROR_E:		return  KW_VMIRROR;
    case HSCALE_E:		return  KW_HSCALE;
    case VSCALE_E:		return  KW_VSCALE;
    case HCOVER_E:		return  KW_HCOVER;
    case VCOVER_E:		return  KW_VCOVER;
    case HCONTRACT_E:		return  KW_HCONTRACT;
    case VCONTRACT_E:		return  KW_VCONTRACT;
    case HLIMITED_E:		return  KW_HLIMITED;
    case VLIMITED_E:		return  KW_VLIMITED;
    case HEXPAND_E:		return  KW_HEXPAND;
    case VEXPAND_E:		return  KW_VEXPAND;
    case START_HVSPAN_E:		return  KW_STARTHVSPAN;
    case START_HSPAN_E:		return  KW_STARTHSPAN;
    case START_VSPAN_E:		return  KW_STARTVSPAN;
    case HSPAN_E:			return  KW_HSPAN;
    case VSPAN_E:			return  KW_VSPAN;
    case HSPANNER_E:		return  AsciiToFull("hspannner");
    case VSPANNER_E:		return  AsciiToFull("vspannner");
    case PADJUST_E:		return  KW_PADJUST;
    case HADJUST_E:		return  KW_HADJUST;
    case VADJUST_E:		return  KW_VADJUST;
    case ROTATE_E:		return  KW_ROTATE;
    case BACKGROUND_E:		return	KW_BACKGROUND;
    case SCALE_E:			return  KW_SCALE;
    case KERN_SHRINK_E:		return  KW_KERN_SHRINK;
    case RAW_VERBATIM_E:		return  KW_RAWVERBATIM;
    case VERBATIM_E:		return  KW_VERBATIM;
    case CASE_E:			return  KW_CASE;
    case YIELD_E:			return  KW_YIELD;
    case BACKEND_E:		return  KW_BACKEND;
    case FILTERED_E:		return  AsciiToFull("filtered");
    case XCHAR_E:			return  KW_XCHAR;
    case FONT_E:			return  KW_FONT;
    case SPACE_E:			return  KW_SPACE;
    case YUNIT_E:			return  KW_YUNIT;
    case ZUNIT_E:			return  KW_ZUNIT;
    case SET_CONTEXT_E:		return  KW_SET_CONTEXT;
    case GET_CONTEXT_E:		return  KW_GET_CONTEXT;
    case BREAK_E:			return  KW_BREAK;
    case UNDERLINE_E:		return  KW_UNDERLINE;
    case UNDERLINE_COLOUR_E:	return  KW_UNDERLINE_COLOUR;
    case COLOUR_E:		return  KW_COLOUR;
    case TEXTURE_E:		return  KW_TEXTURE;
    case OUTLINE_E:		return  KW_OUTLINE;
    case LANGUAGE_E:		return  KW_LANGUAGE;
    case CURR_LANG_E:		return  KW_CURR_LANG;
    case CURR_FAMILY_E:		return  KW_CURR_FAMILY;
    case CURR_FACE_E:		return  KW_CURR_FACE;
    case CURR_YUNIT_E:		return  KW_CURR_YUNIT;
    case CURR_ZUNIT_E:		return  KW_CURR_ZUNIT;
    case COMMON_E:		return  KW_COMMON;
    case RUMP_E:			return  KW_RUMP;
    case MELD_E:			return  KW_MELD;
    case INSERT_E:		return  KW_INSERT;
    case ONE_OF_E:		return  KW_ONE_OF;
    case NEXT_E:			return  KW_NEXT;
    case PLUS_E:			return  KW_PLUS;
    case MINUS_E:			return  KW_MINUS;
    case ENV_OBJ_E:		return  AsciiToFull("env_obj");
    case ENV_E:			return  KW_ENV;
    case ENVA_E:			return  KW_ENVA;
    case ENVB_E:			return  KW_ENVB;
    case ENVC_E:			return  KW_ENVC;
    case ENVD_E:			return  KW_ENVD;
    case CENV_E:			return  KW_CENV;
    case CLOS_E:			return  KW_CLOS;
    case LVIS_E:			return  KW_LVIS;
    case LUSE_E:			return  KW_LUSE;
    case LEO_E:			return  KW_LEO;
    case OPEN_E:			return  KW_OPEN;
    case TAGGED_E:		return  KW_TAGGED;
    case INCGRAPHIC_E:		return  KW_INCGRAPHIC;
    case SINCGRAPHIC_E:		return  KW_SINCGRAPHIC;
    case PLAIN_GRAPHIC_E:		return  KW_PLAINGRAPHIC;
    case GRAPHIC_E:		return  KW_GRAPHIC;
    case LINK_SOURCE_E:		return  KW_LINK_SOURCE;
    case LINK_DEST_E:		return  KW_LINK_DEST;
    case LINK_DEST_NULL_E:	return  KW_LINK_DEST;
    case LINK_URL_E:		return  KW_LINK_URL;
    case ACAT_E:			return  AsciiToFull("acat");
    case HCAT_E:			return  AsciiToFull("hcat");
    case VCAT_E:			return  AsciiToFull("vcat");

    case TSPACE_E:		return  AsciiToFull("tspace");
    case TJUXTA_E:		return  AsciiToFull("tjuxta");
    case LBR_E:			return  AsciiToFull("lbr");
    case RBR_E:			return  AsciiToFull("rbr");
    case UNEXPECTED_EOF_E:	return  AsciiToFull("unexpected_eof");
    case BEGIN_E:			return  KW_BEGIN;
    case END_E:			return  KW_END;
    case USE_E:			return  KW_USE;
    case NOT_REVEALED_E:		return  KW_NOT_REVEALED;
    case GSTUB_NONE_E:		return  AsciiToFull("gstub_none");
    case GSTUB_INT_E:		return  AsciiToFull("gstub_int");
    case GSTUB_EXT_E:		return  AsciiToFull("gstub_ext");
    case INCLUDE_E:		return  KW_INCLUDE;
    case SYS_INCLUDE_E:		return  KW_SYSINCLUDE;
    case PREPEND_E:		return  KW_PREPEND;
    case SYS_PREPEND_E:		return  KW_SYSPREPEND;
    case INCG_REPEATED_E:		return  KW_INCG_REPEATED;
    case SINCG_REPEATED_E:	return  KW_SINCG_REPEATED;
    case DATABASE_E:		return  KW_DATABASE;
    case SYS_DATABASE_E:		return  KW_SYSDATABASE;
    /* case START_E: 		return  AsciiToFull("start"); unused */

    case DEAD_E:			return  AsciiToFull("dead");
    case UNATTACHED_E:		return  AsciiToFull("unattached");
    case RECEPTIVE_E:		return  AsciiToFull("receptive");
    case RECEIVING_E:		return  AsciiToFull("receiving");
    case RECURSIVE_E:		return  AsciiToFull("recursive");
    case PRECEDES_E:		return  AsciiToFull("precedes");
    case FOLLOWS_E:		return  AsciiToFull("follows");
    case CROSS_LIT_E:		return  AsciiToFull("cross_lit");
    case CROSS_FOLL_E:		return  AsciiToFull("cross_foll");
    case CROSS_FOLL_OR_PREC_E:	return  AsciiToFull("cross_foll_or_prec");
    case GALL_FOLL_E:		return  AsciiToFull("gall_foll");
    case GALL_FOLL_OR_PREC_E:	return  AsciiToFull("gall_foll_or_prec");
    case CROSS_TARG_E:		return  AsciiToFull("cross_targ");
    case GALL_TARG_E:		return  AsciiToFull("gall_targ");
    case GALL_PREC_E:		return  AsciiToFull("gall_prec");
    case CROSS_PREC_E:		return  AsciiToFull("cross_prec");
    case PAGE_LABEL_IND_E:	return  AsciiToFull("page_label_ind");
    case SCALE_IND_E:		return  AsciiToFull("scale_ind");
    case COVER_IND_E:		return  AsciiToFull("cover_ind");
    case EXPAND_IND_E:		return  AsciiToFull("expand_ind");
    case THREAD_E:		return  AsciiToFull("thread");
    case CROSS_SYM_E:		return  AsciiToFull("cross_sym");
    case CR_ROOT_E:		return  AsciiToFull("cr_root");
    case MACRO_E:			return  KW_MACRO;
    case LOCAL_E:			return  AsciiToFull("local");
    case LPAR_E:			return  AsciiToFull("lpar");
    case NPAR_E:			return  AsciiToFull("npar");
    case RPAR_E:			return  AsciiToFull("rpar");
    case CR_LIST_E:		return  AsciiToFull("cr_list");
    case EXT_GALL_E:		return  AsciiToFull("ext_gall");
    case DISPOSED_E:		return  AsciiToFull("disposed");

/*
    case BACK_E:			return  AsciiToFull("back");
    case ON_E:			return  AsciiToFull("on");
    case FWD_E:			return  AsciiToFull("fwd");

    case PROMOTE_E:		return  AsciiToFull("promote");
    case CLOSE_E:			return  AsciiToFull("close");
    case BLOCK_E:			return  AsciiToFull("block");
    case CLEAR_E:			return  AsciiToFull("clear");

    case GAP_ABS_E:		return  AsciiToFull("abs");
    case GAP_INC_E:		return  AsciiToFull("inc");
    case GAP_DEC_E:		return  AsciiToFull("dec");
*/

    default:			sprintf( (char *) b, "?? (%d)", c.objtype);
				return b;
  } /* end switch */
} /* end Image */

const FULL_CHAR *Image4Constraints(int c)
{ static FULL_CHAR b[20];
  switch(c)
  {
    case BACK:			return  AsciiToFull("back");
    case ON:			return  AsciiToFull("on");
    case FWD:			return  AsciiToFull("fwd");

    case PROMOTE:		return  AsciiToFull("promote");
    case CLOSE:			return  AsciiToFull("close");
    case BLOCK:			return  AsciiToFull("block");
    case CLEAR:			return  AsciiToFull("clear");

    case GAP_ABS:		return  AsciiToFull("abs");
    case GAP_INC:		return  AsciiToFull("inc");
    case GAP_DEC:		return  AsciiToFull("dec");

    default:			sprintf( (char *) b, "?? (%d)", c);
				return b;
  } /* end switch */
} /* end Image4Constraints */
