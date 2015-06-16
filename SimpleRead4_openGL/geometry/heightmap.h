//---------------------------------------------------------------------------
#ifndef heightmapH
#define heightmapH
#include "matrix2d.h"
#include "matrix2d.cpp"
//---------------------------------------------------------------------------
//�����n�}�̃N���X
//�g�����F�܂��̈�m��allocate()�����āCsetarea()������D
//�f�[�^�̕��Ϗ����͂����ł͂��Ȃ��D��ʃN���X�ł��
class HeightMap : public Matrix2D <double>
{
private:
public:
        double x0,x1,dx,y0,y1,dy;//�����n�}�͈̔�
        double z0;//�����̍ŏ��l���`��ɕK�v
        char allocate(int mesh_i_in,int mesh_j_in);//�̈�m��override
        char setarea(double x0_in,double x1_in,
            double y0_in,double y1_in);//�͈͌���
        int xtoi(double x_in);//�C���f�b�N�X�ϊ�
        int ytoj(double y_in);
        double itox(int i_in);
        double jtoy(int j_in);
        char search_minimum(void);//�ŏ��l��T����z0�ɃZ�b�g����

        void clear(void);

        //char save(char *filename);
        //char load(char *filename);
	char create_samesize_map(HeightMap *org,HeightMap *dst);//�����傫���̋�n�}����
	char create_samesize_map(HeightMap *dst);//�����傫���̋�n�}����
	char copy_map(HeightMap *org,HeightMap *dst);//�n�}�̓��e�R�s�[
	char add_to(HeightMap *dst);//�n�}�̓��e�ǉ�
	char copy_to(HeightMap *dst);//�n�}�̓��e�R�s�[

};
//---------------------------------------------------------------------------
#endif
