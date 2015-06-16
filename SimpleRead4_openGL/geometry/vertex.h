//---------------------------------------------------------------------------
//vertex.cpp
//���_��\���N���X�D�召��r�C����̃����o�֐�������
//�x�N�g����\���̂ɂ��g����D���a�C���C����,�O��
#ifndef VertexH
#define VertexH
//---------------------------------------------------------------------------
struct Vertex//convex hull�p�h���_�h�\���́DSTL�Ή�
{
 double x;
 double y;
 double z;
 void operator= (const Vertex& rhs);
 char nearly_equal(const Vertex& rhs);
 char normalize(void);
 double size();//�x�N�g���̒���
 void  set(double x_in, double y_in, double z_in);
 friend Vertex operator+ (const Vertex& lhs,const Vertex& rhs);//�a
 friend Vertex operator- (const Vertex& lhs,const Vertex& rhs);//��
 friend double operator* (const Vertex& lhs,const Vertex& rhs);//����
 friend Vertex operator% (const Vertex& lhs,const Vertex& rhs);//�O��
 friend Vertex operator% (const double& lhs,const Vertex& rhs);//�O��
 friend bool operator< (const Vertex& lhs,const Vertex& rhs);
 friend bool operator> (const Vertex& lhs,const Vertex& rhs);
 friend bool operator== (const Vertex& lhs,const Vertex& rhs);
 friend bool operator!= (const Vertex& lhs,const Vertex& rhs);
};
//---------------------------------------------------------------------------
#endif
