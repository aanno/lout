/*@z04.c:Token Service:NewToken(), CopyTokenList()@***************************/
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
/*  FILE:         z04.c                                                      */
/*  MODULE:       Token Service                                              */
/*  EXTERNS:      NewToken(), CopyTokenList(), EchoCatOp(), EchoToken()      */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"


/*****************************************************************************/
/*                                                                           */
/*  OBJECT NewToken(xtype, xfpos, xvspace, xhspace, xprec, xactual)          */
/*                                                                           */
/*  Returns a new non-WORD token initialised as the parameters indicate.     */
/*                                                                           */
/*****************************************************************************/

OBJECT NewToken(OBJTYPE xtype, FILE_POS *xfpos, unsigned char xvspace,
unsigned char xhspace, unsigned char xprec, OBJECT xactual)
{ OBJECT res;
  debug1(DTS, DDD, "NewToken(%s, ...)", Image(xtype));
  New(res, xtype);  FposCopy(fpos(res), *xfpos);
  vspace(res) = xvspace;  hspace(res) = xhspace;
  precedence(res) = xprec;  actual(res) = xactual;
  debug1(DTS, DDD, "NewToken returning %s", EchoToken(res));
  return res;
} /* end NewToken */


/*****************************************************************************/
/*                                                                           */
/*  OBJECT CopyTokenList(x, pos)                                             */
/*                                                                           */
/*  Returns a copy of the list of tokens pointed to by x.                    */
/*  All file positions in the copy are set to *pos.                          */
/*                                                                           */
/*****************************************************************************/

OBJECT CopyTokenList(OBJECT x, FILE_POS *pos)
{ OBJECT y, z, res;
  res = nilobj;  y = x;
  if( x != nilobj ) do
  { if( is_word(type(y)) )
    { z = MakeWord(type(y), string(y), pos);
      vspace(z) = vspace(y);  hspace(z) = hspace(y);
    }
    else z = NewToken(type(y), pos,vspace(y),hspace(y),precedence(y),actual(y));
    res = Append(res, z, PARENT);
    y = succ(y, PARENT);
  } while( y != x );
  return res;
} /* end CopyTokenList */

/*@::EchoCatOp(), EchoToken()@************************************************/
/*                                                                           */
/*  FULL_CHAR *EchoCatOp(xtype, xmark, xjoin)                                */
/*                                                                           */
/*  Return the catenation operator with this type, mark and join.            */
/*                                                                           */
/*****************************************************************************/

// deprecated
const FULL_CHAR *EchoCatOpUnsafe(unsigned xtype, BOOLEAN xmark, BOOLEAN xjoin)
{ switch( xtype )
  {
    case VCAT_E:	return	(xmark ? xjoin ? KW_VCAT_MJ : KW_VCAT_MN
			       : xjoin ? KW_VCAT_NJ : KW_VCAT_NN);

    case HCAT_E:	return	(xmark ? xjoin ? KW_HCAT_MJ : KW_HCAT_MN
			       : xjoin ? KW_HCAT_NJ : KW_HCAT_NN);

    case ACAT_E:	return	(xmark ? xjoin ? KW_ACAT_MJ : AsciiToFull("??")
			       : xjoin ? KW_ACAT_NJ : AsciiToFull("??") );

    default:	assert(FALSE, "EchoCatOp");
		return STR_EMPTY;

  } /* end switch */
} /* end EchoCatOp */

const FULL_CHAR *EchoCatOp(OBJTYPE xtype, BOOLEAN xmark, BOOLEAN xjoin)
{ 
  return EchoCatOpUnsafe(xtype.objtype, xmark, xjoin);
} /* end EchoCatOp */


#if DEBUG_ON
/*****************************************************************************/
/*                                                                           */
/*  FULL_CHAR *EchoToken(x)                                                  */
/*                                                                           */
/*  Return an image of token x.  Do not worry about preceding space.         */
/*                                                                           */
/*****************************************************************************/

