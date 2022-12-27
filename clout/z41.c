/*@z41.c:Object Input-Output:AppendToFile, ReadFromFile@**********************/
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
/*  FILE:         z41.c                                                      */
/*  MODULE:       Object Input-Output                                        */
/*  EXTERNS:      ReadFromFile(), AppendToFile(), CloseFiles()               */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"

static FILE_NUM	last_write_fnum;
static FILE	*last_write_fp;


/*****************************************************************************/
/*                                                                           */
/*  void ReadFromFileInit(void)                                              */
/*                                                                           */
/*  Initialize this module.                                                  */
/*                                                                           */
/*****************************************************************************/

void ReadFromFileInit(void)
{
  last_write_fnum = NO_FILE;
  last_write_fp  = null;
}


/*****************************************************************************/
/*                                                                           */
/*  OBJECT ReadFromFile(fnum, pos, lnum)                                     */
/*                                                                           */
/*  Read an object from file fnum starting at position pos.                  */
/*  The object may include @Env operators defining its environment, or       */
/*  not, but in any case ReadFromFile assumes that the correct scope is set. */
/*  lnum is the line number of the spot you end up at when you seek to pos.  */
/*                                                                           */
/*****************************************************************************/

OBJECT ReadFromFile(FILE_NUM fnum, long pos, int lnum)
{ OBJECT t, res;
#if DEBUG_ON
  int ipos = 0;
#endif
  ifdebug(DPP, D, ProfileOn("ReadFromFile"));
  ifdebug(DIO, D, ipos = (int) pos);
  debug3(DIO, D, "ReadFromFile(%s, %d, %d)", FileName(fnum), ipos, lnum);
  LexPush(fnum, (int) pos, DATABASE_FILE, lnum, FALSE);
  t = LexGetToken();
  if( !objectOfType(t, LBR) )
  { debug1(DIO, D, "  following because type(t) = %s", Image(type(t)));
    Error(41, 1, "database index file seems to be out of date",
      FATAL, &fpos(t));
  }
  res = Parse(&t, StartSym, FALSE, FALSE);
  if( t != nilobj || !objectOfType(res, CLOSURE) )
  { debug1(DIO, D, "  following because of %s", t!=nilobj ? "t" : "type(res)");
    Error(41, 2, "syntax error in database file", FATAL, &fpos(res));
  }
  LexPop();
  debug1(DIO, D, "ReadFromFile returning %s", EchoObject(res));
  ifdebug(DPP, D, ProfileOff("ReadFromFile"));
  return res;
} /* end ReadFromFile */


/*****************************************************************************/
/*                                                                           */
/*  static Optimize(x, env)                                                  */
/*                                                                           */
/*****************************************************************************/
static void OptimizeParameterList(OBJECT x, OBJECT env);

static void Optimize(OBJECT x, OBJECT env)
{ OBJECT tmp;
  if( Down(x) != x )
  { OptimizeParameterList(x, env);
  }
  tmp = ParameterCheck(x, env);
  if( tmp != nilobj )
  { ReplaceNode(tmp, x);
    DisposeObject(x);
  }
}


/*****************************************************************************/
/*                                                                           */
/*  OptimizeParameterList(x, env)                                            */
/*                                                                           */
/*  Optimize the space required to print the parameters of x by evaluating   */
/*  them in environment env if this is feasible.                             */
/*                                                                           */
/*****************************************************************************/

static void OptimizeParameterList(OBJECT x, OBJECT env)
{ OBJECT y, z, link, t, tlink;
  assert( objectOfType(x, CLOSURE), "OptimizeParameterList: type(x) != CLOSURE!" );
  if( env == nilobj )  return;
  for( link = Down(x);  link != x;  link = NextDown(link) )
  { Child(y, link);
    if( objectOfType(y, PAR) )
    { Child(z, Down(y));
      if( objectOfType(z, CLOSURE) )
      {
	Optimize(z, env);
      }
      else if( objectOfType(z, ACAT) )
      { for( tlink = Down(z);  tlink != z;  tlink = NextDown(tlink) )
        { Child(t, Down(tlink));
          if( objectOfType(t, CLOSURE) )
	    Optimize(t, env);
        }
      }
    }
  }
} /* end OptimizeParameter */


