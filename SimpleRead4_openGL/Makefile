all:
	g++ OGL.cpp OGL2D.cpp mouse_view.cpp main.cpp geometry/edge.cpp geometry/heightmap.cpp geometry/matrix2d.cpp geometry/OGLGeo.cpp geometry/pfacet.cpp geometry/plane.cpp geometry/rigid.cpp geometry/vertex.cpp geometry/voxel.cpp geometry/vxobj.cpp -o SimpleReadGL -lOpenNI2 -lglut -lGLU -lGL -lm -I/usr/include/openni2	-I./geometry 

mingw:
	g++ OGL2D.cpp mouse_view.cpp gl_tools.cpp main.cpp geometry/edge.cpp geometry/heightmap.cpp geometry/matrix2d.cpp geometry/OGLGeo.cpp geometry/pfacet.cpp geometry/plane.cpp geometry/rigid.cpp geometry/vertex.cpp geometry/voxel.cpp geometry/vxobj.cpp mingw32/libOpenNI2.a -o SimpleReadGL  -lopengl32 -lfreeglut -lglu32 -lm  -I./openni2/include  -L./lib -I./geometry 

