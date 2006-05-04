default: sysdeps
clean: sysdeps_clean

sysdeps:  sd_integers sd_systype
sysdeps_clean:  sd_integers_clean sd_systype_clean

sd_integers:
	( cd integers && make )
sd_integers_clean:
	( cd integers && make clean)

sd_systype:
	( cd systype && make )
sd_systype_clean:
	( cd systype && make clean)

regen:
	./gen-makefile > Makefile.tmp
	mv Makefile.tmp Makefile
