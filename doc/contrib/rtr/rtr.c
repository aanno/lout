/*****************************************************************************/
/*                                                                           */
/*  RTR - A PROGRAM TO TRANSLATE AMONG REFERENCE FORMATS                     */
/*  COPYRIGHT (C) 1995 Jeffrey H. Kingston                                   */
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
/*  FILE:         externs                                                    */
/*  MODULE:       External Declarations                                      */
/*                                                                           */
/*****************************************************************************/
#include <stdio.h>
#define BOOLEAN int
#define FALSE 0
#define TRUE 1
#define MAX_STRING 400
#define MAX_FORMATS 3
#define MAX_FIELDS 44

#define FMT_LOUT	0
#define	FMT_BIBTEX	1
#define	FMT_BARDADYM	2

#define is_upper(ch) ( ch >= 'A' && ch <= 'Z' )
#define is_lower(ch) ( ch >= 'a' && ch <= 'z' )
#define to_lower(ch) ( ch - 'A' + 'a')
#define is_digit(ch) ( ch >= '0' && ch <= '9' )
#define is_white(ch) ( (ch) == ' ' || (ch) == '\t' || (ch) == '\n' )

typedef struct frec {
  char key[MAX_STRING];
  char value[MAX_STRING];
  int line_num;
  BOOLEAN quoted;		/* TRUE if value was found between quotes */
} FIELD;

typedef struct rrec {
  int field_count;
  FIELD field[MAX_FIELDS];
} REFERENCE;

typedef int FORMAT;

#define Get { ch = getc(fp);  if( ch == '\n' )  (*line_num)++; }
#define UnGet { ungetc(ch, fp);  if( ch == '\n' )  (*line_num)--; }
#define SkipGet Get; while( is_white(ch) ) Get;


/*****************************************************************************/
/*                                                                           */
/*  tmap[]                                                                   */
/*                                                                           */
/*  Mapping between type names.  An empty string indicates no equivalent.    */
/*                                                                           */
/*****************************************************************************/
#define MAX_TYPES 20

static char *tmap[MAX_TYPES][MAX_FORMATS] = {
  {	"Lout",		"BibTeX",	"Bardadym",	},
  {	"Book",		"Book",		"B",		},
  {	"Book",		"Booklet",	"B",		},
  {	"Proceedings",	"Proceedings",	"",		},
  {	"Proceedings",	"Conference",	"",		},
  {	"PhDThesis",	"PhdThesis",	"D",		},
  {	"TechReport",	"TechReport",	"R",		},
  {	"TechReport",	"Manual",	"R",		},
  {	"MastersThesis","MastersThesis","D",		},
  {	"Misc",		"Misc", 	"O",		},
  {	"Misc",		"Unpublished", 	"",		},
  {	"Article",	"Article",	"J",		},
  {	"InBook",	"InBook",	"P",		},
  {	"InBook",	"InCollection",	"P",		},
  {	"InProceedings","InProceedings","C",		},
  {	"",		"",		"A",		},
  {	"",		"",		"L",		},
  {	"",		"",		"M",		},
  {	"",		"",		"S",		},
  {	"",		"",		"*",		},
};


/*****************************************************************************/
/*                                                                           */
/*  int SearchTypes(char *typename, FORMAT f)                                */
/*                                                                           */
/*  Search the f column of tmap for this typename; return 0 if none.         */
/*                                                                           */
/*****************************************************************************/

int SearchTypes(char *typename, FORMAT f)
{ int i;
  for( i = 1;  i < MAX_TYPES;  i++ )
  {
    /* ***
    fprintf(stderr, "  comparing %s with tmap[%d][%d] = %s\n",
      typename, i, f, tmap[i][f]);
    *** */
    if( strcmp(typename, tmap[i][f]) == 0 )
      return i;
  }
  return 0;
} /* end SearchTypes */


/*****************************************************************************/
/*                                                                           */
/*  fmap[]                                                                   */
/*                                                                           */
/*  Mapping between field names.  An empty string indicates no equivalent.   */
/*                                                                           */
/*****************************************************************************/

