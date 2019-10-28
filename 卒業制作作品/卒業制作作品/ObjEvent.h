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
	int m_Evwnt_time;	//イベント時間
	int m_rand_num; //イベントランダム変数
	

};