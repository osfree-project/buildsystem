/*
 *  Generic Call Interface for Rexx
 *  Copyright � 2003, Florian Gro�e-Coosmann
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * ----------------------------------------------------------------------------
 *
 * This file contains redefinitions of the maintainer of the current
 * implementation. I don't wanna have these ugly
 * "#if defined(MACHINE_SUBTYPE_FLAVOUR_SMALL_STRAWBERRY) && !defined(...
 * in the code.
 *
 * Proper implementors change the following definitions to their requirements.
 * They may do their "defines" here and not in the code itself. It will be
 * nice to get a note for extensions here!
 */

/*
 * The include file may have the name rexxsaa.h or rexx.h depending on the
 * interpreter.
 */

#include "rexx_charset.h"

#ifndef __REXXSAA_H_INCLUDED
# include "../rexxsaa.h"
# define DONT_TYPEDEF_PFN
#endif
#ifndef __REXX_H_INCLUDED
# include "../rexx.h"
#endif

#include <setjmp.h>
#include <string.h>

/*
 * Though we have RXSTRING, GCI_str has its own implementation for speedup
 * or usage in a direct implementation.
 * We don't use or check for a terminator.
 */
typedef struct {
   int   used; /* really used bytes of val */
   int   max;  /* allocated size of val */
   char *val;  /* buffer for the content */
} GCI_str;

/*
 * We sometimes want to create a GCI_str from a native character buffer.
 * We provide a macro for doing so.
 *
 * .max is set to the buffers size, .used is set to 0.
 */
#define GCI_strOfCharBuffer(buf) GCI_str str_##buf;             \
                                 str_##buf.used = 0;            \
                                 str_##buf.max = sizeof( buf ); \
                                 str_##buf.val = buf

/*
 * malloc and free will be redirected to an implementor's specific code
 * which provides some magic in speed or defragmentation.
 */
#define GCI_malloc(hidden,size) Malloc_TSD( (tsd_t *) (hidden), size )
#define GCI_free(hidden,block)  Free_TSD( (tsd_t *) (hidden), block )

/*
 * GCI_ALIGNMENT sets the alignment for indirections. It is best to use
 * those values used by the memory allocator, but what value shall be used?
 * If you don't know, you should use 16 as a good default value.
 */
#define GCI_ALIGNMENT 16

/*
 * GCI_STACK_ELEMENT sets integral type of a stack element. This is typically
 * an unsigned or int.
 */
#define GCI_STACK_ELEMENT unsigned

/*
 * GCI_LITTLE_ENDIAN must be set to 1 or 0 depending on whether little endian
 * or big endian is the machine's representation.
 * In doubt, select 1 for Intel compatibles and 0 for others.
 */
#define GCI_LITTLE_ENDIAN 1

/*
 * GCI_ARGS shall be the maximum number of GCI_STACK_ELEMENTs which shall
 * be passed on the stack. This is usually the base type of maximum width
 * (e.g. long long or long double) / sizeof(unsigned) * 10.
 * But you can't use sizeof(), therefore you have to compute it by hand.
 */
#define GCI_ARGS 30

/*
 * GCI_PASSARGS is a macro which enumerates GCI_ARGS args of an array which
 * is passed to the macro. I don't know a good ANSI macro for this purpose.
 * Feel free to provide it!
 */
#define GCI_PASSARGS(a) a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],\
                        a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],\
                        a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],\
                        a[28],a[29]

/*
 * GCI_JUMPVAR is a macro which defines a jmp_buf in the file gci_call.c.
 * If the current runtime system of Rexx can fetch/define such a buffer
 * from somewhere without access to stack variables in GCI_JUMP_GETVAR, this
 * may be omitted.
 */
#define GCI_JUMPVAR(name)

/*
 * GCI_JUMP_GETVAR is a macro which returns a longjmp suitable jmp_buf without
 * accessing the stack.
 */
#define GCI_JUMP_GETVAR(name) __regina_get_tsd()->gci_jump

/*
 * GCI_JUMP_SETVAR is a macro which sets a longjmp suitable jmp_buf
 * to a reenterable state.
 * This function must block each other thread from entering GCI_JUMP_SETVAR
 * until GCI_JUMP is issued.
 */
#define GCI_JUMP_SETVAR(hidden,name) setjmp( ((tsd_t *) (hidden))->gci_jump )

/*
 * GCI_JUMP is a macro which does a longjmp to a place you may taken from
 * the argument to GCI_JUMP, but keep in mind that it MUST be static and
 * isn't taken from the stack.
 * This macro unblocks the lock that GCI_JUMP_SETVAR has created in
 * multi-threading systems.
 */
#define GCI_JUMP(jumpentry,status) longjmp( jumpentry, status )

/*
 * Regina has some special function in gci_reginabridge.c.
 */
int GCI_Dispatcher( tsd_t *TSD,
                    PFN func,
                    void *treeinfo,
                    int Params,
                    const PRXSTRING params,
                    PRXSTRING retstr );

int GCI_checkDefinition( tsd_t *TSD,
                         const streng *stem_name,
                         void **tree );