char *fmap[MAX_FIELDS][MAX_FORMATS] = {
  {	"Lout",		"BibTeX",	"Bardadym",	},
  {	"@Type",	"typ",		"TYPE",		},
  {	"@Tag",		"tag",		"NUMBER",	},
  {	"@Abstract",	"",		"",		},
  {	"@Address",	"address",	"",		},
  {	"@Annote",	"annote",	"PROBLEM",	},
  {	"@Author",	"author",	"AUTHOR",	},
  {	"",		"chapter",	"",		},
  {	"@Day",		"",		"",		},
  {	"@Edition",	"edition",	"",		},
  {	"@HowPublished","howpublished",	"",		},
  {	"@InAuthor",	"editor",	"",		},
  {	"@InTitle",	"booktitle",	"",		},
  {	"@Institution",	"institution",	"INSTIT",	},
  {	"@Journal",	"journal",	"SOURCE",	},
  {	"",		"key",		"",		},
  {	"@Keywords",	"",		"",		},
  {	"@Label",	"",		"",		},
  {	"@Month",	"month",	"",		},
  {	"@Note",	"note",		"",		},
  {	"@Number",	"number",	"ISSUE",	},
  {	"@Organization","organization",	"",		},
  {	"@Pages",	"pages",	"FIRSTPAGE",	},
  {	"@Page",	"pages",	"",		},
  {	"@Pinpoint",	"",		"",		},
  {	"@Publisher",	"publisher",	"PUBLISHER",	},
  {	"@Title",	"title",	"NAME",		},
  {	"@TitleNote",	"",		"",		},
  {	"@TRType",	"type",		"",		},
  {	"@URL",		"url",		"",		},
  {	"@Volume",	"volume",	"VOL",		},
  {	"@Year",	"year", 	"YEAR",		},
  {	"",		"", 		"NUMBER",	},
  {	"",		"", 		"LASTAUT",	},
  {	"",		"", 		"LASTPAGE",	},
  {	"",		"", 		"STATE",	},
  {	"",		"", 		"LANGUAGE",	},
  {	"",		"", 		"MODEL",	},
  {	"",		"", 		"APPLIED",	},
  {	"",		"", 		"ALGORITHM",	},
  {	"",		"", 		"INTERFACE",	},
  {	"",		"", 		"SURVEY",	},
  {	"",		"", 		"REFERATS",	},
};


/*****************************************************************************/
/*                                                                           */
/*  FORMAT FindFormat(char *str)                                             */
/*                                                                           */
/*  Find this format in the format list.                                     */
/*                                                                           */
/*****************************************************************************/

FORMAT FindFormat(char *str)
{ int i;
  for( i = 0;  i < MAX_FORMATS;  i++ )
  {
    if( strcmp(str, fmap[0][i]) == 0 )
      return i;
  }
  fprintf(stderr, "unknown reference format %s\n", str);
  exit(1);
} /* end FindFormat */


/*****************************************************************************/
/*                                                                           */
/*  int SearchMap(char *fieldname, FORMAT f)                                 */
/*                                                                           */
/*  Search the f column of fmap for this fieldname; return 0 if none.        */
/*                                                                           */
/*****************************************************************************/

int SearchMap(char *fieldname, FORMAT f)
{ int i;
  for( i = 1;  i < MAX_FIELDS;  i++ )
  {
    if( strcmp(fieldname, fmap[i][f]) == 0 )
      return i;
  }
  return 0;
} /* end SearchMap */


/*****************************************************************************/
/*                                                                           */
/*  TranslateReference(REFERENCE *ref, int old, int new)                     */
/*                                                                           */
/*  Translate reference ref from old format to new format.                   */
/*                                                                           */
/*****************************************************************************/

TranslateReference(REFERENCE *ref, int old, int new)
{ int i, j, k;
  for( i = 0;  i < ref->field_count;  i++ )
  {
    if( strcmp(ref->field[i].key, "") == 0 )
    {
       /* do nothing, this field is not really here */
    }
    else if( (j = SearchMap(ref->field[i].key, old)) == 0 )
    {
      /* this field name is unknown, so omit this field */
      fprintf(stderr, "line %d: field %s omitted (unknown in %s)\n",
	ref->field[i].line_num, ref->field[i].key, fmap[0][old]);
      strcpy(ref->field[i].key, "");
    }
    else if( *fmap[j][new] == '\0' )
    {
      /* this field name has no equivalent in new, so omit this field */
      fprintf(stderr, "line %d: %s field %s omitted (no %s equivalent)\n",
	ref->field[i].line_num, fmap[0][old], ref->field[i].key, fmap[0][new]);
      strcpy(ref->field[i].key, "");
    }
    else if( j == 1 )
    { 
      /* this is the type field */
      k = SearchTypes(ref->field[i].value, old);
      if( k == 0 )
      {
	/* this type is unknown; signal this with a ?? in output */
	fprintf(stderr, "line %d: \"??\" appended to reference type %s (type unknown in %s)\n",
	  ref->field[i].line_num, ref->field[i].value, fmap[0][old]);
	strcat(ref->field[i].value, " ??");
      }
      else if( *tmap[k][new] == '\0' )
      {
	/* this type has no equivalent in new; signal this with ?? in output */
	fprintf(stderr, "line %d: \"??\" appended to %s reference type %s (no %s equivalent)\n",
	  ref->field[i].line_num, fmap[0][old],ref->field[i].value, fmap[0][new]);
	strcpy(ref->field[i].key, "");
      }
      else
      {
	/* the type field can be translated */
        strcpy(ref->field[i].key, fmap[j][new]);
        strcpy(ref->field[i].value, tmap[k][new]);
      }
    }
    else
    {
      /* this field can be translated; handle quotes, and translate */
      if( old != new ) switch( new )
      {
	  case FMT_LOUT:	ref->field[i].quoted = FALSE;
				break;
	
	  case FMT_BIBTEX:	ref->field[i].quoted = TRUE;
				break;
	
	  case FMT_BARDADYM:	ref->field[i].quoted = FALSE;
				break;
      }
      strcpy(ref->field[i].key, fmap[j][new]);
    }
  }
} /* end TranslateReference */


