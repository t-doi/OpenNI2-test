//---------------------------------------------------------------------------
//vxobj.cpp,h
//�{�N�Z���ɂ���ĕ��̂̕\�ʃf�[�^�̓��o�́C�d�S�Z�o
//���s���N���XVXObj
//voxel�̔h���N���X
#include "vxobj.h"
//---------------------------------------------------------------------------
void VXObj::clear(void)
{
int i;
  for(i=0;i<(mesh_x*mesh_y*mesh_z);i++)
  {
  flag[i]=0;
  }
}
//---------------------------------------------------------------------------
char VXObj::input(double x_in,double y_in,double z_in)
{
//�f�[�^����
int i,j,k;
i=xtoi(x_in);
j=ytoj(y_in);
k=ztok(z_in);
if(!check(i,j,k))return 0;

flag[index(i,j,k)]=1;
return 1;
}
//---------------------------------------------------------------------------
char VXObj::calc_cog(double *x_out,double *y_out,double *z_out)
{
int i,j,k;
double cog_x_sum=0;//�f�[�^�̑��a
double cog_y_sum=0;
double cog_z_sum=0;
int data_num=0;//�f�[�^�̌�
  for(k=0;k<mesh_z;k++)
  {
    for(j=0;j<mesh_y;j++)
    {
      for(i=0;i<mesh_x;i++)
      {
       if(flag[index(i,j,k)]!=0)
       {
       cog_x_sum+=itox(i);
       cog_y_sum+=jtoy(j);
       cog_z_sum+=ktoz(k);
       data_num++;
       }
      }
     }
   }
   if(data_num==0)return 0;
   *x_out=cog_x_sum/data_num;
   *y_out=cog_y_sum/data_num;
   *z_out=cog_z_sum/data_num;
   return 1;
}
//---------------------------------------------------------------------------
