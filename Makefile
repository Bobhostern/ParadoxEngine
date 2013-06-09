ifndef XSD
	XSD=xsd
endif

ifndef DOXYGEN
	DOXYGEN=doxygen
endif

ifndef CP
	CP=cp
endif

ifndef CD
	CD=cd
endif

ifndef VERBOSE
	VERBOSE=@
endif

ifndef GAME
	GAME=pdxGame
endif

all: generate doxygen copy
clean: clean-source clean-doxygen
clean-source:
	rm src/xsd/*.h
	rm src/xsd/*.cpp
clean-doxygen:
	rm src/xsd/doxygen.*
	rm -R src/xsd/html
	rm -R src/xsd/latex
generate:
	$(XSD) cxx-tree --generate-serialization --generate-doxygen --output-dir ./src/xsd/ --hxx-suffix .h --ixx-suffix .i --cxx-suffix .cpp --fwd-suffix -fwd.h ./src/xsd/*.xsd
doxygen:
	$(VERBOSE) $(CD) src/xsd && $(DOXYGEN) -g doxygen.dox > doxygen.log && $(DOXYGEN) doxygen.dox > doxygen.2.log
copy:
	$(CP) src/xsd/*.xsd $(GAME)/xsd/
	
help:
	@ echo "Targets:"
	@ echo "\tall\n\tclean\n\tgenerate\n\tdoxygen\n\tcopy\n\tclean"