/*****************************************************************************/
/*                                                                           */
/*  ReadBibTex(ref, fp, line_num)                                            */
/*                                                                           */
/*  Read one BibTex entry from file fp.  Keep line_num up to date.           */
/*                                                                           */
/*****************************************************************************/

ReadBibTex(REFERENCE *ref, FILE *fp, int *line_num)
{
  int ch, i, j;  BOOLEAN whitesig;

  /* initialize reference to empty */
  ref->field_count = 0;

  /* scan input file up to next '@' */
  Get;
  while( ch != EOF && ch != '@' )
    Get;
  if( ch == EOF )  return;

  /* read type */
  strcpy(ref->field[0].key, "typ");
  ref->field[0].line_num = *line_num;
  ref->field[0].quoted   = FALSE;
  if( fscanf(fp, "%[a-zA-Z]", ref->field[0].value) != 1 )
  {
	fprintf(stderr, "line %d: type (Article, etc.) expected\n", *line_num);
	exit(1);
  }
  ref->field_count = 1;

  /* skip opening brace */
  SkipGet;
  if( ch != '{' ) /* } */
  {
    fprintf(stderr, "line %d: open brace expected\n", *line_num);
    exit(1);
  }

  /* read tag */
  strcpy(ref->field[1].key, "tag");
  ref->field[1].line_num = *line_num;
  ref->field[1].quoted   = FALSE;
  SkipGet;
  UnGet;
  if( fscanf(fp, "%[a-zA-Z0-9:+]", ref->field[1].value) != 1 )
  {
	fprintf(stderr, "line %d: tag expected\n", *line_num);
	exit(1);
  }
  SkipGet;
  if( ch != ',' )
  {
	fprintf(stderr, "line %d: comma missing after tag\n", *line_num);
	exit(1);
  }
  SkipGet;
  ref->field_count = 2;

  /* read the entries */    /* { */
  for( i = 2;  i < MAX_FIELDS && ch != '}' && ch != EOF;  i++ )
  {
	/* read the field name */
	UnGet;
	if( fscanf(fp, "%[a-zA-Z]", ref->field[i].key) != 1 )
	{
	  fprintf(stderr, "line %d: field name expected\n", *line_num);
	  exit(1);
	}
	ref->field[i].line_num = *line_num;

	/* read the = sign */
	SkipGet;
	if( ch != '=' )
	{
	  fprintf(stderr, "line %d: = character expected\n", *line_num);
	  exit(1);
	}

	SkipGet;
	if( ch == '"' )
	{
	  /* read the string value of the field */
	  ref->field[i].quoted = TRUE;
	  j = 0;  whitesig = TRUE;  Get;
	  while( ch != EOF && ch != '"' && j < MAX_STRING )
	  {
	    if( whitesig || !is_white(ch) )
	    {
	      ref->field[i].value[j++] = ( ch == '\n' || ch == '\t' ) ? ' ' : ch;
	      whitesig = ch != '\n';
	    }
	    Get;
	  }
	  ref->field[i].value[j++] = '\0';
	}
	else
	{
	  /* read the tag value of the field */
	  ref->field[i].quoted = FALSE;
	  UnGet;
	  fscanf(fp, "%[a-zA-Z+]", ref->field[i].value);
	}

	/* read the following comma, if any */
	SkipGet;
	if( ch == ',' )
	{
	  SkipGet;
	}

	if( SearchMap(ref->field[i].key, FMT_BIBTEX) == 0 )
	{ fprintf(stderr, "line %d: BibTex field with unknown keyword %s omitted\n",
	    ref->field[i].line_num, ref->field[i].key);
	  i--;
	}

  }
  ref->field_count = i;

  /* read the closing right brace */ /* '{' */
  if( ch != '}' )
  {
	fprintf(stderr, "line %d: missing right brace after entry\n", *line_num);
	exit(1);
  }
} /* end ReadBibTex */


/*****************************************************************************/
/*                                                                           */
/*  WriteBibTexField(str, fp)                                                */
/*                                                                           */
/*  Write BibTex field str onto file fp.  Take care to write either a        */
/*  quoted or unquoted field depending on the first characer of str; to      */
/*  not write any quotes except (if quoted) at beginning and end; and        */
/*  to insert newline characters from time to time to keep line width down.  */
/*                                                                           */
/*****************************************************************************/

