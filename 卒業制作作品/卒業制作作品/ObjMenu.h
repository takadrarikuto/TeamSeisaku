#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	void BackDraw(float top, float left, float right, float bottom, float c[]);

private:
	bool m_key_flag;//キーフラグ
	int choose;
	int m_time;
	int m_time_s;
	float m_and;		//透明度処理用
	bool m_andf;		//透明度処理用フラグ
	bool m_andf2;		//透明度処理用フラグ
	bool m_Scene_flg; //シーン移動フラグ
};