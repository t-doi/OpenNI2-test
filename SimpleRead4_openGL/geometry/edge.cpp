//---------------------------------------------------------------------------
//edge.cpp,edge.h
//多面体の辺を表すクラス
//代入，大小比較，コンストラクタを持つ

#include "edge.h"
//---------------------------------------------------------------------------
Edge::Edge(void)//default
{
;
}
//---------------------------------------------------------------------------
void Edge::input(Vertex vertex_1_in,Vertex vertex_2_in)
{
vertex1=vertex_1_in;
vertex2=vertex_2_in;
vertex_order();
}
//---------------------------------------------------------------------------
void Edge::Edge_swap(void)//辺の順番入れ替え
   {
   Vertex temp=vertex1;vertex1=vertex2;vertex2=temp;
   }
//---------------------------------------------------------------------------
void Edge::vertex_order(void)//順番を小さい順にする．
   {
   if(vertex1>vertex2)
   Edge_swap();
   return;
   }
//---------------------------------------------------------------------------
void Edge::operator= (const Edge& rhs)//代入
   {
   vertex1=rhs.vertex1;
   vertex2=rhs.vertex2;
   }
//---------------------------------------------------------------------------
bool operator< (const Edge& lhs,const Edge& rhs)//大小比較
   {
    return(lhs.vertex2<rhs.vertex2);
    //最大要素の比較
   }
//---------------------------------------------------------------------------
bool operator== (const Edge& lhs,const Edge& rhs)//同値チェック
   {
   if((lhs.vertex1==rhs.vertex1)&&(lhs.vertex2==rhs.vertex2))
      return 1;//対応する頂点が等しいかチェック
   else if((lhs.vertex1==rhs.vertex2)&&(lhs.vertex2==rhs.vertex1))
      return 1;//念のため，逆向きもチェック
   else return 0;
   }
//---------------------------------------------------------------------------
char Edge::nearly_equal(const Edge& rhs)
{
//↑近似的にイコールかどうか
   if(vertex1.nearly_equal(rhs.vertex1)&&vertex2.nearly_equal(rhs.vertex2))
      return 1;//対応する頂点が等しいかチェック
   else if(vertex2.nearly_equal(rhs.vertex1)&&vertex1.nearly_equal(rhs.vertex2))
      return 1;//念のため，逆向きもチェック
   else return 0;
}
//---------------------------------------------------------------------------

