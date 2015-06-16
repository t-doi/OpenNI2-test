//---------------------------------------------------------------------------
//rigid.cpp,h剛体の回転計算
//010626
#ifndef rigidH
#define rigidH
#include <vertex.h>
//---------------------------------------------------------------------------
char calc_rpy(Vertex z_axis2,Vertex x_axis2,
         double *roll_out, double *pitch_out, double *yaw_out);
//回転後のz軸，x軸の方向から，ロール，ピッチ，ヨーを求める関数
Vertex x_axis();//x軸を表すベクトルを返す
Vertex y_axis();
Vertex z_axis();
Vertex rotate(Vertex vector_in, Vertex dir_axis, double angle_in);
//↑原点を中心に任意の軸周りの回転
//---------------------------------------------------------------------------
#endif
