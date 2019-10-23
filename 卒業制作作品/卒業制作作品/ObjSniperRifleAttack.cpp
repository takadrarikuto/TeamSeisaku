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
	Distance_max = 4;

	if (m_SRr == 0 || m_SRr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_SRx, m_SRy, 10, 32, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 3);
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_SRx, m_SRy, 32, 10, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 3);
	}


}

//アクション
void CObjSniperRifleAttack::Action()
{
	//メニューを開くと行動停止
	//if (Menu_flg == false)
	//{
	//位置更新
	m_SRx += m_SRvx;
	m_SRy += m_SRvy;
	//}

	////SE処理
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //音楽スタート
	//	Attack_flg = false; //Attackフラグfalse
	//}


	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//HitBoxの内容を更新 
	CHitBox* hit_ga = Hits::GetHitBox(this); //当たり判定情報取得
	if (m_SRr == 0 || m_SRr == 180)
	{
		hit_ga->SetPos(m_SRx, m_SRy); //当たり判定の位置更新
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		hit_ga->SetPos(m_SRx - 10.0f, m_SRy + 10.0f); //当たり判定の位置更新
	}


	//主人公から離れるor画面端に行くとオブジェクト削除
	if (m_SRx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_SRx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	if (m_SRy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_SRy> hy + 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}

	//敵機オブジェクトと接触するとオブジェクト破棄
	if (hit_ga->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
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

	Draw::Draw(3, &src, &dst, c, m_SRr);

}