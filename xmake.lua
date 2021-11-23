add_rules("mode.debug", "mode.release")

target("DLSoftRenderer")
	set_kind("binary")
	add_includedirs("src/include")
	add_files("src/*.cpp")

	if is_plat("windows") then
		add_ldflags("/SUBSYSTEM:CONSOLE")
		add_links("Shell32")
	end

	add_includedirs("third_party/SDL2-2.0.16/include")
	add_linkdirs("third_party/SDL2-2.0.16/lib")
	add_links("SDL2main", "SDL2")