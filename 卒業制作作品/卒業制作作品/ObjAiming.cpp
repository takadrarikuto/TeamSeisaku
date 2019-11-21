//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjAiming.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjAiming::Init()
{
	//初期化
	//位置情報
	m_Ax = 0.0f;
	m_Ay = 0.0f;

	//位置修正変数
	m_A_dst_num = 28.0f; 

	//描画サイズ
	m_dst_size = 64; 

	//削除距離最大値
	m_Aiming_Distance_max = 3;

}

//アクション
void CObjAiming::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	int h_ws = hero->GetWS();
	int h_af = hero->GetUDAF();

	//ハンドガン
	if (h_ws == 0)
	{
		m_Aiming_Distance_max = DISTANCE_Gun;
	}
	//ショットガン
	else if (h_ws == 1)
	{
		m_Aiming_Distance_max = DISTANCE_SHG;
	}
	//アサルトライフル
	else if (h_ws == 2)
	{
		m_Aiming_Distance_max = DISTANCE_AR;
	}
	//スナイパーライフル
	else if (h_ws == 3)
	{
		m_Aiming_Distance_max = DISTANCE_SR;
	}
	//ロケットランチャー
	else if (h_ws == 4)
	{
		m_Aiming_Distance_max = DISTANCE_RL;
	}
	//レールガン
	else if (h_ws == 5)
	{
		m_Aiming_Distance_max = DISTANCE_RG;
	}

	//主人公の移動、向きに合わせる
	if (h_af == 0)
	{
		//上
		m_Ax = hx;
		m_Ay = hy - (64 * m_Aiming_Distance_max + m_A_dst_num);
	}
	else if (h_af == 2)
	{
		//右
		m_Ax = hx + (64 * m_Aiming_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	else if (h_af == 4)
	{
		//下
		m_Ax = hx;
		m_Ay = hy + (64 * m_Aiming_Distance_max + m_A_dst_num);
	}
	else if (h_af == 6)
	{
		//左
		m_Ax = hx - (64 * m_Aiming_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
}

//ドロー
void CObjAiming::Draw()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_ws = hero->GetWS();

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	//ハンドガン
	if (h_ws == 0)
	{		
		src.m_top = 10.0f;
		src.m_left = 435.0f;
		src.m_right = 505.0f;
		src.m_bottom = 90.0f;
	}
	//ショットガン
	else if (h_ws == 1)
	{
		src.m_top = 10.0f;
		src.m_left = 350.0f;
		src.m_right = 425.0f;
		src.m_bottom = 90.0f;
	}
	//アサルトライフル
	else if (h_ws == 2)
	{
		src.m_top = 10.0f;
		src.m_left = 190.0f;
		src.m_right = 265.0f;
		src.m_bottom = 90.0f;
	}
	//スナイパーライフル
	else if (h_ws == 3)
	{
		src.m_top = 10.0f;
		src.m_left = 270.0f;
		src.m_right = 350.0f;
		src.m_bottom = 90.0f;
	}
	//ロケットランチャー
	else if (h_ws == 4)
	{
		src.m_top = 100.0f;
		src.m_left = 30.0f;
		src.m_right = 100.0f;
		src.m_bottom = 165.0f;
	}
	//レールガン
	else if (h_ws == 5)
	{		
		src.m_top = 10.0f;
		src.m_left = 30.0f;
		src.m_right = 100.0f;
		src.m_bottom = 90.0f;
	}

	//描画処理
	dst.m_top = 0.0f + m_Ay;
	dst.m_left = 0.0f + m_Ax;
	dst.m_right = m_dst_size + m_Ax;
	dst.m_bottom = m_dst_size + m_Ay;
	Draw::Draw(12, &src, &dst, c, 0.0f);
}