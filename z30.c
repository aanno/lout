/*@z30.c:Symbol uses:InsertUses()@********************************************/
/*                                                                           */
/*  LOUT: A HIGH-LEVEL LANGUAGE FOR DOCUMENT FORMATTING (VERSION 2.05)       */
/*  COPYRIGHT (C) 1993 Jeffrey H. Kingston                                   */
/*                                                                           */
/*  Jeffrey H. Kingston (jeff@cs.su.oz.au)                                   */
/*  Basser Department of Computer Science                                    */
/*  The University of Sydney 2006                                            */
/*  AUSTRALIA                                                                */
/*                                                                           */
/*  This program is free software; you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation; either version 1, or (at your option)      */
/*  any later version.                                                       */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program; if not, write to the Free Software              */
/*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
/*                                                                           */
/*  FILE:         z30.c                                                      */
/*  MODULE:       Symbol Uses                                                */
/*  EXTERNS:      InsertUses(), FlattenUses(), SearchUses(),                 */
/*                FirstExternTarget(), NextExternTarget()                    */
/*                                                                           */
/*****************************************************************************/
#include "externs"


/*****************************************************************************/
/*                                                                           */
/*  InsertUses(x, y)                                                         */
/*                                                                           */
/*  Record the fact that symbol x uses symbol y, by linking them.            */
/*  Increment count of the number of times y is used, if y is a parameter.   */
/*                                                                           */
/*****************************************************************************/

InsertUses(x, y)
OBJECT x, y;
{ OBJECT tmp;
  debug2(DSU, D, "InsertUses( %s, %s )", SymName(x), SymName(y));
  if( type(x) == LOCAL && type(y) == LOCAL && !predefined(y) )
  { tmp = GetMem(USES_SIZE, no_fpos);  item(tmp) = y;
    if( base_uses(x) == nil )  next(tmp) = tmp;
    else next(tmp) = next(base_uses(x)), next(base_uses(x)) = tmp;
    base_uses(x) = tmp;
  }
  if( is_par(type(y)) )
  { uses_count(y) += (enclosing(y) == x ? 1 : 2);
    if( dirty(y) || uses_count(y) > 1 )  dirty(enclosing(y)) = TRUE;
  }
  else if( sym_body(y) == nil || dirty(y) )  dirty(x) = TRUE;
  debug5(DSU, D, "InsertUses returning ( %s %s; %s %s, count = %d )",
    SymName(x), (dirty(x) ? "dirty" : "clean"),
    SymName(y), (dirty(y) ? "dirty" : "clean"), uses_count(y));
} /* end InsertUses */


/*@::GatherUses(), GatherAllUses(), FlattenUses()@****************************/
/*                                                                           */
/*  static GatherUses(x, sym)                                                */
/*  static GatherAllUses(x)                                                  */
/*                                                                           */
/*  GatherUses adds all the unmarked descendants of x to the uses relation   */
/*  of sym;  GatherAllUses applies gather_uses to all descendants of x.      */
/*                                                                           */
/*****************************************************************************/

static GatherUses(x, sym)
OBJECT x, sym;
{ OBJECT link, y, tmp;
  if( base_uses(x) != nil )
  { link = next(base_uses(x));
    do
    { y = item(link);
      if( marker(y) != sym )
      {	if( y != sym )
	{ marker(y) = sym;
	  tmp = GetMem(USES_SIZE, no_fpos);  item(tmp) = y;
	  if( uses(sym) == nil )  next(tmp) = tmp;
	  else next(tmp) = next(uses(sym)), next(uses(sym)) = tmp;
	  uses(sym) = tmp;
	  if( indefinite(y) )  indefinite(sym) = TRUE;
	  if( uses_extern_target(y) )  uses_extern_target(sym) = TRUE;
	  GatherUses(y, sym);
	}
	else recursive(sym) = TRUE;
      }
      link = next(link);
    } while( link != next(base_uses(x)) );
  }
} /* end GatherUses */


static GatherAllUses(x)
OBJECT x;
{ OBJECT link, y;
  for( link = Down(x);  link != x;  link = NextDown(link) )
  { Child(y, link);
    if( type(y) == LOCAL )  GatherUses(y, y);
    GatherAllUses(y);
  }
} /* end GatherAllUses */


/*****************************************************************************/
/*                                                                           */
/*  FlattenUses()                                                            */
/*                                                                           */
/*  Traverse the directed graph assembled by InsertUses, finding its         */
/*  transitive closure and storing this explicitly in uses(x) for all x.     */
/*                                                                           */
/*****************************************************************************/

FlattenUses()
{ GatherAllUses(StartSym);
} /* end FlattenUses */


/*@::SearchUses(), FirstExternTarget(), NextExternTarget()@*******************/
/*                                                                           */
/*  BOOLEAN SearchUses(x, y)                                                 */
/*                                                                           */
/*  Discover whether symbol x uses symbol y by searching the uses list of x. */
/*                                                                           */
/*****************************************************************************/

BOOLEAN SearchUses(x, y)
OBJECT x, y;
{ OBJECT p;
  debug3(DSU, DD, "SearchUses(%s, %s) uses: %d", SymName(x),SymName(y),uses(x));
  if( x == y )  return TRUE;
  if( uses(x) != nil )
  { p = next(uses(x));
    do
    { debug1(DSU, DDD, "  checking %s", SymName(item(p)));
      if( item(p) == y )  return TRUE;
      p = next(p);
    } while( p != next(uses(x)) );
  }
  return FALSE;
} /* end SearchUses */


/*****************************************************************************/
/*                                                                           */
/*  OBJECT FirstExternTarget(sym, cont)                                      */
/*  OBJECT NextExternTarget(sym, cont)                                       */
/*                                                                           */
/*  Together these two procedures return all symbols which are both used by  */
/*  sym and a target for at least one external galley.  Return nil at end.   */
/*                                                                           */
/*****************************************************************************/

OBJECT FirstExternTarget(sym, cont)
OBJECT sym, *cont;
{ OBJECT res;
  debug1(DSU, D, "FirstExternTarget( %s )", SymName(sym));
  res = nil;  *cont = nil;
  if( is_extern_target(sym) )  res = sym;
  else if( uses(sym) != nil )
  { *cont = next(uses(sym));
    do
    { if( is_extern_target(item(*cont)) )
      {	res = item(*cont);
	break;
      }
      *cont = next(*cont);
    } while( *cont != next(uses(sym)) );
  }
  debug1(DSU, D, "FirstExternTarget returning %s", SymName(res));
  return res;
} /* end FirstExternTarget */

OBJECT NextExternTarget(sym, cont)
OBJECT sym, *cont;
{ OBJECT res;
  debug1(DSU, D, "NextExternTarget( %s )", SymName(sym));
  res = nil;
  if( *cont != nil )
  { *cont = next(*cont);
    while( *cont != next(uses(sym)) )
    { if( is_extern_target(item(*cont)) )
      {	res = item(*cont);
	break;
      }
      *cont = next(*cont);
    }
  }
  debug1(DSU, D, "NextExternTarget returning %s", SymName(res));
  return res;
} /* end NextExternTarget */
