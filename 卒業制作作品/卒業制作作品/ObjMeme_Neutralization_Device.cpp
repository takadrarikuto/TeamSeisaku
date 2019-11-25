//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjMeme_Neutralization_Device.h"

//使用するネームスペース
using namespace GameL;

//死亡処理
bool m_Meme_death_flg = false; //死亡フラグ

//コンストラクタ
CObjMeme_Neutralization_Device::CObjMeme_Neutralization_Device(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Meme_Neu_Devx = x;
	m_Meme_Neu_Devy = y;

}

//イニシャライズ
void CObjMeme_Neutralization_Device::Init()
{
	//初期化
	//描画サイズ
	m_dst_size = 50.0f;
	//HitBoxサイズ
	Hitbox_size = 50;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Meme_Neu_Devx, m_Meme_Neu_Devy, Hitbox_size, Hitbox_size, ELEMENT_FIELD, OBJ_MEME_NEUTRALIZATION_DEVICE, 7);

}

//アクション
void CObjMeme_Neutralization_Device::Action()
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
	bool MND = time->GetMNDFlg();

	//HitBoxの内容を更新 
	CHitBox* hit_end = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_end->SetPos(m_Meme_Neu_Devx, m_Meme_Neu_Devy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && TStop_flg == true
			&& MND == true)
		{
			TStart_flg = true;
			m_Meme_death_flg = true;
			time->SetTStart(TStart_flg);
		}
	}
	else
	{
		m_Meme_death_flg = false;
	}

	//主人公の移動に合わせる
	m_Meme_Neu_Devx -= hvx;
	m_Meme_Neu_Devy -= hvy;

}

//ドロー
void CObjMeme_Neutralization_Device::Draw()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;
	RECT_F src_cpu;
	RECT_F dst_cpu;

	//切り取り処理
	src.m_top = 50.0f;
	src.m_left = 55.0f;
	src.m_right = 95.0f;
	src.m_bottom = 100.0f;
	//切り取り処理
	src_cpu.m_top = 50.0f;
	src_cpu.m_left = 100.0f;
	src_cpu.m_right = 140.0f;
	src_cpu.m_bottom = 90.0f;
	//描画処理
	dst.m_top = 0.0f + m_Meme_Neu_Devy;
	dst.m_left = 0.0f + m_Meme_Neu_Devx;
	dst.m_right = m_dst_size + m_Meme_Neu_Devx;
	dst.m_bottom = m_dst_size + m_Meme_Neu_Devy;
	//描画処理
	dst_cpu.m_top = 0.0f + m_Meme_Neu_Devy - 20;
	dst_cpu.m_left = 0.0f + m_Meme_Neu_Devx - 10;
	dst_cpu.m_right = (m_dst_size + 10) + m_Meme_Neu_Devx - 10;
	dst_cpu.m_bottom = (m_dst_size + 10) + m_Meme_Neu_Devy - 20;
	if (END == true)
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, c, 0.0f);
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, cD, 0.0f);
		Draw::Draw(7, &src, &dst, cD, 0.0f);
	}


}