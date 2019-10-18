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
	m_gax = x;
	m_gay = y;
	//移動ベクトル
	m_gavx = vx;
	m_gavy = vy;
	//画像角度調整
	m_gar = r;
}

//イニシャライズ
void CObjARAttack::Init()
{
	//初期化
		//描画フレーム
	m_ani_frame = 0;
	//アニメーションフレーム動作間隔
	m_ani_time = 0;

	//削除距離最大値
	Distance_max = 3;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_gax, m_gay, 10, 10, ELEMENT_RED, OBJ_GUNATTACK, 3);

}

//アクション
void CObjARAttack::Action()
{
	//アニメーションフレーム更新
	m_ani_time++;

	//メニューを開くと行動停止
	//if (Menu_flg == false)
	//{
	//位置更新
	m_gax += m_gavx;
	m_gay += m_gavy;
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

	//アニメーション処理
	if (m_ani_time > 6)
	{
		m_ani_time = 0;
		m_ani_frame += 1;
	}

	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}

	//HitBoxの内容を更新 
	CHitBox* hit_ga = Hits::GetHitBox(this); //当たり判定情報取得
	hit_ga->SetPos(m_gax + 11, m_gay + 11); //当たり判定の位置更新

	//主人公から離れるor画面端に行くとオブジェクト削除
	if (m_gax < hx - 64 * Distance_max || m_gax < 0.0f)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_gax + 32 > hx + 64 * Distance_max || m_gax + 32 > 800.0f)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	if (m_gay < hy - 64 * Distance_max || m_gay < 0.0f)
	{
		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
	else if (m_gay + 32 > hy + 64 * Distance_max || m_gay + 32 > 600.0f)
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
void CObjARAttack::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//モーション
	int AniData[8] =
	{
		0,1,2,3,4,5,6,7,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 30.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 100;
	src.m_right = 100.0f + AniData[m_ani_frame] * 100;
	src.m_bottom = 70.0f;
	//描画処理
	dst.m_top = 0.0f + m_gay;
	dst.m_left = 0.0f + m_gax;
	dst.m_right = 32.0f + m_gax;
	dst.m_bottom = 32.0f + m_gay;

	Draw::Draw(3, &src, &dst, c, m_gar);

}