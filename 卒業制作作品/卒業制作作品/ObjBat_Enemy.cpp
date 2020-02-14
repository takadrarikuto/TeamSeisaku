//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBat_Enemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBat_Enemy::CObjBat_Enemy(float bex, float bey)
{
	//位置情報登録(数値=位置調整)
	m_bex = bex;
	m_bey = bey;
}

//イニシャライズ
void CObjBat_Enemy::Init()
{
	//初期化
	//移動ベクトル
	m_bevx = 0.0f;
	m_bevy = 0.0f;

	//移動方向確認タイム
	m_move_time = 0;

	//体力
	m_hero_hp = 10;

	//移動ベクトル最大値
	m_bev_max = 3.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 2; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//移動フラグ
	m_be_x_flg = false;
	m_be_y_flg = false;

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

	//攻撃頻度
	m_at = 0;
	//攻撃頻度最大値
	m_at_max = 5;

	//ダメージ点滅時間用
	m_time_d = 0;

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bex, m_bey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_BAT_ENEMY, 4);
}

//アクション
void CObjBat_Enemy::Action()
{

	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX(); //位置
	float hy = hero->GetY();
	float hvx = hero->GetVX(); //移動ベクトル
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_bex; //位置更新
	float hpy = hero->GetPY() - m_bey;

	//ボス
	CObjBoss* boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//アイテムドロップ情報取得
	CObjAitemDrop* AitemDrop = (CObjAitemDrop*)Objs::GetObj(OBJ_AITEMDROP);

	//爆発
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
	{	
		m_bevx = 0.0f; //x移動ベクトル初期化
		m_bevy = 0.0f; //y移動ベクトル初期化
		m_ani_time += 1; //アニメーション進行	
		m_move_time += 1; //移動方向確認タイム進行

		//移動処理
		//上下移動開始
		if (m_move_time < Y_Move)
		{			
			//主人公が上に居ると上に移動
			if (hy < m_bey)
			{
				m_bevy = -m_bev_max;
				m_UDani_frame = 0;
			}
			//主人公が下に居ると下移動
			else if (hy > m_bey)
			{
				m_bevy = m_bev_max;
				m_UDani_frame = 2;
			}
		}
		//左右移動開始
		else if (m_move_time >= Y_Move && m_move_time < X_Move)
		{			
			//主人公が左に居ると左に移動
			if (hx < m_bex)
			{
				m_bevx = -m_bev_max;
				m_UDani_frame = 3;
			}
			//主人公が右に居ると右に移動
			else if (hx > m_bex)
			{
				m_bevx = m_bev_max;
				m_UDani_frame = 1;
			}
		}
		else if (m_move_time == X_Move)
		{
			m_move_time = 0; //移動方向確認タイム初期化
		}

		//位置更新
		//主人公の移動を適応する
		m_bex += (-hvx) + m_bevx;
		m_bey += (-hvy) + m_bevy;

		//アニメーション処理
		if (m_ani_time > 6)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		if (m_LRani_frame == 3)
		{
			m_LRani_frame = 0;
		}
	}

	//HitBoxの内容を更新
	CHitBox* hit_be = Hits::GetHitBox(this); //当たり判定情報取得
	hit_be->SetPos(m_bex, m_bey); //当たり判定の位置更新

	//当たり判定処理
	if (hit_be->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_be->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_be->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_bevx = -0.15f; //右
				}
				if (r > 88 && r < 92)
				{
					m_bevy = 0.15f;//上
				}
				if (r > 92 && r < 268)
				{
					m_bevx = 0.15f;//左
				}
				if (r > 268 && r < 292)
				{
					m_bevy = -0.15f; //下
				}
			}
		}
	}
	else
	{
		//上下左右別当たり判定確認フラグ初期化
		m_UpHit_flg = false;    //上
		m_DownHit_flg = false;	 //下
		m_LeftHit_flg = false;	 //左
		m_RightHit_flg = false; //右
	}
	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_be->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_be->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_be->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_bevx = -0.15f; //右
				}
				if (r > 2 && r < 178)
				{
					m_bevy = 0.15f;//上
				}
				if (r > 178 && r < 182)
				{
					m_bevx = 0.15f;//左
				}
				if (r > 182 && r < 358)
				{
					m_bevy = -0.15f; //下
				}
			}
		}
	}
	else
	{
		//上下左右別当たり判定確認フラグ初期化
		m_UpHit_flg = false;    //上
		m_DownHit_flg = false;	 //下
		m_LeftHit_flg = false;	 //左
		m_RightHit_flg = false; //右
	}

	//主人公弾・爆発オブジェクトと接触したら敵ダメージ、無敵時間開始
	if (m_time_d == 0)
	{
		//ハンドガン
		if (hit_be->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
		{
			m_hero_hp -= Gun_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//ショットガン
		else if (hit_be->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
		{
			m_hero_hp -= SHG_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//アサルトライフル
		else if (hit_be->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
		{
			m_hero_hp -= AR_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//スナイパーライフル
		else if (hit_be->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
		{
			m_hero_hp -= SR_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//ロケットランチャー
		else if (hit_be->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
		{
			m_hero_hp -= RL_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//レールガン
		else if (hit_be->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
		{
			m_hero_hp -= RG_Attack;
			m_time_d = 1;		//点滅時間をセット
		}
		//爆発
		else if (hit_be->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
		{
			m_hero_hp -= EXPDamage;
		}
	}	

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_hero_hp <= 0)
	{
		AitemDrop->SetAitemDrop(true);
		AitemDrop->SetBatDrop(true);
		AitemDrop->SetBat_X(m_bex);
		AitemDrop->SetBat_Y(m_bey);
		boss->SetBR(1);

		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_bex, m_bey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
		Audio::Start(15);

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
	}
}

//ドロー
void CObjBat_Enemy::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	//モーション
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 135.0f + m_UDani_frame * 32.0f;
	src.m_left = 74.4f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_right = 98.0f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_bottom = 170.0f + m_UDani_frame * 32.0f;
	//描画処理
	dst.m_top = 0.0f + m_bey;
	dst.m_left = 0.0f + m_bex;
	dst.m_right = m_dst_size + m_bex;
	dst.m_bottom = m_dst_size + m_bey;

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

}