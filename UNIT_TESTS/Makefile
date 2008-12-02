tests: mk-sosuffix conf-systype run-tests.sh
	./run-tests.sh
tests_clean:
	rm -f t_inst1.out
	rm -f mk-sosuffix conf-systype
clean: tests_clean

mk-sosuffix: ../mk-sosuffix
	rm -f mk-sosuffix
	ln -s ../mk-sosuffix mk-sosuffix
conf-systype: ../conf-systype
	rm -f conf-systype
	ln -s ../conf-systype conf-systype
