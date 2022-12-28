/*@z08.c:Object Manifest:ReplaceWithSplit()@**********************************/
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
/*  FILE:         z08.c                                                      */
/*  MODULE:       Object Manifest                                            */
/*  EXTERNS:      Manifest()                                                 */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"
#define line_breaker(g)							\
  (vspace(g) > 0 || (gapHasUnit(&gap(g), FRAME_UNIT) && width(&gap(g)) > FR))


/*****************************************************************************/
/*                                                                           */
/*  static SetUnderline(x)                                                   */
/*                                                                           */
/*  Set underline() flags in object x to UNDER_ON as appropriate.            */
/*                                                                           */
/*****************************************************************************/

static void SetUnderline(OBJECT x)
{ OBJECT y, link;
  debug2(DOM, DD, "  Manifest underlining %s %s", Image(type(x)),EchoObject(x));
  if( objectOfType(x, ACAT) )
  { for( link = Down(x);  link != x;  link = NextDown(link) )
    { Child(y, link);
      SetUnderline(y);
    }
  }
  debug3(DOM, DDD, "  SetUnderline underline() := %s for %s %s",
    "UNDER_ON", Image(type(x)), EchoObject(x));
  setUnderline(x, UNDER_ON);
} /* end SetUnderline */


/*****************************************************************************/
/*                                                                           */
/*  static ReplaceWithSplit(x, bthr, fthr)                                   */
/*                                                                           */
/*  Replace object x with a SPLIT object, if threads for this object are     */
/*  requested by bthr and/or fthr.                                           */
/*                                                                           */
/*****************************************************************************/

#define ReplaceWithSplit(x, bthr, fthr)					\
   if( bthr[ROWM_E] || bthr[COLM_E] || fthr[ROWM_E] || fthr[COLM_E] )		\
	x = insert_split(x, bthr, fthr)

static OBJECT insert_split(OBJECT x, OBJECT bthr[2], OBJECT fthr[2])
{ OBJECT res, new_op;  int dim;
  debug1(DOM, DD, "ReplaceWithSplit(%s, -)", EchoObject(x));
  assert( !objectOfType(x, SPLIT), "ReplaceWithSplit: type(x) already SPLIT!" );
  New(res, SPLIT);
  setFwd(res, ROWM, 0);
  setFwd(res, COLM, 0);
  setBack(res, ROWM, 0);
  setBack(res, COLM, 0);
  FposCopy(fpos(res), fpos(x));
  ReplaceNode(res, x);
  for( dim = COLM_E;  dim <= ROWM_E;  dim++ )
  { if( bthr[dim] || fthr[dim] )
    {
      debug0(DGP, DD, "  calling New(thread) from Manifest now");
      New(new_op, dim == COLM_E ? COL_THR : ROW_THR);
      thr_state(new_op) = NOTSIZED;
      DIM_TE other = otherDim(dimFromU(dim));
      setFwd(new_op, other, 0);	/* will hold max frame_size */
      setBack(new_op, other, 0);	/* will hold max frame_origin */
      FposCopy(fpos(new_op), fpos(x));
      Link(res, new_op);  Link(new_op, x);
      if( bthr[dim] )  Link(bthr[dim], new_op);
      if( fthr[dim] )  Link(fthr[dim], new_op);
    }
    else Link(res, x);
  }

  debug1(DOM, DD, "ReplaceWithSplit returning %s", EchoObject(res));
  return res;
} /* end insert_split */

/*@::ReplaceWithTidy()@*******************************************************/
/*                                                                           */
/*  OBJECT ReplaceWithTidy(x, spacing)                                       */
/*                                                                           */
/*  Replace object x with a tidier version in which juxtapositions are       */
/*  folded.  If this is not possible, return the original object.            */
/*                                                                           */
/*  Spacing can have value 0, 1, or 2, with the following meaning:           */
/*                                                                           */
/*     ACAT_TIDY    An ACAT is the preferred result                          */
/*                                                                           */
/*     WORD_TIDY    The result is to be a single QWORD with interword spaces */
/*                  converted to as many space characters as there were.     */
/*                                                                           */
/*     PARA_TIDY    The result is to be a single QWORD with interword spaces */
/*                  replaced by single spaces, and line ends marked by       */
/*                  newline characters.                                      */
/*                                                                           */
/*****************************************************************************/

OBJECT ReplaceWithTidy(OBJECT x, TIDY_TE spacing)
{ static FULL_CHAR	buff[MAX_WORD];		/* the growing current word */
  static int		buff_len;		/* length of current word   */
  static FILE_POS	buff_pos;		/* filepos of current word  */
  OBJTYPE	buff_typ;		/* WORD or QWORD of current */
  OBJECT                link, y, tmp, res;	/* temporaries              */
  int i;
  debug2(DOM, DD, "ReplaceWithTidy(%s, %s)", EchoObject(x),
    sameTidy(spacing, ACAT_TIDY) ? "ACAT_TIDY" :
    sameTidy(spacing, WORD_TIDY) ? "WORD_TIDY" : "PARA_TIDY");
  switch( type(x).objtype )
  {
    case ACAT_E:
    
      for( link = Down(x);  link != x;  link = NextDown(link) )
      {	Child(y, link);
	if( objectOfType(y, ACAT) )
	{ tmp = Down(y);  TransferLinks(tmp, y, link);
	  DisposeChild(link);  link = PrevDown(tmp);
	}
      }
      res = nilobj;  buff_len = 0;  buff_typ = WORD;
      FposCopy(buff_pos, fpos(x));
      for( link = Down(x); link != x; link = NextDown(link) )
      {	Child(y, link);
	if( is_word(type(y)) )
	{ if( buff_len + StringLength(string(y)) >= MAX_WORD )
	    Error(8, 1, "word is too long (%d characters)", WARN, &fpos(y),
	     buff_len + StringLength(string(y)));
	  else
	  { if( buff_len == 0 )  FposCopy(buff_pos, fpos(y));
	    StringCopy(&buff[buff_len], string(y));
	    buff_len += StringLength(string(y));
	    if( objectOfType(y, QWORD) )  buff_typ = QWORD;
	  }
	}
	else if( objectOfType(y, GAP_OBJ) )
	{ if( Down(y) != y || hspace(y) + vspace(y) > 0 )
	  {
	    switch( spacing.tidy )
	    {
	      case WORD_TIDY_E:
		      
	        if( buff_len + hspace(y) + vspace(y) >= MAX_WORD )
		  Error(8, 2, "word is too long (%d characters)", WARN, &fpos(y),
		   buff_len + hspace(y) + vspace(y) );
	        else
	        { for( i = 0;  i < hspace(y) + vspace(y);  i++ )
		  { StringCopy(&buff[buff_len], AsciiToFull(" "));
		    buff_len++;
		  }
		  buff_typ = QWORD;
	        }
		break;


	      case ACAT_TIDY_E:

	        tmp = MakeWord(buff_typ, buff, &buff_pos);
	        buff_len = 0;  buff_typ = WORD;
	        if( res == nilobj )
	        { New(res, ACAT);
		  FposCopy(fpos(res), fpos(x));
	        }
	        Link(res, tmp);  Link(res, y);
	        break;


	      case PARA_TIDY_E:

	        if( buff_len + hspace(y) + vspace(y) >= MAX_WORD )
		  Error(8, 2, "word is too long (%d characters)", WARN, &fpos(y),
		   buff_len + hspace(y) + vspace(y));
	        else
	        {
		  for( i = 0;  i < vspace(y);  i++ )
		  { StringCopy(&buff[buff_len], STR_NEWLINE);
		    buff_len++;
		  }
		  for( i = 0;  i < hspace(y);  i++ )
		  { StringCopy(&buff[buff_len], STR_SPACE);
		    buff_len++;
		  }
		  buff_typ = QWORD;
	        }
		break;


	      default:

		assert(FALSE, "bad spacing type in ReplaceWithTidy");
		break;
	    }
	  }
	}
	else /* error */
	{ if( res != nilobj )  DisposeObject(res);
	  debug0(DOM, DD, "ReplaceWithTidy returning unchanged");
	  return x;
	}
      }
      tmp = MakeWord(buff_typ, buff, &buff_pos);
      if( res == nilobj )  res = tmp;
      else Link(res, tmp);
      ReplaceNode(res, x);  DisposeObject(x);
      debug1(DOM, DD, "ReplaceWithTidy returning %s", EchoObject(res));
      return res;


    case WORD_E:
    case QWORD_E:

      debug1(DOM, DD, "ReplaceWithTidy returning %s", EchoObject(x));
      return x;


    default:

      debug0(DOM, DD, "ReplaceWithTidy returning unchanged");
      return x;
  }
} /* end ReplaceWithTidy */


/*@::GetScaleFactor()@********************************************************/
/*                                                                           */
/*  static float GetScaleFactor(x)                                           */
/*                                                                           */
/*  Find a scale factor in object x and return it as a float, after checks.  */
/*                                                                           */
/*****************************************************************************/

float GetScaleFactor(OBJECT x)
{ float scale_factor;
  if( !is_word(type(x)) )
  { Error(8, 3, "replacing invalid scale factor by 1.0", WARN, &fpos(x));
    scale_factor = 1.0;
  }
  else if( sscanf( (char *) string(x), "%f", &scale_factor) != 1 )
  { Error(8, 4, "replacing invalid scale factor %s by 1.0",
      WARN, &fpos(x), string(x));
    scale_factor = 1.0;
  }
  else if( scale_factor < 0.01 )
  { Error(8, 5, "replacing undersized scale factor %s by 1.0",
      WARN, &fpos(x), string(x));
    scale_factor = 1.0;
  }
  else if( scale_factor > 100 )
  { Error(8, 6, "replacing oversized scale factor %s by 1.0",
      WARN, &fpos(x), string(x));
    scale_factor = 1.0;
  }
  return scale_factor;
} /* GetScaleFactor */


static OBJECT nbt[2] = { nilobj, nilobj };	/* constant nilobj threads */
static OBJECT nft[2] = { nilobj, nilobj };	/* constant nilobj threads */
static OBJECT ntarget = nilobj;			/* constant nilobj target  */
static OBJECT nenclose = nilobj;		/* constant nilobj enclose  */


/*@::ManifestCat@*************************************************************/
/*                                                                           */
/*  OBJECT ManifestCat(x,env,style,bthr, fthr, target, crs, ok, need_expand, */
/*                     enclose, fcr)                                         */
/*                                                                           */
/*  This procedure implements Manifest (see below) when x is HCAT or VCAT.   */
/*                                                                           */
/*****************************************************************************/

