/*@z05.c:Read Definitions:ReadLangDef()@**************************************/
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
/*  FILE:         z05.c                                                      */
/*  MODULE:       Read Definitions                                           */
/*  EXTERNS:      ReadPrependDef(), ReadDatabaseDef(), ReadDefinitions()     */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"


/*****************************************************************************/
/*                                                                           */
/*  is_string(t, str)                                                        */
/*                                                                           */
/*  If t is a token denoting unquoted word str, return TRUE.                 */
/*                                                                           */
/*****************************************************************************/

#define is_string(t, str)    (objectOfType(t, WORD) && StringEqual(string(t), str) )


/*****************************************************************************/
/*                                                                           */
/*  static ReadLangDef(encl)                                                 */
/*                                                                           */
/*  Read one language definition and pass it on to the language module.  The */
/*  syntax is  langdef <name> ... <name> { <object> }                        */
/*                                                                           */
/*****************************************************************************/

static void ReadLangDef(OBJECT encl)
{ OBJECT t, names, inside;
  
  New(names, ACAT);
  t = LexGetToken();
  while( is_word(type(t)) )
  { Link(names, t);
    t = LexGetToken();
  }
  if( !objectOfType(t, LBR) )
  { Error(5, 4, "expected opening %s of langdef here", WARN, &fpos(t), KW_LBR);
    Dispose(t);
    return;
  }
  inside = Parse(&t, encl, FALSE, FALSE);
  inside = ReplaceWithTidy(inside, ACAT_TIDY);
  LanguageDefine(names, inside);
  return;
} /* end ReadLangDef */


/*@::ReadPrependDef(), ReadDatabaseDef()@*************************************/
/*                                                                           */
/*  ReadPrependDef(typ, encl)                                                */
/*                                                                           */
/*  Read @PrependGraphic { <filename> } and record its presence, unless it   */
/*  is there already; we allow multiple occurrences but only want to print   */
/*  the file once.                                                           */
/*                                                                           */
/*****************************************************************************/

void ReadPrependDef(OBJTYPE typ, OBJECT encl)
{ OBJECT t, fname;
  FILE_NUM fnum;
  t = LexGetToken();
  if( !objectOfType(t, LBR) )
  { Error(5, 5, "left brace expected here in %s declaration",
      WARN, &fpos(t), KW_PREPEND);
    Dispose(t);
    return;
  }
  fname = Parse(&t, encl, FALSE, FALSE);
  fname = ReplaceWithTidy(fname, ACAT_TIDY);
  if( !is_word(type(fname)) )
  { Error(5, 6, "name of %s file expected here", WARN, &fpos(fname),KW_PREPEND);
    DisposeObject(fname);
    return;
  }
  debug0(DFS, D, "  calling DefineFile from ReadPrependDef");
  fnum = FileNum(string(fname), STR_EMPTY);
  if( fnum == NO_FILE || FileType(fnum) != PREPEND_FILE )
    DefineFile(string(fname), STR_EMPTY, &fpos(fname), PREPEND_FILE,
	   typ.objtype == PREPEND_E ? INCLUDE_PATH : SYSINCLUDE_PATH);

} /* end ReadPrependDef */


/*****************************************************************************/
/*                                                                           */
/*  ReadIncGRepeatedDef(typ, encl)                                           */
/*                                                                           */
/*  Read @IncludeGraphicRepeated { <filename> } and record its presence.     */
/*                                                                           */
/*****************************************************************************/

void ReadIncGRepeatedDef(OBJTYPE typ, OBJECT encl)
{ OBJECT t, fname;
  t = LexGetToken();
  if( !objectOfType(t, LBR) )
  { Error(5, 5, "left brace expected here in %s declaration",
      WARN, &fpos(t), KW_INCG_REPEATED);
    Dispose(t);
    return;
  }
  fname = Parse(&t, encl, FALSE, FALSE);
  fname = ReplaceWithTidy(fname, ACAT_TIDY);
  if( !is_word(type(fname)) )
  { Error(5, 6, "name of %s file expected here", WARN, &fpos(fname),
      KW_INCG_REPEATED);
    DisposeObject(fname);
    return;
  }
  debug0(DFS, D, "  calling PS_IncGRepeated from ReadPrependDef");
  incg_type(fname) = (typ.objtype == INCG_REPEATED_E ? INCGRAPHIC_E : SINCGRAPHIC_E);
  PS_IncGRepeated(fname);
} /* end ReadPrependDef */