const FULL_CHAR *EchoToken(OBJECT x)
{ switch( type(x).objtype )
  {
    case WORD_E:
    
      return string(x);


    case QWORD_E:
    
      return StringQuotedWord(x);


    case TSPACE_E:
    case TJUXTA_E:
    case USE_E:
    case NOT_REVEALED_E:
    case GSTUB_EXT_E:
    case GSTUB_INT_E:
    case GSTUB_NONE_E:
    
      return Image(type(x));


    case UNEXPECTED_EOF_E:
    case BEGIN_E:
    case END_E:
    case ENV_E:
    case ENVA_E:
    case ENVB_E:
    case ENVC_E:
    case ENVD_E:
    case CENV_E:
    case CLOS_E:
    case LBR_E:
    case RBR_E:
    case NULL_CLOS_E:
    case PAGE_LABEL_E:
    case CROSS_E:
    case FORCE_CROSS_E:
    case BEGIN_HEADER_E:
    case END_HEADER_E:
    case SET_HEADER_E:
    case CLEAR_HEADER_E:
    case ONE_COL_E:
    case ONE_ROW_E:
    case WIDE_E:
    case HIGH_E:
    case HSHIFT_E:
    case VSHIFT_E:
    case HMIRROR_E:
    case VMIRROR_E:
    case HSCALE_E:
    case VSCALE_E:
    case HCOVER_E:
    case VCOVER_E:
    case SCALE_E:
    case KERN_SHRINK_E:
    case HCONTRACT_E:
    case VCONTRACT_E:
    case HLIMITED_E:
    case VLIMITED_E:
    case HEXPAND_E:
    case VEXPAND_E:
    case START_HVSPAN_E:
    case START_HSPAN_E:
    case START_VSPAN_E:
    case HSPAN_E:
    case VSPAN_E:
    case PADJUST_E:
    case HADJUST_E:
    case VADJUST_E:
    case ROTATE_E:
    case BACKGROUND_E:
    case VERBATIM_E:
    case RAW_VERBATIM_E:
    case CASE_E:
    case YIELD_E:
    case BACKEND_E:
    case XCHAR_E:
    case FONT_E:
    case SPACE_E:
    case YUNIT_E:
    case ZUNIT_E:
    case SET_CONTEXT_E:
    case GET_CONTEXT_E:
    case BREAK_E:
    case UNDERLINE_E:
    case UNDERLINE_COLOUR_E:
    case COLOUR_E:
    case TEXTURE_E:
    case OUTLINE_E:
    case LANGUAGE_E:
    case CURR_LANG_E:
    case CURR_FAMILY_E:
    case CURR_FACE_E:
    case CURR_YUNIT_E:
    case CURR_ZUNIT_E:
    case COMMON_E:
    case RUMP_E:
    case MELD_E:
    case INSERT_E:
    case ONE_OF_E:
    case NEXT_E:
    case PLUS_E:
    case MINUS_E:
    case OPEN_E:
    case TAGGED_E:
    case INCGRAPHIC_E:
    case SINCGRAPHIC_E:
    case PLAIN_GRAPHIC_E:
    case GRAPHIC_E:
    case LINK_SOURCE_E:
    case LINK_DEST_E:
    case LINK_DEST_NULL_E:
    case LINK_URL_E:
    case ACAT_E:
    case HCAT_E:
    case VCAT_E:
    case CLOSURE_E:
    case PREPEND_E:
    case SYS_PREPEND_E:
    case INCG_REPEATED_E:
    case SINCG_REPEATED_E:
    case DATABASE_E:
    case SYS_DATABASE_E:
    case LUSE_E:
    case LEO_E:
    case LVIS_E:
    
      return actual(x) != nilobj ? SymName(actual(x)) : Image(type(x));


    default:
    
      assert1(FALSE, "EchoToken:", Image(type(x)));
      return STR_EMPTY;
  }
} /* end EchoToken */
#endif
