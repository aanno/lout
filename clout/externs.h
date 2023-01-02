/*@externs.h:External Declarations:Directories and file conventions@**********/
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
/*  FILE:         externs.h                                                  */
/*  MODULE:       External Declarations                                      */
/*                                                                           */
/*****************************************************************************/
#ifndef EXTERNS_HEADER_H
#define EXTERNS_HEADER_H

#include "enums.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <locale.h>

#define INLINE __attribute__((always_inline)) inline

#if LOCALE_ON
#include <nl_types.h>
extern nl_catd MsgCat;
#define condcatgets(cat, set, msg, s) (cat ? catgets(cat, set, msg, s) : s)
#else
#define condcatgets(cat, set, msg, s) s
#endif

typedef unsigned char FULL_CHAR;

// TODO: making this BOOLEAN will break crossrefs
#define	BOOLEAN2		bool
#define	BOOLEAN		unsigned
#define	FALSE		false
#define	TRUE		true
#define	bool2s(x)		(x ? AsciiToFull("TRUE") : AsciiToFull("FALSE") )

/*@::assert(), debug(), debug flags@******************************************/
/*                                                                           */
/*  ASSERT AND DEBUG CODE                                                    */
/*                                                                           */
/*****************************************************************************/

/*****	z27.c	  Debug Service		**************************************/
#if DEBUG_ON
extern	void	  DebugInit(FULL_CHAR *str);
extern	void	  Debug(int category, int urgency, char *str, ...);
extern	void	  ProfileOn(char *str);
extern	void	  ProfileOff(char *str);
extern	void	  ProfilePrint(void);
#endif

#if DEBUG_ON

struct dbs
{	char	*flag;			/* external names for debug flags    */
	BOOLEAN2	on[3];			/* the debug flags                   */
};
extern	struct dbs 	dbg[];

/* debug routines */
#define debug0(cat, urg, str)                				\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str); }
#define debug1(cat, urg, str, p1)					\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1); }
#define debug2(cat, urg, str, p1, p2)					\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2); }
#define debug3(cat, urg, str, p1, p2, p3)				\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2, p3); }
#define debug4(cat, urg, str, p1, p2, p3, p4)				\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2, p3, p4); }
#define debug5(cat, urg, str, p1, p2, p3, p4, p5)			\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2, p3, p4, p5); }
#define debug6(cat, urg, str, p1, p2, p3, p4, p5, p6)			\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2, p3, p4, p5, p6); }
#define debug7(cat, urg, str, p1, p2, p3, p4, p5, p6, p7)		\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2, p3, p4, p5,p6,p7); }
#define debug8(cat, urg, str, p1, p2, p3, p4, p5, p6, p7, p8)		\
    { if( dbg[cat].on[urg] ) Debug(cat, urg, str, p1, p2,p3,p4,p5,p6,p7,p8); }
#define	ifdebug(cat, urg, x)						\
    { if( dbg[cat].on[urg] ) { x; } }

#define debugcond0(cat, urg, cond, str)                			\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str); }
#define debugcond1(cat, urg, cond, str, p1)				\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1); }
#define debugcond2(cat, urg, cond, str, p1, p2)				\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1, p2); }
#define debugcond3(cat, urg, cond, str, p1, p2, p3)			\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1, p2, p3); }
#define debugcond4(cat, urg, cond, str, p1, p2, p3, p4)			\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1, p2, p3, p4); }
#define debugcond5(cat, urg, cond, str, p1, p2, p3, p4, p5)		\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1, p2, p3, p4, p5);}
#define debugcond6(cat, urg, cond, str, p1, p2, p3, p4, p5, p6)		\
    { if( dbg[cat].on[urg] && cond ) Debug(cat, urg, str, p1, p2,p3,p4,p5,p6);}
#define	ifdebugcond(cat, urg, cond, x)					\
    { if( dbg[cat].on[urg] && cond ) { x; } }
#define	debug_init(str)							\
    DebugInit(str)

/* debug styles */
#define	D	 0
#define	DD	 1
#define	DDD	 2

/* debug flags */
#define	DSP	 1		/*  z01.c   -dsp   Supervise                 */
#define	DLA	 2		/*  z02.c   -dla   Lexical Analyser          */
#define	DFS	 3		/*  z03.c   -dfs   File Service              */
#define	DTS	 4		/*  z04.c   -dts   Token Service             */
#define	DRD	 5		/*  z05.c   -drd   Read Definitions          */
#define	DOP	 6		/*  z06.c   -dop   Object Parser             */
#define	DOS	 7		/*  z07.c   -dos   Object Service            */
#define	DOM	 8		/*  z08.c   -dom   Object Manifest           */
#define	DCE	 9		/*  z09.c   -dce   Closure Expansion         */
#define	DCR	10		/*  z10.c   -dcr   Cross References	     */
#define	DSS	11		/*  z11.c   -dss   Style Service	     */
#define	DSF	12		/*  z12.c   -dsf   Size Finder               */
#define	DOB	13		/*  z13.c   -dob   Object Breaking	     */
#define	DOF	14		/*  z14.c   -dof   Object Filling	     */
#define	DSC	15		/*  z15.c   -dsc   Size Constraints          */
#define	DSA	16		/*  z16.c   -dsa   Size Adjustments	     */
#define	DGW	17		/*  z17.c   -dgw   Gap Widths                */
#define	DGT	18		/*  z18.c   -dgt   Galley Transfer           */
#define	DGA	19		/*  z19.c   -dgf   Galley Attaching          */
#define	DGF	20		/*  z20.c   -dgf   Galley Flushing           */
#define	DGM	21		/*  z21.c   -dgm   Galley Maker              */
#define	DGS	22		/*  z22.c   -dgs   Galley Service            */
#define	DGP	23		/*  z23.c   -dgp   Galley Printer            */
#define	DPS	24		/*  z24.c   -dps   Print Service             */
#define	DOE	25		/*  z25.c   -doe   Object Echo               */
#define	DES	26		/*  z26.c   -des   Echo Service		     */
#define	DZZ	27		/*  z27.c   -dzz   Debug Service             */
#define	DYY	28		/*  z28.c   -dyy   Error Service             */
#define	DST	29		/*  z29.c   -dst   Symbol Table              */
#define	DSU	30		/*  z30.c   -dsu   Symbol Uses               */
#define	DMA	31		/*  z31.c   -dma   Memory Allocator          */
#define	DCS	32		/*  z32.c   -dcs   Counter Service           */
#define	DBS	33		/*  z33.c   -dbs   Database Service          */
#define	DRS	34		/*  z34.c   -drs   Rotation Service          */
#define	DTK	35		/*  z35.c   -dtk   Time Keeper               */
#define	DHY	36		/*  z36.c   -dhy   Hyphenation               */
#define	DFT	37		/*  z37.c   -dft   Font Service              */
#define	DCM	38		/*  z38.c   -dcm   Character Mapping         */
#define	DSH	39		/*  z39.c   -dsh   String Handler            */
#define	DFH	40		/*  z40.c   -dsh   Filter Handler            */
#define	DIO	41		/*  z41.c   -dio   Object Input-Output       */
#define	DCO	42		/*  z42.c   -dco   Colour Service            */
#define	DLS	43		/*  z43.c   -dls   Language Service          */
#define	DVH	44		/*  z44.c   -dvh   Vertical Hyphenation      */
#define	DEX	45		/*  z45.c   -dex   External Sort             */
#define	DOG	46		/*  z46.c   -dex   Optimal Galleys           */
#define	DET	47		/*  z47.c   -det   Environment Table         */
#define	DPD	48		/*  z48.c   -dpd   PDF Back End (old)        */
#define	DPO	49		/*  z49.c   -dpo   PostScript Back End       */
#define	DPF	50		/*  z50.c   -dpf   PDF Back End              */
#define	DPT	51		/*  z51.c   -dpt   Plain Text Back End       */
#define	DTX	52		/*  z52.c   -dtx   Texture Service           */
#define	DPP	53		/*          -dpp   Profiling                 */
#define	ANY	54		/*          -d     any                       */

#else
#define ifdebug(cat, urg, x)
#define debug0(cat, urg, str)
#define debug1(cat, urg, str, p1)
#define debug2(cat, urg, str, p1, p2)
#define debug3(cat, urg, str, p1, p2, p3)
#define debug4(cat, urg, str, p1, p2, p3, p4)
#define debug5(cat, urg, str, p1, p2, p3, p4, p5)
#define debug6(cat, urg, str, p1, p2, p3, p4, p5, p6)
#define debug7(cat, urg, str, p1, p2, p3, p4, p5, p6, p7)
#define debug8(cat, urg, str, p1, p2, p3, p4, p5, p6, p7, p8)

#define debugcond0(cat, urg, cond, str)
#define debugcond1(cat, urg, cond, str, p1)
#define debugcond2(cat, urg, cond, str, p1, p2)
#define debugcond3(cat, urg, cond, str, p1, p2, p3)
#define debugcond4(cat, urg, cond, str, p1, p2, p3, p4)
#define debugcond5(cat, urg, cond, str, p1, p2, p3, p4, p5)
#define debugcond6(cat, urg, cond, str, p1, p2, p3, p4, p5, p6)
#define	ifdebugcond(cat, urg, cond, x)
#define	debug_init(str)	Error(1, 4, "%s - debug flags not implemented", \
	FATAL, no_fpos, str)
#endif

/*****************************************************************************/
/*                                                                           */
/*  typedef POINTER- name for type of generic pointer                        */
/*                                                                           */
/*****************************************************************************/

typedef void *POINTER;

/*****************************************************************************/
/*                                                                           */
/*  typedef FILE_NUM - the internal representation of a file.                */
/*                                                                           */
/*****************************************************************************/

typedef unsigned short	FILE_NUM;
#define	NO_FILE		0


/*****************************************************************************/
/*                                                                           */
/*  typedef FILE_POS - a position in the set of input files.                 */
/*                                                                           */
/*****************************************************************************/

typedef	struct
{ OBJTYPE	 otype;			/* space for object type field	     */
  unsigned char	 orec_size;		/* space for object record size      */
  FILE_NUM	 ofile_num;		/* no. of file this record is from   */
  unsigned       oline_num  : 20;	/* the line number of this record    */
  unsigned       ocol_num   : 12;	/* column number this is related to  */
} FILE_POS;

/* error types */
#define	INTERN		     0		/* internal error (i.e. bug)         */
#define	FATAL		     1		/* fatal error, abort now            */
#define	FATAL_WITH_USAGE     2		/* fatal error, abort now + usage    */
#define	WARN		     3		/* warning, non-fatal                */
#define UNEXPECTED_DEFAULT FATAL /* switch which uses default branch: this is unexpected and points to uninitialized memory */

// from z03 header below - but used here
extern	FILE_POS  *no_fpos;
// from z36 header below - but used here
extern	POINTER	  Error(int set_num, int msg_num, char *str, int etype, FILE_POS *pos, ...);

#if ASSERT_ON
#define assert(c, m)							\
{ if( !(c) )  Error(1, 2, "assert failed in %s", INTERN, no_fpos, m); }
#define assert1(c, m, p1)						\
   { if( !(c) )  Error(1, 3, "assert failed in %s %s", INTERN, no_fpos,m, p1); }
#else
#define assert(c, m)
#define assert1(c, m, p1)
#endif


/*****************************************************************************/
/*                                                                           */
/*  Include, font and database directories, and the DEBUG_ON and ASSERT_ON   */
/*  flags (defined by -D options on the cc command line in the makefile).    */
/*                                                                           */
/*  LATIN         Non-zero means compile for ISO-LATIN-1 char set.           */
/*  LIB_DIR       The system directory where library files are kept          */
/*  INCL_DIR      The subdirectory of LIB_DIR where @Include files are kept  */
/*  FONT_DIR      The subdirectory of LIB_DIR where .AFM font files are kept */
/*  MAPS_DIR      The subdirectory of LIB_DIR where .LCM files are kept      */
/*  DATA_DIR      The subdirectory of LIB_DIR where database files are kept  */
/*  HYPH_DIR      The subdirectory of LIB_DIR where hyphenation files kept   */
/*  LOCALE_DIR    The subdirectory of LIB_DIR where locale files are kept    */
/*  CHAR_IN       Determines assignment of input chars to lex classes        */
/*  CHAR_OUT      Determines appearance of literal chars in output           */
/*  DEBUG_ON      Non-zero means compile debug code (lout -d)                */
/*  ASSERT_ON     Non-zero means test assertions                             */
/*  LOCALE_ON     Non-zero means compile setlocale() etc. code               */
/*                                                                           */
/*  #define  LIB_DIR    "/usr/local/lib/lout"                                */
/*  #define  INCL_DIR   "include"                                            */
/*  #define  FONT_DIR   "font"                                               */
/*  #define  MAPS_DIR   "maps"                                               */
/*  #define  DATA_DIR   "data"                                               */
/*  #define  HYPH_DIR   "hyph"                                               */
/*  #define  LOCALE_DIR "locale"  (only used if LOCALE_ON)                   */
/*  #define  CHAR_IN    0                                                    */
/*  #define  CHAR_OUT   0                                                    */
/*  #define  DEBUG_ON   0                                                    */
/*  #define  ASSERT_ON  1                                                    */
/*  #define  LOCALE_ON  1                                                    */
/*                                                                           */
/*****************************************************************************/


/*@::File naming conventions and version@*************************************/
/*                                                                           */
/*  File naming conventions and version                                      */
/*                                                                           */
/*  LOUT_VERSION        Version information                                  */
/*  CROSS_DB            The default name of the cross reference database     */
/*  SOURCE_SUFFIX       Optional suffix of source files and include files    */
/*  INDEX_SUFFIX        The suffix of database index files                   */
/*  NEW_INDEX_SUFFIX    The suffix of new database index files               */
/*  DATA_SUFFIX         The suffix of database data files                    */
/*  NEW_DATA_SUFFIX     The additional suffix of new database data files     */
/*  HYPH_SUFFIX         The suffix of unpacked hyphenation files             */
/*  HYPH_PACKED_SUFFIX  The suffix of packed hyphenation files               */
/*  FILTER_IN           The prefix of the name of the input file to filters  */
/*  FILTER_OUT          The prefix of the name of the output file to filters */
/*  FILTER_ERR          The name of the error file to filters                */
/*                                                                           */
/*****************************************************************************/

// typedef unsigned char FULL_CHAR;
#define              AsciiToFull(x)        ( (FULL_CHAR *) (x) )

extern const FULL_CHAR *const LOUT_VERSION;
extern const FULL_CHAR *const CROSS_DB;
extern const FULL_CHAR *const SOURCE_SUFFIX;
extern const FULL_CHAR *const INDEX_SUFFIX;
extern const FULL_CHAR *const NEW_INDEX_SUFFIX;
extern const FULL_CHAR *const DATA_SUFFIX;
extern const FULL_CHAR *const NEW_DATA_SUFFIX;
extern const FULL_CHAR *const HYPH_SUFFIX;
extern const FULL_CHAR *const HYPH_PACKED_SUFFIX;
extern const FULL_CHAR *const FILTER_IN;
extern const FULL_CHAR *const FILTER_OUT;
extern const FULL_CHAR *const FILTER_ERR;


/*****************************************************************************/
/*                                                                           */
/*  Operating system dependent things                                        */
/*                                                                           */
/*  (1) Reading files                                                        */
/*                                                                           */
/*  Starting from Version 3.27, Lout reads all files in "binary mode", so    */
/*  that the actual characters in the file are presented to Lout.  Lout      */
/*  accepts any of LF, CR, LF+CR, CR+LF as a valid line ending on any        */
/*  line of any file, taking the longest match as usual.                     */
/*                                                                           */
/*  This strategy has two major advantages:  files transferred between       */
/*  operating systems are always read correctly without needing any          */
/*  conversion, and ftell() always works properly on binary files (its       */
/*  behaviour on text files has been observed to vary).                      */
/*                                                                           */
/*  READ_FILE         Mode passed to fopen() when reading any file at all    */
/*                                                                           */
/*  (2) Writing files                                                        */
/*                                                                           */
/*  Starting from Version 3.27, Lout writes all files in "binary mode",      */
/*  so that the actual characters in the file are all explicitly written     */
/*  by Lout.  The macro STR_NEWLINE defines what character(s) Lout will      */
/*  write when it wants to end the line; throughout Lout the "\n" thing      */
/*  never appears, only STR_NEWLINE.  STR_NEWLINE is defined below to be     */
/*  "\n" on Unix, "\r\n" on DOS, and "\r" on Mac.                            */
/*                                                                           */
/*  This strategy might seem to be overkill, given that writing "\n" on      */
/*  a DOS text file would write "\r\n" anyway.  Unfortunately, when Lout     */
/*  is writing a database file, it uses ftell() as it is writing to find     */
/*  out where it's up to.  Since we can only be sure that ftell() will       */
/*  work on binary files, we've made all file writing be binary.             */
/*                                                                           */
/*  WRITE_FILE        Mode passed to fopen() when writing any file at all    */
/*  APPEND_FILE       Mode passed to fopen() when appending any file at all  */
/*  STR_NEWLINE       The string to write to a binary file to end a line     */
/*                                                                           */
/*  (3) Directory character                                                  */
/*                                                                           */
/*  Operating systems differ in the character used in path names.            */
/*                                                                           */
/*  STR_DIR           Directory character used in file path names            */
/*                                                                           */
/*  (4) System command and file name for uncompressing EPS files             */
/*                                                                           */
/*  UNCOMPRESS_COM    System command for uncompressing compressed EPS file   */
/*  LOUT_EPS          Name of temporary uncompressed EPS file                */
/*                                                                           */
/*  There is one further call to system() in the Lout source code:  the one  */
/*  that implements filtered parameters such as prg2lout.  The strings       */
/*  passed to this call to system() are the values of @Filter symbols        */
/*  within Lout definitions.                                                 */
/*                                                                           */
/*****************************************************************************/

extern const char* const READ_FILE;
extern const char* const WRITE_FILE;
extern const char* const APPEND_FILE;
extern const FULL_CHAR* const STR_NEWLINE;
extern const FULL_CHAR* const STR_DIR;
extern const char* const UNCOMPRESS_COM;
extern const char* const PDFTOPS_COM;
extern const char* const CONVERT_COM;
extern const char* const LOUT_EPS;

/*@::Significant limits@******************************************************/
/*                                                                           */
/*  Significant Limits (other insignificant ones appear in other files)      */
/*                                                                           */
/*  MAX_FULL_LENGTH     The maximum value storable in type FULL_LENGTH.      */
/*                      NB this cannot be 2**31 - 1 because there are        */
/*                      intermediate results that exceed MAX_FULL_LENGTH     */
/*                      and are subsequently reduced to MAX_FULL_LENGTH.     */
/*                      For example, some intermediate results may exceed    */
/*                      MAX_FULL_LENGTH by a factor of SF, which is defined  */
/*                      below to be 256 (2**8).  The value given is 2**23-1, */
/*                      which is about 148 metres in Lout's precision.       */
/*                                                                           */
/*  MAX_FILES           The maximum number of files.  This could only be     */
/*                      increased if the file_num() field of type FILE_POS   */
/*                      is enlarged beyond its present 16 bits.              */
/*                                                                           */
/*  MAX_LINE            1 + the maximum length of an input line in source    */
/*                      and database files.  This is used for the lexical    */
/*                      analyser's input line buffer only, and could be      */
/*                      increased immediately to 4096, and even further if   */
/*                      more than the current 12 bits was assigned to the    */
/*                      col_num() field of type FILE_POS.                    */
/*                                                                           */
/*  MAX_WORD            1 + the maximum length of a word storable in an      */
/*                      object record, which includes all file path names    */
/*                      too.  It is reasonable to make this MAX_LINE, since  */
/*                      a word longer than MAX_LINE cannot be read in.       */
/*                                                                           */
/*  MAX_OBJECT_REC      1 + the maximum size of an object record, measured   */
/*                      in ALIGNs.  The value chosen should exceed           */
/*                      ceiling( (wr + MAX_WORD - 4) / sizeof(ALIGN) )       */
/*                      where wr = sizeof(struct word_rec), so that words of */
/*                      length MAX_WORD-1 can be stored in an object record. */
/*                                                                           */
/*  MAX_BUFF            1 + the maximum length of a "standard buffer"; these */
/*                      buffers are used in a variety of places throughout   */
/*                      the program for holding one line of a font file,     */
/*                      one file path name, one symbol full name, etc.  This */
/*                      may be increased immediately without limit.          */
/*                                                                           */
/*  MAX_FONT            The maximum number of sized fonts allowed.           */
/*                                                                           */
/*  MAX_COLOUR          The maximum number of distinct left parameters of    */
/*                      @SetColour and @SetColor symbols allowed (after      */
/*                      evaluation).                                         */
/*                                                                           */
/*  MAX_TEXTURE         The maximum number of distinct left parameters of    */
/*                      the @SetTexture symbol allowed (after evaluation).   */
/*                                                                           */
/*  MAX_LANGUAGE        The maximum number of distinct languages allowed.    */
/*                      This can be increased beyond 256 only by setting     */
/*                      aside a larger word_language() field.                */
/*                                                                           */
/*  MAX_LEX_STACK       The maximum depth of @Includes and @Databases.  This */
/*                      can be increased immediately by any small amount.    */
/*                                                                           */
/*  MAX_CHARS		The maximimum number of characters in a font.  This  */
/*                      cannot be increased easily.                          */
/*                                                                           */
/*  MAX_HCOPIES         The maximimum number of copies of one running header */
/*                      that can appear correctly on one page.  Can be       */
/*                      increased to any small positive integer.             */
/*                                                                           */
/*  MAX_FORMAT          The maximum number of characters for sscanf formats  */
/*                      for splitting strings with tab-delimited fields.     */
/*                                                                           */
/*****************************************************************************/

/*@::Significant limits@******************************************************/
/*                                                                           */
/* ALT_SCALE_FACTOR_SHIFT Scaling for included images is calculated by       */
/*                      trunc(SF * available_space / image_size)             */
/*                      The default value of SF is 256 (SHIFT of 8).         */
/*                      When printing a document with proofs of pages that   */
/*                      contain several pages per sheet, images might be     */
/*                      reduced by a factor of 10.  If such an image needs a */
/*                      a scale factor of 25.9, lout rounds it to 25.        */
/*                      If the image was originally about 11" (792pt),       */
/*                      it will be printed as 792*25/256 = 77.3pt instead of */
/*                      792*25.9/256 = 80.1pt.  This difference can create a */
/*                      visible misalignment of images in a @Graph.          */
/*                      Increasing SF improves the scaling accuracy at the   */
/*                      expense of reducing MAX_FULL_LENGTH, the maximum     */
/*                      page size.                                           */
/*			ALT_SCALE_FACTOR   8  MAX_FULL_LENGTH  148.0m        */
/*			ALT_SCALE_FACTOR   9  MAX_FULL_LENGTH   74.0m        */
/*			ALT_SCALE_FACTOR  10  MAX_FULL_LENGTH   37.0m        */
/*			ALT_SCALE_FACTOR  11  MAX_FULL_LENGTH   18.5m        */
/*			ALT_SCALE_FACTOR  12  MAX_FULL_LENGTH    9.2m        */
/*			ALT_SCALE_FACTOR  13  MAX_FULL_LENGTH    4.6m        */
/*			ALT_SCALE_FACTOR  14  MAX_FULL_LENGTH    2.3m        */
/*			ALT_SCALE_FACTOR  15  MAX_FULL_LENGTH    1.2m        */
/*                                                                           */
/*****************************************************************************/

#define ALT_SCALE_FACTOR_SHIFT	12

#ifdef ALT_SCALE_FACTOR_SHIFT
#define	MAX_FULL_LENGTH	((1 << (31 - ALT_SCALE_FACTOR_SHIFT)) - 1)
#else
#define	MAX_FULL_LENGTH	8388607	/* 2**23 - 1, about 148 metres */
#endif
#define	MAX_FILES	65535
#define MAX_LINE        2048
#define MAX_WORD        2048
#define	MAX_OBJECT_REC	((int) ceiling(sizeof(struct word_type)+MAX_WORD,sizeof(ALIGN)))
#define MAX_BUFF        512
#define MAX_FONT	65535
#define MAX_COLOUR	65535
#define MAX_TEXTURE	65535
#define	MAX_LANGUAGE	64
#define	MAX_LEX_STACK	20
#define	MAX_CHARS	256
#define MAX_HCOPIES	3
#define MAX_FORMAT	100

