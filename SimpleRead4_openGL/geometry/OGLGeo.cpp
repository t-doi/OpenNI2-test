//---------------------------------------------------------------------------
//#include <windows.h>
#include "../vcsetting.h"
#include <GL/gl.h>
#include "OGLGeo.h"
#include <algorithm>
#include <functional>
#include "../gl_tools.h"

//---------------------------------------------------------------------------
void OGLGeo::vertex(Vertex &v_in)
{
//Vertex‚Ìƒ‚ƒfƒŠƒ“ƒO
glBegin(GL_POINTS);
  glVertex3d(v_in.x,v_in.y,v_in.z);
glEnd();
}
//---------------------------------------------------------------------------
void OGLGeo::edge(Edge &e_in)
{
//Edge
glBegin(GL_LINES);
  glVertex3d(e_in.vertex1.x,e_in.vertex1.y,e_in.vertex1.z);
  glVertex3d(e_in.vertex2.x,e_in.vertex2.y,e_in.vertex2.z);
glEnd();
}
//---------------------------------------------------------------------------
void OGLGeo::pfacet(PFacet &f_in)
{
//Facet
glBegin(GL_POLYGON);
    glNormal3d(f_in.alpha,f_in.beta,f_in.gamma);
    glVertex3d(f_in.a.x,f_in.a.y,f_in.a.z);
    glVertex3d(f_in.b.x,f_in.b.y,f_in.b.z);
    glVertex3d(f_in.c.x,f_in.c.y,f_in.c.z);
glEnd();
}
//---------------------------------------------------------------------------
void OGLGeo::pfacet2(PFacet &f_in)
{
//wireframe
//Facet
Edge e1,e2,e3;
e1.vertex1=f_in.b;e1.vertex2=f_in.c;
e2.vertex1=f_in.c;e2.vertex2=f_in.a;
e3.vertex1=f_in.a;e3.vertex2=f_in.b;
edge(e1);
edge(e2);
edge(e3);
}
//---------------------------------------------------------------------------
void OGLGeo::voxel(Voxel &v_in)
{
//Voxel
int i,j,k,index_temp;
for(k=0;k<v_in.mesh_z;k++)
{
for(j=0;j<v_in.mesh_y;j++)
{
for(i=0;i<v_in.mesh_x;i++)
{
   index_temp=v_in.index(i,j,k);
    if(v_in.flag[index_temp]!=0)
    {
    double x0=v_in.x0+i*v_in.dx;
    double x1=v_in.x0+(i+1)*v_in.dx;
    double y0=v_in.y0+j*v_in.dy;
    double y1=v_in.y0+(j+1)*v_in.dy;
    double z0=v_in.z0+k*v_in.dz;
    double z1=v_in.z0+(k+1)*v_in.dz;
    GL_Box(x0,x1,y0,y1,z0,z1);
    }
}
}
}

 }
//---------------------------------------------------------------------------
void OGLGeo::points(std::vector<Vertex> &vertices_ptr)
{
//std::for_each(vertices_ptr.begin(),vertices_ptr.end(),&OGLGeo::vertex);
int i;
int imax=vertices_ptr.size();
    for(i=0;i<imax;i++)
    {
        vertex(vertices_ptr[i]);

    }
}
//---------------------------------------------------------------------------
void OGLGeo::pfacets(std::vector<PFacet> &facets_ptr)
{
//std::for_each(facets_ptr.begin(),facets_ptr.end(),&OGLGeo::pfacet);
int i;
int imax=facets_ptr.size();
    for(i=0;i<imax;i++)
    {
        pfacet(facets_ptr[i]);

    }
}
//---------------------------------------------------------------------------
void OGLGeo::pfacets2(std::vector<PFacet> &facets_ptr)
{
//wireframe
//std::for_each(facets_ptr.begin(),facets_ptr.end(),&OGLGeo::pfacet2);
int i;
int imax=facets_ptr.size();
    for(i=0;i<imax;i++)
    {
        pfacet2(facets_ptr[i]);

    }
}
//---------------------------------------------------------------------------
void OGLGeo::voxel2(Voxel &voxel_in)
{
//ƒ{ƒNƒZƒ‹ƒ‚ƒfƒŠƒ“ƒOŠÖ”2
//“_‚ðo—Í
//GLfloat materialBlue[]={0.2f,0.4f,1.0f,0.5f};
//glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialBlue);

for(int k=0;k<voxel_in.mesh_z;k++)
{
for(int j=0;j<voxel_in.mesh_y;j++)
{
for(int i=0;i<voxel_in.mesh_x;i++)
{
  if(voxel_in.flag[voxel_in.index(i,j,k)])
  {
  glBegin(GL_POINTS);
    glVertex3d(voxel_in.itox(i),voxel_in.jtoy(j),voxel_in.ktoz(k));
  glEnd();
  }
}
}
}

}
//---------------------------------------------------------------------------
void OGLGeo::voxel_all(Voxel &voxel_in)
{
//‘Sƒ{ƒNƒZƒ‹•`‰æ
//“_‚ðo—Í
GLfloat materialBlue[]={0.2f,0.4f,1.0f,0.5f};
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialBlue);

