/*@z32.c:Counter Service:Next()@**********************************************/
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
/*  FILE:         z32.c                                                      */
/*  MODULE:       Counter Service                                            */
/*  EXTERNS:      Next()                                                     */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"

/*****************************************************************************/
/*                                                                           */
/*  OBJECT Next(x, inc, done)                                                */
/*                                                                           */
/*  Return x with its value incremented by inc (if possible).                */
/*  Set *done to TRUE if successful, leave *done unchanged otherwise.        */
/*                                                                           */
/*****************************************************************************/

OBJECT Next(OBJECT x, int inc, BOOLEAN *done)
{ OBJECT y, link;  int l, r, n, len;
  FULL_CHAR buff[MAX_BUFF];
  debug3(DCS, DD, "Next( %s, %d, %s )", EchoObject(x), inc, bool(*done));
  switch( type(x).objtype )
  {
    case WORD_E:
    case QWORD_E:
    
      len = StringLength(string(x));
      for( r = len - 1;  r >= 0 && !decimaldigit(string(x)[r]);  r--);
      if( r < 0 ) break;
      for( l = r-1;  l >= 0 && decimaldigit(string(x)[l]);  l-- );
      sscanf( (char *) &string(x)[l+1], "%d", &n);
      string(x)[l+1] = '\0';
      StringCopy(buff, string(x));
      StringCat(buff, StringInt(n+inc));
      StringCat(buff, &string(x)[r+1]);
      if( StringLength(buff) >= MAX_BUFF )
	Error(32, 1, "word %s is too long", FATAL, &fpos(x), buff);
      y = MakeWord(type(x), buff, &fpos(x));
      word_font(y) = word_font(x);
      word_colour(y) = word_colour(x);
      word_underline_colour(y) = word_underline_colour(x);
      word_texture(y) = word_texture(x);
      word_outline(y) = word_outline(x);
      word_language(y) = word_language(x);
      word_baselinemark(y) = word_baselinemark(x);
      word_ligatures(y) = word_ligatures(x);
      word_hyph(y) = word_hyph(x);
      underline(y) = underline(x);
      MergeNode(y, x);  x = y;
      *done = TRUE;
      break;


    case INCGRAPHIC_E:
    case SINCGRAPHIC_E:
    case GAP_OBJ_E:
    case CLOSURE_E:
    case NULL_CLOS_E:
    case PAGE_LABEL_E:
    case CROSS_E:
    case FORCE_CROSS_E:
    case START_HVSPAN_E:
    case START_HSPAN_E:
    case START_VSPAN_E:
    case HSPAN_E:
    case VSPAN_E:
    case END_HEADER_E:
    case CLEAR_HEADER_E:
    
      break;


    case BEGIN_HEADER_E:
    case SET_HEADER_E:
    case ONE_COL_E:
    case ONE_ROW_E:
    case WIDE_E:
    case HIGH_E:
    case HSHIFT_E:
    case VSHIFT_E:
    case HCONTRACT_E:
    case VCONTRACT_E:
    case HLIMITED_E:
    case VLIMITED_E:
    case HEXPAND_E:
    case VEXPAND_E:
    case PADJUST_E:
    case HADJUST_E:
    case VADJUST_E:
    case HMIRROR_E:
    case VMIRROR_E:
    case HSCALE_E:
    case VSCALE_E:
    case HCOVER_E:
    case VCOVER_E:
    case ROTATE_E:
    case BACKGROUND_E:
    case SCALE_E:
    case KERN_SHRINK_E:
    case SPLIT_E:
    case PLAIN_GRAPHIC_E:
    case GRAPHIC_E:
    case LINK_SOURCE_E:
    case LINK_DEST_E:
    case LINK_DEST_NULL_E:
    case LINK_URL_E:
    case SET_CONTEXT_E:
    case GET_CONTEXT_E:
    
      Child(y, LastDown(x));
      y = Next(y, inc, done);
      break;


    case ACAT_E:
    
      /* *** seems identical!
      link = LastDown(x);
      while( link != x && !*done )
      {	Child(y, link);
	if( is_index(type(y)) )  continue;
	y = Next(y, inc, done);
	if( !*done )  link = PrevDown(link);
      }
      break;
      *** */


    case COL_THR_E:
    case ROW_THR_E:
    case HCAT_E:
    case VCAT_E:
    
      link = LastDown(x);
      while( link != x && !*done )
      {	Child(y, link);
	if( is_index(type(y)) )  continue;
	y = Next(y, inc, done);
	if( !*done )  link = PrevDown(link);
      }
      break;


    default:
    
      assert1(FALSE, "Next:", Image(type(x)));
      break;

  } /* end switch */
  debug1(DCS, DD, "Next returning %s", EchoObject(x));
  return x;
} /* end Next */
