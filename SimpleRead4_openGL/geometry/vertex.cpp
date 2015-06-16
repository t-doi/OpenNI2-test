//---------------------------------------------------------------------------
//vertex.cpp
//���_��\���N���X�D�召��r�C����̃����o�֐�������
#include "Vertex.h"
#include <math.h>
//---------------------------------------------------------------------------
void Vertex::operator= (const Vertex& rhs)
   {
   x=rhs.x;y=rhs.y;z=rhs.z;
   }
//---------------------------------------------------------------------------
char Vertex::nearly_equal(const Vertex& rhs)
{
double threshold=1.0e-15;
if(fabs(x-rhs.x)>threshold)return 0;
if(fabs(y-rhs.y)>threshold)return 0;
if(fabs(z-rhs.z)>threshold)return 0;
return 1;
}
//---------------------------------------------------------------------------
char Vertex::normalize(void)
{
//�x�N�g���̒����P�ɐ��K��
double mother_pow2,mother;
mother_pow2=x*x+y*y+z*z;
//if(mother_pow2==0)return 0;
if(mother_pow2<1.0e-15)return 0;
mother=sqrt(mother_pow2);
x=x/mother;
y=y/mother;
z=z/mother;
return 1;
}
//---------------------------------------------------------------------------
double Vertex::size()
{
//�x�N�g���̒���
return (
       sqrt(x*x+y*y+z*z )
       );
}
//---------------------------------------------------------------------------
void  Vertex::set(double x_in, double y_in, double z_in)
{
//�l���Z�b�g
x=x_in;y=y_in;z=z_in;
return;
}
//---------------------------------------------------------------------------
Vertex operator+ (const Vertex& lhs,const Vertex& rhs)
{
Vertex out_vertex;
out_vertex.x=lhs.x+rhs.x;
out_vertex.y=lhs.y+rhs.y;
out_vertex.z=lhs.z+rhs.z;
return out_vertex;
}
//---------------------------------------------------------------------------
Vertex operator- (const Vertex& lhs,const Vertex& rhs)
{
Vertex out_vertex;
out_vertex.x=lhs.x-rhs.x;
out_vertex.y=lhs.y-rhs.y;
out_vertex.z=lhs.z-rhs.z;
return out_vertex;
}
//---------------------------------------------------------------------------
double operator* (const Vertex& lhs,const Vertex& rhs)
{
//����
return (lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z);
}
//---------------------------------------------------------------------------
Vertex operator% (const double& lhs,const Vertex& rhs)
{
//�x�N�g���̒萔�{
Vertex out_vertex;
out_vertex.x=lhs*rhs.x;
out_vertex.y=lhs*rhs.y;
out_vertex.z=lhs*rhs.z;
return out_vertex;
}
//---------------------------------------------------------------------------
Vertex operator% (const Vertex& lhs,const Vertex& rhs)
{
//�O��
Vertex out_vertex;
out_vertex.x=lhs.y*rhs.z-lhs.z*rhs.y;
out_vertex.y=lhs.z*rhs.x-lhs.x*rhs.z;
out_vertex.z=lhs.x*rhs.y-lhs.y*rhs.x;
return out_vertex;
}
//---------------------------------------------------------------------------
bool operator< (const Vertex& lhs,const Vertex& rhs)
   {
   //x,y,z�̎������ɑ召��r
   if(lhs.x!=rhs.x)return(lhs.x<rhs.x);
   else if(lhs.y!=rhs.y)return(lhs.y<rhs.y);
   else if(lhs.z!=rhs.z)return(lhs.z<rhs.z);
   else return 0;
   }
//---------------------------------------------------------------------------
bool operator> (const Vertex& lhs,const Vertex& rhs)
   {
   //x,y,z�̎������ɑ召��r
   if(lhs.x!=rhs.x)return(lhs.x>rhs.x);
   else if(lhs.y!=rhs.y)return(lhs.y>rhs.y);
   else if(lhs.z!=rhs.z)return(lhs.z>rhs.z);
   else return 0;
   }
//---------------------------------------------------------------------------
bool operator== (const Vertex& lhs,const Vertex& rhs)
   {
   if(lhs.x!=rhs.x)return 0;
   else if(lhs.y!=rhs.y)return 0;
   else if(lhs.z!=rhs.z)return 0;
   else return 1;
   }
//---------------------------------------------------------------------------
bool operator!= (const Vertex& lhs,const Vertex& rhs)
   {
   if(lhs==rhs)return 0;
   else return 1;
   }
//---------------------------------------------------------------------------

