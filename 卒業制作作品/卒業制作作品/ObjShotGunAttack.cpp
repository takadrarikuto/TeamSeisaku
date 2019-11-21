//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjShotGunAttack.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjShotGunAttack::CObjShotGunAttack(float x, float y, float vx, float vy, float r)
{
	//位置情報登録(数値=位置調整)
	m_SGx = x;
	m_SGy = y;
	//移動ベクトル
	m_SGvx = vx;
	m_SGvy = vy;
	//画像角度調整
	m_SGr = r;
}

//イニシャライズ
void CObjShotGunAttack::Init()
{
	//初期化
	//削除距離最大値
	m_Distance_max = 2;

	//所持弾
	m_sga_pb = 60;

	//描画サイズ
	m_dst_size = 32.0f;
	//当たり判定サイズ
	Hitbox_size = 10;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_SGx, m_SGy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_SHOTGUNATTACK, 2);

}

//アクション
void CObjShotGunAttack::Action()
{
	//メニューを開くと停止
	if (Menu_flg == false)
	{
	//斜め移動修正処理
	float r = 0.0f;
	r = m_SGvx * m_SGvx + m_SGvy * m_SGvy;
	r = sqrt(r); //ルートを求める

	//斜めベクトルを求める
	if (r == 0.0f)
	{
		; //0なら何もしない
	}
	else
	{
		m_SGvx = 5.0f / r * m_SGvx;
		m_SGvy = 5.0f / r * m_SGvy;
	}

	//位置更新
	m_SGx += m_SGvx;
	m_SGy += m_SGvy;
	}

	////SE処理
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //音楽スタート
	//	Attack_flg = false; //Attackフラグfalse
	//}


	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//HitBoxの内容を更新 
	CHitBox* hit_sg = Hits::GetHitBox(this); //当たり判定情報取得
	hit_sg->SetPos(m_SGx + 11, m_SGy + 11); //当たり判定の位置更新
		
	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_SGx < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_SGx > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		if (m_SGy < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_SGy > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
	

	//敵オブジェクトと接触するとオブジェクト破棄
	if (hit_sg->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_sg->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_sg->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
		{
			; //火の鳥、ミーム実態(中ボス)、ボスには当たらない
		}
		else
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
	if (hit_sg->CheckElementHit(ELEMENT_FIELD) == true)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjShotGunAttack::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//描画処理
	dst.m_top = 0.0f + m_SGy;
	dst.m_left = 0.0f + m_SGx;
	dst.m_right = m_dst_size + m_SGx;
	dst.m_bottom = m_dst_size + m_SGy;

	Draw::Draw(2, &src, &dst, c, m_SGr);

}