//990924
//3次元ポリゴン計算クラスfacet.cpp,facet.h
//要Plane
//---------------------------------------------------------------------------
#ifndef pfacetH
#define pfacetH
#include <plane.h>
//---------------------------------------------------------------------------
class PFacet : public Plane
{
public:		// ユーザー宣言
  Vertex a,b,c;//3頂点の座標．表から見て反時計周り
  PFacet(void);//デフォルトコンストラクタ
  double menseki(void);//面積を算出
  char half_line(Vertex start,Vertex dir,Vertex *P_out);
  //↑半直線とポリゴンとの交点を求める．始点の座標，方向ベクトル，出力先の順に入力
  //ポリゴン内外チェックも含む
  char in_or_out(Vertex P_in);
  //↑Facetが属する平面上の任意の点に対して，それが
  //三角形内にあるかどうかを1or0で答える関数．1なら中
  void operator= (const PFacet& rhs);//代入演算子
  friend bool operator== (const PFacet& lhs,const PFacet& rhs);
  char abgd(void);//αβγδを計算する関数
  char set(Vertex v1_in,Vertex v2_in,Vertex v3_in);

};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

