##############################################################################
#
#    file                 : Makefile
#    created              : Fri Mai 14 16:21:01 CET 2010
#    copyright            : (C) 2010 by Bernhard Wymann
#    email                : berniw@bluewin.ch 
#    version              : $Id$
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################


WHEEL     = wheel

DATADIR   = wheels/trb1-5

DATA      = wheel3d.png  readme.txt \
            $(shell find *.acc -maxdepth 0 -type f -print)

data_PKGFILES	= $(DATA) $(shell find *.xcf -maxdepth 0 -type f -print)

data_PKGDIR	= $(DATADIR)

include ${MAKE_DEFAULT}
