dnl Copyright (C) 1988 Eleftherios Gkioulekas <lf@amath.washington.edu>
dnl  
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software 
dnl Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
dnl 
dnl As a special exception to the GNU General Public License, if you 
dnl distribute this file as part of a program that contains a configuration 
dnl script generated by Autoconf, you may include it under the same 
dnl distribution terms that you use for the rest of that program.
 
# ------------------------------------------------------------------------
# The following macro is useful for deep packages. It allows you to
# link all the header files *.h under a certain set of directories
# to be linked under an include directory from the toplevel.
# To use this feature in your configure.in call:
#   LF_LINK_HEADERS(dir1 dir2 dir3 .... , [directory] )
# where directory -> put links under include/directory
#       dir1 ...  -> the directories with header files we want to link
# WARNING: This macro will do  --> rm -rf include
# ------------------------------------------------------------------------

AC_DEFUN(LF_LINK_HEADERS,[
  # Find out how to link files if we haven't already
  if test -z "$LN_S"
  then
    AC_PROG_LN_S
  fi

  # Remove the include directory if we haven't done that yet
  if test -z "$lf_link_headers"
  then
    lf_link_headers="we are all Kosh"
    rm -rf "$srcdir/include"
  fi

  # Get the directory from the second argument which is optional
  ifelse([$2], ,  
         [lf_directory="$srcdir/include"] , 
         [lf_directory="$srcdir/include/$2"])
  ${srcdir}/mkinstalldirs "$lf_directory"

  # Link them
  lf_subdirs="`echo $1`"
  for lf_dir in $lf_subdirs
  do
    # Otherwise go ahead and link
    echo "linking headers from $srcdir/$lf_dir"
    # Check if the Headers file exists
    if test -f "$srcdir/$lf_dir/Headers"
    then
      for lf_file in `(cd $srcdir/$lf_dir; cat Headers)`
      do
        rm -f $lf_directory/$lf_file
        $LN_S "`pwd`/$srcdir/$lf_dir/$lf_file" "$lf_directory/$lf_file"
      done
    else
      echo "Warning: No Headers file for $srcdir/$lf_dir"
    fi
  done
])

# --------------------------------------------------------------------------
# The following macro is useful for deep packages. 
# To use it in your configure.in call
#   LF_SET_INCLUDES(dir1 dir2 dir3 ...)
# and in your Makefile.am set
#   @default-includes@
# Then this symbol will be substituted with
#   INCLUDES = -I$(prefix) -I$(top_builddir)/include/dir1 ...
# The prefix entry will be skipped if the prefix is equal to /usr/local
# or /usr
# --------------------------------------------------------------------------

AC_DEFUN(LF_SET_INCLUDES,[
  # See whether to put an entry for the prefix
  if test "$prefix" = "/usr" || test "$prefix" = "/usr/local"
  then
    default_includes=""
  else
    default_includes="-I\$(prefix) "
  fi

  # Get the directory list
  lf_dirs="`echo $1`"
  
  # Check whether we have a lib directory. If so put it in
  AC_MSG_CHECKING([whether sources have a lib directory])
  if test -d "`pwd`/$srcdir/lib"
  then
    AC_MSG_RESULT([yes])
    default_includes="$default_includes -I\$(top_srcdir)/lib"
  else
    AC_MSG_RESULT([no])
  fi

  # Now add in the directories. If the list is empty then just add include/
  # If the list is not empty then add the subdirectories.
  if test -z "$lf_dirs"
  then
    default_includes="$default_includes -I\$(top_srcdir)/include"
  else
    for lf_dir in $lf_dirs
    do
      default_includes="$default_includes -I\$(top_srcdir)/include/$lf_dir"
    done
  fi

  # And that's it
  AC_SUBST(default_includes)
])
