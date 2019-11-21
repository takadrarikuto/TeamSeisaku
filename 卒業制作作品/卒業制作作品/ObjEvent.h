#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEvent :public CObj, public CBaseStatus
{
public:
	CObjEvent() {};
	~CObjEvent() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	int m_Event_time;	//イベント時間
	bool m_Event_time_flg; //イベントフラグ

};