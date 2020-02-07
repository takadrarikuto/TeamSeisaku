//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjRailGunAttack.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRailGunAttack::CObjRailGunAttack(float x, float y, float vx, float vy, float r)
{
	//位置情報登録(数値=位置調整)
	m_RGx = x;
	m_RGy = y;
	//移動ベクトル
	m_RGvx = vx;
	m_RGvy = vy;
	//画像角度調整
	m_RGr = r;
}

//イニシャライズ
void CObjRailGunAttack::Init()
{
//初期化
	//主人公位置取得用
	hy = 0.0f;
	hx = 0.0f;

	//削除距離最大値
	m_Distance_max = 5;

	//HitBox削除フラグ
	m_HitBox_Delete = false;

	if (m_RGr == 0 || m_RGr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RGx, m_RGy, 10, 32, ELEMENT_RED, OBJ_RAILGUNATTACK, 2);
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RGx, m_RGy, 32, 10, ELEMENT_RED, OBJ_RAILGUNATTACK, 2);
	}
	

}

//アクション
void CObjRailGunAttack::Action()
{
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//位置更新
		m_RGx += m_RGvx;
		m_RGy += m_RGvy;
	}

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//チュートリアル主人公情報取得
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//HitBoxの内容を更新 
	CHitBox* hit_rg = Hits::GetHitBox(this); //当たり判定情報取得
	if (m_RGr == 0 || m_RGr == 180)
	{
		hit_rg->SetPos(m_RGx, m_RGy); //当たり判定の位置更新
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		hit_rg->SetPos(m_RGx - 10.0f, m_RGy + 10.0f); //当たり判定の位置更新
	}

	//主人公、チュートリアル主人公のどちらかが生成されている時
	//主人公用
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_RGx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_RGy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGy > hy + 32 + 64 * m_Distance_max)
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
		if (m_RGx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_RGy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	
	//壁オブジェクトと接触するとオブジェクト破棄
	if (hit_rg->CheckElementHit(ELEMENT_WALL) == true || hit_rg->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_rg->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
	}
	//フィールドエレメントと接触すると削除
	if (hit_rg->CheckElementHit(ELEMENT_FIELD) == true || hit_rg->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_rg->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
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
void CObjRailGunAttack::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 105.0f;
	src.m_left = 10.0f;
	src.m_right = 22.0f;
	src.m_bottom = 130.0f;
	//描画処理
	dst.m_top = 0.0f + m_RGy;
	dst.m_left = 0.0f + m_RGx;
	dst.m_right = 10.0f + m_RGx;
	dst.m_bottom = 32.0f + m_RGy;

	Draw::Draw(2, &src, &dst, c, m_RGr);

}