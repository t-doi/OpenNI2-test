/*****************************************************************************
*                                                                            *
*  OpenNI 2.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#include <stdio.h>
#include <OpenNI.h>

#include "OniSampleUtilities.h"

extern "C"
{
//#include <windows.h> //VC++�p
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "GL/freeglut.h"
//#include <GL/freeglut.h>
}
#include "mouse_view.h"
#include "OGL.h"
#include "OGL2D.h"


OGL ogl1;//OpenGL���p���C�u����
MouseView mv1;//�}�E�X���[�V�����Ǘ��N���X
int W_Height=500;//�E�C���h�E����.�`��Ŏg���B
int W_Width=500;//�E�C���h�E��.�`��Ŏg���B



#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

using namespace openni;

#define XTION_PIXEL_WIDTH 320
#define XTION_PIXEL_HEIGHT 240
double depth_data[XTION_PIXEL_WIDTH][XTION_PIXEL_HEIGHT];
typedef struct{
	double p[3];
}Point3D;
Point3D point[XTION_PIXEL_WIDTH][XTION_PIXEL_HEIGHT];


int measure(void);//�v������

//---------------------
void ogl_2d_tri_test(double x0, double y0)//�O�p�`�J�[�\�� 2D�`��
{
    double r=0.1;
    ogl_2d_triangle(x0,y0,x0-0.5*r,y0-r,x0+0.5*r,y0-r);
}
//---------------------
void disp_overlay( void ) //2D-overlay�`��D�}�E�X�Y�[���Ƃ͖��֌W�ɃT�C�Y�Œ�D
{

//�}�E�X�Y�[���ɖ��֌W�̌Œ�g�B�񎟌��w��
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    glColor3f(0.5f,0.5f,0.5f);
    glRasterPos2d(0,0);
	//ogl_2d_tri_test(0,-0.1);//�O�p�`�̃J�[�\��

    //ogl_2d_tri_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//�O�p�`�J�[�\��
    //ogl_2d_circle_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//�~�`�J�[�\��


    //�ʒu�Œ�e�L�X�g
    void *font1=GLUT_BITMAP_9_BY_15;
    glRasterPos2d(-0.9,0.9);//��ʍ��W�Ń��b�Z�[�W�\���ʒu�w��
    //glutBitmapString(font1, reinterpret_cast<const unsigned char*>("Doi Robotics Lab."));
    //glutBitmapString(font1, (unsigned char *)("Doi Robotics Lab.2015.6.9"));
    glutBitmapString(font1, (unsigned char *)("Press [m] for measurement."));

  glPopMatrix();

    //�ړ�����e�L�X�g
    glRasterPos3d(1000,0,0);//�O�������W�Ń��b�Z�[�W�\���ʒu�w��
    glutBitmapString(font1, (unsigned char *)("(1000,0,0)"));
    glRasterPos3d(0,1000,0);//�O�������W�Ń��b�Z�[�W�\���ʒu�w��
    glutBitmapString(font1, (unsigned char *)("(0,1000,0)"));
    glRasterPos3d(0,0,1000);//�O�������W�Ń��b�Z�[�W�\���ʒu�w��
    glutBitmapString(font1, (unsigned char *)("(0,0,1000)"));


}
//-------------------------------------
void disp( void ) //�`��
{

//���_�̌���
double wh_ratio;//�@w/h�̔�
wh_ratio=(double)W_Width/(double)W_Height;
ogl1.set_viewpoint(mv1.distance,mv1.azimuth,mv1.elevation,
  mv1.v_center[0], mv1.v_center[1], mv1.v_center[2], wh_ratio);

    disp_overlay();//�񎟌��`��D�O�����`��ɏd�˂�`
    ogl1.set_light();//�Ɩ��Z�b�g

//�������̂�`�悵�����Ƃ��ɂ͂����Ƀ��f����ǉ�����------

glLineWidth(3);//���̑�������
ogl1.coordinate(1000);//���W���`��

//�t���[���`��
ogl1.set_material(0.5,0.5,0.5,1);
ogl1.Frame(0,3000,-1500,1500,-1000,1000);//���W���`��


ogl1.Blue();//�F�Ɍ���
//ogl1.Box(0,1,-1,1,-0.5,0.5);//���`��

for(int i=0;i<XTION_PIXEL_WIDTH;i++)
{
	for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
	{
		double h=depth_data[i][j]*0.01;
		//ogl1.Box(i,i+1,j,j+1,0,h);//���`��
	}
}

//�_�Q�`��
//ogl1.Red();//�F�ԂɌ���
ogl1.set_material(1.0,0.0,0.0,0.5);//�ԐF�C������
for(int i=0;i<XTION_PIXEL_WIDTH;i++)
{
	for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
	{
		double h=depth_data[i][j]*0.01;
		glPointSize(1);
		glBegin(GL_POINTS);
		glVertex3d(point[i][j].p[0],point[i][j].p[1],point[i][j].p[2]);
		glEnd();
	}
}


//�O�����`�悱���܂�---------------------------


  glFlush();
  glutSwapBuffers();
}
//-----------------------
void mbutton(int button , int state , int x , int y) //�}�E�X�{�^�����������A�グ�C�x���g
{
//printf("mouse event x[%d], y[%d]\n",x,y);

  mv1.drag_mode=DRAG_MODE_STOP;
	if (state== GLUT_DOWN)
          {
            if(button==GLUT_LEFT_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_ZOOM;
              }
            if(button==GLUT_MIDDLE_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_ROTATE;
              }
            if(button==GLUT_RIGHT_BUTTON)
              {
                mv1.drag_mode=DRAG_MODE_TRANSLATE;
              }
            mv1.init(x,y);
            mv1.flag_drag=1;
          }
  	if (state== GLUT_UP)
          {
            mv1.flag_drag=0;
          }
//disp();
  glutPostRedisplay();
}
//-----------------------
void mmotion(int x , int y) //�}�E�X�ړ��C�x���g
{
  if(mv1.flag_drag!=1)return;
	//printf("(x,y)=(%d,%d)",x,y);
  if(mv1.drag_mode==DRAG_MODE_ROTATE)
    {
      mv1.Rotate(x,y);
    }
    if(mv1.drag_mode==DRAG_MODE_ZOOM)
    {
      mv1.Zoom(x,y);
    }
    if(mv1.drag_mode==DRAG_MODE_TRANSLATE)
    {
      mv1.Translate(x,y);
    }
  	glutPostRedisplay();
}

//-----------------------
void keyf(unsigned char key , int x , int y)//��ʃL�[����
{
	printf("key[%c],x[%d],y[%d]\n",key,x,y);
    switch(key)
    {
    case 'm':
		measure();
		break;
    case 'q':
    case 'Q':
    case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
        {
            printf("Exit\n");
            exit(0);
            break;
        }
        default:
        break;
    }
    glutPostRedisplay();
}
/*
GLUT_KEY_F1	F1 function key
GLUT_KEY_F2	F2 function key
GLUT_KEY_F3	F3 function key
GLUT_KEY_F4	F4 function key
GLUT_KEY_F5	F5 function key
GLUT_KEY_F6	F6 function key
GLUT_KEY_F7	F7 function key
GLUT_KEY_F8	F8 function key
GLUT_KEY_F9	F9 function key
GLUT_KEY_F10	F10 function key
GLUT_KEY_F11	F11 function key
GLUT_KEY_F12	F12 function key
GLUT_KEY_LEFT	�����L�[
GLUT_KEY_UP	����L�[
GLUT_KEY_RIGHT	�E���L�[
GLUT_KEY_DOWN	�����L�[
GLUT_KEY_PAGE_UP	Page up �L�[
GLUT_KEY_PAGE_DOWN	Page down �L�[
GLUT_KEY_HOME	Home �L�[
GLUT_KEY_END	End �L�[
GLUT_KEY_INSERT	Inset �L�[
*/