/*****************************************************************************/
/*                                                                           */
/*  ReadDatabaseDef(typ, encl)                                               */
/*                                                                           */
/*  Read @Database <symname> ... <symname> { <filename> } and record it.     */
/*                                                                           */
/*****************************************************************************/

void ReadDatabaseDef(OBJTYPE typ, OBJECT encl)
{ OBJECT symbs, t, fname;
  New(symbs, ACAT);
  t = LexGetToken();
  while( objectOfType(t, CLOSURE) || (objectOfType(t, WORD) && string(t)[0]==CH_SYMSTART) )
  { if( objectOfType(t, CLOSURE) )
    { Link(symbs, t);
    }
    else
    { Error(5, 7, "unknown or misspelt symbol %s", WARN, &fpos(t), string(t));
      Dispose(t);
    }
    t = LexGetToken();
  }
  if( !objectOfType(t, LBR) )
  { Error(5, 8, "symbol name or %s expected here (%s declaration)",
      WARN, &fpos(t), KW_LBR, KW_DATABASE);
    Dispose(t);
    return;
  }
  if( Down(symbs) == symbs )
  { Error(5, 9, "symbol names missing in %s declaration",
      WARN, &fpos(t), KW_DATABASE);
  }
  fname = Parse(&t, encl, FALSE, FALSE);
  fname = ReplaceWithTidy(fname, ACAT_TIDY);
  if( !is_word(type(fname)) )
  { Error(5, 10, "name of %s file expected here", WARN, &fpos(fname),
      KW_DATABASE);
    DisposeObject(fname);
    return;
  }
  if( StringEndsWith(string(fname), DATA_SUFFIX) )
  { Error(5, 47, "%s suffix should be omitted in %s clause", WARN,
      &fpos(fname), DATA_SUFFIX, KW_DATABASE);
    DisposeObject(fname);
    return;
  }
  if( Down(symbs) != symbs )
    (void) DbLoad(fname, typ.objtype == DATABASE_E ? DATABASE_PATH : SYSDATABASE_PATH,
      TRUE, symbs, InMemoryDbIndexes);
} /* end ReadDatabaseDef */


/*@::ReadTokenList()@*********************************************************/
/*                                                                           */
/*  static ReadTokenList(token, res)                                         */
/*                                                                           */
/*  Read a list of tokens from input and append them to sym_body(res).       */
/*  The list is assumed to begin immediately after token, which is either    */
/*  an LBR or a @Begin, and input is to be read up to and including the      */
/*  matching RBR or @End @Sym.                                               */
/*                                                                           */
/*****************************************************************************/
#define NextToken(t, res)						\
  t = LexGetToken(); sym_body(res) = Append(sym_body(res), t, PARENT);