/*****************************************************************************/
/*                                                                           */
/*  Miscellaneous Macros                                                     */
/*                                                                           */
/*****************************************************************************/

/*
#define	CHILD		0
#define	PARENT		1
#define	COLM		0
#define	ROWM		1
*/

INLINE BOOLEAN2 sameDim(DIM_TE x, DIM_TE y) {
  return x.dim == y.dim;
}
INLINE BOOLEAN2 sameDir(DIR_TE x, DIR_TE y) {
  return x.dir = y.dir;
}
INLINE DIM_TE otherDim(DIM_TE x) {
  return x.dim == ROWM_E ? COLM : ROWM;
}
INLINE DIM_TE dimFromU(unsigned v) {
  // dummy value
  DIM_TE res = COLM;
  switch(v) {
    case COLM_E:
      res = COLM;
      break;
    case ROWM_E:
      res = ROWM;
      break;
    default:
      // TODO
      Error(2, 205, "dim %u unknown", UNEXPECTED_DEFAULT, no_fpos, v);
  }
  return res;
}
INLINE DIR_TE otherDir(DIR_TE x) {
  return x.dir == PARENT_E ? CHILD : PARENT;
}
INLINE DIR_TE dirFromU(unsigned v) {
  // dummy value
  DIR_TE res = CHILD;
  switch(v) {
    case PARENT_E:
      res = PARENT;
      break;
    case CHILD_E:
      res = CHILD;
      break;
    default:
      // TODO
      Error(2, 205, "dim %u unknown", UNEXPECTED_DEFAULT, no_fpos, v);
  }
  return res;
}
#define	dimen(x)	( sameDim(x, COLM) ? AsciiToFull("COLM") : AsciiToFull("ROWM") )

#define	nilobj		( (OBJECT) NULL )
#define	null		( (FILE *) NULL )

#define find_max(a, b)	((a) < (b) ? (b) : (a))
#define find_min(a, b)	((a) < (b) ? (a) : (b))
#define	ceiling(a, b)	( ((a) - 1)/(b) + 1 )	/* ceiling(a/b)              */
#define is_odd(x)	( (x) & 1 )		/* TRUE if x is odd number   */

/*@::Some straightforward typedefs@*******************************************/
/*                                                                           */
/*  typedef ALIGN - used for forcing record alignment.                       */
/*                                                                           */
/*****************************************************************************/

typedef char *ALIGN;


/*****************************************************************************/
/*                                                                           */
/*  typedef FULL_LENGTH - an integer physical distance.                      */
/*                                                                           */
/*****************************************************************************/

typedef int FULL_LENGTH;


/*****************************************************************************/
/*                                                                           */
/*  FONT_NUM - internal name for a font.                                     */
/*                                                                           */
/*****************************************************************************/

typedef unsigned short FONT_NUM;


/*****************************************************************************/
/*                                                                           */
/*  COLOUR_NUM - internal name for a colour.                                 */
/*                                                                           */
/*****************************************************************************/

typedef unsigned short COLOUR_NUM;


/*****************************************************************************/
/*                                                                           */
/*  TEXTURE_NUM - internal name for a texture.                               */
/*                                                                           */
/*****************************************************************************/

typedef unsigned short TEXTURE_NUM;


/*****************************************************************************/
/*                                                                           */
/*  LANGUAGE_NUM - internal name for a language.                             */
/*                                                                           */
/*****************************************************************************/

typedef unsigned int LANGUAGE_NUM;


/*****************************************************************************/
/*                                                                           */
/*  MAPPING - internal name for a character mapping vector.                  */
/*                                                                           */
/*****************************************************************************/

typedef unsigned int MAPPING;


/*****************************************************************************/
/*                                                                           */
/*  LINE - a line from a database index file.                                */
/*                                                                           */
/*****************************************************************************/

typedef char *LINE;


/*****************************************************************************/
/*                                                                           */
/*  typedef FULL_CHAR - one of the characters manipulated by Lout.           */
/*                                                                           */
/*  This program does not deal with 7-bit ASCII characters.  Instead, its    */
/*  characters are defined by the FULL_CHAR typedef, and could be anything   */
/*  from 7-bit ASCII to 8-bit ISO-LATIN-1 to 16-bit UNICODE and beyond.      */
/*                                                                           */
/*  Unfortunately C favours signed 8-bit characters: literal strings are     */
/*  pointers to them, argv[] and the standard libraries assume them.  We get */
/*  around these problems by using our own library, including AsciiToFull()  */
/*  to convert an ASCII string (such as a C string) into a FULL_CHAR string. */
/*                                                                           */
/*  Formally this library appears in module z39.c; however since this        */
/*  implementation uses 8-bit unsigned characters, most of the routines      */
/*  can be implemented by macros containing type-cast calls to C standard    */
/*  library routines.  These appear in the z39.c externs list below.         */
/*                                                                           */
/*****************************************************************************/

/* typedef unsigned char FULL_CHAR; */

/*@::Character literals@******************************************************/
/*                                                                           */
/*  Character Literals                                                       */
/*                                                                           */
/*  The following macros ensure that no Lout source is ever compared to a    */
/*  literal character other than '\0':                                       */
/*                                                                           */
/*****************************************************************************/

#define	CH_FLAG_ALTERR		'a'	/* the -a command line flag          */
#define	CH_FLAG_CROSS		'c'	/* the -c command line flag          */
#define	CH_FLAG_ENCPATH		'C'	/* the -C command line flag          */
#define	CH_FLAG_DEBUG		'd'	/* the -d command line flag          */
#define	CH_FLAG_DIRPATH		'D'	/* the -D command line flag          */
#define	CH_FLAG_ERRFILE		'e'	/* the -e command line flag          */
#define	CH_FLAG_EPSFIRST	'E'	/* first letter of the -EPS flag     */
#define	CH_FLAG_FNTPATH		'F'	/* the -F command line flag          */
#define	CH_FLAG_HYPHEN		'h'	/* the -h command line flag          */
#define	CH_FLAG_HYPPATH		'H'	/* the -H command line flag          */
#define	CH_FLAG_INCLUDE		'i'	/* the -i command line flag          */
#define	CH_FLAG_INCPATH		'I'	/* the -I command line flag          */
#define	CH_FLAG_NOKERN		'k'	/* the -k command line flag          */
#define CH_FLAG_NOCOLLATE       'l'     /* the -l command line flag          */
#define CH_FLAG_COLLATE         'L'     /* the -L command line flag          */
#define CH_FLAG_MEMCHECK        'm'     /* the -m command line flag          */
#define	CH_FLAG_MEMCR		'M'	/* the -M command line flag	     */
#define	CH_FLAG_OUTFILE		'o'	/* the -o command line flag          */
#define	CH_FLAG_PLAIN		'p'	/* the -p command line flag          */
#define	CH_FLAG_FFPLAIN		'P'	/* the -P command line flag          */
#define	CH_FLAG_RUNS		'r'	/* the -r command line flag          */
#define	CH_FLAG_SUPPRESS	's'	/* the -s command line flag          */
#define	CH_FLAG_SAFE		'S'	/* the -S command line flag          */
#define	CH_FLAG_NOTEXTURE	't'	/* the -t command line flag          */
#define	CH_FLAG_USAGE		'u'	/* the -u command line flag          */
#define	CH_FLAG_UNSAFE		'U'	/* the -U command line flag          */
#define	CH_FLAG_VERSION		'V'	/* the -V command line flag          */
#define	CH_FLAG_INITALL		'x'	/* the -x command line flag          */
#define	CH_FLAG_OPTION		'-'	/* the -- command line flag          */
#define	CH_FLAG_WORDS		'w'	/* the -w command line flag          */
#define	CH_FLAG_PDF		'Z'	/* the -Z command line flag	     */

#define	CH_SPACE		' '	/* space character                   */
/* #define	CH_NEWLINE		'\n'*/ 	/* the newline character     */
#define	CH_LF			'\n'	/* the line feed character           */
#define	CH_CR			'\r'	/* the carriage return character     */
#define	CH_SYMSTART		'@'	/* extra letter symbols may have     */
#define	CH_UNDERSCORE		'_'	/* extra letter symbols may have     */
#define	CH_QUOTE		'"'	/* the quote character		     */
#define	CH_ZERO			'0'	/* the first digit character, zero   */
#define	CH_EIGHT		'8'	/* the last even digit character     */
#define	CH_NINE			'9'	/* the last odd digit character      */
#define	CH_INCGAP		'+'	/* begins an incrementing gap	     */
#define	CH_DECGAP		'-'	/* begins a decrementing gap	     */
#define	CH_MINUS		'-'	/* minus sign                        */
#define	CH_HYPHEN		'-'	/* the hyphen character		     */
#define	CH_SLASH		'/'	/* the slash character		     */
#define	CH_NOBREAK		'u'	/* `unbreakable' character for gaps  */

#define	CH_UNIT_CM		'c'	/* unit of measurement: centimetres  */
#define	CH_UNIT_IN		'i'	/* unit of measurement: inches       */
#define	CH_UNIT_PT		'p'	/* unit of measurement: points       */
#define	CH_UNIT_EM		'm'	/* unit of measurement: ems          */
#define	CH_UNIT_FT		'f'	/* unit of measurement: fontsizes    */
#define	CH_UNIT_SP		's'	/* unit of measurement: spacewidths  */
#define	CH_UNIT_VS		'v'	/* unit of measurement: vspaces      */
#define	CH_UNIT_WD		'w'	/* unit of measurement: follwidths   */
#define	CH_UNIT_BD		'b'	/* unit of measurement: boundwidths  */
#define	CH_UNIT_RL		'r'	/* unit of measurement: relwidths    */
#define	CH_UNIT_DG		'd'	/* unit of measurement: degrees      */
#define	CH_UNIT_YU		'y'	/* unit of measurement: y unit       */
#define	CH_UNIT_ZU		'z'	/* unit of measurement: z unit       */

#define	CH_MODE_EDGE		'e'	/* spacing mode: edge-to-edge        */
#define	CH_MODE_HYPH		'h'	/* spacing mode: hyphenation         */
#define	CH_MODE_MARK		'x'	/* spacing mode: mark-to-mark        */
#define	CH_MODE_OVER		'o'	/* spacing mode: overstrike          */
#define	CH_MODE_KERN		'k'	/* spacing mode: kerning             */
#define	CH_MODE_TABL		't'	/* spacing mode: tabulation          */

#define octaldigit(ch)		( (ch) >= '0' && (ch) <= '7' )
#define decimaldigit(ch)	( (ch) >= '0' && (ch) <= '9' )
#define	digitchartonum(ch)	( (ch) - '0' )
#define	numtodigitchar(ch)	( (ch) + '0' )
#define	beginsbreakstyle(ch)	( (ch) >= 'a' && (ch) <= 'z' )
#define	numericchar(ch)		( decimaldigit(ch) || (ch) == '.' )


/*@::String literals, FULL_CHAR type@*****************************************/
/*                                                                           */
/*  String Literals.                                                         */
/*                                                                           */
/*  All significant string literals are defined here.  The program has many  */
/*  others, however: format strings, debug output, etc.                      */
/*                                                                           */
/*****************************************************************************/

extern const FULL_CHAR* const STR_EMPTY;
extern const FULL_CHAR* const STR_QUOTE;
extern const FULL_CHAR* const STR_ESCAPE;
extern const FULL_CHAR* const STR_COMMENT;
extern const FULL_CHAR* const STR_SPACE;
extern const FULL_CHAR* const STR_FORMFEED;
extern const FULL_CHAR* const STR_TAB;
extern const FULL_CHAR* const STR_LETTERS_LOWER;
extern const FULL_CHAR* const STR_LETTERS_UPPER;
extern const FULL_CHAR* const STR_LETTERS_SYMSTART;
extern const FULL_CHAR* const STR_LETTERS_UNDERSCORE;

extern const FULL_CHAR* const STR_LETTERS_EXTRA0;
extern const FULL_CHAR* const STR_LETTERS_EXTRA1;
extern const FULL_CHAR* const STR_LETTERS_EXTRA2;
extern const FULL_CHAR* const STR_LETTERS_EXTRA3;
extern const FULL_CHAR* const STR_LETTERS_EXTRA4;
extern const FULL_CHAR* const STR_LETTERS_EXTRA5;
extern const FULL_CHAR* const STR_LETTERS_EXTRA6;
extern const FULL_CHAR* const STR_LETTERS_EXTRA7;

extern const FULL_CHAR* const STR_STDIN;
extern const FULL_CHAR* const STR_STDOUT;
extern const FULL_CHAR* const STR_HYPHEN;
extern const FULL_CHAR* const STR_EPS;

extern const FULL_CHAR* const STR_POSTSCRIPT;
// needed in z49.c
#define STR_POSTSCRIPT_MACRO AsciiToFull("PostScript")

extern const FULL_CHAR* const STR_PLAINTEXT;
// needed in z51.c
#define STR_PLAINTEXT_MACRO AsciiToFull("PlainText")

extern const FULL_CHAR* const STR_PDF;
// needed in z50.c
#define STR_PDF_MACRO AsciiToFull("PDF")

extern const FULL_CHAR* const STR_ELSE;
extern const FULL_CHAR* const STR_NOCROSS;
extern const FULL_CHAR* const STR_BADKEY;
extern const FULL_CHAR* const STR_NONE;
extern const FULL_CHAR* const STR_NOCHAR;
extern const FULL_CHAR* const STR_ZERO;
extern const FULL_CHAR* const STR_PS_SPACENAME;
extern const FULL_CHAR* const STR_FONT_RECODE;
extern const FULL_CHAR* const STR_FONT_NORECODE;
extern const FULL_CHAR* const STR_COLOUR_NOCHANGE;
extern const FULL_CHAR* const STR_TEXTURE_NOCHANGE;

extern const FULL_CHAR* const STR_BREAK_HYPHEN;
extern const FULL_CHAR* const STR_BREAK_NOHYPHEN;
extern const FULL_CHAR* const STR_BREAK_ADJUST;
extern const FULL_CHAR* const STR_BREAK_OUTDENT;
extern const FULL_CHAR* const STR_BREAK_RAGGED;
extern const FULL_CHAR* const STR_BREAK_CRAGGED;
extern const FULL_CHAR* const STR_BREAK_RRAGGED;
extern const FULL_CHAR* const STR_BREAK_ORAGGED;
extern const FULL_CHAR* const STR_BREAK_LINES;
extern const FULL_CHAR* const STR_BREAK_CLINES;
extern const FULL_CHAR* const STR_BREAK_RLINES;
extern const FULL_CHAR* const STR_BREAK_OLINES;
extern const FULL_CHAR* const STR_BREAK_SCALE;
extern const FULL_CHAR* const STR_BREAK_NOFIRST;
extern const FULL_CHAR* const STR_BREAK_FIRST;
extern const FULL_CHAR* const STR_BREAK_NOLAST;
extern const FULL_CHAR* const STR_BREAK_LAST;
extern const FULL_CHAR* const STR_BREAK_SETOUTDENT;
extern const FULL_CHAR* const STR_BREAK_MARGINKERNING;
extern const FULL_CHAR* const STR_BREAK_NOMARGINKERNING;

extern const FULL_CHAR* const STR_SPACE_LOUT;
extern const FULL_CHAR* const STR_SPACE_COMPRESS;
extern const FULL_CHAR* const STR_SPACE_SEPARATE;
extern const FULL_CHAR* const STR_SPACE_TROFF;
extern const FULL_CHAR* const STR_SPACE_TEX;

extern const FULL_CHAR* const STR_SMALL_CAPS_ON;
extern const FULL_CHAR* const STR_SMALL_CAPS_OFF;
extern const FULL_CHAR* const STR_SMALL_CAPS_SET;
extern const FULL_CHAR* const STR_BASELINE_MARK;
extern const FULL_CHAR* const STR_LIG;
extern const FULL_CHAR* const STR_NOLIG;
extern const FULL_CHAR* const STR_XHEIGHT2_MARK;
extern const FULL_CHAR* const STR_NOSTRUT;
extern const FULL_CHAR* const STR_STRUT;

extern const FULL_CHAR* const STR_GAP_RJUSTIFY;
extern const FULL_CHAR* const STR_GAP_ZERO_HYPH;

extern const FULL_CHAR* const STR_SCALE_DOWN;

// typesafe enum inline functions

INLINE BOOLEAN2 sameFiletype(FILE_TYPE x, FILE_TYPE y) {
  return x.filetype == y.filetype;
}

INLINE BOOLEAN2 sameTidy(TIDY_TE x, TIDY_TE y) {
  return x.tidy == y.tidy;
}

INLINE BOOLEAN2 sameUnit(UNIT x, UNIT y) {
  return x.unit == y.unit;
}



/*@::GAP, STYLE@**************************************************************/
/*                                                                           */
/*  typedef GAP - what separates one object from another.                    */
/*                                                                           */
/*****************************************************************************/

typedef struct
{ FULL_LENGTH	owidth;			/* width of the gap                  */
  BOOLEAN2	onobreak : 1;		/* TRUE if this gap is unbreakable   */
  BOOLEAN2	omark	 : 1;		/* TRUE if this gap is marked        */
  BOOLEAN2	ojoin	 : 1;		/* TRUE if joins exist across gap    */
  unsigned	ounits	 : 3;		/* units of measurement: fixed, etc  */
  unsigned	omode	 : 3;		/* spacing mode: edge-to-edge, etc   */
} GAP;

INLINE BOOLEAN2 nobreak(GAP* x) {
  return x->onobreak;
}
INLINE BOOLEAN2 mark(GAP* x) {
  return x->omark;
}
INLINE BOOLEAN2 join(GAP* x) {
  return x->ojoin;
}
INLINE UNIT units(GAP* x) {
  // return x->ounits;
  unsigned units = x->ounits;
  UNIT res = FIXED_UNIT;
  switch(units) {
    case NO_UNIT_E:
      res = NO_UNIT;
      break;
    case FIXED_UNIT_E:
      res = FIXED_UNIT;
      break;
    case FRAME_UNIT_E:
      res = FRAME_UNIT;
      break;
    case AVAIL_UNIT_E:
      res = AVAIL_UNIT;
      break;
    case DEG_UNIT_E:
      res = DEG_UNIT;
      break;
    case NEXT_UNIT_E:
      res = NEXT_UNIT;
      break;
    default:
      // TODO
      // Error(2, 201, "units %u unknown in GAP* %p", UNEXPECTED_DEFAULT, no_fpos, units, x);
      debug2(DCE, DD, "units %u unknown in GAP* %p", units, x);
  }
  return res;
}
INLINE BOOLEAN2 gapHasUnit(GAP* x, UNIT u) {
  return x->ounits == u.unit;
}
INLINE SPACE_MODE mode(GAP* x) {
  // return x->omode;
  unsigned mode = x->omode;
  SPACE_MODE res = NO_MODE;
  switch(mode) {
    case NO_MODE_E:
      res = NO_MODE;
      break;
    case EDGE_MODE_E:
      res = EDGE_MODE;
      break;
    case HYPH_MODE_E:
      res = HYPH_MODE;
      break;
    case MARK_MODE_E:
      res = MARK_MODE;
    case OVER_MODE_E:
      res = OVER_MODE;
      break;
    case KERN_MODE_E:
      res = KERN_MODE;
      break;
    case TAB_MODE_E:
      res = TAB_MODE;
      break;
    case ADD_HYPH_E:
      res = ADD_HYPH;
      break;
    default:
      // TODO
      Error(2, 202, "space mode %u unknown in GAP* %p", UNEXPECTED_DEFAULT, no_fpos, mode, x);
  }
  return res;
}
INLINE FULL_LENGTH width(GAP* x) {
  return x->owidth;
}


INLINE void setNobreak(GAP* x, BOOLEAN2 xnobreak) {
  x->onobreak = xnobreak;
}
INLINE void setMark(GAP* x, BOOLEAN2 xmark) {
  x->omark = xmark;
}
INLINE void setJoin(GAP* x, BOOLEAN2 xjoin) {
  x->ojoin = xjoin;
}
INLINE void setUnits(GAP* x, UNIT xunits) {
  x->ounits = xunits.unit;
}
INLINE void setMode(GAP* x, SPACE_MODE xmode) {
  x->omode = xmode.spacemode;
}
INLINE void setWidth(GAP* x, FULL_LENGTH xwidth) {
  x->owidth = xwidth;
}

// #define SetGap(x, xnobreak, xmark, xjoin, xunits, xmode, xwidth)	\
// ( SetGapOnRef( &(x), xnobreak, xmark, xjoin, xunits, xmode, xwidth) )
INLINE void SetGapOnRef(GAP* x, BOOLEAN2 xnobreak, BOOLEAN2 xmark, BOOLEAN2 xjoin, UNIT xunits, SPACE_MODE xmode, FULL_LENGTH xwidth) {
  setNobreak(x, xnobreak);
  setMark(x, xmark);
  setJoin(x, xjoin);
  setUnits(x, xunits);
  setMode(x, xmode);
  setWidth(x, xwidth);
}

#define ClearGap(x)     SetGap(x, FALSE, FALSE, TRUE, FIXED_UNIT, NO_MODE, 0)

// #define GapCopy(x, y)							\
// ( GapCopyOnRef( &(x), &(y) ) )
INLINE void GapCopyOnRef(GAP* x, GAP* y) {
  setNobreak(x, nobreak(y));
  setMark(x, mark(y));
  setJoin(x, join(y));
  setUnits(x, units(y));
  setMode(x, mode(y));
  setWidth(x, width(y));
}

INLINE BOOLEAN2 GapEqual(GAP* x, GAP* y) {
    return nobreak(x) == nobreak(y) && mark(x) == mark(y) && join(x) == join(y)
             && sameUnit(units(x), units(y)) 
             && mode(x).spacemode == mode(y).spacemode && width(x) == width(y);
}

/*****************************************************************************/
/*                                                                           */
/*  typedef STYLE - information about how to break text, etc.                */
/*                                                                           */
/*****************************************************************************/

/* A key-value pair.  */
typedef struct context_type
{
  union rec	    *okey;		/* name of a context variable        */
  union rec	    *ovalue;		/* associated value		     */
  union rec         *oenv;		/* environment for this value        */
  struct style_type *ostyle;		/* style for this value              */
} CONTEXT;

#define	context_key(x)		(x).okey
#define	context_value(x)	(x).ovalue
#define	context_env(x)		(x).oenv
#define	context_style(x)	(x).ostyle

typedef struct style_type
{
  GAP		oline_gap;		/* separation between lines          */
  GAP		ospace_gap;		/* separation induced by white space */
  FULL_LENGTH	oyunit;			/* value of y unit of measurement    */
  FULL_LENGTH	ozunit;			/* value of z unit of measurement    */
  FULL_LENGTH	ooutdent_len;		/* amount to outdent in outdent style*/
  FULL_LENGTH	osmallcaps_len;		/* size of small capitals            */
  FONT_NUM	ofont;			/* current font                      */
  COLOUR_NUM	ocolour;		/* current colour		     */
  COLOUR_NUM	ounderline_colour;	/* current underline colour	     */
  TEXTURE_NUM	otexture;		/* current texture		     */
  unsigned short oblanklinescale;	/* scale factor for blank lines      */
  LANGUAGE_NUM	olanguage       : 6;	/* current language		     */
  BOOLEAN2	ovadjust	: 1;	/* @VAdjust in effect                */
  BOOLEAN2	ohadjust	: 1;	/* @HAdjust in effect                */
  BOOLEAN2	opadjust	: 1;	/* @PAdjust in effect                */
  unsigned	osmall_caps	: 1;	/* small capitals                    */
  unsigned	ospace_style	: 3;	/* space style: lout, troff, tex, .. */
  unsigned	ohyph_style	: 2;	/* hyphenation off or on             */
  unsigned	ofill_style	: 2;	/* fill lines with text off/on       */
  unsigned	odisplay_style	: 3;	/* display lines adjusted, ragged... */
  // TODO: making this BOOLEAN2 will break crossrefs
  BOOLEAN	ooutline	: 2;	/* TRUE if outlining words           */
  BOOLEAN2	onobreakfirst	: 1;	/* no break after first line of para */
  BOOLEAN2	onobreaklast	: 1;	/* no break after last line of para  */
  BOOLEAN2	obaselinemark	: 1;	/* baseline char metrics             */
  BOOLEAN2	ostrut		: 1;	/* strut char metrics                */
  BOOLEAN2	oligatures	: 1;	/* use ligatures                     */
  BOOLEAN2	omarginkerning	: 1;	/* perform margin kerning            */
  CONTEXT	ocontext;		/* context stack		     */
} STYLE;

