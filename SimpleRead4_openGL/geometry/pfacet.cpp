//990924
//3次元ポリゴン計算クラスfacet.cpp,facet.h
#include <math.h>
#include "vertex.h"
#include "pfacet.h"
//------------------------------------------------------------
char PFacet::abgd(void)
{
//αβγδを計算する関数
Vertex ab,ac;
Vertex temp;

ab=b-a;
ac=c-a;
temp=(ab)%(ac);

alpha=temp.x;
beta=temp.y;
gamma=temp.z;

delta=-(alpha*(a.x)+beta*(a.y)+gamma*(a.z));
        if(!Plane::normalize())
        {
         flag_invalid=1;
        return 0;
        }
return 1;
}
//------------------------------------------------------------
PFacet::PFacet(void)//デフォルトコンストラクタ
{
}
//------------------------------------------------------------
double PFacet::menseki(void)
{
//面積を算出
Vertex ab=b-a;
Vertex ac=c-a;
Vertex temp=(ab)%(ac);

double menseki_out=temp.size()/2;//3角形の面積なので2で割る
return menseki_out;
}
//------------------------------------------------------------
char PFacet::half_line(Vertex start,Vertex dir,Vertex *P_out)
{
//↑半直線とポリゴンとの交点を求める．始点の座標，方向ベクトルの順に入力
//PFacet内にあるかどうかもチェック
//Plane構造体の同名関数のオーバーライド
Vertex temp;

if(!Plane::half_line(start,dir,&temp))
return 0;//交わらない

if(!in_or_out(temp))
return 0;//交点がPFacet外

*P_out=temp;
return 1;//正常な交点が存在する
}
//------------------------------------------------------------
char PFacet::in_or_out(Vertex P_in)
{
//↑9/17ノート参照
//↑5/30改造
//入力した点の座標がPFacet内にあるかないかを判定する関数

Vertex ab,bc,ca;//ポリゴンの3辺．表から見て反時計周り
Vertex ap,bp,cp;
ab=b-a;
bc=c-b;
ca=a-c;

ap=P_in-a;
bp=P_in-b;
cp=P_in-c;


double temp_zero=1.0e-10;
//double temp_zero=0;

if(
((ab%ap)*normal>-temp_zero)&&
((bc%bp)*normal>-temp_zero)&&
((ca%cp)*normal>-temp_zero)
)
return 1;

/*if(
((ab%ap)*normal<temp_zero)&&
((bc%bp)*normal<temp_zero)&&
((ca%cp)*normal<temp_zero)
)
return 1;//これは本来ならありえない．a,b,cの定義順が逆？
*/

return 0;
}
//------------------------------------------------------------
char PFacet::set(Vertex a_in,Vertex b_in,Vertex c_in)
{
a=a_in;
b=b_in;
c=c_in;
return (abgd());
}
//------------------------------------------------------------
void PFacet::operator= (const PFacet& rhs)//代入演算子
{
a=rhs.a;
b=rhs.b;
c=rhs.c;
abgd();
}
//------------------------------------------------------------
bool operator== (const PFacet& lhs,const PFacet& rhs)
{
if(lhs.a!=rhs.a)return 0;
else if(lhs.b!=rhs.b)return 0;
else if(lhs.c!=rhs.c)return 0;
else return 1;
}
//------------------------------------------------------------