static void ReadTokenList(OBJECT token, OBJECT res)
{ OBJECT t, xsym, new_par, imps, link, y;  int scope_count, i;
  NextToken(t, res);
  for(;;) switch(type(t).objtype)
  {
    case WORD_E:

      if( string(t)[0] == CH_SYMSTART )
	Error(5, 11, "symbol %s unknown or misspelt", WARN, &fpos(t),
	  string(t));
      NextToken(t, res);
      break;


    case QWORD_E:

      NextToken(t, res);
      break;


    case VCAT_E:
    case HCAT_E:
    case ACAT_E:
    case CROSS_E:
    case FORCE_CROSS_E:
    case NULL_CLOS_E:
    case PAGE_LABEL_E:
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
    case RAW_VERBATIM_E:
    case VERBATIM_E:
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
    case TAGGED_E:
    case INCGRAPHIC_E:
    case SINCGRAPHIC_E:
    case PLAIN_GRAPHIC_E:
    case GRAPHIC_E:
    case LINK_SOURCE_E:
    case LINK_DEST_E:
    case LINK_DEST_NULL_E:
    case LINK_URL_E:
    case NOT_REVEALED_E:

      NextToken(t, res);
      break;


    case LUSE_E:
    case LVIS_E:
    case ENV_E:
    case USE_E:
    case DATABASE_E:
    case SYS_DATABASE_E:
    case PREPEND_E:
    case SYS_PREPEND_E:
    case INCG_REPEATED_E:
    case SINCG_REPEATED_E:
    case OPEN_E:

      Error(5, 12, "symbol %s not allowed in macro", WARN, &fpos(t),
	SymName(actual(t)));
      NextToken(t, res);
      break;


    case LBR_E:

      ReadTokenList(t, res);
      NextToken(t, res);
      break;


    case UNEXPECTED_EOF_E:

      Error(5, 13, "unexpected end of input", FATAL, &fpos(t));
      break;


    case BEGIN_E:

      Error(5, 14, "%s not expected here", WARN, &fpos(t), SymName(actual(t)));
      NextToken(t, res);
      break;


    case RBR_E:

      if( !objectOfType(token, LBR) )
	Error(5, 15, "unmatched %s in macro", WARN, &fpos(t), KW_RBR);
      return;


    case END_E:

      if( !objectOfType(token, BEGIN) )
	Error(5, 16, "unmatched %s in macro", WARN, &fpos(t), KW_END);
      else
      { NextToken(t, res);
        if( !objectOfType(t, CLOSURE) )
	{
	  if( objectOfType(t, WORD) && string(t)[0] == CH_SYMSTART )
	    Error(5, 17, "symbol %s unknown or misspelt",
	      WARN, &fpos(t), string(t));
	  else
	    Error(5, 18, "symbol name expected after %s", WARN,&fpos(t),KW_END);
	}
        else if( actual(token) != actual(t) )
	  Error(5, 19, "%s %s does not match %s %s", WARN, &fpos(t),
	    SymName(actual(token)), KW_BEGIN, SymName(actual(t)), KW_END);
      }
      return;


    case CLOSURE_E:

      xsym = actual(t);
      PushScope(xsym, TRUE, FALSE);
      NextToken(t, res);
      PopScope();
      if( objectOfType(t, CROSS) || objectOfType(t, FORCE_CROSS) )
      { NextToken(t, res);
	break;
      }

      /* read named parameters */
      while( objectOfType(t, CLOSURE) && enclosing(actual(t)) == xsym &&
	     objectOfType(actual(t), NPAR) )
      {	new_par = t;
	NextToken(t, res);
	if( !objectOfType(t, LBR) )
	{ if( objectOfType(t, RBR) )
	  { if( !objectOfType(token, LBR) )
	      Error(5, 20, "unmatched %s in macro", WARN, &fpos(t), KW_RBR);
	    return;
	  }
	  Error(5, 21, "%s must follow named parameter %s",
	    WARN, &fpos(new_par), KW_LBR, SymName(actual(new_par)));
	  break;
	}

        /* add import list of the named parameter to current scope */
        scope_count = 0;
        imps = imports(actual(new_par));
        if( imps != nilobj )
        { for( link = Down(imps);  link != imps;  link = NextDown(link) )
          { Child(y, link);
            PushScope(actual(y), FALSE, TRUE);
            scope_count++;
          }
        }

	/* read the body of the named parameter */
	PushScope(actual(new_par), FALSE, FALSE);
	ReadTokenList(t, res);
	PopScope();

        /* pop the scopes pushed for the import list */
        for( i = 0;  i < scope_count;  i++ )
          PopScope();

	/* get next token, possibly another named parameter */
	PushScope(xsym, TRUE, FALSE);
	NextToken(t, res);
	PopScope();
      }

      /* read body parameter, if any */
      if( has_body(xsym) )
      {
	if( objectOfType(t, LBR) || objectOfType(t, BEGIN) )
	{ PushScope(xsym, FALSE, TRUE);
	  PushScope(ChildSym(xsym, RPAR), FALSE, FALSE);
	  if( objectOfType(t, BEGIN) )  actual(t) = xsym;
	  ReadTokenList(t, res);
	  PopScope();
	  PopScope();
	  NextToken(t, res);
	}
	else if( !objectOfType(t, RBR) && !objectOfType(t, END) )
	  Error(5, 22, "right parameter of %s must begin with %s",
	    WARN, &fpos(t), SymName(xsym), KW_LBR);
      }
      break;


    default:

      Error(5, 23, "ReadTokenList: %s", INTERN, &fpos(t), Image(type(t)));
      break;

  }
} /* end ReadTokenList */


