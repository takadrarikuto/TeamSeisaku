//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjInstallation_Type_SR.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjInstallation_Type_SR::CObjInstallation_Type_SR(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_IT_SRx = x;
	m_IT_SRy = y;

}

//イニシャライズ
void CObjInstallation_Type_SR::Init()
{
	//初期化
	m_IT_SRvx = 0.0f; //位置更新
	m_IT_SRvy = 0.0f;

	//HitBoxサイズ
	m_HitSize_x = 34;
	m_HitSize_y = 66;

	//設置型スナイパーライフルの弾数回復量最大値
	m_IT_SR_num_max = 0; 

	//フォント表示タイム
	m_Font_time = 0;

	//補充フラグ
	m_Replenishment_flg = false;
	//再補充タイム
	m_Replenishment_time = 0;

	//再補充完了フォント表示フラグ
	m_Replenishment_Font_flg = false;
	//再補充完了フォント表示タイム
	m_Replenishment_Font_time = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_IT_SRx, m_IT_SRy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_SR, 6);

}

//アクション
void CObjInstallation_Type_SR::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//アイテムフォント情報取得
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBoxの内容を更新 
	CHitBox* hit_gen = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_gen->SetPos(m_IT_SRx, m_IT_SRy); //当たり判定の位置更新

	//主人公接触判定処理
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_Font_time = 90; //フォント表示タイム設定
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			if (((UserData*)Save::GetData())->choose == 0)
			{
				m_IT_SR_num_max = 20; //設置型スナイパーライフル弾数回復量変更
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //スナイパーライフル弾数回復	
				aitemfont->SetAitemNum(m_IT_SR_num_max); //弾数表示
			}
			else if (((UserData*)Save::GetData())->choose == 1)
			{
				m_IT_SR_num_max = 15;
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //スナイパーライフル弾数回復
				aitemfont->SetAitemNum(m_IT_SR_num_max); //弾数表示
			}
			else if (((UserData*)Save::GetData())->choose == 2)
			{
				m_IT_SR_num_max = 10;
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //スナイパーライフル弾数回復	
				aitemfont->SetAitemNum(m_IT_SR_num_max); //弾数表示
			}
			aitemfont->SetAGF(3);
			Audio::Start(12); //効果音再生
			//補充フラグ
			m_Replenishment_flg = true;
			//再補充タイム
			m_Replenishment_time = 1800;
			//再補充完了フォント表示タイム
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//主人公の移動に合わせる
	m_IT_SRx -= hvx;
	m_IT_SRy -= hvy;

	//フォント表示タイム減少処理
	//0になるまで減少
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}

	if (Menu_flg == false)
	{
		//再補充タイム
		if (m_Replenishment_time > 0)
		{
			m_Replenishment_time--;
		}
		else if (m_Replenishment_time == 0)
		{
			//再補充完了フォント表示タイム減少処理
			if (m_Replenishment_Font_time > 0)
			{
				//効果音再生
				if (m_Replenishment_Font_time == REPLENIShHMENT_FONT_TIME)
				{
					m_Replenishment_Font_flg = true; //再補充完了フォント表示
					Audio::Start(8);
				}

				m_Replenishment_Font_time--; //再補充完了フォント表示タイム減少									
			}
			else if (m_Replenishment_Font_time == 0)
			{
				//再補充完了フォント表示フラグ初期化
				m_Replenishment_Font_flg = false;
			}
		}
	}
	
}

//ドロー
void CObjInstallation_Type_SR::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];
	wchar_t str_f[256];

	//フォント表示処理
	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"スナイパーライフルの弾が再補充されました。"); //再補充フォント表示
		Font::StrDraw(str, 0, 570, 30, c);
	}
	if (m_Font_time > 0)
	{
		swprintf_s(str_f, L"エンターキーでアイテム補充"); //操作説明フォント表示
		Font::StrDraw(str_f, m_IT_SRx - 80, m_IT_SRy - 40, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 134.0f;
	src.m_left = 540.0f;
	src.m_right = 575.0f;
	src.m_bottom = 200.0f;

	//描画処理
	dst.m_top = 0.0f + m_IT_SRy;
	dst.m_left = 0.0f + m_IT_SRx;
	dst.m_right = 34.0f + m_IT_SRx;
	dst.m_bottom = 66.0f + m_IT_SRy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}