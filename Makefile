# auto generated - do not edit
# cpj-genmk-0.70

SHELL=/bin/sh
default: all
all: phase_sysdeps phase_tools phase_compile phase_library \
	phase_link 

clean: phase_sysdeps_clean phase_tools_clean phase_compile_clean \
	phase_library_clean phase_link_clean 


#--SYSDEPS--------------------------------------------------------------------

phase_sysdeps: sysdeps
phase_sysdeps_clean: sysdeps_clean

#--TOOLS----------------------------------------------------------------------

phase_tools:  mkftools
phase_tools_clean:  mkftools_clean

#--COMPILE--------------------------------------------------------------------

bin_copy.o:\
	compile bin_copy.c bin.h 
	./compile bin_copy bin_copy.c 
bin_copyr.o:\
	compile bin_copyr.c bin.h 
	./compile bin_copyr bin_copyr.c 
buffer1.o:\
	compile buffer1.c buffer.h write.h 
	./compile buffer1 buffer1.c 
buffer2.o:\
	compile buffer2.c buffer.h write.h 
	./compile buffer2 buffer2.c 
buffer_get.o:\
	compile buffer_get.c bin.h buffer.h error.h uint32.h 
	./compile buffer_get buffer_get.c 
buffer_put.o:\
	compile buffer_put.c bin.h buffer.h error.h str.h uint32.h 
	./compile buffer_put buffer_put.c 
error.o:\
	compile error.c error.h 
	./compile error error.c 
error_str.o:\
	compile error_str.c error.h 
	./compile error_str error_str.c 
fmt_u32.o:\
	compile fmt_u32.c fmt.h 
	./compile fmt_u32 fmt_u32.c 
fmt_u32o.o:\
	compile fmt_u32o.c fmt.h 
	./compile fmt_u32o fmt_u32o.c 
fmt_u64.o:\
	compile fmt_u64.c fmt.h uint64.h 
	./compile fmt_u64 fmt_u64.c 
fmt_u64o.o:\
	compile fmt_u64o.c fmt.h uint64.h 
	./compile fmt_u64o fmt_u64o.c 
get_opt.o:\
	compile get_opt.c buffer.h get_opt.h 
	./compile get_opt get_opt.c 
install_ln.o:\
	compile install_ln.c install.h open.h str.h syserr.h 
	./compile install_ln install_ln.c 
installer.o:\
	compile installer.c buffer.h error.h fmt.h fsync.h get_opt.h \
	install.h open.h read.h sstring.h syserr.h write.h uint64.h 
	./compile installer installer.c 
instchk.o:\
	compile instchk.c buffer.h error.h fmt.h install.h open.h read.h \
	sstring.h syserr.h write.h uint64.h 
	./compile instchk instchk.c 
insthier.o:\
	compile insthier.c install.h 
	./compile insthier insthier.c 
open_ro.o:\
	compile open_ro.c open.h 
	./compile open_ro open_ro.c 
open_trunc.o:\
	compile open_trunc.c open.h 
	./compile open_trunc open_trunc.c 
sstring_0.o:\
	compile sstring_0.c sstring.h 
	./compile sstring_0 sstring_0.c 
sstring_catb.o:\
	compile sstring_catb.c sstring.h 
	./compile sstring_catb sstring_catb.c 
sstring_cats.o:\
	compile sstring_cats.c sstring.h 
	./compile sstring_cats sstring_cats.c 
sstring_chop.o:\
	compile sstring_chop.c sstring.h 
	./compile sstring_chop sstring_chop.c 
sstring_trunc.o:\
	compile sstring_trunc.c sstring.h 
	./compile sstring_trunc sstring_trunc.c 
str_len.o:\
	compile str_len.c str.h 
	./compile str_len str_len.c 
syserr_die.o:\
	compile syserr_die.c buffer.h exit.h syserr.h 
	./compile syserr_die syserr_die.c 
syserr_init.o:\
	compile syserr_init.c error.h syserr.h 
	./compile syserr_init syserr_init.c 

