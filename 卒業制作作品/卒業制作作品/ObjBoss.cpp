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
	e_x = 272.0f;
	e_y = 400.0f;
	//ボス拡大ベクトル
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//ボス拡大ベクトル最大値
	m_bv_max = 2.0f;

	//敵生成頻度
	m_Enemy_Generation = 0;
	//ゾンビランダム描画切り替え用
	Ze_dst_flg_num = 1;
	//ゾンビランダム描画切り替え用フラグ
	Ze_dst_flg = false;

	//描画サイズ
	m_dst_size = 128.0f;
	//当たり判定サイズ
	Hitbox_size = 128;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_bx, m_by, Hitbox_size * 2, Hitbox_size, ELEMENT_ENEMY, OBJ_BOSS, 4);
}

//アクション
void CObjBoss::Action()
{
	//拡大停止
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{

		//位置更新
		m_bx += m_bvx;
		m_by += m_bvy;
		//エネミー生成処理
		m_Enemy_Generation++;

		srand(time(NULL)); // ランダム情報を初期化

		e_x = rand() % 192 + m_bx;
		e_y = rand() % 128 + m_by;

		//エネミー生成処理
		if (m_Enemy_Generation == 60)
		{
			//ゾンビの伏せている、立っている描画切り替え処理
			Ze_dst_flg_num = rand() % 3;
			if (Ze_dst_flg_num % 2 == 0)
			{
				Ze_dst_flg = true;
			}
			else if (Ze_dst_flg_num % 2 != 0)
			{
				Ze_dst_flg = false;
			}

			//敵機オブジェクト作成 272, 400)
			CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y, Ze_dst_flg);
			Objs::InsertObj(obj_ze, OBJ_ENEMY, 3);
		}
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
	Draw::Draw(4, &src, &dst, c, 0.0f);
}