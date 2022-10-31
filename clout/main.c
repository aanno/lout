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
// #include "externs.h"
#include "../go-externs.h"
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
  int ret = main2(argc, argv);
  exit(ret);
  return ret;
} /* end main */

