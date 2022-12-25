/*@z31.c:Memory Allocator:DebugMemory()@**************************************/
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
/*  FILE:         z31.c                                                      */
/*  MODULE:       Memory Allocator                                           */
/*  EXTERNS:      DebugMemory(), zz_free[], MemInit(), GetMemory()           */
/*                                                                           */
/*****************************************************************************/
// #include "externs.h"
#include "lout.h"

#define	MEM_CHUNK	1020		/* how many ALIGNs to get from sys   */


#if DEBUG_ON
static	int	no_of_calls	= 0;	/* number of calls to calloc()       */
static  int     recs_created    = 0;	/* number of records created         */
static  int     bytes_created   = 0;	/* number of bytes in created recs   */
	int	zz_newcount	= 0;	/* number of calls to New()          */
	int	zz_disposecount	= 0;	/* number of calls to Dispose()      */
	int	zz_listcount	= 0;	/* number of elements in zz_free[]   */

static	int	usage_nums[MEM_USAGE_MAX_E] = { 0 };
static	int	usage_bytes[MEM_USAGE_MAX_E] = { 0 };
static	int	max_usage_bytes[MEM_USAGE_MAX_E] = { 0 };
static	int	curr_total_bytes, max_total_bytes = 0;
static	char	*usage_strings[] = {
			"lout binary",
			"object memory chunks",
			"font tables",
			"lex buffers",
			"file tables",
			"cross reference tables",
			"plain text output grids",
			"database check tables",
			"in_memory database",
			"hyphenation pattern tables",
			"character mappings",
			"colour tables",
			"texture tables",
			"language tables",
};

/*****************************************************************************/
/*                                                                           */
/*  DebugRegisterUsage(typ, delta_num, delta_size)                           */
/*                                                                           */
/*  Register a change in the number of things of type typ that               */
/*  have been allocated memory, and the change in the number of bytes.       */
/*                                                                           */
/*****************************************************************************/

void DebugRegisterUsage(MEM_TE typ, int delta_num, int delta_size)
{ int i;
  MEM_T t = typ.mem;
  assert(0 <= t && t < MEM_USAGE_MAX_E, "DebugRegisterUsage!");
  usage_nums[t] += delta_num;
  usage_bytes[t] += delta_size;
  curr_total_bytes += delta_size;
  if( curr_total_bytes > max_total_bytes )
  { max_total_bytes = curr_total_bytes;
    for( i = 0; i < MEM_USAGE_MAX_E;  i++ )
      max_usage_bytes[i] = usage_bytes[i];
  }
} /* end DebugRegisterUsage */


/*****************************************************************************/
/*                                                                           */
/*  DebugMemory()                                                            */
/*                                                                           */
/*  Print memory usage.                                                      */
/*                                                                           */
/*****************************************************************************/

void DebugMemory(void)
{ int i, j;
  OBJECT p;
  #pragma clang diagnostic ignored "-Wunused-but-set-variable"
  int recs_free, bytes_free;

  recs_free = bytes_free = 0;
  for( i = 0;  i < MAX_OBJECT_REC;  i++ )
  { if( zz_free[i] != nilobj )
    { j = 0;
      for( p = zz_free[i];  p != nilobj;  p = pred(p, CHILD) )  j++;
      debug3(DMA, DD, "zz_free[%2d]: %5d (%d bytes)", i, j,
	i * j * sizeof(ALIGN));
      recs_free += j;
      bytes_free += i* j * sizeof(ALIGN);
    }
  }

  debug4(DMA, D, "%-35s %8s %8s %8s",
    "Summary of malloc() memory usage", "Quantity", "Bytes", "At max.");

  for( i = 1;  i < MEM_USAGE_MAX_E;  i++ )
  {
    debug4(DMA, D, "%-35s %8d %8d %8d", usage_strings[i], usage_nums[i],
      usage_bytes[i], max_usage_bytes[i]);
  }
  debug4(DMA, D, "%-35s %8s %8s %8s", "", "", "--------", "--------");
  debug4(DMA, D, "%-35s %8s %8d %8d", "","",curr_total_bytes,max_total_bytes);


  /***
  debug3(DMA, D, "%-12s %8s %8s", "", "records", "bytes");
  debug4(DMA, D, "%-12s %8s %8d (%d calls)", "calloc", "-",
    no_of_calls * MEM_CHUNK * sizeof(ALIGN), no_of_calls);
  debug3(DMA, D, "%-12s %8d %8d", "created", recs_created, bytes_created);
  debug3(DMA, D, "%-12s %8d %8d", "free (count)",    recs_free,    bytes_free);
  debug3(DMA, D, "%-12s %8d %8s", "free (var)",      zz_listcount, "-");
  debug3(DMA, D, "%-12s %8d %8s", "new-dispose",
    zz_newcount - zz_disposecount, "-");
  debug3(DMA, D, "%-12s %8d %8s", "created-free",
    recs_created - recs_free, "-");
  debug2(DMA, D, "newcount %d, disposecount %d", zz_newcount, zz_disposecount);
  *** */

  debug0(DMA, D, "");

} /* end DebugMemory */
#endif