// #define	line_gap_ms(x)	(x).oline_gap
// #define	space_gap_ms(x)	(x).ospace_gap

// #define	line_gap_ref(x)	(x)->oline_gap
INLINE GAP* line_gap_ref(STYLE* x) {
  return &((x)->oline_gap);
} 
// #define	space_gap_ref(x)	(x)->ospace_gap
INLINE GAP* space_gap_ref(STYLE* x) {
  return &((x)->ospace_gap);
}
// #define	underline_colour_ref(x) (x)->ounderline_colour
INLINE COLOUR_NUM* underline_colour_ref(STYLE* x) {
  return &((x)->ounderline_colour);
}
// #define	colour_ref(x)	(x)->ocolour
INLINE COLOUR_NUM* colour_ref(STYLE* x) {
  return &((x)->ocolour);
}
// #define	context_ref(x)	(x)->ocontext
INLINE CONTEXT* context_ref(STYLE* x) {
  return &((x)->ocontext);
}

INLINE GAP line_gap(STYLE* x) {
  return (x)->oline_gap;
} 
INLINE GAP space_gap(STYLE* x) {
  return (x)->ospace_gap;
}
INLINE FULL_LENGTH yunit(STYLE* x) {
  return (x)->oyunit;
}
INLINE FULL_LENGTH zunit(STYLE* x) {
  return (x)->ozunit;
}
INLINE FULL_LENGTH outdent_len(STYLE* x) {
  return (x)->ooutdent_len;
}
INLINE FULL_LENGTH smallcaps_len(STYLE* x) {
  return (x)->osmallcaps_len;
}
INLINE FONT_NUM font(STYLE* x) {
  return (x)->ofont;
}
INLINE COLOUR_NUM colour(STYLE* x) {
  return (x)->ocolour;
}
INLINE COLOUR_NUM underline_colour(STYLE* x) {
  return (x)->ounderline_colour;
}
INLINE TEXTURE_NUM texture(STYLE* x) {
  return (x)->otexture;
}
INLINE unsigned short blanklinescale(STYLE* x) {
  return (x)->oblanklinescale;
}
INLINE LANGUAGE_NUM language(STYLE* x) {
  return (x)->olanguage;
}
INLINE BOOLEAN2 vadjust(STYLE* x) {
  return (x)->ovadjust;
}
INLINE BOOLEAN2 hadjust(STYLE* x) {
  return (x)->ohadjust;
}
INLINE BOOLEAN2 padjust(STYLE* x) {
  return (x)->opadjust;
}
INLINE unsigned small_caps(STYLE* x) {
  return (x)->osmall_caps;
}
INLINE SPACE_STYLE space_style(STYLE* x) {
  // return (x)->ospace_style;
  unsigned spacestyle = (x)->ospace_style;
  SPACE_STYLE res = SPACE_LOUT;
  switch(spacestyle) {
    case SPACE_LOUT_E:
      res = SPACE_LOUT;
      break;
    case SPACE_COMPRESS_E:
      res = SPACE_COMPRESS;
      break;
    case SPACE_SEPARATE_E:
      res = SPACE_SEPARATE;
      break;
    case SPACE_TROFF_E:
      res = SPACE_TROFF;
      break;
    case SPACE_TEX_E:
      res = SPACE_TEX;
      break;
    default:
      // TODO
      Error(2, 203, "spacestyle %u unknown in STYLE* %p", UNEXPECTED_DEFAULT, no_fpos, spacestyle, x);
  }
  return res;
}
INLINE BOOLEAN2 styleHasSpaceStyle(STYLE* x, SPACE_STYLE y) {
  return x->ospace_style == y.spacestyle;
}
INLINE HYPH_STYLE hyph_style(STYLE* x) {
  // return (x)->ohyph_style;
  unsigned hyphstyle = (x)->ohyph_style;
  HYPH_STYLE res = HYPH_UNDEF;
  switch(hyphstyle) {
    case HYPH_UNDEF_E:
      res = HYPH_UNDEF;
      break;
    case HYPH_OFF_E:
      res = HYPH_OFF;
      break;
    case HYPH_ON_E:
      res = HYPH_ON;
      break;
    default:
      // TODO
      Error(2, 204, "hyphstyle %u unknown in STYLE* %p", UNEXPECTED_DEFAULT, no_fpos, hyphstyle, x);
  }
  return res;
}
INLINE BOOLEAN2 styleHasHyphStyle(STYLE* x, HYPH_STYLE y) {
  return x->ohyph_style == y.hyphstyle;
}
INLINE unsigned fill_style(STYLE* x) {
  return (x)->ofill_style;
}
INLINE unsigned display_style(STYLE* x) {
  return (x)->odisplay_style;
}
INLINE BOOLEAN outline(STYLE* x) {
  return (x)->ooutline;
}
INLINE BOOLEAN2 nobreakfirst(STYLE* x) {
  return (x)->onobreakfirst;
}
INLINE BOOLEAN2 nobreaklast(STYLE* x) {
  return (x)->onobreaklast;
}
INLINE BOOLEAN2 baselinemark(STYLE* x) {
  return (x)->obaselinemark;
}
INLINE BOOLEAN2 strut(STYLE* x) {
  return (x)->ostrut;
}
INLINE BOOLEAN2 ligatures(STYLE* x) {
  return (x)->oligatures;
}
INLINE BOOLEAN2 marginkerning(STYLE* x) {
  return (x)->omarginkerning;
}
INLINE CONTEXT context(STYLE* x) {
  return (x)->ocontext;
}

INLINE void setLine_gap(STYLE* x, GAP* line_gap) {
  (x)->oline_gap = *line_gap;
} 
INLINE void setSpace_gap(STYLE* x, GAP* space_gap) {
  (x)->ospace_gap = *space_gap;
}
INLINE void setYunit(STYLE* x, FULL_LENGTH yunit) {
  (x)->oyunit = yunit;
}
INLINE void setZunit(STYLE* x, FULL_LENGTH zunit) {
  (x)->ozunit = zunit;
}
INLINE void setOutdent_len(STYLE* x, FULL_LENGTH outdent_len) {
  (x)->ooutdent_len = outdent_len;
}
INLINE void setSmallcaps_len(STYLE* x, FULL_LENGTH smallcaps_len) {
  (x)->osmallcaps_len = smallcaps_len;
}
INLINE void setFont(STYLE* x, FONT_NUM font) {
  (x)->ofont = font;
}
INLINE void setColour(STYLE* x, COLOUR_NUM colour) {
  (x)->ocolour = colour;
}
INLINE void setUnderline_colour(STYLE* x, COLOUR_NUM underline_colour) {
  (x)->ounderline_colour = underline_colour;
}
INLINE void setTexture(STYLE* x, TEXTURE_NUM texture) {
  (x)->otexture = texture;
}
INLINE void setBlanklinescale(STYLE* x, unsigned short blanklinescale) {
  (x)->oblanklinescale = blanklinescale;
}
INLINE void setLanguage(STYLE* x, LANGUAGE_NUM language) {
  (x)->olanguage = language;
}
INLINE void setVadjust(STYLE* x, BOOLEAN2 vadjust) {
  (x)->ovadjust = vadjust;
}
INLINE void setHadjust(STYLE* x, BOOLEAN2 hadjust) {
  (x)->ohadjust = hadjust;
}
INLINE void setPadjust(STYLE* x, BOOLEAN2 padjust) {
  (x)->opadjust = padjust;
}
INLINE void setSmall_caps(STYLE* x, unsigned small_caps) {
  (x)->osmall_caps = small_caps;
}
INLINE void setSpace_style(STYLE* x, SPACE_STYLE space_style) {
  (x)->ospace_style = space_style.spacestyle;
}
INLINE void setHyph_style(STYLE* x, HYPH_STYLE hyph_style) {
  (x)->ohyph_style = hyph_style.hyphstyle;
}
INLINE void setFill_style(STYLE* x, unsigned fill_style) {
  (x)->ofill_style = fill_style;
}
INLINE void setDisplay_style(STYLE* x, unsigned display_style) {
  (x)->odisplay_style = display_style;
}
INLINE void setOutline(STYLE* x, BOOLEAN outline) {
  (x)->ooutline = outline;
}
INLINE void setNobreakfirst(STYLE* x, BOOLEAN2 nobreakfirst) {
  (x)->onobreakfirst = nobreakfirst;
}
INLINE void setNobreaklast(STYLE* x, BOOLEAN2 nobreaklast) {
  (x)->onobreaklast = nobreaklast;
}
INLINE void setBaselinemark(STYLE* x, BOOLEAN2 baselinemark) {
  (x)->obaselinemark = baselinemark;
}
INLINE void setStrut(STYLE* x, BOOLEAN2 strut) {
  (x)->ostrut = strut;
}
INLINE void setLigatures(STYLE* x, BOOLEAN2 ligatures) {
  (x)->oligatures = ligatures;
}
INLINE void setMarginkerning(STYLE* x, BOOLEAN2 marginkerning) {
  (x)->omarginkerning = marginkerning;
}
INLINE void setContext(STYLE* x, CONTEXT* context) {
  (x)->ocontext = *context;
}

INLINE void StyleCopy(STYLE* x, STYLE* y) {
  GapCopyOnRef(line_gap_ref(x), line_gap_ref(y));
  GapCopyOnRef(space_gap_ref(x), space_gap_ref(y));
  setYunit(x, yunit(y));
  setZunit(x, zunit(y));
  setOutdent_len(x, outdent_len(y));
  setSmallcaps_len(x, smallcaps_len(y));
  setFont(x, font(y));
  setColour(x, colour(y));
  setUnderline_colour(x, underline_colour(y));
  setTexture(x, texture(y));
  setBlanklinescale(x, blanklinescale(y));
  setLanguage(x, language(y));
  setVadjust(x, vadjust(y));
  setHadjust(x, hadjust(y));
  setPadjust(x, padjust(y));
  setSmall_caps(x, small_caps(y));
  setSpace_style(x, space_style(y));
  setHyph_style(x, hyph_style(y));
  setFill_style(x, fill_style(y));
  setDisplay_style(x, display_style(y));
  setOutline(x, outline(y));
  setNobreakfirst(x, nobreakfirst(y));
  setNobreaklast(x, nobreaklast(y));
  setBaselinemark(x, baselinemark(y));
  setStrut(x, strut(y));
  setLigatures(x, ligatures(y));
  setMarginkerning(x, marginkerning(y));
  setContext(x, context_ref(y));
}

/*@::CONSTRAINT, FILE_NUM, FILE_POS, LIST@************************************/
/*                                                                           */
/*  typedef CONSTRAINT - a size constraint.                                  */
/*                                                                           */
/*****************************************************************************/

typedef struct
{ FULL_LENGTH  obc;
  FULL_LENGTH  obfc;
  FULL_LENGTH  ofc;
  FULL_LENGTH  osparec;
} CONSTRAINT;

#define	bc(x)		(x).obc
#define	bfc(x)		(x).obfc
#define	fc(x)		(x).ofc
#define	sparec(x)	(x).osparec

INLINE BOOLEAN2 constrained(CONSTRAINT x) {
    return bc(x) != MAX_FULL_LENGTH || bfc(x) != MAX_FULL_LENGTH || fc(x) != MAX_FULL_LENGTH;
}

// #define	SetConstraint(c,x,y,z)	( SetConstraintOnRef(&(c), x, y, z) )
INLINE void SetConstraintOnRef(CONSTRAINT* c, FULL_LENGTH x, FULL_LENGTH y, FULL_LENGTH z) {
    bc(*c) = (x);
    bfc(*c) = (y);
    fc(*c) = (z);
}

// #define	CopyConstraint(x, y)	( CopyConstraintOnRef( &(x), &(y)) )
INLINE void CopyConstraintOnRef(CONSTRAINT* x, CONSTRAINT* y) {
    bc(*x) = bc(*y);
    bfc(*x) = bfc(*y);
    fc(*x) = fc(*y);
}

// #define	FlipConstraint(x, y)	( FlipConstraintOnRef( &(x), &(y)) )
INLINE void FlipConstraintOnRef(CONSTRAINT* x, CONSTRAINT* y) {
    bc(*x) = fc(*y);
    bfc(*x) = bfc(*y);
    fc(*x) = bc(*y);
}

// #define FitsConstraint(b, f, c)	( FitsConstraintOnRef(b, f, &(c)) )
INLINE BOOLEAN2 FitsConstraintOnRef(FULL_LENGTH b, FULL_LENGTH f, CONSTRAINT* c) {
    return b <= bc(*c)  && b + f <= bfc(*c) && f <= fc(*c);
}

INLINE BOOLEAN2 EqualConstraint(CONSTRAINT a, CONSTRAINT b) {
    return bc(a)==bc(b) && bfc(a)==bfc(b) && fc(a)==fc(b);
}

#define	ig_fnum(x)	bc(constraint(x))
#define	ig_xtrans(x)	bfc(constraint(x))
#define	ig_ytrans(x)	fc(constraint(x))


#define	file_num(x)	(x).ofile_num
#define	col_num(x)	(x).ocol_num
#define	line_num(x)	(x).oline_num

#define FposCopy(x, y)							\
( file_num(x) = file_num(y),						\
  line_num(x) = line_num(y),						\
  col_num(x)  = col_num(y)						\
)


/*****************************************************************************/
/*                                                                           */
/*  typedef LIST - two pointers used to make one doubly linked list          */
/*                                                                           */
/*****************************************************************************/

typedef struct { union rec *opred, *osucc; } LIST;


/*@::FIRST_UNION@*************************************************************/
/*                                                                           */
/*  typedef FIRST_UNION - first eight bytes of object record (after LISTs).  */
/*                                                                           */
/*  The fpos is overwritten in WORDs and QWORDs during FixAndPrintObject by  */
/*  the horizontal coordinate of the word, which has to be remembered.       */
/*  This part of the record is also used by font records to hold font        */
/*  bounding box data.                                                       */
/*                                                                           */
/*****************************************************************************/

typedef union
{
  FILE_POS	ofpos;
  struct
  {
  OBJTYPE	otype;
  unsigned char orec_size;
	int		oword_save_mark;
  } os11;

} FIRST_UNION;


/*@::SECOND_UNION, THIRD_UNION, FOURTH_UNION@*********************************/
/*                                                                           */
/*  typedef SECOND_UNION - twelve bytes holding various flags etc.           */
/*                                                                           */
/*****************************************************************************/

typedef union
{
  struct /* used by all tokens */
  {	unsigned char	oprecedence;
	unsigned char	ohspace, ovspace;
  } os21;

  struct /* used by WORD objects only, except underline used by all */
	 /* objects, including GAP_OBJ                              */
  {	FONT_NUM	oword_font;
	COLOUR_NUM	oword_colour;
	COLOUR_NUM	oword_underline_colour;
	TEXTURE_NUM	oword_texture;
	unsigned	ounderline	   : 2; /* aligns with os23.underline */
	BOOLEAN2		oword_outline	   : 1;
	LANGUAGE_NUM	oword_language	   : 6;
	BOOLEAN2		oword_baselinemark : 1;
	BOOLEAN2		oword_strut	   : 1;
	BOOLEAN2		oword_ligatures	   : 1;
	unsigned	oword_hyph	   : 1;
  } os22;

  struct /* used by non-WORD objects */
  {
  OBJTYPE ofoll_or_prec;
	OBJTYPE	ocross_type;	     /* CROSS objects only */
	unsigned short  ounused_os23_a;
	unsigned short  ounused_os23_b;
	unsigned	ounderline   : 2;    /* aligns with os22.underline */
	BOOLEAN2		onon_blocking: 1;
	BOOLEAN2		osized       : 1;
	BOOLEAN2		othreaded    : 1;
	BOOLEAN2		oexternal_hor: 1;
	BOOLEAN2		oexternal_ver: 1;
	BOOLEAN2		oblocked     : 1;
	BOOLEAN2		otrigger_ext : 1;
	BOOLEAN2	        omust_expand : 1;
  // type: COLM ROWM
	BOOLEAN2		ogall_dir    : 1;
	BOOLEAN2		oopt_hyph    : 1;
	BOOLEAN2		oopt_gazumped: 1;
	BOOLEAN2		oadjust_cat  : 1;
	BOOLEAN2		oforce_gall  : 1;
	/* don't forget ounderline from os22 applies in this union! */
  } os23;

  struct /* used by WORD and QWORD when they are database nodes */
  {	unsigned short	oleft_pos;
	unsigned char	oreading;
	unsigned char	oin_memory;
  } os24;

  struct /* used by WORD and QWORD when they are font records */
  {
    	FULL_LENGTH	ofont_bbox_lly;
    	FULL_LENGTH	ofont_bbox_ury;
  } os25;

  struct /* used by symbol table entries */
  {	unsigned char	oprecedence;
	BOOLEAN2		ois_tag		     : 1;
	BOOLEAN2		ohas_tag             : 1;
	BOOLEAN2		ohas_lpar            : 1;
	BOOLEAN2		ohas_rpar            : 1;
	BOOLEAN2		oright_assoc         : 1;
	BOOLEAN2		ois_target           : 1;
	BOOLEAN2		ohas_target          : 1;
	BOOLEAN2		oforce_target	     : 1;
	BOOLEAN2		ohas_body            : 1;
	BOOLEAN2		oindefinite          : 1;
	BOOLEAN2		orecursive           : 1;
	BOOLEAN2		ouses_extern_target  : 1;
	BOOLEAN2		ois_extern_target    : 1;
	BOOLEAN2		ois_key		     : 1;
	BOOLEAN2		ohas_key	     : 1;
	BOOLEAN2		odirty               : 1;
	BOOLEAN2		ovisible	     : 1;
	BOOLEAN2		ohas_mark	     : 1;
	BOOLEAN2		ohas_join	     : 1;
	BOOLEAN2		ohas_par             : 1;
	BOOLEAN2		ouses_galley	     : 1;
	BOOLEAN2		ohoriz_galley	     : 1;
	BOOLEAN2		oimports_encl	     : 1;
  } os26;

} SECOND_UNION;


/*****************************************************************************/
/*                                                                           */
/*  typedef THIRD_UNION - sixteen bytes usually holding an object size.      */
/*                                                                           */
/*  In database records this space is used for a file pointer, or a pointer  */
/*  to a LINE array if the database is in-memory; in certain                 */
/*  WORD objects used privately in z10.c it is used for a galley-position.   */
/*  In font records it holds the font size, space width, etc.  In filter     */
/*  words it holds a pointer to the symbol being filtered.                   */
/*                                                                           */
/*****************************************************************************/

typedef union
{
  struct
  {	FULL_LENGTH	oback[2];
	FULL_LENGTH	ofwd[2];
  } os31;

  FILE *odb_filep;
  LINE *odb_lines;

  struct
  {	FULL_LENGTH	ofont_size;
	FULL_LENGTH	ofont_xheight2;
	FULL_LENGTH	ofont_spacewidth;
    	FONT_NUM	ofont_num;
	unsigned short	ofont_page;
	MAPPING		ofont_mapping	: 7;
	BOOLEAN2		ofont_recoded	: 1;
  } os32;

  struct
  {	
  OBJTYPE	ocs_type;
	FILE_NUM	ocs_fnum;
	int		ocs_pos;
	int		ocs_lnum;
  } os33;

  struct /* words used as file definitions */
  {
	unsigned int	oline_count;
	unsigned short	ofile_number;
	FILE_TYPE	otype_of_file;
	unsigned char	oused_suffix;
	unsigned char	oupdated;
	PATH_TYPE	opath;
  } os34;

  union rec *ofilter_actual;

} THIRD_UNION;


/*****************************************************************************/
/*                                                                           */
/*  typedef FOURTH_UNION - 11 32-bit words holding a STYLE or CONSTRAINT.    */
/*                                                                           */
/*****************************************************************************/

typedef union
{
  STYLE		osave_style;
  CONSTRAINT	oconstraint;

} FOURTH_UNION;


