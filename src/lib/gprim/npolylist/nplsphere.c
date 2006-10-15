/* Copyright (C) 2006 Claus-Justus Heine
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

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include "geom.h"
#include "create.h"
#include "npolylistP.h"
#include "sphere.h"

Geom *NPolyListSphere(NPolyList *npl,
		      Transform T, TransformN *TN, int *axes,
		      int space)
{
  Geom *sphere;

  /* Create a dummy sphere, the center will be corrected later */
  sphere = GeomCreate("sphere", CR_SPACE, space, CR_END);
    
  SphereEncompassPoints((Sphere *)sphere,
			npl->v, npl->pdim-1, npl->pdim, npl->n_verts,
			T, TN, axes);

  return sphere;
}
