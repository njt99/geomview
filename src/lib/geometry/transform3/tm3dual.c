/* Copyright (C) 1992-1998 The Geometry Center
 * Copyright (C) 1998-2000 Stuart Levy, Tamara Munzner, Mark Phillips
 *
 * This file is part of Geomview.
 * 
 * Geomview is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * Geomview is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with Geomview; see the file COPYING.  If not, write
 * to the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,
 * USA, or visit http://www.gnu.org.
 */

#if defined(HAVE_CONFIG_H) && !defined(CONFIG_H_INCLUDED)
#include "config.h"
#endif

static char copyright[] = "Copyright (C) 1992-1998 The Geometry Center\n\
Copyright (C) 1998-2000 Stuart Levy, Tamara Munzner, Mark Phillips";


/* Authors: Charlie Gunn, Pat Hanrahan, Stuart Levy, Tamara Munzner, Mark Phillips */

#include "transform3.h"

/*-----------------------------------------------------------------------
 * Function:	Tm3Dual
 * Description:	compute the dual of a matrix
 * Args:	T: the matrix to compute the dual of (INPUT)
 *		Tdual: the dual matrix (OUTPUT)
 * Returns:	nothing
 * Author:	mbp
 * Date:	Thu Aug  8 14:43:24 1991
 * Notes:	dual = transpose of adjoint matrix
 */
void
Tm3Dual( T, Tdual )
    Transform3 T, Tdual;
{
    Tm3Adjoint( T, Tdual );
    Tm3Transpose( Tdual, Tdual );
}

