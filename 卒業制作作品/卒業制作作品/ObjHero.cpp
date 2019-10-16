//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHero::CObjHero(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjHero::Init()
{
	//初期化
	//移動ベクトル
	m_vx = 0.0f;
	m_vy = 0.0f;

	//体力
	hp = 100;

	//移動ベクトル最大値
	m_v_max = 3.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 4; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//攻撃頻度
	m_bt = 0;

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_dst_size = 64;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//アクション
void CObjHero::Action()
{
	////メニューを開く
	//if (Input::GetVKey('M') == true)
	//{
	//	Menu_flg = true;
	//	//メニューオブジェクト作成
	//	CObjMenu* obj_m = new CObjMenu();
	//	Objs::InsertObj(obj_m, OBJ_MENU, 5);
	//}

	//移動停止
	m_vx = 0.0f;
	m_vy = 0.0f;

	//メニューを開くと行動停止
	//if (Menu_flg == false)
	{
		//移動処理
		//'W'を押すと上に移動
		if (Input::GetVKey('W') == true)
		{
			m_y -= m_v_max;
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//'S'を押すと下に移動
		else if (Input::GetVKey('S') == true)
		{
			m_y += m_v_max;
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//'A'を押すと左に移動
		else if (Input::GetVKey('A') == true)
		{
			m_x -= m_v_max;
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//'D'を押すと右移動
		else if (Input::GetVKey('D') == true)
		{
			m_x += m_v_max;
			m_UDani_frame = 2;
			m_ani_time += 1;
		}
		else
		{
			m_ani_time = 0.0f;
			m_LRani_frame = 0;
		}

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

		//位置更新
		m_x += m_vx;
		m_y += m_vy;

		//攻撃処理
		//スペースキーを押すと弾を発射
		//if (Input::GetVKey(VK_SPACE) == true)
		//{
		//	m_bt += 1;
		//	if (m_bt == 1)
		//	{
		//		//バレットオブジェクト作成
		//		CObjBullet* obj_b = new CObjBullet(m_x, m_y - m_dst_size, Bullet_speed);
		//		Objs::InsertObj(obj_b, OBJ_BULLET, 2);

		//		Attack_flg = true; //Attackフラグtrue
		//	}
		//	//攻撃間隔
		//	else if (m_bt == 20)
		//	{
		//		m_bt = 0;
		//	}
		//}
		//else
		//{
		//	m_bt = 0;
		//}

	}

	//画面範囲外に出ないようにする処理
	if (m_x < 0.0f)
	{
		m_x = 0.0f;
	}
	else if (m_x + m_dst_size > 800.0f)
	{
		m_x = 800.0f - m_dst_size;
	}
	else if (m_y < 0.0f)
	{
		m_y = 0.0f;
	}
	else if (m_y + m_dst_size > 600.0f)
	{
		m_y = 600.0f - m_dst_size;
	}


	//HitBoxの内容を更新
	CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得
	hit_h->SetPos(m_x, m_y); //当たり判定の位置更新

	if (hp == 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);				
	}

	////敵機・敵弾・トラップ系オブジェクトと接触したら主人公機無敵時間開始
	//if ((hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr || hit_h->CheckObjNameHit(OBJ_ENEMYBULLET) != nullptr
	//	|| hit_h->CheckObjNameHit(OBJ_BOMB) != nullptr)
	//	&& hp != 0 && m_ht == 0)
	//{
	//	m_hf = true;
	//	hp -= 1;
	//}
	////敵機オブジェクトor敵弾オブジェクトと3回接触したら主人公機削除
	//else if (hp == 0)
	//{
	//	//爆発オブジェクト作成
	//	CObjExplosion* obj_exp = new CObjExplosion(m_x - 16, m_y - 16, m_exp_dst_size);
	//	Objs::InsertObj(obj_exp, OBJ_EXPLOSION, 2);

	//	Exp_flg = true; //Explosionフラグtrue
	//	GameOver_flg = true; //ゲームオーバーフラグtrue

	//	this->SetStatus(false); //自身の削除命令を出す
	//	Hits::DeleteHitBox(this); //主人公機が所有するHitBoxを削除する		
	//}

	//HP増減処理
	//if (hit_h->CheckObjNameHit(OBJ_ITEM) != nullptr)
	//{
	//	hp += 1;
	//}
	////体力増加限界設定
	////難易度によって体力増加限界を変更
	//if (Difficult_flg == true && hp > 3)
	//{
	//	hp = 3;
	//	//ポイントを獲得
	//}
	//else if (Usually_flg == true && hp > 5)
	//{
	//	hp = 5;
	//	//ポイントを獲得
	//}
	//else if (hp > 10)
	//{
	//	hp = 10;
	//	//ポイントを獲得
	//}

}

//ドロー
void CObjHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//モーション
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 7.0f + m_UDani_frame * 16.0f;
	src.m_left = 143.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_bottom = 34.0f + m_UDani_frame * 16.0f;
	//描画処理
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = m_dst_size + m_x;
	dst.m_bottom = m_dst_size + m_y;
	Draw::Draw(2, &src, &dst, c, 0.0f);
	

}