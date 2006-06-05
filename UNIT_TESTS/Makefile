# auto generated - do not edit
# cpj-genmk-0.73

SHELL=/bin/sh
default: all
all: phase_tools phase_compile phase_library phase_link 

clean: phase_tools_clean phase_compile_clean phase_library_clean \
	phase_link_clean 


#--TOOLS----------------------------------------------------------------------

phase_tools:  mkftools
phase_tools_clean:  mkftools_clean

#--COMPILE--------------------------------------------------------------------

t_inst1.o:\
	compile t_inst1.c ../buffer.h ../install.h ../syserr.h 
	./compile t_inst1 t_inst1.c 
t_inst1h.o:\
	compile t_inst1h.c ../install.h 
	./compile t_inst1h t_inst1h.c 

phase_compile:\
	t_inst1.o t_inst1h.o 
phase_compile_clean:
	rm -f t_inst1.o t_inst1h.o 

#--LIBRARY--------------------------------------------------------------------


phase_library:
phase_library_clean:

#--LINK-----------------------------------------------------------------------

t_inst1:\
	link t_inst1.ld t_inst1.o ../install.o ../install_ln.o t_inst1h.o \
	../open.a ../rmkdir.a ../sstring.a ../syserr.a ../get_opt.a ../fmt.a \
	../buffer.a ../str.a ../bin.a ../error.a 
	./link t_inst1 t_inst1.o ../install.o ../install_ln.o t_inst1h.o \
	../open.a ../rmkdir.a ../sstring.a ../syserr.a ../get_opt.a ../fmt.a \
	../buffer.a ../str.a ../bin.a ../error.a 

phase_link:\
	t_inst1 
phase_link_clean:
	rm -f t_inst1 

#--TOOLS----------------------------------------------------------------------

mkftools: compile makelib sosuffix makeso link 
compile: conf-shebang conf-cc make-compile 
	(cat conf-shebang; ./make-compile) > compile; chmod u+x compile;
link: conf-shebang conf-ld make-link 
	(cat conf-shebang; ./make-link) > link; chmod u+x link;
makelib: conf-shebang make-makelib 
	(cat conf-shebang; ./make-makelib) > makelib; chmod u+x makelib;
makeso: conf-shebang sosuffix make-makeso 
	(cat conf-shebang; ./make-makeso) > makeso; chmod u+x makeso;
sosuffix: conf-shebang make-sosuffix 
	(cat conf-shebang; ./make-sosuffix) > sosuffix; chmod u+x sosuffix;
mkftools_clean: 
	 rm -f compile makelib makeso sosuffix link 
regen:
	cpj-genmk > Makefile.tmp
	mv Makefile.tmp Makefile
