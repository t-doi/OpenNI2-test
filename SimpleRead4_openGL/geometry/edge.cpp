//---------------------------------------------------------------------------
//edge.cpp,edge.h
//���ʑ̂̕ӂ�\���N���X
//����C�召��r�C�R���X�g���N�^������

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
void Edge::Edge_swap(void)//�ӂ̏��ԓ���ւ�
   {
   Vertex temp=vertex1;vertex1=vertex2;vertex2=temp;
   }
//---------------------------------------------------------------------------
void Edge::vertex_order(void)//���Ԃ����������ɂ���D
   {
   if(vertex1>vertex2)
   Edge_swap();
   return;
   }
//---------------------------------------------------------------------------
void Edge::operator= (const Edge& rhs)//���
   {
   vertex1=rhs.vertex1;
   vertex2=rhs.vertex2;
   }
//---------------------------------------------------------------------------
bool operator< (const Edge& lhs,const Edge& rhs)//�召��r
   {
    return(lhs.vertex2<rhs.vertex2);
    //�ő�v�f�̔�r
   }
//---------------------------------------------------------------------------
bool operator== (const Edge& lhs,const Edge& rhs)//���l�`�F�b�N
   {
   if((lhs.vertex1==rhs.vertex1)&&(lhs.vertex2==rhs.vertex2))
      return 1;//�Ή����钸�_�����������`�F�b�N
   else if((lhs.vertex1==rhs.vertex2)&&(lhs.vertex2==rhs.vertex1))
      return 1;//�O�̂��߁C�t�������`�F�b�N
   else return 0;
   }
//---------------------------------------------------------------------------
char Edge::nearly_equal(const Edge& rhs)
{
//���ߎ��I�ɃC�R�[�����ǂ���
   if(vertex1.nearly_equal(rhs.vertex1)&&vertex2.nearly_equal(rhs.vertex2))
      return 1;//�Ή����钸�_�����������`�F�b�N
   else if(vertex2.nearly_equal(rhs.vertex1)&&vertex1.nearly_equal(rhs.vertex2))
      return 1;//�O�̂��߁C�t�������`�F�b�N
   else return 0;
}
//---------------------------------------------------------------------------

