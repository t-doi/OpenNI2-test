//990924
//3�����|���S���v�Z�N���Xfacet.cpp,facet.h
//�vPlane
//---------------------------------------------------------------------------
#ifndef pfacetH
#define pfacetH
#include <plane.h>
//---------------------------------------------------------------------------
class PFacet : public Plane
{
public:		// ���[�U�[�錾
  Vertex a,b,c;//3���_�̍��W�D�\���猩�Ĕ����v����
  PFacet(void);//�f�t�H���g�R���X�g���N�^
  double menseki(void);//�ʐς��Z�o
  char half_line(Vertex start,Vertex dir,Vertex *P_out);
  //���������ƃ|���S���Ƃ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���C�o�͐�̏��ɓ���
  //�|���S�����O�`�F�b�N���܂�
  char in_or_out(Vertex P_in);
  //��Facet�������镽�ʏ�̔C�ӂ̓_�ɑ΂��āC���ꂪ
  //�O�p�`���ɂ��邩�ǂ�����1or0�œ�����֐��D1�Ȃ璆
  void operator= (const PFacet& rhs);//������Z�q
  friend bool operator== (const PFacet& lhs,const PFacet& rhs);
  char abgd(void);//���������v�Z����֐�
  char set(Vertex v1_in,Vertex v2_in,Vertex v3_in);

};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