phase_compile:\
	bin_copy.o bin_copyr.o buffer1.o buffer2.o buffer_get.o \
	buffer_put.o error.o error_str.o fmt_u32.o fmt_u32o.o fmt_u64.o \
	fmt_u64o.o get_opt.o install_ln.o installer.o instchk.o insthier.o \
	open_ro.o open_trunc.o sstring_0.o sstring_catb.o sstring_cats.o \
	sstring_chop.o sstring_trunc.o str_len.o syserr_die.o syserr_init.o 
phase_compile_clean:
	rm -f bin_copy.o bin_copyr.o buffer1.o buffer2.o buffer_get.o \
	buffer_put.o error.o error_str.o fmt_u32.o fmt_u32o.o fmt_u64.o \
	fmt_u64o.o get_opt.o install_ln.o installer.o instchk.o insthier.o \
	open_ro.o open_trunc.o sstring_0.o sstring_catb.o sstring_cats.o \
	sstring_chop.o sstring_trunc.o str_len.o syserr_die.o syserr_init.o 

#--LIBRARY--------------------------------------------------------------------

bin.a:\
	makelib bin.sld bin_copy.o bin_copyr.o 
	./makelib bin bin_copy.o bin_copyr.o 
buffer.a:\
	makelib buffer.sld buffer1.o buffer2.o buffer_get.o buffer_put.o 
	./makelib buffer buffer1.o buffer2.o buffer_get.o buffer_put.o 
error.a:\
	makelib error.sld error.o error_str.o 
	./makelib error error.o error_str.o 
fmt.a:\
	makelib fmt.sld fmt_u32.o fmt_u32o.o fmt_u64.o fmt_u64o.o 
	./makelib fmt fmt_u32.o fmt_u32o.o fmt_u64.o fmt_u64o.o 
get_opt.a:\
	makelib get_opt.sld get_opt.o 
	./makelib get_opt get_opt.o 
insthier.a:\
	makelib insthier.sld insthier.o 
	./makelib insthier insthier.o 
open.a:\
	makelib open.sld open_ro.o open_trunc.o 
	./makelib open open_ro.o open_trunc.o 
sstring.a:\
	makelib sstring.sld sstring_0.o sstring_catb.o sstring_cats.o \
	sstring_chop.o sstring_trunc.o 
	./makelib sstring sstring_0.o sstring_catb.o sstring_cats.o \
	sstring_chop.o sstring_trunc.o 
str.a:\
	makelib str.sld str_len.o 
	./makelib str str_len.o 
syserr.a:\
	makelib syserr.sld syserr_die.o syserr_init.o 
	./makelib syserr syserr_die.o syserr_init.o 

phase_library:\
	bin.a buffer.a error.a fmt.a get_opt.a insthier.a open.a sstring.a \
	str.a syserr.a 
phase_library_clean:
	rm -f bin.a buffer.a error.a fmt.a get_opt.a insthier.a open.a \
	sstring.a str.a syserr.a 

#--LINK-----------------------------------------------------------------------

installer:\
	link installer.ld installer.o install_ln.o open.a sstring.a \
	syserr.a get_opt.a insthier.a fmt.a buffer.a str.a bin.a error.a 
	./link installer installer.o install_ln.o open.a sstring.a syserr.a \
	get_opt.a insthier.a fmt.a buffer.a str.a bin.a error.a 
instchk:\
	link instchk.ld instchk.o install_ln.o open.a sstring.a syserr.a \
	get_opt.a insthier.a fmt.a buffer.a str.a bin.a error.a 
	./link instchk instchk.o install_ln.o open.a sstring.a syserr.a \
	get_opt.a insthier.a fmt.a buffer.a str.a bin.a error.a 

phase_link:\
	installer instchk 
phase_link_clean:
	rm -f installer instchk 

#--SYSDEPS-TARGET-------------------------------------------------------------

sysdeps: sysdeps.out
sysdeps_clean: sysdep_clean
sysdeps.out:
	SYSDEPS/sysdep-header sysdeps.out
	(cd SYSDEPS && make )
sysdep_clean:
	(cd SYSDEPS && make clean)
	rm -f sysdeps.out

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
