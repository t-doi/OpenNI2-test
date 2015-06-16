//---------------------------------------------------------------------------
//vertex.cpp
//頂点を表すクラス．大小比較，代入のメンバ関数を持つ
//ベクトルを表すのにも使える．→和，差，内積,外積
#ifndef VertexH
#define VertexH
//---------------------------------------------------------------------------
struct Vertex//convex hull用”頂点”構造体．STL対応
{
 double x;
 double y;
 double z;
 void operator= (const Vertex& rhs);
 char nearly_equal(const Vertex& rhs);
 char normalize(void);
 double size();//ベクトルの長さ
 void  set(double x_in, double y_in, double z_in);
 friend Vertex operator+ (const Vertex& lhs,const Vertex& rhs);//和
 friend Vertex operator- (const Vertex& lhs,const Vertex& rhs);//差
 friend double operator* (const Vertex& lhs,const Vertex& rhs);//内積
 friend Vertex operator% (const Vertex& lhs,const Vertex& rhs);//外積
 friend Vertex operator% (const double& lhs,const Vertex& rhs);//外積
 friend bool operator< (const Vertex& lhs,const Vertex& rhs);
 friend bool operator> (const Vertex& lhs,const Vertex& rhs);
 friend bool operator== (const Vertex& lhs,const Vertex& rhs);
 friend bool operator!= (const Vertex& lhs,const Vertex& rhs);
};
//---------------------------------------------------------------------------
#endif
