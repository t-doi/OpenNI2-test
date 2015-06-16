//---------------------------------------------------------------------------
//�����n�}�̃N���XHeightMap
//heightmap.cpp,h
//�vgeometory.lib
//#include <stdio.h>
#include "heightmap.h"
//#define HEIGHT_M2DINDEX i+j*mesh_i

//---------------------------------------------------------------------------
char HeightMap::allocate(int mesh_i_in,int mesh_j_in)
{
//�̈�m��override
char flag;
flag=Matrix2D <double>::allocate(mesh_i_in,mesh_j_in);
return flag;
}
//---------------------------------------------------------------------------
char HeightMap::setarea(double x0_in,double x1_in
      ,double y0_in,double y1_in)
{
//�͈͌���
double tempdx,tempdy;

x0=x0_in;
x1=x1_in;
y0=y0_in;
y1=y1_in;
if(mesh_i==0)return 0;
if(mesh_j==0)return 0;

tempdx=x1_in-x0_in;
tempdy=y1_in-y0_in;

dx=tempdx/mesh_i;
dy=tempdy/mesh_j;
return 1;
}
//---------------------------------------------------------------------------
int HeightMap::xtoi(double x_in)
{
//�`�F�b�N�Ȃ�
int i=(x_in-x0)/dx;
return i;
}
//---------------------------------------------------------------------------
int HeightMap::ytoj(double y_in)
{
int j=(y_in-y0)/dy;
return j;
}
//---------------------------------------------------------------------------
double HeightMap::itox(int i_in)
{
//�`�F�b�N�Ȃ�
double x=(i_in+0.5)*dx+x0;
return x;
}
//---------------------------------------------------------------------------
double HeightMap::jtoy(int j_in)
{
//�`�F�b�N�Ȃ�
double y=(j_in+0.5)*dy+y0;
return y;
}
//---------------------------------------------------------------------------
void HeightMap::clear(void)
{
 for(int j=0;j<mesh_j;j++)
 {
 for(int i=0;i<mesh_i;i++)
 {
  cell_array[index(i,j)]=0;
  flag_array[index(i,j)]=0;
 }
 }
}
//---------------------------------------------------------------------------
/*char HeightMap::save(char *filename)
{
FILE *fp_out;

fp_out=fopen(filename,"w");
if(fp_out==NULL)return 0;

fprintf(fp_out,"%d \n",mesh_i);//�f�[�^�T�C�Ymesh_x
fprintf(fp_out,"%d \n",mesh_j);//�f�[�^�T�C�Ymesh_x
fprintf(fp_out,"----------------\n");
//�f�[�^
double temp_cell;
 for(int j=0;j<mesh_j;j++)
 {
  for(int i=0;i<mesh_i;i++)
  {
  Matrix2D<double>::read(&temp_cell,i,j);
  fprintf(fp_out,"%6.2lf           ",temp_cell);
  }
  fprintf(fp_out,"\n");
 }
fprintf(fp_out,"----------------\n");

//�t���O
 for(int j=0;j<mesh_j;j++)
 {
  for(int i=0;i<mesh_i;i++)
  {
   if(Matrix2D<double>::read(&temp_cell,i,j))
   fprintf(fp_out,"1       ");
   else
   fprintf(fp_out,"0       ");
  }
  fprintf(fp_out,"\n");
 }
fprintf(fp_out,"----------------\n");

fclose(fp_out);
return 1;
}
//---------------------------------------------------------------------------
char HeightMap::load(char *filename)
{
FILE *fp_in;
char temp_buf[64];//��ǂݗp

fp_in=fopen(filename,"r");
if(fp_in==NULL)return 0;

fscanf(fp_in,"%d \n",&mesh_i);//�f�[�^�T�C�Ymesh_i
fscanf(fp_in,"%d \n",&mesh_j);//�f�[�^�T�C�Ymesh_j
allocate(mesh_i,mesh_j);
fgets(temp_buf,64,fp_in);
//�f�[�^
double temp_cell;
 for(int j=0;j<mesh_j;j++)
 {
  for(int i=0;i<mesh_i;i++)
  {
  fscanf(fp_in,"%6.2lf           ",temp_cell);
  Matrix2D<double>::write(temp_cell,i,j);
  }
  fgets(temp_buf,64,fp_in);//���s
 }

fgets(temp_buf,64,fp_in);//��ǂ�

//�t���O
char temp_flag;
 for(int j=0;j<mesh_j;j++)
 {
  for(int i=0;i<mesh_i;i++)
  {
   fscanf(fp_in,"%c",&temp_flag);
   if(temp_flag)
   flag_array[HEIGHT_M2DINDEX]=1;
   else
   flag_array[HEIGHT_M2DINDEX]=0;
  }
 fgets(temp_buf,64,fp_in);//��ǂ�
 }

fclose(fp_in);
return 1;
}
*/
//---------------------------------------------------------------------------
char HeightMap::search_minimum(void)
{
//�ŏ��l��T����z0�ɃZ�b�g����
double minimum,temp_minimum;
if(!allocate_flag)return 0;

minimum=0;
temp_minimum=0;

 for(int j=0;j<mesh_j;j++)
 {
  for(int i=0;i<mesh_i;i++)
  {
   if(Matrix2D<double>::read(&temp_minimum,i,j));
   {
    if(temp_minimum<minimum)
       minimum=temp_minimum;
   }
  }
 }

z0=minimum;
return 1;
}
//---------------------------------------------------------------------------
char HeightMap::create_samesize_map(HeightMap *org,HeightMap *dst)
{
//�����n�}�̑傫���R�s�[
  dst->allocate(org->mesh_i,org->mesh_j);
  dst->setarea(org->x0,org->x1,org->y0,org->y1);
  dst->clear();
return 1;
}
//---------------------------------------------------------------------------
char HeightMap::create_samesize_map(HeightMap *dst)
{
//�����傫���̋�n�}����
   char flag=create_samesize_map(this, dst);
return flag;
}
//---------------------------------------------------------------------------
char HeightMap::copy_map(HeightMap *org,HeightMap *dst)
{
//�����n�}�̓��e�R�s�[
org->copy_to(dst);
return 1;
}
//---------------------------------------------------------------------------
char HeightMap::add_to(HeightMap *dst)
{
//�n�}�̓��e�ǉ�
int i2,j2;
double h;
  for(int j=0;j<mesh_j;j++)
  {
  for(int i=0;i<mesh_i;i++)
  {
   if(read(&h,i,j))
   {
    i2=dst->xtoi(itox(i));
    j2=dst->ytoj(jtoy(j));
    dst->write(h,i2,j2);
   }
  }
  }
return 1;
}
//---------------------------------------------------------------------------
char HeightMap::copy_to(HeightMap *dst)
{
//�n�}�̓��e�R�s�[
dst->clear();
return (add_to(dst));
}
//---------------------------------------------------------------------------

