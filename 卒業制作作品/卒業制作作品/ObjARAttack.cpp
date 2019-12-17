//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjARAttack.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjARAttack::CObjARAttack(float x, float y, float vx, float vy, float r)
{
	//位置情報登録(数値=位置調整)
	m_ARx = x;
	m_ARy = y;
	//移動ベクトル
	m_ARvx = vx;
	m_ARvy = vy;
	//画像角度調整
	m_ARr = r;
}

//イニシャライズ
void CObjARAttack::Init()
{
	//初期化
	//削除距離最大値
	m_Distance_max = 3;

	//描画サイズ
	m_dst_size = 32.0f;
	//当たり判定サイズ
	Hitbox_size = 10;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ARx, m_ARy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ARATTACK, 2);

}

//アクション
void CObjARAttack::Action()
{
	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//位置更新
		m_ARx += m_ARvx;
		m_ARy += m_ARvy;
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
	CHitBox* hit_ar = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ar->SetPos(m_ARx + 11, m_ARy + 11); //当たり判定の位置更新

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
	
	/*OBJ_AR_ITEM
	OBJ_ARMOR
	OBJ_GRENADE_ITEM
	OBJ_HEAL
	OBJ_RAILGUN_ITEM
	OBJ_ROCKETLAUNCHER_ITEM
	OBJ_SHOTGUN_ITEM
	OBJ_SNIPERRIFLE_ITEM
	OBJ_TOOLBOX
	*/
	//敵オブジェクトと接触するとオブジェクト破棄
	if (hit_ar->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_ar->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_ar->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_ar->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr	
			|| hit_ar->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			; //火の鳥、ミーム実態(中ボス)、ボス、小さい有刺鉄線には当たらない
		}
		else 
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
	//壁オブジェクト、有刺鉄線オブジェクトと接触するとオブジェクト破棄ELEMENT_BARBED_V
	if (hit_ar->CheckElementHit(ELEMENT_WALL) == true || hit_ar->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_ar->CheckElementHit(ELEMENT_NET_S) == true || hit_ar->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_ar->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	//フィールドエレメントと接触すると削除
	if (hit_ar->CheckElementHit(ELEMENT_FIELD) == true || hit_ar->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_ar->CheckObjNameHit(OBJ_AR_ITEM) != nullptr|| hit_ar->CheckObjNameHit(OBJ_ARMOR) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_HEAL) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
		{
			; //アイテム系には当たらない
		}
		else
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}		
	}
}

//ドロー
void CObjARAttack::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 30.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 70.0f;
	//描画処理
	dst.m_top = 0.0f + m_ARy;
	dst.m_left = 0.0f + m_ARx;
	dst.m_right = m_dst_size + m_ARx;
	dst.m_bottom = m_dst_size + m_ARy;

	Draw::Draw(2, &src, &dst, c, m_ARr);

}