/*@::OBJECT@******************************************************************/
/*                                                                           */
/*  typedef OBJECT - the general-purpose record used throughout Lout.        */
/*                                                                           */
/*  This record is a complex union type.  Which fields are defined in any    */
/*  given record depends on its type() tag field, as follows.  But first     */
/*  we define some collections of fields that are commonly defined together. */
/*                                                                           */
/*  ALL - these fields are defined in all objects.  They won't be mentioned  */
/*        again, but they are always there.                                  */
/*                                                                           */
/*      type            Tag field for the record                             */
/*      rec_size        Size of this record, in words (for memory allocator) */
/*      succ            Next element on list of parents, children            */
/*      pred            Previous element on list of parents, children        */
/*      fpos            Position in input file which gave rise to this       */
/*                      object (could be null; overwritten by word_save_mark */
/*                      locally in FixAndPrintOjbect).  It sub-fields are:   */
/*                                                                           */
/*                          file_num   internal file number                  */
/*                          line_num   line number in that file              */
/*                          col_num    column number on that line            */
/*                                                                           */
/*                      Lout attempts to put a meaningful fpos into every    */
/*                      object, so that error messages related to that       */
/*                      object can have meaningful line numbers.  This has   */
/*                      not been done in every case; it ought to be.         */
/*                                                                           */
/*  TOKEN - these fields are defined for all objects that are input tokens.  */
/*          They may be overwritten after parsing is completed.              */
/*                                                                           */
/*      precedence      Precedence of this token (0 if has no parameters)    */
/*      hspace          Horizontal space preceding this token                */
/*      vspace          Vertical space preceding this token                  */
/*                                                                           */
/*  SIZED - these fields are defined for all objects that represent Lout     */
/*          objects and hence have a horizontal and vertical size.  They     */
/*          will be undefined until after MinSize() is called on the object, */
/*          and defined thereafter.                                          */
/*                                                                           */
/*      back[COLM]      Horizontal size to left of object's mark             */
/*      fwd[COLM]       Horizontal size to right of object's mark            */
/*      back[ROWM]      Vertical size above object's mark                    */
/*      fwd[ROWM]       Vertical size below object's mark                    */
/*                                                                           */
/*  GAP - a gap between two Lout objects.                                    */
/*                                                                           */
/*      nobreak         TRUE if gap is unbreakable (has u tag)               */
/*      mark            TRUE if gap is marked (has ^ tag)                    */
/*      join            TRUE if a mark-joining gap (e.g. | not ||)           */
/*      units           units of measurement (fixed, or r or d etc)          */
/*      mode            gap mode (mark-to-mark, etc.)                        */
/*      width           width of gap in the given units                      */
/*                                                                           */
/*  STYLE - the style (attributes affecting the appearance) of an object.    */
/*                                                                           */
/*      line_gap        separation between lines                             */
/*      space_gap       separation induced by white space                    */
/*      yunit           value of y unit of measurement                       */
/*      zunit           value of z unit of measurement                       */
/*      outdent_len     amount to outdent in outdent style                   */
/*      smallcaps_len   size of small capitals                               */
/*      font            current font                                         */
/*      colour          current colour		                             */
/*      texture         current texture		                             */
/*      blanklinescale  scale factor for blank lines                         */
/*      language        current language		                     */
/*      vadjust	        @VAdjust in effect                                   */
/*      hadjust	        @HAdjust in effect                                   */
/*      padjust	        @PAdjust in effect                                   */
/*      small_caps	small capitals                                       */
/*      space_style	space style: lout, troff, tex, ..                    */
/*      hyph_style	hyphenation off or on                                */
/*      fill_style	fill lines with text off/on                          */
/*      display_style	display lines adjusted, ragged...                    */
/*      outline	: 2     TRUE if outlining words                              */
/*      nobreakfirst	no break after first line of para                    */
/*      nobreaklast	no break after last line of para                     */
/*      baselinemark	baseline char metrics                                */
/*      strut       	strut char metrics                                   */
/*      ligatures	use ligatures                                        */
/*      marginkerning	perform margin kerning                               */
/*                                                                           */
/*  CONSTRAINT - a constraint on how large some object is allowed to be,     */
/*               either horizontally or vertically                           */
/*                                                                           */
/*      bc              how large back may be (MAX_FULL_LEN if infinite)     */
/*      fc              how large fwd may be (MAX_FULL_LEN if infinite)      */
/*      bfc             how large back + fwd may be (MAX_FULL_LEN if inf.)   */
/*                                                                           */
/*                                                                           */
/*  Here now is the list of all object types, what they represent, and       */
/*  what fields they contain.  The list also indicates what children each    */
/*  object of the given type can expect to have.                             */
/*                                                                           */
/*  LINK - one link in the directed acyclic graph which is Lout's universal  */
/*         internal data structure.  All the other types below are various   */
/*         types of nodes.  Has ALL only (and no fpos) except see CROSS_SYM  */
/*                                                                           */
/*  GAP_OBJ - a gap between two Lout objects                                 */
/*                                                                           */
/*      gap             The gap itself (type GAP)                            */
/*      underline       TRUE if continuous underlining crosses this gap      */
/*      save_*          These fields used by optimum paragraph breaker only  */
/*      first child     If the gap is not just white space, the gap object   */
/*                                                                           */
/*  CLOSURE - an invocation of a user-defined symbol, not yet expanded       */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           After sizing if indefinite (the sizes will be zero)  */
/*      save_style      Style to print this invocation in when expanded      */
/*      actual          The symbol table record defining this symbol         */
/*      threaded        TRUE if symbol lies on a vertical thread             */
/*      external_ver    TRUE if symbol is external in a vertical galley      */
/*      external_hor    TRUE if symbol is external in a horizontal galley    */
/*      children        PAR objects whose children are the actual parameters */
/*                                                                           */
/*  UNDER_REC - a temporary object inserted by FixAndPrintObject to help     */
/*              with working out continuous underlining                      */
/*                                                                           */
/*      back(COLM)      Horizontal position of start of underline            */
/*      fwd(COLM)       Horizontal position of end of underline              */
/*      word_font       Font determining underline appearance                */
/*      word_underline_colour  The colour of the underline                   */
/*      word_texture    The texture of the underline                         */
/*                                                                           */
/*  PAGE_LABEL - a @PageLabel object                                         */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           Indefinite, so all sizes will be zero                */
/*      first child     The parameter of the @PageLabel object               */
/*                                                                           */
/*  NULL_CLOS - a @Null object                                               */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           Indefinite, so all sizes will be zero                */
/*                                                                           */
/*  CROSS, FORCE_CROSS - a cross reference (or forcing cross reference) obj  */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           Indefinite, so all sizes will be zero                */
/*      cross_type      Type of cross reference (preceding, following, etc.) */
/*      children        The two parameters of the cross reference            */
/*                                                                           */
/*  HEAD - the header record for a galley invocation                         */
/*                                                                           */
/*      force_gall      TRUE if this is a forcing galley (i.e. "force into") */
/*      actual          The symbol table record defining this galley         */
/*      enclose_obj     If galley has @Enclose, the enclose object           */
/*      limiter         Helps decide whether to break off or scale if stuck  */
/*      opt_components  If optimizing, the sequence of components            */
/*      opt_constraints If optimizing, the sequence of size constraints      */
/*      opt_counts      If optimizing, the sequence of numbers of components */
/*                      In each child of opt_counts, comp_count has the num  */
/*      opt_comps_permitted number of components left before opt break       */
/*      opt_hyph        If optimizing, whether to hyphenate the galley       */
/*      opt_gazumped    If optimizing, galley has been gazumped recently     */
/*      gall_dir        Promotion direction (COLM for horizontal galleys)    */
/*      ready_galls     Galleys read in from cross reference database        */
/*      must_expand     TRUE if must expand galley object even if indefinite */
/*      sized           TRUE after galley object has been sized              */
/*      foll_or_prec    Direction of search for target (forward, back, etc.) */
/*      whereto         Symbol this galley is targeted at                    */
/*      seen_nojoin     TRUE if // op found within galley anywhere           */
/*      headers[i]      each either nilobj or an ACAT of header components   */
/*      head_next       which header[i] we will use next.                    */
/*                                                                           */
/*  SPLIT - a split object, used for building tables                         */
/*                                                                           */
/*      SIZED           The size of the whole object                         */
/*      first child     An object whose horizontal size is the overall size  */
/*      second child    An object whose vertical size is the overall size    */
/*                                                                           */
/*  PAR - actual parameter of a symbol invocation (always child of CLOSURE)  */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      actual          The symbol table record defining this parameter      */
/*      first child     A Lout object, the value of this parameter           */
/*                                                                           */
/*  WORD, QWORD - a literal word, or a literal word entered in quotes ""     */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the word                                 */
/*      word_font       Font to print this word in (from style)              */
/*      word_colour     Colour to print this word in (from style)            */
/*      word_underline_colour  Colour to print underlines in (from style)    */
/*      word_texture    texture to print this word in (from style)           */
/*      word_outline    If TRUE, print this word in outline (from style)     */
/*      word_language   Language (for hyphenation) of this word (from style) */
/*      word_baselinemark TRUE if mark of this word goes through baseline    */
/*      word_strut      TRUE if this word's char metrics are to be strutted  */
/*      word_ligatures  TRUE if ligatures wanted in this word                */
/*      underline       TRUE if continuous underlining goes under this word  */
/*      word_hyph       Hyphenation wanted for this word (from style)        */
/*      word_save_mark  Coord of column mark, temporarily in FixAndPrint     */
/*      string[]        The characters of the word, null-terminated          */
/*                                                                           */
/*  WORD, QWORD when used as database header records                         */
/*                                                                           */
/*      string[]        Database index file name                             */
/*      reading         TRUE if this database can be read from               */
/*      in_memory       TRUE if this database's index is held in memory      */
/*      db_filep        Pointer to database file (if not in_memory)          */
/*      left_pos        Seek pos of 1st entry in db_filep (if not in_memory) */
/*      db_lines        Pointer to database index lines (if in_memory)       */
/*      db_lineslen     Number of database index lines (if in_memory)        */
/*      first child     List of symbols held in this database                */
/*      other children  CROSS_SYM symbols of symbols in this database        */
/*                      The *links* to these have the following fields:      */
/*                          number   An ID number for this sym in this db    */
/*                          db_targ  TRUE if sym is a galley target          */
/*                                                                           */
/*  WORD, QWORD when used as font records (consult z37.c for more detail)    */
/*                                                                           */
/*      string[]        Font name                                            */
/*      font_num        The number of this font                              */
/*      font_page       Number of most recent page using this font           */
/*      font_size       Size of this font                                    */
/*      font_xheight2   Half-x height of this font                           */
/*      font_bbox_lly   The lly value of the font bounding box               */
/*      font_bbox_ury   The ury value of the font bounding box               */
/*      font_spacewidth Preferred width of space between words in this font  */
/*      font_mapping    The mapping to apply with this font                  */
/*      font_recoded    TRUE if font needs recoding in PostScript output     */
/*                                                                           */
/*  WORD, QWORD when used in hash table to check whether crs defined twice   */
/*                                                                           */
/*      db_checksym     Symbol of the cross reference                        */
/*      string[]        Tag of the cross reference                           */
/*                                                                           */
/*  HSPANNER (VSPANNER) - An object that spans columns (rows)                */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      spanner_broken  TRUE after BreakObject() applied to this object      */
/*      spanner_count   Number of columns (rows) spanned by this spanner     */
/*      spanner_sized   Number of cols (rows) of this spanner sized so far   */
/*      spanner_fixed   Number of cols (rows) of this spanner fixed so far   */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      constraint      Space available for this object as known to MinSize  */
/*      first child     The object that is doing the spanning                */
/*                                                                           */
/*  COL_THR (ROW_THR) - object representing all objects on a col (row) mark  */
/*                                                                           */
/*      SIZED           The horizontal (vertical) size only                  */
/*      thr_state       Tells whether thread is sized or not yet             */
/*      children        The objects on the mark                              */
/*      parents         The parents of the children (one-to-one)             */
/*                                                                           */
/*  ACAT - a paragraph (sequence of objects separated by & or white space)   */
/*                                                                           */
/*      SIZED           The size of the object                               */
/*      save_style      The style to print this paragraph in                 */
/*      children        The paragraph's objects and gaps (obj-gap-obj...obj) */
/*                                                                           */
/*  HCAT (VCAT) - a horizontal (vertical) sequence of objects                */
/*                                                                           */
/*      SIZED           The size of the object                               */
/*      save_style      The style to print this object in                    */
/*      children        The objects and gaps (obj-gap-obj...obj)             */
/*      adjust_cat      Whether to perform adjustment (@VAdjust, etc.)       */
/*                                                                           */
/*  WIDE (HIGH) - @Wide (@High) object                                       */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      constraint      The horizontal (vertical) size constraint            */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  HSHIFT (VSHIFT) - @HShift (@VShift) object                               */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      shift_type      left, right etc.                                     */
/*      shift_gap       The amount to shift                                  */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  HMIRROR (VMIRROR) - @HMirror (@VMirror) object                           */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  HSCALE (VSCALE) - @HScale (@VScale) object                               */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      constraint      used temporarily by FixAndPrintObject                */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  SCALE - @Scale object                                                    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      bc(constraint)  The horizontal scale factor                          */
/*      fc(constraint)  The vertical scale factor                            */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      vert_sized      TRUE if vertical size of object is known             */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  BEGIN_HEADER, SET_HEADER - @BeginHeaderComponent, @SetHeaderComponent    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object (will be 0)                   */
/*      first child     The gap for after this header (before manifesting)   */
/*      last child      The right parameter of this symbol                   */
/*                                                                           */
/*  END_HEADER, CLEAR_HEADER - @EndHeaderComponent, @ClearHeaderComponent    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object (will be 0)                   */
/*                                                                           */
/*  ONE_COL (ONE_ROW) - @OneCol (@OneRow) object                             */
/*  HCOVER (VCOVER) - @HCover (@VCover) object                               */
/*  HCONTRACT (VCONTRACT) - @HContract (@VContract) object                   */
/*  HEXPAND (VEXPAND) - @HExpand (@VExpand) object                           */
/*  START_HSPAN, START_VSPAN - @StartHSpan, @StartVSpan                      */
/*  START_HVSPAN - @StartHVSpan                                              */
/*  HSPAN (VSPAN) - @HSpan (@VSpan) symbols                                  */
/*  KERN_SHRINK - @KernShrink object                                         */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      first child     The right parameter of this symbol (if any)          */
/*                                                                           */
/*  PADJUST (HADJUST, VADJUST) - @PAdjust (@HAdjust, @VAdjust) symbols       */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  ROTATE - @Rotate symbol                                                  */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      sparec(cons)    Amount to rotate by (after manifesting)              */
/*      first child     Amount to rotate by (before manifesting)             */
/*      last child      The right parameter of this symbol                   */
/*                                                                           */
/*  BACKGROUND - @Background symbol                                          */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      children        The two parameters of this symbol                    */
/*                                                                           */
/*  GRAPHIC, PLAIN_GRAPHIC - @Graphic, @PlainGraphic symbols                 */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      children        The two parameters of this symbol                    */
/*                                                                           */
/*  LINK_SOURCE, LINK_DEST, LINK_URL - @LinkSource, @LinkDest, @URLLink      */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      children        The two parameters of this symbol                    */
/*                                                                           */
/*  CASE - @Case symbol                                                      */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      first child     The left parameter of @Case                          */
/*      last child      The right parameter (sequence of @Yield objects)     */
/*                                                                           */
/*  VERBATIM (RAWVERBATIM) - @Verbatim (@RawVerbatim) symbol                 */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      first child     The right parameter of this symbol                   */
/*                                                                           */
/*  FILTERED - object recording filtered Lout object                         */
/*                                                                           */
/*      filter_use_begin TRUE if filter enclosed in @Begin ... @End          */
/*      filter_actual   The symbol this is an invocation of                  */
/*      first child     WORD containing file name of filter input file       */
/*      second child    WORD containing file name of filter output file      */
/*      last child      Scope snapshot for reading filter output file        */
/*                                                                           */
/*  XCHAR - @Char symbol                                                     */
/*  NEXT - @Next symbol                                                      */
/*  ONE_OF - @OneOf symbol                                                   */
/*  UNDERLINE - @Underline symbol                                            */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      last child      The right parameter of this symbol                   */
/*                                                                           */
/*  FONT, SPACE, BREAK - @Font, @Space, @Break symbols                       */
/*  YUNIT, ZUNIT - @YUnit, @ZUnit symbols                                    */
/*  COLOUR, UNDERLINE_COLOUR, TEXTURE - @SetColour, @SetUnderlineColour      */
/*  TEXTURE - @SetTexture                                                    */
/*  OUTLINE, LANGUAGE - @Outline, @Language symbols                          */
/*  PLUS, MINUS, - @Plus, @Minus symbols                                     */
/*  MELD, COMMON, RUMP, INSERT - @Meld, @Common, @Rump, @Insert symbols      */
/*  OPEN, TAGGED - @Open, @Tagged symbols                                    */
/*  YIELD - @Yield symbol                                                    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      first child     The left parameter of this symbol                    */
/*      last child      The right parameter of this symbol                   */
/*                                                                           */
/*  ENV_OBJ - a Lout object with environment attached                        */
/*                                                                           */
/*      first child     The Lout object                                      */
/*      last child      Its environment (ENV object)                         */
/*                                                                           */
/*  ENV - environment of some Lout object                                    */
/*                                                                           */
/*      children        Components of the environment                        */
/*                                                                           */
/*  INCGRAPHIC, SINCGRAPHIC - @IncludeGraphic, @SysIncludeGraphic symbols    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      SIZED           The size of the object                               */
/*      save_mark       used temporarily by FixAndPrintObject                */
/*      incgraphic_ok   TRUE if file name pans out OK                        */
/*      last child      The right parameter of this symbol                   */
/*                                                                           */
/*  TSPACE, TJUXTA - tokens representing white space                         */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      mark(gap)       FALSE                                                */
/*      join(gap)       TRUE                                                 */
/*                                                                           */
/*  BEGIN - @Begin symbol                                                    */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*      actual          Symbol this @Begin starts parameter of               */
/*                                                                           */
/*  END - @End symbol                                                        */
/*  LBR, RBR - tokens representing left brace and right brace                */
/*  USE, NOT_REVEALED - @Use, @NotRevealed symbols                           */
/*  GSTUB_EXT, GSTUB_INT, GSTUB_NONE - stubs for transferred galleys         */
/*  UNEXPECTED_EOF - unexpected end of file token                            */
/*  INCLUDE, SYS_INCLUDE - @Include, @SysInclude symbols                     */
/*  INCG_REPEATED, SINCG_REPEATED -                                          */
/*    @IncludeGraphicRepeated, @SysIncludeGraphicRepeated symbols            */
/*  PREPEND, SYS_PREPEND - @PrependGraphic, @SysPrependGraphic symbols       */
/*  ENVA, ENVB, ENVC, ENVD - @LEnvA, @LEnvB, @LEnvC, @LEnvD tokens only      */
/*  CENV, CLOS, LVIS, LUSE, LEO - @LCEnv, @LClos, @LVis, @LUse, @LEO tokens  */
/*  BACKEND - @BackEnd symbol                                                */
/*  CURR_LANG, CURR_FAMILY, CURR_FACE - @CurrLang, @CurrFamily, @CurrFace    */
/*  CURR_YUNIT, CURR_ZUNIT - @CurrYUnit, @CurrZUnit                          */
/*                                                                           */
/*      TOKEN           While still being parsed                             */
/*                                                                           */
/*  DEAD - the index of a dead galley                                        */
/*                                                                           */
/*  UNATTACHED - the index of an unattached galley                           */
/*                                                                           */
/*      actual          The galley referred to                               */
/*      non_blocking    TRUE if this index should not block galley flushing  */
/*      blocked         TRUE if this index is now blocking galley flushing   */
/*      pinpoint        Exact anchor point of this index                     */
/*                                                                           */
/*  RECEPTIVE, RECEIVING - the index of a receptive or receiving object      */
/*                                                                           */
/*      actual          The object (symbol invocation) referred to           */
/*      trigger_externs TRUE is this index's galley has external galleys     */
/*      non_blocking    TRUE if this index should not block galley flushing  */
/*      blocked         TRUE if this index is now blocking galley flushing   */
/*                                                                           */
/*  RECURSIVE - the index of a recursive but definite object                 */
/*                                                                           */
/*      actual          The recursive symbol invocation referred to          */
/*                                                                           */
/*  PRECEDES - an index recording a precedes/follows flushing constraint     */
/*                                                                           */
/*      first child     Other parent of this is the corresponding FOLLOWS    */
/*                                                                           */
/*  FOLLOWS - an index recording a precedes/follows flushing constraint      */
/*                                                                           */
/*      blocked         TRUE if this index is now blocking galley flushing   */
/*      first child     Other parent of this is the corresponding PRECEDES   */
/*                                                                           */
/*  CROSS_LIT - not actually an object at all                                */
/*                                                                           */
/*  CROSS_PREC, CROSS_FOLL, CROSS_FOLL_OR_PREC - the index of a cross ref    */
/*                                                                           */
/*      actual          The cross reference referred to                      */
/*      underline       TRUE if continuous underline goes through here       */
/*      first child     Equal to actual                                      */
/*                                                                           */
/*  GALL_PREC, GALL_FOLL, GALL_FOLL_OR_PREC - index of a galley              */
/*                                                                           */
/*      actual          The galley referred to                               */
/*      underline       TRUE if continuous underline goes through here       */
/*      pinpoint        Exact anchor point of this index                     */
/*                                                                           */
/*  GALL_TARG - index of the target of a galley                              */
/*                                                                           */
/*      actual          The galley target (symbol invocation) referred to    */
/*      underline       TRUE if continuous underline goes through here       */
/*                                                                           */
/*  PAGE_LABEL_IND - the index of a @PageLabel object                        */
/*                                                                           */
/*      actual          The @PageLabel object referred to                    */
/*      underline       TRUE if continuous underline goes through here       */
/*      first child     Equal to actual                                      */
/*                                                                           */
/*  SCALE_IND - the index of a @Scale symbol with empty left parameter       */
/*  COVER_IND - the index of an @HCover or @VCover object                    */
/*  EXPAND_IND - the index of an @HExpand or @VExpand object                 */
/*                                                                           */
/*      actual          The object referred to                               */
/*      underline       TRUE if continuous underline goes through here       */
/*                                                                           */
/*  THREAD - a sequence of threads (basically local to Manifest)             */
/*                                                                           */
/*      children        The threads                                          */
/*                                                                           */
/*  CROSS_SYM - a record of the cross reference state of some symbol         */
/*                                                                           */
/*      target_state    Whether we currently have a preceding target         */
/*      target_file     Which file target is written to                      */
/*      target_val      Value of target (if target_state == SEEN_TARGET)     */
/*      target_seq      A sequence number                                    */
/*      target_pos      Seek position of target in target_file               */
/*      target_lnum     Line number of target in target_file                 */
/*      gall_seq        Sequence number for galleys targeted to here         */
/*      symb            The symbol table record of the symbol this is for    */
/*      gall_tag        I forget!                                            */
/*      gall_tfile      The most recent cr database file for this sym        */
/*      children        Cross references and galleys waiting for a target    */
/*                      These children have the following fields:            */
/*                                                                           */
/*                          string[]   The sequence number                   */
/*                          cs_type    The cross reference type              */
/*                          cs_fnum    File number where value written       */
/*                          cs_pos     File seek position                    */
/*                          cs_lnum    File line number                      */
/*                                                                           */
/*  CR_ROOT - all CROSS_SYM objects are children of this singleton           */
/*                                                                           */
/*      children        All CROSS_SYM symbols                                */
/*                                                                           */
/*  MACRO - a symbol table entry for a symbol which is a macro               */
/*  LOCAL - a symbol table entry for a symbol which is a local symbol        */
/*  LPAR - a symbol table entry for a symbol which is a left parameter       */
/*  RPAR - a symbol table entry for a symbol which is a right parameter      */
/*  NPAR - a symbol table entry for a symbol which is a named parameter      */
/*                                                                           */
/*      enclosing       The symbol that this one is defined within, if any   */
/*      sym_body        The symbol body (token sequence if MACRO)            */
/*      base_uses       Local to symbol table, for calculating call graph    */
/*      uses            Call graph info                                      */
/*      marker          For call graph calculation                           */
/*      imports         The import list preceding this symbol, if any        */
/*      filter          Child @Filter symbol, if any                         */
/*      use_invocation  A @Use clause containing this symbol, if any         */
/*      predefined      If predefined symbol, its non-zero enum code         */
/*      has_compulsory  Number of parameters with "compulsory" tag           */
/*      uses_count      Number of times this symbol is used                  */
/*      npar_code       One-letter abbreviation for this NPAR                */
/*      cross_sym       The CROSS_SYM record for this symbol, if any         */
/*      recursive       TRUE if symbol is recursive                          */
/*      has_body        TRUE if symbol has a body parameter                  */
/*      imports_encl    TRUE if symbol imports the symbol enclosing itself   */
/*      right_assoc     TRUE if this symbol has "associativity right"        */
/*      precedence      The precedence of this symbol                        */
/*      indefinite      TRUE if this symbol is indefinite (e.g. receptive)   */
/*      recursive       TRUE if symbol is recursive                          */
/*      is_extern_target   TRUE if symbol is the target of external galley   */
/*      uses_extern_target TRUE if symbol uses target of an external galley  */
/*      visible         TRUE if symbol is exported                           */
/*      uses_galley     TRUE if symbol uses a galley                         */
/*      horiz_galley    if galley, ROWM if vertical, COLM if horizontal      */
/*      is_compulsory   TRUE if this is a parameter with "compulsory" tag    */
/*      dirty           TRUE if must copy this parameter, not link it        */
/*      has_par         TRUE if this symbol has at least one parameter       */
/*      has_lpar        TRUE if this symbol has a left parameter             */
/*      has_rpar        TRUE if this symbol has a right or body parameter    */
/*      has_target      TRUE if this symbol has a target (is a galley)       */
/*      force_target    TRUE if this symbol has a forcing target             */
/*      is_target       TRUE if this symbol is @Target, defining a target    */
/*      has_tag         TRUE if this symbol has a @Tag parameter             */
/*      is_tag          TRUE if this symbol is a @Tag parameter              */
/*      has_key         TRUE if this symbol has a @Key parameter             */
/*      is_key          TRUE if this symbol is a @Key parameter              */
/*      has_optimize    TRUE if this symbol has an @Optimize parameter       */
/*      is_optimize     TRUE if this symbol is an @Optimize parameter        */
/*      has_merge       TRUE if this symbol has a @Merge parameter           */
/*      is_merge        TRUE if this symbol is a @Merge parameter            */
/*      has_enclose     TRUE if this symbol has an @Enclose parameter        */
/*      is_enclose      TRUE if this symbol is an @Enclose parameter         */
/*                                                                           */
/*  EXT_GALL - a record of an external galley, not actually read in yet      */
/*                                                                           */
/*      eg_fnum         Number of file read from                             */
/*      eg_fpos         Position in that file                                */
/*      eg_lnum         Line number in that file                             */
/*      eg_cont         Continuation (where to look for next galley)         */
/*      eg_symbol       The symbol that is the target of this galley         */
/*      first child     The galley tag                                       */
/*      second child    The galley sequence string                           */
/*                                                                           */
/*  CR_LIST - a list of cross references                                     */
/*                                                                           */
/*      children        The cross-references                                 */
/*                                                                           */
/*  SCOPE_SNAPSHOT - a snapshot of one element of the current scope stack    */
/*                                                                           */
/*      ss_npars_only   Value of npars_only in this element                  */
/*      ss_vis_only     Value of vis_only in this element                    */
/*      ss_body_ok      Value of body_ok in this element                     */
/*      ss_suppress     Value of suppress_visible in this element            */
/*                                                                           */
/*  DISPOSED - a disposed object (available for reallocation)                */
/*                                                                           */
/*****************************************************************************/

