//---------------------------------------------------------------------------
//OpenGL�ɂ��`��
//160805 doi
#ifndef GL_TOOLS		//���d��h��
#define GL_TOOLS

#define WIN32 1
#ifdef WIN32
#include <windows.h>
#endif
//---------------------------------------------------------------------------
//�O�όv�Z
char GL_outer_product(double vx1_in,double vy1_in,double vz1_in,
                       double vx2_in,double vy2_in,double vz2_in,
                       double *vx_out,double *vy_out,double *vz_out
                       );

//���_����
void GL_set_viewpoint(double l,double theta_in,double phi_in);//���_����
void GL_set_viewpoint(double l,double theta_in,double phi_in,
              double cx_in, double cy_in, double cz_in, double wh_ratio_in);//���_����

//�}�e���A���C�F�C�Ɩ�
void GL_set_material(double r_in,double g_in,double b_in,double alpha_in);//�}�e���A��
void GL_Red(void);//�F�w��F��
void GL_Green(void);//�F�w��F��
void GL_Blue(void);//�F�w��F��
void GL_set_light(void);//�Ɩ�
void GL_set_background(char IsWhite);//�w�i�F

//�`��
void GL_Facet(double x0,double y0,double z0,
                       double x1,double y1,double z1,
                       double x2,double y2,double z2);//�|���S��
void GL_Frame(double x0,double x1,double y0,double y1,double z0,double z1);//�|���S��
void GL_Box(double x0,double x1,double y0,double y1,double z0,double z1);//���`��
void GL_Arrow(double size, double x0, double y0, double z0, double x1, double y1, double z1);//���D���̃T�C�Y�C�n�_�C�I�_
void GL_Coordinate(int size);//x,y,z�̏���RGB�̐F�ō��W�n��\��
void GL_Cylinder(double radius, double height, int sides);	// �p���̊֐�( �O�ډ~�̒��a, ����, �p�̐� )
void GL_FloorGrid(double x0, double x1, double y0, double y1, int meshx, int meshy);
//-------------
//GLUT�̋@�\�𗘗p
void GLUT_3D_message(void *font, double x, double y, double z, char *str);//3D�̃e�L�X�g���b�Z�[�W
void GLUT_Coordinate(int size);//x,y,z�̏���RGB�̐F�ō��W�n��\��

//---------------------------------------------------------------------------
#endif