#pragma clang diagnostic ignored "-Wunused-parameter"
static OBJECT ManifestCat(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
OBJECT fthr[2], OBJECT *target, OBJECT *crs, BOOLEAN2 ok, BOOLEAN2 need_expand,
OBJECT *enclose, BOOLEAN2 fcr)
{ OBJECT bt[2], ft[2], y, link, gaplink, g, first_bt, last_ft, z;
  int par, perp;
  unsigned res_inc;  BOOLEAN2 still_backing;
  STYLE new_style, gap_style;
  debug1(DOM, DD, "[ ManifestCat(%s)", EchoObject(x));
    
  StyleCopy(&new_style, style);
  if( objectOfType(x, HCAT) )
  { par = ROWM_E;
    adjust_cat(x) = hadjust(style);
    setHadjust(&new_style, FALSE);
  }
  else
  { par = COLM_E;
    adjust_cat(x) = vadjust(style);
    setVadjust(&new_style, FALSE);
  }
  perp = 1 - par;
  link = Down(x);
  gaplink = NextDown(link);
  assert( link!=x && gaplink!=x, "Manifest/VCAT: less than two children!" );
  Child(y, link);  Child(g, gaplink);

  /* set bt and ft threads for y */
  bt[perp] = bthr[perp];
  ft[perp] = fthr[perp];
  if( bthr[par] )  { New(first_bt, THREAD); }
  else first_bt = nilobj;
  bt[par] = first_bt;
  if( join(&gap(g)) )  { New(ft[par], THREAD); }
  else ft[par] = nilobj;
  still_backing = first_bt != nilobj;

  /* manifest y and insinuate any cross-references */
  y = Manifest(y, env, &new_style, bt, ft, target, crs, ok, FALSE, enclose, fcr);
  if( objectOfType(x, VCAT) && ok && *crs != nilobj )
  { debug1(DCR, DD, "  insinuating %s", EchoObject(*crs));
    TransferLinks(Down(*crs), *crs, link);
    DisposeObject(*crs);
    *crs = nilobj;
  }

  /* manifest the remaining children */
  while( g != nilobj )
  {	
    /* manifest the gap object, store it in gap(g), add perp threads */
    assert( objectOfType(g, GAP_OBJ), "Manifest/VCAT: type(g) != GAP_OBJECT!" );
    assert( Down(g) != g, "Manifest/VCAT: GAP_OBJ has no child!" );
    Child(z, Down(g));
    debug2(DOM, DD, "manifesting gap, z = %s, style = %s",
      EchoObject(z), EchoStyle(style));
    z = Manifest(z, env, &new_style, nbt, nft, &ntarget, crs, FALSE,
      FALSE, enclose, fcr);
    debug1(DOM, DD, "after manifesting gap, z = %s", EchoObject(z));
    if( objectOfType(z, ACAT) )
      StyleCopy(&gap_style, &save_style(z));
    else
      StyleCopy(&gap_style, style);
    z = ReplaceWithTidy(z, ACAT_TIDY);
    debug1(DOM, DD, "calling GetGap, style = %s", EchoStyle(&gap_style));
    GetGap(z, &gap_style, &gap(g), &res_inc);
    if( bt[perp] )  Link(bt[perp], g);
    if( ft[perp] )  Link(ft[perp], g);

    /* find the next child y, and following gap if any */
    link = NextDown(gaplink);
    assert( link != x, "Manifest/VCAT: GAP_OBJ is last child!" );
    Child(y, link);
    gaplink = NextDown(link);
    if( gaplink == x )  g = nilobj;
    else Child(g, gaplink);

    /* set bt and ft threads for y */
    last_ft = ft[par];
    if( ft[par] ) { New(bt[par], THREAD); }  else bt[par] = nilobj;
    if( g != nilobj )
    { if( join(&gap(g)) )  { New(ft[par], THREAD); }  else ft[par] = nilobj;
    }
    else
    {
      if( fthr[par] )  { New(ft[par], THREAD); }  else ft[par] = nilobj;
    }

    /* manifest y and insinuate any cross references */
    y = Manifest(y, env, &new_style, bt, ft, target, crs, ok, FALSE, enclose, fcr);
    if( objectOfType(x, VCAT) && ok && *crs != nilobj )
    { debug1(DCR, DD, "  insinuating %s", EchoObject(*crs));
      TransferLinks(Down(*crs), *crs, link);
      DisposeObject(*crs);
      *crs = nilobj;
    }

    if( bt[par] )	/* then thread lists last_ft and bt[par] must merge */
    { OBJECT llink, rlink, lthread, rthread;
      BOOLEAN2 goes_through;
      assert( Down(bt[par]) != bt[par], "Manifest: bt[par] no children!" );
      assert( last_ft!=nilobj && Down(last_ft)!=last_ft, "Manifest:last_ft!" );

      /* check whether marks run right through y in par direction */
      goes_through = FALSE;
      if( ft[par] )
      {	assert( Down(ft[par]) != ft[par], "Manifest: ft[par] child!" );
	Child(lthread, LastDown(bt[par]));
	Child(rthread, LastDown(ft[par]));
	goes_through = lthread == rthread;
      }

      /* merge the thread lists */
      llink = Down(last_ft);  rlink = Down(bt[par]);
      while( llink != last_ft && rlink != bt[par] )
      {	Child(lthread, llink);
	Child(rthread, rlink);
	assert( lthread != rthread, "Manifest: lthread == rthread!" );
	MergeNode(lthread, rthread);
	llink = NextDown(llink);
	rlink = NextDown(rlink);
      }

      /* attach leftover back threads to first_bt if required */
      if( rlink != bt[par] )
      { 
	if( still_backing )  TransferLinks(rlink, bt[par], first_bt);
      }
      DisposeObject(bt[par]);

      /* attach leftover forward threads to ft[par] if required */
      if( llink != last_ft )
      {
	if( goes_through )  TransferLinks(llink, last_ft, ft[par]);
      }
      DisposeObject(last_ft);

      if( !goes_through )  still_backing = FALSE;

    }
    else still_backing = FALSE;

  } /* end while */

  /* export par threads */
  if( fthr[par] )  MergeNode(fthr[par], ft[par]);
  if( bthr[par] )  MergeNode(bthr[par], first_bt);
  debug0(DOM, DD, "] ManifestCat returning");
  return x;
} /* end ManifestCat */


/*@::ManifestCase@************************************************************/
/*                                                                           */
/*  OBJECT ManifestCase(x,env,style,bthr,fthr, target, crs, ok, need_expand, */
/*                      enclose, fcr)                                        */
/*                                                                           */
/*  This procedure implements Manifest (see below) when x is CASE.           */
/*                                                                           */
/*****************************************************************************/

#pragma clang diagnostic ignored "-Wunused-parameter"
static OBJECT ManifestCase(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
OBJECT fthr[2], OBJECT *target,  OBJECT *crs, BOOLEAN2 ok, BOOLEAN2 need_expand,
OBJECT *enclose, BOOLEAN2 fcr)
{ OBJECT y, tag, ylink, yield, ytag, zlink;
  OBJECT res, z, firsttag, firstres = nilobj;

  /* make sure left parameter (the tag) is in order */
  debug0(DOM, DD, "  manifesting CASE now");
  Child(tag, Down(x));
  debug1(DOM, DD, "  manifesting CASE tag %s now", EchoObject(tag));
  tag = Manifest(tag, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
  &nenclose, fcr);
  tag = ReplaceWithTidy(tag, ACAT_TIDY);

  /* make sure the right parameter is an ACAT */
  Child(y, LastDown(x));
  if( objectOfType(y, YIELD) )
  { New(z, ACAT);
    MoveLink(Up(y), z, PARENT);
    Link(x, z);
    y = z;
  }
  if( !objectOfType(y, ACAT) )
  { Error(8, 7, "%s deleted (right parameter is malformed)",
      WARN, &fpos(y), KW_CASE);
    y = MakeWord(WORD, STR_EMPTY, &fpos(x));
    ReplaceNode(y, x);  DisposeObject(x);
    x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    return x;
  }

  /* hunt through right parameter for res, the selected case */
  res = nilobj;  firsttag = nilobj;
  for( ylink = Down(y);  ylink != y && res == nilobj;  ylink = NextDown(ylink) )
  { Child(yield, ylink);
    if( objectOfType(yield, GAP_OBJ) )  continue;
    if( !objectOfType(yield, YIELD) )
    { Error(8, 8, "%s expected here", WARN, &fpos(yield), KW_YIELD);
      break;
    }
    Child(ytag, Down(yield));
    ytag = Manifest(ytag, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
      &nenclose, fcr);
    ytag = ReplaceWithTidy(ytag, ACAT_TIDY);
    if( is_word(type(ytag)) )
    { if( firsttag == nilobj )
      {	firsttag = ytag;
	Child(firstres, LastDown(yield));
      }
      if( (is_word(type(tag)) && StringEqual(string(ytag), string(tag))) ||
	     StringEqual(string(ytag), STR_ELSE)  )
      {	Child(res, LastDown(yield));
	break;
      }
    }
    else if( objectOfType(ytag, ACAT) )
    { z = ytag;
      for( zlink = Down(z);  zlink != z;  zlink = NextDown(zlink) )
      {	Child(ytag, zlink);
	if( objectOfType(ytag, GAP_OBJ) )  continue;
	if( !is_word(type(ytag)) )
	{ Error(8, 9, "error in left parameter of %s",
	    WARN, &fpos(ytag), KW_YIELD);
	  break;
        }
        if( firsttag == nilobj )
        { firsttag = ytag;
	  Child(firstres, LastDown(yield));
        }
        if( (is_word(type(tag)) && StringEqual(string(ytag), string(tag)))
	        || StringEqual(string(ytag), STR_ELSE) )
        { Child(res, LastDown(yield));
	  break;
        }
      }
    }
    else Error(8, 10, "error in left parameter of %s",
	   WARN, &fpos(ytag), KW_YIELD);
  }
  if( res == nilobj )
  { if( firsttag != nilobj )
    { Error(8, 11, "replacing unknown %s option %s by %s",
	WARN, &fpos(tag), KW_CASE, string(tag), string(firsttag));
      res = firstres;
      debug1(DGP, D, "  res = %s", EchoObject(res));
    }
    else
    { Error(8, 12, "%s deleted (choice %s unknown)",
	WARN, &fpos(tag), KW_CASE, string(tag));
      y = MakeWord(WORD, STR_EMPTY, &fpos(x));
      ReplaceNode(y, x);  DisposeObject(x);
      x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      return x;
    }
  }

  /* now manifest the result and replace x with it */
  DeleteLink(Up(res));
  ReplaceNode(res, x);
  DisposeObject(x);
  x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
  return x;
} /* ManifestCase */


