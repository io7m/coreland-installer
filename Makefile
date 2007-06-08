# auto generated - do not edit

default: all

all: local ctxt.a deinstaller inst-check inst-copy inst-dir \
	inst-link installer instchk 

cc-compile: conf-cc conf-cctype 
cc-link: conf-ld 
cc-slib: conf-systype 
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
	cc-slib ctxt.sld ctxt/repos.o 
	./cc-slib ctxt ctxt/repos.o 
ctxt/repos.o:\
	cc-compile ctxt/repos.c 
	./cc-compile ctxt/repos.c
deinstaller:\
	cc-link deinstaller.ld deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./cc-link deinstaller deinstaller.o insthier.o install_core.o \
	install_error.o ctxt.a 
deinstaller.o:\
	cc-compile deinstaller.c install.h 
	./cc-compile deinstaller.c
generic-conf.o:\
	cc-compile generic-conf.c ctxt.h 
	./cc-compile generic-conf.c
inst-check:\
	cc-link inst-check.ld inst-check.o install_error.o 
	./cc-link inst-check inst-check.o install_error.o 
inst-check.o:\
	cc-compile inst-check.c install.h 
	./cc-compile inst-check.c
inst-copy:\
	cc-link inst-copy.ld inst-copy.o install_error.o 
	./cc-link inst-copy inst-copy.o install_error.o 
inst-copy.o:\
	cc-compile inst-copy.c install.h 
	./cc-compile inst-copy.c
inst-dir:\
	cc-link inst-dir.ld inst-dir.o install_error.o 
	./cc-link inst-dir inst-dir.o install_error.o 
inst-dir.o:\
	cc-compile inst-dir.c install.h 
	./cc-compile inst-dir.c
inst-link:\
	cc-link inst-link.ld inst-link.o install_error.o 
	./cc-link inst-link inst-link.o install_error.o 
inst-link.o:\
	cc-compile inst-link.c install.h 
	./cc-compile inst-link.c
install_core.o:\
	cc-compile install_core.c install.h 
	./cc-compile install_core.c
install_error.o:\
	cc-compile install_error.c install.h 
	./cc-compile install_error.c
installer:\
	cc-link installer.ld installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./cc-link installer installer.o insthier.o install_core.o \
	install_error.o ctxt.a 
installer.o:\
	cc-compile installer.c install.h 
	./cc-compile installer.c
instchk:\
	cc-link instchk.ld instchk.o insthier.o install_core.o \
	install_error.o ctxt.a 
	./cc-link instchk instchk.o insthier.o install_core.o \
	install_error.o ctxt.a 
instchk.o:\
	cc-compile instchk.c install.h 
	./cc-compile instchk.c
insthier.o:\
	cc-compile insthier.c ctxt.h install.h 
	./cc-compile insthier.c
mk-cctype: conf-cc conf-systype 
mk-ctxt.o:\
	cc-compile mk-ctxt.c
	./cc-compile mk-ctxt.c
mk-ctxt:\
	cc-link mk-ctxt.o mk-ctxt.ld
	./cc-link mk-ctxt mk-ctxt.o
mk-sosuffix: conf-systype 
mk-systype: conf-cc 
clean-all: tests_clean local_clean obj_clean 
clean: obj_clean
obj_clean: 
	rm -f conf-cctype conf-systype ctxt.a ctxt/repos.c ctxt/repos.o \
	deinstaller deinstaller.o generic-conf.o inst-check inst-check.o \
	inst-copy inst-copy.o inst-dir inst-dir.o inst-link inst-link.o \
	install_core.o install_error.o installer installer.o instchk \
	instchk.o insthier.o mk-ctxt mk-ctxt.o 

deinstall: deinstaller inst-check inst-copy inst-dir inst-link
	./deinstaller
deinstall-dryrun: deinstaller inst-check inst-copy inst-dir inst-link
	./deinstaller dryrun
install: installer inst-check inst-copy inst-dir inst-link postinstall
	./installer
	./postinstall

install-dryrun: installer inst-check inst-copy inst-dir inst-link
	./installer dryrun
install-check: instchk inst-check
	./instchk
tests:
	(cd UNIT_TESTS && make && make tests)
tests_clean:
	(cd UNIT_TESTS && make clean)
local:
local_clean:

ctxt/repos.c: mk-ctxt conf-repos
	rm -f ctxt/repos.c
	./mk-ctxt ctxt_repos < conf-repos > ctxt/repos.c
regen:
	cpj-genmk > Makefile.tmp && mv Makefile.tmp Makefile