WriteBibTexField(char *str, BOOLEAN quoted, FILE *fp)
{ 
  int i, col, maxcol;
  col = 0;  maxcol = 50;

  if( quoted ) fprintf(fp, "\"");
  for( i = 0;  str[i] != '\0';  i++ )
  {
    if( str[i] != '"' )
    {
      if( str[i] == ' ' && col > maxcol )
      {  str[i] = '\n';
	 col = 0;
	 maxcol = 70;
      }
      putc(str[i], fp);
      col++;
    }
  }
  if( quoted ) fprintf(fp, "\"");
} /* end WriteBibTexField */


/*****************************************************************************/
/*                                                                           */
/*  WriteBibTex(ref, fp)                                                     */
/*                                                                           */
/*  Write ref in BibTex format onto file fp.                                 */
/*                                                                           */
/*****************************************************************************/

WriteBibTex(REFERENCE *ref, FILE *fp)
{ int i;

  /* find and write the type */
  for( i = 0;  i < ref->field_count;  i++ )
  {
    if( strcmp(ref->field[i].key, "typ") == 0 )
    {
      fprintf(fp, "@%s{", ref->field[i].value);
      strcpy(ref->field[i].key, "");
      break;
    }
  }
  if( i == ref->field_count )
  {
    fprintf(fp, "@%s{", "Article");
    fprintf(stderr, "line %d: missing type, substituting \"@Article\"\n",
      ref->field[0].line_num);
  }

  /* find and write the tag */
  for( i = 0;  i < ref->field_count;  i++ )
  {
    if( strcmp(ref->field[i].key, "tag") == 0 )
    {
      fprintf(fp, "%s,\n", ref->field[i].value);   /* } */
      strcpy(ref->field[i].key, "");
      break;
    }
  }
  if( i == ref->field_count )
  {
    fprintf(fp, "%s,\n", "notag");   /* } */
    fprintf(stderr, "line %d: missing tag, substituting \"notag\"\n",
      ref->field[0].line_num);
  }

  /* write the fields */
  for( i = 2;  i < ref->field_count;  i++ )
  {
    if( ref->field[i].key[0] != '\0' )
    { fprintf(fp, "  %s = ", ref->field[i].key);
      WriteBibTexField(ref->field[i].value, ref->field[i].quoted, fp);
      fprintf(fp, ",\n");
    }
  }

  /* write the closing right brace */ /* '{' */
  fprintf(fp, "}\n\n");
  
} /* end WriteBibTex */


/*****************************************************************************/
/*                                                                           */
/*  ReadBardadym(ref, fp, line_num)                                          */
/*                                                                           */
/*  Read one Bardadym entry from file fp.  Keep line_num up to date.         */
/*  Bardadym's format consists of exactly 22 lines as follows:               */
/*                                                                           */
/*    Line    Field       Meaning                                            */
/*    Number  Name                                                           */
/*                                                                           */
/*     1      NUMBER      Reference number                                   */
/*     2      TYPE        Article, thesis, etc. (see below)                  */
/*     3      AUTHOR      Single author or first co-author                   */
/*     4      LASTAUT     Other authors                                      */
/*     5      NAME        Title                                              */
/*     6      SOURCE      Journal name                                       */
/*     7      PUBLISHER   Publisher                                          */
/*     8      YEAR        Year                                               */
/*     9      VOL         Volume                                             */
/*    10      ISSUE       Number                                             */
/*    11      FIRSTPAGE   First page                                         */
/*    12      LASTPAGE    Last page (number of pages in book etc.)           */
/*    13      STATE       Country where work was done                        */
/*    14      INSTIT      Institution where work was done                    */
/*    15      LANGUAGE    Language paper is written in                       */
/*    16      PROBLEM     Problem addressed by the work                      */
/*    17      MODEL       Model used (graph theory, flows, etc.)             */
/*    18      APPLIED     Where system can be applied (university, school..) */
/*    19      ALGORITHM   Approach used (heuristic, colouring, genetic...)   */
/*    10      INTERFACE   User interface to the work                         */
/*    21      SURVEY      True when work contains a survey                   */
/*    22      REFERATS    References to this work in review magazines        */
/*                                                                           */
/*****************************************************************************/
#define BARD_LINES 22

static char *bard_names[BARD_LINES] = {
  "NUMBER", "TYPE", "AUTHOR", "LASTAUT", "NAME", "SOURCE", "PUBLISHER", "YEAR",
  "VOL", "ISSUE", "FIRSTPAGE", "LASTPAGE", "STATE", "INSTIT", "LANGUAGE",
  "PROBLEM", "MODEL", "APPLIED", "ALGORITHM", "INTERFACE", "SURVEY", "REFERATS"
};

ReadBardadym(REFERENCE *ref, FILE *fp, int *line_num)
{
  int i;

  for( i = 0;  i < BARD_LINES;  i++ )
  {
    strcpy(ref->field[i].key, bard_names[i]);
    if( fgets(ref->field[i].value, MAX_STRING, fp) != ref->field[i].value )
    { ref->field_count = 0;
      return;
    }
    ref->field[i].value[strlen(ref->field[i].value) - 1] = '\0';
    ref->field[i].line_num = *line_num;
    ref->field[i].quoted = FALSE;
    (*line_num)++;
  }
  ref->field_count = BARD_LINES;
} /* end ReadBardadym */


