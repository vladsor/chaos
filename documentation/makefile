# $Id: makefile,v 1.1.1.1 2000/09/26 19:08:06 plundis Exp $

DSSSL_FILE = /usr/lib/sgml/stylesheet/dsssl/docbook/nwalsh/print/docbook.dsl
TARGETS = coding-standards.pdf filesystem-hierarchy.pdf installation.pdf

all: $(TARGETS)

%.pdf: %.sgml
	jade -t tex -d $(DSSSL_FILE) $<
	pdfjadetex $(*F).tex
	rm $(*F).tex
