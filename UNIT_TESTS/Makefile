# auto generated - do not edit

default: all

all:\
files/t2/t2.vlb mk-ctxt t_deinst1 t_deinst12 t_deinst2 t_inst1 t_inst2 \
t_instchk1 t_instchk2 t_instchkpre 

cc-compile:\
conf-cc conf-cctype conf-systype 

cc-compile-dl:\
cc-compile conf-dlflag 

cc-dlib:\
conf-ldtype conf-ld conf-sosuffix mk-libname 

cc-link:\
conf-ld conf-ldtype conf-systype 

cc-slib:\
conf-systype 

conf-cctype:\
conf-systype conf-cc mk-cctype 
	./mk-cctype > conf-cctype.tmp && mv conf-cctype.tmp conf-cctype

conf-dlflag:\
mk-dlflag 
	./mk-dlflag > conf-dlflag.tmp && mv conf-dlflag.tmp conf-dlflag

conf-ldtype:\
conf-systype conf-ld conf-cctype mk-ldtype 
	./mk-ldtype > conf-ldtype.tmp && mv conf-ldtype.tmp conf-ldtype

conf-sosuffix:\
mk-sosuffix 
	./mk-sosuffix > conf-sosuffix.tmp && mv conf-sosuffix.tmp \
	conf-sosuffix

conf-systype:\
mk-systype 
	./mk-systype > conf-systype.tmp && mv conf-systype.tmp conf-systype

files/t2/t2.o:\
cc-compile-dl files/t2/t2.c 
	./cc-compile-dl files/t2/t2.c

files/t2/t2.vlb:\
cc-dlib files/t2/t2.dld files/t2/t2.o 
	./cc-dlib files/t2/t2 files/t2/t2.o 

mk-cctype:\
conf-cc conf-systype 

mk-ctxt:\
cc-link mk-ctxt.ld mk-ctxt.o 
	./cc-link mk-ctxt mk-ctxt.o 

mk-ctxt.o:\
cc-compile mk-ctxt.c 
	./cc-compile mk-ctxt.c

mk-dlflag:\
conf-cctype conf-systype 

mk-ldtype:\
conf-cctype conf-systype 

mk-libname:\
conf-systype conf-sosuffix 

mk-mk-ctxt:\
conf-cc 

mk-sosuffix:\
conf-systype 

mk-systype:\
conf-cc 

t_deinst1:\
cc-link t_deinst1.ld t_deinst1.o t_inst1h.o ../install_core.o \
../install_error.o 
	./cc-link t_deinst1 t_deinst1.o t_inst1h.o ../install_core.o \
	../install_error.o 

t_deinst1.o:\
cc-compile t_deinst1.c ../install.h 
	./cc-compile t_deinst1.c

t_deinst12:\
cc-link t_deinst12.ld t_deinst12.o t_inst1h.o ../install_core.o \
../install_error.o 
	./cc-link t_deinst12 t_deinst12.o t_inst1h.o ../install_core.o \
	../install_error.o 

t_deinst12.o:\
cc-compile t_deinst12.c ../install.h 
	./cc-compile t_deinst12.c

t_deinst2:\
cc-link t_deinst2.ld t_deinst2.o t_inst2h.o ../install_core.o \
../install_error.o 
	./cc-link t_deinst2 t_deinst2.o t_inst2h.o ../install_core.o \
	../install_error.o 

t_deinst2.o:\
cc-compile t_deinst2.c ../install.h 
	./cc-compile t_deinst2.c

t_inst1:\
cc-link t_inst1.ld t_inst1.o t_inst1h.o ../install_core.o ../install_error.o 
	./cc-link t_inst1 t_inst1.o t_inst1h.o ../install_core.o \
	../install_error.o 

t_inst1.o:\
cc-compile t_inst1.c ../install.h 
	./cc-compile t_inst1.c

t_inst1h.o:\
cc-compile t_inst1h.c ../install.h 
	./cc-compile t_inst1h.c

t_inst2:\
cc-link t_inst2.ld t_inst2.o t_inst2h.o ../install_core.o ../install_error.o 
	./cc-link t_inst2 t_inst2.o t_inst2h.o ../install_core.o \
	../install_error.o 

t_inst2.o:\
cc-compile t_inst2.c ../install.h 
	./cc-compile t_inst2.c

t_inst2h.o:\
cc-compile t_inst2h.c ../install.h 
	./cc-compile t_inst2h.c

t_instchk1:\
cc-link t_instchk1.ld t_instchk1.o t_inst1h.o ../install_core.o \
../install_error.o 
	./cc-link t_instchk1 t_instchk1.o t_inst1h.o ../install_core.o \
	../install_error.o 

t_instchk1.o:\
cc-compile t_instchk1.c ../install.h 
	./cc-compile t_instchk1.c

t_instchk2:\
cc-link t_instchk2.ld t_instchk2.o t_inst2h.o ../install_core.o \
../install_error.o 
	./cc-link t_instchk2 t_instchk2.o t_inst2h.o ../install_core.o \
	../install_error.o 

t_instchk2.o:\
cc-compile t_instchk2.c ../install.h 
	./cc-compile t_instchk2.c

t_instchkpre:\
cc-link t_instchkpre.ld t_instchkpre.o t_inst1h.o ../install_core.o \
../install_error.o 
	./cc-link t_instchkpre t_instchkpre.o t_inst1h.o ../install_core.o \
	../install_error.o 

t_instchkpre.o:\
cc-compile t_instchkpre.c ../install.h 
	./cc-compile t_instchkpre.c

clean-all: tests_clean obj_clean 
clean: obj_clean
obj_clean: 
	rm -f conf-cctype conf-ldtype conf-systype files/t2/t2.o `cat \
	files/t2/t2.vlb` files/t2/t2.vlb mk-ctxt mk-ctxt.o t_deinst1 \
	t_deinst1.o t_deinst12 t_deinst12.o t_deinst2 t_deinst2.o t_inst1 \
	t_inst1.o t_inst1h.o t_inst2 t_inst2.o t_inst2h.o t_instchk1 \
	t_instchk1.o t_instchk2 t_instchk2.o t_instchkpre t_instchkpre.o 

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
	cpj-genmk > Makefile.tmp && mv Makefile.tmp Makefile

