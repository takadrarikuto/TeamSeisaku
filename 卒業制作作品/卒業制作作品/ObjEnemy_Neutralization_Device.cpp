//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemy_Neutralization_Device.h"

//使用するネームスペース
using namespace GameL;

//死亡処理
bool m_END_death_flg = false; //死亡フラグ

//コンストラクタ
CObjEnemy_Neutralization_Device::CObjEnemy_Neutralization_Device(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Enemy_Neu_Devx = x;
	m_Enemy_Neu_Devy = y;

}

//イニシャライズ
void CObjEnemy_Neutralization_Device::Init()
{
	//初期化
	m_Enemy_Neu_Dev_HitSize_x = 55;  //HitBoxサイズ
	m_Enemy_Neu_Dev_HitSize_y = 50;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Enemy_Neu_Devx, m_Enemy_Neu_Devy, m_Enemy_Neu_Dev_HitSize_x, m_Enemy_Neu_Dev_HitSize_y, ELEMENT_FIELD2, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 6);

}

//アクション
void CObjEnemy_Neutralization_Device::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool END = time->GetENDFlg();
	bool Rep_flg = time->GetRepFlg();

	//HitBoxの内容を更新 
	CHitBox* hit_end = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_end->SetPos(m_Enemy_Neu_Devx, m_Enemy_Neu_Devy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && TStop_flg == true
			&& END == true)
		{
			TStart_flg = true;	
			m_END_death_flg = true;
			time->SetTStart(TStart_flg);
		}
	}
	else
	{
		m_END_death_flg = false;
	}

	//主人公の移動に合わせる
	m_Enemy_Neu_Devx -= hvx;
	m_Enemy_Neu_Devy -= hvy;

}

//ドロー
void CObjEnemy_Neutralization_Device::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 15.0f;
	src.m_left = 110.0f;
	src.m_right = 145.0f;
	src.m_bottom = 80.0f;

	//描画処理
	dst.m_top = 0.0f + m_Enemy_Neu_Devy;
	dst.m_left = 0.0f + m_Enemy_Neu_Devx;
	dst.m_right = 55.0f + m_Enemy_Neu_Devx;
	dst.m_bottom = 105.0f + m_Enemy_Neu_Devy;
	if (END == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}


}