//---------------------------------------------------------------------------
//vxobj.cpp,h
//�{�N�Z���ɂ���ĕ��̂̕\�ʃf�[�^�̓��o�́C�d�S�Z�o
//���s���N���XVXObj
//Voxel�̔h���N���X
#ifndef vxobjH
#define vxobjH
#include "voxel.h"
//---------------------------------------------------------------------------
class VXObj : public Voxel
{
private:
public:
       void clear(void);
       char input(double x_in,double y_in,double z_in);
       char calc_cog(double *x_out,double *y_out,double *z_out);
};
//---------------------------------------------------------------------------
#endif
