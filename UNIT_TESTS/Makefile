# auto generated - do not edit

default: all

all:\
	files/t2/t2.vlb t_deinst1 t_deinst12 t_deinst2 t_inst1 t_inst2 \
	t_instchk1 t_instchk2 t_instchkpre 

cc: ../cc conf-cctype conf-cc
	rm -f cc
	ln -s ../cc cc

cc-pic:\
	cc conf-picflag 
conf-cc: ../conf-cc
	rm -f conf-cc
	ln -s ../conf-cc conf-cc

conf-cctype: ../conf-cctype
	rm -f conf-cctype
	ln -s ../conf-cctype conf-cctype

conf-ld: ../conf-ld
	rm -f conf-ld
	ln -s ../conf-ld conf-ld

conf-ldtype:\
	conf-systype conf-ld conf-cctype mk-ldtype 
	./mk-ldtype > conf-ldtype
conf-picflag:\
	mk-picflag 
	./mk-picflag > conf-picflag
conf-sosuffix:\
	mk-sosuffix 
	./mk-sosuffix > conf-sosuffix
conf-systype: ../conf-systype
	rm -f conf-systype
	ln -s ../conf-systype conf-systype

files/t2/t2.o:\
	cc-pic files/t2/t2.c 
	./cc-pic files/t2/t2.c
files/t2/t2.vlb:\
	mk-dlib files/t2/t2.dld files/t2/t2.o 
	./mk-dlib files/t2/t2 files/t2/t2.o 
ld: ../ld conf-ld
	rm -f ld
	ln -s ../ld ld

mk-dlib:\
	conf-ldtype conf-ld conf-sosuffix mk-libname 
mk-ldtype:\
	conf-cctype conf-systype 
mk-libname:\
	conf-systype conf-sosuffix 
mk-picflag:\
	conf-cctype conf-systype 
mk-sosuffix: ../mk-sosuffix
	rm -f mk-sosuffix
	ln -s ../mk-sosuffix mk-sosuffix

t_deinst1:\
	ld t_deinst1.ld t_deinst1.o t_inst1h.o ../install_core.o \
	../install_error.o 
	./ld t_deinst1 t_deinst1.o t_inst1h.o ../install_core.o \
	../install_error.o 
t_deinst1.o:\
	cc t_deinst1.c ../install.h 
	./cc t_deinst1.c
t_deinst12:\
	ld t_deinst12.ld t_deinst12.o t_inst1h.o ../install_core.o \
	../install_error.o 
	./ld t_deinst12 t_deinst12.o t_inst1h.o ../install_core.o \
	../install_error.o 
t_deinst12.o:\
	cc t_deinst12.c ../install.h 
	./cc t_deinst12.c
t_deinst2:\
	ld t_deinst2.ld t_deinst2.o t_inst2h.o ../install_core.o \
	../install_error.o 
	./ld t_deinst2 t_deinst2.o t_inst2h.o ../install_core.o \
	../install_error.o 
t_deinst2.o:\
	cc t_deinst2.c ../install.h 
	./cc t_deinst2.c
t_inst1:\
	ld t_inst1.ld t_inst1.o t_inst1h.o ../install_core.o \
	../install_error.o 
	./ld t_inst1 t_inst1.o t_inst1h.o ../install_core.o \
	../install_error.o 
t_inst1.o:\
	cc t_inst1.c ../install.h 
	./cc t_inst1.c
t_inst1h.o:\
	cc t_inst1h.c ../install.h 
	./cc t_inst1h.c
t_inst2:\
	ld t_inst2.ld t_inst2.o t_inst2h.o ../install_core.o \
	../install_error.o 
	./ld t_inst2 t_inst2.o t_inst2h.o ../install_core.o \
	../install_error.o 
t_inst2.o:\
	cc t_inst2.c ../install.h 
	./cc t_inst2.c
t_inst2h.o:\
	cc t_inst2h.c ../install.h 
	./cc t_inst2h.c
t_instchk1:\
	ld t_instchk1.ld t_instchk1.o t_inst1h.o ../install_core.o \
	../install_error.o 
	./ld t_instchk1 t_instchk1.o t_inst1h.o ../install_core.o \
	../install_error.o 
t_instchk1.o:\
	cc t_instchk1.c ../install.h 
	./cc t_instchk1.c
t_instchk2:\
	ld t_instchk2.ld t_instchk2.o t_inst2h.o ../install_core.o \
	../install_error.o 
	./ld t_instchk2 t_instchk2.o t_inst2h.o ../install_core.o \
	../install_error.o 
t_instchk2.o:\
	cc t_instchk2.c ../install.h 
	./cc t_instchk2.c
t_instchkpre:\
	ld t_instchkpre.ld t_instchkpre.o t_inst1h.o ../install_core.o \
	../install_error.o 
	./ld t_instchkpre t_instchkpre.o t_inst1h.o ../install_core.o \
	../install_error.o 
t_instchkpre.o:\
	cc t_instchkpre.c ../install.h 
	./cc t_instchkpre.c
clean: tests_clean 
	rm -f cc conf-cc conf-cctype conf-ld conf-ldtype conf-picflag \
	conf-systype files/t2/t2.o `cat files/t2/t2.vlb` files/t2/t2.vlb ld \
	mk-sosuffix t_deinst1 t_deinst1.o t_deinst12 t_deinst12.o t_deinst2 \
	t_deinst2.o t_inst1 t_inst1.o t_inst1h.o t_inst2 t_inst2.o \
	t_inst2h.o t_instchk1 t_instchk1.o t_instchk2 t_instchk2.o \
	t_instchkpre t_instchkpre.o 

tests: inst-check inst-copy inst-dir inst-link run-tests.sh
	./run-tests.sh
tests_clean:
	rm -f t_inst1.out

inst-check: ../inst-check
	rm -f inst-check
	ln -s ../inst-check inst-check
inst-copy: ../inst-copy
	rm -f inst-copy
	ln -s ../inst-copy inst-copy
inst-dir: ../inst-dir
	rm -f inst-dir
	ln -s ../inst-dir inst-dir
inst-link: ../inst-link
	rm -f inst-link
	ln -s ../inst-link inst-link
regen:
	cpj-genmk > Makefile.tmp
	mv Makefile.tmp Makefile

