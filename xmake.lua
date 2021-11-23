add_rules("mode.debug", "mode.release")
add_cxxflags("-std=c++14")

target("DLSoftRenderer")
	set_kind("binary")
	add_includedirs("src/include")
	add_files("src/*.cpp")

	add_includedirs("third_party/SDL2-2.0.16/include")

	if is_os("windows") then
		add_ldflags("/SUBSYSTEM:CONSOLE")
		add_links("Shell32")
		add_linkdirs("third_party/SDL2-2.0.16/lib/win")
	elseif is_os("macosx") then
		add_linkdirs("third_party/SDL2-2.0.16/lib/mac")
	end

	add_links("SDL2main", "SDL2")
