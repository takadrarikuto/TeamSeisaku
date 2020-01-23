//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoZombieEnemy.h"

//使用するネームスペース
using namespace GameL;

//チュートリアルONOFFフラグ
bool Tuto_flg = false;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//コンストラクタ
CObjTutoZombieEnemy::CObjTutoZombieEnemy(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_zex = x;
	m_zey = y;
}

//イニシャライズ
void CObjTutoZombieEnemy::Init()
{
	//初期化
	//体力
	m_hero_hp = 50;

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	m_zombie_count_tu = 0;

	m_time_d = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 4);
}

//アクション
void CObjTutoZombieEnemy::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	bool h_gel = hero->GetDel(); //削除チェック

	//爆発
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	m_zex += -hvx;
	m_zey += -hvy;

	//HitBoxの内容を更新
	CHitBox* hit_ze = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ze->SetPos(m_zex, m_zey); //当たり判定の位置更新

	//敵機・敵弾・トラップ系オブジェクトと接触したら主人公機無敵時間開始
	//ハンドガン
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= Gun_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//ショットガン
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= SHG_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//アサルトライフル
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= AR_Attack;
		m_time_d = 30;		//点滅時間をセット
	}
	//スナイパーライフル
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= SR_Attack;
		m_time_d = 5;		//点滅時間をセット
	}
	//ロケットランチャー
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= RL_Attack;
		m_time_d = 5;		//点滅時間をセット
	}
	//レールガン
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= RG_Attack;
		m_time_d = 5;		//点滅時間をセット
	}
	//爆発
	else if (hit_ze->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
	{
		m_hero_hp -= EXPDamage;
	}

	if (m_hero_hp <= 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
		Audio::Start(15);
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する

		g_zombie_count_tu += 1;
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}
}

//ドロー
void CObjTutoZombieEnemy::Draw()
{
	//描画カラー情報
	float c[4] = {  1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	//モーション
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 64.0f;
	src.m_left = 26.0f;
	src.m_right = 50.0f;
	src.m_bottom = 95.0f;
	
	//描画処理
	dst.m_top = 0.0f + m_zey;
	dst.m_left = 0.0f + m_zex;
	dst.m_right = m_dst_size + m_zex;
	dst.m_bottom = m_dst_size + m_zey;

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
}