/*@::WriteClosure()@**********************************************************/
/*                                                                           */
/*  static WriteClosure(x, linecount, fnum, env)                             */
/*                                                                           */
/*  Write closure x to file last_write_fp, without enclosing braces and      */
/*  without any environment attached.  If x happens to be a closure that     */
/*  was previously read as a @Use clause, write only @LUse and the name.     */
/*  Increment *linecount by the number of lines written.                     */
/*  The file being written to is fnum; the environment is env (for optim.)   */
/*                                                                           */
/*****************************************************************************/
static void WriteObject(OBJECT x, int outer_prec, int *linecount, FILE_NUM fnum);

static BOOLEAN2 need_lvis(OBJECT sym)	/* true if @LVis needed before sym */
{ return !visible(sym) &&
	 enclosing(sym) != StartSym &&
	 objectOfType(enclosing(sym), LOCAL);
} /* end need_lvis */

static void WriteClosure(OBJECT x, int *linecount, FILE_NUM fnum, OBJECT env)
{ OBJECT y, link, z, sym;
  BOOLEAN2 npar_written, name_printed;
  debug2(DIO, D, "[ WriteClosure(%s %s)", Image(type(x)), EchoObject(x));

  sym = actual(x);
  /* *** if( use_invocation(sym) == x ) *** */
  if( use_invocation(sym) != nilobj )
  { StringFPuts(KW_LUSE, last_write_fp);
    StringFPuts(STR_SPACE, last_write_fp);
    StringFPuts(SymName(sym), last_write_fp);
  }
  else
  { npar_written = FALSE;  name_printed = FALSE;
    OptimizeParameterList(x, env);
    for( link = Down(x);  link != x;  link = NextDown(link) )
    { Child(y, link);
      if( objectOfType(y, PAR) )  switch( type(actual(y)).objtype )
      {
        case LPAR_E:
      
	  assert( Down(y) != y, "WriteObject/CLOSURE: LPAR!" );
	  Child(z, Down(y));
	  WriteObject(z, (int) precedence(sym), linecount, fnum);
	  StringFPuts(STR_SPACE, last_write_fp);
	  break;


        case NPAR_E:
      
	  assert( Down(y) != y, "WriteObject/CLOSURE: NPAR!" );
	  Child(z, Down(y));
	  if( !name_printed )
	  { if( need_lvis(sym) )
	    { StringFPuts(KW_LVIS, last_write_fp);
	      StringFPuts(STR_SPACE, last_write_fp);
	    }
	    StringFPuts(SymName(sym), last_write_fp);
	    name_printed = TRUE;
	  }
	  StringFPuts(STR_NEWLINE, last_write_fp);
	  *linecount += 1;
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);

	  if( npar_code(actual(y)) != ' ' )
	  { StringFPuts(STR_ESCAPE, last_write_fp);
	    fprintf(last_write_fp, "%c", (char) npar_code(actual(y)));
	  }
	  else
	  { StringFPuts(SymName(actual(y)), last_write_fp);
	  }

	  StringFPuts(KW_LBR, last_write_fp);
	  WriteObject(z, NO_PREC, linecount, fnum);
	  StringFPuts(KW_RBR, last_write_fp);
	  npar_written = TRUE;
	  break;


        case RPAR_E:
      
	  assert( Down(y) != y, "WriteObject/CLOSURE: RPAR!" );
	  Child(z, Down(y));
	  if( !name_printed )
	  { if( need_lvis(sym) )
	    { StringFPuts(KW_LVIS, last_write_fp);
	      StringFPuts(STR_SPACE, last_write_fp);
	    }
	    StringFPuts(SymName(sym), last_write_fp);
	    name_printed = TRUE;
	  }
	  if( npar_written )
	  { StringFPuts(STR_NEWLINE, last_write_fp);
	    *linecount += 1;
	  }
	  else
	  { StringFPuts(STR_SPACE, last_write_fp);
	  }
	  /* old version: if( filter(sym) != nilobj ) */
	  if( filter(sym) != nilobj && objectOfType(z, FILTERED) ) /* ??? */
	  {
	    debug1(DIO, D, "  filter(sym) != nilobj, type(z) == %s",
	      Image(type(z)));
	    assert( objectOfType(z, FILTERED), "WriteClosure:  filter!" );
	    WriteObject(z, NO_PREC, linecount, fnum);
	  }
	  else if( has_body(sym) )
	  {
	    StringFPuts(KW_LBR, last_write_fp);
	    StringFPuts(STR_SPACE, last_write_fp);
	    WriteObject(z, NO_PREC, linecount, fnum);
	    StringFPuts(STR_SPACE, last_write_fp);
	    StringFPuts(KW_RBR, last_write_fp);
	  }
	  else WriteObject(z, (int) precedence(sym), linecount, fnum);
	  break;


        default:
      
	  assert1(FALSE, "WriteClosure:", Image(type(actual(y))));
	  break;

      } /* end switch */
    } /* end for each parameter */
    if( !name_printed )
    { if( need_lvis(sym) )
      { StringFPuts(KW_LVIS, last_write_fp);
        StringFPuts(STR_SPACE, last_write_fp);
      }
      StringFPuts(SymName(sym), last_write_fp);
      name_printed = TRUE;
    }
  }
  debug0(DIO, D, "] WriteClosure returning");
} /* end WriteClosure */


