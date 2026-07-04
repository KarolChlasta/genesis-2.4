# $Id: macros.make.in,v 1.3 2005/08/04 20:10:53 svitak Exp $

# The purpose of this file is to contain common make(1) macros.
# It should be processed by every execution of that utility.


# POSIX shell.  Shouldn't be necessary -- but is under IRIX 5.3.
SHELL		= /bin/sh


# Installation Directories:
prefix		= .
exec_prefix	= $(prefix)
INCDIR		= $(exec_prefix)/include
LIBDIR		= $(exec_prefix)/lib
BINDIR		= $(exec_prefix)/bin
MANDIR		= $(prefix)/man


# Preprocessing:
M4		= m4
M4FLAGS		= -B10000
CPP		= cpp -P
CPPFLAGS	= $(INCLUDES) $(DEFINES) -DNDEBUG
FPP		= cpp -P
FPPFLAGS	= 
CXXCPPFLAGS	= $(CPPFLAGS)


# Compilation:
CC		= gcc
CXX		= 
FC		= 
CFLAGS		= -O2 -D__NO_MATH_INLINES -DLONGWORDS -std=gnu89 -Wno-implicit-function-declaration -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-strict-prototypes -I/usr/lib/x86_64-linux-gnu/include -Dnetcdf -DFMT1 -DINCSPRNG -DNO_X
CXXFLAGS	= $(CFLAGS) 
FFLAGS		= -O
CC_MAKEDEPEND	= false
COMPILE.c	= $(CC) -c $(CFLAGS) $(CPPFLAGS)
COMPILE.cxx	= $(CXX) -c $(CXXFLAGS) $(CXXCPPFLAGS)
COMPILE.f	= $(FC) -c $(FFLAGS)
# The following command isn't available on some systems; therefore, the
# `.F.o' rule is relatively complicated.
COMPILE.F	= 


# Linking:
MATHLIB		= 
FLIBS		=  
LIBS		= -lfl  -lm
LINK.c		= $(CC) -o $@ $(CFLAGS) $(LDFLAGS)
LINK.cxx	= $(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS)
LINK.F		= $(FC) -o $@ $(FFLAGS) $(FLDFLAGS)
LINK.f		= $(FC) -o $@ $(FFLAGS) $(FLDFLAGS)


# NetCDF files:
NCDUMP		= ncdump
NCGEN		= ncgen


# Manual pages:
WHATIS		= whatis
# The following macro should be empty on systems that don't
# allow users to create their own manual-page indexes.
MAKEWHATIS_CMD	= 


# Misc. Utilities:
AR		= ar
ARFLAGS		= cru	# NB: SunOS 4 doesn't like `-' option prefix
RANLIB		= ranlib
TARFLAGS	= -chf


# Dummy macros: used only as placeholders to silence GNU make.  They are
# redefined, as necessary, in subdirectory makefiles.
HEADER		= dummy_header
HEADER1		= dummy_header1
HEADER2		= dummy_header2
LIBRARY		= dummy_library.a
MANUAL		= dummy_manual
PROGRAM		= dummy_program


# Distribution macros:
FTPDIR		= /tmp/netcdf-ftp
FTPBINDIR	= /tmp/netcdf-ftp/binary
VERSION		= dummy_version