/*****************************************************************************/
/*                                                                           */
/*  BOOLEAN MassageBardadym(ref)                                             */
/*                                                                           */
/*  Massage Bardadym reference ref to change the interpretation of its       */
/*  fields in the following way:                                             */
/*                                                                           */
/*  NUMBER        Tag: combination of first author's surname plus year       */
/*  TYPE          Not changed                                                */
/*  AUTHOR        Dropped if empty; else AUTHOR plus LASTAUT                 */
/*                Also, an attempt is made to reformat this entry            */
/*  LASTAUT       Dropped                                                    */
/*  NAME          Not changed                                                */
/*  SOURCE        Dropped if empty                                           */
/*  PUBLISHER     Dropped if empty                                           */
/*  YEAR          Dropped if empty or 0                                      */
/*  VOL           Dropped if empty or 0                                      */
/*  ISSUE         Dropped if empty or 0                                      */
/*  FIRSTPAGE     Dropped if empty or 0                                      */
/*                else not changed if LASTPAGE is 0;                         */
/*                else page number range (i.e. FIRSTPAGE--LASTPAGE)          */
/*  LASTPAGE      Dropped                                                    */
/*  STATE         Dropped                                                    */
/*  INSTIT        Dropped if empty                                           */
/*  LANGUAGE      Dropped                                                    */
/*  PROBLEM       Converted into a list of keywords                          */
/*  MODEL         Dropped                                                    */
/*  APPLIED       Dropped                                                    */
/*  ALGORITHM     Interpreted as keyword and added to PROBLEM, then dropped  */
/*  INTERFACE     Interpreted as keyword and added to PROBLEM, then dropped  */
/*  SURVEY        Interpreted as keyword and added to PROBLEM, then dropped  */
/*  REFERATS      Dropped                                                    */
/*                                                                           */
/*  Return FALSE if it seems that the reference cannot be massaged into      */
/*  anything useful e.g. if the TYPE field has no BibTeX equivalent.         */
/*                                                                           */
/*****************************************************************************/
#define NUMBER		 0
#define TYPE		 1
#define AUTHOR		 2
#define LASTAUT		 3
#define NAME		 4
#define SOURCE		 5
#define PUBLISHER	 6
#define YEAR		 7
#define VOL		 8
#define ISSUE		 9
#define FIRSTPAGE	10
#define LASTPAGE	11
#define STATE		12
#define INSTIT		13
#define LANGUAGE	14
#define PROBLEM		15
#define MODEL		16
#define APPLIED		17
#define ALGORITHM	18
#define INTERFACE	19
#define SURVEY		20
#define REFERATS	21

MassageString(char *str)
{ int i, j;
  j = 0;
  for( i = 0;  str[i] != '\0';  i++ )
  {
    if( is_upper(str[i]) || is_lower(str[i]) || is_digit(str[i]) )
    { if( is_upper(str[i]) )
	str[j++] = to_lower(str[i]);
      else
	str[j++] = str[i];
    }
  }
  str[j++] = '\0';
} /* end MassageString */


