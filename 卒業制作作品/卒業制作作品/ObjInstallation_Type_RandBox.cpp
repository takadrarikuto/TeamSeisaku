//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include <time.h>

#include "GameHead.h"
#include "ObjInstallation_Type_RandBox.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjInstallation_Type_RandBox::CObjInstallation_Type_RandBox(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_IT_Rand_Box_x = x;
	m_IT_Rand_Box_y = y;

}

//イニシャライズ
void CObjInstallation_Type_RandBox::Init()
{
	//初期化
	m_IT_Rand_Box_vx = 0.0f; //位置更新
	m_IT_Rand_Box_vy = 0.0f;

	//HitBoxサイズ
	m_HitSize_x = 33;
	m_HitSize_y = 32;

	//補充フラグ
	m_Replenishment_flg = false;
	//再補充タイム
	m_Replenishment_time = 0;
	//アイテムランダム選択変数 
	m_Rand_aitem_num = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_IT_Rand_Box_x, m_IT_Rand_Box_y, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_RANDBOX, 6);

}

//アクション
void CObjInstallation_Type_RandBox::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_IT_Rand_Box_x, m_IT_Rand_Box_y); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			/*m_Rand_aitem_num = rand() % 100;*/
			m_Rand_aitem_num = 1;

			//補充フラグ
			m_Replenishment_flg = true;
			//再補充タイム
			m_Replenishment_time = 600;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	if (m_Rand_aitem_num > 0)
	{
		if (m_Rand_aitem_num == 1)
		{
			aitemfont->SetAGF(7);
			aitemfont->SetAitemNum(100);
			hero->SetHP(100); //体力
		}
		else if (m_Rand_aitem_num == 2)
		{
			aitemfont->SetAGF(8);
			aitemfont->SetAitemNum(150);
			hero->SetEN(150); //アーマー
		}
		else if (m_Rand_aitem_num == 3)
		{
			aitemfont->SetAGF(4);
			aitemfont->SetAitemNum(2);
			hero->SetRL(2);	//ロケットランチャー弾
		}
		else if (m_Rand_aitem_num == 4)
		{
			aitemfont->SetAGF(5);
			aitemfont->SetAitemNum(1);
			hero->SetRG(1);	//レールガン弾
		}
		else if (m_Rand_aitem_num == 5)
		{
			aitemfont->SetAGF(6);
			aitemfont->SetAitemNum(3);
			hero->SetGRE(3); //グレネード
		}
		m_Rand_aitem_num = 0;
		/*srand(time(NULL)); // ランダム情報を初期化*/
	}
	

	//主人公の移動に合わせる
	m_IT_Rand_Box_x -= hvx;
	m_IT_Rand_Box_y -= hvy;

	//再補充タイム
	if (m_Replenishment_time > 0)
	{
		m_Replenishment_time--;
	}
}

//ドロー
void CObjInstallation_Type_RandBox::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 300.0f;
	src.m_left = 432.0f;
	src.m_right = 465.0f;
	src.m_bottom = 332.0f;

	//描画処理
	dst.m_top = 0.0f + m_IT_Rand_Box_y;
	dst.m_left = 0.0f + m_IT_Rand_Box_x;
	dst.m_right = 33.0f + m_IT_Rand_Box_x;
	dst.m_bottom = 32.0f + m_IT_Rand_Box_y;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}