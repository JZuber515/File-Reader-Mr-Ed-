#
# Created by gmakemake (Ubuntu Sep  7 2011) on Tue Apr 15 18:18:05 2014
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -ggdb -Wall -std=c99

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	dlList.c mrEd.c test.c testdlList.c testdlList2.c testdllist.c
PS_FILES =	
S_FILES =	
H_FILES =	dlList.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	dlList.o 

#
# Main targets
#

all:	mrEd test testdlList testdlList2 testdllist 

mrEd:	mrEd.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mrEd mrEd.o $(OBJFILES) $(CLIBFLAGS)

test:	test.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test test.o $(OBJFILES) $(CLIBFLAGS)

testdlList:	testdlList.o $(OBJFILES)
	$(CC) $(CFLAGS) -o testdlList testdlList.o $(OBJFILES) $(CLIBFLAGS)

testdlList2:	testdlList2.o $(OBJFILES)
	$(CC) $(CFLAGS) -o testdlList2 testdlList2.o $(OBJFILES) $(CLIBFLAGS)

testdllist:	testdllist.o $(OBJFILES)
	$(CC) $(CFLAGS) -o testdllist testdllist.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

dlList.o:	dlList.h
mrEd.o:	dlList.h
test.o:	
testdlList.o:	dlList.h
testdlList2.o:	dlList.h
testdllist.o:	dlList.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) mrEd.o test.o testdlList.o testdlList2.o testdllist.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf mrEd test testdlList testdlList2 testdllist 
