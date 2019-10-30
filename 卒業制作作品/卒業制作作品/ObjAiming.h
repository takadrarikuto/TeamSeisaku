#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAiming :public CObj, public CBaseStatus
{
public:
	CObjAiming() {};
	~CObjAiming() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Ax; //位置情報
	float m_Ay;
	float m_A_dst_num; //位置修正変数

	int m_Distance_max; //削除距離最大値

};