typedef union rec
{
  struct word_type	/* all fields of WORD and QWORD, token and object */
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     THIRD_UNION	ou3;
     FULL_CHAR		ostring[4];
  } os1;

  struct closure_type	/* all fields of CLOSURE, both as token and object */
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     THIRD_UNION	ou3;
     FOURTH_UNION	ou4;
     union rec		*oactual;
     union
     { union rec *owhereto;
       union rec *opinpoint;
       FULL_LENGTH    osave_mark;
     } oux;
  } os2;
  
  struct head_type	/* all fields of HEAD, both as token and object */
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     THIRD_UNION	ou3;
     FOURTH_UNION	ou4;
     union rec		*oactual;
     union
     { union rec *owhereto;
       union rec *opinpoint;
       FULL_LENGTH    osave_mark;
     } oux;
     union rec *oready_galls;
     union rec *oopt_components;
     union rec *oopt_constraints;
     union rec *oopt_counts;
     union rec *olimiter;
     union rec *oenclose_obj;
     union rec *oheaders[MAX_HCOPIES];
     int	ohead_next;
     int        oopt_comps_permitted;
  } os2a;
  
  struct object_type	/* the general OBJECT */
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     THIRD_UNION	ou3;
     FOURTH_UNION	ou4;
  } os3;

  struct link_type	/* LINK */
  {  LIST		olist[2];
     OBJTYPE	otype;
     unsigned char	onumber;
     unsigned char	odb_targ;
  } os4;
  
  struct gapobj_type	/* GAP_OBJ */
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     GAP		ogap;
     int		osave_badness;		/* optimum paragraph breaker */
     FULL_LENGTH	osave_space;		/* optimum paragraph breaker */
     FULL_LENGTH	osave_actual_gap;	/* optimum paragraph breaker */
     union rec  	*osave_prev;		/* optimum paragraph breaker */
     union rec  	*osave_cwid;		/* optimum paragraph breaker */
  } os5;

  struct symbol_type
  {  LIST		olist[2];
     FIRST_UNION	ou1;
     SECOND_UNION	ou2;
     union rec		*oenclosing;
     union rec		*osym_body;
     union rec		*obase_uses;
     union rec		*ouses;
     union rec		*omarker;
     union rec		*ocross_sym;
     union rec		*oimports;
     union rec		*ofilter;
     union rec		*ouse_invocation;
     OBJTYPE 	opredefined;
     unsigned short 	ohas_compulsory;
     unsigned char	ouses_count;
     unsigned char	onpar_code;
     BOOLEAN2		ois_optimize	     : 1;
     BOOLEAN2		ohas_optimize	     : 1;
     BOOLEAN2		ois_merge	     : 1;
     BOOLEAN2		ohas_merge	     : 1;
     BOOLEAN2		ois_enclose	     : 1;
     BOOLEAN2		ohas_enclose	     : 1;
     BOOLEAN2		ois_compulsory	     : 1;
  } os6;

  struct cr_type
  {  LIST		olist[2];
     OBJTYPE	otype;
     unsigned char	otarget_state;
     FILE_NUM		otarget_file;
     union rec		*otarget_val;
     int		otarget_seq;
     int		otarget_pos;
     int		otarget_lnum;
     int		ogall_seq;
     union rec		*osymb;
     union rec		*ogall_tag;
     FILE_NUM		ogall_tfile;
  } os7;

  struct ext_gall_type
  {  LIST		olist[2];
     OBJTYPE	otype;
     FILE_NUM		oeg_fnum;
     int		oeg_lnum;
     long		oeg_fpos;
     long		oeg_cont;
     union rec		*oeg_symbol;
  } os8;

  struct uses_type
  {  union rec	*oitem;
     union rec	*onext;
  } os9;
#define	USES_SIZE ceiling( sizeof(struct uses_type), sizeof(ALIGN) )

  struct hash_entry_type
  {  LIST	olist[1];
  } os10;

} REAL_OBJECT;

// Attention: OBJECT is a pointer type!
typedef REAL_OBJECT* OBJECT;

/*@::macros for fields of OBJECT@*********************************************/
/*                                                                           */
/*  Macros for fields of OBJECT.                                             */
/*                                                                           */
/*****************************************************************************/

// #define	succ(x, dim)		(x)->os1.olist[dim].osucc
INLINE OBJECT succ(OBJECT x, DIR_TE dir) {
  return (x)->os1.olist[dir.dir].osucc;
}
// TODO: make void
INLINE OBJECT setSucc(OBJECT x, DIR_TE dir, OBJECT y) {
  return (x)->os1.olist[dir.dir].osucc = y;
}
// #define	pred(x, dim)		(x)->os1.olist[dim].opred
INLINE OBJECT pred(OBJECT x, DIR_TE dir) {
  return (x)->os1.olist[dir.dir].opred;
}
// TODO: make void
INLINE OBJECT setPred(OBJECT x, DIR_TE dir, OBJECT y) {
  return (x)->os1.olist[dir.dir].opred = y;
}

#define	rec_size(x)		(x)->os1.ou1.os11.orec_size
#define font_bbox_lly(x)	(x)->os1.ou2.os25.ofont_bbox_lly
#define font_bbox_ury(x)	(x)->os1.ou2.os25.ofont_bbox_ury
#define	precedence(x)		(x)->os1.ou2.os21.oprecedence
#define	hspace(x)		(x)->os1.ou2.os21.ohspace
#define	vspace(x)		(x)->os1.ou2.os21.ovspace

INLINE OBJTYPE type(OBJECT x) {
  return (x)->os1.ou1.os11.otype;
}
INLINE void setType(OBJECT x, OBJTYPE type) {
  (x)->os1.ou1.os11.otype = type;
}

#define	word_font(x)		(x)->os1.ou2.os22.oword_font
#define spanner_count(x)	word_font(x)

// TODO: only allowed values INCGRAPHIC_E and SINCGRAPHIC_E
INLINE void setIncg_type(OBJECT x, OBJTYPE type) {
  word_font(x) = type.objtype;
}

INLINE OBJTYPE incg_type(OBJECT x) {
  switch(word_font(x)) {
    case INCGRAPHIC_E:
      return INCGRAPHIC;
    case SINCGRAPHIC_E:
      return SINCGRAPHIC;
    default:
      Error(1, 1, "incg_type: only (S)INCGRAPHIC allowed", FATAL, no_fpos);
  }
  return DUMMY;
}

#define	word_colour(x)		(x)->os1.ou2.os22.oword_colour
#define	word_underline_colour(x) (x)->os1.ou2.os22.oword_underline_colour
#define	word_texture(x)		(x)->os1.ou2.os22.oword_texture
#define spanner_sized(x)	word_colour(x)
#define	word_outline(x)		(x)->os1.ou2.os22.oword_outline
#define	word_language(x)	(x)->os1.ou2.os22.oword_language
#define	word_baselinemark(x)	(x)->os1.ou2.os22.oword_baselinemark
#define	word_strut(x)		(x)->os1.ou2.os22.oword_strut
#define	word_ligatures(x)	(x)->os1.ou2.os22.oword_ligatures
#define	spanner_fixed(x)	word_language(x)
#define	spanner_broken(x)	word_outline(x)

// #define	underline(x)		(x)->os1.ou2.os22.ounderline
INLINE UNDER underline(OBJECT x) {
  // return (x)->os1.ou2.os22.ounderline;
  unsigned under = (x)->os1.ou2.os22.ounderline;
  UNDER res = UNDER_UNDEF;
  switch(under) {
    case UNDER_UNDEF_E:
      res = UNDER_UNDEF;
      break;
    case UNDER_OFF_E:
      res = UNDER_OFF;
      break;
    case UNDER_ON_E:
      res = UNDER_ON;
      break;
    default:
      // TODO
      Error(2, 205, "underline %u unknown in OBJECT %p", UNEXPECTED_DEFAULT, no_fpos, under, x);
  }
  return res;
}
INLINE void setUnderline(OBJECT x, UNDER under) {
  (x)->os1.ou2.os22.ounderline = under.underline;
}
INLINE BOOLEAN2 objectHasUnderline(OBJECT x, UNDER under) {
  return (x)->os1.ou2.os22.ounderline == under.underline;
}

#define	word_hyph(x)		(x)->os1.ou2.os22.oword_hyph
#define	filter_use_begin(x)	(x)->os1.ou2.os22.oword_colour

#define	ss_npars_only(x)	word_font(x)
#define	ss_vis_only(x)		word_colour(x)
#define	ss_body_ok(x)		word_outline(x)
#define	ss_suppress(x)		word_language(x)

#define	non_blocking(x)		(x)->os1.ou2.os23.onon_blocking
#define	vert_sized(x)		non_blocking(x)
#define	sized(x)		(x)->os1.ou2.os23.osized
#define	threaded(x)		(x)->os1.ou2.os23.othreaded
#define	external_ver(x)		(x)->os1.ou2.os23.oexternal_ver
#define	external_hor(x)		(x)->os1.ou2.os23.oexternal_hor
#define	blocked(x)		(x)->os1.ou2.os23.oblocked
#define	seen_nojoin(x)		blocked(x)
#define	trigger_externs(x)	(x)->os1.ou2.os23.otrigger_ext
#define	must_expand(x)		(x)->os1.ou2.os23.omust_expand
#define	gall_dir(x)		(x)->os1.ou2.os23.ogall_dir
#define	opt_hyph(x)		(x)->os1.ou2.os23.oopt_hyph
#define	opt_gazumped(x)		(x)->os1.ou2.os23.oopt_gazumped
#define	adjust_cat(x)		(x)->os1.ou2.os23.oadjust_cat
#define	force_gall(x)		(x)->os1.ou2.os23.oforce_gall
#define	cross_type(x)		(x)->os1.ou2.os23.ocross_type
#define	foll_or_prec(x)		(x)->os1.ou2.os23.ofoll_or_prec
#define	thr_state(x)		cross_type(x)
#define	incgraphic_ok(x)	cross_type(x)

#define	left_pos(x)		(x)->os1.ou2.os24.oleft_pos
#define	db_lineslen(x)		left_pos(x)
#define	reading(x)		(x)->os1.ou2.os24.oreading
#define	in_memory(x)		(x)->os1.ou2.os24.oin_memory

#define	is_tag(x)		(x)->os1.ou2.os26.ois_tag
#define	has_tag(x)		(x)->os1.ou2.os26.ohas_tag
#define	has_lpar(x)		(x)->os1.ou2.os26.ohas_lpar
#define	has_rpar(x)		(x)->os1.ou2.os26.ohas_rpar
#define	right_assoc(x)		(x)->os1.ou2.os26.oright_assoc
#define	is_target(x)		(x)->os1.ou2.os26.ois_target
#define	has_target(x)		(x)->os1.ou2.os26.ohas_target
#define	force_target(x)		(x)->os1.ou2.os26.oforce_target
#define	has_body(x)		(x)->os1.ou2.os26.ohas_body
#define	indefinite(x)		(x)->os1.ou2.os26.oindefinite
#define	recursive(x)		(x)->os1.ou2.os26.orecursive
#define	uses_extern_target(x)	(x)->os1.ou2.os26.ouses_extern_target
#define	is_extern_target(x)	(x)->os1.ou2.os26.ois_extern_target
#define	is_key(x)		(x)->os1.ou2.os26.ois_key
#define	has_key(x)		(x)->os1.ou2.os26.ohas_key
#define	dirty(x)		(x)->os1.ou2.os26.odirty
#define	visible(x)		(x)->os1.ou2.os26.ovisible
#define	has_mark(x)		(x)->os1.ou2.os26.ohas_mark
#define	has_join(x)		(x)->os1.ou2.os26.ohas_join
#define	has_par(x)		(x)->os1.ou2.os26.ohas_par
#define	uses_galley(x)		(x)->os1.ou2.os26.ouses_galley
#define	horiz_galley(x)		(x)->os1.ou2.os26.ohoriz_galley
#define	imports_encl(x)		(x)->os1.ou2.os26.oimports_encl

#define	fpos(x)			(x)->os1.ou1.ofpos
#define word_save_mark(x)	(x)->os1.ou1.os11.oword_save_mark

// #define	back(x, dim)		(x)->os1.ou3.os31.oback[dim]
INLINE FULL_LENGTH back(OBJECT x, DIM_TE dim) {
  return (x)->os1.ou3.os31.oback[dim.dim];
}
INLINE FULL_LENGTH* back_ref(OBJECT x, DIM_TE dim) {
  return &((x)->os1.ou3.os31.oback[dim.dim]);
}
INLINE void setBack(OBJECT x, DIM_TE dim, FULL_LENGTH l) {
  (x)->os1.ou3.os31.oback[dim.dim] = l;
}
#define	comp_count(x)		back(x, COLM)
#define	setComp_count(x, l)		setBack(x, COLM, l)
// #define	fwd(x, dim)		(x)->os1.ou3.os31.ofwd[dim]
INLINE FULL_LENGTH fwd(OBJECT x, DIM_TE dim) {
  return (x)->os1.ou3.os31.ofwd[dim.dim];
}
INLINE FULL_LENGTH* fwd_ref(OBJECT x, DIM_TE dim) {
  return &((x)->os1.ou3.os31.ofwd[dim.dim]);
}
INLINE void setFwd(OBJECT x, DIM_TE dim, FULL_LENGTH l) {
  (x)->os1.ou3.os31.ofwd[dim.dim] = l;
}
#define	size(x, dim)		(back(x, dim) + fwd(x, dim))
#define	db_filep(x)		(x)->os1.ou3.odb_filep
#define	db_lines(x)		(x)->os1.ou3.odb_lines
#define	filter_actual(x)	(x)->os1.ou3.ofilter_actual
#define	db_checksym(x)		filter_actual(x)

#define	cs_type(x)		(x)->os1.ou3.os33.ocs_type
#define	cs_fnum(x)		(x)->os1.ou3.os33.ocs_fnum
#define	cs_pos(x)		(x)->os1.ou3.os33.ocs_pos
#define	cs_lnum(x)		(x)->os1.ou3.os33.ocs_lnum

#define line_count(x)		(x)->os1.ou3.os34.oline_count
#define file_number(x)		(x)->os1.ou3.os34.ofile_number
#define type_of_file(x)		(x)->os1.ou3.os34.otype_of_file
#define used_suffix(x)		(x)->os1.ou3.os34.oused_suffix
#define updated(x)		(x)->os1.ou3.os34.oupdated
#define path(x)			(x)->os1.ou3.os34.opath

#define string(x)		(x)->os1.ostring

#define	save_style(x)		(x)->os2.ou4.osave_style
#define	constraint(x)		(x)->os2.ou4.oconstraint
#define	shift_type(x)		width(space_gap_ref(&save_style(x)))
#define	setShift_type(x, y)		setWidth(space_gap_ref(&save_style(x)), (y))
// #define	setShift_type(x, y)		width(space_gap(save_style(x))) = (y)
#define	shift_gap_ref(x)		line_gap_ref(&save_style(x))

#define actual(x)		(x)->os2.oactual
#define whereto(x)		(x)->os2.oux.owhereto
#define pinpoint(x)		(x)->os2.oux.opinpoint
#define save_mark(x)		(x)->os2.oux.osave_mark
#define ready_galls(x)		(x)->os2a.oready_galls
#define opt_components(x)	(x)->os2a.oopt_components
#define opt_constraints(x)	(x)->os2a.oopt_constraints
#define opt_counts(x)		(x)->os2a.oopt_counts
#define limiter(x)		(x)->os2a.olimiter
#define enclose_obj(x)		(x)->os2a.oenclose_obj
#define headers(x, i)		(x)->os2a.oheaders[i]
#define head_next(x)		(x)->os2a.ohead_next
#define opt_comps_permitted(x)	(x)->os2a.oopt_comps_permitted

#define	number(x)		(x)->os4.onumber
#define	db_targ(x)		(x)->os4.odb_targ

#define	gap(x)			(x)->os5.ogap
#define	save_badness(x)		(x)->os5.osave_badness
#define	save_space(x)		(x)->os5.osave_space
#define	save_actual_gap(x)	(x)->os5.osave_actual_gap
#define	save_prev(x)		(x)->os5.osave_prev
#define	save_cwid(x)		(x)->os5.osave_cwid

#define	enclosing(x)		(x)->os6.oenclosing
#define	sym_body(x)		(x)->os6.osym_body
#define	base_uses(x)		(x)->os6.obase_uses
#define	uses(x)			(x)->os6.ouses
#define	marker(x)		(x)->os6.omarker
#define	cross_sym(x)		(x)->os6.ocross_sym
#define	imports(x)		(x)->os6.oimports
#define	filter(x)		(x)->os6.ofilter
#define	use_invocation(x)	(x)->os6.ouse_invocation
#define	predefined(x)		(x)->os6.opredefined
#define	has_compulsory(x)	(x)->os6.ohas_compulsory
#define	uses_count(x)		(x)->os6.ouses_count
#define	npar_code(x)		(x)->os6.onpar_code
#define	is_optimize(x)		(x)->os6.ois_optimize
#define	has_optimize(x)		(x)->os6.ohas_optimize
#define	is_merge(x)		(x)->os6.ois_merge
#define	has_merge(x)		(x)->os6.ohas_merge
#define	is_enclose(x)		(x)->os6.ois_enclose
#define	has_enclose(x)		(x)->os6.ohas_enclose
#define	is_compulsory(x)	(x)->os6.ois_compulsory

#define	target_state(x)		(x)->os7.otarget_state
#define	target_file(x)		(x)->os7.otarget_file
/* #define cr_file(x)		(x)->os7.ocr_file unused */
#define	target_val(x)		(x)->os7.otarget_val
#define	target_seq(x)		(x)->os7.otarget_seq
#define	target_pos(x)		(x)->os7.otarget_pos
#define	target_lnum(x)		(x)->os7.otarget_lnum
/* #define cr_seq(x)		(x)->os7.ocr_seq unused */
#define	gall_seq(x)		(x)->os7.ogall_seq
#define	symb(x)			(x)->os7.osymb
#define	gall_tag(x)		(x)->os7.ogall_tag
#define	gall_tfile(x)		(x)->os7.ogall_tfile

#define	eg_fnum(x)		(x)->os8.oeg_fnum
#define	eg_fpos(x)		(x)->os8.oeg_fpos
#define	eg_lnum(x)		(x)->os8.oeg_lnum
#define	eg_cont(x)		(x)->os8.oeg_cont
#define	eg_symbol(x)		(x)->os8.oeg_symbol

#define	item(x)			(x)->os9.oitem
#define	next(x)			(x)->os9.onext

#define	font_num(x)		(x)->os1.ou3.os32.ofont_num
#define	font_page(x)		(x)->os1.ou3.os32.ofont_page
#define	font_size(x)		(x)->os1.ou3.os32.ofont_size
#define	font_xheight2(x)	(x)->os1.ou3.os32.ofont_xheight2
#define	font_spacewidth(x)	(x)->os1.ou3.os32.ofont_spacewidth
#define	font_mapping(x)		(x)->os1.ou3.os32.ofont_mapping
#define	font_recoded(x)		(x)->os1.ou3.os32.ofont_recoded

INLINE BOOLEAN2 objectOfType(OBJECT x, OBJTYPE typ) {
  return type(x).objtype == typ.objtype;
}

INLINE BOOLEAN2 sameObjType(OBJTYPE x, OBJTYPE y) {
  return x.objtype == y.objtype;
}

INLINE BOOLEAN2 spaceMode(GAP* x, SPACE_MODE m) {
  return (mode(x).spacemode == m.spacemode);
}

/*@::FONT_INFO@***************************************************************/
/*                                                                           */
/*  typedef FONT_INFO - information about font metrics etc.  Really private  */
/*  but shared between z37.c and z24.c                                       */
/*                                                                           */
/*****************************************************************************/

struct metrics {
  FULL_LENGTH up;
  FULL_LENGTH down;
  FULL_LENGTH left;
  FULL_LENGTH right;
  FULL_LENGTH last_adjust;
};

typedef struct composite_rec {
  FULL_CHAR char_code;
  FULL_LENGTH x_offset;
  FULL_LENGTH y_offset;
} COMPOSITE;

typedef struct font_rec {
  struct metrics	*size_table;		/* metrics of sized fonts    */
  FULL_CHAR		*lig_table;		/* ligatures                 */
  unsigned short	*composite;		/* non-zero means composite  */
  COMPOSITE		*cmp_table;		/* composites to build	     */
  int			cmp_top;		/* length of cmp_table	     */
  OBJECT		font_table;		/* record of sized fonts     */
  OBJECT		original_face;		/* face object of this font  */
  FULL_LENGTH		underline_pos;		/* position of underline     */
  FULL_LENGTH		underline_thick;	/* thickness of underline    */
  unsigned short	*kern_table;		/* first kerning chars       */
  FULL_CHAR		*kern_chars;		/* second kerning chars      */
  unsigned char		*kern_value;		/* points into kern_lengths  */
  FULL_LENGTH		*kern_sizes;		/* sizes of kernings         */
} FONT_INFO;


typedef struct mapvec {
  OBJECT        file_name;              /* name of file containing the vec   */
  FILE_NUM      fnum;                   /* the file number of this file      */
  BOOLEAN2       seen_recoded;           /* TRUE if a font recode was seen    */
  int		last_page_printed;	/* most recent page on which printed */
  OBJECT        name;                   /* PostScript name of encoding vec   */
  OBJECT        vector[MAX_CHARS];      /* character names                   */
  FULL_CHAR     hash_table[MAX_CHASH];  /* character hash table for inverse  */
  FULL_CHAR     map[MAPS][MAX_CHARS];   /* the mappings                      */
} *MAP_VEC;


/*@::BACK_END@****************************************************************/
/*                                                                           */
/*  typedef BACK_END - an OO-like record describing one back end             */
/*                                                                           */
/*****************************************************************************/

typedef struct back_end_rec {
  int code;				/* the code number of the back end   */
  FULL_CHAR *name;			/* string name of the back end	     */
  BOOLEAN2 scale_avail;			/* TRUE if @Scale is available	     */
  BOOLEAN2 rotate_avail;			/* TRUE if @Rotate is available	     */
  BOOLEAN2 mirror_avail;			/* TRUE if @HMirror, @VMirror avail  */
  BOOLEAN2 graphic_avail;		/* TRUE if @Graphic is available     */
  BOOLEAN2 incgraphic_avail;		/* TRUE if @IncludeGraphic is avail. */
  BOOLEAN2 plaingraphic_avail;		/* TRUE if @PlainGraphic is avail.   */
  BOOLEAN2 fractional_spacing_avail;	/* TRUE if fractional spacing avail. */
  BOOLEAN2 uses_font_metrics;		/* TRUE if actual font metrics used  */
  BOOLEAN2 colour_avail;			/* TRUE if colour is available       */
  void (*PrintInitialize)(FILE *fp, BOOLEAN2 encapsulated);
  void (*PrintLength)(FULL_CHAR *buff, int length, DIM_TE length_dim);
  void (*PrintPageSetupForFont)(OBJECT face, int font_curr_page,
    FULL_CHAR *font_name, FULL_CHAR *first_size_str);
  void (*PrintPageResourceForFont)(FULL_CHAR *font_name, BOOLEAN2 first);
  void (*PrintMapping)(MAPPING m);
  void (*PrintBeforeFirstPage)(FULL_LENGTH h, FULL_LENGTH v, FULL_CHAR *label);
  void (*PrintBetweenPages)(FULL_LENGTH h, FULL_LENGTH v, FULL_CHAR *label);
  void (*PrintAfterLastPage)(void);
  void (*PrintWord)(OBJECT x, int hpos, int vpos);
  void (*PrintPlainGraphic)(OBJECT x, FULL_LENGTH xmk,FULL_LENGTH ymk,OBJECT z);
  void (*PrintUnderline)(FONT_NUM fnum, COLOUR_NUM col, TEXTURE_NUM pat,
    FULL_LENGTH xstart, FULL_LENGTH xstop, FULL_LENGTH ymk);
  void (*CoordTranslate)(FULL_LENGTH xdist, FULL_LENGTH ydist);
  void (*CoordRotate)(FULL_LENGTH amount);
  void (*CoordScale)(float hfactor, float vfactor);
  void (*CoordHMirror)(void);
  void (*CoordVMirror)(void);
  void (*SaveGraphicState)(OBJECT x);
  void (*RestoreGraphicState)(void);
  void (*PrintGraphicObject)(OBJECT x);
  void (*DefineGraphicNames)(OBJECT x);
  void (*SaveTranslateDefineSave)(OBJECT x,FULL_LENGTH xdist,FULL_LENGTH ydist);
  void (*PrintGraphicInclude)(OBJECT x,FULL_LENGTH colmark,FULL_LENGTH rowmark);
  void (*LinkSource)(OBJECT name, FULL_LENGTH llx, FULL_LENGTH lly,
    FULL_LENGTH urx, FULL_LENGTH ury);
  void (*LinkDest)(OBJECT name, FULL_LENGTH llx, FULL_LENGTH lly,
    FULL_LENGTH urx, FULL_LENGTH ury);
  void (*LinkURL)(OBJECT url, FULL_LENGTH llx, FULL_LENGTH lly,
    FULL_LENGTH urx, FULL_LENGTH ury);
  void (*LinkCheck)(void);
} *BACK_END;