/*@::ManifestTg@**************************************************************/
/*                                                                           */
/*  OBJECT ManifestTg(x,env,style,bthr, fthr, target, crs, ok, need_expand,  */
/*                    enclose, fcr)                                          */
/*                                                                           */
/*  This procedure implements Manifest (see below) when x is TAGGED.         */
/*                                                                           */
/*****************************************************************************/

#pragma clang diagnostic ignored "-Wunused-parameter"
static OBJECT ManifestTg(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
OBJECT fthr[2], OBJECT *target, OBJECT *crs, BOOLEAN2 ok, BOOLEAN2 need_expand,
OBJECT *enclose, BOOLEAN2 fcr)
{ OBJECT y, tag, z;

  /* make sure first argument is a cross-reference */
  assert( Down(x) != x && NextDown(Down(x)) != x &&
	NextDown(NextDown(Down(x))) == x, "Manifest TAGGED: children!" );
  Child(y, Down(x));
  if( !is_cross(type(y)) )
  {
    y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, TRUE);
    if( !is_cross(type(y)) )
    { Error(8, 13, "left parameter of %s is not a cross reference",
        WARN, &fpos(y), KW_TAGGED);
      y = MakeWord(WORD, STR_EMPTY, &fpos(x));
      ReplaceNode(y, x);  DisposeObject(x);
      x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      return x;
    }
  }

  /* make sure the arguments of the cross-reference are OK */
  Child(z, Down(y));
  if( !objectOfType(z, CLOSURE) )
  { Error(8, 14, "left parameter of %s must be a symbol",
      WARN, &fpos(y), KW_TAGGED);
    y = MakeWord(WORD, STR_EMPTY, &fpos(x));
    ReplaceNode(y, x);  DisposeObject(x);
    x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    return x;
  }
  if( !has_tag(actual(z)) )
  { Error(8, 15, "symbol %s not allowed here (it has no %s)",
      WARN, &fpos(z), SymName(actual(z)), KW_TAG);
    y = MakeWord(WORD, STR_EMPTY, &fpos(x));
    ReplaceNode(y, x);  DisposeObject(x);
    x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    return x;
  }
  Child(z, NextDown(Down(y)));
  z = Manifest(z, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
  z = ReplaceWithTidy(z, ACAT_TIDY);
  if( is_word(type(z)) && StringEqual(string(z), KW_PRECEDING) )
    cross_type(y) = CROSS_PREC;
  else if( is_word(type(z)) && StringEqual(string(z), KW_FOLLOWING) )
    cross_type(y) = CROSS_FOLL;
  else if( is_word(type(z)) && StringEqual(string(z), KW_FOLL_OR_PREC) )
    cross_type(y) = CROSS_FOLL_OR_PREC;
  else
  { Error(8, 16, "%s, %s or %s expected in left parameter of %s",
      WARN, &fpos(z), KW_PRECEDING, KW_FOLLOWING, KW_FOLL_OR_PREC, KW_TAGGED);
    y = MakeWord(WORD, STR_EMPTY, &fpos(x));
    ReplaceNode(y, x);  DisposeObject(x);
    x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    return x;
  }

  /* make sure second argument (the new key) is ok */
  Child(tag, LastDown(x));
  tag = Manifest(tag, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
  tag = ReplaceWithTidy(tag, WORD_TIDY); /* && */
  if( !is_word(type(tag)) )
  { Error(8, 17, "right parameter of %s must be a simple word",
      WARN, &fpos(tag), KW_TAGGED);
    ifdebug(DOM, DD, DebugObject(tag));
    y = MakeWord(WORD, STR_EMPTY, &fpos(x));
    ReplaceNode(y, x);  DisposeObject(x);
    x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    return x;
  }

  /* assemble insinuated cross reference which replaces x */
  ReplaceNode(tag, z);
  DisposeObject(z);
  ReplaceNode(y, x);
  DisposeObject(x);
  x = y;
  ReplaceWithSplit(x, bthr, fthr);
  debug1(DCR, DD, "  tagged manifesting %s", EchoObject(x));
  return x;
} /* end ManifestTg */


/*@::ManifestCl@**************************************************************/
/*                                                                           */
/*  OBJECT ManifestCl(x,env,style,bthr, fthr, target, crs, ok, need_expand,  */
/*                    enclose, fcr)                                          */
/*                                                                           */
/*  This procedure implements Manifest (see below) when x is CLOSURE.        */
/*                                                                           */
/*****************************************************************************/

static OBJECT ManifestCl(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
OBJECT fthr[2], OBJECT *target, OBJECT *crs, BOOLEAN2 ok, BOOLEAN2 need_expand,
OBJECT *enclose, BOOLEAN2 fcr)
{ OBJECT y, link, sym, res_env, hold_env, hold_env2, z, newz, command;
  BOOLEAN2 symbol_free;

  sym = actual(x);
  StyleCopy(&save_style(x), style);
  debugcond2(DOM, DD, StringEqual(SymName(sym), "@Section"),
     "manifesting %s at %s", SymName(sym), EchoFilePos(&fpos(x)));
  debug1(DOM, DD,  "  [ manifesting closure %s", SymName(sym));

  /* enclose, if required */
  if( *enclose != nilobj && (actual(x)==GalleySym || actual(x)==ForceGalleySym) )
  { OBJECT sym, par;
    ReplaceNode(*enclose, x);
    Child(sym, Down(*enclose));
    Child(par, Down(sym));
    DisposeChild(Down(par));
    Link(par, x);
    x = *enclose;
    *enclose = nilobj;
    debug1(DHY, DD, "  Manifest/enclose: %s", EchoObject(x));
    debug1(DOM, DD, "  Manifest/enclose: %s", EchoObject(x));
    x = Manifest(x, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    debug0(DOM, DD,  "  ] returning from manifesting closure (enclose)");
    return x;
  }

  /* expand parameters where possible, and find if they are all free */
  symbol_free = TRUE;
  debugcond1(DOM, DD, indefinite(sym), "  freeing %s", EchoObject(x));
  for( link = Down(x);  link != x;  link = NextDown(link) )
  { Child(y, link);
    assert( objectOfType(y, PAR), "Manifest/CLOSURE: type(y) != PAR!" );
    Child(z, Down(y));

    /* try to evaluate the actual parameter z */
    if( !is_word(type(z)) && !has_par(actual(y)) )
    {
      if( is_tag(actual(y)) || is_key(actual(y)) )
      {	z = Manifest(z, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
	z = ReplaceWithTidy(z, WORD_TIDY);
	if( !is_word(type(z)) )
	{
	  debug2(ANY, D, "z = %s %s", Image(type(z)), EchoObject(z));
	  Error(8, 41, "this %s is not a sequence of one or more words", FATAL,
	    &fpos(y), SymName(actual(y)));
	}
      }
      else if( objectOfType(z, NEXT) )
      {	z = Manifest(z, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
	z = ReplaceWithTidy(z, ACAT_TIDY);
      }
      else if( objectOfType(z, CLOSURE) && is_par(type(actual(z))) )
      {
        /* see whether z would come to something simple if expanded */
        newz = ParameterCheck(z, env);
        debugcond2(DOM, DD, indefinite(sym), "  ParameterCheck(%s, env) = %s",
	  EchoObject(z), EchoObject(newz));
        if( newz != nilobj )
        { ReplaceNode(newz, z);
	  DisposeObject(z);
	  z = newz;
        }
      }
    }

    if( !is_word(type(z)) )
    { symbol_free = FALSE;
    }
  }
  debugcond2(DOM, DD, indefinite(sym),"  s_f = %s, x = %s",
    bool2s(symbol_free), EchoObject(x));

  /* if all parameters are free of symbols, optimize environment */
  if( symbol_free && imports(sym) == nilobj && enclosing(sym) != StartSym )
  { y = SearchEnv(env, enclosing(sym));
    if( y != nilobj && objectOfType(y, CLOSURE) )
    { OBJECT prntenv;
      Parent(prntenv, Up(y));
      assert(objectOfType(prntenv, ENV), "Manifest: prntenv!");
      if( Down(prntenv) == LastDown(prntenv) )
      { env = prntenv;
      }
      else
      { debug0(DCR, DDD, "calling SetEnv from Manifest (a)");
        env = SetEnv(y, nilobj);
      }
      New(hold_env2, ACAT);  Link(hold_env2, env);
    }
    else
    { /* *** letting this through now
      if( has_par(enclosing(sym)) )
	Error(8, 18, "symbol %s used outside %s", WARN, &fpos(x), SymName(sym),
	  SymName(enclosing(sym)));
      *** */
      hold_env2 = nilobj;
    }
  }
  else hold_env2 = nilobj;

  debug3(DOM, DD, " expansion: has_target %s, indefinite %s, recursive %s",
    bool2s(has_target(sym)), bool2s(indefinite(sym)), bool2s(recursive(sym)));
  if( has_target(sym) && !need_expand )
  {
    /* convert symbols with targets to unsized galleys */
    OBJECT hd;
    New(hd, HEAD);
    FposCopy(fpos(hd), fpos(x));
    actual(hd) = sym;
    limiter(hd) = opt_components(hd) = opt_constraints(hd) = nilobj;
    gall_dir(hd) = horiz_galley(sym);
    ready_galls(hd) = nilobj;
    must_expand(hd) = TRUE;
    sized(hd) = FALSE;
    seen_nojoin(hd) = FALSE;
    ReplaceNode(hd, x);
    Link(hd, x);
    AttachEnv(env, x);
    SetTarget(hd);
    enclose_obj(hd) = (has_enclose(sym) ? BuildEnclose(hd) : nilobj);
    ClearHeaders(hd);
    x = hd;
    threaded(x) = bthr[COLM_E] != nilobj || fthr[COLM_E] != nilobj;
    ReplaceWithSplit(x, bthr, fthr);
    debug3(DGA, D, "  manifesting %sgalley %s at %s",
      force_gall(hd) ? "force " : "", SymName(actual(hd)),
      EchoFilePos(&fpos(hd)));
  }
  else if(
	    *target == sym			  ? (*target = nilobj, TRUE) :
	    need_expand				  ? TRUE  :
	    uses_galley(sym) && !recursive(sym)   ? TRUE  :
	    !indefinite(sym) && !recursive(sym)   ? TRUE  :
	    indefinite(sym)  && *target != nilobj ? SearchUses(sym, *target)
						  : FALSE
	 )
  {
    /* expand the closure and manifest the result */
    debug1(DOM, DD, "expanding; style: %s", EchoStyle(style));
    debug0(DCE, DD, "  calling ClosureExpand from Manifest/CLOSURE");
    /* *** now requesting cross refs always, not only if ok
    x = ClosureExpand(x, env, ok, crs, &res_env);
    *** */
    x = ClosureExpand(x, env, TRUE, crs, &res_env);
    New(hold_env, ACAT);  Link(hold_env, res_env);
    debug1(DOM, DD, "recursive call; style: %s", EchoStyle(style));
    if( objectOfType(x, FILTERED) )
    { assert( objectOfType(sym, RPAR), "ManifestCl/filtered: type(sym)!" );
      assert( filter(enclosing(sym)) != nilobj, "ManifestCl filter-encl!" );
      New(command, CLOSURE);
      FposCopy(fpos(command), fpos(x));
      actual(command) = filter(enclosing(sym));
      FilterSetFileNames(x);
      command = Manifest(command,env,style,nbt,nft,&ntarget,crs,FALSE,FALSE, &nenclose, fcr);
      command = ReplaceWithTidy(command, WORD_TIDY);
      if( !is_word(type(command)) )
	Error(8, 19, "filter parameter of %s symbol is not simple",
	  FATAL, &fpos(command), SymName(enclosing(sym)));
      y = FilterExecute(x, string(command), res_env);
      debug2(DFH, D, "after \"%s\", will manifest result with style %s",
	string(command), EchoStyle(style));
      DisposeObject(command);
      ReplaceNode(y, x);
      DisposeObject(x);
      x = y;
    }
    x = Manifest(x, res_env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
    DisposeObject(hold_env);
  }
  else
  {
    AttachEnv(env, x);
    threaded(x) = bthr[COLM_E] != nilobj || fthr[COLM_E] != nilobj;
    debug0(DOM, DD,  "  closure; calling ReplaceWithSplit");
    ReplaceWithSplit(x, bthr, fthr);
  }
  if( hold_env2 != nilobj )  DisposeObject(hold_env2);
  debug0(DOM, DD,  "  ] returning from manifesting closure");
  return x;
} /* end ManifestCl */


/*@::Manifest()@**************************************************************/
/*                                                                           */
/*  OBJECT Manifest(x, env, style, bthr, fthr, target, crs, ok, need_expand, */
/*                  enclose, fcr)                                            */
/*                                                                           */
/*  Manifest object x, interpreted in environment env and style style.       */
/*  The result replaces x, and is returned also.                             */
/*  The manifesting operation converts x from a pure parse tree object       */
/*  containing closures and no threads, to an object ready for sizing,       */
/*  with fonts propagated to the words, fill styles propagated to the        */
/*  ACATs, and line spacings propagated to all interested parties.           */
/*  All non-recursive, non-indefinite closures are expanded.                 */
/*  Threads joining objects on a mark are constructed, and SPLIT objects     */
/*  inserted, so that sizing becomes a trivial operation.                    */
/*                                                                           */
/*  Manifest will construct threads and pass them up as children of bthr[]   */
/*  and fthr[] whenever non-nilobj values of these variables are passed in:  */
/*                                                                           */
/*      bthr[COLM]           protrudes upwards from x                        */
/*      fthr[COLM]           protrudes downwards from x                      */
/*      bthr[ROWM]           protrudes leftwards from x                      */
/*      fthr[ROWM]           protrudes rightwards from x                     */
/*                                                                           */
/*  If *target != nilobj, Manifest will expand indefinite closures leading   */
/*  to the first @Galley lying within an object of type *target.             */
/*                                                                           */
/*  If *target != nilobj and *enclose != nilobj, Manifest will enclose       */
/*  any @Galley or @ForceGalley it comes across in *enclose.                 */
/*                                                                           */
/*  The env parameter contains the environment in which x is to be           */
/*  evaluated.  Environments are shared, so their correct disposal is not    */
/*  simple.  The rule is this:  the code which creates an environment, or    */
/*  detaches it, is responsible for holding it with a dummy parent until     */
/*  it is no longer required.                                                */
/*                                                                           */
/*  Some objects x are not "real" in the sense that they do not give rise    */
/*  to rectangles in the final printed document.  The left parameter of      */
/*  @Wide and similar operators, and the gap following a concatenation       */
/*  operator, are examples of such non-real objects.  The ok flag is true    */
/*  when x is part of a real object.  This is needed because some things,    */
/*  such as the insinuation of cross references, the breaking of             */
/*  lines @Break ACAT objects, and conversion to small capitals, only apply  */
/*  to real objects.                                                         */
/*                                                                           */
/*  If *crs != nilobj, it points to a list of indexes to cross-references    */
/*  which are to be insinuated into the manifested form of x if x is real.   */
/*                                                                           */
/*  If need_expand is TRUE it forces closure x to expand.                    */
/*                                                                           */
/*  If fcr is TRUE, the objective is to expand until a cross-reference is    */
/*  the result; so expansion will stop at a CROSS or FORCE_CROSS object.     */
/*                                                                           */
/*  A postcondition of Manifest() is that the underline() flag is set to     */
/*  either UNDER_ON or UNDER_OFF in every WORD, every QWORD, and every child */
/*  of every ACAT, including the gaps.  This can be verified by checking     */
/*  that the WORD and QWORD cases set underline() to UNDER_OFF, and the ACAT */
/*  case sets every child of the ACAT to UNDER_OFF.  To see that the correct */
/*  subset of these flags gets changed to UNDER_ON, consult SetUnderline().  */
/*  The underline() flag is undefined otherwise, and should have value       */
/*  UNDER_UNDEF.                                                             */
/*                                                                           */
/*****************************************************************************/
#define MAX_DEPTH 2000

OBJECT Manifest(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
OBJECT fthr[2], OBJECT *target, OBJECT *crs, BOOLEAN2 ok, BOOLEAN2 need_expand,
OBJECT *enclose, BOOLEAN2 fcr)
{ OBJECT bt[2], ft[2], y, link, nextlink, gaplink, g, gword;
  register FULL_CHAR *p;
  OBJECT res = nilobj, res_env, res_env2, hold_env, hold_env2, z, prev;
  OBJECT link1, link2, x1, x2, y1, y2, vc, value_env, key, value;
  int i, par, num1, num2;  GAP res_gap;  unsigned res_inc;  STYLE new_style;
  #pragma clang diagnostic ignored "-Wunused-but-set-variable"
  BOOLEAN2 done, multiline;
  FULL_CHAR ch;
  float scale_factor;
  static int depth = 0;
#if DEBUG_ON
  static OBJTYPE debug_type[MAX_DEPTH];
  static OBJECT	      debug_actual[MAX_DEPTH];
  static int	      debug_lnum[MAX_DEPTH];
  BOOLEAN2 eee = (*enclose != nilobj);
  debug_type[depth] = type(x);
  debug_lnum[depth] = line_num(fpos(x));
  if( objectOfType(x, CLOSURE) ) debug_actual[depth] = actual(x);
  depth++;
  if( depth == MAX_DEPTH )
  { Error(8, 20, "maximum depth of symbol expansion (%d) reached",
      WARN, &fpos(x), MAX_DEPTH);
    Error(8, 21, "the symbols currently being expanded are:", WARN, &fpos(x));
    while( --depth >= 0 )
    {
      Error(8, 22, "at %d: %d %s %s", WARN, &fpos(x), depth, debug_lnum[depth],
	Image(debug_type[depth]), sameObjType(debug_type[depth], CLOSURE) ?
	  FullSymName(debug_actual[depth], AsciiToFull(".")) : STR_EMPTY);
    }
    Error(8, 23, "exiting now", FATAL, &fpos(x));
  }
#else
  depth++;
  if( depth == MAX_DEPTH )
  {
    Error(8, 40, "maximum depth of symbol expansion (%d) reached",
      FATAL, &fpos(x), MAX_DEPTH);
  }
#endif

  debug1(DOM, DD,   "[Manifest(%s)", Image(type(x)));
  debug0(DOM, DD,  "  object: ");
  ifdebug(DOM, DD, DebugObject(x));
  debug1(DOM, DD,  "  environment: %s", EchoObject(env));
  debug6(DOM, DD,  "  style: %s;  target: %s;  threads: %s%s%s%s",
	EchoStyle(style), SymName(*target),
	bthr[COLM_E] ? " up"    : "",  fthr[COLM_E] ? " down"  : "",
	bthr[ROWM_E] ? " left"  : "",  fthr[ROWM_E] ? " right" : "");
  debugcond2(DHY, DD, eee, "[ Manifest(%s, *enclose = %s)",
    EchoObject(x), EchoObject(*enclose));

  switch( type(x).objtype )
  {

    case ENV_OBJ_E:

      debug0(DHY, DD, "[Manifest env_obj:");
      ifdebug(DHY, DD, DebugObject(x));
      Child(y, Down(x));
      Child(res_env, NextDown(Down(x)));
      assert( objectOfType(res_env, ENV), "Manifest/ENV_OBJ: res_env!");
      y = Manifest(y, res_env, style, bthr, fthr, target, crs, ok, TRUE, enclose, fcr);
      /* we always expand children of ENV_OBJ (need_expand == TRUE) */
      ReplaceNode(y, x);
      DisposeObject(x);
      x = y;
      debug1(DHY, DD, "]Manifest env_obj returning %s", EchoObject(x));
      break;


    case CLOSURE_E:
    
      x = ManifestCl(x, env, style, bthr, fthr, target, crs, ok, need_expand, enclose, fcr);
      break;


    case PAGE_LABEL_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, WORD_TIDY);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case NULL_CLOS_E:

      StyleCopy(&save_style(x), style);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case CROSS_E:
    case FORCE_CROSS_E:
    
      assert( Down(x) != x && LastDown(x) != Down(x), "Manifest: CROSS child!");
      if( !fcr )  /* stop if fcr, i.e. if purpose was to find a cross-reference */
      {
        debug0(DCR, DD, "  calling CrossExpand from Manifest/CROSS");
        Child(y, Down(x));
        if( objectOfType(y, CLOSURE) )
        {
	  /* *** want cross ref now always, not only if ok
	  x = CrossExpand(x, env, style, ok, crs, &res_env);
	  *** */
	  x = CrossExpand(x, env, style, crs, &res_env);
          assert( objectOfType(x, CLOSURE), "Manifest/CROSS: type(x)!" );
          New(hold_env, ACAT);  Link(hold_env, res_env);
          /* expand here (calling Manifest immediately makes unwanted cr) */
          debug0(DCE, DD, "  calling ClosureExpand from Manifest/CROSS");
          x = ClosureExpand(x, res_env, FALSE, crs, &res_env2);
          New(hold_env2, ACAT);  Link(hold_env2, res_env2);
          x = Manifest(x, res_env2, style, bthr, fthr, target, crs, ok, TRUE, enclose, fcr);
          DisposeObject(hold_env);
          DisposeObject(hold_env2);
        }
        else
        { y = MakeWord(WORD, STR_EMPTY, &fpos(x));
          ReplaceNode(y, x);
          DisposeObject(x);
          x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
        }
      }
      break;


    case WORD_E:
    case QWORD_E:
    
      /* *** patched by JeffK 17/10/06 as suggested by Ludovic Courtes *** */
      /* if( !ok || *crs == nilobj ) */
      if( !ok )
      {	word_font(x) = font(style);
	word_colour(x) = colour(style);
	word_underline_colour(x) = underline_colour(style);
	word_texture(x) = texture(style);
	word_outline(x) = outline(style);
	word_language(x) = language(style);
	word_baselinemark(x) = baselinemark(style);
	word_strut(x) = strut(style);
	word_ligatures(x) = ligatures(style);
	word_hyph(x) = hyph_style(style).hyphstyle == HYPH_ON_E;
	debug3(DOM, DDD, "  manfifest/WORD underline() := %s for %s %s",
	  "UNDER_OFF", Image(type(x)), EchoObject(x));
	if( small_caps(style) && ok )  x = MapSmallCaps(x, style);  /* unreachable */
	setUnderline(x, UNDER_OFF);
	ReplaceWithSplit(x, bthr, fthr);
	break;
      }
      New(y, ACAT);
      FposCopy(fpos(y), fpos(x));
      ReplaceNode(y, x);
      Link(y, x);  x = y;
      /* NB NO BREAK! */


    case ACAT_E:
    
      StyleCopy(&save_style(x), style);
      adjust_cat(x) = padjust(style);
      StyleCopy(&new_style, style);
      setPadjust(&new_style, FALSE);
      assert(Down(x) != x, "Manifest: ACAT!" );
      link = Down(x);  Child(y, link);
      assert( !objectOfType(y, GAP_OBJ), "Manifest ACAT: GAP_OBJ is first!" );
      multiline = FALSE;

      /* manifest first child and insert any cross references */
      if( is_word(type(y)) )
      { word_font(y) = font(style);
	word_colour(y) = colour(style);
	word_underline_colour(y) = underline_colour(style);
	word_texture(y) = texture(style);
	word_outline(y) = outline(style);
	word_language(y) = language(style);
	word_baselinemark(y) = baselinemark(style);
	word_strut(y) = strut(style);
	word_ligatures(y) = ligatures(style);
	word_hyph(y) = hyph_style(style).hyphstyle == HYPH_ON_E;
	if( small_caps(style) && ok )  y = MapSmallCaps(y, style);
      }
      else y = Manifest(y, env, &new_style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      debug3(DOM, DDD, "  manfifest/ACAT1 underline() := %s for %s %s",
	"UNDER_OFF", Image(type(y)), EchoObject(y));
      setUnderline(y, UNDER_OFF);
      /* ??? if( is_word(type(y)) ) */
      if( ok && *crs != nilobj )
      {	
	debug1(DCR, DD, "  insinuating %s", EchoObject(*crs));
	TransferLinks(Down(*crs), *crs, link);
	DisposeObject(*crs);
	*crs = nilobj;
      }
      prev = y;

      /* manifest subsequent gaps and children */
      for( gaplink = Down(link);  gaplink != x;  gaplink = NextDown(link) )
      {
	Child(g, gaplink);
	assert( objectOfType(g, GAP_OBJ), "Manifest ACAT: no GAP_OBJ!" );
        debug3(DOM, DDD, "  manfifest/ACAT2 underline() := %s for %s %s",
	  "UNDER_OFF", Image(type(g)), EchoObject(g));
        setUnderline(g, UNDER_OFF);
	link = NextDown(gaplink);
	assert( link != x, "Manifest ACAT: GAP_OBJ is last!" );
	Child(y, link);
	assert( !objectOfType(y, GAP_OBJ), "Manifest ACAT: double GAP_OBJ!" );

	/* manifest the next child */
        debug1(DOM, DD, "  in ACAT (3), style = %s", EchoStyle(style));
	if( is_word(type(y)) )
	{ word_font(y) = font(style);
	  word_colour(y) = colour(style);
	  word_underline_colour(y) = underline_colour(style);
	  word_texture(y) = texture(style);
	  word_outline(y) = outline(style);
	  word_language(y) = language(style);
	  word_baselinemark(y) = baselinemark(style);
	  word_strut(y) = strut(style);
	  word_ligatures(y) = ligatures(style);
	  word_hyph(y) = hyph_style(style).hyphstyle == HYPH_ON_E;
	  if( small_caps(style) && ok )  y = MapSmallCaps(y, style);
	}
	else y = Manifest(y, env, &new_style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
        debug3(DOM, DDD, "  manifest/ACAT3 underline() := %s for %s %s",
	  "UNDER_OFF", Image(type(y)), EchoObject(y));
        setUnderline(y, UNDER_OFF);

	/* manifest the gap object */
	if( Down(g) != g )
	{
	  /* explicit & operator whose value is the child of g */
	  Child(z, Down(g));
	  z = Manifest(z, env, &new_style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
	  z = ReplaceWithTidy(z, ACAT_TIDY);
	  GetGap(z, style, &gap(g), &res_inc);
	  vspace(g) = hspace(g) = 0;
	}
	else
	{
	  /* implicit & operator */
	  GapCopyOnRef(&gap(g), space_gap_ref(style));
	  switch( space_style(style).spacestyle )
	  {
	    case SPACE_LOUT_E:

	      /* usual Lout spacing, the number of white space characters */
	      setWidth(&gap(g), width(&gap(g)) * (vspace(g) + hspace(g)));
	      break;


	    case SPACE_COMPRESS_E:

	      /* either zero or one space */
	      if( vspace(g) + hspace(g) == 0 )
	      { setWidth(&gap(g), 0);
	      }
	      else
	      { /* else width is like one space, so OK as is */
	      }
	      break;


	    case SPACE_SEPARATE_E:

	      /* exactly one space always, so do nothing further */
	      break;


	    case SPACE_TROFF_E:

	      /* Lout spacing plus one extra space for sentence end at eoln */
	      setWidth(&gap(g), width(&gap(g)) * (vspace(g) + hspace(g)));
	      debugcond2(DLS, DD, vspace(g) > 0, "  prev = %s %s",
		Image(type(prev)), EchoObject(prev));
	      if( vspace(g) > 0 )
	      { 
		/* set z to the preceding object; may need to search ACATs! */
		z = prev;
		while( objectOfType(z, ACAT)
		       || objectOfType(z, ONE_COL) || objectOfType(z, ONE_ROW)
		       || objectOfType(z, HCONTRACT) || objectOfType(z, VCONTRACT) )
		{ Child(z, LastDown(z));
		}

		/* if preceding object is a word, check for end sentence */
		if( is_word(type(z)) )
		{
		  for( p = string(z);  *p != '\0';  p++ )
      ;
		  debug4(DLS, DD, "  prev = %s, last = %c, LSE = %s, LWES = %s",
		    EchoObject(z), *(p-1), bool2s(LanguageSentenceEnds[*(p-1)]),
		    bool2s(LanguageWordEndsSentence(z, FALSE)));
		  if( p != string(z) && LanguageSentenceEnds[*(p-1)]
		      && LanguageWordEndsSentence(z, FALSE) )
		    setWidth(&gap(g), width(&gap(g)) + width(space_gap_ref(style)));
		}
	      }
	      break;


	    case SPACE_TEX_E:

	      if( vspace(g) + hspace(g) == 0 )
	      {
		/* zero spaces gives zero result, as for compress above */
		setWidth(&gap(g), 0);
	      }
	      else
	      {
	        /* set z to the preceding object; may need to search ACATs! */
	        z = prev;
		while( objectOfType(z, ACAT)
		       || objectOfType(z, ONE_COL) || objectOfType(z, ONE_ROW)
		       || objectOfType(z, HCONTRACT) || objectOfType(z, VCONTRACT) )
	        { Child(z, LastDown(z));
	        }

	        /* one extra space if preceding is word ending sentence */
	        if( is_word(type(z)) )
	        {
		  for( p = string(z);  *p != '\0';  p++ )
      ;
		  debug4(DLS, DD, "  prev = %s, last = %c, LSE = %s, LWES = %s",
		      EchoObject(z), *(p-1), bool2s(LanguageSentenceEnds[*(p-1)]),
		      bool2s(LanguageWordEndsSentence(z, TRUE)));
		  if( p != string(z) && LanguageSentenceEnds[*(p-1)]
		      && LanguageWordEndsSentence(z, TRUE) )
		    setWidth(&gap(g), width(&gap(g)) + width(space_gap_ref(style)));
	        }
	      }
	      break;


	    default:

	      assert(FALSE, "Manifest: unexpected space_style!");
	      break;
	  }
	  setNobreak(&gap(g), (width(&gap(g)) == 0));
	  if( line_breaker(g) && is_definite(type(y)) )  multiline = TRUE;
	}
        debug1(DOM, DD, "  in ACAT, gap = %s", EchoLength(width(&gap(g))));

	/* compress adjacent juxtaposed words of equal font, etc. */
	if( is_word(type(y)) && width(&gap(g)) == 0 && nobreak(&gap(g)) &&
	    vspace(g)+hspace(g)==0 &&
	    gapHasUnit(&gap(g), FIXED_UNIT) && spaceMode(&gap(g), EDGE_MODE) &&
	    prev != nilobj && is_word(type(prev)) && !mark(&gap(g)) &&
	    word_font(prev) == word_font(y) &&
	    word_colour(prev) == word_colour(y) &&
	    word_underline_colour(prev) == word_underline_colour(y) &&
	    word_texture(prev) == word_texture(y) &&
	    word_outline(prev) == word_outline(y) &&
	    word_language(prev) == word_language(y) &&
	    word_baselinemark(prev) == word_baselinemark(y) &&
	    word_strut(prev) == word_strut(y) &&
	    word_ligatures(prev) == word_ligatures(y) )
	    /* no need to compare underline() since both are false */
	{ OBJTYPE typ;
	  assert( objectHasUnderline(prev, UNDER_OFF), "Manifest/ACAT: underline(prev)!" );
	  assert( objectHasUnderline(y, UNDER_OFF), "Manifest/ACAT: underline(y)!" );
	  if( StringLength(string(prev))+StringLength(string(y)) >= MAX_WORD )
	    Error(8, 24, "word %s%s is too long",
	      FATAL, &fpos(prev), string(prev), string(y));
	  z = y;
	  typ = objectOfType(prev, QWORD) || objectOfType(y, QWORD) ? QWORD : WORD;
	  y = MakeWordTwo(typ, string(prev), string(y), &fpos(prev));
	  word_font(y) = word_font(prev);
	  word_colour(y) = word_colour(prev);
	  word_underline_colour(y) = word_underline_colour(prev);
	  word_texture(y) = word_texture(prev);
	  word_outline(y) = word_outline(prev);
	  word_language(y) = word_language(prev);
	  word_baselinemark(y) = word_baselinemark(prev);
	  word_strut(y) = word_strut(prev);
	  word_ligatures(y) = word_ligatures(prev);
	  word_hyph(y) = word_hyph(prev);
	  setUnderline(y, UNDER_OFF);
          debug3(DOM, DDD, "  manifest/ACAT4 underline() := %s for %s %s",
	    "UNDER_OFF", Image(type(y)), EchoObject(y));
	  MoveLink(link, y, CHILD);
	  DisposeObject(z);
	  DisposeChild(Up(prev));
	  DisposeChild(gaplink);
	}
	prev = y;

	/* insinuate any cross-references */
	if( ok && *crs != nilobj )
	{
	  debug1(DCR, DD, "  insinuating %s", EchoObject(*crs));
	  TransferLinks(Down(*crs), *crs, link);
	  DisposeObject(*crs);
	  *crs = nilobj;
	}
      }
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case HCAT_E:
    case VCAT_E:

     x = ManifestCat(x, env, style, bthr, fthr, target, crs, ok, need_expand,
       enclose, fcr);
     break;


    case WIDE_E:
    case HIGH_E:
    
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
	&nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      num1 = GetWidth(y, style);
      SetConstraintOnRef(&constraint(x), MAX_FULL_LENGTH, num1, MAX_FULL_LENGTH);
      DisposeChild(Down(x));
      goto ETC;		/* two cases down from here */


    case HSHIFT_E:
    case VSHIFT_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      GetGap(y, style, shift_gap_ref(x), &res_inc);
      setShift_type(x, res_inc);
      if( !spaceMode(shift_gap_ref(x), EDGE_MODE) || 
	  (!gapHasUnit(shift_gap_ref(x), FIXED_UNIT) && !gapHasUnit(shift_gap_ref(x), NEXT_UNIT)) )
      {	Error(8, 27, "replacing invalid left parameter of %s by +0i",
	  WARN, &fpos(y), Image(type(x)) );
	setShift_type(x, GAP_INC);
	setUnits(shift_gap_ref(x), FIXED_UNIT);
	setWidth(shift_gap_ref(x), 0);
	setMode(shift_gap_ref(x), EDGE_MODE);
      }
      DisposeChild(Down(x));
      goto ETC;		/* next case down from here */


    case HCONTRACT_E:
    case VCONTRACT_E:
    case HLIMITED_E:
    case VLIMITED_E:
    case HEXPAND_E:
    case VEXPAND_E:
    case ONE_COL_E:
    case ONE_ROW_E:
    
      ETC:
      par = (objectOfType(x, ONE_COL) || objectOfType(x, HEXPAND) || objectOfType(x, HCONTRACT) ||
	   objectOfType(x, HLIMITED) || objectOfType(x, WIDE) || objectOfType(x, HSHIFT)) ? COLM_E : ROWM_E;
      Child(y, Down(x));

      /* manifest the child, propagating perp threads and suppressing pars */
      bt[par] = ft[par] = nilobj;
      bt[1-par] = bthr[1-par];  ft[1-par] = fthr[1-par];
      y = Manifest(y, env, style, bt, ft, target, crs, ok, FALSE, enclose, fcr);

      /* replace with split object if par threads needed */
      bt[par] = bthr[par];  ft[par] = fthr[par];
      bt[1-par] = ft[1-par] = nilobj;
      ReplaceWithSplit(x, bt, ft);
      break;


    case BEGIN_HEADER_E:
    case SET_HEADER_E:

      /* first manifest gap, which is left parameter */
      debug1(DGS, D, "[ Manifest(%s)", EchoObject(x));
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
	&nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      GetGap(y, style, line_gap_ref(&save_style(x)), &res_inc);

      /* make vc, a joined VCAT of MAX_HCOPIES copies of the header */
      Child(y, LastDown(x));
      DeleteLink(Up(y));
      New(vc, VCAT);
      Link(vc, y);
      for( i = 1;  i < MAX_HCOPIES;  i++ )
      {
	/* make new gap object and link to vc */
	New(g, GAP_OBJ);
	setMark(&gap(g), FALSE);
	setJoin(&gap(g), TRUE);
	FposCopy(fpos(g), fpos(y));
	gword = MakeWord(WORD, STR_EMPTY, &fpos(g));
	Link(g, gword);
	Link(vc, g);

	/* copy y and link to vc */
	z = CopyObject(y, &fpos(y));
	Link(vc, z);
      }
      ifdebug(DGS, D, DebugObject(x));
      
      /* manifest vc */
      vc = Manifest(vc, env, style, bthr, fthr, target, crs, ok, need_expand,
	enclose, fcr);

      /* make the MAX_HCOPIES children of vc into children of header */
      assert(objectOfType(vc, VCAT), "Manifest/BEGIN_HEADER: vc!");
      for( link = Down(vc);  link != vc;  link = nextlink )
      {
	nextlink = NextDown(link);
	Child(z, link);
	if( !objectOfType(z, GAP_OBJ) )
	  MoveLink(link, x, PARENT);
      }
      /* DisposeObject(vc); */
      debug0(DGS, D, "] Manifest returning");
      /* ifdebug(DGS, D, DebugObject(x)); */
      break;


    case END_HEADER_E:
    case CLEAR_HEADER_E:

      /* give these objects a dummy child, just so that threads can attach */
      /* to it and keep the thread code happy.  Don't use ReplaceWithSplit */
      /* because we don't want a split above a header                      */
      y = MakeWord(WORD, STR_EMPTY, &fpos(x));
      Link(x, y);
      y = Manifest(y, env, style, bthr, fthr, target, crs, ok, need_expand,
	enclose, fcr);
      break;


    case HSPAN_E:
    case VSPAN_E:

      ReplaceWithSplit(x, bthr, fthr);
      break;


    case ROTATE_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      GetGap(y, style, &res_gap, &res_inc);
      if( res_inc != GAP_ABS || !spaceMode(&res_gap, EDGE_MODE) ||
		!gapHasUnit(&res_gap, DEG_UNIT) )
      {	Error(8, 28, "replacing invalid left parameter of %s by 0d",
	  WARN, &fpos(y), Image(type(x)) );
	setUnits(&res_gap, DEG_UNIT);
	setWidth(&res_gap, 0);
      }
      sparec(constraint(x)) = width(&res_gap);
      DisposeChild(Down(x));
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE,enclose,fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case BACKGROUND_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE,enclose,fcr);
      Child(y, LastDown(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE,enclose,fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case START_HVSPAN_E:
    case START_HSPAN_E:
    case START_VSPAN_E:
    case HMIRROR_E:
    case VMIRROR_E:
    case HSCALE_E:
    case VSCALE_E:
    case HCOVER_E:
    case VCOVER_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE,enclose,fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case SCALE_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      if( is_word(type(y)) && StringEqual(string(y), STR_EMPTY) )
      {
	/* missing scale factor, meaning to be inserted automatically */
        bc(constraint(x)) = fc(constraint(x)) = 0;  /* work out later */
	bfc(constraint(x)) = 0;
      }
      else if( is_word(type(y)) && StringEqual(string(y), STR_SCALE_DOWN) )
      {
	/* scale factor "downifneeded", meaning to be inserted automatically */
        bc(constraint(x)) = fc(constraint(x)) = 0;  /* work out later */
	bfc(constraint(x)) = -1;
      }
      else if( !objectOfType(y, ACAT) )
      {
	/* presumably one word, common factor for horizontal and vertical */
	scale_factor = GetScaleFactor(y);
        bc(constraint(x)) = fc(constraint(x)) = scale_factor * SF;
      }
      else
      {
	/* get horizontal scale factor */
	Child(z, Down(y));
	scale_factor = GetScaleFactor(z);
        bc(constraint(x)) = scale_factor * SF;

	/* get vertical scale factor */
	Child(z, LastDown(y));
	scale_factor = GetScaleFactor(z);
        fc(constraint(x)) = scale_factor * SF;
      }
      DisposeChild(Down(x));
      Child(y, LastDown(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case KERN_SHRINK_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      Child(y, LastDown(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case YIELD_E:

      Error(8, 29, "%s not expected here", FATAL, &fpos(x), KW_YIELD);
      break;


    case RAW_VERBATIM_E:
    case VERBATIM_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      DeleteLink(Down(x));
      MergeNode(y, x);  x = y;
      break;


    case CASE_E:

      x = ManifestCase(x,env,style, bthr, fthr, target, crs, ok, need_expand, enclose, fcr);
      break;


    case BACKEND_E:

      res = MakeWord(WORD, BackEnd->name, &fpos(x));
      ReplaceNode(res, x);
      DisposeObject(x);
      x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      break;


    case XCHAR_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      if( !is_word(type(y)) )
      {	Error(8, 30, "%s dropped (parameter is not a simple word)",
	  WARN, &fpos(y), KW_XCHAR);
	res = MakeWord(WORD, STR_EMPTY, &fpos(x));
      }
      else if( (word_font(y) = font(style)) == 0 )
      {	Error(8, 31, "%s dropped (no current font at this point)",
	  WARN, &fpos(y), KW_XCHAR);
	res = MakeWord(WORD, STR_EMPTY, &fpos(x));
      }
      else
      { ch = MapCharEncoding(string(y), FontMapping(word_font(y), &fpos(y)));
        if( ch == '\0' )
        { setType(y, QWORD);
	  Error(8, 32, "%s dropped (character %s unknown in font %s)",
	    WARN, &fpos(y), KW_XCHAR, StringQuotedWord(y),
	    FontFamilyAndFace(word_font(y)));
	  res = MakeWord(WORD, STR_EMPTY, &fpos(x));
        }
        else
        { res = MakeWord(QWORD, STR_SPACE, &fpos(x));
	  string(res)[0] = ch;
        }
      }
      ReplaceNode(res, x);
      DisposeObject(x);
      x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      break;


    case CURR_LANG_E:

      if( language(style) == 0 )
      { Error(8, 33, "no current language at this point, using %s",
	  WARN, &fpos(x), STR_NONE);
	res = MakeWord(WORD, STR_NONE, &fpos(x));
      }
      else res = MakeWord(WORD, LanguageString(language(style)), &fpos(x));
      ReplaceNode(res, x);
      DisposeObject(x);
      x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      break;


    case CURR_FAMILY_E:
    case CURR_FACE_E:

      if( font(style) == 0 )
      { Error(8, 38, "no current font at this point, using %s",
	  WARN, &fpos(x), STR_NONE);
	res = MakeWord(WORD, STR_NONE, &fpos(x));
      }
      else if( objectOfType(x, CURR_FAMILY) )
	res = MakeWord(WORD, FontFamily(font(style)), &fpos(x));
      else
	res = MakeWord(WORD, FontFace(font(style)), &fpos(x));
      ReplaceNode(res, x);
      DisposeObject(x);
      x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      break;


    case CURR_YUNIT_E:
    case CURR_ZUNIT_E:

      { FULL_CHAR buff[20];
        if( objectOfType(x, CURR_YUNIT) )
          sprintf( (char *) buff, "%dp", yunit(style) / PT);
        else
	  sprintf( (char *) buff, "%dp", zunit(style) / PT);
        res = MakeWord(WORD, buff, &fpos(x));
      }
      ReplaceNode(res, x);
      DisposeObject(x);
      x = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      break;


    case UNDERLINE_E:

      /* change x to an ACAT */
      assert(Down(x) != x && NextDown(Down(x)) == x, "Manifest: UNDERLINE!");
      setType(x, ACAT);
      adjust_cat(x) = padjust(style);
      setPadjust(style, FALSE);
      StyleCopy(&save_style(x), style);

      /* manifest x's sole child and set underline flags in the child */
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok,FALSE,enclose,fcr);
      SetUnderline(x);
      ReplaceWithSplit(x, bthr, fthr);
      break;


    case FONT_E:
    case SPACE_E:
    case YUNIT_E:
    case ZUNIT_E:
    case BREAK_E:
    case COLOUR_E:
    case UNDERLINE_COLOUR_E:
    case TEXTURE_E:
    case LANGUAGE_E:
    
      assert( Down(x) != x && NextDown(Down(x)) != x, "Manifest: FONT!" );
      StyleCopy(&new_style, style);
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
	&nenclose, fcr);
      switch( type(x).objtype )
      {
	case FONT_E:

	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  FontChange(&new_style, y);
	  break;

	case SPACE_E:

	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  SpaceChange(&new_style, y);
	  break;

	case YUNIT_E:

	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  YUnitChange(&new_style, y);
	  break;

	case ZUNIT_E:

	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  ZUnitChange(&new_style, y);
	  break;

	case BREAK_E:

	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  BreakChange(&new_style, y);
	  break;
	
	case COLOUR_E:

	  y = ReplaceWithTidy(y, WORD_TIDY);
	  ColourChange(&new_style, y);
	  break;

	case UNDERLINE_COLOUR_E:
	  
	  y = ReplaceWithTidy(y, WORD_TIDY);
	  ColourUnderlineChange(&new_style, y);
	  break;

	case TEXTURE_E:
	  
	  y = ReplaceWithTidy(y, PARA_TIDY);
	  TextureChange(&new_style, y);
	  break;

	case LANGUAGE_E:
	  
	  y = ReplaceWithTidy(y, ACAT_TIDY);
	  LanguageChange(&new_style, y);
	  break;

  default:
    // do nothing
    ;

      } /* end inner switch */
      DisposeChild(Down(x));
      Child(y, Down(x));
      y = Manifest(y, env, &new_style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      DeleteLink(Down(x));
      MergeNode(y, x);  x = y;
      break;


    case SET_CONTEXT_E:

      /* check that we have a valid YIELD node for left parameter */
      debug0(DOM, D, " entering @SetContext");
      Child(y, Down(x));
      if( !objectOfType(y, YIELD) )
	Error(8, 33, "left parameter of @SetContext is not obj @Yield obj",
	  FATAL, &fpos(x));
      assert(Down(y) != y && NextDown(Down(y)) == LastDown(y),
	"@Yield in @SetContext");

      /* unlink key and manifest it */
      Child(key, Down(y));
      DeleteLink(Down(y));
      key = Manifest(key, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
	&nenclose, fcr);
      key = ReplaceWithTidy(key, WORD_TIDY);
      if( !is_word(type(key)) )
	Error(8, 33, "@SetContext: key is not a simple word", FATAL,&fpos(key));
      debug1(DOM, D, " @SetContext: `key' argument: %s", string(key));

      /* unlink value but don't manifest it */
      Child(value, Down(y));
      DeleteLink(Down(y));
      debug1(DOM, D, " @SetContext: `value' argument: type %s",
	Image(type(value)));
      debug0(DOM, D, " @SetContext: parameters fetched");

      /* get the right parameter's value */
      Child(z, LastDown(x));

      /* memorize the key, value, style and environment for use when */
      /* manifesting VALUE in `@GetContext'.  */
      StyleCopy(&new_style, style);
      context_key(*context_ref(&new_style)) = key;
      context_value(*context_ref(&new_style)) = value;
      context_style(*context_ref(&new_style)) = style;
      context_env(*context_ref(&new_style)) = env;

      ReplaceNode(z, x);
      DisposeObject(x);
      x = Manifest(z, env, &new_style, bthr, fthr, target, crs, ok,
	FALSE, enclose, fcr);
      break;


    case GET_CONTEXT_E:

      assert( Down(x) != x, "Manifest: GET_CONTEXT!" );
      Child(y, Down(x));
      y = ReplaceWithTidy(y, WORD_TIDY);
      value_env = env;
      if( is_word(type(y)) )
      { STYLE *s; OBJECT value = nilobj; int found = 0;

	debug1(DOM, D, " @GetContext %s", string(y));

	/* iterate over the contexts until one that contains the key being */
	/* looked for (currently Y) is found.  */
	for( s = style; s != NULL; )
	{
	  CONTEXT *ctx = context_ref(s);
	  if( !ctx )
	  { s = NULL;
	  }
	  else if( context_key(*ctx) != nilobj
		   && (StringEqual(string(context_key(*ctx)), string(y))) )
	  {
	    value = context_value(*ctx), found = TRUE;

	    /* VALUE is to be manifested with the style associated to CTX */
	    StyleCopy(&new_style, style);
	    setContext(&new_style, context_ref(context_style(*ctx)));
	    debug3(DOM, D, " @GetContext %s -> value has type %s (%p)", string(y),
	      Image(type(value)), value);

	    /* same for the environment */
	    value_env = context_env(*ctx);
	    break;
	  }
	  else s = context_style(*ctx);
	}

	if( !found )
	{ Error(8, 33, "no value for context variable `%s', using the empty string",
	    WARN, &fpos(x), string(y));
	  res = MakeWord(WORD, STR_EMPTY, &fpos(x));
	  StyleCopy(&new_style, style);
	}
	else res = CopyObject(value, &fpos(value));
      }
      else
      { Error(8, 33, "%s dropped (right parameter is not a simple word)",
	  WARN, &fpos(x), KW_GET_CONTEXT);
	res = MakeWord(WORD, STR_EMPTY, &fpos(x));
	StyleCopy(&new_style, style);
      }

      ReplaceNode(res, x);
      DisposeObject(x);

      /* manifest the context value under the style and environment that */
      /* were in effect at the `@SetContext' invocation point.  */
      x = Manifest(res, value_env, &new_style, bthr, fthr, target, crs,
	ok, FALSE, enclose, fcr);
      break;


    case OUTLINE_E:
    case PADJUST_E:
    case HADJUST_E:
    case VADJUST_E:

      StyleCopy(&new_style, style);
      if(      objectOfType(x, OUTLINE) )  setOutline(&new_style, TRUE);
      else if( objectOfType(x, VADJUST) )  setVadjust(&new_style, TRUE);
      else if( objectOfType(x, HADJUST) )  setHadjust(&new_style, TRUE);
      else                           setPadjust(&new_style, TRUE);
      Child(y, Down(x));
      y = Manifest(y, env, &new_style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      DeleteLink(Down(x));
      MergeNode(y, x);  x = y;
      break;


    case MELD_E:
    case COMMON_E:
    case RUMP_E:

      assert( Down(x) != x && NextDown(Down(x)) != x, "Manifest: COMMON!" );
      debug2(DOM, D, "[Manifest %s %s", EchoObject(x), EchoObject(env));

      /* find the first child of x, make sure it is an ACAT, and manifest */
      Child(x1, Down(x));
      if( !objectOfType(x1, ACAT) )
      { OBJECT newx1;
	New(newx1, ACAT);
        adjust_cat(newx1) = padjust(style);
	setPadjust(style, FALSE);
        MoveLink(Down(x), newx1, CHILD);
        Link(newx1, x1);
        x1 = newx1;
      }
      x1 = Manifest(x1, env, style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      link1 = x1;
      while( NextDown(link1) != x1 )
      { Child(z, NextDown(link1));
	if( objectOfType(z, ACAT) )
	{ TransferLinks(Down(z), z, NextDown(link1));
	  DisposeChild(Up(z));
	}
	else link1 = NextDown(link1);
      }
      debug1(DOM, D, "  manifested x1 = %s", EchoObject(x1));
 
      /* find the second child of x, make sure it is an ACAT, and manifest */
      Child(x2, NextDown(Down(x)));
      if( !objectOfType(x2, ACAT) )
      { OBJECT newx2;
	New(newx2, ACAT);
        adjust_cat(newx2) = padjust(style);
	setPadjust(style, FALSE);
        MoveLink(NextDown(Down(x)), newx2, CHILD);
        Link(newx2, x2);
        x2 = newx2;
      }
      x2 = Manifest(x2, env, style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      link2 = x2;
      while( NextDown(link2) != x2 )
      { Child(z, NextDown(link2));
	if( objectOfType(z, ACAT) )
	{ TransferLinks(Down(z), z, NextDown(link2));
	  DisposeChild(Up(z));
	}
	else link2 = NextDown(link2);
      }
      debug1(DOM, D, "  manifested x2 = %s", EchoObject(x2));
     
      if( objectOfType(x, MELD) )
      {
        /* if Meld, result is Meld(x1, x2) */
        res = Meld(x1, x2);
      }
      else
      {

        /* find the point where x1 and x2 begin to differ */
        link1 = Down(x1);
        link2 = Down(x2);
        while( link1 != x1 && link2 != x2 )
        {
	  Child(y1, link1);
	  Child(y2, link2);
	  debug1(DOM, D, "    y1 = %s", EchoObject(y1));
	  debug1(DOM, D, "    y2 = %s", EchoObject(y2));
	  if( !EqualManifested(y1, y2) )
	    break;
	  link1 = NextDown(link1);
	  link2 = NextDown(link2);
        }

        /* if COMMON, result is x1 or x2 if either ran out,             */
        /* or else x2 (say) up to but not including link2 and prec gap  */
        if( objectOfType(x, COMMON) )
        { if( link2 == x2 )
	  { res = x2;
	  }
	  else if( link1 == x1 )
	  { res = x1;
	  }
	  else
	  { if( link2 == Down(x2) )
	      res = MakeWord(WORD, STR_EMPTY, &fpos(x2));
	    else
	    { TransferLinks(PrevDown(link2), x2, x1);
	      res = x2;
	    }
	  }
        }

        /* if RUMP, result is x2 starting from link2 or NextDown(link2) */
        else if( objectOfType(x, RUMP) )
        { if( link2 == x2 )
	    res = MakeWord(WORD, STR_EMPTY, &fpos(x2));
	  else if( link1 == x1 )
	  { 
	    TransferLinks(Down(x2), NextDown(link2), x1);
	    res = x2;
	  }
	  else /* link1 != x1 */
	  {
	    TransferLinks(Down(x2), link2, x1);
	    res = x2;
	  }
        }
      }

      /* now res replaces x */
      ReplaceNode(res, x);
      DisposeObject(x);
      x = res;
      ReplaceWithSplit(x, bthr, fthr);
      debug1(DOM, D, "]Manifest returning %s", EchoObject(x));
      break;


    case INSERT_E:

      /* manifest and detach the left parameter, call it z */
      Child(z, Down(x));
      z = Manifest(z, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      DeleteLink(Down(x));

      /* manifest the right parameter and make it the result */
      Child(y, LastDown(x));
      y = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      DeleteLink(LastDown(x));
      MergeNode(y, x);  x = y;

      /* now find the reattachment point for z down inside the result, x */
      x = InsertObject(x, &z, style);
      if( z != nilobj )
      { Error(8, 34, "object dropped by %s: no suitable insert point", WARN,
	  &fpos(x), KW_INSERT);
	DisposeObject(z);
      }
      break;


    case ONE_OF_E:

      Child(y, Down(x));
      if( !objectOfType(y, ACAT) )
      {
	/* child is not a sequence of choices, so ignore ONE_OF */
	Error(8, 39, "%s ignored: no choices in right parameter", WARN,
	  &fpos(x), KW_ONE_OF);
        y = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE,
	      enclose, fcr);
        DeleteLink(Down(x));
        MergeNode(y, x);  x = y;
      }
      else
      {
	/* try each child in turn; result is first to find *target */
	OBJECT target_before;
	for( link = Down(y);  link != y;  link = NextDown(link) )
	{
	  Child(z, link);
	  if( objectOfType(z, GAP_OBJ) )  continue;
	  target_before = *target;
	  z = Manifest(z, env, style, bthr, fthr, target, crs, ok, FALSE,
	    enclose, fcr);
	  if( *target != target_before )
	    break;
	}
	DeleteLink(Up(z));
	ReplaceNode(z, x);
	DisposeObject(x);
	x = z;
      }
      break;


    case NEXT_E:

      assert( Down(x) != x, "Manifest/NEXT: Down(x) == x!" );
      Child(y, Down(x));
      debug1(DCS, DD, "  Manifesting Next( %s, 1 )", EchoObject(y));
      y = Manifest(y, env, style, bthr, fthr, target, crs, FALSE, FALSE, enclose, fcr);
      debug1(DCS, DD, "  calling Next( %s, 1 )", EchoObject(y));
      done = FALSE;
      y = Next(y, 1, &done);
      debug2(DCS, DD, "  Next(done = %s) returning %s",
			bool2s(done), EchoObject(y));
      DeleteLink(Down(x));
      MergeNode(y, x);  x = y;
      break;


    case PLUS_E:
    case MINUS_E:

      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, ACAT_TIDY);
      Child(z, NextDown(Down(x)));
      z = Manifest(z, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      z = ReplaceWithTidy(z, ACAT_TIDY);
      if( is_word(type(y)) && sscanf( (char *) string(y), "%d", &num1) == 1 &&
          is_word(type(z)) && sscanf( (char *) string(z), "%d", &num2) == 1 )
      {
	FULL_CHAR buff[MAX_WORD];
	sprintf( (char *) buff, "%d", objectOfType(x, PLUS) ? num1+num2 : num1-num2);
	res = MakeWord(WORD, buff, &fpos(x));
      }
      else
      { res = MakeWord(WORD, (FULL_CHAR *) "???", &fpos(x));
      }
      debug4(DOM, DD, "{ %s } %s { %s } = %s", EchoObject(y), Image(type(x)),
	EchoObject(z), EchoObject(res));
      res = Manifest(res, env, style, bthr, fthr, target, crs, FALSE, FALSE, enclose, fcr);
      ReplaceNode(res, x);
      DisposeObject(x);
      x = res;
      break;


    case OPEN_E:

      debug0(DCR, DD, "  [ Manifest/OPEN begins:");
      Child(y, Down(x));
      DeleteLink(Down(x));
      Child(res, LastDown(x));
      hold_env = nilobj;
      if( objectOfType(y, CLOSURE) )
      { AttachEnv(env, y);
	StyleCopy(&save_style(y), style);
	debug0(DCR, DDD, "calling SetEnv from Manifest (b)");
	res_env = SetEnv(y, nilobj);
	New(hold_env, ACAT);  Link(hold_env, res_env);
	res = Manifest(res, res_env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      }
      else if( is_cross(type(y)) )
      { Child(z, Down(y));
	if( objectOfType(z, CLOSURE) )
	{ debug0(DCR, DD, "  calling CrossExpand from Manifest/OPEN");
	  /* *** want cross ref now always, not only if ok
	  y = CrossExpand(y, env, style, ok, crs, &res_env);
	  *** */
	  y = CrossExpand(y, env, style, crs, &res_env);
	  AttachEnv(res_env, y);
	  debug0(DCR, DDD, "calling SetEnv from Manifest (c)");
	  res_env = SetEnv(y, env);
	  New(hold_env, ACAT);  Link(hold_env, res_env);
	  res = Manifest(res, res_env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
	}
	else
	{ Error(8, 35, "invalid left parameter of %s", WARN, &fpos(y), KW_OPEN);
	  res = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
	}
      }
      else
      {	Error(8, 36, "invalid left parameter of %s", WARN, &fpos(y), KW_OPEN);
	res = Manifest(res, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
      }
      ReplaceNode(res, x);
      DisposeObject(x);
      if( hold_env != nilobj )  DisposeObject(hold_env);
      x = res;
      debug0(DCR, DD, "  ] Manifest/OPEN ends");
      break;


    case TAGGED_E:

      x = ManifestTg(x, env, style, bthr, fthr, target, crs, ok, need_expand, enclose, fcr);
      debug2(DCR, DD, "Manifest returning %ld %s", (long) x, EchoObject(x));
      break;


    case PLAIN_GRAPHIC_E:
    case GRAPHIC_E:

      debug1(DRS, DD, "  graphic style in Manifest = %s", EchoStyle(style));
      Child(y, LastDown(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok, FALSE, enclose, fcr);
      StyleCopy(&save_style(x), style);
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      ReplaceWithSplit(x, bthr, fthr);
      break;
	

    case LINK_SOURCE_E:
    case LINK_DEST_E:
    case LINK_URL_E:

      /* save_mark(x) = 0; */
      Child(y, LastDown(x));
      y = Manifest(y, env, style, nbt, nft, target, crs, ok,FALSE,enclose,fcr);
      StyleCopy(&save_style(x), style);
      if( objectOfType(x, LINK_DEST) && is_indefinite(type(y)) )
	setType(x, LINK_DEST_NULL);
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE,
	&nenclose, fcr);
      y = ReplaceWithTidy(y, WORD_TIDY);
      ReplaceWithSplit(x, bthr, fthr);
      break;
	

    case INCGRAPHIC_E:
    case SINCGRAPHIC_E:

      StyleCopy(&save_style(x), style);
      debug2(DGP, DD, "  manifest at %s (style %s)",
	EchoObject(x), EchoStyle(&save_style(x)));
      Child(y, Down(x));
      y = Manifest(y, env, style, nbt, nft, &ntarget, crs, FALSE, FALSE, &nenclose, fcr);
      y = ReplaceWithTidy(y, WORD_TIDY);
      if( !is_word(type(y)) )
      { Error(8, 37, "%s deleted (invalid right parameter)", WARN, &fpos(y),
	  objectOfType(x, INCGRAPHIC) ? KW_INCGRAPHIC : KW_SINCGRAPHIC);
	y = MakeWord(WORD, STR_EMPTY, &fpos(x));
	ReplaceNode(y, x);  DisposeObject(x);
	x = Manifest(y, env, style, bthr, fthr, target, crs, ok, FALSE, enclose, fcr);
	return x;
      }
      ReplaceWithSplit(x, bthr, fthr);
      break;
	

    default:

      assert1(FALSE, "Manifest:", Image(type(x)));
      break;

  } /* end switch */

  debug2(DOM, DD, "]Manifest returning %s %s", Image(type(x)), EchoObject(x));
  debug1(DOM, DD, "  at exit, style = %s", EchoStyle(style));
  debug1(DOM, DDD, "up:    ", EchoObject(bthr[COLM_E]));
  debug1(DOM, DDD, "down:  ", EchoObject(fthr[COLM_E]));
  debug1(DOM, DDD, "left:  ", EchoObject(bthr[ROWM_E]));
  debug1(DOM, DDD, "right: ", EchoObject(fthr[ROWM_E]));
  debugcond1(DHY, DD, eee, "] Manifest returning %s", EchoObject(x));
  depth--;
  return x;
} /* end Manifest */
