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

#include "mibload.h"
#include "mibwidgets.h"

extern Display	*dpy;
extern GC	 mib_gc;

/* Code for ScrollBars */
/*****************************************************************************/

mib_Widget *mib_create_ScrollBar(mib_Widget *parent, char *name, char *orient,
		int posx, int posy, int width, int height, int mib_fill)
{
  mib_Widget	*temp;
  mib_ScrollBar *myres;
  Arg		 args[20];
  int		 n;

  /* create the new widget and add it to the tree */

  temp = mib_new_mib_Widget();
  if (mib_fill == WDEFAULT)
    mib_add_backward(temp, parent);
  else
    mib_add_mib_Widget(temp, parent);

  myres = (mib_ScrollBar *)malloc(sizeof(mib_ScrollBar));

  /* initialize public resources */

  if (mib_fill == WDEFAULT)
  {
    temp->name = (char *)malloc(strlen(name)+1);
    strcpy(temp->name,name);
  }
  temp->mib_class = (char *)malloc(10);
  sprintf(temp->mib_class,"ScrollBar");
  temp->mib_class_num = MIB_SCROLLBAR;
  temp->width = width;
  temp->height = height;
  temp->topOffset = posy;
  temp->leftOffset = posx;
  temp->bottomOffset = 0;
  temp->rightOffset = 0;
  temp->topAttachment = 1;
  temp->leftAttachment = 1;
  temp->bottomAttachment = 0;
  temp->rightAttachment = 0;

  temp->mib_allowresize = 1;

  /* initialize private resources */

  temp->myres = (void *)myres;
  myres->orientation = 0;

  /* create Xt widget */

  n = 0;

  if (mib_fill == WDEFAULT)
  {
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
    XtSetArg (args[n], XmNleftOffset, posx);n++;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg (args[n], XmNtopOffset, posy);n++;
    XtSetArg (args[n], XmNwidth, width); n++;
    XtSetArg (args[n], XmNheight, height); n++;
  }

  XtSetArg (args[n], XmNrubberPositioning, False); n++;

  if ((mib_fill == WDEFAULT)) {
    if (!strcmp("VertScrollBar",orient))
      {
	XtSetArg (args[n], XmNorientation, XmVERTICAL); n++;
      } else {
	if (!strcmp("HorzScrollBar",orient))
	  {
	    XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
	    myres->orientation = 1;
	  }
      }
  }

  temp->me = XtCreateManagedWidget(name, xmScrollBarWidgetClass,
                temp->parent->me, args, n);

  if (mib_fill == WEDIT || mib_fill == WDEFAULT)
  {
    mib_apply_eventhandlers(temp->me, temp);
  }

  return temp;
}

void mib_delete_ScrollBar(mib_Widget *this)
{
  mib_ScrollBar *temp = (mib_ScrollBar *)this->myres;

  free(temp);
}

void mib_save_ScrollBar(mib_Widget *this, FILE *fout)
{
  mib_ScrollBar *temp = (mib_ScrollBar *)this->myres;

  fprintf(fout,"orientation: %d\\n\\\n", temp->orientation);
}

int mib_load_ScrollBar(mib_Widget *this, mib_Buffer *fin)
{
  mib_ScrollBar *myres;
  unsigned char *label_text;
  char          res[MI_MAXSTRLEN];
  char          val[MI_MAXSTRLEN];
  Arg           args[5];
  int           n;

  myres = (mib_ScrollBar *)this->myres;

  if (!mib_read_line(fin, res, val))
    return 0;

  if (!strcmp(res,"orientation"))
  {
    sscanf(val,"%d",&(myres->orientation));

    n = 0;
    switch (myres->orientation) {
        case 0:
        XtSetArg (args[n], XmNorientation, XmVERTICAL); n++;
        break;
        case 1:
        XtSetArg (args[n], XmNorientation, XmHORIZONTAL); n++;
        break;
        default:
        break;
    }
    XtSetValues(this->me, args, n);
  }
  else
    return 0;

  if (!mib_read_line(fin, res, val))
    return 0;

  if (strcmp(res,"EndWidget"))
    return 0;

  return 1;
}
