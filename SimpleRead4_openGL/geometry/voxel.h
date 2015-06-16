//---------------------------------------------------------------------------
//voxelの構造体voxel.cpp,h
//mapを3次元に拡張したもの
//各voxelはchar型で，通常0か1しか入らない
#ifndef voxelH
#define voxelH
//---------------------------------------------------------------------------
struct Voxel
{
 double x0,x1,y0,y1,z0,z1;
 int mesh_x,mesh_y,mesh_z;
 double dx,dy,dz;
 char *flag;//ボクセル本体

 void array_allocate(int mesh_x_in,int mesh_y_in,int mesh_z_in);
  //↑領域確保
 void set_area(double x0_in,double x1_in,double y0_in,double y1_in,
              double z0_in,double z1_in);
  //↑全体の範囲決定と，dx,dy,dzの計算
 int index(int i,int j,int k);//3次元配列を1次元配列で表す際のインデックス
 char check(int i,int j,int k);//領域内外チェック
 int xtoi(double x_in);//実座標からセルのカウント数への変換
 int ytoj(double y_in);
 int ztok(double z_in);
 double itox(int i_in);//カウント数から，実座標への変換
 double jtoy(int j_in);//カウント数から，実座標への変換
 double ktoz(int k_in);//カウント数から，実座標への変換
};

//---------------------------------------------------------------------------
#endif
