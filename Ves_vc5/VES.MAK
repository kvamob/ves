.AUTODEPEND

.PATH.obj = F:\USER\VEZ\WIN

#		*Translator Definitions*
CC = bcc +VES.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = F:\BC\LIB
INCLUDEPATH = F:\BC\INCLUDE


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
 ves_solv.obj \
 ..\..\..\bc\lib\bwcc.lib \
 ves_gr.obj \
 ves.obj \
 ves_dlg.obj \
 ves.def \
 ves_io.obj \
 ves.res

#		*Explicit Rules*
f:\user\vez\win\ves.exe: ves.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/Twe/L$(LIBPATH) @&&|
c0wm.obj+
f:\user\vez\win\ves_solv.obj+
f:\user\vez\win\ves_gr.obj+
f:\user\vez\win\ves.obj+
f:\user\vez\win\ves_dlg.obj+
f:\user\vez\win\ves_io.obj
f:\user\vez\win\ves
		# no map file
..\..\..\bc\lib\bwcc.lib+
mathwm.lib+
import.lib+
cwm.lib
ves.def
|
  RC -k ves.res f:\user\vez\win\ves.exe


#		*Individual File Dependencies*
ves_solv.obj: ves.cfg ves_solv.c 

ves_gr.obj: ves.cfg ves_gr.c 

ves.obj: ves.cfg ves.c 

ves_dlg.obj: ves.cfg ves_dlg.c 

ves_io.obj: ves.cfg ves_io.c 

#		*Compiler Configuration File*
ves.cfg: ves.mak
  copy &&|
-R
-mm
-3
-v
-W
-vi-
-H=VES.SYM
-wpro
-weas
-wpre
-nF:\USER\VEZ\WIN
-I$(INCLUDEPATH)
-L$(LIBPATH)
-P-.C
| ves.cfg


