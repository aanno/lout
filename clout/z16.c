/*@z16.c:Size Adjustment:SetNeighbours(), CatAdjustSize()@********************/
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
/*  FILE:         z16.c                                                      */
/*  MODULE:       Size Adjustment                                            */
/*  EXTERNS:      FindShift(), SetNeighbours(), AdjustSize()                 */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"


/*****************************************************************************/
/*                                                                           */
/*  FULL_LENGTH FindShift(x, y, dim)                                         */
/*                                                                           */
/*  x = @HShift y or @VShift y depending on dim.  FindShift returns the      */
/*  length of the shift measured from the mark of y to the mark of x.        */
/*  This is negative if the mark of y is to the right of the mark of x.      */
/*                                                                           */
/*****************************************************************************/

FULL_LENGTH FindShift(OBJECT x, OBJECT y, DIM_TE dim)
{ FULL_LENGTH len = 0, res = 0;  /* initial values unused */
  debug4(DSF, DD, "FindShift(%s, %s %s, %s)", Image(type(x)),
    Image(type(y)), EchoObject(y), dimen(dim));

  /* first determine the magnitude of the shift */
  switch( units(shift_gap_ref(x)).unit )
  {
    case FIXED_UNIT_E:	len = width(shift_gap_ref(x));
			break;

    case NEXT_UNIT_E:	len = (size(y, dim) * width(shift_gap_ref(x))) / FR;
			break;

    default:		assert(FALSE, "FindShift: units");
			break;
  }

  /* then calculate the shift depending on the shift type */
  switch( shift_type(x) )
  {
    case GAP_ABS:	res = len - back(y, dim);
			break;

    case GAP_INC:	res = len;
			break;

    case GAP_DEC:	res = - len;
			break;

    default:		assert(FALSE, "FindShift: type");
			break;
  }

  debug1(DSF, DD, "FindShift returning %s", EchoLength(res));
  return res;
} /* end FindShift */


/*****************************************************************************/
/*                                                                           */
/*  SetNeighbours(link, ratm, pg, pdef, sg, sdef, side)                      */
/*                                                                           */
/*  This is a utility routine used by CatConstrained(), AdjustSize(),        */
/*  BreakTable() and FlushGalley() for calculating size updates in objects.  */
/*  Assuming that link is the link of a component of a VCAT etc., and that   */
/*  ratm is TRUE if there is a marked component to the right of link, set    */
/*                                                                           */
/*     pg    to the gap separating link from the first definite object       */
/*           to the left, or nilobj if none.  If pg != nilobj, set pdef to   */
/*           the preceding definite object;  else pdef is undefined.         */
/*                                                                           */
/*     sg    to the gap separating link from the first definite object       */
/*           to the right, or nilobj if none.  if sg != nilobj, set sdef to  */
/*           the succeeding definite object;  else sdef is undefined.        */
/*                                                                           */
/*     side  to the side of the mark link is on; either BACK, ON or FWD.     */
/*                                                                           */
/*****************************************************************************/

void SetNeighbours(OBJECT link, BOOLEAN2 ratm, OBJECT *pg, OBJECT *pdef,
OBJECT *sg, OBJECT *sdef, int *side)
{ OBJECT plink, slink;

  /* find preceding definite; if it exists, set *pg */
  *pg = nilobj;
  for( plink = PrevDown(link);  objectOfType(plink, LINK);  plink = PrevDown(plink) )
  { Child(pdef, plink);
    if( objectOfType(*pdef, SPLIT) ? SplitIsDefinite(*pdef) : is_definite(type(*pdef)) )
    { Child(pg, PrevDown(link));
      while( is_index(type(*pg)) )
      {	link = PrevDown(link);
	Child(pg, PrevDown(link));
      }
      assert( objectOfType(*pg, GAP_OBJ), "SetNeighbours: type(*pg)!" );
      break;
    }
  }

  /* find succeeding definite; if it exists, set *sg */
  *sg = nilobj;
  for( slink = NextDown(link);  objectOfType(slink, LINK);  slink = NextDown(slink) )
  { Child(sdef, slink);
    if( objectOfType(*sdef, SPLIT) ? SplitIsDefinite(*sdef) : is_definite(type(*sdef)) )
    { Child(sg, PrevDown(slink));
      while( is_index(type(*sg)) )
      {	slink = PrevDown(slink);
	Child(sg, PrevDown(slink));
      }
      assert( objectOfType(*sg, GAP_OBJ), "SetNeighbours: type(*sg)!" );
      break;
    }
  }

  *side = ratm ? BACK : *pg == nilobj || mark(&gap(*pg)) ? ON : FWD;
  debug4(DSA, DD,
    "SetNeighbours: ratm == %s, pg %s nilobj, sg %s nilobj, side == %s",
    bool2s(ratm), *pg == nilobj ? "==" : "!=", *sg == nilobj ? "==" : "!=", 
    *side == BACK ? "BACK" : *side == ON ? "ON" : "FWD");
} /* end SetNeighbours */


