#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoAiming :public CObj, public CBaseStatus
{
public:
	CObjTutoAiming() {};
	~CObjTutoAiming() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_TAx; //位置情報
	float m_TAy;
	float m_TA_dst_num; //位置修正変数

	int m_Aiming_Distance_max; //削除距離最大値

};