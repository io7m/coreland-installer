# auto generated - do not edit
# cpj-genmk-0.78

SHELL=/bin/sh
default: all
all: phase_tools phase_compile phase_library phase_link 

tests: phase_test 

clean: phase_tools_clean phase_compile_clean phase_library_clean \
	phase_link_clean phase_test_clean 


#--TOOLS----------------------------------------------------------------------

phase_tools:  mkftools
phase_tools_clean:  mkftools_clean

#--COMPILE--------------------------------------------------------------------

t_deinst1.o:\
	compile t_deinst1.c ../install.h 
	./compile t_deinst1 t_deinst1.c 
t_deinst12.o:\
	compile t_deinst12.c ../install.h 
	./compile t_deinst12 t_deinst12.c 
t_deinst2.o:\
	compile t_deinst2.c ../install.h 
	./compile t_deinst2 t_deinst2.c 
t_inst1.o:\
	compile t_inst1.c ../install.h 
	./compile t_inst1 t_inst1.c 
t_inst1h.o:\
	compile t_inst1h.c ../install.h 
	./compile t_inst1h t_inst1h.c 
t_inst2.o:\
	compile t_inst2.c ../install.h 
	./compile t_inst2 t_inst2.c 
t_inst2h.o:\
	compile t_inst2h.c ../install.h 
	./compile t_inst2h t_inst2h.c 
t_instchk1.o:\
	compile t_instchk1.c ../install.h 
	./compile t_instchk1 t_instchk1.c 
t_instchk2.o:\
	compile t_instchk2.c ../install.h 
	./compile t_instchk2 t_instchk2.c 
t_instchkpre.o:\
	compile t_instchkpre.c ../install.h 
	./compile t_instchkpre t_instchkpre.c 
files/t2/t2.o:\
	compile files/t2/t2.c 
	./compile files/t2/t2 files/t2/t2.c 

phase_compile:\
	t_deinst1.o t_deinst12.o t_deinst2.o t_inst1.o t_inst1h.o t_inst2.o \
	t_inst2h.o t_instchk1.o t_instchk2.o t_instchkpre.o files/t2/t2.o 
phase_compile_clean:
	rm -f t_deinst1.o t_deinst12.o t_deinst2.o t_inst1.o t_inst1h.o \
	t_inst2.o t_inst2h.o t_instchk1.o t_instchk2.o t_instchkpre.o \
	files/t2/t2.o 

#--LIBRARY--------------------------------------------------------------------

files/t2/t2.lib:\
	makeso files/t2/t2.dld files/t2/t2.o 
	./makeso files/t2/t2 files/t2/t2.o 

phase_library:\
	files/t2/t2.lib 
phase_library_clean:
	rm -f `cat files/t2/t2.lib` files/t2/t2.lib 

#--LINK-----------------------------------------------------------------------

t_deinst1:\
	link t_deinst1.ld t_deinst1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_deinst1 t_deinst1.o t_inst1h.o ../install.o \
	../install_error.o 
t_deinst12:\
	link t_deinst12.ld t_deinst12.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_deinst12 t_deinst12.o t_inst1h.o ../install.o \
	../install_error.o 
t_deinst2:\
	link t_deinst2.ld t_deinst2.o t_inst2h.o ../install.o \
	../install_error.o 
	./link t_deinst2 t_deinst2.o t_inst2h.o ../install.o \
	../install_error.o 
t_inst1:\
	link t_inst1.ld t_inst1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_inst1 t_inst1.o t_inst1h.o ../install.o ../install_error.o 
t_inst2:\
	link t_inst2.ld t_inst2.o t_inst2h.o ../install.o \
	../install_error.o 
	./link t_inst2 t_inst2.o t_inst2h.o ../install.o ../install_error.o 
t_instchk1:\
	link t_instchk1.ld t_instchk1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_instchk1 t_instchk1.o t_inst1h.o ../install.o \
	../install_error.o 
t_instchk2:\
	link t_instchk2.ld t_instchk2.o t_inst2h.o ../install.o \
	../install_error.o 
	./link t_instchk2 t_instchk2.o t_inst2h.o ../install.o \
	../install_error.o 
t_instchkpre:\
	link t_instchkpre.ld t_instchkpre.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_instchkpre t_instchkpre.o t_inst1h.o ../install.o \
	../install_error.o 

phase_link:\
	t_deinst1 t_deinst12 t_deinst2 t_inst1 t_inst2 t_instchk1 \
	t_instchk2 t_instchkpre 
phase_link_clean:
	rm -f t_deinst1 t_deinst12 t_deinst2 t_inst1 t_inst2 t_instchk1 \
	t_instchk2 t_instchkpre 

#--TEST-----------------------------------------------------------------------

phase_test: inst-check inst-copy inst-dir inst-link

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

tests: run-tests.sh
	./run-tests.sh

phase_test_clean:
	rm -f t_inst1.out

#--TOOLS----------------------------------------------------------------------

mkftools: compile makelib libname makeso link sosuffix 
compile: conf-shebang conf-cc make-compile 
	(cat conf-shebang; ./make-compile) > compile; chmod u+x compile;
link: conf-shebang conf-ld make-link 
	(cat conf-shebang; ./make-link) > link; chmod u+x link;
makelib: conf-shebang make-makelib 
	(cat conf-shebang; ./make-makelib) > makelib; chmod u+x makelib;
makeso: conf-shebang libname make-makeso 
	(cat conf-shebang; ./make-makeso) > makeso; chmod u+x makeso;
libname: conf-shebang make-libname 
	(cat conf-shebang; ./make-libname) > libname; chmod u+x libname;
sosuffix: conf-shebang libname make-sosuffix 
	(cat conf-shebang; ./make-sosuffix) > sosuffix; chmod u+x sosuffix;
mkftools_clean: 
	 rm -f compile makelib makeso libname link \
	sosuffix 
regen:
	cpj-genmk > Makefile.tmp
	mv Makefile.tmp Makefile
