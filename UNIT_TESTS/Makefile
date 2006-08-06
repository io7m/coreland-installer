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
t_inst1.o:\
	compile t_inst1.c ../install.h 
	./compile t_inst1 t_inst1.c 
t_inst1h.o:\
	compile t_inst1h.c ../install.h 
	./compile t_inst1h t_inst1h.c 
t_instchk1.o:\
	compile t_instchk1.c ../install.h 
	./compile t_instchk1 t_instchk1.c 

phase_compile:\
	t_deinst1.o t_inst1.o t_inst1h.o t_instchk1.o 
phase_compile_clean:
	rm -f t_deinst1.o t_inst1.o t_inst1h.o t_instchk1.o 

#--LIBRARY--------------------------------------------------------------------


phase_library:
phase_library_clean:

#--LINK-----------------------------------------------------------------------

t_deinst1:\
	link t_deinst1.ld t_deinst1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_deinst1 t_deinst1.o t_inst1h.o ../install.o \
	../install_error.o 
t_inst1:\
	link t_inst1.ld t_inst1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_inst1 t_inst1.o t_inst1h.o ../install.o ../install_error.o 
t_instchk1:\
	link t_instchk1.ld t_instchk1.o t_inst1h.o ../install.o \
	../install_error.o 
	./link t_instchk1 t_instchk1.o t_inst1h.o ../install.o \
	../install_error.o 

phase_link:\
	t_deinst1 t_inst1 t_instchk1 
phase_link_clean:
	rm -f t_deinst1 t_inst1 t_instchk1 

#--TEST-----------------------------------------------------------------------

phase_test: inst-check inst-copy inst-dir inst-link success

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

success:
	@echo 'The software passed all tests.'

phase_test_clean:

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
