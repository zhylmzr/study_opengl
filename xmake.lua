add_rules("mode.debug", "mode.release")

target("opengl_tutorial")
    set_kind("binary")
    add_frameworks("Cocoa", "IOKit")
    add_files("src/*.cpp", "lib/**/*.cpp", "lib/**/*.c")
    
    set_rundir("src")
    set_languages("c++11")
    add_includedirs("include")
    add_defines("STB_IMAGE_IMPLEMENTATION")
    
    if is_plat("windows") then
        add_linkdirs("lib")
        add_links("glfw")
    end

    on_load(function (target)
        if is_plat("linux", "macosx") then
            target:add(find_packages("glfw3"))
        end
    end)