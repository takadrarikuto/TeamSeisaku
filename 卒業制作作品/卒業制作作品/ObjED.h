#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数

#define GAME_ED_X (40)
#define GAME_ED_Y (150)
#define GAME_ED_FONT_SIZE (25)
#define GAME_CC_FONT_SIZE (20)


//オブジェクト:クリア
class CObjED : public CObj
{
public:
	CObjED() {};
	~CObjED() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag;//キーフラグ
	float m_y;
};