tests: conf-sosuffix conf-systype run-tests.sh
	./run-tests.sh

tests_clean:
	rm -f t_inst1.out
	rm -f conf-sosuffix conf-systype

clean: tests_clean

conf-sosuffix:
	rm -f conf-sosuffix
	cp ../conf-sosuffix conf-sosuffix
conf-systype:
	rm -f conf-systype
	cp ../conf-systype conf-systype
