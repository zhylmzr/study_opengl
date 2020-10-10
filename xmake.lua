add_rules("mode.debug", "mode.release")

target("opengl_tutorial")
    set_kind("binary")
    add_frameworks("Cocoa", "IOKit")
    add_files("src/*.cpp", "lib/**/*.cpp", "lib/**/*.c")

    add_cflags('/source-charset:utf-8')
    add_cxxflags('/source-charset:utf-8')
    
    set_rundir("src")
    set_languages("c++11")
    add_includedirs("include")
    add_defines("STB_IMAGE_IMPLEMENTATION")
    
    if is_plat("windows") then
        add_links("gdi32", "shell32")

        add_linkdirs("lib")
        if is_arch("x64", "x86_64") then
            add_links("x64/glfw3")
        elseif is_arch("x86", "i386") then
            add_links("x86/glfw3")
        end
    end

    on_load(function (target)
        if is_plat("linux", "macosx") then
            target:add(find_packages("glfw3"))
        end
    end)
