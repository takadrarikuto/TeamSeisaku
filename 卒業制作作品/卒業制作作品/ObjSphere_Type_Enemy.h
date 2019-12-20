#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

//武器別ダメージ
#define RG_Attack  200;  //レールガン

class CObjSphere_Type_Enemy : public CObj, public CBaseStatus
{
public:
	CObjSphere_Type_Enemy(float st_ex, float st_ey);
	~CObjSphere_Type_Enemy() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	//float GetX() { return m_zex; } //エネミー情報取得用
	//float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得
																						 
private:

	float m_st_ex; //位置更新
	float m_st_ey;
	float m_st_evx; //移動ベクトル
	float m_st_evy;
	float m_st_ev_max; //移動ベクトル最大値

	bool m_st_e_x_flg; //移動フラグ
	bool m_st_e_y_flg;

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_RightHit_flg; //右

	int m_at; //攻撃頻度
	int m_at_max; //攻撃頻度最大値

	int m_EXPDameg_num; //爆発ダメージ
};