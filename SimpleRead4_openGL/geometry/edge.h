//---------------------------------------------------------------------------
#ifndef edgeH
#define edgeH
#include "vertex.h"
//---------------------------------------------------------------------------
//”辺”構造体．STL対応
//要Vertex
class Edge
{
private:	// ユーザー宣言
   void Edge_swap(void);
public:	// ユーザー宣言
   //辞書順で小さいほうを１とする
   Vertex vertex1,vertex2;
   Edge(void);//default
   void input(Vertex vertex_1_in,Vertex vertex_2_in);
   void vertex_order(void);//順番を小さい順にする．
   void operator= (const Edge& rhs);
   char nearly_equal(const Edge& rhs);
   //↑近似的にイコールかどうか

friend bool operator< (const Edge& lhs,const Edge& rhs);
friend bool operator== (const Edge& lhs,const Edge& rhs);
};
//---------------------------------------------------------------------------
#endif