void keyf2(int key , int x , int y)//����L�[�̈���
{
	switch(key)
	{
		case GLUT_KEY_UP:
			printf("GLUT_KEY_UP\n");
                        break;
		case GLUT_KEY_DOWN:
			printf("GLUT_KEY_DOWN\n");
                        break;
		case GLUT_KEY_RIGHT:
			printf("GLUT_KEY_RIGHT\n");
			break;
		case GLUT_KEY_LEFT:
			printf("GLUT_KEY_LEFT\n");
                        break;

	}
	printf("key[%c],x[%d],y[%d]\n",key,x,y);
  	glutPostRedisplay();
}
//-----------------------
void js_func(unsigned int buttonMask, int x, int y, int z)//�W���C�X�e�B�b�N�C�x���g
{
  /*
    GLUT_JOYSTICK_BUTTON_A
    GLUT_JOYSTICK_BUTTON_B
    GLUT_JOYSTICK_BUTTON_C
    GLUT_JOYSTICK_BUTTON_D
    */
  printf("Joystick x,y,z=(%d,%d,%d)\n",x,y,z);
  /*
  switch (buttonMask)
    {
    case GLUT_JOYSTICK_BUTTON_A:
      printf("A ON");
      break;
    case GLUT_JOYSTICK_BUTTON_B:
      printf("B ON");
      break;
    }
    */
  	glutPostRedisplay();
}
//-----------------------
void reshape(int width, int height)//�ĕ`��̊֐�
{
W_Width=width;
W_Height=height;
printf("(width,height)=(%d,%d)\n",width,height);
glViewport(0,0,W_Width,W_Height);
  	glutPostRedisplay();
}
//-----------------------
int main(int argc , char ** argv) {
int id;

  glutInit(&argc , argv);
	glutInitWindowPosition(100 , 50);
	glutInitWindowSize((int)W_Width , (int)W_Height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);



	id=glutCreateWindow("OpenNI2 test - Doi Robotics Lab. 150610");

        glutDisplayFunc(disp);//�`�揈��
	glutKeyboardFunc(keyf);//�L�[���̓C�x���g
	glutSpecialFunc(keyf2);//����L�[���̓C�x���g
	glutMouseFunc(mbutton);//�}�E�X�{�^�����������A�グ
	glutMotionFunc(mmotion);//�}�E�X�ړ��C�x���g
	glutReshapeFunc(reshape);//�ĕ`��C�x���g
   //     glutJoystickFunc(js_func,100);//�W���C�X�e�B�b�N�C�x���g

	printf("Press [m] for measurement\n");
	measure();

	glutMainLoop();
	return 0;
}
//---------------------------
int measure()
{
	//OpenNI�𗘗p�����Z���T����̏��擾��3�����f�[�^�ւ̕ϊ��D
	Status rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
		return 1;
	}

	Device device;
	rc = device.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		return 2;
	}

	//�Z���T���̎擾�H
	VideoStream depth;
	if (device.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth.create(device, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	rc = depth.start();
	if (rc != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}

	//�t���[���̎擾�H
	VideoFrameRef frame;
	rc = depth.readFrame(&frame);
		int width=frame.getWidth();
	int height=frame.getHeight();
	printf("W%d,H%d\n",width,height);
	//getchar();


	float x,y,z;//�_�Q�ʒu�ǂݍ��ݗp�ϐ�

	//while (!wasKeyboardHit())
	while(1)
	{
		int changedStreamDummy;
		VideoStream* pStream = &depth;
		rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		if (rc != STATUS_OK)
		{
			printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
			continue;
		}

		rc = depth.readFrame(&frame);
		if (rc != STATUS_OK)
		{
			printf("Read failed!\n%s\n", OpenNI::getExtendedError());
			continue;
		}

		if (frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
		{
			printf("Unexpected frame format\n");
			continue;
		}

		//�f�[�^�擾�H
		DepthPixel* pDepth = (DepthPixel*)frame.getData();

		int middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;//�����̒l�擾�i�e�X�g�p�j

		printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), pDepth[middleIndex]);

		for(int i=0;i<XTION_PIXEL_WIDTH;i++)
		{
			for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
			{
				int index=j*XTION_PIXEL_WIDTH+i;
				depth_data[i][j]=pDepth[index];//�[�x����2�����z��ɓ��꒼��
				//printf("%.0f, ",depth_data[i][j]);
				
				//�[�x����x,y,z�ɏ����o���D�J�������W�n�͑O��z�Ȃ̂Œ��ӁD
				openni::CoordinateConverter::convertDepthToWorld((openni::VideoStream &)depth,(int)i,(int)j,(openni::DepthPixel)pDepth[index],
					(float *)&x,(float *)&y,(float *)&z);
				point[i][j].p[0]=(double)z;
				point[i][j].p[1]=(double)x;
				point[i][j].p[2]=(double)y;
				//printf("[%.0f, %.0f, %.0f]\n",x,y,z);
				
			}
			//printf("\n");

		}
		//printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), depth_data[160][120]);
		//getchar();
		break;
	}
	printf("Done.\n");

	depth.stop();
	depth.destroy();
	device.close();
	OpenNI::shutdown();

	return 0;
}
