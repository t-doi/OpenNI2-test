//---------------------------------------------------------------------------
//vxobj.cpp,h
//ボクセルによって物体の表面データの入出力，重心算出
//を行うクラスVXObj
//Voxelの派生クラス
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
