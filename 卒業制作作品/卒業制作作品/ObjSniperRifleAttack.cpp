//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSniperRifleAttack.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSniperRifleAttack::CObjSniperRifleAttack(float x, float y, float vx, float vy, float r)
{
	//位置情報登録(数値=位置調整)
	m_SRx = x;
	m_SRy = y;
	//移動ベクトル
	m_SRvx = vx;
	m_SRvy = vy;
	//画像角度調整
	m_SRr = r;
}

//イニシャライズ
void CObjSniperRifleAttack::Init()
{
//初期化
	//削除距離最大値
	m_Distance_max = 4;

	//HitBox削除フラグ
	m_HitBox_Delete = false;

	if (m_SRr == 0 || m_SRr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_SRx, m_SRy, 10, 32, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 2);
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_SRx, m_SRy, 32, 10, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 2);
	}


}

//アクション
void CObjSniperRifleAttack::Action()
{
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//位置更新
		m_SRx += m_SRvx;
		m_SRy += m_SRvy;
	}

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//HitBoxの内容を更新 
	CHitBox* hit_sr = Hits::GetHitBox(this); //当たり判定情報取得
	if (m_SRr == 0 || m_SRr == 180)
	{
		hit_sr->SetPos(m_SRx, m_SRy); //当たり判定の位置更新
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		hit_sr->SetPos(m_SRx - 10.0f, m_SRy + 10.0f); //当たり判定の位置更新
	}

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_SRx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_SRy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}

	//壁オブジェクトと接触するとオブジェクト破棄
	if (hit_sr->CheckElementHit(ELEMENT_WALL) == true || hit_sr->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_sr->CheckElementHit(ELEMENT_NET_S) == true || hit_sr->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_sr->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
	}
	//フィールドエレメントと接触すると削除
	if (hit_sr->CheckElementHit(ELEMENT_FIELD) == true || hit_sr->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_sr->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
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
void CObjSniperRifleAttack::Draw()
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
	dst.m_top = 0.0f + m_SRy;
	dst.m_left = 0.0f + m_SRx;
	dst.m_right = 10.0f + m_SRx;
	dst.m_bottom = 32.0f + m_SRy;

	Draw::Draw(2, &src, &dst, c, m_SRr);

}