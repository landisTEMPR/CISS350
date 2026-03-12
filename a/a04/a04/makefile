pdf:
	pdflatex --shell-escape main.tex
	pdflatex --shell-escape main.tex
	make c
	make v

student:
	rm -rf a04-student
	mkdir a04-student
	cp *.* a04-student/
	cp makefile a04-student/
	find a04-student -name '*~' -exec rm {} \;
	rm -f a04-student.tar
	rm -f a04-student.tar.gz
	sleep 1
	tar -cvf a04-student.tar a04-student
	gzip a04-student.tar
	rm -rf a04-student
	rm -f a04-student.tar


view:
	xdg-open main.pdf
v:
	xdg-open main.pdf
clean:
	rm -rf abc.outut
	rm -rf 'main.log' 
	rm -rf 'main.aux'
	rm -rf 'main.toc'
	rm -rf 'main.out'
	rm -rf 'main.idx'
	rm -rf 'main.ilg'
	rm -rf 'texput.log'
	rm -rf 'shEsc.tmp'
	rm -rf 'main.vrb'
	rm -rf 'main.snm'
	rm -rf 'main.nav'
	rm -rf 'abc.output'
	rm -rf main.py.err main.py.out
	rm -rf latex.py main.pytxcode
c:
	make clean