/*****************************************************************************/
/*                                                                           */
/*  static CatAdjustSize(x, b, f, ratm, y, dim)                              */
/*                                                                           */
/*  Adjust the size of x to be *b, *f.  Object x is known to lie in add-set  */
/*  y;  ratm is TRUE iff there is a mark to the right of x.  Return the      */
/*  new size of y in *b, *f.                                                 */
/*                                                                           */
/*****************************************************************************/

static void CatAdjustSize(OBJECT x, FULL_LENGTH *b, FULL_LENGTH *f, BOOLEAN2 ratm,
OBJECT y, DIM_TE dim)
{ OBJECT link;
  OBJECT pg, prec_def, sg, sd;
  FULL_LENGTH beffect, feffect, seffect;  int side;
  int bb = 0, ff = 0;  /* initial values unused */

  debug6(DSA, DD, "CatAdjustSize(%s x, %s, %s, %s, %s y, %s)", Image(type(x)),
    EchoLength(*b), EchoLength(*f), bool2s(ratm), Image(type(y)), dimen(dim));
  debug2(DSA,DD, "x(%s,%s) =", EchoLength(back(x,dim)), EchoLength(fwd(x,dim)));
  ifdebug(DSA, DD, DebugObject(x));
  debug2(DSA,DD, "y(%s,%s) =", EchoLength(back(y,dim)), EchoLength(fwd(y,dim)));
  ifdebug(DSA, DD, DebugObject(y));

  /* DO_ADJUST ACAT is a special case because adjustment affects its size */
  if( sameDim(dim, COLM) && objectOfType(y, ACAT) && display_style(&save_style(y)) == DO_ADJUST_E )
  { setBack(x, dim, *b);  setFwd(x, dim, *f);
    *b = back(y, dim);  *f = fwd(y, dim);
    debug2(DSA, DD, "CatAdjustSize ACAT %s,%s", EchoLength(*b), EchoLength(*f));
    return;
  }

  link = UpDim(x, dim);
  SetNeighbours(link, ratm, &pg, &prec_def, &sg, &sd, &side);
  { ifdebug(DSA, DD,
    if( pg != nilobj && spaceMode(&gap(pg), NO_MODE) )
    { debug1(DSA, DD, "NO_MODE gap pg, is_indefinite(x) == %s, y =",
	bool2s(is_indefinite(type(x))) );
      ifdebug(DSA, DD, DebugObject(y));
    }
    if( sg != nilobj && spaceMode(&gap(sg), NO_MODE) )
    { debug1(DSA, DD, "NO_MODE gap sg, is_indefinite(x) == %s, y =",
	bool2s(is_indefinite(type(x))) );
      ifdebug(DSA, DD, DebugObject(y));
    }
  ); }
  if( is_indefinite(type(x)) )
  {
    beffect = pg == nilobj ? *b :
      MinGap(fwd(prec_def, dim), *b, *f, &gap(pg));

    feffect = sg == nilobj ? *f :
      MinGap(*f, back(sd, dim), fwd(sd, dim), &gap(sg));

    seffect = pg == nilobj ? sg == nilobj ? 0 : back(sd, dim) :
      sg == nilobj ? fwd(prec_def, dim) :
      MinGap(fwd(prec_def, dim), back(sd,dim), fwd(sd,dim), &gap(sg));
  }
  else /* !is_indefinite(type(x)) */
  {
    beffect = pg == nilobj ?  *b - back(x, dim) :
      MinGap(fwd(prec_def, dim), *b,           *f,          &gap(pg)) -
      MinGap(fwd(prec_def, dim), back(x, dim), fwd(x, dim), &gap(pg));

    feffect = sg == nilobj ? *f - fwd(x, dim) :
      MinGap(*f,          back(sd, dim), fwd(sd, dim), &gap(sg)) -
      MinGap(fwd(x, dim), back(sd, dim), fwd(sd, dim), &gap(sg));
	
    seffect = 0;
  }

  debug3(DSA, D, "  pg = %s, sg = %s, side = %s",
    pg == nilobj ? AsciiToFull("<nil>") : EchoGap(&gap(pg)),
    sg == nilobj ? AsciiToFull("<nil>") : EchoGap(&gap(sg)), Image4Constraints(side));
  debug3(DSA, D, "  beffect = %s, feffect = %s, seffect = %s",
    EchoLength(beffect), EchoLength(feffect), EchoLength(seffect));
  setBack(x, dim, *b);  setFwd(x, dim, *f);
  switch( side )
  {
    case BACK:	bb = back(y, dim) + beffect + feffect - seffect;
		ff = fwd(y, dim);
		break;

    case ON:	bb = back(y, dim) + beffect - seffect;
		ff = fwd(y, dim) + feffect;
		break;

    case FWD:	bb = back(y, dim);
		ff = fwd(y, dim) + beffect + feffect - seffect;
		break;
  }
  *b = bb;  *f = ff;
  debug2(DSA, DD, "CatAdjustSize returning %s,%s", EchoLength(*b), EchoLength(*f));
} /* end CatAdjustSize */


