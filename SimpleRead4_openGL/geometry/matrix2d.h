//画像比較用2次元画像情報格納クラス
//c++のtemplate使用
//000417
//使い方：まず最初にallocateして，領域確保してから，
//cell_array,flag_arrayにデータを入れれば良い

//operator=が定義されている型でないと要素にならない
//---------------------------------------------------------------------------
#ifndef matrix2dH
#define matrix2dH
template <class T> struct Matrix2D
{
T *cell_array;//2次元画素へのポインタ．これを配列にして使う．
char *flag_array;//データがあるかないか
int mesh_i,mesh_j;//メッシュの数
char allocate_flag;//データ領域確保フラグ

char allocate(int mesh_i_in,int mesh_j_in);//領域確保
char write(T cell,int i_in,int j_in);//入力
char read(T *cell,int i_in,int j_in);//出力
char check(int i_in,int j_in);//メッシュの数の範囲に入っているかどうか
int index(int i_in,int j_in);
//↑低レベルアクセス用インデックス関数．できるだけ使わないようにする．
//使用時にはフラグに注意
Matrix2D(void);//コンストラクタ

void operator=(const Matrix2D<T>& rhs);//代入関数
};
//クリア関数も作りたかったが，汎用性のため，作らないことにした000417
//---------------------------------------------------------------------------
//テンプレートなので，関数も全部インクルードしてやらないといけないらしい．
//---------------------------------------------------------------------------
#endif
 