for(int k=0;k<voxel_in.mesh_z;k++)
{
for(int j=0;j<voxel_in.mesh_y;j++)
{
for(int i=0;i<voxel_in.mesh_x;i++)
{
  glBegin(GL_POINTS);
    glVertex3d(voxel_in.itox(i),voxel_in.jtoy(j),voxel_in.ktoz(k));
  glEnd();
}
}
}

}
//---------------------------------------------------------------------------
void OGLGeo::heightmap(HeightMap &map_in)
{
//‚‚³’n}‚Ì•`‰æ
GLfloat materialTop[]={0.2f,1.0f,0.4f,0.5f};//ã–Ê‚ÌF
GLfloat materialSide[]={0.9f,0.8f,0.4f,0.5f};//‘¤–Ê

double x0,x1,y0,y1,z0,z1;
 for(int j=0;j<map_in.mesh_j;j++)
 {
 for(int i=0;i<map_in.mesh_i;i++)
 {
  x0=map_in.x0+i*map_in.dx;
  x1=map_in.x0+(i+1)*map_in.dx;
  y0=map_in.y0+j*map_in.dy;
  y1=map_in.y0+(j+1)*map_in.dy;
  z0=map_in.z0;

   if(map_in.read(&z1,i,j))
   {
    //ã–Ê
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialTop);
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    glVertex3d(x0,y0,z1);
    glVertex3d(x1,y0,z1);
    glVertex3d(x1,y1,z1);
    glVertex3d(x0,y1,z1);
    glEnd();

    //‘¤–Ê
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,materialSide);
    glBegin(GL_POLYGON);
    glNormal3d(1,0,0);
    glVertex3d(x1,y0,z0);
    glVertex3d(x1,y1,z0);
    glVertex3d(x1,y1,z1);
    glVertex3d(x1,y0,z1);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3d(-1,0,0);
    glVertex3d(x0,y0,z0);
    glVertex3d(x0,y0,z1);
    glVertex3d(x0,y1,z1);
    glVertex3d(x0,y1,z0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3d(0,1,0);
    glVertex3d(x0,y1,z0);
    glVertex3d(x0,y1,z1);
    glVertex3d(x1,y1,z1);
    glVertex3d(x1,y1,z0);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3d(0,-1,0);
    glVertex3d(x0,y0,z0);
    glVertex3d(x1,y0,z0);
    glVertex3d(x1,y0,z1);
    glVertex3d(x0,y0,z1);
    glEnd();
   }
 }
 }
}
//---------------------------------------------------------------------------
void OGLGeo::heightmap2(HeightMap &map_in)
{
//‚‚³’n}‚Ì•`‰æ‚»‚Ì‚QDƒ|ƒŠƒSƒ“‚ðŽg‚¤
PFacet facet1,facet2;
Vertex p00,p01,p10,p11;
double x0,y0,x1,y1;
 for(int j=0;j<map_in.mesh_j-1;j++)
 {
 for(int i=0;i<map_in.mesh_i-1;i++)
 {
  x0=map_in.itox(i);
  x1=map_in.itox(i+1);
  y0=map_in.jtoy(j);
  y1=map_in.jtoy(j+1);
  p00.x=x0;
  p00.y=y0;
  p01.x=x0;
  p01.y=y1;
  p10.x=x1;
  p10.y=y0;
  p11.x=x1;
  p11.y=y1;
   if(
    (map_in.read(&p00.z,i,j))&&
    (map_in.read(&p10.z,i+1,j))&&
    (map_in.read(&p01.z,i,j+1))
    )
   {
   facet1.a=p00;
   facet1.b=p10;
   facet1.c=p01;
   facet1.abgd();
   pfacet(facet1);
   }

   if(
    (map_in.read(&p10.z,i+1,j))&&
    (map_in.read(&p11.z,i+1,j+1))&&
    (map_in.read(&p01.z,i,j+1))
    )
   {
   facet2.a=p10;
   facet2.b=p11;
   facet2.c=p01;
   facet2.abgd();
   pfacet(facet2);
   }

 }
 }
}
//---------------------------------------------------------------------------
void OGLGeo::heightmap2a(HeightMap &map_in, double rangeH, double rangeL)
{
//‚‚³’n}‚Ì•`‰æ‚»‚Ì‚QADƒ|ƒŠƒSƒ“‚ðŽg‚¤
//‚‚³‚É‚æ‚Á‚ÄF‚ð•Ï‚¦‚é
	PFacet facet1,facet2;
Vertex p00,p01,p10,p11;
double x0,y0,x1,y1;
double h_ratio;


for(int j=0;j<map_in.mesh_j-1;j++)
 {
 for(int i=0;i<map_in.mesh_i-1;i++)
 {
  x0=map_in.itox(i);
  x1=map_in.itox(i+1);
  y0=map_in.jtoy(j);
  y1=map_in.jtoy(j+1);
  p00.x=x0;
  p00.y=y0;
  p01.x=x0;
  p01.y=y1;
  p10.x=x1;
  p10.y=y0;
  p11.x=x1;
  p11.y=y1;
   if(
    (map_in.read(&p00.z,i,j))&&
    (map_in.read(&p10.z,i+1,j))&&
    (map_in.read(&p01.z,i,j+1))
    )
   {
   facet1.a=p00;
   facet1.b=p10;
   facet1.c=p01;
   facet1.abgd();
   h_ratio=(facet1.a.z-rangeL)/(rangeH-rangeL);
   if(h_ratio>1)h_ratio=1;
   if(h_ratio<0)h_ratio=0;
//   set_material(0,h_ratio,0,1);
   GL_set_material(1-h_ratio,h_ratio,1-h_ratio,1);
   pfacet(facet1);
   }

   if(
    (map_in.read(&p10.z,i+1,j))&&
    (map_in.read(&p11.z,i+1,j+1))&&
    (map_in.read(&p01.z,i,j+1))
    )
   {
   facet2.a=p10;
   facet2.b=p11;
   facet2.c=p01;
   facet2.abgd();
   h_ratio=(facet1.a.z-rangeL)/(rangeH-rangeL);
   if(h_ratio>1)h_ratio=1;
   if(h_ratio<0)h_ratio=0;
   GL_set_material(1-h_ratio,h_ratio,1-h_ratio,1);
   pfacet(facet2);
   }

 }
 }
}
//---------------------------------------------------------------------------
void OGLGeo::heightmap3(HeightMap &map_in)
{
//‚‚³’n}‚Ì•`‰æDã–Ê‚Ì‚Ý
double x0,x1,y0,y1,z0,z1;
 for(int j=0;j<map_in.mesh_j;j++)
 {
 for(int i=0;i<map_in.mesh_i;i++)
 {
  x0=map_in.x0+i*map_in.dx;
  x1=map_in.x0+(i+1)*map_in.dx;
  y0=map_in.y0+j*map_in.dy;
  y1=map_in.y0+(j+1)*map_in.dy;
//  z0=map_in.z0;

   if(map_in.read(&z1,i,j))
   {
    //ã–Ê
    glBegin(GL_POLYGON);
    glNormal3d(0,0,1);
    glVertex3d(x0,y0,z1);
    glVertex3d(x1,y0,z1);
    glVertex3d(x1,y1,z1);
    glVertex3d(x0,y1,z1);
    glEnd();
   }
 }
 }
}
//---------------------------------------------------------------------------
void OGLGeo::arrow(Vertex org_in, Vertex dst_in,double size)
{
//–îˆó
glBegin(GL_LINES);
  glVertex3d(org_in.x,org_in.y,org_in.z);
  glVertex3d(dst_in.x,dst_in.y,dst_in.z);
glEnd();
glPointSize(3);
glBegin(GL_POINTS);
  glVertex3d(dst_in.x,dst_in.y,dst_in.z);
glEnd();

double temp_zero=1.0e-10;
Vertex y_axis,x_axis;
x_axis.set(1,0,0);
y_axis.set(0,1,0);
Vertex dir,wing1,wing2;//ƒxƒNƒgƒ‹‚Ì•ûŒü‚Æ–îˆó‚Ì‰H‚ÌŒü‚«
dir=dst_in-org_in;
if((dir%x_axis).size()<temp_zero)wing1=(dir%y_axis);
else wing1=(dir%x_axis);
wing2=(dir%wing1);
wing1.normalize();
wing2.normalize();

if(size<temp_zero)size=0.5*(dir.size());
dir.normalize();
Vertex wing_org=dst_in-size%dir;//‰H‚Ì•t‚¯ªˆÊ’u
Vertex wing_top[4];//‰Hæ’[
wing_top[0]=wing_org+0.5*size%wing1;
wing_top[1]=wing_org-0.5*size%wing1;
wing_top[2]=wing_org+0.5*size%wing2;
wing_top[3]=wing_org-0.5*size%wing2;

 for(int i=0;i<4;i++)
 {
 glBegin(GL_LINE_LOOP);
  glVertex3d(wing_org.x,wing_org.y,wing_org.z);
  glVertex3d(wing_top[i].x,wing_top[i].y,wing_top[i].z);
  glVertex3d(dst_in.x,dst_in.y,dst_in.z);
 glEnd();
 }

}
//---------------------------------------------------------------------------