/*@::ReadMacro()@*************************************************************/
/*                                                                           */
/*  static OBJECT ReadMacro(token, encl)                                     */
/*                                                                           */
/*  Read a macro from input and insert into symbol table.                    */
/*  Token *token contains the "macro" keyword.  Input is read up to and      */
/*  including the closing right brace, and nilobj returned in *token if OK.  */
/*  The proper scope for reading the macro body is open at entry and exit.   */
/*  ReadMacro returns the new symbol table entry if successful, else nilobj. */
/*                                                                           */
/*****************************************************************************/

static OBJECT ReadMacro(OBJECT *token, OBJECT curr_encl, OBJECT encl)
{ OBJECT t, res;

  /* find macro name and insert into symbol table */
  SuppressScope();
  Dispose(*token);  t = LexGetToken();
  if( !is_word(type(t)) )
  { Error(5, 24, "%s ignored (name is missing)", WARN, &fpos(t), KW_MACRO);
    debug1(ANY, D, "offending type is %s", Image(type(t)));
    UnSuppressScope();
    *token = t;
    return nilobj;
  }
  res = InsertSym(string(t), MACRO, &fpos(t), 0, FALSE,TRUE, DUMMY, curr_encl, nilobj);
  if( curr_encl != encl )  visible(res) = TRUE;
  UnSuppressScope();

  /* find alternative names for this symbol */
  Dispose(t);  t = LexGetToken();
  while( is_word(type(t)) )
  {
    InsertAlternativeName(string(t), res, &fpos(t));
    Dispose(t);  t = LexGetToken();
  }

  /* find opening left brace */
  if( !objectOfType(t, LBR) )
  { Error(5, 25, "%s ignored (opening %s is missing)",
      WARN, &fpos(t), KW_MACRO, KW_LBR);
    *token = t;
    return nilobj;
  }
  
  /* read macro body */
  ReadTokenList(t, res);
  Dispose(t);

  /* clean up (kill final RBR, dispose macro name) and exit */
  t = pred(sym_body(res), PARENT);
  sym_body(res) = Delete(t, PARENT);
  Dispose(t);
  recursive(res) = FALSE;
  *token = nilobj;
  return res;
} /* end ReadMacro */


/*@::ReadDefinitions()@*******************************************************/
/*                                                                           */
/*  ReadDefinitions(token, encl, res_type)                                   */
/*                                                                           */
/*  Read a sequence of definitions and insert them into the symbol table.    */
/*  Either a sequence of local definitions (res_type == LOCAL) or named      */
/*  parameters (res_type == NPAR) is expected; *token is the first def etc.  */
/*  A scope appropriate for reading the bodies of the definitions is open.   */
/*  The parent definition is encl.                                           */
/*                                                                           */
/*****************************************************************************/

