//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjRocketLauncherAttack.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CObjRocketLauncherAttack::CObjRocketLauncherAttack(float x, float y, float vx, float vy, float r)
{
	//位置情報登録(数値=位置調整)
	m_RLx = x;
	m_RLy = y;
	//移動ベクトル
	m_RLvx = vx;
	m_RLvy = vy;
	//画像角度調整
	m_RLr = r;
}

//イニシャライズ
void CObjRocketLauncherAttack::Init()
{
//初期化
	//描画フレーム
	m_ani_frame = 0;
	//アニメーションフレーム動作間隔
	m_ani_time = 0;

	//削除距離最大値
	Distance_max = 5;

	//ダメージ量
	RL_Attack = 150;

	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = 320.0f;

	if (m_RLr == 0 || m_RLr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RLx, m_RLy, 32, 70, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 3);
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RLx, m_RLy, 70, 32, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 3);
	}
	

}

//アクション
void CObjRocketLauncherAttack::Action()
{
	//アニメーションフレーム更新
	m_ani_time++;

	//メニューを開くと停止
	if (Menu_flg == false)
	{
		//位置更新
		m_RLx += m_RLvx;
		m_RLy += m_RLvy;

		////SE処理
		//if (Attack_flg == true)
		//{
		//	Audio::Start(1); //音楽スタート
		//	Attack_flg = false; //Attackフラグfalse
		//}	

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
	}

	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公の移動に合わせる

	//HitBoxの内容を更新 
	CHitBox* hit_rl = Hits::GetHitBox(this); //当たり判定情報取得
	if (m_RLr == 0 || m_RLr == 180)
	{
		hit_rl->SetPos(m_RLx, m_RLy); //当たり判定の位置更新
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		hit_rl->SetPos(m_RLx - 20.0f, m_RLy + 19.0f); //当たり判定の位置更新
	}

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//主人公から離れるとオブジェクト削除
		if (m_RLx < hx - 64 * Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_RLx > hx + 32 + 64 * Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		if (m_RLy < hy - 64 * Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
		else if (m_RLy > hy + 32 + 64 * Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
		}
	}

	//敵オブジェクトと接触するとオブジェクト破棄
	if (hit_rl->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		//爆発オブジェクト作成
		CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, RL_Attack);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}

}

//ドロー
void CObjRocketLauncherAttack::Draw()
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
	src.m_top = 200.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 32;
	src.m_right = 28.0f + AniData[m_ani_frame] * 32;
	src.m_bottom = 280.0f;
	//描画処理
	dst.m_top = 0.0f + m_RLy;
	dst.m_left = 0.0f + m_RLx;
	dst.m_right = 32.0f + m_RLx;
	dst.m_bottom = 70.0f + m_RLy;

	Draw::Draw(3, &src, &dst, c, m_RLr);

}