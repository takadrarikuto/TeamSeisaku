//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGrenadeAttack.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGrenadeAttack::CObjGrenadeAttack(float x, float y, float vx, float vy)
{
	//位置情報登録(数値=位置調整)
	m_Grex = x;
	m_Grey = y;
	//移動ベクトル
	m_Grevx = vx;
	m_Grevy = vy;
}

//イニシャライズ
void CObjGrenadeAttack::Init()
{
	//初期化
	//主人公位置取得用
	hy = 0.0f;
	hx = 0.0f;
	//主人公ベクトル取得用
	hvx = 0.0f;
	hvy = 0.0f;

	//停止位置
	Stop_max = 3; 

	//ダメージ量
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool Hp_f = hero->GetHP_F();
	bool En_f = hero->GetEN_F();
	//耐久力フラグがオンの時
	if (En_f == true)
	{
		m_EXPDameg_num = 50; //爆発ダメージ
	}
	//体力フラグがオンの時
	if (Hp_f == true)
	{
		m_EXPDameg_num = 100; //爆発ダメージ
	}

	//爆破時間
	EXP_time = 0;

	//描画サイズ
	m_dst_size = 15.0f;
	//当たり判定サイズ
	Hitbox_size = 15;

	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = 192.0f;

	//HitBox削除フラグ
	m_HitBox_Delete = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Grex, m_Grey, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);

}

//アクション
void CObjGrenadeAttack::Action()
{
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();
	
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//チュートリアル主人公情報取得
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false)
	{
		//主人公、チュートリアル主人公のどちらかが生成されている時
		//主人公用
		if (hero != nullptr)
		{
			hx = hero->GetX();
			hy = hero->GetY();
			hvx = hero->GetVX();
			hvy = hero->GetVY();	
		}
		//チュートリアル主人公用
		if (Tuhero != nullptr)
		{
			hx = Tuhero->GetX();
			hy = Tuhero->GetY();
			hvx = Tuhero->GetVX();
			hvy = Tuhero->GetVY();
		}
		//爆破処理
		EXP_time++;

		//位置更新
		//主人公の移動に合わせる
		m_Grex += (-hvx) + m_Grevx;
		m_Grey += (-hvy) + m_Grevy;

		//HitBoxの内容を更新 
		CHitBox* hit_gre = Hits::GetHitBox(this); //当たり判定情報取得
		hit_gre->SetPos(m_Grex, m_Grey); //当たり判定の位置更新


		//主人公から離れるとオブジェクト移動停止
		if (m_Grex < hx - 64 * Stop_max || m_Grex > hx + 32 + 64 * Stop_max
			|| m_Grey < hy - 64 * Stop_max || m_Grey > hy + 32 + 64 * Stop_max 
			|| hit_gre->CheckElementHit(ELEMENT_FIELD) == true || hit_gre->CheckElementHit(ELEMENT_FIELD2) == true
			|| hit_gre->CheckElementHit(ELEMENT_WALL) == true  || hit_gre->CheckElementHit(ELEMENT_WALL2) == true
			|| hit_gre->CheckElementHit(ELEMENT_NET_S) == true || hit_gre->CheckElementHit(ELEMENT_NET_V) == true
			|| hit_gre->CheckElementHit(ELEMENT_BARBED_V) == true)
		{
			//フィールドエレメント、壁エレメントと接触すると削除
			if (hit_gre->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_ARMOR) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_HEAL) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_gre->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_TOOLBOX) != nullptr || hit_gre->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
			{
				; //アイテム系　小さい有刺鉄線には当たらない
			}
			else
			{
				//移動停止
				m_Grevx = 0.0f;
				m_Grevy = 0.0f;				
			}	
		}		
		if (EXP_time >= 180)
		{
			//爆発オブジェクト作成
			CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, m_EXPDameg_num);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}

		//敵オブジェクトと接触するとオブジェクト破棄
		if (hit_gre->CheckElementHit(ELEMENT_ENEMY) == true)
		{
			if (hit_gre->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_gre->CheckObjNameHit(OBJ_BOSS) != nullptr
				|| hit_gre->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr 
				|| hit_gre->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
			{
				; //火の鳥、ミーム実態(中ボス)、ボス、小さい有刺鉄線には当たらない
			}
			else
			{
				//爆発オブジェクト作成
				CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, m_EXPDameg_num);
				Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
				Audio::Start(9);

				m_HitBox_Delete = true;
			}
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
void CObjGrenadeAttack::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 320.0f;
	src.m_left = 15.0f;
	src.m_right = 30.0f;
	src.m_bottom = 330.0f;
	//描画処理
	dst.m_top = 0.0f + m_Grey;
	dst.m_left = 0.0f + m_Grex;
	dst.m_right = m_dst_size + m_Grex;
	dst.m_bottom = m_dst_size + m_Grey;

	Draw::Draw(2, &src, &dst, c, 0.0f);

}