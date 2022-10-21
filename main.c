/*@main.c@********************************************************************/
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
/*  FILE:         main.c                                                      */
/*  MODULE:       main                                                       */
/*  EXTERNS:      main(),                                                    */
/*                                                                           */
/*****************************************************************************/
#include "externs.h"
#include <signal.h>

/* On DOS/Win32 we need to set binary mode on stdout (Uwe) */
#if OS_DOS
#include <io.h>
#include <fcntl.h>
#ifdef __DJGPP__
#define _setmode(fd, mode)     setmode((fd), (mode))
#define _fileno(stream)        fileno((stream))
#endif
#endif

/*****************************************************************************/
/*                                                                           */
/*  main(argc, argv)                                                         */
/*                                                                           */
/*  Read command line, initialise everything, read definitions, read         */
/*  galleys, clean up and exit.                                              */
/*                                                                           */
/*****************************************************************************/

int main(int argc, char *argv[])
{ 
  FULL_CHAR *lib;			/* name of library directory         */
  int run_num, runs_to_do;
#if LOCALE_ON
  char catname[MAX_BUFF], *loc;
#endif

  /* find the name of the library directory, from envt or else from -D */
  lib = AsciiToFull(getenv("LOUTLIB"));
  if( lib == (FULL_CHAR *) NULL )
    lib = AsciiToFull(LIB_DIR);

  /* set locale if that's what we are doing */
#if LOCALE_ON
  loc = setlocale(LC_MESSAGES, "");
  if( loc == (char *) NULL )
  { Error(1, 6, "unable to initialize locale", WARN, no_fpos);
    loc = "C";
  }
  sprintf(catname, "%s/%s/%s/LC_MESSAGES/errors.%s",
    lib, LOCALE_DIR, loc, loc);
  MsgCat = catopen(catname, 0);
#endif

  run_num = 1;  runs_to_do = -1;
  do
  {
    if( run_num > 1 )
      Error(1, 34, "lout -r beginning run %d:", WARN, no_fpos, run_num);
    run(argc, argv, run_num, &runs_to_do, lib);
    run_num++;
  }
  while( run_num <= runs_to_do );

#if LOCALE_ON
  catclose(MsgCat);
#endif

  exit(0);
  return 0;
} /* end main */

