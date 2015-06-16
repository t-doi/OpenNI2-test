//---------------------------------------------------------------------------
//rigid.cpp,h���̂̉�]�v�Z
//010626
#include <math.h>
#include "rigid.h"

//---------------------------------------------------------------------------
char calc_rpy(Vertex z_axis2,Vertex x_axis2,
         double *roll_out, double *pitch_out, double *yaw_out)
{
//��]���z���Cx���̕�������C���[���C�s�b�`�C���[�����߂�֐�
//�։ؖ[�@���{�b�g�H�wp147�Q��

double threshold=1.0e-6;
if(z_axis2.size()<threshold)return 0;
if(x_axis2.size()<threshold)return 0;
z_axis2.normalize();
x_axis2.normalize();
if(z_axis2*x_axis2>threshold)return 0;//�������Ă��Ȃ������ꍇ

double roll=atan2(-z_axis2.y,z_axis2.z);
double pitch=atan2(cos(roll)*z_axis2.x,z_axis2.z);
double yaw=atan2(cos(pitch)*(cos(roll)*x_axis2.y+sin(roll)*x_axis2.z),
                        x_axis2.x);

*roll_out=roll;
*pitch_out=pitch;
*yaw_out=yaw;
return 1;
}
//---------------------------------------------------------------------------
Vertex rotate(Vertex vector_in, Vertex dir_axis, double angle_in)
{
//���_�𒆐S�ɔC�ӂ̎�����̃x�N�g���̉�]
//���{�b�g�H�wp.11�Q��
//�p�x�����W�A��
double threshold=1.0e-6;
if(dir_axis.size()<threshold)return vector_in;//���s����]���Ȃ�
Vertex tempv;
 tempv=(vector_in*dir_axis)%dir_axis+cos(angle_in)%(vector_in-(vector_in*dir_axis)%dir_axis)
 +sin(angle_in)%(dir_axis%vector_in);

return tempv;
}
//---------------------------------------------------------------------------
Vertex x_axis()
{
//x���̒l��Ԃ�
Vertex temp;
temp.x=1;temp.y=0;temp.z=0;
return temp;
}
//---------------------------------------------------------------------------
Vertex y_axis()
{
//y���̒l��Ԃ�
Vertex temp;
temp.x=0;temp.y=1;temp.z=0;
return temp;
}
//---------------------------------------------------------------------------
Vertex z_axis()
{
//z���̒l��Ԃ�
Vertex temp;
temp.x=0;temp.y=0;temp.z=1;
return temp;
}

