all: mydash-project dox

mydash-project:
	cd mydash-src; make

dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config > doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

clean:
	/bin/rm -f *.o a.out core mydash doxygen.log
	/bin/rm -rf docs
	cd mydash-src; make clean