void ReadDefinitions(OBJECT *token, OBJECT encl, OBJTYPE res_type)
{ OBJECT t, res, res_target, export_list, import_list, link, y, z;
  OBJECT curr_encl;  BOOLEAN compulsory_par, has_import_encl;
  t = *token;

  while( res_type.objtype==LOCAL_E || is_string(t, KW_NAMED) || is_string(t, KW_IMPORT) )
  {
    curr_encl = encl;

    if( is_string(t, KW_LANGDEF) )
    { ReadLangDef(encl);
      t = LexGetToken();
      continue;  /* next definition */
    }
    else if( objectOfType(t, PREPEND) || objectOfType(t, SYS_PREPEND) )
    { ReadPrependDef(type(t), encl);
      Dispose(t);
      t = LexGetToken();
      continue;  /* next definition */
    }
    else if( objectOfType(t, INCG_REPEATED) || objectOfType(t, SINCG_REPEATED) )
    { ReadIncGRepeatedDef(type(t), encl);
      Dispose(t);
      t = LexGetToken();
      continue;  /* next definition */
    }
    else if( objectOfType(t, DATABASE) || objectOfType(t, SYS_DATABASE) )
    { ReadDatabaseDef(type(t), encl);
      Dispose(t);
      t = LexGetToken();
      continue;  /* next definition */
    }

    if( !is_string(t, KW_DEF)    && !is_string(t, KW_MACRO)  &&
	!is_string(t, KW_NAMED)  && !is_string(t, KW_IMPORT) &&
        !is_string(t, KW_EXTEND) && !is_string(t, KW_EXPORT) )
      break;

    /* get import or extend list and change scope appropriately */
    BodyParNotAllowed();
    New(import_list, ACAT);
    has_import_encl = FALSE;
    if( is_string(t, KW_IMPORT) )
    { Dispose(t);
      t = LexGetToken();
      while( objectOfType(t, CLOSURE) ||
	       (objectOfType(t, WORD) && !is_string(t,KW_EXPORT) && !is_string(t,KW_DEF)
	       && !is_string(t, KW_MACRO) && !is_string(t, KW_NAMED)) )
      {	if( objectOfType(t, CLOSURE) )
	{ if( objectOfType(actual(t), LOCAL) )
	  {
	    /* *** letting this through now
	    if( res_type == NPAR && has_par(actual(t)) )
	    {
	      Error(5, 46, "named parameter import %s has parameters",
		WARN, &fpos(t), SymName(actual(t)));
	    }
	    else
	    {
	    *** */
	      PushScope(actual(t), FALSE, TRUE);
	      if( actual(t) == encl )  has_import_encl = TRUE;
	      Link(import_list, t);
	    /* ***
	    }
	    *** */
	  }
	  else
	  { Error(5, 26, "import name expected here", WARN, &fpos(t));
	    Dispose(t);
	  }
	}
	else
	{ Error(5, 27, "import %s not in scope", WARN, &fpos(t), string(t));
	  Dispose(t);
	}
	t = LexGetToken();
      }
    }
    else if( is_string(t, KW_EXTEND) )
    { Dispose(t);
      t = LexGetToken();
      while( objectOfType(t, CLOSURE) ||
	       (objectOfType(t, WORD) && !is_string(t,KW_EXPORT) && !is_string(t,KW_DEF)
	       && !is_string(t, KW_MACRO)) )
      {	if( objectOfType(t, CLOSURE) )
	{ if( imports(actual(t)) != nilobj )
	  { Error(5, 48, "%s has %s clause, so cannot be extended",
	      WARN, &fpos(t), SymName(actual(t)), KW_IMPORT);
	  }
	  else if( objectOfType(actual(t), LOCAL) )
	  { PushScope(actual(t), FALSE, FALSE);
	    curr_encl = actual(t);
            debug1(DRD, D, "  curr_encl = %s", SymName(curr_encl));
	    Link(import_list, t);
	  }
	  else
	  { Error(5, 28, "%s symbol name expected here",
	      WARN, &fpos(t), KW_EXTEND);
	    Dispose(t);
	  }
	}
	else
	{ Error(5, 29, "extend symbol %s not in scope", WARN,&fpos(t),string(t));
	  Dispose(t);
	}
	t = LexGetToken();
      }
    }

    /* get export list and store for setting visible flags below */
    New(export_list, ACAT);
    if( is_string(t, KW_EXPORT) )
    { Dispose(t);
      SuppressScope();
      t = LexGetToken();
      while( is_word(type(t)) && !is_string(t, KW_DEF) && !is_string(t, KW_IMPORT)
	&& !is_string(t, KW_MACRO) && !is_string(t, KW_EXTEND) )
      { Link(export_list, t);
	t = LexGetToken();
      }
      UnSuppressScope();
    }


    if( res_type.objtype == LOCAL_E && !is_string(t, KW_DEF) && !is_string(t, KW_MACRO) )
    { Error(5, 30, "keyword %s or %s expected here", WARN, &fpos(t),
	KW_DEF, KW_MACRO);
      break;
    }
    if( res_type.objtype == NPAR_E && !is_string(t, KW_NAMED) )
    { Error(5, 31, "keyword %s expected here", WARN, &fpos(t), KW_NAMED);
      break;
    }

    if( is_string(t, KW_MACRO) )
    { if( Down(export_list) != export_list )
	Error(5, 32, "ignoring export list of macro", WARN, &fpos(t));
      res = ReadMacro(&t, curr_encl, encl);
    }
    else
    {
      SuppressScope();  Dispose(t);  t = LexGetToken();

      /* check for compulsory keyword */
      if( res_type.objtype == NPAR_E && is_string(t, KW_COMPULSORY) )
      { compulsory_par = TRUE;
	Dispose(t);  t = LexGetToken();
      }
      else compulsory_par = FALSE;

      /* find name of symbol and insert it */
      if( !is_word(type(t)) )
      { Error(5, 33, "symbol name expected here", WARN, &fpos(t));
	debug1(ANY, D, "offending type is %s", Image(type(t)));
	UnSuppressScope();
	*token = t;
	return;
      }
      res = InsertSym(string(t), res_type, &fpos(t), DEFAULT_PREC,
		FALSE, FALSE, DUMMY, curr_encl, nilobj);
      if( curr_encl != encl )  visible(res) = TRUE;
      if( has_import_encl )
      {
	imports_encl(res) = TRUE;
	debug1(DCE, D, "  setting import_encl(%s) to TRUE", SymName(res));
      }
      if( compulsory_par )
      { has_compulsory(encl)++;
	is_compulsory(res) = TRUE;
      }
      Dispose(t);  t = LexGetToken();

      /* find alternative names for this symbol */
      while( is_word(type(t)) && !is_string(t, KW_NAMED) &&
	!is_string(t, KW_IMPORT) &&
	!is_string(t, KW_FORCE) && !is_string(t, KW_INTO) &&
	!is_string(t, KW_HORIZ) && !is_string(t, KW_PRECEDENCE) &&
	!is_string(t, KW_ASSOC) && !is_string(t, KW_LEFT) &&
	!is_string(t, KW_RIGHT) && !is_string(t, KW_BODY) &&
	!is_string(t, KW_LBR) && !is_string(t, KW_BEGIN) )
      {
	InsertAlternativeName(string(t), res, &fpos(t));
	Dispose(t);  t = LexGetToken();
      }

      /* find force, if any */
      if( is_string(t, KW_FORCE) )
      {	force_target(res) = TRUE;
	Dispose(t);  t = LexGetToken();
	if( !is_string(t, KW_INTO) && !is_string(t, KW_HORIZ) )
	   Error(5, 34, "%s expected here", WARN, &fpos(t), KW_INTO);
      }
	
      /* find horizontally, if any */
      if( is_string(t, KW_HORIZ) )
      { horiz_galley(res) = COLM;
	Dispose(t);  t = LexGetToken();
	/* *** want to allow KW_HORIZ with @Target form now
	if( !is_string(t, KW_INTO) )
	  Error(5, 35, "%s expected here", WARN, &fpos(t), KW_INTO);
	*** */
      }

      /* find into clause, if any */
      res_target = nilobj;
      if( is_string(t, KW_INTO) )
      { UnSuppressScope();
	Dispose(t);  t = LexGetToken();
	if( !objectOfType(t, LBR) )
	{ Error(5, 36, "%s expected here", WARN, &fpos(t), KW_LBR);
	  debug1(ANY, D, "offending type is %s", Image(type(t)));
	  UnSuppressScope();
	  *token = t;
	  return;
	}
	res_target = Parse(&t, curr_encl, FALSE, FALSE);
	SuppressScope();
	if( t == nilobj )  t = LexGetToken();
      }

      /* find precedence clause, if any */
      if( is_string(t, KW_PRECEDENCE) )
      {	int prec = 0;
	UnSuppressScope();
	Dispose(t);
	t = LexGetToken();
	while( objectOfType(t, WORD) && decimaldigit(string(t)[0]) )
	{
	  prec = prec * 10 + digitchartonum(string(t)[0]);
	  Dispose(t);  t = LexGetToken();
	}
	SuppressScope();

	if( prec < MIN_PREC )
	{ Error(5, 37, "precedence is too low (%d substituted)",
	    WARN, &fpos(t), MIN_PREC);
	  prec = MIN_PREC;
	}
	else if( prec > MAX_PREC )
	{ Error(5, 38, "precedence is too high (%d substituted)",
	    WARN, &fpos(t), MAX_PREC);
	  prec = MAX_PREC;
	}
	precedence(res) = prec;
      }

      /* find associativity clause, if any */
      if( is_string(t, KW_ASSOC) )
      {
	UnSuppressScope();
	Dispose(t);  t = LexGetToken();
	if( is_string(t, KW_LEFT) )  right_assoc(res) = FALSE;
	else if( !is_string(t, KW_RIGHT) )
	  Error(5, 39, "associativity altered to %s", WARN, &fpos(t), KW_RIGHT);
	SuppressScope();
	Dispose(t);  t = LexGetToken();
      }

      /* find left parameter, if any */
      if( is_string(t, KW_LEFT) )
      {	Dispose(t);  t = LexGetToken();
	if( !objectOfType(t, WORD) )
	{ Error(5, 40, "cannot find %s parameter name", WARN, &fpos(t), KW_LEFT);
	  debug1(ANY, D, "offending type is %s", Image(type(t)));
	  UnSuppressScope();
	  *token = t;
	  return;
	}
	InsertSym(string(t), LPAR, &fpos(t), DEFAULT_PREC, 
	  FALSE, FALSE, DUMMY, res, nilobj);
	Dispose(t);  t = LexGetToken();
      }

      /* find named parameters, if any */
      UnSuppressScope();
      ReadDefinitions(&t, res, NPAR);

      /* find right or body parameter, if any */
      if( is_string(t, KW_RIGHT) || is_string(t, KW_BODY) )
      {	has_body(res) = is_string(t, KW_BODY);
	SuppressScope();
	Dispose(t);  t = LexGetToken();
	if( !objectOfType(t, WORD) )
	{ Error(5, 41, "cannot find %s parameter name", WARN,&fpos(t),KW_RIGHT);
	  debug1(ANY, D, "offending type is %s", Image(type(t)));
	  UnSuppressScope();
	  *token = t;
	  return;
	}
	InsertSym(string(t), RPAR, &fpos(t), DEFAULT_PREC,
	  FALSE, FALSE, DUMMY, res, nilobj);
	UnSuppressScope();
	Dispose(t);  t = LexGetToken();
      }

      /* read local definitions and body */
      if( res_target != nilobj )
	InsertSym(KW_TARGET, LOCAL, &fpos(res_target), DEFAULT_PREC,
			FALSE, FALSE, DUMMY, res, res_target);
      if( objectOfType(t, WORD) && StringEqual(string(t), KW_LBR) )
      {	z = NewToken(LBR, &fpos(t), 0, 0, LBR_PREC, StartSym);
	Dispose(t);
	t = z;
      }
      else if( objectOfType(t, WORD) && StringEqual(string(t), KW_BEGIN) )
      {	z = NewToken(BEGIN, &fpos(t), 0, 0, BEGIN_PREC, StartSym);
	Dispose(t);
	t = z;
      }
      else if( !objectOfType(t, LBR) && !objectOfType(t, BEGIN) )
	Error(5, 42, "opening left brace or @Begin of %s expected",
	  FATAL, &fpos(t), SymName(res));
      if( objectOfType(t, BEGIN) )  actual(t) = res;
      PushScope(res, FALSE, FALSE);
      BodyParAllowed();
      sym_body(res) = Parse(&t, res, TRUE, FALSE);

      /* set visible flag of the exported symbols */
      for( link=Down(export_list);  link != export_list;  link=NextDown(link) )
      {	Child(y, link);
	z = SearchSym(string(y), StringLength(string(y)));
	if( z == nilobj || enclosing(z) != res )
	  Error(5, 43, "exported symbol %s is not defined in %s",
	    WARN, &fpos(y), string(y), SymName(res));
	else if( has_body(res) && objectOfType(z, RPAR) )
	  Error(5, 44, "body parameter %s may not be exported",
	    WARN, &fpos(y), string(y));
	else if( visible(z) )
	  Error(5, 45, "symbol %s exported twice", WARN, &fpos(y), string(y));
	else visible(z) = TRUE;
      }
      DisposeObject(export_list);

      /* pop scope of res */
      PopScope();
    }

    /* pop import scopes and store imports in sym tab */
    for( link=Down(import_list);  link != import_list;  link=NextDown(link) )
    {
      PopScope();
    }
    if( Down(import_list) == import_list || curr_encl != encl )
    { DisposeObject(import_list);
      import_list = nilobj;
    }
    else
    {
      imports(res) = import_list;
    }

    BodyParAllowed();
    if( t == nilobj ) t = LexGetToken();

  } /* end while */

  *token = t;
  return;
} /* end ReadDefinitions */
