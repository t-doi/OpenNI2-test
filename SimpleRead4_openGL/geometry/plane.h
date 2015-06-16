//---------------------------------------------------------------------------
#ifndef planeH
#define planeH
//�����������ʂ�\���\����plane.cpp,h
//�vVertex
//000203 doi
//��x+��y+��z+��=0�̎�
//��^2+��^2+��^2==1�Ƃ���
//���C���C���̌����͕ς��Ă͂����Ȃ��D
#include <vertex.h>
//---------------------------------------------------------------------------
struct Plane
{
 char flag_invalid;
 double alpha,beta,gamma,delta;//���ʂ̃p�����[�^
 Vertex normal;//�@���x�N�g��
 char normalize(void);
 char line(Vertex start,Vertex dir,double *param_out);
  //�������ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���C�o�͐�̏��ɓ���
  //���}��ϐ��\��
 char line(Vertex start,Vertex dir,Vertex *P_out);
  //�������ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���C�o�͐�̏��ɓ���
 char half_line(Vertex start,Vertex dir,Vertex *P_out);
  //���������ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���C�o�͐�̏��ɓ���
 char front_or_not(Vertex point_in);
  //�����͂����_���ʂ̕\�������𔻒�
  //�@���x�N�g�������h�\�h�Ƃ���D
 char on_or_not(Vertex point_in);
  //�����͓_���C���ʏ�ɏ���Ă��邩�ǂ���
 char define(Vertex vertex0_in,Vertex vector_in);
  //�����ʂ̒�`�D�n�_�ƕ����x�N�g��
 double distance(Vertex P_in);//�_�ƕ��ʂƂ̋���
};
//---------------------------------------------------------------------------
#endif
