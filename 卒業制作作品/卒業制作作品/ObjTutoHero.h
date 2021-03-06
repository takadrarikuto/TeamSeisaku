#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoHero : public CObj, public CBaseStatus
{
public:
	CObjTutoHero(float x, float y);
	~CObjTutoHero() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetPX() { return m_px; }
	float GetPY() { return m_py; }
	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }
	float GetHitBox() { return m_dst_size; }

	int GetWS() { return m_Weapon_switching; }
	int GetHP() { return m_hero_hp; }	//主人公のHPを取得
	int GetUDAF() { return m_UDani_frame; } //上下アニメーション取得用

	//上下左右別当たり判定確認フラグ取得用
	bool GetUH() { return m_UpHit_flg; }  //上
	bool GetDH() { return m_DownHit_flg; } //下
	bool GetLH() { return m_LeftHit_flg; }	 //左
	bool GetRH() { return m_RightHit_flg; } //右

	int GetHG_E() { return m_hg_pb; }	//ハンドガンの残り弾数を取得(装備分)
	int GetSG_E() { return m_sg_pb; }	//ショットガンの残り弾数を取得(装備分)
	int GetAR_E() { return m_ar_pb; }	//アサルトライフルの残り弾数を取得(装備分)
	int GetSR_E() { return m_sr_pb; }	//スナイパーライフルの残り弾数を取得(装備分)
	int GetRL_E() { return m_rl_pb; }	//ロケットランチャーの残り弾数を取得(装備分)
	int GetRG_E() { return m_rg_pb; }	//レールガンの残り弾数を取得(装備分)
	int GetGRE_E() { return m_gre_pb; }	//グレネードの残り弾数を取得(装備分)

	int GetSG() { return m_sg_pb_me; }	//ショットガンの残り弾数を取得(全体所持弾用)
	int GetAR() { return m_ar_pb_me; }	//アサルトライフルの残り弾数を取得(全体所持弾用)
	int GetSR() { return m_sr_pb_me; }	//スナイパーライフルの残り弾数を取得(全体所持弾用)
	int GetRL() { return m_rl_pb_me; }	//ロケットランチャーの残り弾数を取得(全体所持弾用)
	int GetRG() { return m_rg_pb_me; }	//レールガンの残り弾数を取得(全体所持弾用)
	int GetGRE() { return m_gre_pb_me; }	//グレネードの残り弾数を取得(全体所持弾用)

	int GetSG_R() { return m_sg_pb_r; }	//ショットガンのリロード用取得
	int GetAR_R() { return m_ar_pb_r; }	//アサルトライフルのリロード用取得
	int GetSR_R() { return m_sr_pb_r; }	//スナイパーライフルのリロード用取得
	int GetRL_R() { return m_rl_pb_r; }	//ロケットランチャーのリロード用取得
	int GetRG_R() { return m_rg_pb_r; }	//レールガンのリロード用取得
	int GetGRE_R() { return m_gre_pb_r; }	//グレネードのリロード用取得

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }
	void SetHP(int hp) { m_hero_hp = hp; }

	//上下左右別当たり判定確認フラグ設定用
	void SetUpHit(float uh) { m_UpHit_flg = uh; }    //上
	void SetDownHit(float dh) { m_DownHit_flg = dh; } //下
	void SetLeftHit(float leh) { m_LeftHit_flg = leh; }	 //左
	void SetrightHit(float rih) { m_RightHit_flg = rih; } //右

	void SetSG(int sg) { m_sg_pb_me = sg; }	//ショットガン弾セット用
	void SetAR(int ar) { m_ar_pb_me = ar; }	//アサルトライフル弾セット用
	void SetSR(int sr) { m_sr_pb_me = sr; }	//スナイパーライフル弾セット用
	void SetRL(int rl) { m_rl_pb_me = rl; }	//ロケットランチャー弾セット用
	void SetRG(int rg) { m_rg_pb_me = rg; }	//レールガン弾セット用
	void SetGRE(int gre) { m_gre_pb_me = gre; }	//グレネードセット用

private:
	float m_x; //位置更新
	float m_y;
	float m_px; //位置把握
	float m_py;
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

	int m_Footprint_time; //足跡生成タイム
	bool m_Footprint_flg; //足跡生成フラグ

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_RightHit_flg; //右

	int m_hg_pb;//ハンドガン現在弾数用(上部表示用)
	int m_sg_pb;//ショットガン現在弾数用(上部表示用)
	int m_ar_pb;//アサルトライフル現在弾数用(上部表示用)
	int m_sr_pb;//スナイパーライフル現在弾数用(上部表示用)
	int m_rl_pb;//ロケットランチャー現在弾数用(上部表示用)
	int m_rg_pb;//レールガン現在弾数用(上部表示用)
	int m_gre_pb;//グレネード現在弾数用(上部表示用)

	int m_sg_pb_c;//ショットガン現在弾数用(計算用)
	int m_ar_pb_c;//アサルトライフル現在弾数用(計算用)
	int m_sr_pb_c;//スナイパーライフル現在弾数用(計算用)
	int m_rl_pb_c;//ロケットランチャー現在弾数用(計算用)
	int m_rg_pb_c;//レールガン現在弾数用(計算用)
	int m_gre_pb_c;//グレネード現在弾数用(計算用)

	int m_sg_pb_cc;//ショットガン現在弾数用(計算用)
	int m_ar_pb_cc;//アサルトライフル現在弾数用(計算用)
	int m_sr_pb_cc;//スナイパーライフル現在弾数用(計算用)
	int m_rl_pb_cc;//ロケットランチャー現在弾数用(計算用)
	int m_rg_pb_cc;//レールガン現在弾数用(計算用)
	int m_gre_pb_cc;//グレネード現在弾数用(計算用)

	int m_sg_pb_me;//ショットガン　メニュー表示用
	int m_ar_pb_me;//アサルトライフル　メニュー表示用
	int m_sr_pb_me;//スナイパーライフル　メニュー表示用
	int m_rl_pb_me;//ロケットランチャー　メニュー表示用
	int m_rg_pb_me;//レールガン　メニュー表示用
	int m_gre_pb_me;//グレネード　メニュー表示用

	int m_sg_pb_r;//ショットガン　リロード用
	int m_ar_pb_r;//アサルトライフル　リロード用
	int m_sr_pb_r;//スナイパーライフル　リロード用
	int m_rl_pb_r;//ロケットランチャー　リロード用
	int m_rg_pb_r;//レールガン　リロード用
	int m_gre_pb_r;//グレネード　リロード用

	int m_sg_pb_num;//ショットガン残り弾数
	int m_ar_pb_num;//アサルトライフル残り弾数
	int m_sr_pb_num;//スナイパーライフル残り弾数
	int m_rl_pb_num;//ロケットランチャー残り弾数
	int m_rg_pb_num;//レールガン残り弾数
	int m_gre_pb_num;//グレネード残り弾数

	int m_Weapon_switching; //武器切り替え
	bool m_Weapon_switching_flg; //武器切り替えフラグ
	bool m_Grenade_flg; //グレネード投下処理

	bool m_hg_flg; //ショットガンリロード処理用フラグ
	bool m_sg_flg; //ショットガンリロード処理用フラグ
	bool m_ar_flg; //アサルトライフルリロード処理用フラグ
	bool m_sr_flg; //スナイパーライフルリロード処理用フラグ
	bool m_rl_flg; //ロケットランチャーリロード処理用フラグ
	bool m_rg_flg; //レールガンリロード処理用フラグ

};