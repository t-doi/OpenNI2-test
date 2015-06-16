//---------------------------------------------------------------------------
//�����������ʂ�\���\����plane.cpp,h
//000203 doi
//��x+��y+��z+��=0�̎�
//��^2+��^2+��^2==1�Ƃ���
#include <math.h>

#include "plane.h"
//---------------------------------------------------------------------------
char Plane::normalize(void)
{
//���ʂ̖@���x�N�g���̑傫����1�ɐ��K������
double mother;
//���@���x�N�g���̑傫���C���K�����������̕����x�N�g��
mother=sqrt(alpha*alpha+beta*beta+gamma*gamma);
  //if(mother==0)
  if(fabs(mother)<1.0e-10)
  {
  flag_invalid=1;
  return 0;
  }
alpha=alpha/mother;
beta=beta/mother;
gamma=gamma/mother;
delta=delta/mother;

//�@���x�N�g��
normal.x=alpha;
normal.y=beta;
normal.z=gamma;

flag_invalid=0;
return 1;
}
//---------------------------------------------------------------------------
char Plane::line(Vertex start,Vertex dir,double *param_out)
{
//���}��ϐ����g���Ē����ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���̏��ɓ���
//9/30�̃m�[�g�Q��
//�o�́F�}��ϐ�
double parameter1,parameter2;
double zero_temp=1.0e-10;//�[���̂����


parameter1=alpha*(dir.x)+beta*(dir.y)+gamma*(dir.z);
if(fabs(parameter1)<zero_temp)
//�������ƕ��ʖ@���x�N�g���Ƃ����������ʂƔ������Ƃ����s
return 0;

parameter2=-(alpha*(start.x)+beta*(start.y)+gamma*(start.z)+delta)
                                                         /parameter1;


*param_out=parameter2;

return 1;//����Ȍ�_�����݂���

}
//---------------------------------------------------------------------------
char Plane::line(Vertex start,Vertex dir,Vertex *P_out)
{
//�������ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���̏��ɓ���
double parameter;
Vertex temp;

 if(line(start,dir,(double*)&parameter)!=1)
  return 0;
 else 
  temp=(parameter)%(dir)+start;

*P_out=temp;
return 1;//����Ȍ�_�����݂���

}
//---------------------------------------------------------------------------
char Plane::half_line(Vertex start,Vertex dir,Vertex *P_out)
{
//���������ƕ��ʂƂ̌�_�����߂�D�n�_�̍��W�C�����x�N�g���̏��ɓ���

Vertex intersection;
double zero_temp=1.0e-10;
double param;

if(!line(start,dir,&intersection))return 0;

Vertex temp=intersection-start;
if(temp*dir<zero_temp)return 0;
//����_���C���������猩�Đ��̕����ɂ��邩�ǂ���


*P_out=intersection;
return 1;
}
//---------------------------------------------------------------------------
char Plane::front_or_not(Vertex point_in)
{
//�����͂����_���ʂ̕\�������𔻒�
//�@���x�N�g�������h�\�h�Ƃ���D
//���ʏ�ɏ���Ă���ꍇ���܂�
double zero_value=1.0e-10;//�[���̑���
double x_in=point_in.x;
double y_in=point_in.y;
double z_in=point_in.z;
return alpha*x_in+beta*y_in+gamma*z_in+delta > (-1*zero_value);
}
//---------------------------------------------------------------------------
char Plane::on_or_not(Vertex point_in)
{
//�����͓_���C���ʏ�ɏ���Ă��邩�ǂ���
double zero_value=1.0e-10;//�[���̑���
double x_in=point_in.x;
double y_in=point_in.y;
double z_in=point_in.z;
if(
     (alpha*x_in+beta*y_in+gamma*z_in+delta > (-1*zero_value))&&
     (alpha*x_in+beta*y_in+gamma*z_in+delta < (zero_value))
   )
return  1;
else return 0;
}
//---------------------------------------------------------------------------
char Plane::define(Vertex vertex0_in,Vertex vector_in)
{
//�����ʂ̒�`�D�n�_�ƕ����x�N�g��
alpha=vector_in.x;
beta=vector_in.y;
gamma=vector_in.z;
delta=-1*(alpha*(vertex0_in.x)+beta*(vertex0_in.y)+gamma*(vertex0_in.z));
if(!normalize())
return 0;

return 1;
}
//---------------------------------------------------------------------------
double Plane::distance(Vertex P_in)
{
//���_�ƕ��ʂƂ̋�����Ԃ��֐�
return (fabs(alpha*P_in.x+beta*P_in.y+gamma*P_in.z+delta));
}
//---------------------------------------------------------------------------

