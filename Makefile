# auto generated - do not edit

default: all

all:\
local UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_deinst12 \
UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o \
UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_instchk2 \
UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
ctxt/ctxt.a ctxt/repos.o deinstaller deinstaller.o generic-conf.o i-check.o \
i-copy.o i-core.o i-core_posix.o i-core_win32.o i-dir.o i-error.o i-link.o \
inst-check inst-copy inst-dir inst-link installer installer.o instchk instchk.o \
insthier.o

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
local:
local_clean:

ctxt/repos.c: mk-ctxt conf-repos
	rm -f ctxt/repos.c
	./mk-ctxt ctxt_repos < conf-repos > ctxt/repos.c

# Mkf-test
tests:
	(cd UNIT_TESTS && make tests)
tests_clean:
	(cd UNIT_TESTS && make clean)

UNIT_TESTS/conf-sosuffix:\
mk-sosuffix
	./mk-sosuffix > UNIT_TESTS/conf-sosuffix.tmp && mv UNIT_TESTS/conf-sosuffix.tmp \
UNIT_TESTS/conf-sosuffix

UNIT_TESTS/conf-systype:\
mk-systype
	./mk-systype > UNIT_TESTS/conf-systype.tmp && mv UNIT_TESTS/conf-systype.tmp \
UNIT_TESTS/conf-systype

UNIT_TESTS/mk-sosuffix:\
conf-systype

UNIT_TESTS/t_deinst1:\
cc-link UNIT_TESTS/t_deinst1.ld UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_deinst1.o:\
cc-compile UNIT_TESTS/t_deinst1.c install.h
	./cc-compile UNIT_TESTS/t_deinst1.c

UNIT_TESTS/t_deinst12:\
cc-link UNIT_TESTS/t_deinst12.ld UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_deinst12 UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_deinst12.o:\
cc-compile UNIT_TESTS/t_deinst12.c install.h
	./cc-compile UNIT_TESTS/t_deinst12.c

UNIT_TESTS/t_deinst2:\
cc-link UNIT_TESTS/t_deinst2.ld UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_deinst2.o:\
cc-compile UNIT_TESTS/t_deinst2.c install.h
	./cc-compile UNIT_TESTS/t_deinst2.c

UNIT_TESTS/t_inst1:\
cc-link UNIT_TESTS/t_inst1.ld UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_inst1.o:\
cc-compile UNIT_TESTS/t_inst1.c install.h
	./cc-compile UNIT_TESTS/t_inst1.c

UNIT_TESTS/t_inst1h.o:\
cc-compile UNIT_TESTS/t_inst1h.c install.h
	./cc-compile UNIT_TESTS/t_inst1h.c

UNIT_TESTS/t_inst2:\
cc-link UNIT_TESTS/t_inst2.ld UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_inst2.o:\
cc-compile UNIT_TESTS/t_inst2.c install.h
	./cc-compile UNIT_TESTS/t_inst2.c

UNIT_TESTS/t_inst2h.o:\
cc-compile UNIT_TESTS/t_inst2h.c install.h
	./cc-compile UNIT_TESTS/t_inst2h.c

UNIT_TESTS/t_instchk1:\
cc-link UNIT_TESTS/t_instchk1.ld UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_instchk1.o:\
cc-compile UNIT_TESTS/t_instchk1.c install.h
	./cc-compile UNIT_TESTS/t_instchk1.c

UNIT_TESTS/t_instchk2:\
cc-link UNIT_TESTS/t_instchk2.ld UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_instchk2 UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
	i-core.o i-core_posix.o i-core_win32.o i-error.o

UNIT_TESTS/t_instchk2.o:\
cc-compile UNIT_TESTS/t_instchk2.c install.h
	./cc-compile UNIT_TESTS/t_instchk2.c

UNIT_TESTS/t_instchkpre:\
cc-link UNIT_TESTS/t_instchkpre.ld UNIT_TESTS/t_instchkpre.o \
UNIT_TESTS/t_inst1h.o i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
	UNIT_TESTS/t_inst1h.o i-core.o i-core_posix.o i-core_win32.o i-error.o

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
conf-cc conf-cc mk-cctype
	./mk-cctype > conf-cctype.tmp && mv conf-cctype.tmp conf-cctype

conf-ldtype:\
conf-ld conf-ld mk-ldtype
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
cc-link deinstaller.ld deinstaller.o insthier.o i-core.o i-core_posix.o \
i-core_win32.o i-error.o ctxt/ctxt.a
	./cc-link deinstaller deinstaller.o insthier.o i-core.o i-core_posix.o \
	i-core_win32.o i-error.o ctxt/ctxt.a

deinstaller.o:\
cc-compile deinstaller.c install.h
	./cc-compile deinstaller.c

generic-conf.o:\
cc-compile generic-conf.c ctxt.h
	./cc-compile generic-conf.c

i-check.o:\
cc-compile i-check.c install.h
	./cc-compile i-check.c

i-copy.o:\
cc-compile i-copy.c install.h
	./cc-compile i-copy.c

i-core.o:\
cc-compile i-core.c install.h
	./cc-compile i-core.c

i-core_posix.o:\
cc-compile i-core_posix.c install.h
	./cc-compile i-core_posix.c

i-core_win32.o:\
cc-compile i-core_win32.c install.h
	./cc-compile i-core_win32.c

i-dir.o:\
cc-compile i-dir.c install.h
	./cc-compile i-dir.c

i-error.o:\
cc-compile i-error.c install.h
	./cc-compile i-error.c

i-link.o:\
cc-compile i-link.c install.h
	./cc-compile i-link.c

inst-check:\
cc-link inst-check.ld i-check.o i-error.o
	./cc-link inst-check i-check.o i-error.o

inst-copy:\
cc-link inst-copy.ld i-copy.o i-core.o i-core_posix.o i-core_win32.o i-error.o
	./cc-link inst-copy i-copy.o i-core.o i-core_posix.o i-core_win32.o i-error.o

inst-dir:\
cc-link inst-dir.ld i-dir.o i-error.o
	./cc-link inst-dir i-dir.o i-error.o

inst-link:\
cc-link inst-link.ld i-link.o i-error.o
	./cc-link inst-link i-link.o i-error.o

install.h:\
install_os.h

installer:\
cc-link installer.ld installer.o insthier.o i-core.o i-core_posix.o \
i-core_win32.o i-error.o ctxt/ctxt.a
	./cc-link installer installer.o insthier.o i-core.o i-core_posix.o \
	i-core_win32.o i-error.o ctxt/ctxt.a

installer.o:\
cc-compile installer.c install.h
	./cc-compile installer.c

instchk:\
cc-link instchk.ld instchk.o insthier.o i-core.o i-core_posix.o i-core_win32.o \
i-error.o ctxt/ctxt.a
	./cc-link instchk instchk.o insthier.o i-core.o i-core_posix.o i-core_win32.o \
	i-error.o ctxt/ctxt.a

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
	i-check.o i-copy.o i-core.o i-core_posix.o i-core_win32.o i-dir.o i-error.o \
	i-link.o inst-check inst-copy inst-dir inst-link installer installer.o instchk \
	instchk.o insthier.o
ext_clean:
	rm -f UNIT_TESTS/conf-sosuffix UNIT_TESTS/conf-systype conf-cctype conf-ldtype \
	conf-sosuffix conf-systype mk-ctxt

regen:
	cpj-genmk > Makefile.tmp && mv Makefile.tmp Makefile
