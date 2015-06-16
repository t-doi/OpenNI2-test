//---------------------------------------------------------------------------
//voxel�̍\����voxel.cpp,h
//map��3�����Ɋg����������
//�evoxel��char�^�ŁC�ʏ�0��1��������Ȃ�
#ifndef voxelH
#define voxelH
//---------------------------------------------------------------------------
struct Voxel
{
 double x0,x1,y0,y1,z0,z1;
 int mesh_x,mesh_y,mesh_z;
 double dx,dy,dz;
 char *flag;//�{�N�Z���{��

 void array_allocate(int mesh_x_in,int mesh_y_in,int mesh_z_in);
  //���̈�m��
 void set_area(double x0_in,double x1_in,double y0_in,double y1_in,
              double z0_in,double z1_in);
  //���S�͈̂̔͌���ƁCdx,dy,dz�̌v�Z
 int index(int i,int j,int k);//3�����z���1�����z��ŕ\���ۂ̃C���f�b�N�X
 char check(int i,int j,int k);//�̈���O�`�F�b�N
 int xtoi(double x_in);//�����W����Z���̃J�E���g���ւ̕ϊ�
 int ytoj(double y_in);
 int ztok(double z_in);
 double itox(int i_in);//�J�E���g������C�����W�ւ̕ϊ�
 double jtoy(int j_in);//�J�E���g������C�����W�ւ̕ϊ�
 double ktoz(int k_in);//�J�E���g������C�����W�ւ̕ϊ�
};

//---------------------------------------------------------------------------
#endif