/*@::AdjustSize()@************************************************************/
/*                                                                           */
/*  AdjustSize(x, b, f, dim)                                                 */
/*                                                                           */
/*  Adjust the size of object x, in dimension dim, to be b, f.  If x is a    */
/*  CLOSURE, the adjustment is from a CLOSURE to a definite object of size   */
/*  b, f.                                                                    */
/*                                                                           */
/*****************************************************************************/

void AdjustSize(OBJECT x, FULL_LENGTH b, FULL_LENGTH f, DIM_TE dim)
{ OBJECT y, link, tlink, lp, rp, z, index;
  BOOLEAN2 ratm;  FULL_LENGTH tb, tf, cby, cfy, rby, rfy;
  BOOLEAN2 is_rotate;

  SetLengthDim(dim);
  debug6(DSA, D, "[ AdjustSize( %s(%s,%s), %s, %s, %s ), x =",
	objectOfType(x, CLOSURE) ? SymName(actual(x)) : Image(type(x)),
	EchoLength(back(x, dim)), EchoLength(fwd(x, dim)),
	EchoLength(b), EchoLength(f), dimen(dim));
  ifdebug(DSA, DD, DebugObject(x) );
  is_rotate = objectOfType(x, ROTATE);

  while( b != back(x, dim) || f != fwd(x, dim) || is_indefinite(type(x)) )
  { assert( Up(x) != x, "AdjustSize: Up(x) == x!" );
    if (b < 0) {
      fprintf(stderr,
        "b %d < 0, back(x, dim %d) = %d, type(x) %d is_rotate %d, declared %s:%d\n",
        b, dim.dim, back(x, dim), type(x).objtype, is_rotate, malloc_oalloc_file_name(x), malloc_oalloc_line_num(x));
      ifdebug(DSA, D, DebugObject(x));
    }
    if (f < 0) {
      fprintf(stderr,
        "f %d < 0, fwd(x, dim %d) = %d, type(x) %d is_rotate %d, declared %s:%d\n",
        f, dim.dim, fwd(x, dim), type(x).objtype, is_rotate, malloc_oalloc_file_name(x), malloc_oalloc_line_num(x));
      ifdebug(DSA, D, DebugObject(x));
    }
    if (b < 0 || f < 0) {
      OBJECT p;
      Parent(p, Up(x));
      fprintf(stderr, "  Up type %d declared %s:%d\n", type(Up(x)).objtype, malloc_oalloc_file_name(Up(x)), malloc_oalloc_line_num(Up(x)));
      fprintf(stderr, "  Parent type %d declared %s:%d\n", type(p).objtype, malloc_oalloc_file_name(p), malloc_oalloc_line_num(p));
    }
    if( b < 0 && !is_rotate)
      Error(16, 5, "back < 0; cannot recover from earlier errors", FATAL, &fpos(x));
    if (f < 0 && !is_rotate)
      Error(16, 5, "fwd < 0 and not rotate; cannot recover from earlier errors", FATAL, &fpos(x));

    /* these cases are unique because they have multiple parents */
    if( objectOfType(x, COL_THR) || objectOfType(x, ROW_THR) )
    { assert( (objectOfType(x, COL_THR)) == (sameDim(dim, COLM)), "AdjustSize: COL_THR!" );
      setBack(x, dim, b);  setFwd(x, dim, f);
      for( link = Up(x);  link != x;  link = NextUp(link) )
      { Parent(y, link);
	assert( objectOfType(y, SPLIT), "AdjustSize: type(y) != SPLIT!") ;
	AdjustSize(y, b, f, dim);
      }
      debug0(DSA, D, "] AdjustSize (thread case) returning.");
      return;
    }

    link = UpDim(x, dim);  ratm = FALSE;
    for( tlink=NextDown(link);  objectOfType(tlink, LINK);  tlink=NextDown(tlink) )
    { Child(&y, tlink);
      if( objectOfType(y, GAP_OBJ) && mark(&gap(y)) )  ratm = TRUE;
    }
    y = tlink;

    debug5(DSA, D, "  b = %s, f = %s, y = %s(%s,%s), x =",
	EchoLength(b), EchoLength(f), Image(type(y)),
	EchoLength(back(y, dim)), EchoLength(fwd(y, dim)));
    ifdebug(DSA, DD, DebugObject(x) );

    switch( type(y).objtype )
    {

      case HEAD_E:
      
	if( gall_dir(y) == COLM_E )
	{ setBack(x, dim, b), setFwd(x, dim, f);
	  debug0(DSA, D, "] AdjustSize returning at horiz HEAD");
	  return;
	}
	else if( sameDim(dim, ROWM) )
	{ setBack(x, dim, b), setFwd(x, dim, f);
	  debug0(DSA, D, "] AdjustSize ROWM returning at HEAD");
	  return;
	}
	else
	{
	  /* let lp and rp be the gaps delimiting the          */
	  /* components joined to x                            */
	  for( lp = PrevDown(link);  lp != y;  lp = PrevDown(lp) )
	  { Child(&z, lp);
	    if( objectOfType(z, GAP_OBJ) && !join(&gap(z)) )  break;
	  }
	  for( rp = NextDown(link);  rp != y;  rp = NextDown(rp) )
	  { Child(&z, rp);
	    if( objectOfType(z, GAP_OBJ) && !join(&gap(z)) )  break;
	  }

	  setBack(x, dim, b);  setFwd(x, dim, f);
	  if( lp == y && rp == y && !seen_nojoin(y) )
	  {	
	    /* if whole object is joined, do this */
	    b = find_max(b, back(y, dim));
	    f = find_max(f, fwd(y, dim));
	    debug3(DSA, D, "  under head %s, whole object joined, b = %s, f = %s)",
	      SymName(actual(y)), EchoLength(b), EchoLength(f));
	  }
	  else
	  {
	    /* if // or || is present, do this */
	    debug1(DSA, D, "  [ under head %s with //, working out tb and tf:",
	      SymName(actual(y)));
	    tb = tf = 0;
	    for( link = NextDown(lp);  link != rp;  link = NextDown(link) )
	    { Child(&z, link);
	      debugcond1(DSA, D, objectOfType(z, GAP_OBJ),
		"    gap %s", EchoCatOp(VCAT, mark(&gap(z)), join(&gap(z))));
	      if( objectOfType(z, GAP_OBJ) || is_index(type(z)) )  continue;
	      debug6(DSA, D,  "    component %s %s(%s, %s) so tb = %s, tf = %s",
		Image(type(z)), objectOfType(z, CLOSURE) ?  SymName(actual(z)) : STR_EMPTY,
		EchoLength(back(z, dim)), EchoLength(fwd(z, dim)),
		EchoLength(tb), EchoLength(tf));
	      ifdebugcond(DSA, DD,  sameDim(dim, COLM) && fwd(z, dim) > 20*CM, DebugObject(z));
	      tb = find_max(tb, back(z, dim));
	      tf = find_max(tf, fwd(z, dim));
	    }
	    b = 0;  f = find_max(tb + tf, fwd(y, dim));
	    debug5(DSA, D, "  ] under head %s with //, tb = %s, tf = %s, b = %s, f = %s",
	      SymName(actual(y)), EchoLength(tb), EchoLength(tf),
	      EchoLength(b), EchoLength(f));
	  }
	  if( back(y, dim) == b && fwd(y, dim) == f )
	  {
	    debug0(DSA, D, "] AdjustSize (COLM) returning at HEAD (no wider)");
	    return;
	  }
	  debug3(DSA, DD, "AdjustSize widening HEAD %s to b = %s, f = %s",
		   SymName(actual(y)), EchoLength(b), EchoLength(f));
	  ifdebugcond(DSA, DD,  sameDim(dim, COLM) && f > 20*CM, DebugObject(y));
	  setBack(y, dim, b);  setFwd(y, dim, f);
	  if( Up(y) == y )
	  {
	    debug0(DSA, D, "] AdjustSize ret. at HEAD (no parent)" );
	    return;
	  }
	  Parent(index, Up(y));
	  if( !objectOfType(index, RECEIVING) )
	  {
	    debug1(DSA,D, "] AdjustSize ret. at HEAD (%s)", Image(type(index)));
	    return;
	  }
	  assert(actual(index)!=nilobj, "AdjustSize: actual(index)==nilobj!" );
	  assert( objectOfType(actual(index), CLOSURE), "AdjustSize: index non-C!" );
	  if( actual(actual(index)) != GalleySym &&
	      actual(actual(index)) != ForceGalleySym )
	  {
	    debug0(DSA, D, "] AdjustSize ret. at HEAD (not @Galley, so root)" );
	    return;
	  }
	  y = actual(index);
	  debug3(DSA, DD, "AdjustSize jumping to y = %s of size %s,%s",
	    Image(type(y)), EchoLength(back(y, dim)), EchoLength(fwd(y, dim)));
	}
	break;


      case SPLIT_E:
      case HCONTRACT_E:
      case VCONTRACT_E:
      case HEXPAND_E:
      case VEXPAND_E:
      case BEGIN_HEADER_E:
      case END_HEADER_E:
      case SET_HEADER_E:
      case CLEAR_HEADER_E:
      case ONE_COL_E:
      case ONE_ROW_E:
      case PLAIN_GRAPHIC_E:
      case GRAPHIC_E:
      case LINK_SOURCE_E:
      case LINK_DEST_E:
      case LINK_DEST_NULL_E:
      case LINK_URL_E:
      case KERN_SHRINK_E:
      case BACKGROUND_E:

	setBack(x, dim, b);  setFwd(x, dim, f);
	break;


      case HMIRROR_E:
      case VMIRROR_E:

	setBack(x, dim, b);  setFwd(x, dim, f);
	if( (sameDim(dim, COLM)) == (objectOfType(y, HMIRROR)) )
	{
	  tb = b; b = f; f = tb;
	}
	break;


      case HSCALE_E:
      case VSCALE_E:

	setBack(x, dim, b);  setFwd(x, dim, f);
	if( (sameDim(dim, COLM)) == (objectOfType(y, HSCALE)) )
	{ debug0(DSA, D, "] AdjustSize returning at HSCALE or VSCALE");
	  return;
	}
	break;


      case HCOVER_E:
      case VCOVER_E:

	/* dubious, but not likely to arise in practice */
	setBack(x, dim, b);  setFwd(x, dim, f);
	if( (sameDim(dim, COLM)) == (objectOfType(y, HCOVER)) )
	{ debug0(DSA, D, "] AdjustSize returning at HCOVER or VCOVER");
	  return;
	}
	break;


      case SCALE_E:

	setBack(x, dim, b);  setFwd(x, dim, f);
	if( sameDim(dim, COLM) )
	{ b *= bc(constraint(y)) / SF;
	  f *= bc(constraint(y)) / SF;
	}
	else
	{ b *= fc(constraint(y)) / SF;
	  f *= fc(constraint(y)) / SF;
	}
	break;


      case ROTATE_E:
      
	setBack(x, dim, b);  setFwd(x, dim, f);
	RotateSize(&cby, &cfy, &rby, &rfy, x, sparec(constraint(y)));
	if( cby != back(y, COLM) || cfy != fwd(y, COLM) )
	  AdjustSize(y, cby, cfy, COLM);
	if( rby != back(y, ROWM) || rfy != fwd(y, ROWM) )
	  AdjustSize(y, rby, rfy, ROWM);
	debug1(DSA, D, "] AdjustSize returning at %s.", Image(type(y)));
	return;


      case WIDE_E:
      case HIGH_E:
      
	if( (objectOfType(y, WIDE)) == (sameDim(dim, COLM)) )
	{ if( !FitsConstraintOnRef(b, f, &constraint(y)) )
	  { Error(16, 2, "size constraint %s,%s,%s broken by %s,%s",
	      WARN, &fpos(y),
	      EchoLength(bc(constraint(y))), EchoLength(bfc(constraint(y))),
	      EchoLength(fc(constraint(y))), EchoLength(b), EchoLength(f));
	    SetConstraintOnRef(&constraint(y), MAX_FULL_LENGTH, b+f, MAX_FULL_LENGTH);
	  }
	  setBack(x, dim, b);  setFwd(x, dim, f);
	  EnlargeToConstraint(&b, &f, &constraint(y));
	}
	else
	{ setBack(x, dim, b);
	  setFwd(x, dim, f);
	}
	break;


      case HLIMITED_E:
      case VLIMITED_E:
      
	if( (objectOfType(y, HLIMITED)) == (sameDim(dim, COLM)) )
	{
	  /* ***
          Parent(z, UpDim(y, dim));
          if( type(z) == ROW_THR || type(z) == COL_THR )
          {
            SetConstraintOnRef(&constraint(y), back(z,dim), size(z,dim), fwd(z,dim));
          }
          else
          {
            SetConstraintOnRef(&constraint(y), back(y,dim), size(y,dim), fwd(y,dim));
          }
	  if( !FitsConstraintOnRef(b, f, &constraint(y)) )
	  { Error(16, 3, "%s of size %s,%s broken by %s,%s",
	      WARN, &fpos(y), Image(type(y)),
	      EchoLength(back(y, dim)), EchoLength(fwd(y, dim)),
	      EchoLength(b), EchoLength(f));
	  }
	  *** */
	  setBack(x, dim, b);  setFwd(x, dim, f);
	}
	else
	{ setBack(x, dim, b);
	  setFwd(x, dim, f);
	}
	break;


      case HSHIFT_E:
      case VSHIFT_E:

	setBack(x, dim, b);  setFwd(x, dim, f);
	if( (objectOfType(y, HSHIFT)) == (sameDim(dim, COLM)) )
	{ tf = FindShift(y, x, dim);
	  b = find_min(MAX_FULL_LENGTH, find_max(0, b + tf));
	  f = find_min(MAX_FULL_LENGTH, find_max(0, f - tf));
	}
	break;


      case COL_THR_E:
      case ROW_THR_E:

	assert( (objectOfType(y, COL_THR)) == (sameDim(dim, COLM)), "AdjustSize: COL_THR!" );
	setBack(x, dim, b);  setFwd(x, dim, f);
	b = find_max(b, back(y, dim));
	f = find_max(f, fwd(y, dim));
	break;


      case VCAT_E:
      case HCAT_E:
      case ACAT_E:

	if( (objectOfType(y, VCAT)) == (sameDim(dim, ROWM)) )
	  CatAdjustSize(x, &b, &f, ratm, y, dim);
	else
	{
	  /* let lp and rp be the gaps bracketing the components joined to x */
	  for( lp = PrevDown(link);  lp != y;  lp = PrevDown(lp) )
	  { Child(&z, lp);
	    if( objectOfType(z, GAP_OBJ) && !join(&gap(z)) )  break;
	  }
	  for( rp = NextDown(link);  rp != y;  rp = NextDown(rp) )
	  { Child(&z, rp);
	    if( objectOfType(z, GAP_OBJ) && !join(&gap(z)) )  break;
	  }

	  setBack(x, dim, b);  setFwd(x, dim, f);
	  if( lp == y && rp == y )
	  {
	    /* if whole object is joined, do this */
	    b = find_max(b, back(y, dim));
	    f = find_max(f, fwd(y, dim));
	  }
	  else
	  { /* if // or || is present, do this */
	    tb = tf = 0;
	    for( link = NextDown(lp); link != rp;  link = NextDown(link) )
	    { Child(&z, link);
	      if( objectOfType(z, GAP_OBJ) || is_index(type(z)) )  continue;
	      tb = find_max(tb, back(z, dim));
	      tf = find_max(tf, fwd(z, dim));
	    }
	    b = 0;  f = find_max(tb + tf, fwd(y, dim));
	  }
	}
	break;


      case START_HVSPAN_E:

	Error(16, 4, "size adjustment of %s not implemented",
	       WARN, &fpos(y), Image(type(y)));
	break;


      case START_VSPAN_E:
      case VSPAN_E:

	if( sameDim(dim, COLM) )
	{
	  setBack(x, dim, b);  setFwd(x, dim, f);
	}
	else Error(16, 4, "size adjustment of %s not implemented",
	       WARN, &fpos(y), Image(type(y)));
	break;


      case START_HSPAN_E:
      case HSPAN_E:

	if( sameDim(dim, ROWM) )
	{
	  setBack(x, dim, b);  setFwd(x, dim, f);
	}
	else Error(16, 4, "size adjustment of %s not implemented",
	       WARN, &fpos(y), Image(type(y)));
	break;


      case HSPANNER_E:
      case VSPANNER_E:

	assert( (sameDim(dim, COLM)) == (objectOfType(y, HSPANNER)), "AdjustSize: span");
	setBack(x, dim, b);  setFwd(x, dim, f);
	debug5(DSC, D, "  adjusting %s from (%s,%s) to (%s,%s)",
	  Image(type(y)), EchoLength(back(y, dim)), EchoLength(fwd(y, dim)),
	  EchoLength(b), EchoLength(f));
	setBack(y, dim, b);  setFwd(y, dim, f);
	debug1(DSA, D, "] AdjustSize returning at %s", Image(type(y)));
	return;
	break;


      case WORD_E:
      case QWORD_E:
      case CLOSURE_E:
      case NULL_CLOS_E:
      case PAGE_LABEL_E:
      case CROSS_E:
      case FORCE_CROSS_E:
      default:
      
	assert1(FALSE, "AdjustSize:", Image(type(y)));
	break;


    } /* end switch */
    x = y;
  } /* end while */
  debug0(DSA, D, "] AdjustSize returning.");
} /* end AdjustSize */
