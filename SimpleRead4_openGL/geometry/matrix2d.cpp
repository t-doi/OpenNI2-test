//---------------------------------------------------------------------------
//Matrix2D
//�摜��r�p2�����摜���i�[�N���X
//000417
//�e���v���[�g�����炩�C���̃t�@�C�����C���N���[�h���Ă��Ȃ��Ǝg���Ȃ�

#include "matrix2d.h"
//---------------------------------------------------------------------------
#ifndef matrix2DCPP
#define matrix2DCPP
//���Q�d�ǂݍ��݂�h��
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::allocate(int mesh_i_in,int mesh_j_in)
{
//�̈�m��
mesh_i=mesh_i_in;
mesh_j=mesh_j_in;

cell_array=new T[(mesh_i_in*mesh_j_in)];
flag_array=new char[(mesh_i_in*mesh_j_in)];

if(!cell_array)
{
return 0;
}
  for(int i=0;i<(mesh_i_in*mesh_j_in);i++)
  {
   flag_array[i]=0;//������
  }

allocate_flag=1;
return 1;
}
//---------------------------------------------------------------------------
template <class T> int Matrix2D<T>::index(int i_in,int j_in)
{
//�჌�x���A�N�Z�X�p�C���f�b�N�X�֐�
return (i_in+j_in*mesh_i);
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::write(T cell,int i_in,int j_in)
{
//����
if(!allocate_flag)return 0;
if(!check(i_in,j_in))return 0;//�`�F�b�N����

cell_array[index(i_in,j_in)]=cell;
flag_array[index(i_in,j_in)]=1;//�t���O����
return 1;
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::read(T *cell,int i_in,int j_in)
{
//�o��
if(!allocate_flag)
  return 0;
if(!check(i_in,j_in))
  return 0;//�`�F�b�N����
if(!flag_array[index(i_in,j_in)])
 return 0;//�f�[�^�t���O�̃`�F�b�N
 
*cell=cell_array[index(i_in,j_in)];
return 1;
}
//---------------------------------------------------------------------------
template <class T> char Matrix2D<T>::check(int i_in,int j_in)
{
//���b�V���̐��͈̔͂ɓ����Ă��邩�ǂ���
if((i_in<0)||(i_in>=mesh_i))return 0;
if((j_in<0)||(j_in>=mesh_j))return 0;
return 1;
}
//---------------------------------------------------------------------------
template <class T> Matrix2D<T>::Matrix2D(void)
{
//�R���X�g���N�^
allocate_flag=0;
}
//---------------------------------------------------------------------------
template <class T> void Matrix2D<T>::operator=(const Matrix2D<T>& rhs)
{
//����֐�
//allocate������Ŏg��

  for(int i=0;i<(mesh_i*mesh_j);i++)
  {
  cell_array[i]=rhs.cell_array[i];
  flag_array[i]=rhs.flag_array[i];
  }
}
//---------------------------------------------------------------------------
#endif
