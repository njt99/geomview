PSIMAGES = figs/ap.ps figs/command.ps figs/light.ps figs/mat.ps\
 figs/secondlinelist.ps figs/cam.ps figs/fig2.ps figs/load.ps\
 figs/myfilelist.ps figs/tools.ps figs/color.ps figs/initial.ps\
 figs/main.ps figs/save.ps figs/trefdodecinter.ps
EPSIMAGES = $(PSIMAGES:.ps=.eps)
PDFIMAGES = $(PSIMAGES:.ps=.pdf)
PNGIMAGES = $(PSIMAGES:.ps=.png)

LANGUAGES = "" "-pt_BR"

man_MANS = geomview.5gv lisp.3gv oogl.5gv

EXTRA_DIST = geomview.pdf geomview.html\
  geomview-pt_BR.pdf geomview-pt_BR.html\
  README README.gvplot oogltour oogltour-pt_BR\
  example1.c example2.c example3.c example4.tcl\
  OOGL.m.txt motion.tex $(man_MANS)\
  $(PSIMAGES) $(PNGIMAGES) $(PDFIMAGES) $(EPSIMAGES)\
  pt_BR/texinfo.tex pt_BR/acentos_texinfo.sh pt_BR/geomview_cvs.sh

AM_MAKEINFOFLAGS = --no-validate
info_TEXINFOS = geomview.texi geomview-pt_BR.texi
infoimgdir = $(infodir)
nobase_infoimg_DATA = $(PNGIMAGES)

geomview_pt_BR_texi_MAKEINFOFLAGS = --enable-encoding --lang=pt_BR

dochtmldir = $(docdir)/html
doc_DATA = geomview.pdf geomview-pt_BR.pdf

geomview.pdf:  $(PDFIMAGES)
geomview.ps:   $(EPSIMAGES)
geomview.dvi:  $(EPSIMAGES)
geomview.html: $(PNGIMAGES)

geomview-pt_BR.pdf:  $(PDFIMAGES)
geomview-pt_BR.ps:   $(EPSIMAGES)
geomview-pt_BR.dvi:  $(EPSIMAGES)
geomview-pt_BR.html: $(PNGIMAGES)

TEXINPUTS = $(srcdir):.:
all-local: htdocs pdf

htdocs/*.html htdocs/figs/*.png: htdocs

htdocs: geomview.html geomview-pt_BR.html
	if test -d $@; then rm -rf $@; fi
	for loc in $(LANGUAGES); do \
	  if test -d $(srcdir)/geomview$${loc}.html; then \
            htmldir=$(srcdir)/geomview$${loc}.html; \
	  else \
            htmldir=geomview$${loc}.html; \
	  fi; \
	  loc2=`echo $${loc}|$(SED) -e 's/-//g'`; \
	  $(MKDIR_P) $@/$${loc2}; \
	  cp -R $${htmldir}/. $@/$${loc2}/.; \
	  $(MKDIR_P) $@/$${loc2}/figs; \
	  chmod 0755 $@/$${loc2}/figs; \
	  for f in $(PNGIMAGES); do \
	    test -f $(srcdir)/$$f && f=$(srcdir)/$$f; \
	    cp $$f $@/$${loc2}/figs/; \
	  done; \
	done; \
	chmod 0755 $@; \
	find $@ -type f -exec chmod 644 \{\} \;

install-data-local: htdocs
	$(MKDIR_P) $(DESTDIR)$(dochtmldir)
	cp -pR htdocs/. $(DESTDIR)$(dochtmldir)/.
	chmod 0755 $(DESTDIR)$(dochtmldir)
	find $(DESTDIR)$(dochtmldir) -type d -exec chmod 0755 \{\} \;
	find $(DESTDIR)$(dochtmldir) -type f -exec chmod 644 \{\} \;

uninstall-local:
	rm -rf $(DESTDIR)$(dochtmldir)

.ps.eps:
	@D=`dirname $@`; $(MKDIR_P) $$D
	$(PS2EPSI) $< $@

.eps.pdf:
	@D=`dirname $@`; $(MKDIR_P) $$D
	$(EPSTOPDF) $<

.pdf.png:
	$(MKDIR_P) figs
	$(PDFIMAGESPROG) $< $(<:.pdf=)
	$(PNMTOPNG) $(<:.pdf=-000.ppm) > $@
	-rm -f $(<:.pdf=-000.ppm)

# Anoyingly, automake includes XXX~ files into the distro, caused by a
# somewhat broken dist-info: target.
dist-hook: html pdf
	rm -rf `find $(distdir) -name '*~'`

MAINTAINERCLEANFILES = \
 $(PNGIMAGES) $(PDFIMAGES) $(EPSIMAGES) geomview.pdf geomview-pt_BR.pdf

distclean-local:
	-rm -rf htdocs

maintainerclean-local:
	-for loc in $(LANGUAGES); do rm -rf geomview$${loc}.html; done

#
# override to disable deletion of .pdf, .html by the user.
#
mostlyclean-aminfo:
	-for loc in $(LANGUAGES); do \
	  rm -rf \
	    geomview$${loc}.aux geomview$${loc}.cp geomview$${loc}.cps \
	    geomview$${loc}.fn geomview$${loc}.fns geomview$${loc}.ky \
	    geomview$${loc}.kys geomview$${loc}.log geomview$${loc}.pg \
	    geomview$${loc}.pgs geomview$${loc}.tmp geomview$${loc}.toc \
	    geomview$${loc}.tp geomview$${loc}.tps geomview$${loc}.vr \
	    geomview$${loc}.vrs geomview$${loc}.dvi geomview$${loc}.ps ; \
	done
