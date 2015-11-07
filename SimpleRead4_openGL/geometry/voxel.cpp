//---------------------------------------------------------------------------
//voxel�̍\����voxel.cpp,h
//map��3�����Ɋg����������
//�evoxel��char�^�ŁC�ʏ�0��1��������Ȃ�
#include <math.h>
#include "voxel.h"

//---------------------------------------------------------------------------
void Voxel::array_allocate(int mesh_x_in,int mesh_y_in,int mesh_z_in)
{
//���̈�m��
mesh_x=mesh_x_in;
mesh_y=mesh_y_in;
mesh_z=mesh_z_in;
flag=new char[mesh_x*mesh_y*mesh_z];
}
//---------------------------------------------------------------------------
void Voxel::set_area(double x0_in,double x1_in,double y0_in,double y1_in,
              double z0_in,double z1_in)
{
//���S�͈̂̔͌���ƁCdx,dy,dz�̌v�Z
x0=x0_in;
x1=x1_in;
y0=y0_in;
y1=y1_in;
z0=z0_in;
z1=z1_in;
dx=(x1-x0)/mesh_x;
dy=(y1-y0)/mesh_y;
dz=(z1-z0)/mesh_z;
}
//---------------------------------------------------------------------------
int Voxel::index(int i,int j,int k)
{
//3�����z���1�����z��ŕ\���ۂ̃C���f�b�N�X
return (mesh_x*mesh_y)*k+mesh_x*j+i;
}
//---------------------------------------------------------------------------
char Voxel::check(int i,int j,int k)
{
//�̈���O�`�F�b�N
if((i<0)||(i>=mesh_x))return 0;
if((j<0)||(j>=mesh_y))return 0;
if((k<0)||(k>=mesh_z))return 0;
return 1;
}
//---------------------------------------------------------------------------
int Voxel::xtoi(double x_in)
{
//�����W����Z���̃J�E���g���ւ̕ϊ�
return (int)((x_in-x0)/dx);
}
//---------------------------------------------------------------------------
int Voxel::ytoj(double y_in)
{
return (int)((y_in-y0)/dy);
}
//---------------------------------------------------------------------------
int Voxel::ztok(double z_in)
{
return (int)((z_in-z0)/dz);
}
//---------------------------------------------------------------------------
double Voxel::itox(int i_in)
{
//�J�E���g������C�����W�ւ̕ϊ�
return x0+(i_in+0.5)*dx;
}
//---------------------------------------------------------------------------
double Voxel::jtoy(int j_in)
{
//�J�E���g������C�����W�ւ̕ϊ�
return y0+(j_in+0.5)*dy;
}
//---------------------------------------------------------------------------
double Voxel::ktoz(int k_in)
{
//�J�E���g������C�����W�ւ̕ϊ�
return z0+(k_in+0.5)*dz;
}
//---------------------------------------------------------------------------
