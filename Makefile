# auto generated - do not edit
# cpj-genmk-0.78

SHELL=/bin/sh
default: all
all: phase_tools_local phase_tools phase_compile_local phase_compile \
	phase_library_local phase_library phase_link_local phase_link 

tests: phase_test 

clean: phase_local_clean phase_tools_clean phase_compile_clean \
	phase_library_clean phase_link_clean phase_test_clean 


#--TOOLS----------------------------------------------------------------------

phase_tools:  mkftools
phase_tools_clean:  mkftools_clean

#--COMPILE--------------------------------------------------------------------

auto-text.o:\
	compile auto-text.c 
	./compile auto-text auto-text.c 
deinstaller.o:\
	compile deinstaller.c install.h 
	./compile deinstaller deinstaller.c 
inst-check.o:\
	compile inst-check.c 
	./compile inst-check inst-check.c 
inst-copy.o:\
	compile inst-copy.c 
	./compile inst-copy inst-copy.c 
inst-dir.o:\
	compile inst-dir.c 
	./compile inst-dir inst-dir.c 
inst-link.o:\
	compile inst-link.c 
	./compile inst-link inst-link.c 
install.o:\
	compile install.c install.h 
	./compile install install.c 
installer.o:\
	compile installer.c install.h 
	./compile installer installer.c 
instchk.o:\
	compile instchk.c install.h 
	./compile instchk instchk.c 
insthier.o:\
	compile insthier.c ctxt.h install.h 
	./compile insthier insthier.c 
ctxt/ctxt_repos.o:\
	compile ctxt/ctxt_repos.c ctxt/../ctxt.h 
	./compile ctxt/ctxt_repos ctxt/ctxt_repos.c 

phase_compile:\
	auto-text.o deinstaller.o inst-check.o inst-copy.o inst-dir.o \
	inst-link.o install.o installer.o instchk.o insthier.o \
	ctxt/ctxt_repos.o 
phase_compile_clean:
	rm -f auto-text.o deinstaller.o inst-check.o inst-copy.o inst-dir.o \
	inst-link.o install.o installer.o instchk.o insthier.o \
	ctxt/ctxt_repos.o 

#--LIBRARY--------------------------------------------------------------------

ctxt.a:\
	makelib ctxt.sld ctxt/ctxt_repos.o 
	./makelib ctxt ctxt/ctxt_repos.o 

phase_library:\
	ctxt.a 
phase_library_clean:
	rm -f ctxt.a 

#--LINK-----------------------------------------------------------------------

auto-text:\
	link auto-text.ld auto-text.o 
	./link auto-text auto-text.o 
deinstaller:\
	link deinstaller.ld deinstaller.o insthier.o install.o ctxt.a 
	./link deinstaller deinstaller.o insthier.o install.o ctxt.a 
inst-check:\
	link inst-check.ld inst-check.o 
	./link inst-check inst-check.o 
inst-copy:\
	link inst-copy.ld inst-copy.o 
	./link inst-copy inst-copy.o 
inst-dir:\
	link inst-dir.ld inst-dir.o 
	./link inst-dir inst-dir.o 
inst-link:\
	link inst-link.ld inst-link.o 
	./link inst-link inst-link.o 
installer:\
	link installer.ld installer.o insthier.o install.o ctxt.a 
	./link installer installer.o insthier.o install.o ctxt.a 
instchk:\
	link instchk.ld instchk.o insthier.o install.o ctxt.a 
	./link instchk instchk.o insthier.o install.o ctxt.a 

phase_link:\
	auto-text deinstaller inst-check inst-copy inst-dir inst-link \
	installer instchk 
phase_link_clean:
	rm -f auto-text deinstaller inst-check inst-copy inst-dir inst-link \
	installer instchk 

#--TEST-----------------------------------------------------------------------

phase_test:
	(cd UNIT_TESTS && make && make tests)
phase_test_clean:
	(cd UNIT_TESTS && make clean)

#--LOCAL----------------------------------------------------------------------

phase_sysdeps_local:
phase_tools_local:
phase_compile_local:
phase_library_local:
phase_link_local:
phase_local_clean: ctxt_clean

ctxt_clean:
	rm -f ctxt/ctxt_repos.c
	touch ctxt/ctxt_repos.c

ctxt/ctxt_repos.c: auto-text conf-repos
	rm -f ctxt/ctxt_repos.c
	./auto-text ctxt_repos ../ctxt < conf-repos > ctxt/ctxt_repos.c

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
