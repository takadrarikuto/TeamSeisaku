//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjRailGunAttack.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

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
	//削除距離最大値
	Distance_max = 5;

	if (m_RGr == 0 || m_RGr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RGx, m_RGy, 10, 32, ELEMENT_RED, OBJ_RAILGUNATTACK, 3);
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RGx, m_RGy, 32, 10, ELEMENT_RED, OBJ_RAILGUNATTACK, 3);
	}
	

}

//アクション
void CObjRailGunAttack::Action()
{
	//メニューを開くと停止
	if (Menu_flg == false)
	{
	//位置更新
	m_RGx += m_RGvx;
	m_RGy += m_RGvy;
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
	CHitBox* hit_rg = Hits::GetHitBox(this); //当たり判定情報取得
	if (m_RGr == 0 || m_RGr == 180)
	{
		hit_rg->SetPos(m_RGx, m_RGy); //当たり判定の位置更新
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		hit_rg->SetPos(m_RGx - 10.0f, m_RGy + 10.0f); //当たり判定の位置更新
	}

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//主人公から離れるor画面端に行くとオブジェクト削除
		if (m_RGx < hx - 64 * Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_RGx > hx + 32 + 64 * Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		if (m_RGy < hy - 64 * Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_RGy > hy + 32 + 64 * Distance_max)
		{
			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}
	

	//敵オブジェクトと接触するとオブジェクト破棄
	if (hit_rg->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
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

	Draw::Draw(3, &src, &dst, c, m_RGr);

}