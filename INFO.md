This is the directory structure.
ParadoxEngine/ - main directory\n
	pdxGame/ - test game (incomplete)
	PEconf/ - application configuration directory
	src/ - source code
	Makefile - used to create XSD lib
	premake4.lua - Premake4 file
	README - This.

Required programs:
	premake4 - needed for the generation of the build scripts. Get it here: http://industriousone.com/premake
	CodeSynthesis XSD - needed for the generation of the XML XSD library. Get it here: http://www.codesynthesis.com/products/xsd

Required libraries:
	Poco - http://pocoproject.org
	Falcon Programming Language - http://www.falconpl.org
	Xerces-C - http://xerces.apache.org/xerces-c
	SFML - http://www.sfml-dev.org

Optional programs:
	make - For the Makefile, which automatically generates the XSD, builds the documentation using Doxygen, then copies the XSD files to the test game. If you don't have make, you will need to run the commands yourself
	doxygen - generate documentation for the XSD lib
