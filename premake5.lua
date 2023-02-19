include "cpptutorial.lua"

workspace "CppTutorial"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./"

    include "./01_SimpleCApp/build.lua"
    include "./02_Pointers/build.lua"
    include "./03_MemoryUtils/build.lua"
    include "./04_INIParser/build.lua"
    include "./05_INIExplorer/build.lua"
    include "./06_AdvancedCStructs/build.lua"
    include "./07_SimpleCppApp/build.lua"
    include "./08_CatsAndDogs/build.lua"
    include "./09_INIpp/build.lua"

    group "Exercises"
        include "./Exercises/E01_Functions/build.lua"
    group ""
