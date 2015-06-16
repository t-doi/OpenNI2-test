//---------------------------------------------------------------------------
#ifndef planeH
#define planeH
//向きを持つ平面を表す構造体plane.cpp,h
//要Vertex
//000203 doi
//αx+βy+γz+δ=0の式
//α^2+β^2+γ^2==1とする
//α，β，γの向きは変えてはいけない．
#include <vertex.h>
//---------------------------------------------------------------------------
struct Plane
{
 char flag_invalid;
 double alpha,beta,gamma,delta;//平面のパラメータ
 Vertex normal;//法線ベクトル
 char normalize(void);
 char line(Vertex start,Vertex dir,double *param_out);
  //↑直線と平面との交点を求める．始点の座標，方向ベクトル，出力先の順に入力
  //↑媒介変数表示
 char line(Vertex start,Vertex dir,Vertex *P_out);
  //↑直線と平面との交点を求める．始点の座標，方向ベクトル，出力先の順に入力
 char half_line(Vertex start,Vertex dir,Vertex *P_out);
  //↑半直線と平面との交点を求める．始点の座標，方向ベクトル，出力先の順に入力
 char front_or_not(Vertex point_in);
  //↑入力した点が面の表か裏かを判定
  //法線ベクトル側を”表”とする．
 char on_or_not(Vertex point_in);
  //↑入力点が，平面上に乗っているかどうか
 char define(Vertex vertex0_in,Vertex vector_in);
  //↑平面の定義．始点と方向ベクトル
 double distance(Vertex P_in);//点と平面との距離
};
//---------------------------------------------------------------------------
#endif
