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

links{
	"OpenGL.framework",
	"GLUT.framework"
}

includedirs{
	"../boost",
	"../glm"
}
