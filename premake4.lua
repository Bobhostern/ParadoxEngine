solution "ParadoxEngine"
	configurations { "Debug", "Release" }
	location "build"
	newoption {
		trigger = "build",
		value = "VALUE",
		description = "How to build library",
		allowed = {
			{ "static", "Static library (*.a)" },
			{ "dynamic", "Dynamic library (Linux *.so, Windows *.dll, Mac *.dylib)" }
		}
	}

	newoption {
		trigger = "disable-wait",
		description = "Disable wait function"
	}

	if not _OPTIONS["build"] then
		_OPTIONS["build"] = "static"
	end

	configuration "disable-wait"
		defines { "_NO_WAIT_FUNC" }

	project "pugixml"
		language "C++"
		location "build/pugixml"
		files { "src/pugixml/**.cpp", "src/pugixml/**.h" }

		configuration "static"
			kind "StaticLib"
		
		configuration "dynamic"
			kind "SharedLib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project "pugitmx-parser"
		language "C++"
		location "build/pugitmx-parser"
		files { "src/pugitmx-parser/**.cpp", "src/pugitmx-parser/**.h" }

		configuration "static"
			kind "StaticLib"
		
		configuration "dynamic"
			kind "SharedLib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
	
	
	project "ParadoxEngineLIB"
		language "C++"
		location "build/lib"
		links { "falcon_engine", "ParadoxEngineXSDLIB", "SDL", "SDLmain" }
		files { "src/lib/**.cpp", "src/lib/**.h" }

		configuration "static"
			kind "StaticLib"
		
		configuration "dynamic"
			kind "SharedLib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project "ParadoxEngineXSDLIB"
		language "C++"
		location "build/libxsd"
		links { "xerces-c" }
		files { "src/xsd/**.cpp", "src/xsd/**.h" }

		configuration "static"
			kind "StaticLib"
		
		configuration "dynamic"
			kind "SharedLib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project "ParadoxEngineSoundLib"
		language "C++"
		location "build/libsound"
		links { "sfml-audio", "sfml-system", "ParadoxEngineXSDLIB" }
		files { "src/sound/**.cpp", "src/sound/**.h" }

		configuration "static"
			kind "StaticLib"
	
		configuration "dynamic"
			kind "SharedLib"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project "ParadoxEngine"
		kind "ConsoleApp"
		language "C++"
		location "build/program"
		files { "src/main.*" }

		configuration "static"
			links { "ParadoxEngineLIB", "ParadoxEngineSoundLib", "ParadoxEngineXSDLIB", "sfml-audio", "sfml-system",  "PocoFoundation", "PocoUtil", "falcon_engine", "xerces-c", "pugixml", "SDL", "SDLmain" }

		configuration "dynamic"
			links { "ParadoxEngineLIB", "ParadoxEngineSoundLib", "ParadoxEngineXSDLIB", "PocoFoundation", "PocoUtil" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
		