INLINE BOOLEAN2 is_indefinite(OBJTYPE x) {
    return (x).objtype >= CLOSURE_E && (x).objtype <= HEAD_E;
}
INLINE BOOLEAN2 is_header(OBJTYPE x) {
    return (x).objtype >= BEGIN_HEADER_E && (x).objtype <= CLEAR_HEADER_E;
}
INLINE BOOLEAN2 is_definite(OBJTYPE x) {
    return (x).objtype >= SPLIT_E && (x).objtype <= LINK_URL_E;
}
INLINE BOOLEAN2 is_par(OBJTYPE x) {
    return (x).objtype >= LPAR_E && (x).objtype <= RPAR_E;
}
INLINE BOOLEAN2 is_index(OBJTYPE x) {
    return (x).objtype >= DEAD_E && (x).objtype <= EXPAND_IND_E;
}
INLINE BOOLEAN2 is_type(OBJTYPE x) {
    return (x).objtype >= LINK_E && (x).objtype < DISPOSED_E;
}
INLINE BOOLEAN2 is_word(OBJTYPE x) {
    return (x).objtype == WORD_E || (x).objtype == QWORD_E;
}
INLINE BOOLEAN2 is_cross(OBJTYPE x) {
    return (x).objtype == CROSS_E || (x).objtype == FORCE_CROSS_E;
}
INLINE BOOLEAN2 is_cat_op(OBJTYPE x) {
    return ((x).objtype>=ACAT_E && (x).objtype<=VCAT_E) || (x).objtype==TSPACE_E || (x).objtype<=TJUXTA_E;
}


/*@::miscellaneous constants@*************************************************/
/*                                                                           */
/*  Miscellaneous globally defined constants                                 */
/*                                                                           */
/*****************************************************************************/

/* sides of a mark */
#define	BACK	           160		/* means lies to left of mark        */
#define	ON	           161		/* means lies on mark                */
#define	FWD	           162		/* means lies to right of mark       */

/* constraint statuses */
#define	PROMOTE	           163		/* this component may be promoted    */
#define	CLOSE	           164		/* must close dest before promoting  */
#define	BLOCK	           165		/* cannot promote this component     */
#define	CLEAR	           166		/* this constraint is now satisfied  */

/* gap increment types */
#define	GAP_ABS	           167		/* absolute,  e.g.  3p               */
#define	GAP_INC	           168		/* increment, e.g. +3p               */
#define	GAP_DEC	           169		/* decrement, e.g. -3p               */

/* statuses of thread objects */
// TODO
#define	NOTSIZED	     DUMMY		/* this thread object is not sized   */
#define	SIZED		     DUMMY1		/* thread is sized but not printed   */
#define	FINALSIZE	     DUMMY2		/* thread object size is now final   */

 
/* units of distance as multiples of the basic unit */
// #define UNIT_TYPE float
#define	CM	  (72*20/2.54)		/* 1 centimetre                      */
#define	IN	          1440		/* 1 inch                            */
#define	EM	           120		/* 1 em (= 1/12 inch)                */
#define	PT		    20		/* 1 point (= 1/72 inch)             */
#define	FR	          4096		/* virtual unit for frame units      */
#define	DG	           128		/* virtual unit for degrees          */
#ifdef ALT_SCALE_FACTOR_SHIFT
#define	SF (1 << ALT_SCALE_FACTOR_SHIFT) /* virtual unit for @Scale factors  */
#else
#define	SF	           256		/* virtual unit for @Scale factors   */
#endif
                                        /* including blankline scale         */

/* default size of characters for the PLAINTEXT back end */
#define	PLAIN_WIDTH        144		/* default char width, 10 per inch   */
#define	PLAIN_HEIGHT       240		/* default char height, 6 per inch   */

/* precedences */
#define	NO_PREC		     0		/* lower than any precedence         */
#define	BEGIN_PREC	     1		/* precedence of @Begin              */
#define	END_PREC	     2		/* precedence of @End                */
#define	LBR_PREC	     3		/* precedence of {                   */
#define	RBR_PREC	     4		/* precedence of }                   */
#define	VCAT_PREC	     5		/* precedence of /                   */
#define	HCAT_PREC	     6		/* precedence of |                   */
#define	ACAT_PREC	     7		/* precedence of & and white space   */
#define	MIN_PREC            10		/* minimum precedence of user ops    */
#define	MAX_PREC           100		/* maximim precedence of user ops    */
#define	DEFAULT_PREC       100		/* default precedence of user ops    */
#define CROSSOP_PREC       101		/* precedence of && and &&& ops      */
#define GAP_PREC           102		/* precedence of gap op after cat op */
#define JUXTA_PREC         103		/* precedence of juxtaposition &     */
#define	FILTER_PREC        104		/* precedence of filter symbol ops   */
#define	FORCE_PREC         105		/* higher than any precedence        */

/*@::Keywords@****************************************************************/
/*                                                                           */
/*  Keywords.                                                                */
/*                                                                           */
/*****************************************************************************/

extern const FULL_CHAR* const KW_START;
extern const FULL_CHAR* const KW_PRINT;
extern const FULL_CHAR* const KW_OPTGALL;
extern const FULL_CHAR* const KW_DEF;
extern const FULL_CHAR* const KW_FONTDEF;
extern const FULL_CHAR* const KW_FAMILY;
extern const FULL_CHAR* const KW_FACE;
extern const FULL_CHAR* const KW_NAME;
extern const FULL_CHAR* const KW_METRICS;
extern const FULL_CHAR* const KW_EXTRA_METRICS;
extern const FULL_CHAR* const KW_MAPPING;
extern const FULL_CHAR* const KW_RECODE;
extern const FULL_CHAR* const KW_LANGDEF;
extern const FULL_CHAR* const KW_FORCE;
extern const FULL_CHAR* const KW_HORIZ;
extern const FULL_CHAR* const KW_INTO;
extern const FULL_CHAR* const KW_EXTEND;
extern const FULL_CHAR* const KW_IMPORT;
extern const FULL_CHAR* const KW_EXPORT;
extern const FULL_CHAR* const KW_PRECEDENCE;
extern const FULL_CHAR* const KW_ASSOC;
extern const FULL_CHAR* const KW_LEFT;
extern const FULL_CHAR* const KW_RIGHT;
extern const FULL_CHAR* const KW_BODY;
extern const FULL_CHAR* const KW_FILTER;
extern const FULL_CHAR* const KW_FILTERIN;
extern const FULL_CHAR* const KW_FILTEROUT;
extern const FULL_CHAR* const KW_FILTERERR;
extern const FULL_CHAR* const KW_MACRO;
extern const FULL_CHAR* const KW_NAMED;
extern const FULL_CHAR* const KW_COMPULSORY;
extern const FULL_CHAR* const KW_COMMON;
extern const FULL_CHAR* const KW_RUMP;
extern const FULL_CHAR* const KW_MELD;
extern const FULL_CHAR* const KW_INSERT;
extern const FULL_CHAR* const KW_ONE_OF;
extern const FULL_CHAR* const KW_NEXT;
extern const FULL_CHAR* const KW_PLUS;
extern const FULL_CHAR* const KW_MINUS;
extern const FULL_CHAR* const KW_WIDE;
extern const FULL_CHAR* const KW_HIGH;
extern const FULL_CHAR* const KW_HSHIFT;
extern const FULL_CHAR* const KW_VSHIFT;
extern const FULL_CHAR* const KW_BEGIN_HEADER;
extern const FULL_CHAR* const KW_END_HEADER;
extern const FULL_CHAR* const KW_SET_HEADER;
extern const FULL_CHAR* const KW_CLEAR_HEADER;
extern const FULL_CHAR* const KW_ONE_COL;
extern const FULL_CHAR* const KW_ONE_ROW;
extern const FULL_CHAR* const KW_HMIRROR;
extern const FULL_CHAR* const KW_VMIRROR;
extern const FULL_CHAR* const KW_HSCALE;
extern const FULL_CHAR* const KW_VSCALE;
extern const FULL_CHAR* const KW_HCOVER;
extern const FULL_CHAR* const KW_VCOVER;
extern const FULL_CHAR* const KW_SCALE;
extern const FULL_CHAR* const KW_KERN_SHRINK;
extern const FULL_CHAR* const KW_HCONTRACT;
extern const FULL_CHAR* const KW_VCONTRACT;
extern const FULL_CHAR* const KW_HLIMITED;
extern const FULL_CHAR* const KW_VLIMITED;
extern const FULL_CHAR* const KW_HEXPAND;
extern const FULL_CHAR* const KW_VEXPAND;
extern const FULL_CHAR* const KW_STARTHVSPAN;
extern const FULL_CHAR* const KW_STARTHSPAN;
extern const FULL_CHAR* const KW_STARTVSPAN;
extern const FULL_CHAR* const KW_HSPAN;
extern const FULL_CHAR* const KW_VSPAN;
extern const FULL_CHAR* const KW_PADJUST;
extern const FULL_CHAR* const KW_HADJUST;
extern const FULL_CHAR* const KW_VADJUST;
extern const FULL_CHAR* const KW_ROTATE;
extern const FULL_CHAR* const KW_BACKGROUND;
extern const FULL_CHAR* const KW_INCGRAPHIC;
extern const FULL_CHAR* const KW_SINCGRAPHIC;
extern const FULL_CHAR* const KW_GRAPHIC;
extern const FULL_CHAR* const KW_LINK_SOURCE;
extern const FULL_CHAR* const KW_LINK_DEST;
extern const FULL_CHAR* const KW_LINK_URL;
extern const FULL_CHAR* const KW_PLAINGRAPHIC;
extern const FULL_CHAR* const KW_VERBATIM;
extern const FULL_CHAR* const KW_RAWVERBATIM;
extern const FULL_CHAR* const KW_CASE;
extern const FULL_CHAR* const KW_YIELD;
extern const FULL_CHAR* const KW_BACKEND;
extern const FULL_CHAR* const KW_XCHAR;
extern const FULL_CHAR* const KW_FONT;
extern const FULL_CHAR* const KW_SPACE;
extern const FULL_CHAR* const KW_YUNIT;
extern const FULL_CHAR* const KW_ZUNIT;
extern const FULL_CHAR* const KW_BREAK;
extern const FULL_CHAR* const KW_UNDERLINE;
extern const FULL_CHAR* const KW_COLOUR;
extern const FULL_CHAR* const KW_COLOR;
extern const FULL_CHAR* const KW_UNDERLINE_COLOUR;
extern const FULL_CHAR* const KW_UNDERLINE_COLOR;
extern const FULL_CHAR* const KW_TEXTURE;
extern const FULL_CHAR* const KW_OUTLINE;
extern const FULL_CHAR* const KW_LANGUAGE;
extern const FULL_CHAR* const KW_CURR_LANG;
extern const FULL_CHAR* const KW_CURR_FAMILY;
extern const FULL_CHAR* const KW_CURR_FACE;
extern const FULL_CHAR* const KW_CURR_YUNIT;
extern const FULL_CHAR* const KW_CURR_ZUNIT;
extern const FULL_CHAR* const KW_ENV;
extern const FULL_CHAR* const KW_ENVA;
extern const FULL_CHAR* const KW_ENVB;
extern const FULL_CHAR* const KW_ENVC;
extern const FULL_CHAR* const KW_ENVD;
extern const FULL_CHAR* const KW_CENV;
extern const FULL_CHAR* const KW_CLOS;
extern const FULL_CHAR* const KW_LVIS;
extern const FULL_CHAR* const KW_LUSE;
extern const FULL_CHAR* const KW_LEO;
extern const FULL_CHAR* const KW_OPEN;
extern const FULL_CHAR* const KW_USE;
extern const FULL_CHAR* const KW_NOT_REVEALED;
extern const FULL_CHAR* const KW_TAGGED;
extern const FULL_CHAR* const KW_DATABASE;
extern const FULL_CHAR* const KW_SYSDATABASE;
extern const FULL_CHAR* const KW_INCLUDE;
extern const FULL_CHAR* const KW_SYSINCLUDE;
extern const FULL_CHAR* const KW_INCG_REPEATED;
extern const FULL_CHAR* const KW_SINCG_REPEATED;
extern const FULL_CHAR* const KW_PREPEND;
extern const FULL_CHAR* const KW_SYSPREPEND;
extern const FULL_CHAR* const KW_TARGET;
extern const FULL_CHAR* const KW_FOLLOWING;
extern const FULL_CHAR* const KW_PRECEDING;
extern const FULL_CHAR* const KW_FOLL_OR_PREC;
extern const FULL_CHAR* const KW_NOW;
extern const FULL_CHAR* const KW_NULL;
extern const FULL_CHAR* const KW_PAGE_LABEL;
extern const FULL_CHAR* const KW_GALLEY;
extern const FULL_CHAR* const KW_FORCE_GALLEY;
extern const FULL_CHAR* const KW_INPUT;
extern const FULL_CHAR* const KW_SPLIT;
extern const FULL_CHAR* const KW_TAG;
extern const FULL_CHAR* const KW_KEY;
extern const FULL_CHAR* const KW_OPTIMIZE;
extern const FULL_CHAR* const KW_MERGE;
extern const FULL_CHAR* const KW_ENCLOSE;
extern const FULL_CHAR* const KW_CROSS;
extern const FULL_CHAR* const KW_FORCE_CROSS;
extern const FULL_CHAR* const KW_LBR;
extern const FULL_CHAR* const KW_RBR;
extern const FULL_CHAR* const KW_BEGIN;
extern const FULL_CHAR* const KW_END;
extern const FULL_CHAR* const KW_VCAT_NN;
extern const FULL_CHAR* const KW_VCAT_MN;
extern const FULL_CHAR* const KW_VCAT_NJ;
extern const FULL_CHAR* const KW_VCAT_MJ;
extern const FULL_CHAR* const KW_HCAT_NN;
extern const FULL_CHAR* const KW_HCAT_MN;
extern const FULL_CHAR* const KW_HCAT_NJ;
extern const FULL_CHAR* const KW_HCAT_MJ;
extern const FULL_CHAR* const KW_ACAT_NJ;
extern const FULL_CHAR* const KW_ACAT_MJ;
extern const FULL_CHAR* const KW_MOMENT;
extern const FULL_CHAR* const KW_SECOND;
extern const FULL_CHAR* const KW_MINUTE;
extern const FULL_CHAR* const KW_HOUR;
extern const FULL_CHAR* const KW_DAY;
extern const FULL_CHAR* const KW_MONTH;
extern const FULL_CHAR* const KW_YEAR;
extern const FULL_CHAR* const KW_CENTURY;
extern const FULL_CHAR* const KW_WEEKDAY;
extern const FULL_CHAR* const KW_YEARDAY;
extern const FULL_CHAR* const KW_DAYLIGHTSAVING;
extern const FULL_CHAR* const KW_SET_CONTEXT;
extern const FULL_CHAR* const KW_GET_CONTEXT;

/*@::GetMem(), New(), NewWord()@**********************************************/
/*                                                                           */
/*  GetMem(x, siz, pos)                                                      */
/*  New(x, typ)                                                              */
/*  NewWord(x, typ, len, pos)                                                */
/*                                                                           */
/*  Set x to point to a new record, of appropriate length (in ALIGNs).       */
/*  The New and NewWord versions initialise LIST, type and rec_size fields.  */
/*  NewWord must be used for WORD and QWORD objects.                         */
/*                                                                           */
/*****************************************************************************/

/*@::Memory alllocation@******************************************************/
/*                                                                           */
/* USE_SYSTEM_MALLOC    Use the system malloc/free instead of lout's         */
/*                      built-in allocator. It can be useful for debugging   */
/*                      memory errors with tools like valgrind. Using the    */
/*                      system malloc/free can double the lout run time.     */
/*                                                                           */
/* USE_MALLOC_DEBUG     Add additional memory debugging that tracks the      */
/*                      size, type and allocation point of each object.      */
/*****************************************************************************/

/*****  z31.c     Memory Allocator      **************************************/
extern  void      DebugRegisterUsage(MEM_TE typ, int delta_num, int delta_size);
extern  void      DebugMemory(void);
extern  void      MemInit(void);
extern  OBJECT    GetMemory(int siz, FILE_POS *pos);
extern  OBJECT    zz_free[];
extern  unsigned char   zz_lengths[];
extern  int       zz_newcount;
extern  int       zz_disposecount;
extern  int       zz_listcount;
extern  OBJECT    zz_hold;
extern  OBJECT    zz_tmp;
extern  OBJECT    zz_res;
extern  int       zz_size;
extern  OBJECT    xx_link, xx_tmp;
extern  OBJECT    xx_hold, xx_res;

// from z01 headers below - but used here
extern	POINTER	  MemCheck;
// from z26 headers below - but used here
extern	const FULL_CHAR *Image(OBJTYPE c);
extern	const FULL_CHAR *Image4Constraints(int c);

#define	USE_SYSTEM_MALLOC	0
#define	USE_MALLOC_DEBUG	0

// defined in z31.c
/*
extern OBJECT		zz_free[], zz_hold, zz_tmp, zz_res;
extern int		zz_size;
extern unsigned char	zz_lengths[];		/ DISPOSED is 1 + max type /
extern OBJECT 		xx_link, xx_tmp, xx_res, xx_hold;
*/

#if DEBUG_ON

// defined in z31.c if DEBUG_ON
extern int	zz_newcount;	/* number of calls to New()          */
extern int	zz_disposecount;	/* number of calls to Dispose()      */
extern int	zz_listcount;	/* number of elements in zz_free[]   */

#define newcount zz_newcount++
#define freecount zz_listcount--

#define checknew(typ)							\
{ assert1( is_type(typ), "New: type", Image(typ) );			\
  assert(  zz_lengths[typ.objtype] > 0, "New: zero length!" );			\
}

#define checkmem(z, typ)						\
{ if( (MemCheck != 0) && ( (POINTER) z == MemCheck) )			\
    fprintf(stderr, "%ld = New(%s)%s",(long)z,Image(type(z)),STR_NEWLINE); \
}

#else
#define newcount
#define freecount
#define checknew(typ)
#define checkmem(z, typ)
#endif

#if USE_MALLOC_DEBUG

/* Add a header and trailer */
/* The header includes the allocation point which can help identify */
/* where an object needed to be initialized. */

typedef struct
{ short otype;				/* object type                  */
  short orec_size;			/* object record size in ALIGNS */
  const char *oalloc_file_name;		/* C file that called New       */
  int oalloc_line_num;			/* line number of call          */
} MALLOC_HEADER;

#define	MALLOC_HEADER_SIZE		(ceiling(sizeof(MALLOC_HEADER), sizeof(ALIGN)))

typedef struct
{ short osentinel;			/* sentinel value */
} MALLOC_TRAILER;

#define MALLOC_SENTINEL			0x1e87	/* randomly-selected value to check for overwrites */

#define MALLOC_TRAILER_SIZE		(ceiling(sizeof(MALLOC_TRAILER), sizeof(ALIGN)))

#define malloc_oheader(x)		((MALLOC_HEADER *)(((ALIGN *)(x)) - MALLOC_HEADER_SIZE))
#define	malloc_otype(x)			(malloc_oheader(x)->otype)
#define malloc_orec_size(x)		(malloc_oheader(x)->orec_size)
#define malloc_oalloc_file_name(x)	(malloc_oheader(x)->oalloc_file_name)
#define malloc_oalloc_line_num(x)	(malloc_oheader(x)->oalloc_line_num)

#define malloc_otrailer(x)		((MALLOC_TRAILER *)(((ALIGN *)(x)) + malloc_orec_size(x)))
#define malloc_osentinel(x)		(malloc_otrailer(x)->osentinel)

#define	setmemtype(x,typ)		malloc_otype(x) = (typ);

#define mallocheadercheck(x,size)					\
{ if (size != malloc_orec_size(x)) fprintf(stderr, "putmem, siz %d != allocated %d\n", size, malloc_orec_size(x));	\
  if (type(x) != malloc_otype(x)) fprintf(stderr, "putmem, typ %d != orig %d\n", type(x), malloc_otype(x)); 		\
  if (malloc_osentinel(x) != MALLOC_SENTINEL) fprintf(stderr, "putmem, invalid sentinel %x\n", malloc_osentinel(x));	\
}

#define	mallocsetfile(x)						\
{ if (x != NULL)							\
  { malloc_oalloc_file_name(x) = __FILE__;				\
    malloc_oalloc_line_num(x) = __LINE__;				\
  }									\
}

#else

#define setmemtype(x,typ)
#define mallocheadercheck(x,size)
#define	mallocsetfile(x)
#define malloc_oalloc_file_name(x)					""
#define malloc_oalloc_line_num(x)					0

#endif

/* GetMem does not initialize objects that come from the free list.          */
/* Clearing the object with memset() adds 30% to the lout run time.          */
/* Callers of New should initialize everything necessary.                    */

INLINE OBJECT GetMem(OBJECT x, size_t siz, FILE_POS* pos) {
  newcount;
  if( (zz_size=(siz)) >= MAX_OBJECT_REC )
    x = NULL, Error(1, 1, "word is too long", FATAL, pos);
  else if( zz_free[zz_size] == nilobj )
    x = GetMemory(zz_size, pos);
  else
  { x = zz_free[zz_size];
    freecount;
    zz_free[zz_size] = pred(x, CHILD);
  }
  mallocsetfile(x);
  return x;
}

#define New(x, typ) (x) = returnNew((x), (typ))

#pragma clang diagnostic ignored "-Wuninitialized"
INLINE OBJECT returnNew(OBJECT x, OBJTYPE typ) {
  checknew(typ);
  zz_hold = GetMem(zz_hold, zz_lengths[typ.objtype], no_fpos);
  setType(zz_hold, typ);
  setmemtype(zz_hold, typ);
  mallocheadercheck(zz_hold,zz_lengths[typ]);
  checkmem(zz_hold, typ);
  setSucc(zz_hold, PARENT, zz_hold);
  setPred(zz_hold, PARENT, zz_hold);
  setSucc(zz_hold, CHILD, zz_hold);
  setPred(zz_hold, CHILD, zz_hold);
  x = zz_hold;
  assert(objectOfType(x, typ), "returnNew: created object has unexpected token type");
  return x;
}

INLINE OBJECT NewWord(OBJECT x, OBJTYPE typ, size_t len, FILE_POS* pos) {
  zz_size = sizeof(struct word_type) - 4 + ((len)+1)*sizeof(FULL_CHAR);
  /* NB the following line RESETS zz_size */
  zz_hold = GetMem(zz_hold, ceiling(zz_size, sizeof(ALIGN)), pos);
  checkmem(zz_hold, typ);
  rec_size(zz_hold) = zz_size;
  setmemtype(zz_hold, typ);
  setType(zz_hold, typ);
  mallocheadercheck(zz_hold,zz_size);
  setSucc(zz_hold, PARENT, zz_hold);
  setPred(zz_hold, PARENT, zz_hold);
  setSucc(zz_hold, CHILD, zz_hold);
  setPred(zz_hold, CHILD, zz_hold);
  x = zz_hold;
  assert(objectOfType(x, typ), "NewWord: created object has unexpected token type");
  return x;
}

/*@::PutMem(), Dispose()@*****************************************************/
/*                                                                           */
/*  PutMem(x, siz)                                                           */
/*  Dispose(x)                                                               */
/*                                                                           */
/*  Dispose x, which is of size siz.  Dispose works out the size itself.     */
/*                                                                           */
/*****************************************************************************/
#if DEBUG_ON
// #define disposecount zz_disposecount++; zz_listcount++;
INLINE void disposecount(void) {
    zz_disposecount++;
    zz_listcount++;
}

/*
#define disposecheck							\
{ assert( zz_size >= 0 && zz_size < MAX_OBJECT_REC, "Dispose: size" );	\
}
*/
INLINE void disposecheck(void) {
    assert( zz_size >= 0 && zz_size < MAX_OBJECT_REC, "Dispose: size" );
}

/*
#define	setdisposed							\
{ if( (MemCheck != 0) && ((POINTER) zz_hold == MemCheck) )		\
    fprintf(stderr, "Dispose(%ld, %s)%s", (long) zz_hold,		\
      Image(type(zz_hold)), STR_NEWLINE);				\
  type(zz_hold) = DISPOSED;						\
}
*/
INLINE void setdisposed(void) {
    if( (MemCheck != 0) && ((POINTER) zz_hold == MemCheck) )
        fprintf(stderr, "Dispose(%ld, %s)%s", (long) zz_hold,
            Image(type(zz_hold)), STR_NEWLINE);
    setType(zz_hold, DISPOSED);
}

#else
/*
#define disposecount
#define disposecheck()
#define	setdisposed()
*/
INLINE void disposecount(void) {
}

