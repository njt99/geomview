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


/* Authors: Charlie Gunn, Stuart Levy, Tamara Munzner, Mark Phillips */

#ifndef DISCGRPDEF
#define DISCGRPDEF

#include "bbox.h"
#include "dgflag.h"
#include "create.h"
#include "appearance.h"
#include "pick.h"
#include "streampool.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef	FALSE
#define	FALSE 0
#endif

#define DISCGRPMAGIC	GeomMagic('d',1)

typedef struct DiscGrp DiscGrp ;

extern DiscGrp	*DiscGrpPick( DiscGrp *, Pick *, Appearance *, Transform );
extern GeomClass *DiscGrpMethods( void );
extern char	*DiscGrpName( void );
/*
extern DiscGrp	*DiscGrpFLoad( FILE *, char * );
extern DiscGrp	*DiscGrpLoad( char * );
*/
extern Geom  *DiscGrpImport (Pool * );
extern DiscGrp	*DiscGrpSave( DiscGrp *, char * );
extern DiscGrp	*DiscGrpFSave( DiscGrp *, FILE *, char * );
extern BBox	*DiscGrpBound( DiscGrp *, Transform );
extern DiscGrp	*DiscGrpDraw( DiscGrp * );
/*
extern DiscGrpElList *DiscGrpElListCreate(DiscGrpElList *, ...);
extern DiscGrp	*DiscGrpEvert( DiscGrp * );
extern DiscGrp     *DiscGrpTransform( DiscGrp *, Transform );
extern DiscGrp     *DiscGrpTransformTo( DiscGrp *, Transform );
*/

/* tokens used by the create routines, not duplicated in create.h */
/* we'll use the '900' region: this ought to be registered somewhere */
/* DGELC == DiscGrpElListCreate
   DGC == DiscGrpCreate
*/
#define 	DGCR_ATTRIBUTE	900	/* int : attributes in both DGC and DGELC */
#define 	DGCR_ATTRIBUTELIST 901	/* int * : list of attributes in DGELC */
#define 	DGCR_WORD	902	/* char (*)[DG_WORDLENGTH] : used by DiscGrpElListCreate */
#define		DGCR_ELEM	903	/* DiscGrpEl * : used in DGELC  */
					/* note that CR_ELEM is also used here */
#define		DGCR_CPOINT	905	/* HPoint3 * :base  point of dirichlet domain: */
#define		DGCR_CAMGEOM	906	/* Geom * :geometry used to represent the observer*/
#define		DGCR_DDGEOM	907	/* Geom * :geometry for Dirichlet domain */
#define 	DGCR_GENS	908	/* DiscGrpElList * : generators */
#define 	DGCR_BIGLIST	910	/* DiscGrpElList * : general list */
#define 	DGCR_ENUMDEPTH	911	/* int : depth to compute wordlist */
#define 	DGCR_ENUMDIST	912	/* float : maximum distance of tiles */
#define 	DGCR_SCALE	913	/* float : scaling factor for dirdom */
#define 	DGCR_FLAG	914	/* the flag field of the DiscGrp */
#define 	DGCR_NAME	915	/* the flag field of the DiscGrp */
#define 	DGCR_COMMENT	916	/* the flag field of the DiscGrp */

#endif /*DISCGRPDEF*/
