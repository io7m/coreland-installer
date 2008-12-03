# auto generated - do not edit

default: all

all:\
local UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_deinst12 \
UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o \
UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_instchk2 \
UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
ctxt/ctxt.a ctxt/repos.o deinstaller deinstaller.o generic-conf.o \
install-error.o install-posix.o install-win32.o install.a install.o installer \
installer.o instchk instchk.o insthier.o

# Mkf-deinstall
deinstall: deinstaller inst-check inst-copy inst-dir inst-link
	./deinstaller
deinstall-dryrun: deinstaller inst-check inst-copy inst-dir inst-link
	./deinstaller dryrun

# Mkf-install
install: installer inst-check inst-copy inst-dir inst-link postinstall
	./installer
	./postinstall

install-dryrun: installer inst-check inst-copy inst-dir inst-link
	./installer dryrun

# Mkf-instchk
install-check: instchk inst-check
	./instchk

# Mkf-local
local: conf-sosuffix
local_clean:

ctxt/repos.c: mk-ctxt conf-repos
	rm -f ctxt/repos.c
	./mk-ctxt ctxt_repos < conf-repos > ctxt/repos.c

# Mkf-test
tests:
	(cd UNIT_TESTS && make tests)
tests_clean:
	(cd UNIT_TESTS && make clean)

UNIT_TESTS/t_deinst1:\
cc-link UNIT_TESTS/t_deinst1.ld UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
install.a
	./cc-link UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
	install.a

UNIT_TESTS/t_deinst1.o:\
cc-compile UNIT_TESTS/t_deinst1.c install.h
	./cc-compile UNIT_TESTS/t_deinst1.c

UNIT_TESTS/t_deinst12:\
cc-link UNIT_TESTS/t_deinst12.ld UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
install.a
	./cc-link UNIT_TESTS/t_deinst12 UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
	install.a

UNIT_TESTS/t_deinst12.o:\
cc-compile UNIT_TESTS/t_deinst12.c install.h
	./cc-compile UNIT_TESTS/t_deinst12.c

UNIT_TESTS/t_deinst2:\
cc-link UNIT_TESTS/t_deinst2.ld UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
install.a
	./cc-link UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
	install.a

UNIT_TESTS/t_deinst2.o:\
cc-compile UNIT_TESTS/t_deinst2.c install.h
	./cc-compile UNIT_TESTS/t_deinst2.c

UNIT_TESTS/t_inst1:\
cc-link UNIT_TESTS/t_inst1.ld UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
install.a
	./cc-link UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
	install.a

UNIT_TESTS/t_inst1.o:\
cc-compile UNIT_TESTS/t_inst1.c install.h
	./cc-compile UNIT_TESTS/t_inst1.c

UNIT_TESTS/t_inst1h.o:\
cc-compile UNIT_TESTS/t_inst1h.c install.h
	./cc-compile UNIT_TESTS/t_inst1h.c

UNIT_TESTS/t_inst2:\
cc-link UNIT_TESTS/t_inst2.ld UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
install.a
	./cc-link UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
	install.a

UNIT_TESTS/t_inst2.o:\
cc-compile UNIT_TESTS/t_inst2.c install.h
	./cc-compile UNIT_TESTS/t_inst2.c

UNIT_TESTS/t_inst2h.o:\
cc-compile UNIT_TESTS/t_inst2h.c install.h
	./cc-compile UNIT_TESTS/t_inst2h.c

UNIT_TESTS/t_instchk1:\
cc-link UNIT_TESTS/t_instchk1.ld UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
install.a
	./cc-link UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
	install.a

UNIT_TESTS/t_instchk1.o:\
cc-compile UNIT_TESTS/t_instchk1.c install.h
	./cc-compile UNIT_TESTS/t_instchk1.c

UNIT_TESTS/t_instchk2:\
cc-link UNIT_TESTS/t_instchk2.ld UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
install.a
	./cc-link UNIT_TESTS/t_instchk2 UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
	install.a

UNIT_TESTS/t_instchk2.o:\
cc-compile UNIT_TESTS/t_instchk2.c install.h
	./cc-compile UNIT_TESTS/t_instchk2.c

