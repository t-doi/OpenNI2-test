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
//#include <windows.h> //VC++用
#include "vcsetting.h" //VC++用
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include "GL/freeglut.h"
//#include <GL/freeglut.h>
}
#include "mouse_view.h"
#include "gl_tools.h"
#include "OGL2D.h"
#include <OGLGeo.h>
#include <vertex.h>
#include <heightmap.h>


OGLGeo *ogl1;//OpenGL応用ライブラリ
MouseView mv1;//マウスモーション管理クラス
HeightMap map1;
int W_Height=500;//ウインドウ高さ.描画で使う。
int W_Width=500;//ウインドウ幅.描画で使う。

double sensor_position[]={0,0,1000};//センサの位置
double sensor_pitch_angle=-30*M_PI/180;//センサのピッチ角


#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

using namespace openni;

#define XTION_PIXEL_WIDTH 320
#define XTION_PIXEL_HEIGHT 240
double depth_data[XTION_PIXEL_WIDTH][XTION_PIXEL_HEIGHT];
typedef struct{
	double p[3];
}Point3D;
Point3D point[XTION_PIXEL_WIDTH][XTION_PIXEL_HEIGHT];


char stop_flag;//計測停止フラグ
char point_draw_flag;//点群描画フラグ
char map_draw_flag;//高さ地図描画フラグ

int measure_init(void);//計測準備
int measure(void);//計測処理
int measure_close(void);//計測終了処理

void timerfunc1(int val);//周期計測用タイマー関数


//---------------------
void ogl_2d_tri_test(double x0, double y0)//三角形カーソル 2D描画
{
    double r=0.1;
    ogl_2d_triangle(x0,y0,x0-0.5*r,y0-r,x0+0.5*r,y0-r);
}
//---------------------
void disp_overlay( void ) //2D-overlay描画．マウスズームとは無関係にサイズ固定．
{

//マウスズームに無関係の固定枠。二次元指定
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    glColor3f(0.5f,0.5f,0.5f);
    glRasterPos2d(0,0);
	//ogl_2d_tri_test(0,-0.1);//三角形のカーソル

    //ogl_2d_tri_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//三角形カーソル
    //ogl_2d_circle_test_p((double)cursor_pos_global[0]/10,(double)cursor_pos_global[1]/10);//円形カーソル


    //位置固定テキスト
    void *font1=GLUT_BITMAP_9_BY_15;
    glRasterPos2d(-0.9,0.9);//画面座標でメッセージ表示位置指定
    //glutBitmapString(font1, reinterpret_cast<const unsigned char*>("Doi Robotics Lab."));
    //glutBitmapString(font1, (unsigned char *)("Doi Robotics Lab.2016.8.5"));
    glutBitmapString(font1, (unsigned char *)("[m] :measurement."));
    glRasterPos2d(-0.9,0.85);//画面座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("[q] :quit."));
    glRasterPos2d(-0.9,0.8);//画面座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("[a] : toggle points."));
    glRasterPos2d(-0.9,0.75);//画面座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("[s] : toggle map."));
    glRasterPos2d(-0.9,0.7);//画面座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("[d] : data dump."));

  glPopMatrix();

    //移動するテキスト
    glRasterPos3d(1000,0,0);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(1000,0,0)"));
    glRasterPos3d(0,1000,0);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(0,1000,0)"));
    glRasterPos3d(0,0,1000);//三次元座標でメッセージ表示位置指定
    glutBitmapString(font1, (unsigned char *)("(0,0,1000)"));


}
//-------------------------------------
void disp( void ) //描画
{

//視点の決定
double wh_ratio;//　w/hの比
wh_ratio=(double)W_Width/(double)W_Height;
GL_set_viewpoint(mv1.distance,mv1.azimuth,mv1.elevation,
  mv1.v_center[0], mv1.v_center[1], mv1.v_center[2], wh_ratio);

    disp_overlay();//二次元描画．三次元描画に重ねる形
    GL_set_light();//照明セット

//何か物体を描画したいときにはここにモデルを追加する------

glLineWidth(3);//線の太さ決定
GL_Coordinate(1000);//座標軸描画

//フレーム描画
GL_set_material(0.5,0.5,0.5,1);
//ogl1->Frame(0,3000,-1500,1500,-1000,1000);//座標軸描画

//床描画
GL_set_material(0.5,0.5,0.5,1);
GL_FloorGrid(-1000,3000,-2000,2000,20,20);


GL_Blue();//色青に決定
//ogl1->Box(0,1,-1,1,-0.5,0.5);//箱描画

for(int i=0;i<XTION_PIXEL_WIDTH;i++)
{
	for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
	{
		double h=depth_data[i][j]*0.01;
		//ogl1->Box(i,i+1,j,j+1,0,h);//箱描画
	}
}


//センサ描画
Vertex Org;//原点
Vertex dst;//方向ベクトル
Org.x=sensor_position[0];Org.y=sensor_position[1];Org.z=sensor_position[2];
dst.x=Org.x+4000*cos(sensor_pitch_angle);
dst.y=Org.y;
dst.z=Org.z+4000*sin(sensor_pitch_angle);
GL_set_material(1.0,1.0,1.0,0.5);//黒色，半透明
glPointSize(10);
glBegin(GL_POINTS);
glVertex3d(Org.x, Org.y,Org.z);
glEnd();
glBegin(GL_LINES);
	glVertex3d(Org.x,Org.y,Org.z);
	glVertex3d(dst.x,dst.y,dst.z);
glEnd();


if(point_draw_flag==1)
{
//点群描画
//ogl1->Red();//色赤に決定
GL_set_material(1.0,0.0,0.0,0.5);//赤色，半透明
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
}
if(map_draw_flag==1)
{
//高さ地図描画
GL_set_material(0.0,1.0,0.0,0.5);//緑，半透明
//ogl1->heightmap(map1);
//ogl1->heightmap2(map1);
ogl1->heightmap2a(map1,500,-500);
//ogl1->heightmap3(map1);
}

//三次元描画ここまで---------------------------


  glFlush();
  glutSwapBuffers();
}
//-----------------------