BOOLEAN MassageBardadym(REFERENCE *ref)
{
  int i; char *keyword;
  char buff[MAX_STRING], buff2[MAX_STRING], buff3[MAX_STRING];
  /* ***
  static char save_buff[MAX_STRING] = "";
  static char append_ch[1] = "a";
  *** */

  for( i = 0;  i < BARD_LINES;  i++ )  switch( i )
  {
    case NUMBER:

	/* set buff to the author field, or else unknown */
	if( sscanf(ref->field[AUTHOR].value, "%s", buff) != 1 )
	  strcpy(buff, "unknown");

	/* append the year to buff, or 0000 if missing */
	if( strcmp(ref->field[YEAR].value, "")  == 0 ||
	    strcmp(ref->field[YEAR].value, "0") == 0 )
	  strcat(buff, "0000");
	else
	  strcat(buff, ref->field[YEAR].value);

	/* tidy up buff to be suitable as a tag */
	MassageString(buff);

	/* if same as previous tag, add a sequence letter */
	/* ***
	if( strcmp(buff, save_buff) == 0 )
	{ strcat(buff, append_ch);
	  append_ch[0]++;
	}
	else
	{
	  strcpy(save_buff, buff);
	  append_ch[0] = 'a';
	}
	*** */

	strcpy(ref->field[NUMBER].value, buff);
	break;


    case AUTHOR:

	/* drop whole field if value is empty */
	if( strcmp(ref->field[AUTHOR].value, "") == 0 )
	{ strcpy(ref->field[AUTHOR].key, "");
	}
	else
	{
	  /* tidy up the AUTHOR field by putting comma after surname */   
	  if( sscanf(ref->field[AUTHOR].value, "%s %[a-zA-Z0-9.]",
	    buff2, buff3) == 2 )
	  {
	    sprintf(ref->field[AUTHOR].value, "%s, %s", buff2, buff3);
	  }

	  /* add LASTAUT field; replace commas by and within it */
	  if( strcmp(ref->field[LASTAUT].value, "") != 0 )
	  { char *p, *q;  BOOLEAN first_space = TRUE;
	    strcat(ref->field[AUTHOR].value, " and ");

	    p = &ref->field[AUTHOR].value[strlen(ref->field[AUTHOR].value)];
	    for( q = &ref->field[LASTAUT].value[0];  *q != '\0';  q++ )
	    { if( *q == ',' )
	      {
		*p++ = ' ';
		*p++ = 'a';
		*p++ = 'n';
		*p++ = 'd';
		*p++ = ' ';
		while( *(q+1) == ' ' )  q++;
		first_space = TRUE;
	      }
	      else if( *q == ' ' && first_space)
	      {
		*p++ = ',';
		*p++ = *q;
		first_space = FALSE;
	      }
	      else
	      {
		*p++ = *q;
	      }
	    }
	    *p++ = '\0';
	  }
	}
	break;


    case FIRSTPAGE:

	/* drop field if value is empty or 0 */
	if( strcmp(ref->field[i].value, "")  == 0 ||
	    strcmp(ref->field[i].value, "0") == 0 )
	  strcpy(ref->field[i].key, "");

	/* page number range if LASTPAGE is non-empty and non-zero */
	else if( strcmp(ref->field[LASTPAGE].value, "")  != 0 &&
		 strcmp(ref->field[LASTPAGE].value, "0") != 0 )
	{
	  strcat(ref->field[FIRSTPAGE].value, "--");
	  strcat(ref->field[FIRSTPAGE].value, ref->field[LASTPAGE].value);
	}

	/* else unchanged */
	break;


    case TYPE:
    case NAME:

	/* leave intact */
	break;

    case VOL:
    case ISSUE:
    case YEAR:

	/* drop field if value is 0 */
	if( strcmp(ref->field[i].value, "0")  == 0 )
	  strcpy(ref->field[i].key, "");

	/* drop field if value is empty */
	if( strcmp(ref->field[i].value, "") == 0 )
	  strcpy(ref->field[i].key, "");
	break;


    case SOURCE:
    case PUBLISHER:
    case INSTIT:

	/* drop field if value is empty */
	if( strcmp(ref->field[i].value, "") == 0 )
	  strcpy(ref->field[i].key, "");
	break;


    case LASTAUT:
    case LASTPAGE:
    case STATE:
    case LANGUAGE:
    case REFERATS:
    case INTERFACE:

	/* drop field unconditionally */
	strcpy(ref->field[i].key, "");
	break;


    case PROBLEM:

	/* find keyword appropriate to this field */
	switch( *ref->field[i].value )
	{
	  case 'T':	keyword = "school";  break;
	  case 'C':	keyword = "school";  break;
	  case 'L':	keyword = "university";  break;
	  case 'F':	keyword = "university";  break;
	  case 'R':	keyword = "room";  break;
	  case 'E':	keyword = "examination";  break;
	  case 'A':	keyword = "";  break;
	  case 'D':	keyword = "";  break;
	  case 'G':	keyword = "";  break;
	  case 'S':	keyword = "competition";  break;
	  case 'M':	keyword = "management information systems";  break;
	  default :	keyword = "";  break;
	}

	/* replace field value by this keyword */
	strcpy(ref->field[i].value, keyword);
	break;


    case MODEL:
    case APPLIED:

	/* drop field unconditionally */
	strcpy(ref->field[i].key, "");
	break;


    case ALGORITHM:

	/* find keyword appropriate to this field */
	switch( *ref->field[i].value )
	{
	  case 'H':	keyword = "heuristic";  break;
	  case 'F':	keyword = "matching flow";  break;
	  case 'L':	keyword = "lagrangian relaxation";  break;
	  case 'C':	keyword = "colouring coloring";  break;
	  case 'T':	keyword = "tabu search";  break;
	  case 'S':	keyword = "simulated annealing";  break;
	  case 'M':	keyword = "monte carlo";  break;
	  case 'P':	keyword = "";  break;
	  case 'I':	keyword = "";  break;
	  case 'D':	keyword = "";  break;
	  case 'A':	keyword = "artificial intelligence";  break;
	  case 'B':	keyword = "backtracking branch-and-bound";  break;
	  case 'G':	keyword = "";  break;
	  case 'O':	keyword = "";  break;
	  default :	keyword = "";  break;
	}

	/* append keyword (if any) to PROBLEM field */
	if( strcmp(keyword, "") != 0 )
	{ if( strcmp(ref->field[PROBLEM].value, "") != 0 )
	    strcat(ref->field[PROBLEM].value, " ");
	  strcat(ref->field[PROBLEM].value, keyword);
	}

	/* now drop this field */
	strcpy(ref->field[i].key, "");
	break;


    case SURVEY:

	/* append survey keyword (if appropriate) to PROBLEM field */
	if( strcmp(ref->field[i].value, "Survey") == 0 )
	{ if( strcmp(ref->field[PROBLEM].value, "") != 0 )
	    strcat(ref->field[PROBLEM].value, " ");
	  strcat(ref->field[PROBLEM].value, "survey");
	}

	/* now drop this field */
	strcpy(ref->field[i].key, "");
	break;

  }

  /* now drop PROBLEM field if its value is empty */
  if( strcmp(ref->field[PROBLEM].value, "") == 0 )
    strcpy(ref->field[PROBLEM].key, "");

  /* return TRUE if the type is known and has a BibTex equivalent */
  i = SearchTypes(ref->field[TYPE].value, FMT_BARDADYM);
  return( i != 0 && strcmp(tmap[i][FMT_BIBTEX], "") != 0 );
} /* end MassageBardadym */