INLINE void disposecheck(void) {
}

INLINE void setdisposed(void) {
}

#endif

#if USE_SYSTEM_MALLOC

#if USE_MALLOC_DEBUG

/*
#define	PutMem(x, siz)							\
{ disposecount;								\
  zz_hold = (x);							\
  zz_size = (siz);							\
  mallocheadercheck(zz_hold,zz_size);					\
  free( malloc_oheader(x) );						\
}
*/
INLINE void PutMem(POINTER x, int siz) {
    disposecount();
    zz_hold = (x);
    zz_size = (siz);
    mallocheadercheck(zz_hold,zz_size);
    free( malloc_oheader(x) );
}

/*
#define Dispose(x)							\
{ zz_hold = (x);							\
  PutMem(zz_hold, is_word(type(zz_hold)) ?				\
    rec_size(zz_hold) : zz_lengths[type(zz_hold)]);			\
}
*/
INLINE void Dispose(POINTER x) {
    zz_hold = (x);
    PutMem(zz_hold, is_word(type(zz_hold)) ?
        rec_size(zz_hold) : zz_lengths[type(zz_hold)]);
}

#else

/*
#define	PutMem(x, siz)							\
{ disposecount;								\
  free( (x) );								\
}
*/
#pragma clang diagnostic ignored "-Wunused-parameter"
INLINE void PutMem(POINTER x , int size) {
    disposecount();
    free( (x) );
}

/*
#define	Dispose(x)							\
{ zz_hold = (x);							\
  setdisposed;								\
  PutMem(zz_hold,0);							\
}
*/
INLINE void Dispose(POINTER x) {
    zz_hold = (x);
    setdisposed();
    PutMem(zz_hold, 0);
}

#endif

#else

INLINE void PutMem(POINTER x, int size) {
    disposecount();
    zz_hold = (x);
    zz_size = (size);
    mallocheadercheck(zz_hold,zz_size);
    disposecheck();
    setPred(zz_hold, CHILD, zz_free[zz_size]);
    zz_free[zz_size] = zz_hold;
}

INLINE void Dispose(OBJECT x) {
    zz_hold = (x);
    PutMem(zz_hold, is_word(type(zz_hold)) ?
        rec_size(zz_hold) : zz_lengths[type(zz_hold).objtype]);
    setdisposed();
}

#endif

/*@::Append(), Delete()@******************************************************/
/*                                                                           */
/*  OBJECT Append(x, y, dir)                                                 */
/*                                                                           */
/*  Return the append of lists x and y (dir is PARENT or CHILD).             */
/*                                                                           */
/*****************************************************************************/

INLINE OBJECT Append(OBJECT x, OBJECT y, DIR_TE dir) {
    return zz_res = (x),
    zz_hold = (y),
    zz_hold == nilobj ? zz_res  : 
        zz_res == nilobj ? zz_hold : 
            ( zz_tmp = pred(zz_hold, dir),
            setPred(zz_hold, dir, pred(zz_res, dir)),
            setSucc(pred(zz_res, dir), dir, zz_hold),
            setPred(zz_res, dir, zz_tmp),
            setSucc(zz_tmp, dir, zz_res)
            );
}


/*****************************************************************************/
/*                                                                           */
/*  OBJECT Delete(x, dir)                                                    */
/*                                                                           */
/*  Delete x from its dir list, and return succ(x, dir) or nilobj if none.   */
/*                                                                           */
/*****************************************************************************/

INLINE OBJECT Delete(OBJECT x, DIR_TE dir) {
    return zz_hold = (x),
    succ(zz_hold, dir) == zz_hold ? nilobj :
        ( zz_res = succ(zz_hold, dir),
        setPred(zz_res, dir, pred(zz_hold, dir)),
        setSucc(pred(zz_hold, dir), dir, zz_res),
        setSucc(zz_hold, dir, zz_hold),
        setPred(zz_hold, dir, zz_hold),
        zz_res
        );
}

#define Down(x)		succ(x, CHILD)
#define NextDown(x)	succ(x, CHILD)
#define LastDown(x)	pred(x, CHILD)
#define PrevDown(x)	pred(x, CHILD)
#define	Up(x)		succ(x, PARENT)
#define	NextUp(x)	succ(x, PARENT)
#define	LastUp(x)	pred(x, PARENT)
#define	PrevUp(x)	pred(x, PARENT)

INLINE void Child(OBJECT* y, OBJECT link) {
  for( *y = pred(link, PARENT);  objectOfType(*y, LINK);  *y = pred(*y, PARENT) )
  ;
}

// cannot inline
#define CountChild(y, link, i)                                          \
for( y=pred(link, PARENT), *i = 1; objectOfType(y, LINK);  y = pred(y, PARENT), (*i)++ ) \
;
/*
INLINE void CountChild(OBJECT y, OBJECT link, unsigned *i) {
  for( y=pred(link, PARENT), *i = 1; objectOfType(y, LINK);  y = pred(y, PARENT), (*i)++ )
  ;
}
*/

// cannot inline
#define	Parent(y, link)							\
for( y = pred(link, CHILD);   objectOfType(y, LINK);  y = pred(y, CHILD) ) \
;
/*
INLINE void Parent(OBJECT y, OBJECT link) {
  for( y = pred(link, CHILD);   objectOfType(y, LINK);  y = pred(y, CHILD) ) \
  ;
}
*/


/*@::UpDim(), DownDim(), Link(), DeleteLink(), etc.@**************************/
/*                                                                           */
/*  UpDim(x, dim)                                                            */
/*  DownDim(x, dim)                                                          */
/*                                                                           */
/*  Returns the dim child or parent link of node x (dim == COLM or ROWM).    */
/*                                                                           */
/*****************************************************************************/

// #define UpDim(x, dim)	( sameDim(dim, COLM) ? succ(x, PARENT) : pred(x, PARENT) )
INLINE OBJECT UpDim(OBJECT x, DIM_TE dim) {
  return sameDim(dim, COLM) ? succ(x, PARENT) : pred(x, PARENT);
}
// #define DownDim(x, dim)	( sameDim(dim, COLM) ? succ(x, CHILD) : pred(x, CHILD) )
INLINE OBJECT DownDim(OBJECT x, DIM_TE dim) {
  return sameDim(dim, COLM) ? succ(x, CHILD) : pred(x, CHILD);
}

/*****************************************************************************/
/*                                                                           */
/*  OBJECT Link(x, y)                                                        */
/*                                                                           */
/*  Make y a child of x in the directed graph, using a new link.             */
/*  The link node is returned.                                               */
/*                                                                           */
/*****************************************************************************/

// from c07 headers below - but used here
extern	BOOLEAN2	  SplitIsDefinite(OBJECT x);
extern	int	  DisposeObject(OBJECT x);

INLINE OBJECT Link(OBJECT x, OBJECT y) {
    OBJECT xx_link;
    New(xx_link, LINK);
    Append(xx_link, (x), CHILD);
    return Append(xx_link, (y), PARENT);
}

/*****************************************************************************/
/*                                                                           */
/*  DeleteLink(link)                                                         */
/*                                                                           */
/*  Cut the link between nodes x and y of the directed graph.                */
/*  Returns the link node of the next child of x, or x if none.              */
/*                                                                           */
/*****************************************************************************/

INLINE void DeleteLink(OBJECT link) {
    OBJECT xx_link = (link);
    Delete(xx_link, PARENT);
    Delete(xx_link, CHILD);
    Dispose(xx_link);
}

/*****************************************************************************/
/*                                                                           */
/*  DisposeChild(link)                                                       */
/*                                                                           */
/*  Delete link, and if its child is thereby unattached, dispose it.         */
/*                                                                           */
/*****************************************************************************/

INLINE void DisposeChild(OBJECT link) {
    OBJECT xx_link = (link);
    OBJECT xx_tmp = Delete(xx_link, PARENT);
    Delete(xx_link, CHILD);
    Dispose(xx_link);
    if( succ(xx_tmp, PARENT) == xx_tmp )  DisposeObject(xx_tmp);
}

/*****************************************************************************/
/*                                                                           */
/*  MoveLink(link, x, dir)                                                   */
/*                                                                           */
/*  Move the dir end of link from wherever it is now to node x.              */
/*                                                                           */
/*****************************************************************************/

INLINE OBJECT MoveLink(OBJECT link, OBJECT x, DIR_TE dir) {
    OBJECT xx_link = (link);
    DIR_TE other = otherDir(dir);
    Delete(xx_link, other );
    return Append(xx_link, (x), other );
}

/*@::TransferLinks(), DeleteNode(), etc.@*************************************/
/*                                                                           */
/*  TransferLinks(start_link, stop_link, dest_link)                          */
/*                                                                           */
/*  Move parent end of links start_link (inclusive) to stop_link (exclusive) */
/*  to just before dest_link.                                                */
/*                                                                           */
/*****************************************************************************/

INLINE void TransferLinks(OBJECT start_link, OBJECT stop_link, OBJECT dest_link) {
    OBJECT xxstart = start_link, xxstop = stop_link, xxdest = dest_link;
    if( xxstart != xxstop )
    {
        assert( objectOfType(xxstart, LINK), "TransferLinks: start_link!" );	\
        Append(xxstart, xxstop, CHILD); /* actually a split */
        Append(xxstart, xxdest, CHILD);
    }
}

/*****************************************************************************/
/*                                                                           */
/*  DeleteNode(x)                                                            */
/*                                                                           */
/*  Delete node x and every edge attaching to x.                             */
/*                                                                           */
/*****************************************************************************/

INLINE void DeleteNode(OBJECT x) {
    OBJECT xx_hold = (x);
    while( Up(xx_hold) != xx_hold ) DeleteLink( Up(xx_hold) );
    while( Down(xx_hold) != xx_hold ) DeleteLink( Down(xx_hold) );
    Dispose(xx_hold);
}

/*****************************************************************************/
/*                                                                           */
/*  MergeNode(x, y)                                                          */
/*                                                                           */
/*  Take all the children of y and make them children of x.                  */
/*  Take all the parents of y and make them parents of x.  Dispose y.        */
/*                                                                           */
/*****************************************************************************/

INLINE void MergeNode(OBJECT x, OBJECT y) {
    OBJECT xx_res = (x);
    OBJECT xx_hold = (y);
    OBJECT xx_tmp = Delete(xx_hold, PARENT);
    Append(xx_res, xx_tmp, PARENT);
    xx_tmp = Delete(xx_hold, CHILD);
    Append(xx_res, xx_tmp, CHILD);
    Dispose(xx_hold);
}

/*****************************************************************************/
/*                                                                           */
/*  ReplaceNode(x, y)                                                        */
/*                                                                           */
/*  Move all the parent links of y to x.                                     */
/*                                                                           */
/*****************************************************************************/

INLINE void ReplaceNode(OBJECT x, OBJECT y) {
    OBJECT xx_tmp = Delete((y), PARENT);
    Append((x), xx_tmp, PARENT);
}

/*@::FirstDefinite(), NextDefinite(), etc.@***********************************/
/*                                                                           */
/*  FirstDefinite(x, link, y, jn)                                            */
/*                                                                           */
/*  On input, x is an object and link and y are undefined.  On output there  */
/*  are two cases:                                                           */
/*                                                                           */
/*  link != x.  Then y is first definite child of x and link is its link;    */
/*              jn is TRUE iff all gaps on the way to link were joined.      */
/*                                                                           */
/*  link == x.  Then x has no definite child and y is undefined.             */
/*                                                                           */
/*  A SPLIT object is considered to be definite if both its children are     */
/*  definite.  This condition is returned by SplitIsDefinite.                */
/*                                                                           */
/*****************************************************************************/

// cannot inline
#define FirstDefinite(x, link, y, jn)					\
{ jn = TRUE;								\
  for( link = Down(x);  link != x;  link = NextDown(link) )		\
  { Child(&y, link);							\
    if( objectOfType(y, GAP_OBJ) )  jn = jn && join(&gap(y));			\
    else if( objectOfType(y, SPLIT) ? SplitIsDefinite(y) : is_definite(type(y)))\
      break;								\
  }									\
} /* end FirstDefinite */


/*****************************************************************************/
/*                                                                           */
/*  NextDefinite(x, link, y)                                                 */
/*                                                                           */
/*  On input, x is an object and link is a link to one of its children; y    */
/*  is undefined.  On output there are two cases:                            */
/*                                                                           */
/*  link != x.  Then y is the first definite child of x following link, and  */
/*              link is changed to be the link of y.                         */
/*                                                                           */
/*  link == x.  Then x has no definite child following link, and y remains   */
/*              undefined.                                                   */
/*                                                                           */
/*****************************************************************************/

/*
#define NextDefinite(x, link, y)					\
{ for( *link = NextDown(*link);  *link != *x;  *link = NextDown(*link) )	\
  { Child(*y, *link);							\
    if( objectOfType(*y, SPLIT) ? SplitIsDefinite(*y) : is_definite(type(*y)) )	\
	break;								\
  }									\
} */ /* end NextDefinite */

INLINE void NextDefinite(OBJECT* x, OBJECT* link, OBJECT* y) {
    for( *link = NextDown(*link);  *link != *x;  *link = NextDown(*link) )
    {
        Child(y, *link);
        if( objectOfType(*y, SPLIT) ? SplitIsDefinite(*y) : is_definite(type(*y)) )
            break;
    }
}

/*****************************************************************************/
/*                                                                           */
/*  NextDefiniteWithGap(x, link, y, g, jn)                                   */
/*                                                                           */
/*  On input, x is an object and link is a link to one of its children; y    */
/*  and g are undefined.  On output there are two cases:                     */
/*                                                                           */
/*  link != x.  Then y is the first definite child of x following link, and  */
/*              link is changed to be the link of y.  Also, g is defined     */
/*              to be the gap just before y; this must exist and is tested   */
/*              by an assert test; and jn is true iff all of the gaps on     */
/*              the way from old link to new link are join gaps.             */
/*                                                                           */
/*  link == x.  Then x has no definite child following link, and y and g     */
/*              remain undefined.                                            */
/*                                                                           */
/*****************************************************************************/

// cannot inline
#define NextDefiniteWithGap(x, link, y, g, jn)				\
{ g = nilobj;  jn = TRUE;						\
  for( link = NextDown(link);  link != x;  link = NextDown(link) )	\
  { Child(&y, link);							\
    if( objectOfType(y, GAP_OBJ) )  g = y, jn = jn && join(&gap(y));		\
    else if( objectOfType(y, SPLIT) ? SplitIsDefinite(y):is_definite(type(y)) )	\
    {									\
      debug2(DFS, DD, "  NextDefiniteWithGap at %s %s",			\
	Image(type(y)), EchoObject(y));					\
      assert( g != nilobj, "NextDefiniteWithGap: g == nilobj!" );	\
      break;								\
    }									\
  }									\
} /* end NextDefiniteWithGap */

/*@@**************************************************************************/
/*                                                                           */
/*  LastDefinite(x, link, y)                                                 */
/*                                                                           */
/*  On input, x is an object and link and y are undefined.  On output there  */
/*  are two cases:                                                           */
/*                                                                           */
/*  link != x.  Then y is the last definite child of x and link is its link. */
/*                                                                           */
/*  link == x.  Then x has no definite child and y is undefined.             */
/*                                                                           */
/*  A SPLIT object is considered to be definite if both its children are     */
/*  definite.  This condition is returned by SplitIsDefinite.                */
/*                                                                           */
/*****************************************************************************/

INLINE void LastDefinite(OBJECT x, OBJECT link, OBJECT y) {
    for( link = LastDown(x);  link != x;  link = PrevDown(link) )
    {
        Child(&y, link);
        if( objectOfType(y, SPLIT) ? SplitIsDefinite(y) : is_definite(type(y)) )
            break;
    }
}

/*****************************************************************************/
/*                                                                           */
/*  PrevDefinite(x, link, y)                                                 */
/*                                                                           */
/*  On input, x is an object and link is a link to one of its children; y    */
/*  is undefined.  On output there are two cases:                            */
/*                                                                           */
/*  link != x.  Then y is the first definite child of x preceding link, and  */
/*              link is changed to be the link of y.                         */
/*                                                                           */
/*  link == x.  Then x has no definite child preceding link, and y remains   */
/*              undefined.                                                   */
/*                                                                           */
/*****************************************************************************/

INLINE void PrevDefinite(OBJECT x, OBJECT link, OBJECT y) {
    for( link = PrevDown(link);  link != x;  link = PrevDown(link) )
    {
        Child(&y, link);
        if( objectOfType(y, SPLIT) ? SplitIsDefinite(y) : is_definite(type(y)) )
            break;
    }
}


/*@::Module Declarations@*****************************************************/
/*                                                                           */
/*  MODULE DECLARATIONS                                                      */
/*                                                                           */
/*****************************************************************************/

/*****  z01.c	  Supervise		**************************************/
extern	void	  run(int argc, char *argv[], int run_num, int *runs_to_do, FULL_CHAR *lib);
extern	void	  PrintUsage(FILE *fp);
extern	int	  main2(int argc, char *argv[]);
// for use from go lang
extern  int   main1(char* all_in_one);
// extern	POINTER	  MemCheck;
extern	OBJECT	  StartSym;
extern	OBJECT	  GalleySym;
extern	OBJECT	  ForceGalleySym;
extern	OBJECT	  InputSym;
extern	OBJECT	  PrintSym;
extern	OBJECT	  FilterInSym;
extern	OBJECT	  FilterOutSym;
extern	OBJECT	  FilterErrSym;
extern	OBJECT	  VerbatimSym;
extern	OBJECT	  RawVerbatimSym;
extern	OBJECT	  OptGallSym;
extern	BACK_END  BackEnd;
extern	OBJECT	  CommandOptions;
extern	BOOLEAN2	  AllowCrossDb;
extern	BOOLEAN2	  UseCollate;
extern	BOOLEAN2	  InMemoryDbIndexes;
extern	BOOLEAN2	  Kern;
extern	BOOLEAN2	  SafeExecution;
extern	BOOLEAN2   AltErrorFormat;
extern	int	  TotalWordCount;
extern	BOOLEAN2	  InitializeAll;
#if LOCALE_ON
extern	nl_catd	  MsgCat;
#endif

/*****  z02.c	  Lexical Analyser	**************************************/
extern	BOOLEAN2	  LexLegalName(const FULL_CHAR *str);
extern	void	  LexInit(void);
extern	void	  LexPush(FILE_NUM x, int offs, FILE_TYPE ftyp, int lnum, BOOLEAN2 same);
extern	void	  LexPop(void);
extern	long	  LexNextTokenPos(void);
extern	OBJECT	  LexGetToken(void);
extern	OBJECT	  LexScanVerbatim(FILE *fp, BOOLEAN2 end_stop, FILE_POS *err_pos,
		    BOOLEAN2 lessskip);

/*****  z03.c	  File Service	        **************************************/
// extern	FILE_POS  *no_fpos;
extern	void	  InitFiles(void);
extern	void	  AddToPath(PATH_TYPE fpath, OBJECT dirname);
extern	FILE_NUM  DefineFile(const FULL_CHAR *str, const FULL_CHAR *suffix,
		    FILE_POS *xfpos, FILE_TYPE ftype, PATH_TYPE fpath);
extern	FILE_NUM  FirstFile(FILE_TYPE ftype);
extern	FILE_NUM  NextFile(FILE_NUM i);
extern	FILE_NUM  FileNum(FULL_CHAR *str, const FULL_CHAR *suffix);
extern	FILE_NUM  DatabaseFileNum(FILE_POS *xfpos);
extern	FULL_CHAR *FileName(FILE_NUM fnum);
extern	FULL_CHAR *FullFileName(FILE_NUM fnum);
extern	FILE_TYPE	FileType(FILE_NUM fnum);
extern	FULL_CHAR *EchoFilePos(FILE_POS *pos);
extern	FULL_CHAR *EchoAltFilePos(FILE_POS *pos);
extern	FULL_CHAR *EchoFileSource(FILE_NUM fnum);
extern	FULL_CHAR *EchoFileLine(FILE_POS *pos);
extern	FILE_POS  *PosOfFile(FILE_NUM fnum);
extern	FILE	  *OpenFile(FILE_NUM fnum, BOOLEAN2 check_ld, BOOLEAN2 check_lt);
extern	FILE	  *OpenIncGraphicFile(const FULL_CHAR *str, OBJTYPE typ,
		    OBJECT *full_name, FILE_POS *xfpos, BOOLEAN2 *compressed);
extern	void	  FileSetUpdated(FILE_NUM fnum, int newlines);
extern	int	  FileGetLineCount(FILE_NUM fnum);
extern	BOOLEAN2	  FileTestUpdated(FILE_NUM fnum);

/*****  z04.c	  Token Service	        **************************************/
extern	OBJECT	  NewToken(OBJTYPE xtype, FILE_POS *xfpos,
		    unsigned char xvspace, unsigned char xhspace,
		    unsigned char xprec, OBJECT xactual);
extern	OBJECT	  CopyTokenList(OBJECT x, FILE_POS *pos);

// deprecated
extern	const FULL_CHAR *EchoCatOpUnsafe(unsigned xtype, BOOLEAN2 xmark, BOOLEAN2 xjoin);

extern	const FULL_CHAR *EchoCatOp(OBJTYPE xtype, BOOLEAN2 xmark, BOOLEAN2 xjoin);
extern	const FULL_CHAR *EchoToken(OBJECT x);

/*****  z05.c	  Read Definitions  	**************************************/
extern	void	  ReadPrependDef(OBJTYPE typ, OBJECT encl);
extern	void	  ReadIncGRepeatedDef(OBJTYPE typ, OBJECT encl);
extern	void	  ReadDatabaseDef(OBJTYPE typ, OBJECT encl);
extern	void	  ReadDefinitions(OBJECT *token, OBJECT encl, OBJTYPE res_type);

/*****  z06.c	  Object Parser	        **************************************/
extern	BOOLEAN	  InDefinitions;
extern	void	  SetScope(OBJECT env, int *count, BOOLEAN vis_only);
extern	void	  InitParser(const FULL_CHAR *cross_db);
extern	OBJECT	  Parse(OBJECT *token, OBJECT encl, BOOLEAN defs_allowed,
		    BOOLEAN transfer_allowed);

/*****  z07.c	  Object Service	**************************************/
// extern	BOOLEAN2	  SplitIsDefinite(OBJECT x);
// extern	int	  DisposeObject(OBJECT x);
extern	OBJECT	  MakeWord(OBJTYPE typ, const FULL_CHAR *str, FILE_POS *pos);
extern	OBJECT	  MakeWordTwo(OBJTYPE typ, const FULL_CHAR *str1, const FULL_CHAR *str2,
		    FILE_POS *pos);
extern	OBJECT	  MakeWordThree(const FULL_CHAR *s1, const FULL_CHAR *s2, const FULL_CHAR *s3);
extern	OBJECT	  CopyObject(OBJECT x, FILE_POS *pos);
extern	OBJECT	  InsertObject(OBJECT x, OBJECT *ins, STYLE *style);
extern	OBJECT	  Meld(OBJECT x, OBJECT y);
extern	BOOLEAN2	  EqualManifested(OBJECT x, OBJECT y);

/*****  z08.c	  Object Manifest	**************************************/
extern	OBJECT	  ReplaceWithTidy(OBJECT x, TIDY_TE one_word);
extern	float	  GetScaleFactor(OBJECT x);
extern	OBJECT	  Manifest(OBJECT x, OBJECT env, STYLE *style, OBJECT bthr[2],
		    OBJECT fthr[2], OBJECT *target, OBJECT *crs, BOOLEAN2 ok,
		    BOOLEAN2 need_expand, OBJECT *enclose, BOOLEAN2 fcr);

/*****  z09.c	  Closure Expansion	**************************************/
extern	OBJECT	  SearchEnv(OBJECT env, OBJECT sym);
extern	OBJECT	  SetEnv(OBJECT x, OBJECT y);
extern	void	  AttachEnv(OBJECT env, OBJECT x);
extern	OBJECT	  GetEnv(OBJECT x);
extern	OBJECT	  DetachEnv(OBJECT x);
extern	OBJECT	  ClosureExpand(OBJECT x, OBJECT env, BOOLEAN2 crs_wanted,
		    OBJECT *crs, OBJECT *res_env);
extern	OBJECT	  ParameterCheck(OBJECT x, OBJECT env);

