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

//メニューONOFFフラグ
extern bool Menu_flg;

//HP ONOFFフラグ
extern bool Hp_flg;

//耐久力ONOFFフラグ
extern bool En_flg;

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
	//停止位置
	Stop_max = 3; 

	//ダメージ量
	//耐久力フラグがオンの時
	if (En_flg == true)
	{
		((UserData*)Save::GetData())->GRE_Attack = 50; //爆発
	}
	//体力フラグがオンの時
	if (Hp_flg == true)
	{
		((UserData*)Save::GetData())->GRE_Attack = 100; //爆発
	}

	//爆破時間
	EXP_time = 0;

	//描画サイズ
	m_dst_size = 15.0f;
	//当たり判定サイズ
	Hitbox_size = 15;

	//爆発・血しぶき用描画サイズ
	m_exp_blood_dst_size = 192.0f;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Grex, m_Grey, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);

}

//アクション
void CObjGrenadeAttack::Action()
{
	////SE処理
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //音楽スタート
	//	Attack_flg = false; //Attackフラグfalse
	//}	

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//主人公位置取得
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();
		float hvx = hero->GetVX();
		float hvy = hero->GetVY();
		
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
			|| hit_gre->CheckElementHit(ELEMENT_FIELD) == true
			|| hit_gre->CheckElementHit(ELEMENT_WALL) == true || 
			hit_gre->CheckElementHit(ELEMENT_WALL2) == true)
		{
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
			CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, ((UserData*)Save::GetData())->GRE_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //オブジェクト破棄
			Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
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
				CObjExplosion* obj_bs = new CObjExplosion(m_Grex - 80, m_Grey - 90, m_exp_blood_dst_size, ((UserData*)Save::GetData())->GRE_Attack);
				Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

				this->SetStatus(false); //オブジェクト破棄
				Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
			}
		}
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