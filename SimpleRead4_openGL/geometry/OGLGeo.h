//---------------------------------------------------------------------------
#ifndef OGLgeoH
#define OGLgeoH
#include "vertex.h"
#include "edge.h"
#include "pfacet.h"
#include "voxel.h"
#include "heightmap.h"
#include "vector"
//---------------------------------------------------------------------------
class OGLGeo
{
public:
        void vertex(Vertex &v_in);
        void edge(Edge &e_in);
        void pfacet(PFacet &f_in);
        void pfacet2(PFacet &f_in);//wireframe
        void voxel(Voxel &v_in);
        void heightmap(HeightMap &map_in);
        void heightmap2(HeightMap &map_in);
        void heightmap3(HeightMap &map_in);
        void heightmap2a(HeightMap &map_in, double rangeH, double rangeL);

        void points(std::vector<Vertex> &vertices_ptr);
        void pfacets(std::vector<PFacet> &facets_ptr);
        void pfacets2(std::vector<PFacet> &facets_ptr);//wireframe
        void voxel2(Voxel &voxel_in);
        void voxel_all(Voxel &voxel_in);//‘Sƒ{ƒNƒZƒ‹•`‰æ

	void arrow(Vertex org_in, Vertex dst_in,double size);//–îˆó‚ð•`‚­
};
//---------------------------------------------------------------------------
#endif
