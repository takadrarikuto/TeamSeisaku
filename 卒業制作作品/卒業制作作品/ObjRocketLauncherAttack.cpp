//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRocketLauncherAttack.h"

//使用するネームスペース
using namespace GameL;

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
	//主人公位置取得用
	hy = 0.0f;
	hx = 0.0f;

	//描画フレーム
	m_ani_frame = 0;
	//アニメーションフレーム動作間隔
	m_ani_time = 0;

	//削除距離最大値
	m_Distance_max = 5;

	//ダメージ量
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool Hp_f = hero->GetHP_F();
	bool En_f = hero->GetEN_F();
	//耐久力フラグがオンの時
	if (En_f == true)
	{
		m_EXPDameg_num = 75; //爆発ダメージ
	}
	//体力フラグがオンの時
	if (Hp_f == true)
	{
		m_EXPDameg_num = 150; //爆発ダメージ
	}

	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = 320.0f;

	//HitBox削除フラグ
	m_HitBox_Delete = false;

	if (m_RLr == 0 || m_RLr == 180)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RLx, m_RLy, 32, 70, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_RLx, m_RLy, 70, 32, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);
	}
	
}

//アクション
void CObjRocketLauncherAttack::Action()
{
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//アニメーションフレーム更新
		m_ani_time++;

		//位置更新
		m_RLx += m_RLvx;
		m_RLy += m_RLvy;

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
	//チュートリアル主人公情報取得
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

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

	//主人公、チュートリアル主人公のどちらかが生成されている時	
	//主人公用
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//主人公から離れるとオブジェクト削除
		if (m_RLx < hx - 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLx > hx + 32 + 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		if (m_RLy < hy - 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLy > hy + 32 + 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
	}
	//チュートリアル主人公用
	if (Tuhero != nullptr)
	{
		hx = Tuhero->GetX();
		hy = Tuhero->GetY();

		//主人公から離れるとオブジェクト削除
		if (m_RLx < hx - 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLx > hx + 32 + 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		if (m_RLy < hy - 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLy > hy + 32 + 64 * m_Distance_max)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
	}
	
	

	//敵オブジェクトと接触するとオブジェクト破棄
	if (hit_rl->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_rl->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_rl->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			; //火の鳥、ミーム実態(中ボス)、ボス、小さい有刺鉄線には当たらない
		}
		else
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
	}	
	//壁オブジェクトと接触するとオブジェクト破棄
	if (hit_rl->CheckElementHit(ELEMENT_WALL) == true || hit_rl->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_rl->CheckElementHit(ELEMENT_NET_S) == true || hit_rl->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_rl->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		//爆発オブジェクト作成
		CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, m_EXPDameg_num);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
		Audio::Start(9);

		m_HitBox_Delete = true;
	}
	//フィールドエレメントと接触すると削除
	if (hit_rl->CheckElementHit(ELEMENT_FIELD) == true || hit_rl->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_rl->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
		{
			; //アイテム系には当たらない
		}
		else
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

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

	Draw::Draw(2, &src, &dst, c, m_RLr);

}