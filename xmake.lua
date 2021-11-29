add_rules("mode.debug", "mode.release")
set_languages("c++14")

-- SDL2
add_requires("libsdl")

-- Main Renderer
target("DLSoftRenderer")
	set_kind("binary")
	add_includedirs("src/include")
	add_files("src/*.cpp")
	add_packages("libsdl")
