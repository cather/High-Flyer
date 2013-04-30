#############################################################################
# Makefile for building: game_catherhj
# Generated by qmake (2.01a) (Qt 4.8.1) on: Mon Apr 29 21:25:44 2013
# Project:  game_catherhj.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile game_catherhj.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = alien.cpp \
		clickscene.cpp \
		laser.cpp \
		main.cpp \
		mainwindow.cpp \
		mainwindow_constructor.cpp \
		meteor.cpp \
		missile.cpp \
		planet.cpp \
		rocket.cpp \
		star.cpp \
		thing.cpp moc_mainwindow.cpp
OBJECTS       = alien.o \
		clickscene.o \
		laser.o \
		main.o \
		mainwindow.o \
		mainwindow_constructor.o \
		meteor.o \
		missile.o \
		planet.o \
		rocket.o \
		star.o \
		thing.o \
		moc_mainwindow.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		game_catherhj.pro
QMAKE_TARGET  = game_catherhj
DESTDIR       = 
TARGET        = game_catherhj

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: game_catherhj.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile game_catherhj.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile game_catherhj.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/game_catherhj1.0.0 || $(MKDIR) .tmp/game_catherhj1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/game_catherhj1.0.0/ && $(COPY_FILE) --parents alien.h clickscene.h laser.h mainwindow.h meteor.h missile.h mylist.h planet.h rocket.h star.h thing.h .tmp/game_catherhj1.0.0/ && $(COPY_FILE) --parents alien.cpp clickscene.cpp laser.cpp main.cpp mainwindow.cpp mainwindow_constructor.cpp meteor.cpp missile.cpp planet.cpp rocket.cpp star.cpp thing.cpp .tmp/game_catherhj1.0.0/ && (cd `dirname .tmp/game_catherhj1.0.0` && $(TAR) game_catherhj1.0.0.tar game_catherhj1.0.0 && $(COMPRESS) game_catherhj1.0.0.tar) && $(MOVE) `dirname .tmp/game_catherhj1.0.0`/game_catherhj1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/game_catherhj1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp
moc_mainwindow.cpp: clickscene.h \
		mainwindow.h \
		thing.h \
		rocket.h \
		laser.h \
		alien.h \
		missile.h \
		meteor.h \
		planet.h \
		star.h \
		mylist.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

alien.o: alien.cpp alien.h \
		thing.h \
		missile.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o alien.o alien.cpp

clickscene.o: clickscene.cpp clickscene.h \
		mainwindow.h \
		thing.h \
		rocket.h \
		laser.h \
		alien.h \
		missile.h \
		meteor.h \
		planet.h \
		star.h \
		mylist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o clickscene.o clickscene.cpp

laser.o: laser.cpp laser.h \
		thing.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o laser.o laser.cpp

main.o: main.cpp mainwindow.h \
		clickscene.h \
		thing.h \
		rocket.h \
		laser.h \
		alien.h \
		missile.h \
		meteor.h \
		planet.h \
		star.h \
		mylist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		clickscene.h \
		thing.h \
		rocket.h \
		laser.h \
		alien.h \
		missile.h \
		meteor.h \
		planet.h \
		star.h \
		mylist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

mainwindow_constructor.o: mainwindow_constructor.cpp mainwindow.h \
		clickscene.h \
		thing.h \
		rocket.h \
		laser.h \
		alien.h \
		missile.h \
		meteor.h \
		planet.h \
		star.h \
		mylist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow_constructor.o mainwindow_constructor.cpp

meteor.o: meteor.cpp meteor.h \
		thing.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o meteor.o meteor.cpp

missile.o: missile.cpp missile.h \
		thing.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o missile.o missile.cpp

planet.o: planet.cpp planet.h \
		thing.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o planet.o planet.cpp

rocket.o: rocket.cpp rocket.h \
		thing.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rocket.o rocket.cpp

star.o: star.cpp star.h \
		thing.h \
		rocket.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o star.o star.cpp

thing.o: thing.cpp thing.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o thing.o thing.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

