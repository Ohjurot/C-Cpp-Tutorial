function cpptNewProject(projectName, src)
    srcdir = projectName
    if src ~= nil then
        srcdir = src
    end

    project(projectName)
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"

        targetdir "%{wks.location}/build/bin/%{cfg.architecture}-%{cfg.buildcfg}/"
        objdir "%{wks.location}/build/obj/%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}/"

        location("%{wks.location}/" .. srcdir)
        files { 
            "%{prj.location}/**.h", "%{prj.location}/**.hpp", "%{prj.location}/**.hh", "%{prj.location}/**.hxx",  
            "%{prj.location}/**.c", "%{prj.location}/**.cpp", "%{prj.location}/**.cc", "%{prj.location}/**.cxx",
            "%{prj.location}/**.lua", "%{prj.location}/**.txt", "%{prj.location}/**.md", "%{prj.location}/**.ini",
        }
        includedirs { "%{wks.location}", "%{prj.location}" }

        defines { "__%{prj.name}_BUILD" }

        filter "configurations:Debug"
            defines { "DEBUG", "_DEBUG" }
            symbols "On"
        filter {}

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        filter {}
end

function cpptSetSharedLib()
    kind "SharedLib"
    defines { "__%{prj.name}_BUILD_DLL" }
end
