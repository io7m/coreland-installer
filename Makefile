# auto generated - do not edit
# cpj-genmk-0.78

SHELL=/bin/sh
default: all
all: phase_tools phase_compile phase_library phase_link 

clean: phase_tools_clean phase_compile_clean phase_library_clean \
	phase_link_clean 


#--TOOLS----------------------------------------------------------------------

phase_tools:  mkftools
phase_tools_clean:  mkftools_clean

#--COMPILE--------------------------------------------------------------------

inst-check.o:\
	compile inst-check.c 
	./compile inst-check inst-check.c 
inst-copy.o:\
	compile inst-copy.c 
	./compile inst-copy inst-copy.c 
inst-dir.o:\
	compile inst-dir.c 
	./compile inst-dir inst-dir.c 
inst-gid.o:\
	compile inst-gid.c 
	./compile inst-gid inst-gid.c 
inst-uid.o:\
	compile inst-uid.c 
	./compile inst-uid inst-uid.c 

phase_compile:\
	inst-check.o inst-copy.o inst-dir.o inst-gid.o inst-uid.o 
phase_compile_clean:
	rm -f inst-check.o inst-copy.o inst-dir.o inst-gid.o inst-uid.o 

#--LIBRARY--------------------------------------------------------------------


phase_library:
phase_library_clean:

#--LINK-----------------------------------------------------------------------

inst-check:\
	link inst-check.ld inst-check.o 
	./link inst-check inst-check.o 
inst-copy:\
	link inst-copy.ld inst-copy.o 
	./link inst-copy inst-copy.o 
inst-dir:\
	link inst-dir.ld inst-dir.o 
	./link inst-dir inst-dir.o 
inst-gid:\
	link inst-gid.ld inst-gid.o 
	./link inst-gid inst-gid.o 
inst-uid:\
	link inst-uid.ld inst-uid.o 
	./link inst-uid inst-uid.o 

phase_link:\
	inst-check inst-copy inst-dir inst-gid inst-uid 
phase_link_clean:
	rm -f inst-check inst-copy inst-dir inst-gid inst-uid 

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
