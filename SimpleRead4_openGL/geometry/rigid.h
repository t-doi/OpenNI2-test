//---------------------------------------------------------------------------
//rigid.cpp,h���̂̉�]�v�Z
//010626
#ifndef rigidH
#define rigidH
#include <vertex.h>
//---------------------------------------------------------------------------
char calc_rpy(Vertex z_axis2,Vertex x_axis2,
         double *roll_out, double *pitch_out, double *yaw_out);
//��]���z���Cx���̕�������C���[���C�s�b�`�C���[�����߂�֐�
Vertex x_axis();//x����\���x�N�g����Ԃ�
Vertex y_axis();
Vertex z_axis();
Vertex rotate(Vertex vector_in, Vertex dir_axis, double angle_in);
//�����_�𒆐S�ɔC�ӂ̎�����̉�]
//---------------------------------------------------------------------------
#endif
