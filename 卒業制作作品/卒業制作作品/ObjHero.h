#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHero : public CObj, public CBaseStatus
{
public:
	CObjHero(float x, float y);
	~CObjHero() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	int GetWS() { return m_Weapon_switching; }
	int GetHP() { return m_hero_hp; }	//主人公のHPを取得

	int GetSG() { return m_sg_pb_num; }	//ショットガンの残り弾数を取得
	int GetAR() { return m_ar_pb_num; }	//アサルトライフルの残り弾数を取得
	int GetSR() { return m_sr_pb_num; }	//スナイパーライフルの残り弾数を取得
	int GetRL() { return m_rl_pb_num; }	//ロケットランチャーの残り弾数を取得
	int GetRG() { return m_rg_pb_num; }	//レールガンの残り弾数を取得

	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }

private:
	float m_x; //位置更新
	float m_y;
	float m_vx; //移動ベクトル
	float m_vy;
	float m_v_max; //移動ベクトル最大値
	float m_ga_vx_max; //武器攻撃移動ベクトル最大値
	float m_ga_vy_max;
	float m_speed_power; //スピードパワー

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_ani_time;	//アニメーションフレーム動作間隔	
	int m_LRani_frame;

	int m_damage;	//主人公が受けるダメージ用

	int m_time_d;	//ダメージ無敵時間用
	int m_time_dead;	//死亡用

	int m_bt; //攻撃頻度
	int m_bt_max; //攻撃頻度最大値

	int m_hg_pb;//ハンドガン現在弾数用(上部表示用)
	int m_sg_pb;//ショットガン現在弾数用(上部表示用)
	int m_ar_pb;//アサルトライフル現在弾数用(上部表示用)
	int m_sr_pb;//スナイパーライフル現在弾数用(上部表示用)
	int m_rl_pb;//ロケットランチャー現在弾数用(上部表示用)
	int m_rg_pb;//レールガン現在弾数用(上部表示用)

	int m_sg_pb_num;//ショットガン残り弾数
	int m_ar_pb_num;//アサルトライフル残り弾数
	int m_sr_pb_num;//スナイパーライフル残り弾数
	int m_rl_pb_num;//ロケットランチャー残り弾数
	int m_rg_pb_num;//レールガン残り弾数

	int m_Weapon_switching; //武器切り替え
	bool m_Weapon_switching_flg; //武器切り替えフラグ
	bool m_Grenade_flg; //グレネード投下処理

	bool m_del;			//削除チェック
	bool m_eff_flag;	//エフェクト用フラグ

	bool m_del;			//削除チェック
	bool m_eff_flag;	//エフェクト用フラグ
	bool m_inputf;	//死亡用キー入力制御

};