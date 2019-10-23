//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjShotGunAttack.h"

//使用するネームスペース
using namespace GameL;

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
	Distance_max = 2;

	//攻撃力
	m_Offensive_Power = 30; 

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_SGx, m_SGy, 10, 10, ELEMENT_RED, OBJ_GUNATTACK, 3);

}

//アクション
void CObjShotGunAttack::Action()
{
	//メニューを開くと行動停止
	//if (Menu_flg == false)
	//{
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
	hit_ga->SetPos(m_SGx + 11, m_SGy + 11); //当たり判定の位置更新
		
	//主人公から離れるor画面端に行くとオブジェクト削除
	if (m_SGx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_SGx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	if (m_SGy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_SGy> hy + 64 * Distance_max)
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
	dst.m_right = 32.0f + m_SGx;
	dst.m_bottom = 32.0f + m_SGy;

	Draw::Draw(3, &src, &dst, c, m_SGr);

}