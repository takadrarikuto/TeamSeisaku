#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数
#define TITLE_POS_X (200)
#define TITLE_POS_Y (250)
#define TITLE_FONT_SIZE (40)

//オブジェクト:タイトル
class CObjOperation :public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag; //キーフラグ
	bool  m_f;     //弾丸発射制御用
	float m_and;		//透明度処理用
	bool m_andf;		//透明度処理用フラグ
	int choose;
	int m_time;
};
