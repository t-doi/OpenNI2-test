//---------------------------------------------------------------------------
//向きを持つ平面を表す構造体plane.cpp,h
//000203 doi
//αx+βy+γz+δ=0の式
//α^2+β^2+γ^2==1とする
#include <math.h>

#include "plane.h"
//---------------------------------------------------------------------------
char Plane::normalize(void)
{
//平面の法線ベクトルの大きさを1に正規化する
double mother;
//↑法線ベクトルの大きさ，正規化した直線の方向ベクトル
mother=sqrt(alpha*alpha+beta*beta+gamma*gamma);
  //if(mother==0)
  if(fabs(mother)<1.0e-10)
  {
  flag_invalid=1;
  return 0;
  }
alpha=alpha/mother;
beta=beta/mother;
gamma=gamma/mother;
delta=delta/mother;

//法線ベクトル
normal.x=alpha;
normal.y=beta;
normal.z=gamma;

flag_invalid=0;
return 1;
}
//---------------------------------------------------------------------------
char Plane::line(Vertex start,Vertex dir,double *param_out)
{
//↑媒介変数を使って直線と平面との交点を求める．始点の座標，方向ベクトルの順に入力
//9/30のノート参照
//出力：媒介変数
double parameter1,parameter2;
double zero_temp=1.0e-10;//ゼロのかわり


parameter1=alpha*(dir.x)+beta*(dir.y)+gamma*(dir.z);
if(fabs(parameter1)<zero_temp)
//半直線と平面法線ベクトルとが直交→平面と半直線とが平行
return 0;

parameter2=-(alpha*(start.x)+beta*(start.y)+gamma*(start.z)+delta)
                                                         /parameter1;


*param_out=parameter2;

return 1;//正常な交点が存在する

}
//---------------------------------------------------------------------------
char Plane::line(Vertex start,Vertex dir,Vertex *P_out)
{
//↑直線と平面との交点を求める．始点の座標，方向ベクトルの順に入力
double parameter;
Vertex temp;

 if(line(start,dir,(double*)&parameter)!=1)
  return 0;
 else 
  temp=(parameter)%(dir)+start;

*P_out=temp;
return 1;//正常な交点が存在する

}
//---------------------------------------------------------------------------
char Plane::half_line(Vertex start,Vertex dir,Vertex *P_out)
{
//↑半直線と平面との交点を求める．始点の座標，方向ベクトルの順に入力

Vertex intersection;
double zero_temp=1.0e-10;
double param;

if(!line(start,dir,&intersection))return 0;

Vertex temp=intersection-start;
if(temp*dir<zero_temp)return 0;
//↑交点が，半直線から見て正の方向にあるかどうか


*P_out=intersection;
return 1;
}
//---------------------------------------------------------------------------
char Plane::front_or_not(Vertex point_in)
{
//↑入力した点が面の表か裏かを判定
//法線ベクトル側を”表”とする．
//平面上に乗っている場合も含む
double zero_value=1.0e-10;//ゼロの代わり
double x_in=point_in.x;
double y_in=point_in.y;
double z_in=point_in.z;
return alpha*x_in+beta*y_in+gamma*z_in+delta > (-1*zero_value);
}
//---------------------------------------------------------------------------
char Plane::on_or_not(Vertex point_in)
{
//↑入力点が，平面上に乗っているかどうか
double zero_value=1.0e-10;//ゼロの代わり
double x_in=point_in.x;
double y_in=point_in.y;
double z_in=point_in.z;
if(
     (alpha*x_in+beta*y_in+gamma*z_in+delta > (-1*zero_value))&&
     (alpha*x_in+beta*y_in+gamma*z_in+delta < (zero_value))
   )
return  1;
else return 0;
}
//---------------------------------------------------------------------------
char Plane::define(Vertex vertex0_in,Vertex vector_in)
{
//↑平面の定義．始点と方向ベクトル
alpha=vector_in.x;
beta=vector_in.y;
gamma=vector_in.z;
delta=-1*(alpha*(vertex0_in.x)+beta*(vertex0_in.y)+gamma*(vertex0_in.z));
if(!normalize())
return 0;

return 1;
}
//---------------------------------------------------------------------------
double Plane::distance(Vertex P_in)
{
//↑点と平面との距離を返す関数
return (fabs(alpha*P_in.x+beta*P_in.y+gamma*P_in.z+delta));
}
//---------------------------------------------------------------------------