void dump_data(char mode_c)
{
	//xyzデータを出力
	//mode_c ==1でファイル出力
	//mode_c==2で画面出力

	FILE *fp;
	double xw,yw,zw;

	if(mode_c==1)
	{
		fp=fopen("data.csv","a");
	}

	for(int i=0;i<XTION_PIXEL_WIDTH;i++)
	{
			for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
			{
				xw=point[i][j].p[0];
				yw=point[i][j].p[1];
				zw=point[i][j].p[2];

				printf("%f,%f,%f \n",xw,yw,zw);
				if(mode_c==1)
				{
					fprintf(fp,"%f,%f,%f \n",xw,yw,zw);
				}
				

			}
	}

	if(mode_c==1)
	{
		fclose(fp);
	}

			
}
//-----------------------
void mbutton(int button , int state , int x , int y) //マウスボタン押し下げ、上げイベント
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
void mmotion(int x , int y) //マウス移動イベント
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
void keyf(unsigned char key , int x , int y)//一般キー入力
{
	printf("key[%c],x[%d],y[%d]\n",key,x,y);
    switch(key)
    {
    case 'm':
		if(stop_flag==1)stop_flag=0;
		else stop_flag=1;
		//measure();
		timerfunc1(0);
		break;
    case 'q':
    case 'Q':
    case '\033':  /* '\033' は ESC の ASCII コード */
        {
            printf("Exit\n");
			stop_flag=1;
			measure_close();
            exit(0);
            break;
        }
    case 'a':
		if(point_draw_flag==1)point_draw_flag=0;
		else point_draw_flag=1;
		break;
    case 's':
		if(map_draw_flag==1)map_draw_flag=0;
		else map_draw_flag=1;
		break;
	case 'd':
		{
			//データ出力
			dump_data(2);//引数１でファイル出力．それ以外はコマンドウインドウ出力のみ
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
GLUT_KEY_LEFT	左矢印キー
GLUT_KEY_UP	上矢印キー
GLUT_KEY_RIGHT	右矢印キー
GLUT_KEY_DOWN	下矢印キー
GLUT_KEY_PAGE_UP	Page up キー
GLUT_KEY_PAGE_DOWN	Page down キー
GLUT_KEY_HOME	Home キー
GLUT_KEY_END	End キー
GLUT_KEY_INSERT	Inset キー
*/

void keyf2(int key , int x , int y)//特殊キーの扱い
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
void js_func(unsigned int buttonMask, int x, int y, int z)//ジョイスティックイベント
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
void reshape(int width, int height)//再描画の関数
{
W_Width=width;
W_Height=height;
//printf("(width,height)=(%d,%d)\n",width,height);
glViewport(0,0,W_Width,W_Height);
  	glutPostRedisplay();
}
//-----------------------
void timerfunc1(int val)
{
	measure();
  	glutPostRedisplay();
	//printf("timerfunc1\n");//debug

	if(stop_flag==0)
	glutTimerFunc(300,timerfunc1,0);
}
	
//-----------------------
int main(int argc , char ** argv) {
int id;

  glutInit(&argc , argv);
	glutInitWindowPosition(100 , 50);
	glutInitWindowSize((int)W_Width , (int)W_Height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	id=glutCreateWindow("OpenNI2 test - Doi Robotics Lab. 150616");

	ogl1=new OGLGeo();
	map1.allocate(200,200);
//	map1.setarea(0,5000,-2500,2500);
	map1.setarea(0,10000,-5000,5000);
	map1.clear();
	stop_flag=1;
	point_draw_flag=1;
	map_draw_flag=1;
	
	glutDisplayFunc(disp);//描画処理
	glutKeyboardFunc(keyf);//キー入力イベント
	glutSpecialFunc(keyf2);//特殊キー入力イベント
	glutMouseFunc(mbutton);//マウスボタン押し下げ、上げ
	glutMotionFunc(mmotion);//マウス移動イベント
	glutReshapeFunc(reshape);//再描画イベント
   //     glutJoystickFunc(js_func,100);//ジョイスティックイベント
	//glutTimerFunc(1000,timerfunc1,0);

	printf("Press [m] for measurement\n");
	measure_init();
	
	glutMainLoop();
	return 0;
}
//---------------------------
Device device1;
VideoStream depth1;
VideoFrameRef frame1;
int measure_init()
{
	Status rc = OpenNI::initialize();
	if (rc != STATUS_OK)
	{
		printf("Initialize failed\n%s\n", OpenNI::getExtendedError());
		return 1;
	}

//	Device device;
//	rc = device.open(ANY_DEVICE);
	rc = device1.open(ANY_DEVICE);
	if (rc != STATUS_OK)
	{
		printf("Couldn't open device\n%s\n", OpenNI::getExtendedError());
		return 2;
	}

	//センサ情報の取得？
//	VideoStream depth;
	if (device1.getSensorInfo(SENSOR_DEPTH) != NULL)
	{
		rc = depth1.create(device1, SENSOR_DEPTH);
		if (rc != STATUS_OK)
		{
			printf("Couldn't create depth stream\n%s\n", OpenNI::getExtendedError());
			return 3;
		}
	}

	rc = depth1.start();
	if (rc != STATUS_OK)
	{
		printf("Couldn't start the depth stream\n%s\n", OpenNI::getExtendedError());
		return 4;
	}

	//フレームの取得？
//	VideoFrameRef frame;
	rc = depth1.readFrame(&frame1);
		int width=frame1.getWidth();
	int height=frame1.getHeight();
	printf("W%d,H%d\n",width,height);
	//getchar();
return 0;
}
//---------------------------
int measure()
{
	int GLtimebase,GLtimenow;
	GLtimebase = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	//OpenNIを利用したセンサからの情報取得と3次元データへの変換．
	//先に初期化をしてから


	Status rc;


	float x,y,z;//点群位置読み込み用変数
	int i2,j2;//map書き込み用
	double xw,yw,zw;//鉛直上向きzの座標
	double theta;//センサの傾斜[rad]
	double xw2,yw2,zw2;//鉛直上向きzの座標．座標変換後

	map1.clear();
	
	while(1)
	{
	GLtimebase = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得
		int changedStreamDummy;
		VideoStream* pStream = &depth1;
		rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		if (rc != STATUS_OK)
		{
			printf("Wait failed! (timeout is %d ms)\n%s\n", SAMPLE_READ_WAIT_TIMEOUT, OpenNI::getExtendedError());
			continue;
		}

		rc = depth1.readFrame(&frame1);
		if (rc != STATUS_OK)
		{
			printf("Read failed!\n%s\n", OpenNI::getExtendedError());
			continue;
		}

		if (frame1.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_1_MM && frame1.getVideoMode().getPixelFormat() != PIXEL_FORMAT_DEPTH_100_UM)
		{
			printf("Unexpected frame format\n");
			continue;
		}

		//データ取得？
		DepthPixel* pDepth = (DepthPixel*)frame1.getData();

		int middleIndex = (frame1.getHeight()+1)*frame1.getWidth()/2;//中央の値取得（テスト用）

		printf("[%08llu] %8d\n", (long long)frame1.getTimestamp(), pDepth[middleIndex]);

		for(int i=0;i<XTION_PIXEL_WIDTH;i++)
		{
			for(int j=0;j<XTION_PIXEL_HEIGHT;j++)
			{
				int index=j*XTION_PIXEL_WIDTH+i;
				depth_data[i][j]=pDepth[index];//深度情報を2次元配列に入れ直し
				//printf("%.0f, ",depth_data[i][j]);
				
				//深度情報をx,y,zに書き出し．カメラ座標系は前方zなので注意．
				openni::CoordinateConverter::convertDepthToWorld((openni::VideoStream &)depth1,(int)i,(int)j,(openni::DepthPixel)pDepth[index],
					(float *)&x,(float *)&y,(float *)&z);
				xw=(double)z;
				yw=(double)x;
				zw=(double)y;
				//座標変換
				//センサの傾斜
				//theta=(-30)*M_PI/180;//rad
				theta=sensor_pitch_angle;
				xw2=xw*cos(theta)-zw*sin(theta);
				yw2=yw;
				zw2=xw*sin(theta)+zw*cos(theta);

				//位置調整
				xw2=xw2+sensor_position[0];
				yw2=yw2+sensor_position[1];
				zw2=zw2+sensor_position[2];
				
				point[i][j].p[0]=xw2;
				point[i][j].p[1]=yw2;
				point[i][j].p[2]=zw2;
				//printf("[%.0f, %.0f, %.0f]\n",x,y,z);
				
				
				//map構造体へ書き込み
				i2=map1.xtoi(xw2);
				j2=map1.ytoj(yw2);
				if(map1.check(i2,j2)==1)
				{
				map1.write(zw2,i2,j2);
				}
				
			}
			//printf("\n");

		}
		//printf("[%08llu] %8d\n", (long long)frame.getTimestamp(), depth_data[160][120]);
		//getchar();
		break;
	}
	GLtimenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得
	printf("Done. %d[msec]elapsed\n",GLtimenow-GLtimebase);




	return 0;
}
//------------
int measure_close()
{
	depth1.stop();
	depth1.destroy();
	device1.close();
	OpenNI::shutdown();
return 0;
}
