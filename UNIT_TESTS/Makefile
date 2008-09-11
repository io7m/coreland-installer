tests: mk-sosuffix conf-systype inst-check inst-copy inst-dir inst-link run-tests.sh
	./run-tests.sh
tests_clean:
	rm -f t_inst1.out
	rm -f inst-check inst-copy inst-dir inst-link mk-sosuffix conf-systype
clean: tests_clean

inst-check: ../inst-check
	rm -f inst-check
	ln -s ../inst-check inst-check
inst-copy: ../inst-copy
	rm -f inst-copy
	ln -s ../inst-copy inst-copy
inst-dir: ../inst-dir
	rm -f inst-dir
	ln -s ../inst-dir inst-dir
inst-link: ../inst-link
	rm -f inst-link
	ln -s ../inst-link inst-link
mk-sosuffix: ../mk-sosuffix
	rm -f mk-sosuffix
	ln -s ../mk-sosuffix mk-sosuffix
conf-systype: ../conf-systype
	rm -f conf-systype
	ln -s ../conf-systype conf-systype