/*****************************************************************************/
/*                                                                           */
/*  WriteBardadym(ref, fp)                                                   */
/*                                                                           */
/*  Write ref in Bardadym format onto file fp.                               */
/*                                                                           */
/*****************************************************************************/

WriteBardadym(REFERENCE *ref, FILE *fp)
{
  int i;

  for( i = 0;  i < ref->field_count;  i++ )
  {
    fprintf(fp, "%s\n", ref->field[i].value);
  }
} /* end WriteBardadym */


/*****************************************************************************/
/*                                                                           */
/*  ReadLout(ref, fp, line_num)                                              */
/*                                                                           */
/*  Read one Lout entry from file fp.  Keep line_num up to date.             */
/*                                                                           */
/*****************************************************************************/

ReadLout(REFERENCE *ref, FILE *fp, int *line_num)
{
  int ch, i, j, level;  char buff[MAX_STRING];

  /* initialize reference to empty */
  ref->field_count = 0;

  /* scan input file up to next left brace */ 
  Get;
  while( ch != EOF && ch != '{' )  /* '}' */
    Get;
  if( ch == EOF )  return;

  /* read @Reference keyword */
  SkipGet;
  if( ch != '@' || fscanf(fp, "%[a-zA-Z]", buff) != 1 ||
      strcmp(buff, "Reference") != 0 )
  {
	fprintf(stderr, "line %d: @Reference keyword expected\n", *line_num);
	exit(1);
  }
  SkipGet;

  /* read the entries */    /* { */
  for( i = 0;  i < MAX_FIELDS && ch != '}' && ch != EOF;  i++ )
  {
	/* read the field name */
	UnGet;
	if( fscanf(fp, "%[@a-zA-Z]", ref->field[i].key) != 1 )
	{
	  fprintf(stderr, "line %d: field name expected\n", *line_num);
	  exit(1);
	}
	ref->field[i].line_num = *line_num;

	/* read the left brace */
	SkipGet;
	if( ch != '{' ) /* } */
	{
	  fprintf(stderr, "line %d: left brace expected\n", *line_num);
	  exit(1);
	}

	SkipGet;  level = 1;  j = 0;
	ref->field[i].quoted = (ch == '"');
	while( ch != EOF && level > 0 )
	{
	  if( ch == '"' )
	  { /* skip it, too dangerous */
	  }
	  else if( ch == '{' )
	  { level++;
	    if( j < MAX_STRING )
	      ref->field[i].value[j++] = ch;
	  }
	  else if( ch == '}' )
	  { level--;
	    if( level > 0 && j < MAX_STRING )  ref->field[i].value[j++] = ch;
	  }
	  else if( j < MAX_STRING )
	    ref->field[i].value[j++] = ( ch == '\n' || ch == '\t' ) ? ' ' : ch;
	  Get;
	}
	if( j == MAX_STRING )
	{
	  fprintf(stderr, "line %d: string too long\n", *line_num);
	  exit(1);
	}
	while( j > 0 && is_white(ref->field[i].value[j-1]) )  j--;
	ref->field[i].value[j++] = '\0';

	if( SearchMap(ref->field[i].key, FMT_LOUT) == 0 )
	{ fprintf(stderr, "line %d: Lout field with unknown keyword %s omitted\n",
	    *line_num, ref->field[i].key);
	  i--;
	}

	/* skip to next field */
	SkipGet;

  }
  ref->field_count = i;

  /* read the closing right brace */
  /* '{' */
  if( ch != '}' )
  {
	fprintf(stderr, "line %d: missing right brace after entry\n", *line_num);
	exit(1);
  }
  
} /* end ReadLout */


/*****************************************************************************/
/*                                                                           */
/*  WriteLoutField(str, quoted, fp)                                          */
/*                                                                           */
/*  Write Lout field str onto file fp.  Take care to write either a          */
/*  quoted or unquoted field depending on the first characer of str; to      */
/*  not write any quotes except (if quoted) at beginning and end; and        */
/*  to insert newline characters from time to time to keep line width down.  */
/*                                                                           */
/*****************************************************************************/

