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
/*
 * plutil.h
 * author:  Celeste Fowler
 * date:  June 12, 1992
 */

#ifndef PLUTIL_H
#define PLUTIL_H

typedef struct _PLData PLData;

Geom *PLCombine(Geom *a1, Geom *b1);
Geom *AnyToPL(Geom *old, Transform T);
Geom *PLConsol(Geom *g, float prec);

/* Anyone wanting to use this entry point must #include "transformn.h" first */
#ifdef TRANSFORMNDEF
PLData *AnyGeomToPLData(Geom *old, Transform T, TransformN *Tn, Appearance *ap, PLData *pd);
Geom *PLDataToGeom(PLData *pd, int want, int unwant);

#define PL_C            0x1	/* Bits for "want" and "unwant" flags. */
#define PL_N            0x2
#define PL_H            0x4
#define PL_ND           0x8

#endif

#endif /* PLUTIL_H */
