//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include <time.h>

#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBoss.h"

//使用するネームスペース
using namespace GameL;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

//コンストラクタ
CObjBoss::CObjBoss(float bx, float by)
{
	//位置情報登録(数値=位置調整)
	m_bx = bx;
	m_by = by;
}

//イニシャライズ
void CObjBoss::Init()
{
	//初期化
	//スクロール初期化
	m_scrollx = 0.0f;
	m_scrolly = 0.0f;

	//エネミー出現位置
	e_x = 0.0f;
	e_y = 0.0f;
	//ゾンビ生成座標記録
	m_Enemy_Generation_x = 0.0f;
	m_Enemy_Generation_y = 0.0f;
	//ボス移動ベクトル
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//敵生成頻度
	m_Zombie_Generation = 0; //ゾンビ生成頻度
	m_Bat_Enemy_Generation = 0; //蝙蝠生成頻度
	m_Frie_Lizard_Generation = 0; //火トカゲ敵生成頻度
	m_Frie_Bird_Generation = 0; //火の鳥敵生成頻度
	m_Sphere_Type_Enemy_Generation = 0; //球体型敵敵生成頻度
//ゾンビ
	//ゾンビ生成数制限
	m_Zombie_Restriction = 0;
	m_Zombie_Restriction_num = 0; //ゾンビ生成数制限減少
	m_Zombie_Restriction_max = 5; //ゾンビ生成数制限最大数	
	m_Zombie_time_max = 200; //ゾンビ生成タイム最大値	
	Ze_dst_flg_num = 0; //ゾンビランダム描画切り替え用	
	Ze_dst_flg = false; //ゾンビランダム描画切り替え用フラグ
//蝙蝠	
	m_Bat_Enemy_time_max = 300; //蝙蝠生成タイム最大値	
	m_Bat_Enemy_Restriction = 0; //蝙蝠生成数制限
	m_Bat_Enemy_Restriction_num = 0; //蝙蝠生成数制限減少
	m_Bat_Enemy_Restriction_max = 9; //蝙蝠生成数制限最大数	
	m_Bat_Enemy_co_num = 3; //蝙蝠生成数カウント変数

	m_Bat_Enemy_x = 0.0f; //x位置修正
	m_Bat_Enemy_y = 0.0f; //y位置修正
//火の鳥	
	m_Frie_Bird_time_max = 900; //火の鳥生成タイム最大値	
	m_Frie_Bird_Restriction = 0; //火の鳥生成数制限
	m_Frie_Bird_Restriction_num = 0; //火の鳥生成数制限減少
	m_Frie_Bird_Restriction_max = 2; //火の鳥生成数制限最大値	
//火トカゲ	
	m_Frie_Lizard_time_max = 400; //火トカゲ生成タイム最大値
	m_Frie_Lizard_Restriction = 0; //火トカゲ生成数制限
	m_Frie_Lizard_Restriction_num = 0; //火トカゲ生成数制限減少
	m_Frie_Lizard_Restriction_max = 5; //火トカゲ生成数制限最大値
//球体型敵	
	m_Sphere_Type_Enemy_Restriction = 5 + (((UserData*)Save::GetData())->choose - 1); //球体型敵生成数
	m_Sphere_Type_Enemy_Restriction_Stop_flg = false; //球体型生成停止フラグ

	m_Sphere_Type_Enemy_x = 0.0f; //x位置修正
	m_Sphere_Type_Enemy_y = 0.0f; //y位置修正
//ミーム実態
	m_Meme_Medium_Boss_Restriction_Stop_flg = false; //ミーム実態生成停止フラグ

	//描画サイズ
	m_dst_size = 128.0f;
	//当たり判定サイズ
	Hitbox_size = 128;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, Hitbox_size * 2, Hitbox_size, ELEMENT_ENEMY, OBJ_BOSS, 3);
}