/*@::WriteObject()@***********************************************************/
/*                                                                           */
/*  static WriteObject(x, outer_prec, linecount, fnum)                       */
/*                                                                           */
/*  Write object x to file last_write_fp, assuming it is a subobject of an   */
/*  object and the precedence of operators enclosing it is outer_prec.       */
/*  Increment *linecount by the number of lines written.                     */
/*  The file being written to is fnum.                                       */
/*                                                                           */
/*****************************************************************************/

static void WriteObject(OBJECT x, int outer_prec, int *linecount, FILE_NUM fnum)
{ OBJECT link, y, z, gap_obj, sym, env;
  const FULL_CHAR *name;
  int offset, lnum;
  int prec, i, last_prec;  BOOLEAN2 braces_needed;
  debug2(DIO, D, "[ WriteObject(%s %s)", Image(type(x)), EchoObject(x));
  switch( type(x).objtype )
  {

    case WORD_E:

      if( StringLength(string(x)) == 0 && outer_prec > ACAT_PREC )
      { StringFPuts(KW_LBR, last_write_fp);
	StringFPuts(KW_RBR, last_write_fp);
      }
      else StringFPuts(string(x), last_write_fp);
      break;

    
    case QWORD_E:

      StringFPuts(StringQuotedWord(x), last_write_fp);
      break;

    
    case VCAT_E:  prec = VCAT_PREC;  goto ETC;
    case HCAT_E:  prec = HCAT_PREC;  goto ETC;
    case ACAT_E:  prec = ACAT_PREC;  goto ETC;

      ETC:
      if( prec < outer_prec )  StringFPuts(KW_LBR, last_write_fp);
      last_prec = prec;
      for( link = Down(x);  link != x;  link = NextDown(link) )
      {	Child(y, link);
	if( objectOfType(y, GAP_OBJ) )
	{ if( Down(y) == y )
	  { assert( objectOfType(x, ACAT), "WriteObject: Down(y) == y!" );
	    for( i = 1;  i <= vspace(y);  i++ )
	      StringFPuts(STR_NEWLINE, last_write_fp);
	    *linecount += vspace(y);
	    for( i = 1;  i <= hspace(y);  i++ )
	      StringFPuts(STR_SPACE,  last_write_fp);
	    last_prec = (vspace(y) + hspace(y) == 0) ? JUXTA_PREC : ACAT_PREC;
	  }
	  else
	  { Child(gap_obj, Down(y));
	    if( objectOfType(x, ACAT) )
	      StringFPuts(STR_SPACE, last_write_fp);
	    else
	    { StringFPuts(STR_NEWLINE, last_write_fp);
	      *linecount += 1;
	    }
	    StringFPuts(EchoCatOp(type(x), mark(gap(y)), join(gap(y))),
	      last_write_fp);
	    if( !is_word(type(gap_obj)) || StringLength(string(gap_obj)) != 0 )
		WriteObject(gap_obj, FORCE_PREC, linecount, fnum);
	    StringFPuts(STR_SPACE, last_write_fp);
	    last_prec = prec;
	  }
	}
	else
	{ if( objectOfType(x, ACAT) )
	  { OBJECT next_gap;  int next_prec;
	    if( NextDown(link) != x )
	    { Child(next_gap, NextDown(link));
	      assert( objectOfType(next_gap, GAP_OBJ), "WriteObject: next_gap!" );
	      next_prec = (vspace(next_gap) + hspace(next_gap) == 0)
				? JUXTA_PREC : ACAT_PREC;
	    }
	    else next_prec = prec;
	    WriteObject(y, find_max(last_prec, next_prec), linecount, fnum);
	  }
	  else WriteObject(y, prec, linecount, fnum);
	}
      }
      if( prec < outer_prec )  StringFPuts(KW_RBR, last_write_fp);
      break;


    case ENV_E:

      if( Down(x) == x )
      {
	/* environment is empty */
	StringFPuts(KW_ENVC, last_write_fp);
	StringFPuts(STR_NEWLINE, last_write_fp);
	*linecount += 1;
      }
      else if( EnvWriteRetrieve(x, fnum, &offset, &lnum) )
      {
	/* environment was previously written to this file */
	StringFPuts(KW_ENVD, last_write_fp);
	fprintf(last_write_fp, " \"%d %d\"", offset, lnum);
	StringFPuts(STR_NEWLINE, last_write_fp);
	*linecount += 1;
      }
      else
      {
	/* record the position of this environment */
	EnvWriteInsert(x, fnum, (int) ftell(last_write_fp), *linecount);

	/* write the environment */
	if( Down(x) == LastDown(x) )
        {
	  /* envt contains just one closure (with its environment) */
	  Child(y, Down(x));
	  assert( objectOfType(y, CLOSURE), "WriteObject: ENV/CLOSURE!" );
	  StringFPuts(KW_LBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_ENVA, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_LBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  WriteObject(y, NO_PREC, linecount, fnum);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_RBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_RBR, last_write_fp);
	  StringFPuts(STR_NEWLINE, last_write_fp);
	  *linecount += 1;
        }
        else
        {
	  /* envt contains a closure (with envt) plus an environment */
	  Child(env, LastDown(x));
	  assert( objectOfType(env, ENV), "WriteObject: ENV/ENV!" );
	  StringFPuts(KW_LBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_ENVB, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_LBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  WriteObject(env, NO_PREC, linecount, fnum);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_RBR, last_write_fp);
	  StringFPuts(STR_NEWLINE, last_write_fp);
	  *linecount += 1;
	  Child(y, Down(x));
	  assert( objectOfType(y, CLOSURE), "WriteObject: ENV/ENV+CLOSURE!" );
	  StringFPuts(KW_LBR, last_write_fp);
	  WriteObject(y, NO_PREC, linecount, fnum);
	  StringFPuts(KW_RBR, last_write_fp);
	  StringFPuts(STR_SPACE, last_write_fp);
	  StringFPuts(KW_RBR, last_write_fp);
	  StringFPuts(STR_NEWLINE, last_write_fp);
	  *linecount += 1;
        }
      }
      break;


    case CLOSURE_E:

      sym = actual(x);  env = nilobj;
      if( LastDown(x) != x )
      {	Child(y, LastDown(x));
	if( objectOfType(y, ENV) )  env = y;
      }

      braces_needed = env != nilobj ||
	(precedence(sym) <= outer_prec && (has_lpar(sym) || has_rpar(sym))) ||
	outer_prec >= JUXTA_PREC;

      /* print environment */
      if( env != nilobj )
      {	StringFPuts(KW_CENV, last_write_fp);
	StringFPuts(STR_SPACE, last_write_fp);
	StringFPuts(KW_LBR, last_write_fp);
      	StringFPuts(STR_NEWLINE, last_write_fp);
	*linecount += 1;
	WriteObject(env, NO_PREC, linecount, fnum);
        StringFPuts(KW_RBR, last_write_fp);
      	StringFPuts(STR_NEWLINE, last_write_fp);
	*linecount += 1;
      }

      /* print left brace if needed */
      if( braces_needed )  StringFPuts(KW_LBR, last_write_fp);
	
      /* print the closure proper */
      WriteClosure(x, linecount, fnum, env);

      /* print closing brace if needed */
      if( braces_needed )  StringFPuts(KW_RBR, last_write_fp);

      /* print closing environment if needed */
      /* ***
      if( env != nilobj )
      { StringFPuts(KW_RBR, last_write_fp);
	StringFPuts(STR_NEWLINE, last_write_fp);
	*linecount += 1;
      }
      *** */
      break;


    case CROSS_E:
    case FORCE_CROSS_E:

      Child(y, Down(x));
      assert( objectOfType(y, CLOSURE), "WriteObject/CROSS: type(y) != CLOSURE!" );
      if( DEFAULT_PREC <= outer_prec )  StringFPuts(KW_LBR, last_write_fp);
      if( need_lvis(actual(y)) )
      { StringFPuts(KW_LVIS, last_write_fp);
        StringFPuts(STR_SPACE, last_write_fp);
      }
      StringFPuts(SymName(actual(y)), last_write_fp);
      StringFPuts(objectOfType(x, CROSS) ? KW_CROSS : KW_FORCE_CROSS, last_write_fp);
      Child(y, LastDown(x));
      WriteObject(y, FORCE_PREC, linecount, fnum);
      if( DEFAULT_PREC <= outer_prec )  StringFPuts(KW_RBR, last_write_fp);
      break;


    case NULL_CLOS_E:	name = KW_NULL;		goto SETC;
    case PAGE_LABEL_E:	name = KW_PAGE_LABEL;	goto SETC;
    case BEGIN_HEADER_E:	name = KW_BEGIN_HEADER;	goto SETC;
    case END_HEADER_E:	name = KW_END_HEADER;	goto SETC;
    case SET_HEADER_E:	name = KW_SET_HEADER;	goto SETC;
    case CLEAR_HEADER_E:	name = KW_CLEAR_HEADER;	goto SETC;
    case ONE_COL_E:	name = KW_ONE_COL;	goto SETC;
    case ONE_ROW_E:	name = KW_ONE_ROW;	goto SETC;
    case WIDE_E:		name = KW_WIDE;		goto SETC;
    case HIGH_E:		name = KW_HIGH;		goto SETC;
    case HSHIFT_E:	name = KW_HSHIFT;	goto SETC;
    case VSHIFT_E:	name = KW_VSHIFT;	goto SETC;
    case HMIRROR_E:	name = KW_HMIRROR;	goto SETC;
    case VMIRROR_E:	name = KW_VMIRROR;	goto SETC;
    case HSCALE_E:	name = KW_HSCALE;	goto SETC;
    case VSCALE_E:	name = KW_VSCALE;	goto SETC;
    case HCOVER_E:	name = KW_HCOVER;	goto SETC;
    case VCOVER_E:	name = KW_VCOVER;	goto SETC;
    case SCALE_E:		name = KW_SCALE;	goto SETC;
    case KERN_SHRINK_E:	name = KW_KERN_SHRINK;	goto SETC;
    case HCONTRACT_E:	name = KW_HCONTRACT;	goto SETC;
    case VCONTRACT_E:	name = KW_VCONTRACT;	goto SETC;
    case HLIMITED_E:	name = KW_HLIMITED;	goto SETC;
    case VLIMITED_E:	name = KW_VLIMITED;	goto SETC;
    case HEXPAND_E:	name = KW_HEXPAND;	goto SETC;
    case VEXPAND_E:	name = KW_VEXPAND;	goto SETC;
    case START_HVSPAN_E:	name = KW_STARTHVSPAN;	goto SETC;
    case START_HSPAN_E:	name = KW_STARTHSPAN;	goto SETC;
    case START_VSPAN_E:	name = KW_STARTVSPAN;	goto SETC;
    case HSPAN_E:		name = KW_HSPAN;	goto SETC;
    case VSPAN_E:		name = KW_VSPAN;	goto SETC;
    case PADJUST_E:	name = KW_PADJUST;	goto SETC;
    case HADJUST_E:	name = KW_HADJUST;	goto SETC;
    case VADJUST_E:	name = KW_VADJUST;	goto SETC;
    case ROTATE_E:	name = KW_ROTATE;	goto SETC;
    case BACKGROUND_E:	name = KW_BACKGROUND;	goto SETC;
    case CASE_E:		name = KW_CASE;		goto SETC;
    case YIELD_E:		name = KW_YIELD;	goto SETC;
    case BACKEND_E:	name = KW_BACKEND;	goto SETC;
    case XCHAR_E:		name = KW_XCHAR;	goto SETC;
    case FONT_E:		name = KW_FONT;		goto SETC;
    case SPACE_E:		name = KW_SPACE;	goto SETC;
    case YUNIT_E:		name = KW_YUNIT;	goto SETC;
    case ZUNIT_E:		name = KW_ZUNIT;	goto SETC;
    case SET_CONTEXT_E:	name = KW_SET_CONTEXT;	goto SETC;
    case GET_CONTEXT_E:	name = KW_GET_CONTEXT;	goto SETC;
    case BREAK_E:		name = KW_BREAK;	goto SETC;
    case UNDERLINE_E:	name = KW_UNDERLINE;	goto SETC;
    case UNDERLINE_COLOUR_E: name=KW_UNDERLINE_COLOUR ;goto SETC;
    case COLOUR_E:	name = KW_COLOUR;	goto SETC;
    case TEXTURE_E:	name = KW_TEXTURE;	goto SETC;
    case OUTLINE_E:	name = KW_OUTLINE;	goto SETC;
    case LANGUAGE_E:	name = KW_LANGUAGE;	goto SETC;
    case CURR_LANG_E:	name = KW_CURR_LANG;	goto SETC;
    case CURR_FAMILY_E:	name = KW_CURR_FAMILY;	goto SETC;
    case CURR_FACE_E:	name = KW_CURR_FACE;	goto SETC;
    case CURR_YUNIT_E:	name = KW_CURR_YUNIT;	goto SETC;
    case CURR_ZUNIT_E:	name = KW_CURR_ZUNIT;	goto SETC;
    case COMMON_E:	name = KW_COMMON;	goto SETC;
    case RUMP_E:		name = KW_RUMP;		goto SETC;
    case MELD_E:		name = KW_MELD;		goto SETC;
    case INSERT_E:	name = KW_INSERT;	goto SETC;
    case ONE_OF_E:	name = KW_ONE_OF;	goto SETC;
    case NEXT_E:		name = KW_NEXT;		goto SETC;
    case PLUS_E:		name = KW_PLUS;		goto SETC;
    case MINUS_E:		name = KW_MINUS;	goto SETC;
    case OPEN_E:		name = KW_OPEN;		goto SETC;
    case TAGGED_E:	name = KW_TAGGED;	goto SETC;
    case INCGRAPHIC_E:	name = KW_INCGRAPHIC;	goto SETC;
    case SINCGRAPHIC_E:	name = KW_SINCGRAPHIC;	goto SETC;
    case PLAIN_GRAPHIC_E:	name = KW_PLAINGRAPHIC;	goto SETC;
    case GRAPHIC_E:	name = KW_GRAPHIC;	goto SETC;
    case LINK_SOURCE_E:	name = KW_LINK_SOURCE;	goto SETC;
    case LINK_DEST_E:	name = KW_LINK_DEST;	goto SETC;
    case LINK_DEST_NULL_E:name = KW_LINK_DEST;	goto SETC;
    case LINK_URL_E:	name = KW_LINK_URL;	goto SETC;

      /* print left parameter, if present */
      SETC:
      if( DEFAULT_PREC <= outer_prec )  StringFPuts(KW_LBR, last_write_fp);
      if( Down(x) != LastDown(x) )
      {	Child(y, Down(x));
	WriteObject(y, DEFAULT_PREC, linecount, fnum);
	StringFPuts(STR_SPACE, last_write_fp);
      }

      /* print the name of the symbol */
      StringFPuts(name, last_write_fp);

      /* print right parameter, if present */
      if( LastDown(x) != x )
      {	Child(y, LastDown(x));
	StringFPuts(STR_SPACE, last_write_fp);
	if( objectOfType(x, OPEN) )
	{ StringFPuts(KW_LBR, last_write_fp);
	  WriteObject(y, NO_PREC, linecount, fnum);
	  StringFPuts(KW_RBR, last_write_fp);
	}
	else WriteObject(y, DEFAULT_PREC, linecount, fnum);
      }
      if( DEFAULT_PREC <= outer_prec )  StringFPuts(KW_RBR, last_write_fp);
      break;


    case RAW_VERBATIM_E:
    case VERBATIM_E:

      StringFPuts(objectOfType(x, VERBATIM) ? KW_VERBATIM : KW_RAWVERBATIM, last_write_fp);
      StringFPuts(STR_SPACE, last_write_fp);
      StringFPuts(KW_BEGIN, last_write_fp);
      StringFPuts(STR_NEWLINE, last_write_fp);
      Child(y, Down(x));
      if( objectOfType(y, WORD) )
      {
	StringFPuts(string(y), last_write_fp);
        StringFPuts(STR_SPACE, last_write_fp);
      }
      else
      {
	assert( objectOfType(y, VCAT), "WriteObject/VERBATIM!" );
	for( link = Down(y);  link != y;  link = NextDown(link) )
	{ Child(z, link);
	  if( objectOfType(z, GAP_OBJ) )  continue;
	  assert( objectOfType(z, WORD), "WriteObject/VERBATIM/WORD!");
	  StringFPuts(string(z), last_write_fp);
	  StringFPuts(STR_NEWLINE, last_write_fp);
	  *linecount += 1;
	}
      }
      StringFPuts(KW_END, last_write_fp);
      StringFPuts(STR_SPACE, last_write_fp);
      StringFPuts(objectOfType(x, VERBATIM) ? KW_VERBATIM : KW_RAWVERBATIM, last_write_fp);
      break;


    case FILTERED_E:

      FilterWrite(x, last_write_fp, linecount);
      break;


    default:

      assert1(FALSE, "WriteObject:", Image(type(x)));
      break;

  } /* end switch */
  debug0(DIO, D, "] WriteObject returning");
} /* end WriteObject */


