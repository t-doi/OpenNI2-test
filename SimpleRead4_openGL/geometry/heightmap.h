//---------------------------------------------------------------------------
#ifndef heightmapH
#define heightmapH
#include "matrix2d.h"
#include "matrix2d.cpp"
//---------------------------------------------------------------------------
//高さ地図のクラス
//使い方：まず領域確保allocate()をして，setarea()をする．
//データの平均処理はここではしない．上位クラスでやる
class HeightMap : public Matrix2D <double>
{
private:
public:
        double x0,x1,dx,y0,y1,dy;//高さ地図の範囲
        double z0;//高さの最小値→描画に必要
        char allocate(int mesh_i_in,int mesh_j_in);//領域確保override
        char setarea(double x0_in,double x1_in,
            double y0_in,double y1_in);//範囲決定
        int xtoi(double x_in);//インデックス変換
        int ytoj(double y_in);
        double itox(int i_in);
        double jtoy(int j_in);
        char search_minimum(void);//最小値を探してz0にセットする

        void clear(void);

        //char save(char *filename);
        //char load(char *filename);
	char create_samesize_map(HeightMap *org,HeightMap *dst);//同じ大きさの空地図生成
	char create_samesize_map(HeightMap *dst);//同じ大きさの空地図生成
	char copy_map(HeightMap *org,HeightMap *dst);//地図の内容コピー
	char add_to(HeightMap *dst);//地図の内容追加
	char copy_to(HeightMap *dst);//地図の内容コピー

};
//---------------------------------------------------------------------------
#endif
