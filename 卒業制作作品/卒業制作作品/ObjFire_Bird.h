#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjFire_Bird : public CObj, public CBaseStatus
{
public:
	CObjFire_Bird(float zex, float zey);
	~CObjFire_Bird() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	//float GetX() { return m_zex; } //エネミー情報取得用
	//float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得

private:

	float m_fbx; //位置更新
	float m_fby;
	float m_fbvx; //移動ベクトル
	float m_fbvy;
	float m_fbv_max; //移動ベクトル最大値

	bool m_fb_x_flg; //移動フラグ
	bool m_fb_y_flg;

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_RightHit_flg; //右

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//描画フレーム切り替えフラグ
	int m_ani_time;	//アニメーションフレーム動作間隔	

	int m_at; //攻撃頻度
	int m_at_max; //攻撃頻度最大値
};