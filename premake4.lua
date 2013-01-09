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

configuration "windows"
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