/*@::zz_free[], zz_lengths[], MemInit()@**************************************/
/*                                                                           */
/*  OBJECT         zz_free[], zz_hold, zz_tmp, zz_res                        */
/*  int            zz_size                                                   */
/*  unsigned char  zz_lengths[]                                              */
/*                                                                           */
/*  zz_free[i]:    free records of size i*sizeof(ALIGN).                     */
/*  zz_lengths[i]: the number of ALIGNs in a record of type i.               */
/*  These variables are used only within the New() and Dispose() macros,     */
/*  and the list handling macros.                                            */
/*                                                                           */
/*****************************************************************************/

OBJECT		zz_free[MAX_OBJECT_REC], zz_hold, zz_tmp, zz_res;
int		zz_size;
unsigned char	zz_lengths[DISPOSED_E];		/* DISPOSED is 1 + max type */
OBJECT 		xx_link, xx_tmp, xx_res, xx_hold;


/*****************************************************************************/
/*                                                                           */
/*  MemInit()                                                                */
/*                                                                           */
/*  Initialise memory allocator.                                             */
/*                                                                           */
/*****************************************************************************/

void MemInit(void)
{
  zz_lengths[ WORD_E         ] = 0;
  zz_lengths[ QWORD_E        ] = 0;
  zz_lengths[ LINK_E         ] = ceiling(sizeof(struct link_type), sizeof(ALIGN));

  /* object types, except closure NB have actual() field in token phase! */
  zz_lengths[ CLOSURE_E      ] =
  zz_lengths[ NULL_CLOS_E    ] =
  zz_lengths[ PAGE_LABEL_E   ] =
  zz_lengths[ UNDER_REC_E    ] =
  zz_lengths[ CROSS_E        ] =
  zz_lengths[ FORCE_CROSS_E  ] =
  zz_lengths[ SPLIT_E        ] =
  zz_lengths[ PAR_E          ] =
  zz_lengths[ ROW_THR_E      ] =
  zz_lengths[ COL_THR_E      ] =
  zz_lengths[ HSPANNER_E     ] =
  zz_lengths[ VSPANNER_E     ] =
  zz_lengths[ ACAT_E         ] =
  zz_lengths[ HCAT_E         ] =
  zz_lengths[ VCAT_E         ] =
  zz_lengths[ BEGIN_HEADER_E ] =
  zz_lengths[ END_HEADER_E   ] =
  zz_lengths[ SET_HEADER_E   ] =
  zz_lengths[ CLEAR_HEADER_E ] =
  zz_lengths[ ONE_COL_E      ] =
  zz_lengths[ ONE_ROW_E      ] =
  zz_lengths[ WIDE_E         ] =
  zz_lengths[ HIGH_E         ] =
  zz_lengths[ HSHIFT_E       ] =
  zz_lengths[ VSHIFT_E       ] =
  zz_lengths[ HMIRROR_E      ] =
  zz_lengths[ VMIRROR_E      ] =
  zz_lengths[ HSCALE_E       ] =
  zz_lengths[ VSCALE_E       ] =
  zz_lengths[ HCOVER_E       ] =
  zz_lengths[ VCOVER_E       ] =
  zz_lengths[ SCALE_E        ] =
  zz_lengths[ KERN_SHRINK_E  ] =
  zz_lengths[ HCONTRACT_E    ] =
  zz_lengths[ VCONTRACT_E    ] =
  zz_lengths[ HLIMITED_E     ] =
  zz_lengths[ VLIMITED_E     ] =
  zz_lengths[ HEXPAND_E      ] =
  zz_lengths[ VEXPAND_E      ] =
  zz_lengths[ START_HVSPAN_E ] =
  zz_lengths[ START_HSPAN_E  ] =
  zz_lengths[ START_VSPAN_E  ] =
  zz_lengths[ HSPAN_E        ] =
  zz_lengths[ VSPAN_E        ] =
  zz_lengths[ PADJUST_E      ] =
  zz_lengths[ HADJUST_E      ] =
  zz_lengths[ VADJUST_E      ] =
  zz_lengths[ ROTATE_E       ] =
  zz_lengths[ BACKGROUND_E   ] =
  zz_lengths[ VERBATIM_E     ] =
  zz_lengths[ RAW_VERBATIM_E ] =
  zz_lengths[ CASE_E         ] =
  zz_lengths[ YIELD_E        ] =
  zz_lengths[ BACKEND_E      ] =
  zz_lengths[ FILTERED_E     ] =
  zz_lengths[ XCHAR_E        ] =
  zz_lengths[ FONT_E         ] =
  zz_lengths[ SPACE_E        ] =
  zz_lengths[ YUNIT_E        ] =
  zz_lengths[ ZUNIT_E        ] =
  zz_lengths[ BREAK_E        ] =
  zz_lengths[ UNDERLINE_E    ] =
  zz_lengths[ UNDERLINE_COLOUR_E ] =
  zz_lengths[ COLOUR_E       ] =
  zz_lengths[ TEXTURE_E      ] =
  zz_lengths[ OUTLINE_E      ] =
  zz_lengths[ LANGUAGE_E     ] =
  zz_lengths[ CURR_LANG_E    ] =
  zz_lengths[ CURR_FAMILY_E  ] =
  zz_lengths[ CURR_FACE_E    ] =
  zz_lengths[ CURR_YUNIT_E   ] =
  zz_lengths[ CURR_ZUNIT_E   ] =
  zz_lengths[ GET_CONTEXT_E  ] =
  zz_lengths[ SET_CONTEXT_E  ] =
  zz_lengths[ COMMON_E       ] =
  zz_lengths[ RUMP_E         ] =
  zz_lengths[ MELD_E         ] =
  zz_lengths[ INSERT_E       ] =
  zz_lengths[ ONE_OF_E       ] =
  zz_lengths[ NEXT_E         ] =
  zz_lengths[ PLUS_E         ] =
  zz_lengths[ MINUS_E        ] =
  zz_lengths[ ENV_OBJ_E      ] =
  zz_lengths[ ENV_E          ] =
  zz_lengths[ ENVA_E         ] =
  zz_lengths[ ENVB_E         ] =
  zz_lengths[ ENVC_E         ] =
  zz_lengths[ ENVD_E         ] =
  zz_lengths[ CENV_E         ] =
  zz_lengths[ CLOS_E         ] =
  zz_lengths[ LVIS_E         ] =
  zz_lengths[ LUSE_E         ] =
  zz_lengths[ LEO_E          ] =
  zz_lengths[ OPEN_E         ] =
  zz_lengths[ TAGGED_E       ] =
  zz_lengths[ INCGRAPHIC_E   ] =
  zz_lengths[ SINCGRAPHIC_E  ] =
  zz_lengths[ PLAIN_GRAPHIC_E] =
  zz_lengths[ GRAPHIC_E      ] =
  zz_lengths[ LINK_SOURCE_E  ] =
  zz_lengths[ LINK_DEST_E    ] =
  zz_lengths[ LINK_DEST_NULL_E] =
  zz_lengths[ LINK_URL_E     ] =
	ceiling(sizeof(struct closure_type), sizeof(ALIGN));

  zz_lengths[ HEAD_E         ] =
	ceiling(sizeof(struct head_type), sizeof(ALIGN));

  zz_lengths[ LBR_E          ] =
  zz_lengths[ RBR_E          ] =
  zz_lengths[ BEGIN_E        ] =
  zz_lengths[ END_E          ] =
  zz_lengths[ USE_E          ] =
  zz_lengths[ NOT_REVEALED_E ] =
  zz_lengths[ GSTUB_NONE_E   ] =
  zz_lengths[ GSTUB_INT_E    ] =
  zz_lengths[ GSTUB_EXT_E    ] =
  zz_lengths[ UNEXPECTED_EOF_E] =
  zz_lengths[ INCG_REPEATED_E ] =
  zz_lengths[ SINCG_REPEATED_E] =
  zz_lengths[ PREPEND_E      ] =
  zz_lengths[ SYS_PREPEND_E  ] =
  zz_lengths[ DATABASE_E     ] =
  zz_lengths[ SYS_DATABASE_E ] =
  zz_lengths[ DEAD_E         ] =
  zz_lengths[ UNATTACHED_E   ] =
  zz_lengths[ RECEPTIVE_E    ] =
  zz_lengths[ RECEIVING_E    ] =
  zz_lengths[ RECURSIVE_E    ] =
  zz_lengths[ PRECEDES_E     ] =
  zz_lengths[ FOLLOWS_E      ] =
  zz_lengths[ CROSS_FOLL_E   ] =
  zz_lengths[ CROSS_FOLL_OR_PREC_E] =
  zz_lengths[ GALL_FOLL_E    ] =
  zz_lengths[ GALL_FOLL_OR_PREC_E ] =
  zz_lengths[ CROSS_TARG_E   ] =
  zz_lengths[ GALL_TARG_E    ] =
  zz_lengths[ GALL_PREC_E    ] =
  zz_lengths[ CROSS_PREC_E   ] =
  zz_lengths[ PAGE_LABEL_IND_E] =
  zz_lengths[ SCALE_IND_E    ] =
  zz_lengths[ COVER_IND_E    ] =
  zz_lengths[ EXPAND_IND_E   ] =
  zz_lengths[ THREAD_E       ] =
  zz_lengths[ CR_LIST_E      ] =
  zz_lengths[ SCOPE_SNAPSHOT_E] =
	ceiling(sizeof(struct closure_type), sizeof(ALIGN));

  /* symbol types */
  zz_lengths[ MACRO_E        ] =
  zz_lengths[ LOCAL_E        ] =
  zz_lengths[ LPAR_E         ] =
  zz_lengths[ RPAR_E         ] =
  zz_lengths[ NPAR_E         ] =
	ceiling(sizeof(struct symbol_type), sizeof(ALIGN));

  /* gap objects */
  zz_lengths[ TSPACE_E       ] =
  zz_lengths[ TJUXTA_E       ] =
  zz_lengths[ GAP_OBJ_E      ] =
	ceiling(sizeof(struct gapobj_type), sizeof(ALIGN));

  /* cross-reference and data base types */
  zz_lengths[ CROSS_SYM_E    ] =
  zz_lengths[ CR_ROOT_E      ] = ceiling(sizeof(struct cr_type) , sizeof(ALIGN));

  /* external galley record */
  zz_lengths[ EXT_GALL_E  ] = ceiling(sizeof(struct ext_gall_type),sizeof(ALIGN));

} /* end MemInit() */


