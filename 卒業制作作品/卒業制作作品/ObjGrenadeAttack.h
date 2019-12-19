#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGrenadeAttack :public CObj, public CBaseStatus
{
public:
	CObjGrenadeAttack(float x, float y, float vx, float vy);
	~CObjGrenadeAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Grex; //位置情報
	float m_Grey;
	float m_Grevx; //移動ベクトル
	float m_Grevy;

	int Stop_max; //停止位置
	int EXP_time; //爆破時間

	int m_EXPDameg_num; //爆発ダメージ

	bool m_HitBox_Delete; //HitBox削除フラグ
};