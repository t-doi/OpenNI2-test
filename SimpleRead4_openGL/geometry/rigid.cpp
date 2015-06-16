//---------------------------------------------------------------------------
//rigid.cpp,h剛体の回転計算
//010626
#include <math.h>
#include "rigid.h"

//---------------------------------------------------------------------------
char calc_rpy(Vertex z_axis2,Vertex x_axis2,
         double *roll_out, double *pitch_out, double *yaw_out)
{
//回転後のz軸，x軸の方向から，ロール，ピッチ，ヨーを求める関数
//裳華房　ロボット工学p147参照

double threshold=1.0e-6;
if(z_axis2.size()<threshold)return 0;
if(x_axis2.size()<threshold)return 0;
z_axis2.normalize();
x_axis2.normalize();
if(z_axis2*x_axis2>threshold)return 0;//直交していなかった場合

double roll=atan2(-z_axis2.y,z_axis2.z);
double pitch=atan2(cos(roll)*z_axis2.x,z_axis2.z);
double yaw=atan2(cos(pitch)*(cos(roll)*x_axis2.y+sin(roll)*x_axis2.z),
                        x_axis2.x);

*roll_out=roll;
*pitch_out=pitch;
*yaw_out=yaw;
return 1;
}
//---------------------------------------------------------------------------
Vertex rotate(Vertex vector_in, Vertex dir_axis, double angle_in)
{
//原点を中心に任意の軸周りのベクトルの回転
//ロボット工学p.11参照
//角度→ラジアン
double threshold=1.0e-6;
if(dir_axis.size()<threshold)return vector_in;//失敗→回転しない
Vertex tempv;
 tempv=(vector_in*dir_axis)%dir_axis+cos(angle_in)%(vector_in-(vector_in*dir_axis)%dir_axis)
 +sin(angle_in)%(dir_axis%vector_in);

return tempv;
}
//---------------------------------------------------------------------------
Vertex x_axis()
{
//x軸の値を返す
Vertex temp;
temp.x=1;temp.y=0;temp.z=0;
return temp;
}
//---------------------------------------------------------------------------
Vertex y_axis()
{
//y軸の値を返す
Vertex temp;
temp.x=0;temp.y=1;temp.z=0;
return temp;
}
//---------------------------------------------------------------------------
Vertex z_axis()
{
//z軸の値を返す
Vertex temp;
temp.x=0;temp.y=0;temp.z=1;
return temp;
}

