/* Copyright (C) 1992-1998 The Geometry Center
 * Copyright (C) 1998-2000 Geometry Technologies, Inc.
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

static char copyright[] = "Copyright (C) 1992-1998 The Geometry Center\n\
Copyright (C) 1998-2000 Geometry Technologies, Inc.";

/*
 *      file:   main.c:   
 *      author: Charlie Gunn & Tamara Munzner
 *      date:   September 1, 1992
 *      
 *      simple example of geomview external module and
 *	OOGL graphics library routines.
 *
 *      The main program continually computes a function on a mesh of
 *      (x,y) pairs.  The updated mesh is printed to stdout. When this
 *	program is invoked as a geomview external module, pipes are hooked
 * 	up 
 */

#include <math.h>
#include <stdio.h>
#include "forms.h"
#include "xforms-compat.h"
#include "panel.h"
#include "ooglutil.h"

float dt;


/* replace this with your favorite function */
float
myfunc(x,y,t)
     float x,y,t;
{
        float r;
        r = sqrt(x*x+y*y) + .000001;
        return(sin(r + t)*sqrt(r));
}

main(argc, argv)        
     char **argv;
{
        int xdim, ydim, i, j;
        float xmin, xmax, ymin, ymax, xsize, ysize, dx, dy, x, y, t, zscale;
        float *data;
        
        xdim = 24;
        ydim = 24;
        xmin = -5;
        xmax = 5;
        ymin = -5;
        ymax = 5;
        zscale = 2.0;

	dt = .1; /* initial velocity */

	/* geomview communications setup. */

        Begin_OOGL();

#ifdef XFORMS
	FL_INITIALIZE("Example");
#else
	/* If we don't foreground then the process forks and dies
	   as soon as we do graphics. This is bad.
	 */
	foreground();
#endif
	/* This routine is defined in the code generated by 
	   the forms designer.
	 */

        create_the_forms();

	/* We set the slider and display the form. */

	fl_set_slider_bounds(VelocitySlider, 0.0, 1.0);
	fl_set_slider_value(VelocitySlider, dt);
	fl_show_form(Example, FL_PLACE_SIZE, TRUE, "Example");

        
        xsize = xmax-xmin;
        ysize = ymax-ymin;
        dx = xsize/(xdim-1);
        dy = ysize/(ydim-1);
        
        data = (float *) OOGLNewN(float, xdim * ydim);
        for (t=0; ; t += dt)
        {
	        /* Let forms library do its thing. */
	        fl_check_forms();

                /* compute mesh of some function value */
                for (j=0, y = -ysize/2; j<ydim; ++j, y += dy)
                {
                        for (i=0, x = -xsize/2; i<xdim; ++i, x += dx)
                        {
                                data[j*xdim + i] = myfunc(x,y,t);
                        }
                }
                
                /* geomview communications update */
                UpdateOOGL(xdim, ydim, zscale, data);
        }
	
}