/*@::AppendToFile(), CloseFiles()@********************************************/
/*                                                                           */
/*  AppendToFile(x, fnum, pos, lnum)                                         */
/*                                                                           */
/*  Append object x to file fnum, returning its fseek position in *pos.      */
/*  and its line number in lnum.  Record that this file has been updated.    */
/*                                                                           */
/*****************************************************************************/

void AppendToFile(OBJECT x, FILE_NUM fnum, int *pos, int *lnum)
{ FULL_CHAR buff[MAX_BUFF], *str;  int linecount;
  debug2(DIO, D, "[ AppendToFile( %s, %s )", EchoObject(x), FileName(fnum));

  /* open file fnum for writing */
  if( last_write_fnum != fnum )
  { if( last_write_fnum != NO_FILE )  fclose(last_write_fp);
    str = FileName(fnum);
    if( StringLength(str) + StringLength(NEW_DATA_SUFFIX) >= MAX_BUFF )
      Error(41, 3, "file name %s%s is too long",
	FATAL, PosOfFile(fnum), str, NEW_DATA_SUFFIX);
    StringCopy(buff, str);  StringCat(buff, NEW_DATA_SUFFIX);
    last_write_fp = StringFOpen(buff,
      FileTestUpdated(fnum) ? APPEND_FILE : WRITE_FILE);
    if( last_write_fp == null )
      Error(41, 4, "cannot append to database file %s", FATAL, no_fpos, buff);
    last_write_fnum = fnum;
    (void) fseek(last_write_fp, 0L, SEEK_END);
  }

  /* write x out and record the fact that fnum has changed */
  *pos = (int) ftell(last_write_fp);
  StringFPuts(KW_LBR, last_write_fp);
  linecount = FileGetLineCount(fnum);
  *lnum = linecount + 1;
  WriteObject(x, NO_PREC, &linecount, fnum);
  StringFPuts(KW_RBR, last_write_fp);
  StringFPuts(STR_NEWLINE, last_write_fp);
  StringFPuts(STR_NEWLINE, last_write_fp);
  FileSetUpdated(fnum, linecount + 2);
  debug0(DIO, D, "] AppendToFile returning.");
} /* end AppendToFile */


