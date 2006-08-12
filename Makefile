# auto generated - do not edit
# cpj-genmk-0.78

SHELL=/bin/sh
default: all
all: phase_tools_local phase_tools phase_compile_local phase_compile \
	phase_library_local phase_library phase_link_local phase_link 

tests: phase_test 

install: phase_install 

install-check: phase_install_check 

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
	compile inst-check.c install.h 
	./compile inst-check inst-check.c 
inst-copy.o:\
	compile inst-copy.c install.h 
	./compile inst-copy inst-copy.c 
inst-dir.o:\
	compile inst-dir.c install.h 
	./compile inst-dir inst-dir.c 
inst-link.o:\
	compile inst-link.c install.h 
	./compile inst-link inst-link.c 
install_core.o:\
	compile install_core.c install.h 
	./compile install_core install_core.c 
install_error.o:\
	compile install_error.c install.h 
	./compile install_error install_error.c 
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
	compile ctxt/ctxt_repos.c 
	./compile ctxt/ctxt_repos ctxt/ctxt_repos.c 

phase_compile:\
	auto-text.o deinstaller.o inst-check.o inst-copy.o inst-dir.o \
	inst-link.o install_core.o install_error.o installer.o instchk.o \
	insthier.o ctxt/ctxt_repos.o 
phase_compile_clean:
	rm -f auto-text.o deinstaller.o inst-check.o inst-copy.o inst-dir.o \
	inst-link.o install_core.o install_error.o installer.o instchk.o \
	insthier.o ctxt/ctxt_repos.o 

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
	link deinstaller.ld deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./link deinstaller deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
inst-check:\
	link inst-check.ld inst-check.o install_error.o 
	./link inst-check inst-check.o install_error.o 
inst-copy:\
	link inst-copy.ld inst-copy.o install_error.o 
	./link inst-copy inst-copy.o install_error.o 
inst-dir:\
	link inst-dir.ld inst-dir.o install_error.o 
	./link inst-dir inst-dir.o install_error.o 
inst-link:\
	link inst-link.ld inst-link.o install_error.o 
	./link inst-link inst-link.o install_error.o 
installer:\
	link installer.ld installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./link installer installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
instchk:\
	link instchk.ld instchk.o insthier.o install_core.o install_error.o \
	ctxt.a 
	./link instchk instchk.o insthier.o install_core.o install_error.o \
	ctxt.a 

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

#--INSTALL--------------------------------------------------------------------

phase_install: installer
	./installer

install-dryrun: installer
	./installer dryrun

deinstall: deinstaller
	./deinstaller

deinstall-dryrun: deinstaller
	./deinstaller dryrun

#--INSTALL-CHECK--------------------------------------------------------------

phase_install_check: instchk
	./instchk

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