/*@::GetMemory()@*************************************************************/
/*                                                                           */
/*  OBJECT GetMemory(siz, pos)                                               */
/*                                                                           */
/*  Return a pointer to siz ALIGNs of memory (0 < siz < MAX_OBJECT_REC).     */
/*                                                                           */
/*****************************************************************************/

OBJECT GetMemory(int siz, FILE_POS *pos)
{ static ALIGN *next_free = (ALIGN *) nilobj;
#pragma clang diagnostic ignored "-Wunused-variable"
  static ALIGN *top_free  = (ALIGN *) nilobj;
  OBJECT res;

  debug1(DMA, DDD, "GetMemory( %d )", siz);

#if USE_SYSTEM_MALLOC

#if DEBUG_ON
  DebugRegisterUsage(MEM_OBJECTS, 1, siz * sizeof(ALIGN));
#endif

#if USE_MALLOC_DEBUG

  /* malloc + debugging */

  next_free = (ALIGN *) calloc(siz + MALLOC_HEADER_SIZE + MALLOC_TRAILER_SIZE, sizeof(ALIGN));
  if (next_free != NULL)
  { next_free += MALLOC_HEADER_SIZE;
    malloc_otype(next_free) = -1;
    malloc_orec_size(next_free) = siz;
    malloc_osentinel(next_free) = MALLOC_SENTINEL;
  }
#else

  /* malloc, no debugging */

  next_free = (ALIGN *) calloc(siz, sizeof(ALIGN));

#endif

  /* malloc, generic */

  if( next_free == NULL )
    Error(31, 1, "exiting now (run out of memory)", FATAL, pos);
  ifdebug(DMA, D, no_of_calls++; )

  res = (OBJECT) next_free;

#else

#if USE_MALLOC_DEBUG

  /* built-in + debugging */

  /* get memory from operating system, if not enough left here */
  if( &next_free[ siz + MALLOC_HEADER_SIZE + MALLOC_TRAILER_SIZE ] > top_free )
  {
#if DEBUG_ON
    DebugRegisterUsage(MEM_OBJECTS, 1, MEM_CHUNK * sizeof(ALIGN));
#endif
    next_free = (ALIGN *) calloc(MEM_CHUNK, sizeof(ALIGN));
    ifdebug(DMA, D, no_of_calls++; )
    if( next_free == NULL )
      Error(31, 1, "exiting now (run out of memory)", FATAL, pos);
    top_free = &next_free[MEM_CHUNK];
    debug2(DMA, DD, "GetMemory: calloc returned %ld - %ld",
      (long) next_free, (long) top_free);
  }

  res = (OBJECT) (&next_free[MALLOC_HEADER_SIZE]);

  malloc_otype(res) = -1;
  malloc_orec_size(res) = siz;
  malloc_osentinel(res) = MALLOC_SENTINEL;

  next_free = &next_free[ siz + MALLOC_HEADER_SIZE + MALLOC_TRAILER_SIZE ];

#else

  /* built-in, no debugging */

  /* get memory from operating system, if not enough left here */
  if( &next_free[siz] > top_free )
  {
#if DEBUG_ON
    DebugRegisterUsage(MEM_OBJECTS, 1, MEM_CHUNK * sizeof(ALIGN));
#endif
    next_free = (ALIGN *) calloc(MEM_CHUNK, sizeof(ALIGN));
    ifdebug(DMA, D, no_of_calls++; )
    if( next_free == NULL )
      Error(31, 1, "exiting now (run out of memory)", FATAL, pos);
    top_free = &next_free[MEM_CHUNK];
    debug2(DMA, DD, "GetMemory: calloc returned %ld - %ld",
      (long) next_free, (long) top_free);
  }

  res = (OBJECT) next_free;
  next_free = &next_free[siz];

#endif
#endif

  /* Uncomment the next line to test that objects initialize themselves correctly. */
  /* Objects that are reused from the free list are not initialized. */
  /* This memset simulates that and makes problems happen sooner. */
  /* memset(res, 0xFF, siz * sizeof(ALIGN)); */

#if DEBUG_ON
  recs_created++; bytes_created += siz * sizeof(ALIGN);
#endif
  debug3(DMA, DDD, "GetMemory returning @%ld (next_free = @%ld, top_free = @%ld",
    (long) res, (long) next_free, (long) top_free);
  return res;
} /* end GetMemory */
