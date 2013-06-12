This is the directory structure.

	ParadoxEngine/ - main directory
	pdxGame/ - test game (incomplete)
	PEconf/ - application configuration directory
	src/ - source code
	Makefile - used to create XSD lib
	premake4.lua - Premake4 file
	README - This.

Required programs:

	premake4 - needed for the generation of the build scripts. Get it here: http://industriousone.com/premake

Required libraries:

	Poco - http://pocoproject.org
	Falcon Programming Language - http://www.falconpl.org
	Xerces-C - http://xerces.apache.org/xerces-c
	SFML - http://www.sfml-dev.org
	
Optional headers:

	SDL - required for the wait function. Use --disable-wait to turn off