//アクション
void CObjBoss::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();
	bool Eve_Rep_E = Event->GetEvePena_Enemy();
	bool Eve_Rep_M = Event->GetEvePena_Meme();
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//移動停止
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//主人公の移動ベクトルをボスの移動ベクトルに入れる
		m_bvx += hvx;
		m_bvy += hvy;

		//移動処理
		m_bx -= m_bvx;
		m_by -= m_bvy;
		//エネミー生成処理
		m_Zombie_Generation++; //ゾンビ生成頻度
		m_Bat_Enemy_Generation++; //蝙蝠生成頻度
		m_Frie_Lizard_Generation++; //火トカゲ敵生成頻度
		m_Frie_Bird_Generation++; //火の鳥敵生成頻度
	//エネミー生成数制限減少処理
		//ゾンビ
		if (m_Zombie_Restriction_num > 0)
		{
			m_Zombie_Restriction -= m_Zombie_Restriction_num;
			m_Zombie_Restriction_num = 0;
		}
		//蝙蝠
		if (m_Bat_Enemy_Restriction_num > 0)
		{
			m_Bat_Enemy_Restriction -= m_Bat_Enemy_Restriction_num;
			m_Bat_Enemy_Restriction_num = 0;
		}
		//火トカゲ
		if (m_Frie_Lizard_Restriction_num > 0)
		{
			m_Frie_Lizard_Restriction -= m_Frie_Lizard_Restriction_num;
			m_Frie_Lizard_Restriction_num = 0;
		}
		//火の鳥
		if (m_Frie_Bird_Restriction_num > 0)
		{
			m_Frie_Bird_Restriction -= m_Frie_Bird_Restriction_num;
			m_Frie_Bird_Restriction_num = 0;
		}

		e_x = rand() % 192 + m_bx;
		e_y = rand() % 64 + m_by;
		
		e_x -= hvx;
		e_y -= hvy;

		//エネミー生成処理
		//ゾンビ
		if (m_Zombie_Generation >= m_Zombie_time_max)
		{
			if (m_Zombie_Restriction < m_Zombie_Restriction_max)
			{
				//ゾンビの伏せている、立っている描画切り替え処理
				Ze_dst_flg_num = rand() % 100;
				if (Ze_dst_flg_num <= 30)
				{
					Ze_dst_flg = true;
				}
				else if (Ze_dst_flg_num > 30)
				{
					Ze_dst_flg = false;
				}

				//ゾンビオブジェクト作成
				CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y, Ze_dst_flg);
				Objs::InsertObj(obj_ze, OBJ_ENEMY, 5);

				Audio::Start(11);

				//ゾンビ生成座標記録
				m_Enemy_Generation_x = e_x;
				m_Enemy_Generation_y = e_y;

				m_Zombie_Restriction++; //ゾンビ生成カウント
			}			
			m_Zombie_Generation = 0;
		}
		//蝙蝠
		if (m_Bat_Enemy_Generation >= m_Bat_Enemy_time_max)
		{
			if (m_Bat_Enemy_Restriction < m_Bat_Enemy_Restriction_max)
			{
				for (int i = 1; i <= m_Bat_Enemy_co_num; i++)
				{
					//蝙蝠オブジェクト作成
					CObjBat_Enemy* obj_be = new CObjBat_Enemy(e_x + m_Bat_Enemy_x, e_y + m_Bat_Enemy_y);
					Objs::InsertObj(obj_be, OBJ_BAT_ENEMY, 5);

					if (i % 2 == 0 && i != 0)
					{
						m_Bat_Enemy_x += 50.0f; //x位置修正
					}
					else if (i % 2 != 0)
					{
						m_Bat_Enemy_y += 30.0f; //y位置修正
					}		

					
				}	
				Audio::Start(20);
				m_Bat_Enemy_Restriction += 3; //蝙蝠生成カウント
			}				
			m_Bat_Enemy_Generation = 0;
		}
		//火トカゲ
		if (m_Frie_Lizard_Generation >= m_Frie_Lizard_time_max)
		{
			if (m_Frie_Lizard_Restriction < m_Frie_Lizard_Restriction_max)
			{
				//火トカゲオブジェクト作成 
				CObjFire_Lizard* obj_fl = new CObjFire_Lizard(e_x, e_y);
				Objs::InsertObj(obj_fl, OBJ_FIRE_LIZARD, 5);

				m_Frie_Lizard_Restriction++; //火トカゲ生成カウント	
			}			
			m_Frie_Lizard_Generation = 0;
		}
		//火の鳥
		if (m_Frie_Bird_Generation >= m_Frie_Bird_time_max)
		{
			if (m_Frie_Bird_Restriction < m_Frie_Bird_Restriction_max)
			{
				//火の鳥オブジェクト作成
				CObjFire_Bird* obj_fb = new CObjFire_Bird(e_x, e_y);
				Objs::InsertObj(obj_fb, OBJ_FIRE_BIRD, 5);

				m_Frie_Bird_Restriction++; //火の鳥生成カウント
			}			
			m_Frie_Bird_Generation = 0;
		}

		//敵無力化イベント時敵生成
		if ((END_flg == true || Eve_Rep_E == true) && m_Sphere_Type_Enemy_Restriction_Stop_flg == false)
		{
			for (int c = 1; c < m_Sphere_Type_Enemy_Restriction; c++)
			{
				//球体型敵オブジェクト作成
				CObjSphere_Type_Enemy* obj_ste = new CObjSphere_Type_Enemy(e_x + m_Sphere_Type_Enemy_x, e_y + m_Sphere_Type_Enemy_y);
				Objs::InsertObj(obj_ste, OBJ_SPHERE_TYPE_ENEMY, 5);

				if (c % 2 == 0 && c != 0)
				{
					m_Sphere_Type_Enemy_x += 50.0f; //x位置修正
				}
				else if (c % 2 != 0)
				{
					m_Sphere_Type_Enemy_y += 30.0f; //y位置修正
				}
			}			
			m_Sphere_Type_Enemy_Restriction_Stop_flg = true; //球体型生成停止フラグ
			Eve_Rep_E = false;
			Event->SetEvePena_Enemy(Eve_Rep_E);
		}		
		if ((MND_flg == true || Eve_Rep_M == true) && m_Meme_Medium_Boss_Restriction_Stop_flg == false)
		{
			//ミーム実態(中ボス)オブジェクト作成
			CObjMeme_Medium_Boss* obj_mmb = new CObjMeme_Medium_Boss(e_x, e_y);
			Objs::InsertObj(obj_mmb, OBJ_MEME_MEDIUM_BOSS, 5);

			m_Meme_Medium_Boss_Restriction_Stop_flg = true; //ミーム実態生成停止フラグ
			Eve_Rep_M = false;
			Event->SetEvePena_Meme(Eve_Rep_M);
		}
		//初期化処理
		if (END_flg == false)
		{
			m_Sphere_Type_Enemy_Restriction_Stop_flg = false; //球体型生成停止フラグ
		}
		if (MND_flg == false)
		{
			m_Meme_Medium_Boss_Restriction_Stop_flg = false; //ミーム実態生成停止フラグ
		}
	}
	
	//HitBoxの内容を更新
	CHitBox* hit_boss = Hits::GetHitBox(this); //当たり判定情報取得
	hit_boss->SetPos(m_bx, m_by); //当たり判定の位置更新
	
}

//ドロー
void CObjBoss::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };


	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 279.0f;
	src.m_bottom = 181.0f;
	//描画処理
	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = m_dst_size * 2 + m_bx;
	dst.m_bottom = m_dst_size + m_by;
	Draw::Draw(3, &src, &dst, c, 0.0f);
}