/*****************************************************************************/
/*                                                                           */
/*  CloseFiles()                                                             */
/*                                                                           */
/*  Close all files and move new versions to the names of old versions.      */
/*                                                                           */
/*****************************************************************************/

void CloseFiles(void)
{ FILE_NUM fnum;  FULL_CHAR oldname[MAX_BUFF], newname[MAX_BUFF];
  FILE *fp;
  ifdebug(DPP, D, ProfileOn("CloseFiles"));
  debug0(DIO, D, "CloseFiles()");

  /* close off last file opened by AppendToFile above */
  if( last_write_fnum != NO_FILE )  fclose(last_write_fp);

  /* get rid of old database files */
  for( fnum=FirstFile(SOURCE_FILE);  fnum != NO_FILE;  fnum = NextFile(fnum) )
  { StringCopy(oldname, FileName(fnum));
    StringCat(oldname, DATA_SUFFIX);
    debug1(DIO, D, "remove(%s)", oldname);
    StringRemove(oldname);
  }

  /* move any new database files to the old names, if updated */
  /* just to avoid confusion: the "new name" means the ".ldx" */
  /* temporary file name; the "old name" means the permanent  */
  /* name, i.e. ".ld".  So we have to move the new name to    */
  /* the old name.                                            */

  for( fnum=FirstFile(DATABASE_FILE); fnum != NO_FILE; fnum = NextFile(fnum) )
  { if( FileTestUpdated(fnum) )
    {
      /* construct new and old file names */
      StringCopy(oldname, FileName(fnum));
      StringCopy(newname, oldname);
      StringCat(newname, NEW_DATA_SUFFIX);

      /* guaranteed portable algorithm for changing the name of file	*/
      /* "newname" to "oldname": if "oldname" exists already, then	*/
      /* remove it (avoids removing a non-existent file, which can	*/
      /* be a problem); then rename "newname" to be "oldname" (avoids	*/
      /* overwriting an existing file "oldname", another problem)	*/

      if( (fp = StringFOpen(oldname, READ_FILE)) != NULL )
      { fclose(fp);
	StringRemove(oldname);
      }
      debug2(DIO, D, "rename(%s, %s)", newname, oldname);
      if( StringRename(newname, oldname) != 0 )
	Error(41, 5, "rename(%s, %s) failed", INTERN, no_fpos,newname,oldname);
    }
  }
  debug0(DIO, D, "CloseFiles returning.");
  ifdebug(DPP, D, ProfileOff("CloseFiles"));
} /* end CloseFiles */
