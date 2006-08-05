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


phase_compile:
phase_compile_clean:

#--LIBRARY--------------------------------------------------------------------


phase_library:
phase_library_clean:

#--LINK-----------------------------------------------------------------------


phase_link:
phase_link_clean:

#--TEST-----------------------------------------------------------------------

phase_test: success

success:
	@echo 'The software passed all tests.'

phase_test_clean:

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
