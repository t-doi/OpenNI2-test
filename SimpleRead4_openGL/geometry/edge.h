//---------------------------------------------------------------------------
#ifndef edgeH
#define edgeH
#include "vertex.h"
//---------------------------------------------------------------------------
//�h�Ӂh�\���́DSTL�Ή�
//�vVertex
class Edge
{
private:	// ���[�U�[�錾
   void Edge_swap(void);
public:	// ���[�U�[�錾
   //�������ŏ������ق����P�Ƃ���
   Vertex vertex1,vertex2;
   Edge(void);//default
   void input(Vertex vertex_1_in,Vertex vertex_2_in);
   void vertex_order(void);//���Ԃ����������ɂ���D
   void operator= (const Edge& rhs);
   char nearly_equal(const Edge& rhs);
   //���ߎ��I�ɃC�R�[�����ǂ���

friend bool operator< (const Edge& lhs,const Edge& rhs);
friend bool operator== (const Edge& lhs,const Edge& rhs);
};
//---------------------------------------------------------------------------
#endif
