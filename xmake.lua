add_rules("mode.debug", "mode.release")
add_cxxflags("-std=c++14")

-- SDL2
if is_os("windows") then
	add_ldflags("/SUBSYSTEM:CONSOLE")
	add_links("Shell32")
	add_includedirs("third_party/SDL2-2.0.16/include")
	add_linkdirs("third_party/SDL2-2.0.16/lib")
	add_links("SDL2main", "SDL2")
elseif is_os("macosx") then
	add_requires("brew::sdl2 2.0.16", { alias = "sdl2" })
	add_packages("sdl2")
end

-- Main Renderer
target("DLSoftRenderer")
	set_kind("binary")
	add_includedirs("src/include")
	add_files("src/*.cpp")
