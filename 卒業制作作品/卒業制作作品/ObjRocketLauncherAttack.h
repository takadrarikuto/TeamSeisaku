#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRocketLauncherAttack :public CObj , public CBaseStatus
{
public:
	CObjRocketLauncherAttack(float x, float y, float vx, float vy, float r);
	~CObjRocketLauncherAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	int GetRLDistance() { return m_Distance_max; } //削除距離最大値取得用

private:
	float m_RLx; //位置情報
	float m_RLy;
	float m_RLvx; //移動ベクトル
	float m_RLvy;
	float m_RLr; //画像角度調整

	int m_ani_frame; //描画フレーム
	int m_ani_time;	//アニメーションフレーム動作間隔	

	float hx; //主人公位置取得用
	float hy;

	int m_Distance_max; //削除距離最大値
	
	int m_EXPDameg_num; //爆発ダメージ

	bool Hp_f; //HP減少フラグ
	bool En_f; //耐久力減少フラグ

	bool m_HitBox_Delete; //HitBox削除フラグ
};