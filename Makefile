# auto generated - do not edit

default: all

all: local \
	ctxt.a deinstaller inst-check inst-copy inst-dir inst-link \
	installer instchk 

cc:\
	conf-cc conf-cctype 
conf-cctype:\
	conf-systype conf-cc mk-cctype 
	./mk-cctype > conf-cctype
conf-sosuffix:\
	mk-sosuffix 
	./mk-sosuffix > conf-sosuffix
conf-systype:\
	mk-systype 
	./mk-systype > conf-systype
ctxt.a:\
	mk-slib ctxt.sld ctxt/repos.o 
	./mk-slib ctxt ctxt/repos.o 
ctxt/repos.o:\
	cc ctxt/repos.c 
	./cc ctxt/repos.c
deinstaller:\
	ld deinstaller.ld deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./ld deinstaller deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
deinstaller.o:\
	cc deinstaller.c install.h 
	./cc deinstaller.c
inst-check:\
	ld inst-check.ld inst-check.o install_error.o 
	./ld inst-check inst-check.o install_error.o 
inst-check.o:\
	cc inst-check.c install.h 
	./cc inst-check.c
inst-copy:\
	ld inst-copy.ld inst-copy.o install_error.o 
	./ld inst-copy inst-copy.o install_error.o 
inst-copy.o:\
	cc inst-copy.c install.h 
	./cc inst-copy.c
inst-dir:\
	ld inst-dir.ld inst-dir.o install_error.o 
	./ld inst-dir inst-dir.o install_error.o 
inst-dir.o:\
	cc inst-dir.c install.h 
	./cc inst-dir.c
inst-link:\
	ld inst-link.ld inst-link.o install_error.o 
	./ld inst-link inst-link.o install_error.o 
inst-link.o:\
	cc inst-link.c install.h 
	./cc inst-link.c
install_core.o:\
	cc install_core.c install.h 
	./cc install_core.c
install_error.o:\
	cc install_error.c install.h 
	./cc install_error.c
installer:\
	ld installer.ld installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./ld installer installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
installer.o:\
	cc installer.c install.h 
	./cc installer.c
instchk:\
	ld instchk.ld instchk.o insthier.o install_core.o install_error.o \
	ctxt.a 
	./ld instchk instchk.o insthier.o install_core.o install_error.o \
	ctxt.a 
instchk.o:\
	cc instchk.c install.h 
	./cc instchk.c
insthier.o:\
	cc insthier.c ctxt.h install.h 
	./cc insthier.c
ld:\
	conf-ld 
mk-cctype:\
	conf-cc conf-systype 
mk-ctxt.o:\
	cc mk-ctxt.c
	./cc mk-ctxt.c
mk-ctxt:\
	ld mk-ctxt.o mk-ctxt.ld
	./ld mk-ctxt mk-ctxt.o
mk-slib:\
	conf-systype 
mk-sosuffix:\
	conf-systype 
clean: tests_clean local_clean 
	rm -f ctxt.a ctxt/repos.c ctxt/repos.o deinstaller deinstaller.o \
	inst-check inst-check.o inst-copy inst-copy.o inst-dir inst-dir.o \
	inst-link inst-link.o install_core.o install_error.o installer \
	installer.o instchk instchk.o insthier.o 

deinstall: deinstaller
	./deinstaller

deinstall-dryrun: deinstaller
	./deinstaller dryrun
install: installer
	./installer

install-dryrun: installer
	./installer dryrun
install-check: instchk
	./instchk
tests:
	(cd UNIT_TESTS && make && make tests)
tests_clean:
	(cd UNIT_TESTS && make clean)
local:
local_clean:

ctxt/repos.c: mk-ctxt conf-repos
	rm -f ctxt/repos.c
	./mk-ctxt ctxt_repos ../ctxt < conf-repos > ctxt/repos.c
regen:
	cpj-genmk > Makefile.tmp
	mv Makefile.tmp Makefile