/*****  z10.c	  Cross References	**************************************/
extern	void	  CrossInitModule(void);
extern	void	  CrossInit(OBJECT sym);
extern	OBJECT	  CrossMake(OBJECT sym, OBJECT val, OBJTYPE ctype);
extern	OBJECT	  GallTargEval(OBJECT sym, FILE_POS *dfpos);
extern	void	  CrossAddTag(OBJECT x);
extern	OBJECT	  CrossExpand(OBJECT x, OBJECT env, STYLE *style,
		    OBJECT *crs, OBJECT *res_env);
extern	void	  CrossSequence(OBJECT x);
extern	void	  CrossClose(void);

/*****  z11.c	  Style Service		**************************************/
extern	FULL_CHAR *EchoStyle(STYLE *style);
extern	void	  SpaceChange(STYLE *style, OBJECT x);
extern	void	  BreakChange(STYLE *style, OBJECT x);
extern	void	  YUnitChange(STYLE *style, OBJECT x);
extern	void	  ZUnitChange(STYLE *style, OBJECT x);

/*****  z12.c	  Size Finder		**************************************/
extern	void	  SpannerAvailableSpace(OBJECT y, DIM_TE dim, FULL_LENGTH *resb,
		     FULL_LENGTH *resf);
extern	OBJECT	  MinSize(OBJECT x, DIM_TE dim, OBJECT *extras);

/*****  z13.c	  Object Breaking	**************************************/
extern	OBJECT	  BreakObject(OBJECT x, CONSTRAINT *c);

/*****  z14.c	  Object Filling        **************************************/
extern	OBJECT	  FillObject(OBJECT x, CONSTRAINT *c, OBJECT multi,
		     BOOLEAN2 can_hyphenate, BOOLEAN2 allow_shrink,
		     BOOLEAN2 extend_unbreakable, BOOLEAN2 *hyph_used);

/*****  z15.c	  Size Constraints	**************************************/
extern	void	  MinConstraint(CONSTRAINT *xc, CONSTRAINT *yc);
extern	void	  SetSizeToMaxForwardConstraint(FULL_LENGTH *b, FULL_LENGTH *f,
		    CONSTRAINT *c);
extern	void	  EnlargeToConstraint(FULL_LENGTH *b, FULL_LENGTH *f,
		    CONSTRAINT *c);
extern	int	  ScaleToConstraint(FULL_LENGTH b, FULL_LENGTH f,
		    CONSTRAINT *c);
extern	void	  InvScaleConstraint(CONSTRAINT *yc, FULL_LENGTH sf,
		    CONSTRAINT*xc);
extern	void	  RotateConstraint(CONSTRAINT *c, OBJECT y, FULL_LENGTH angle,
		    CONSTRAINT *hc, CONSTRAINT *vc, DIM_TE dim);
extern	BOOLEAN2	  InsertScale(OBJECT x, CONSTRAINT *c);
extern	void	  Constrained(OBJECT x, CONSTRAINT *xc, DIM_TE dim, OBJECT *why);
extern	FULL_CHAR *EchoConstraint(CONSTRAINT *c);
extern	void	  DebugConstrained(OBJECT x);

/*****  z16.c	  Size Adjustments	**************************************/
extern	FULL_LENGTH	  FindShift(OBJECT x, OBJECT y, DIM_TE dim);
extern	void	  SetNeighbours(OBJECT link, BOOLEAN2 ratm, OBJECT *pg,
		    OBJECT *pdef, OBJECT *sg, OBJECT *sdef, int *side);
extern	void	  AdjustSize(OBJECT x, FULL_LENGTH b, FULL_LENGTH f, DIM_TE dim);

/*****  z17.c	  Gap Widths		**************************************/
extern	int	  GetWidth(OBJECT x, STYLE *style);
extern	void	  GetGap(OBJECT x, STYLE *style, GAP *res_gap,
		    unsigned *res_inc);
extern	FULL_LENGTH  MinGap(FULL_LENGTH a, FULL_LENGTH b, FULL_LENGTH c, GAP *xgap);
extern	FULL_LENGTH  ExtraGap(FULL_LENGTH a, FULL_LENGTH b, GAP *xgap, int dir);
extern	FULL_LENGTH  ActualGap(FULL_LENGTH a, FULL_LENGTH b, FULL_LENGTH c,
		       GAP *xgap, FULL_LENGTH f, FULL_LENGTH mk);
extern	FULL_CHAR *EchoGap(GAP *xgap);

/*****  z18.c	  Galley Transfer	**************************************/
extern	STYLE	  InitialStyle;
extern	CONTEXT	  InitialContext;
extern	OBJECT	  InitialEnvironment;
extern	void	  TransferInit(OBJECT InitEnv);
extern	OBJECT	  TransferBegin(OBJECT x);
extern	void	  TransferComponent(OBJECT x);
extern	void	  TransferEnd(OBJECT x);
extern	void	  TransferClose(void);

/*****  z19.c	  Galley Attaching	**************************************/
extern	void	  DetachGalley(OBJECT hd);
extern	OBJECT	  SearchGalley(OBJECT start, OBJECT sym, BOOLEAN2 forwards,
		    BOOLEAN2 subgalleys, BOOLEAN2 closures, BOOLEAN2 input);
extern	ATTACH	  AttachGalley(OBJECT hd, OBJECT *inners, OBJECT *suspend_pt);

/*****  z20.c	  Galley Flushing	**************************************/
extern	FULL_CHAR *DebugInnersNames(OBJECT inners);
extern	void	  FlushGalley(OBJECT hd);

/***    z21.c	  Galley Maker		**************************************/
extern	void	  SizeGalley(OBJECT hd, OBJECT env, BOOLEAN2 rows,
		    BOOLEAN2 joined, BOOLEAN2 nonblock, BOOLEAN2 trig,
		    STYLE *style, CONSTRAINT *c, OBJECT target,
		    OBJECT *dest_index, OBJECT *recs, OBJECT *inners,
		    OBJECT enclose);

/***    z22.c	  Galley Service	**************************************/
extern	void	  PromoteInit(void);
extern	void	  ClearHeaders(OBJECT hd);
extern	void	  Interpose(OBJECT z, OBJTYPE typ, OBJECT x, OBJECT y);
extern	void	  FlushInners(OBJECT inners, OBJECT hd);
extern	void	  ExpandRecursives(OBJECT recs);
extern	void	  HandleHeader(OBJECT hd, OBJECT header);
extern	void	  Promote(OBJECT hd, OBJECT stop_link, OBJECT dest_index,
		    BOOLEAN2 join_after);
extern	void	  KillGalley(OBJECT hd, BOOLEAN2 optimize);
extern	void	  FreeGalley(OBJECT hd, OBJECT stop_link, OBJECT *inners,
		    OBJECT relocate_link, OBJECT sym);
extern	void	  SetTarget(OBJECT hd);
extern	int	  CheckComponentOrder(OBJECT preceder, OBJECT follower);

/*****  z23.c	  Galley Printer	**************************************/
extern	OBJECT	  FixAndPrintObject(OBJECT x, FULL_LENGTH xmk, FULL_LENGTH xb,
		    FULL_LENGTH xf, DIM_TE dim, BOOLEAN2 suppress, FULL_LENGTH pg,
		    unsigned count, FULL_LENGTH *actual_back, FULL_LENGTH *actual_fwd);

/*****  z24.c	  Print Service         **************************************/
extern	char	  *EightBitToPrintForm[];

/*****  z25.c	  Object Echo	        **************************************/
extern	FULL_CHAR *EchoObject(OBJECT x);
extern	void	  DebugObject(OBJECT x);
extern	FULL_CHAR *EchoIndex(OBJECT index);
extern	void	  DebugGalley(OBJECT hd, OBJECT pinpt, int indent);

/*****  z26.c	  Echo Service	        **************************************/
extern	void	  BeginString(void);
extern	void	  AppendString(const FULL_CHAR *str);
extern	FULL_CHAR *EndString(void);
extern	FULL_CHAR *EchoLength(int len);
// extern	FULL_CHAR *Image(unsigned int c);
extern	void	  SetLengthDim(DIM_TE dim);

/*****	z28.c	  Error Service		**************************************/
extern	void	  ErrorInit(void);
extern	void	  ErrorSetFile(FULL_CHAR *str);
extern	BOOLEAN2	  ErrorSeen(void);
extern	void	  EnterErrorBlock(BOOLEAN2 ok_to_print);
extern	void	  LeaveErrorBlock(BOOLEAN2 commit);
extern	void	  CheckErrorBlocks(void);
// extern	POINTER	  Error(int set_num, int msg_num, char *str, int etype, FILE_POS *pos, ...);

/*****  z29.c	  Symbol Table		**************************************/
extern	void	  InitSym(void);
extern	void	  PushScope(OBJECT x, BOOLEAN2 npars, BOOLEAN2 vis);
extern	void	  PopScope(void);
extern	void	  SuppressVisible(void);
extern	void	  UnSuppressVisible(void);
extern	void	  SuppressScope(void);
extern	void	  UnSuppressScope(void);
extern	void	  SwitchScope(OBJECT sym);
extern	void	  UnSwitchScope(OBJECT sym);
extern	void	  BodyParAllowed(void);
extern	void	  BodyParNotAllowed(void);
extern	OBJECT	  GetScopeSnapshot(void);
extern	void	  LoadScopeSnapshot(OBJECT ss);
extern	void	  ClearScopeSnapshot(OBJECT ss);
extern	OBJECT	  InsertSym(const FULL_CHAR *str, OBJTYPE xtype,
		    FILE_POS *xfpos, unsigned char xprecedence,
		    BOOLEAN2 xindefinite, BOOLEAN2 xrecursive,
		    OBJTYPE xpredefined, OBJECT xenclosing, OBJECT xbody);
extern	void	  InsertAlternativeName(FULL_CHAR *str, OBJECT s,
		    FILE_POS *xfpos);
extern	OBJECT	  SearchSym(FULL_CHAR *str, int len);
extern	FULL_CHAR *SymName(OBJECT s);
extern	FULL_CHAR *FullSymName(OBJECT x, FULL_CHAR *str);
extern	OBJECT	  ChildSym(OBJECT s, OBJTYPE typ);
extern	OBJECT	  ChildSymWithCode(OBJECT s, unsigned char code);
extern	void	  CheckSymSpread(void);
extern	void	  DeleteEverySym(void);
extern	void	  DebugScope(void);

/*****  z30.c	  Symbol Uses		**************************************/
extern	void	  InsertUses(OBJECT x, OBJECT y);
extern	void	  FlattenUses(void);
extern	BOOLEAN2	  SearchUses(OBJECT x, OBJECT y);
extern	OBJECT	  FirstExternTarget(OBJECT sym, OBJECT *cont);
extern	OBJECT	  NextExternTarget(OBJECT sym, OBJECT *cont);

/*****  z32.c	  Counter Service           **********************************/
extern	OBJECT	  Next(OBJECT x, int inc, BOOLEAN2 *done);

/*****  z33.c	  Database Service	**************************************/
extern	OBJECT	  OldCrossDb;
extern	OBJECT	  NewCrossDb;
extern	void	  DbInit(void);
extern	OBJECT	  DbCreate(OBJECT x);
extern	void	  DbInsert(OBJECT db, BOOLEAN2 gall, OBJECT sym, const FULL_CHAR *tag,
		    FILE_POS *tagfpos, const FULL_CHAR *seq, FILE_NUM dfnum,
		    long dfpos, int dlnum, BOOLEAN2 check);
extern	void	  DbConvert(OBJECT db, BOOLEAN2 full_name);
extern	void	  DbClose(OBJECT db);
extern	OBJECT	  DbLoad(OBJECT stem, PATH_TYPE fpath, BOOLEAN2 create, OBJECT symbs,
		    BOOLEAN2 in_memory);
extern	BOOLEAN2	  DbRetrieve(OBJECT db, BOOLEAN2 gall, OBJECT sym,
		    FULL_CHAR *tag, FULL_CHAR *seq, FILE_NUM *dfnum,
		    long *dfpos, int *dlnum, long *cont);
extern	BOOLEAN2	  DbRetrieveNext(OBJECT db, BOOLEAN2 *gall, OBJECT *sym,
		    FULL_CHAR *tag, FULL_CHAR *seq, FILE_NUM *dfnum,
		    long *dfpos, int *dlnum, long *cont);

/*****  z34.c	  Rotation Service    	**************************************/
extern	void	  RotateSize(FULL_LENGTH *xcb, FULL_LENGTH *xcf,
		    FULL_LENGTH *xrb, FULL_LENGTH *xrf, OBJECT y,
		    FULL_LENGTH theta);

/*****  z35.c	  Time Keeper     	**************************************/
extern	FULL_CHAR *TimeString(void);
extern	void	  InitTime(void);
extern	OBJECT	  MomentSym;
extern	OBJECT	  StartMoment(void);

/*****  z36.c	  Hyphenation     	**************************************/
extern	void	  HyphInit(void);
extern	BOOLEAN2	  ReadHyphTable(LANGUAGE_NUM lnum);
extern	OBJECT	  Hyphenate(OBJECT x);

/*****  z37.c	  Font Service           *************************************/
extern	OBJECT	  FontDefSym;
extern	FONT_INFO *finfo;
extern	int	  font_curr_page;
extern	void	  FontInit(void);
extern	void	  FontChange(STYLE *style, OBJECT x);
extern	FULL_LENGTH FontKernLength(FONT_NUM fnum, FULL_CHAR *unacc_map,
  FULL_CHAR ch1, FULL_CHAR ch2);
extern	void	  FontWordSize(OBJECT x);
extern	FULL_LENGTH  FontSize(FONT_NUM fnum, OBJECT x);
extern	FULL_LENGTH  FontHalfXHeight(FONT_NUM fnum);
extern	MAPPING	  FontMapping(FONT_NUM fnum, FILE_POS *xfpos);
extern	FULL_CHAR *FontName(FONT_NUM fnum);
extern	FULL_CHAR *FontFamily(FONT_NUM fnum);
extern	FULL_CHAR *FontFace(FONT_NUM fnum);
extern	FULL_CHAR *FontFamilyAndFace(FONT_NUM fnum);
extern	void	  FontPrintAll(FILE *fp);
extern	void	  FontPrintPageSetup(FILE *fp);
extern	void	  FontPrintPageResources(FILE *fp);
extern	void	  FontAdvanceCurrentPage(void);
extern	void	  FontPageUsed(OBJECT face);
extern	BOOLEAN2	  FontNeeded(FILE *fp);
extern	FULL_LENGTH FontGlyphHeight(FONT_NUM fnum, FULL_CHAR chr);
extern	FULL_LENGTH FontGlyphWidth(FONT_NUM fnum, FULL_CHAR chr);

/*****  z38.c	  Character Mappings    **************************************/
extern	MAP_VEC	  MapTable[];
extern	void	  MapInit(void);
extern	MAPPING	  MapLoad(OBJECT filename, BOOLEAN2 recoded);
extern	FULL_CHAR MapCharEncoding(const FULL_CHAR *str, MAPPING m);
extern	FULL_CHAR *MapEncodingName(MAPPING m);
extern	void	  MapPrintEncodings(void);
extern	void	  MapEnsurePrinted(MAPPING m, int curr_page);
extern	void	  MapPrintPSResources(FILE *fp);
extern	OBJECT	  MapSmallCaps(OBJECT x, STYLE *style);
extern	BOOLEAN2	  MapIsLowerCase(FULL_CHAR ch, MAPPING m);


/*****  z39.c	  String Handler        **************************************/
/* #define		  AsciiToFull(x)	( (FULL_CHAR *) (x) ) */
#define		  StringEqual(a, b)	(strcmp((char *)(a), (char *)(b))==0)
extern int	  strcollcmp(char *a, char *b);
#define		  TabbedStringLessEqual(a, b) \
		    ( UseCollate ? strcollcmp((char *)(a),(char *)(b)) <= 0 \
				 : strcmp((char *)(a),(char *)(b)) <= 0 )
#define		  StringCat(a, b)	strcat((char *)(a),(char *)(b))
#define		  StringCopy(a, b)	strcpy((char *)(a),(char *)(b))
#define		  StringLength(a)	strlen((char *)(a))
#define		  StringFOpen(a, b)	fopen( (char *) (a), (b) )
#define		  StringFPuts(a, b)	fputs( (char *) (a), (b) )
#define		  StringRemove(a)	remove((char *)(a))
#define		  StringRename(a, b)	rename((char *)(a),(char *)(b))
extern	BOOLEAN2	  StringBeginsWith(const FULL_CHAR *str, const FULL_CHAR *pattern);
extern	BOOLEAN2	  StringBeginsWithWord(const FULL_CHAR *str, const FULL_CHAR *pattern);
extern	BOOLEAN2	  StringEndsWith(const FULL_CHAR *str, const FULL_CHAR *pattern);
extern	BOOLEAN2	  StringContains(const FULL_CHAR *str, const FULL_CHAR *pattern);
extern	FULL_CHAR *StringInt(int i);
extern	FULL_CHAR *StringFiveInt(int i);
extern	FULL_CHAR *StringQuotedWord(OBJECT x);

/*****  z40.c	  Filter Handler        **************************************/
extern	void	  FilterInit(void);
extern	OBJECT	  FilterCreate(BOOLEAN2 use_begin, OBJECT act, FILE_POS *xfpos);
extern	void	  FilterSetFileNames(OBJECT x);
extern	OBJECT	  FilterExecute(OBJECT x, FULL_CHAR *command, OBJECT env);
extern	void	  FilterWrite(OBJECT x, FILE *fp, int *linecount);
extern	void	  FilterScavenge(BOOLEAN2 all);

/*****  z41.c	  Object Input-Output   **************************************/
extern	void	  ReadFromFileInit(void);
extern	OBJECT	  ReadFromFile(FILE_NUM fnum, long pos, int lnum);
extern	void	  AppendToFile(OBJECT x, FILE_NUM fnum, int *pos, int *lnum);
extern	void	  CloseFiles(void);

/*****  z42.c	  Colour Service        **************************************/
extern	void	  ColourInit(void);
extern	void	  ColourChange(STYLE *style, OBJECT x);
extern	void	  ColourUnderlineChange(STYLE *style, OBJECT x);
extern	FULL_CHAR *ColourCommand(COLOUR_NUM cnum);

/*****  z43.c	  Language Service      **************************************/
extern	void	  LanguageInit(void);
extern	BOOLEAN2	  LanguageWordEndsSentence(OBJECT wd, BOOLEAN2 lc_prec);
extern	void	  LanguageDefine(OBJECT names, OBJECT hyph_file);
extern	void	  LanguageChange(STYLE *style, OBJECT x);
extern	FULL_CHAR *LanguageString(LANGUAGE_NUM lnum);
extern	OBJECT	  LanguageHyph(LANGUAGE_NUM lnum);
extern	BOOLEAN2	  LanguageSentenceEnds[];

/*****  z44.c	  Vertical Hyphenation  **************************************/
extern	BOOLEAN2	  VerticalHyphenate(OBJECT y);
extern	OBJECT	  ConvertGalleyList(OBJECT x);
extern	OBJECT	  BuildEnclose(OBJECT hd);

/*****  z45.c	  External Sort         **************************************/
extern	int	  ReadOneLine(FILE *fp, FULL_CHAR *buff, int buff_len);
extern	int	  ReadOneBinaryLine(FILE *fp, FULL_CHAR *buff, int buff_len,
                    int *count, long *remaining_len);
extern	LINE	  *ReadLines(FILE *fp, FULL_CHAR *fname, FULL_CHAR *first_line, int *len);
extern	void	  WriteLines(FILE *fp, LINE *lines, int len);
extern	void	  SortLines(LINE *lines, int lines_len);
extern	void	  SortFile(FULL_CHAR *infile, FULL_CHAR *outfile);

/*****  z46.c	  Optimal Galleys       **************************************/
extern	BOOLEAN2	  FindOptimize(OBJECT x, OBJECT env);
extern	void	  SetOptimize(OBJECT hd, STYLE *style);
extern	void	  GazumpOptimize(OBJECT hd, OBJECT dest);
extern	void	  CalculateOptimize(OBJECT hd);
extern	void	  DebugOptimize(OBJECT hd);

/*****  z47.c	  Environment Table     **************************************/
extern	void	  EnvInit(void);
extern	BOOLEAN2	  EnvWriteRetrieve(OBJECT env, FILE_NUM fnum, int *offset,
		    int *lnum);
extern	void	  EnvWriteInsert(OBJECT env, FILE_NUM fnum, int offset,int lnum);
extern	BOOLEAN2	  EnvReadRetrieve(FILE_NUM fnum, int offset, OBJECT *env);
extern	void	  EnvReadInsert(FILE_NUM fnum, int offset, OBJECT env);
extern	void	  EnvDebug(void);

/*****  z48.c	  PDF back end (old)    **************************************/
extern	void      PDFFile_Init(FILE* in_fp, int in_h_bound, int in_v_bound,
				int in_IN, int in_CM, int in_PT, int in_EM);
extern	void      PDFFile_BeginFontEncoding(FILE* in_fp,
				const char* in_encoding_name);
extern	void      PDFFile_EndFontEncoding(FILE* in_fp);
extern	void      PDFFile_Cleanup(FILE* in_fp);
extern	void      PDFPage_Init(FILE* in_fp, float in_scale_factor,
				int in_line_width);
extern	void      PDFPage_Cleanup(FILE* in_fp);
extern	void	  PDFPage_Write(FILE* in_fp, char* in_str);
extern	void      PDFPage_Push(FILE* in_fp);
extern	void      PDFPage_Pop(FILE* in_fp);
extern	void	  PDFPage_Scale(FILE* in_fp, float in_h_scale_factor,
				float in_v_scale_factor);
extern	void	  PDFPage_Translate(FILE* in_fp, float in_delta_h,
				float in_delta_v);
extern	void	  PDFPage_Rotate(FILE* in_fp, float in_angle_in_radians);
extern	void	  PDFPage_SetVars(int xsize, int ysize, int xmark, int ymark,
				int loutf, int loutv, int louts);
extern	void	  PDFPage_WriteGraphic(FILE* in_fp, FULL_CHAR* in_str);
extern	void	  PDFPage_PrintUnderline(FILE* in_fp, int in_x1, int in_x2,
				int in_y, int in_thickness);

extern	void      PDFFont_AddFont(
				FILE* in_fp,
				const FULL_CHAR* in_short_font_name,
				const FULL_CHAR* in_real_font_name,
				const FULL_CHAR* in_font_encoding_name);
extern	void      PDFFont_Set(FILE* in_fp, FULL_LENGTH in_font_size,
				FULL_CHAR * in_short_font_name);
extern	void    PDFText_OpenXY(FILE* in_fp, int hpos, int vpos);
extern	void    PDFText_OpenX(FILE* in_fp, int hpos);
extern	void    PDFText_Open(FILE* in_fp);
extern	void    PDFText_Kern(FILE* in_fp, int in_kern);
extern	void    PDFText_Close(FILE* in_fp);
extern	BOOLEAN2 PDFHasValidTextMatrix(void);

/*****  z49.c	  PostScript back end   **************************************/
extern	BACK_END  PS_BackEnd;
extern	BACK_END  PS_NullBackEnd;
extern	void	  PS_IncGRepeated(OBJECT x);
/* extern	int	  PS_FindIncGRepeated(OBJECT x, int typ); */
/* extern	void	  PS_PrintEPSFile(FILE *fp, FILE_POS *pos); */
extern	BOOLEAN2	  PS_FindBoundingBox(FILE *fp, FILE_POS *pos, FULL_LENGTH *llx,
		    FULL_LENGTH *lly, FULL_LENGTH *urx, FULL_LENGTH *ury);

/*****  z50.c	  PDF back end (new)    **************************************/
extern	BACK_END  PDF_BackEnd;		/* PDF back end record               */

/*****  z51.c	  Plain text back end   **************************************/
extern	BACK_END  Plain_BackEnd;	/* Plain Text back end record        */
extern	BACK_END  Plain_NullBackEnd;	/* Plain Text null back end record   */
extern	FULL_LENGTH PlainCharWidth;	/* character width                   */
extern	FULL_LENGTH PlainCharHeight;	/* character height		     */
extern	BOOLEAN2	  PlainFormFeed;	/* true if using \f		     */

/*****  z52.c	  Texture Service        **************************************/
extern	BOOLEAN2	  UseTexture;
extern	void	  TextureInit(void);
extern	void	  TextureChange(STYLE *style, OBJECT x);
extern	FULL_CHAR *TextureCommand(TEXTURE_NUM pnum);

#endif
