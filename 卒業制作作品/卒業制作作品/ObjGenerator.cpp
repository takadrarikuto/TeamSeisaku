//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGenerator::CObjGenerator(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_Genx = x;
	m_Geny = y;
	
}

//イニシャライズ
void CObjGenerator::Init()
{
	//初期化
	//発電機起動フラグ
	m_Gen_flg = false; 

	//描画サイズ
	m_dst_size = 100.0f; 
	//当たり判定サイズ
	Hitbox_size = 100; 

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_Genx, m_Geny, Hitbox_size, Hitbox_size, ELEMENT_FIELD, OBJ_APPARATUS, 7);

}

//アクション
void CObjGenerator::Action()
{
	//主人公位置取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	if ((hx < m_Genx + 100.0f) && (hx + 64.0f > m_Genx) && (hy < m_Geny + 100.0f) && (hy + 64.0f > m_Geny))
	{
		//上下左右判定
		float vx = hx - m_Genx;
		float vy = hy - m_Geny;

		//斜めの長さを求める
		float len = (vx*vx + vy*vy);

		//角度を求める
		float r = atan2(vy, vx);
		r = r * 180 / 3.14f;

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//角度で判定を行う
		//右
		if ((r < 45 & r>0) || r > 315)
		{
			hero->SetX(m_Genx + 100); 	
			hero->SetVX(-hero->GetVX()*0.1f);
		}
		//上
		else if (r > 45 || r < 135)
		{
			hero->SetY(m_Geny - 64.0f);	
			hero->SetVY(-hero->GetVY()*0.1f);
		}
		//左
		else if (r > 135 || r < 225)
		{
			hero->SetX(m_Genx - 64.0f); 
			hero->SetVX(-hero->GetVX()*0.1f);
		}
		//下
		else if (r > 225 || r < 315)
		{
			hero->SetY(m_Geny + 100);	
			hero->SetVY(-hero->GetVY()*0.1f);
		}
	}
	//主人公の移動に合わせる
	m_Genx -= hvx;
	m_Geny -= hvy;
	
			

	//HitBoxの内容を更新 
	CHitBox* hit_exp = Hits::GetHitBox(this); //当たり判定情報取得 
	hit_exp->SetPos(m_Genx, m_Geny); //当たり判定の位置更新

}

//ドロー
void CObjGenerator::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画処理
	dst.m_top = 0.0f + m_Geny;
	dst.m_left = 0.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	Draw::Draw(7, &src, &dst, c, 0.0f);



}