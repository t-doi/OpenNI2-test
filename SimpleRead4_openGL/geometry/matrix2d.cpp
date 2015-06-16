//---------------------------------------------------------------------------
//Matrix2D
//画像比較用2次元画像情報格納クラス
//000417
//テンプレートだからか，このファイルをインクルードしてやらないと使えない

#include "matrix2d.h"
//---------------------------------------------------------------------------
#ifndef matrix2DCPP
#define matrix2DCPP
//↑２重読み込みを防ぐ
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::allocate(int mesh_i_in,int mesh_j_in)
{
//領域確保
mesh_i=mesh_i_in;
mesh_j=mesh_j_in;

cell_array=new T[(mesh_i_in*mesh_j_in)];
flag_array=new char[(mesh_i_in*mesh_j_in)];

if(!cell_array)
{
return 0;
}
  for(int i=0;i<(mesh_i_in*mesh_j_in);i++)
  {
   flag_array[i]=0;//初期化
  }

allocate_flag=1;
return 1;
}
//---------------------------------------------------------------------------
template <class T> int Matrix2D<T>::index(int i_in,int j_in)
{
//低レベルアクセス用インデックス関数
return (i_in+j_in*mesh_i);
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::write(T cell,int i_in,int j_in)
{
//入力
if(!allocate_flag)return 0;
if(!check(i_in,j_in))return 0;//チェックあり

cell_array[index(i_in,j_in)]=cell;
flag_array[index(i_in,j_in)]=1;//フラグ立て
return 1;
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::read(T *cell,int i_in,int j_in)
{
//出力
if(!allocate_flag)
  return 0;
if(!check(i_in,j_in))
  return 0;//チェックあり
if(!flag_array[index(i_in,j_in)])
 return 0;//データフラグのチェック
 
*cell=cell_array[index(i_in,j_in)];
return 1;
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::check(int i_in,int j_in)
{
//メッシュの数の範囲に入っているかどうか
if((i_in<0)||(i_in>=mesh_i))return 0;
if((j_in<0)||(j_in>=mesh_j))return 0;
return 1;
}
//---------------------------------------------------------------------------
template <class T> Matrix2D<T>::Matrix2D(void)
{
//コンストラクタ
allocate_flag=0;
}
//---------------------------------------------------------------------------
template <class T> void Matrix2D<T>::operator=(const Matrix2D<T>& rhs)
{
//代入関数
//allocateした後で使う

  for(int i=0;i<(mesh_i*mesh_j);i++)
  {
  cell_array[i]=rhs.cell_array[i];
  flag_array[i]=rhs.flag_array[i];
  }
}
//---------------------------------------------------------------------------
#endif
