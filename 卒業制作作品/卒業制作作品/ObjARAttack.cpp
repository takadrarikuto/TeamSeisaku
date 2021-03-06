//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjARAttack.h"

//使用するネームスペース
using namespace GameL;

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
	//主人公位置取得用
	hy = 0.0f;
	hx = 0.0f;

	//削除距離最大値
	m_Distance_max = 3;

	//描画サイズ
	m_dst_size = 32.0f;
	//当たり判定サイズ
	Hitbox_size = 10;

	//HitBox削除フラグ
	m_HitBox_Delete = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ARx, m_ARy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ARATTACK, 2);

}

//アクション
void CObjARAttack::Action()
{
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//位置更新
		m_ARx += m_ARvx;
		m_ARy += m_ARvy;
	}

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//チュートリアル主人公情報取得
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//HitBoxの内容を更新 
	CHitBox* hit_ar = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ar->SetPos(m_ARx + 11, m_ARy + 11); //当たり判定の位置更新

	//主人公、チュートリアル主人公のどちらかが生成されている時
	//主人公用
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//主人公から離れるとオブジェクト削除
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	//チュートリアル主人公用
	if (Tuhero != nullptr)
	{
		hx = Tuhero->GetX();
		hy = Tuhero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	
	
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
			m_HitBox_Delete = true;
		}
	}
	//壁オブジェクト、有刺鉄線オブジェクトと接触するとオブジェクト破棄
	if (hit_ar->CheckElementHit(ELEMENT_WALL) == true || hit_ar->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_ar->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
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
			m_HitBox_Delete = true;
		}		
	}

	//削除処理
	if (m_HitBox_Delete == true)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する

		m_HitBox_Delete = false; //初期化
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