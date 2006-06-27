# auto generated - do not edit
# cpj-genmk-0.77

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
	compile t_deinst1.c ../buffer.h ../install.h ../syserr.h 
	./compile t_deinst1 t_deinst1.c 
t_inst1.o:\
	compile t_inst1.c ../buffer.h ../install.h ../syserr.h 
	./compile t_inst1 t_inst1.c 
t_inst1h.o:\
	compile t_inst1h.c ../install.h 
	./compile t_inst1h t_inst1h.c 
t_instc1.o:\
	compile t_instc1.c ../buffer.h ../fmt.h ../install.h ../syserr.h 
	./compile t_instc1 t_instc1.c 

phase_compile:\
	t_deinst1.o t_inst1.o t_inst1h.o t_instc1.o 
phase_compile_clean:
	rm -f t_deinst1.o t_inst1.o t_inst1h.o t_instc1.o 

#--LIBRARY--------------------------------------------------------------------


phase_library:
phase_library_clean:

#--LINK-----------------------------------------------------------------------

t_deinst1:\
	link t_deinst1.ld t_deinst1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 
	./link t_deinst1 t_deinst1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 
t_inst1:\
	link t_inst1.ld t_inst1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 
	./link t_inst1 t_inst1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 
t_instc1:\
	link t_instc1.ld t_instc1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 
	./link t_instc1 t_instc1.o ../install.o t_inst1h.o ../open.a \
	../syserr.a ../get_opt.a ../fmt.a ../buffer.a ../str.a ../bin.a \
	../error.a 

phase_link:\
	t_deinst1 t_inst1 t_instc1 
phase_link_clean:
	rm -f t_deinst1 t_inst1 t_instc1 

#--TEST-----------------------------------------------------------------------

phase_test: t_deinst1.out t_inst1.out t_instc1.out success

t_deinst1.out: t_deinst1.sh cmp.sh
	./t_deinst1.sh
	./cmp.sh t_deinst1

t_inst1.out: t_inst1.sh cmp.sh
	./t_inst1.sh
	./cmp.sh t_inst1

t_instc1.out: t_instc1.sh cmp.sh
	./t_instc1.sh
	./cmp.sh t_instc1

success:
	@echo 'The software passed all tests.'

phase_test_clean:
	rm -f t_deinst1.out t_inst1.out t_instc1.out

#--TOOLS----------------------------------------------------------------------

mkftools: compile makelib libname makeso link 
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
mkftools_clean: 
	 rm -f compile makelib makeso libname link 
regen:
	cpj-genmk > Makefile.tmp
	mv Makefile.tmp Makefile
