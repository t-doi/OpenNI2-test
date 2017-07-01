SRCS := OGL2D.cpp mouse_view.cpp gl_tools.cpp main.cpp 
SRCS2 := geometry/edge.cpp geometry/heightmap.cpp geometry/matrix2d.cpp geometry/OGLGeo.cpp geometry/pfacet.cpp geometry/plane.cpp geometry/rigid.cpp geometry/vertex.cpp geometry/voxel.cpp geometry/vxobj.cpp
WIN_LIB := mingw32_lib/libOpenNI2/libOpenNI2.a mingw32_lib/libfreeglut/libfreeglut.a

all: mingw

mingw:
	g++  $(SRCS) $(SRCS2) $(WIN_LIB) -o SimpleReadGL  -lopengl32 -lglu32 -lm  -I./openni2/include  -I./geometry 

linux:
	g++ $(SRCS) $(SRCS2) -o SimpleReadGL -lOpenNI2 -lglut -lGLU -lGL -lm -I/usr/include/openni2	-I./geometry 
