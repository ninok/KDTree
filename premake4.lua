solution "KDTree"
	configurations	{ "Debug", "Release" }


project "KDTree"
	kind		"ConsoleApp"
	language	"C++"

files
{
	"src/*.h",
	"src/*.cpp"
}

pchheader "PCH.h"
pchsource "src/PCH.cpp"

configuration "windows"
    buildoptions { "-Zm256" }
    includedirs{
        "$(BOOSTDIR)",
        "$(GLMDIR)",
        "$(GLUTDIR)/include"
    }
    libdirs{
        "$(GLUTDIR)/lib/x86"
    }
    
configuration "macosx"
    includedirs{
        "../boost",
        "../glm"
    }
    links{
        "OpenGL.framework",
        "GLUT.framework"
    }



