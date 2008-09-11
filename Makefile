# auto generated - do not edit

default: all

all:\
local UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_deinst12 \
UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o \
UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_instchk2 \
UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
ctxt/ctxt.a ctxt/repos.o deinstaller deinstaller.o generic-conf.o inst-check \
inst-check.o inst-copy inst-copy.o inst-dir inst-dir.o inst-link inst-link.o \
install_core.o install_error.o installer installer.o instchk instchk.o \
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

UNIT_TESTS/t_deinst1:\
cc-link UNIT_TESTS/t_deinst1.ld UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_deinst1 UNIT_TESTS/t_deinst1.o UNIT_TESTS/t_inst1h.o \
	install_core.o install_error.o

UNIT_TESTS/t_deinst1.o:\
cc-compile UNIT_TESTS/t_deinst1.c install.h
	./cc-compile UNIT_TESTS/t_deinst1.c

UNIT_TESTS/t_deinst12:\
cc-link UNIT_TESTS/t_deinst12.ld UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_deinst12 UNIT_TESTS/t_deinst12.o UNIT_TESTS/t_inst1h.o \
	install_core.o install_error.o

UNIT_TESTS/t_deinst12.o:\
cc-compile UNIT_TESTS/t_deinst12.c install.h
	./cc-compile UNIT_TESTS/t_deinst12.c

UNIT_TESTS/t_deinst2:\
cc-link UNIT_TESTS/t_deinst2.ld UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_deinst2 UNIT_TESTS/t_deinst2.o UNIT_TESTS/t_inst2h.o \
	install_core.o install_error.o

UNIT_TESTS/t_deinst2.o:\
cc-compile UNIT_TESTS/t_deinst2.c install.h
	./cc-compile UNIT_TESTS/t_deinst2.c

UNIT_TESTS/t_inst1:\
cc-link UNIT_TESTS/t_inst1.ld UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_inst1 UNIT_TESTS/t_inst1.o UNIT_TESTS/t_inst1h.o \
	install_core.o install_error.o

UNIT_TESTS/t_inst1.o:\
cc-compile UNIT_TESTS/t_inst1.c install.h
	./cc-compile UNIT_TESTS/t_inst1.c

UNIT_TESTS/t_inst1h.o:\
cc-compile UNIT_TESTS/t_inst1h.c install.h
	./cc-compile UNIT_TESTS/t_inst1h.c

UNIT_TESTS/t_inst2:\
cc-link UNIT_TESTS/t_inst2.ld UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_inst2 UNIT_TESTS/t_inst2.o UNIT_TESTS/t_inst2h.o \
	install_core.o install_error.o

UNIT_TESTS/t_inst2.o:\
cc-compile UNIT_TESTS/t_inst2.c install.h
	./cc-compile UNIT_TESTS/t_inst2.c

UNIT_TESTS/t_inst2h.o:\
cc-compile UNIT_TESTS/t_inst2h.c install.h
	./cc-compile UNIT_TESTS/t_inst2h.c

UNIT_TESTS/t_instchk1:\
cc-link UNIT_TESTS/t_instchk1.ld UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_instchk1 UNIT_TESTS/t_instchk1.o UNIT_TESTS/t_inst1h.o \
	install_core.o install_error.o

UNIT_TESTS/t_instchk1.o:\
cc-compile UNIT_TESTS/t_instchk1.c install.h
	./cc-compile UNIT_TESTS/t_instchk1.c

UNIT_TESTS/t_instchk2:\
cc-link UNIT_TESTS/t_instchk2.ld UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
install_core.o install_error.o
	./cc-link UNIT_TESTS/t_instchk2 UNIT_TESTS/t_instchk2.o UNIT_TESTS/t_inst2h.o \
	install_core.o install_error.o

UNIT_TESTS/t_instchk2.o:\
cc-compile UNIT_TESTS/t_instchk2.c install.h
	./cc-compile UNIT_TESTS/t_instchk2.c

UNIT_TESTS/t_instchkpre:\
cc-link UNIT_TESTS/t_instchkpre.ld UNIT_TESTS/t_instchkpre.o \
UNIT_TESTS/t_inst1h.o install_core.o install_error.o
	./cc-link UNIT_TESTS/t_instchkpre UNIT_TESTS/t_instchkpre.o \
	UNIT_TESTS/t_inst1h.o install_core.o install_error.o

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
cc-link deinstaller.ld deinstaller.o insthier.o install_core.o install_error.o \
ctxt/ctxt.a
	./cc-link deinstaller deinstaller.o insthier.o install_core.o install_error.o \
	ctxt/ctxt.a

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
cc-link installer.ld installer.o insthier.o install_core.o install_error.o \
ctxt/ctxt.a
	./cc-link installer installer.o insthier.o install_core.o install_error.o \
	ctxt/ctxt.a

installer.o:\
cc-compile installer.c install.h
	./cc-compile installer.c

instchk:\
cc-link instchk.ld instchk.o insthier.o install_core.o install_error.o \
ctxt/ctxt.a
	./cc-link instchk instchk.o insthier.o install_core.o install_error.o \
	ctxt/ctxt.a

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
conf-cc

mk-sosuffix:\
conf-systype

mk-systype:\
conf-cc

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
	inst-check inst-check.o inst-copy inst-copy.o inst-dir inst-dir.o inst-link \
	inst-link.o install_core.o install_error.o installer installer.o instchk \
	instchk.o insthier.o
ext_clean:
	rm -f conf-cctype conf-ldtype conf-sosuffix conf-systype mk-ctxt

regen:
	cpj-genmk > Makefile.tmp && mv Makefile.tmp Makefile
