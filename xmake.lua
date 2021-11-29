add_rules("mode.debug", "mode.release")
set_languages("c++14")

-- SDL2
add_requires("libsdl")

if is_os("windows") then
	-- Avoid for error LINK1561
	add_ldflags("/SUBSYSTEM:CONSOLE")
end

-- Main Renderer
target("DLSoftRenderer")
	set_kind("binary")
	add_includedirs("src/include")
	add_files("src/*.cpp")
	add_packages("libsdl")