WriteLoutField(char *str, BOOLEAN quoted, FILE *fp)
{ 
  int i, col, maxcol;
  col = 0;  maxcol = 50;

  if( quoted ) fprintf(fp, "\"");
  for( i = 0;  str[i] != '\0';  i++ )
  {
    if( str[i] != '"' )
    {
      if( str[i] == ' ' && col > maxcol )
      {  str[i] = '\n';
	 col = 0;
	 maxcol = 70;
      }
      putc(str[i], fp);
      col++;
    }
  }
  if( quoted ) fprintf(fp, "\"");
} /* end WriteLoutField */


/*****************************************************************************/
/*                                                                           */
/*  WriteLout(ref, fp)                                                       */
/*                                                                           */
/*  Write ref in Lout format onto file fp.                                   */
/*                                                                           */
/*****************************************************************************/

WriteLout(REFERENCE *ref, FILE *fp)
{ int i;

  /* write the header */
  fprintf(fp, "{ @Reference\n"); /* } */

  /* write the fields */
  for( i = 0;  i < ref->field_count;  i++ )
  {
    if( ref->field[i].key[0] != '\0' )
    {
	fprintf(fp, "    %s {", ref->field[i].key);
	if( ref->field[i].value[0] != '\0' )
	{
	  fprintf(fp, " ");
	  WriteLoutField(ref->field[i].value, ref->field[i].quoted, fp);
	  fprintf(fp, " ");
	}
	fprintf(fp, "}\n");
    }
  }

  /* write the closing right brace */
  /* '{' */
  fprintf(fp, "}\n\n");
  
} /* end WriteLout */


/*****************************************************************************/
/*                                                                           */
/*  ReadReference(ref, fp, line_num, fmt)                                    */
/*                                                                           */
/*  Read one reference in the given format.                                  */
/*                                                                           */
/*****************************************************************************/

ReadReference(REFERENCE *ref, FILE *fp, int *line_num, FORMAT fmt)
{
  switch( fmt )
  {
    case FMT_LOUT:	ReadLout(ref, fp, line_num);
			break;

    case FMT_BIBTEX:	ReadBibTex(ref, fp, line_num);
			break;

    case FMT_BARDADYM:	ReadBardadym(ref, fp, line_num);
			break;

    default:		fprintf(fp, "unknown format number %d\n", fmt);
			exit(1);
			break;
  }
} /* end ReadReference */


/*****************************************************************************/
/*                                                                           */
/*  WriteReference(ref, fp, fmt)                                             */
/*                                                                           */
/*  Write one reference in the given format.                                 */
/*                                                                           */
/*****************************************************************************/

WriteReference(REFERENCE *ref, FILE *fp, FORMAT fmt)
{
  switch( fmt )
  {
    case FMT_LOUT:	WriteLout(ref, fp);
			break;

    case FMT_BIBTEX:	WriteBibTex(ref, fp);
			break;

    case FMT_BARDADYM:	WriteBardadym(ref, fp);
			break;

    default:		fprintf(fp, "unknown format number %d\n", fmt);
			exit(1);
			break;
  }
} /* end WriteReference */


/*****************************************************************************/
/*                                                                           */
/*  main(argc, argv)                                                         */
/*                                                                           */
/*  Translate reference file from one format to another.                     */
/*                                                                           */
/*****************************************************************************/

main(int argc, char *argv[])
{ int i, j;
  REFERENCE ref;  int line_num;
  FORMAT infmt, outfmt;
  line_num = 1;

  if( argc != 3 )
  {
    fprintf(stderr, "usage: %s inputformat outputformat", argv[0]);
    exit(1);
  }

  /* ***
  for( i = 0;  i < MAX_TYPES;  i++ )
  {
    for( j = 0;  j < MAX_FORMATS;  j++ )
    {
      fprintf(stderr, "\"%20s\", ", tmap[i][j]);
    }
    fprintf(stderr, "\n");
  }
  *** */

  infmt = FindFormat(argv[1]);
  outfmt = FindFormat(argv[2]);

  ReadReference(&ref, stdin, &line_num, infmt);
  while( ref.field_count >= 2 )
  {
    if( infmt == FMT_BARDADYM && outfmt != FMT_BARDADYM )
    {
      if( MassageBardadym(&ref) )
      { TranslateReference(&ref, infmt, outfmt);
        WriteReference(&ref, stdout, outfmt);
      }
      else
      { fprintf(stderr, "line %d: reference dropped (can't translate type %s)\n",
	  ref.field[0].line_num, ref.field[TYPE].value);
      }
    }
    else
    { TranslateReference(&ref, infmt, outfmt);
      WriteReference(&ref, stdout, outfmt);
    }
    ReadReference(&ref, stdin, &line_num, infmt);
  }

} /* end main */
