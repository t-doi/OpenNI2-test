//---------------------------------------------------------------------------
//voxelの構造体voxel.cpp,h
//mapを3次元に拡張したもの
//各voxelはchar型で，通常0か1しか入らない
#include <math.h>
#include "voxel.h"

//---------------------------------------------------------------------------
void Voxel::array_allocate(int mesh_x_in,int mesh_y_in,int mesh_z_in)
{
//↑領域確保
mesh_x=mesh_x_in;
mesh_y=mesh_y_in;
mesh_z=mesh_z_in;
flag=new char[mesh_x*mesh_y*mesh_z];
}
//---------------------------------------------------------------------------
void Voxel::set_area(double x0_in,double x1_in,double y0_in,double y1_in,
              double z0_in,double z1_in)
{
//↑全体の範囲決定と，dx,dy,dzの計算
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
//3次元配列を1次元配列で表す際のインデックス
return (mesh_x*mesh_y)*k+mesh_x*j+i;
}
//---------------------------------------------------------------------------
char Voxel::check(int i,int j,int k)
{
//領域内外チェック
if((i<0)||(i>=mesh_x))return 0;
if((j<0)||(j>=mesh_y))return 0;
if((k<0)||(k>=mesh_z))return 0;
return 1;
}
//---------------------------------------------------------------------------
int Voxel::xtoi(double x_in)
{
//実座標からセルのカウント数への変換
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
//カウント数から，実座標への変換
return x0+(i_in+0.5)*dx;
}
//---------------------------------------------------------------------------
double Voxel::jtoy(int j_in)
{
//カウント数から，実座標への変換
return y0+(j_in+0.5)*dy;
}
//---------------------------------------------------------------------------
double Voxel::ktoz(int k_in)
{
//カウント数から，実座標への変換
return z0+(k_in+0.5)*dz;
}
//---------------------------------------------------------------------------
