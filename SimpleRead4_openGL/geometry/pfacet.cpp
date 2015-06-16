//990924
//3�����|���S���v�Z�N���Xfacet.cpp,facet.h
#include <math.h>
#include "vertex.h"
#include "pfacet.h"
//------------------------------------------------------------
char PFacet::abgd(void)
{
//���������v�Z����֐�
Vertex ab,ac;
Vertex temp;

ab=b-a;
ac=c-a;
temp=(ab)%(ac);

alpha=temp.x;
beta=temp.y;
gamma=temp.z;

delta=-(alpha*(a.x)+beta*(a.y)+gamma*(a.z));
        if(!Plane::normalize())
        {
         flag_invalid=1;
        return 0;
        }
return 1;
}
//------------------------------------------------------------
PFacet::PFacet(void)//�f�t�H���g�R���X�g���N�^
{
}
//------------------------------------------------------------
double PFacet::menseki(void)
{
//�ʐς��Z�o
Vertex ab=b-a;
Vertex ac=c-a;
Vertex temp=(ab)%(ac);

double menseki_out=temp.size()/2;//3�p�`�̖ʐςȂ̂�2�Ŋ���
return menseki_out;
}
//------------------------------------------------------------
char PFacet::half_line(Vertex start,Vertex dir,Vertex *P_out)
{
//���������ƃ|���S���Ƃ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���̏��ɓ���
//PFacet���ɂ��邩�ǂ������`�F�b�N
//Plane�\���̂̓����֐��̃I�[�o�[���C�h
Vertex temp;

if(!Plane::half_line(start,dir,&temp))
return 0;//�����Ȃ�

if(!in_or_out(temp))
return 0;//��_��PFacet�O

*P_out=temp;
return 1;//����Ȍ�_�����݂���
}
//------------------------------------------------------------
char PFacet::in_or_out(Vertex P_in)
{
//��9/17�m�[�g�Q��
//��5/30����
//���͂����_�̍��W��PFacet���ɂ��邩�Ȃ����𔻒肷��֐�

Vertex ab,bc,ca;//�|���S����3�ӁD�\���猩�Ĕ����v����
Vertex ap,bp,cp;
ab=b-a;
bc=c-b;
ca=a-c;

ap=P_in-a;
bp=P_in-b;
cp=P_in-c;


double temp_zero=1.0e-10;
//double temp_zero=0;

if(
((ab%ap)*normal>-temp_zero)&&
((bc%bp)*normal>-temp_zero)&&
((ca%cp)*normal>-temp_zero)
)
return 1;

/*if(
((ab%ap)*normal<temp_zero)&&
((bc%bp)*normal<temp_zero)&&
((ca%cp)*normal<temp_zero)
)
return 1;//����͖{���Ȃ炠�肦�Ȃ��Da,b,c�̒�`�����t�H
*/

return 0;
}
//------------------------------------------------------------
char PFacet::set(Vertex a_in,Vertex b_in,Vertex c_in)
{
a=a_in;
b=b_in;
c=c_in;
return (abgd());
}
//------------------------------------------------------------
void PFacet::operator= (const PFacet& rhs)//������Z�q
{
a=rhs.a;
b=rhs.b;
c=rhs.c;
abgd();
}
//------------------------------------------------------------
bool operator== (const PFacet& lhs,const PFacet& rhs)
{
if(lhs.a!=rhs.a)return 0;
else if(lhs.b!=rhs.b)return 0;
else if(lhs.c!=rhs.c)return 0;
else return 1;
}
//------------------------------------------------------------


