//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include <time.h>

#include "GameHead.h"
#include "ObjBoss.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

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
	//ゾンビ生成数制限最大値
	m_Zombie_Restriction_max = 10;
	//ゾンビ生成タイム最大値
	m_Zombie_time_max = 300;
	//ゾンビランダム描画切り替え用
	Ze_dst_flg_num = 1;
	//ゾンビランダム描画切り替え用フラグ
	Ze_dst_flg = false;
//蝙蝠
	//蝙蝠生成タイム最大値
	m_Bat_Enemy_time_max = 240; 
	//蝙蝠生成数制限
	m_Bat_Enemy_Restriction = 0; 
	//蝙蝠生成数制限最大値
	m_Bat_Enemy_Restriction_max = 30; 
	//蝙蝠生成数カウント変数
	m_Bat_Enemy_co_num = 1; 
//火の鳥
	//火の鳥生成タイム最大値
	m_Frie_Bird_time_max = 600;
	//火の鳥生成数制限
	m_Frie_Bird_Restriction = 0;
	//火の鳥生成数制限最大値
	m_Frie_Bird_Restriction_max = 2;
//火トカゲ	
	m_Frie_Lizard_time_max = 420; //火トカゲ生成タイム最大値
	m_Frie_Lizard_Restriction = 0; //火トカゲ生成数制限
	m_Frie_Lizard_Restriction_max = 5; //火トカゲ生成数制限最大値
//球体型敵	
	m_Sphere_Type_Enemy_time_max = 300/*3000*/; //球体型敵生成タイム最大値
	m_Sphere_Type_Enemy_Restriction = 0; //球体型敵生成数制限
	m_Sphere_Type_Enemy_Restriction_max = 5; //球体型敵生成数制限最大値

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

	//移動停止
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//主人公の移動ベクトルをボスの移動ベクトルに入れる
		m_bvx += hvx;
		m_bvy += hvy;

		//移動処理
		m_bx -= m_bvx;
		m_by -= m_bvy;
		//エネミー生成処理
		//m_Zombie_Generation++; //ゾンビ生成頻度
		//m_Bat_Enemy_Generation++; //蝙蝠生成頻度
		//m_Frie_Lizard_Generation++; //火トカゲ敵生成頻度
		//m_Frie_Bird_Generation++; //火の鳥敵生成頻度
		m_Sphere_Type_Enemy_Generation++; //球体型敵敵生成頻度

		//e_x = rand() % 192 + m_bx;
		//e_y = rand() % 64 + m_by;
		//
		//e_x -= hvx;
		//e_y -= hvy;

		//エネミー生成処理
		//ゾンビ
		//if (m_Zombie_Generation >= m_Zombie_time_max && m_Zombie_Restriction < m_Zombie_Restriction_max)
		//{
		//	//ゾンビの伏せている、立っている描画切り替え処理
		//	Ze_dst_flg_num = rand() % 3;
		//	if (Ze_dst_flg_num % 2 == 0)
		//	{
		//		Ze_dst_flg = true;
		//	}
		//	else if (Ze_dst_flg_num % 2 != 0)
		//	{
		//		Ze_dst_flg = false;
		//	}

		//	//ゾンビオブジェクト作成
		//	CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y, Ze_dst_flg);
		//	Objs::InsertObj(obj_ze, OBJ_ENEMY, 4);

		//	//ゾンビ生成座標記録
		//	m_Enemy_Generation_x = e_x; 
		//	m_Enemy_Generation_y = e_y;

		//	srand(time(NULL)); // ランダム情報を初期化
		//	m_Zombie_Restriction++; //ゾンビ生成カウント
		//	m_Zombie_Generation = 0;
		//}
		////蝙蝠
		//if (m_Bat_Enemy_Generation >= m_Bat_Enemy_time_max && m_Bat_Enemy_Restriction < m_Bat_Enemy_Restriction_max)
		//{
		//	srand(time(NULL)); // ランダム情報を初期化
		//	m_Bat_Enemy_co_num = rand() % 3;
		//	for (int i = 0; i > m_Bat_Enemy_co_num; i++)
		//	{
		//		//蝙蝠オブジェクト作成
		//		CObjBat_Enemy* obj_be = new CObjBat_Enemy(e_x, e_y);
		//		Objs::InsertObj(obj_be, OBJ_BAT_ENEMY, 4);
		//	}			

		//	m_Bat_Enemy_Generation = 0;
		//	m_Bat_Enemy_Restriction += m_Bat_Enemy_co_num; //蝙蝠生成カウント
		//}
		//火トカゲ
		//if (m_Frie_Lizard_Generation >= m_Frie_Lizard_time_max && m_Frie_Lizard_Restriction < m_Frie_Lizard_Restriction_max)
		//{
		//	//火トカゲオブジェクト作成 
		//	CObjFire_Lizard * obj_fl = new CObjFire_Lizard(e_x, e_y);
		//	Objs::InsertObj(obj_fl, OBJ_FIRE_LIZARD, 4);

		//	srand(time(NULL)); // ランダム情報を初期化
		//	m_Frie_Lizard_Restriction++; //火トカゲ生成カウント	
		//	m_Frie_Lizard_Generation = 0;
		//}
		//火の鳥
		//if (m_Frie_Bird_Generation >= m_Frie_Bird_time_max && m_Frie_Bird_Restriction < m_Frie_Bird_Restriction_max)
		//{
		//	//火の鳥オブジェクト作成
		//	CObjFire_Bird* obj_fb = new CObjFire_Bird(e_x, e_y);
		//	Objs::InsertObj(obj_fb, OBJ_FIRE_BIRD, 4);

		//	srand(time(NULL)); // ランダム情報を初期化
		//	m_Frie_Bird_Restriction++; //火の鳥生成カウント
		//	m_Frie_Bird_Generation = 0;
		//}
		//球体型敵
		if (m_Sphere_Type_Enemy_Generation >= m_Sphere_Type_Enemy_time_max && m_Sphere_Type_Enemy_Restriction < m_Sphere_Type_Enemy_Restriction_max)
		{
			//球体型敵オブジェクト作成
			CObjSphere_Type_Enemy* obj_ste = new CObjSphere_Type_Enemy(e_x, e_y);
			Objs::InsertObj(obj_ste, OBJ_SPHERE_TYPE_ENEMY, 4);
			
			srand(time(NULL)); // ランダム情報を初期化
			m_Sphere_Type_Enemy_Restriction++; //球体型敵生成カウント
			m_Sphere_Type_Enemy_Generation = 0;
		}
		/*
		//ミーム実態(中ボス)オブジェクト作成
		CObjMeme_Medium_Boss* obj_mmb = new CObjMeme_Medium_Boss(100, 150);
		Objs::InsertObj(obj_mmb, OBJ_MEME_MEDIUM_BOSS, 4);
		*/
	}

	//HitBoxの内容を更新
	CHitBox* hit_boss = Hits::GetHitBox(this); //当たり判定情報取得
	hit_boss->SetPos(m_bx, m_by); //当たり判定の位置更新

	////敵機・敵弾・トラップ系オブジェクトと接触したら主人公機無敵時間開始
	//if ((hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr || hit_h->CheckObjNameHit(OBJ_ENEMYBULLET) != nullptr
	//	|| hit_h->CheckObjNameHit(OBJ_BOMB) != nullptr)
	//	&& hp != 0 && m_ht == 0)
	//{
	//	m_hf = true;
	//	hp -= 1;
	//}
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