UNIT_TESTS/t_instchkpre:\
cc-link UNIT_TESTS/t_instchkpre.ld UNIT_TESTS/t_instchkpre.o \
UNIT_TESTS/t_inst1h.o install.a
	./cc-link UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
	UNIT_TESTS/t_inst1h.o install.a

UNIT_TESTS/t_instchkpre.o:\
cc-compile UNIT_TESTS/t_instchkpre.c install.h
	./cc-compile UNIT_TESTS/t_instchkpre.c

cc-compile:\
conf-cc conf-cctype conf-systype conf-cflags

cc-link:\
conf-ld conf-ldtype conf-systype

cc-slib:\
conf-systype

conf-cctype:\
conf-cc mk-cctype
	./mk-cctype > conf-cctype.tmp && mv conf-cctype.tmp conf-cctype

conf-ldtype:\
conf-ld mk-ldtype
	./mk-ldtype > conf-ldtype.tmp && mv conf-ldtype.tmp conf-ldtype

conf-sosuffix:\
mk-sosuffix
	./mk-sosuffix > conf-sosuffix.tmp && mv conf-sosuffix.tmp conf-sosuffix

conf-systype:\
mk-systype
	./mk-systype > conf-systype.tmp && mv conf-systype.tmp conf-systype

ctxt/ctxt.a:\
cc-slib ctxt/ctxt.sld ctxt/repos.o
	./cc-slib ctxt/ctxt ctxt/repos.o

ctxt/repos.o:\
cc-compile ctxt/repos.c
	./cc-compile ctxt/repos.c

deinstaller:\
cc-link deinstaller.ld deinstaller.o insthier.o install.a ctxt/ctxt.a
	./cc-link deinstaller deinstaller.o insthier.o install.a ctxt/ctxt.a

deinstaller.o:\
cc-compile deinstaller.c install.h
	./cc-compile deinstaller.c

generic-conf.o:\
cc-compile generic-conf.c ctxt.h
	./cc-compile generic-conf.c

install-error.o:\
cc-compile install-error.c install.h
	./cc-compile install-error.c

install-posix.o:\
cc-compile install-posix.c install.h
	./cc-compile install-posix.c

install-win32.o:\
cc-compile install-win32.c install.h
	./cc-compile install-win32.c

install.a:\
cc-slib install.sld install.o install-posix.o install-win32.o install-error.o
	./cc-slib install install.o install-posix.o install-win32.o install-error.o

install.h:\
install_os.h

install.o:\
cc-compile install.c install.h
	./cc-compile install.c

installer:\
cc-link installer.ld installer.o insthier.o install.a ctxt/ctxt.a
	./cc-link installer installer.o insthier.o install.a ctxt/ctxt.a

installer.o:\
cc-compile installer.c install.h
	./cc-compile installer.c

instchk:\
cc-link instchk.ld instchk.o insthier.o install.a ctxt/ctxt.a
	./cc-link instchk instchk.o insthier.o install.a ctxt/ctxt.a

instchk.o:\
cc-compile instchk.c install.h
	./cc-compile instchk.c

insthier.o:\
cc-compile insthier.c ctxt.h install.h
	./cc-compile insthier.c

mk-cctype:\
conf-cc conf-systype

mk-ctxt:\
mk-mk-ctxt
	./mk-mk-ctxt

mk-ldtype:\
conf-ld conf-systype conf-cctype

mk-mk-ctxt:\
conf-cc conf-ld

mk-sosuffix:\
conf-systype

mk-systype:\
conf-cc conf-ld

clean-all: tests_clean local_clean obj_clean ext_clean
clean: obj_clean
obj_clean:
	rm -f UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_deinst12 \
	UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o \
	UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
	UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
	UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_instchk2 \
	UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
	ctxt/ctxt.a ctxt/repos.c ctxt/repos.o deinstaller deinstaller.o generic-conf.o \
	install-error.o install-posix.o install-win32.o install.a install.o installer \
	installer.o instchk instchk.o insthier.o
ext_clean:
	rm -f conf-cctype conf-ldtype conf-sosuffix conf-systype mk-ctxt

regen:
	cpj-genmk > Makefile.tmp && mv Makefile.tmp Makefile
