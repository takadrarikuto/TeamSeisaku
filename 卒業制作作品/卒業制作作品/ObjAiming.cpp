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
	m_Distance_max = 0;
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
	//武器飛距離情報取得
	CObjGunAttack* Gun = (CObjGunAttack*)Objs::GetObj(OBJ_GUNATTACK);
	int Distance_Gun = Gun->GetGunDistance();
	CObjShotGunAttack* ShotGun = (CObjShotGunAttack*)Objs::GetObj(OBJ_SHOTGUNATTACK);
	int Distance_ShG = ShotGun->GetShotGunDistance();
	CObjARAttack* AR = (CObjARAttack*)Objs::GetObj(OBJ_ARATTACK);
	int Distance_AR = AR->GetARDistance();
	CObjSniperRifleAttack*SniperRifle = (CObjSniperRifleAttack*)Objs::GetObj(OBJ_SNIPERRIFLEATTACK);
	int Distance_SR = SniperRifle->GetSRDistance();
	CObjRocketLauncherAttack*RocketLauncher = (CObjRocketLauncherAttack*)Objs::GetObj(OBJ_ROCKETLAUNCHERATTACK);
	int Distance_RL = RocketLauncher->GetRLDistance();
	CObjRailGunAttack*RailGun = (CObjRailGunAttack*)Objs::GetObj(OBJ_RAILGUNATTACK);
	int Distance_RG = RailGun->GetRGDistance();

	//ハンドガン
	if (h_ws == 0)
	{
		m_Distance_max = Distance_Gun;
	}
	//ショットガン
	else if (h_ws == 1)
	{
		m_Distance_max = Distance_ShG;
	}
	//アサルトライフル
	else if (h_ws == 2)
	{
		m_Distance_max = Distance_AR;
	}
	//スナイパーライフル
	else if (h_ws == 3)
	{
		m_Distance_max = Distance_SR;
	}
	//ロケットランチャー
	else if (h_ws == 4)
	{
		m_Distance_max = Distance_RL;
	}
	//レールガン
	else if (h_ws == 5)
	{
		m_Distance_max = Distance_RG;
	}

	//主人公の移動、向きに合わせる
	if (h_af == 0)
	{
		//上
		m_Ax = hx;
		m_Ay = hy - (64 * m_Distance_max + m_A_dst_num);
	}
	else if (h_af == 2)
	{
		//右
		m_Ax = hx + (64 * m_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	else if (h_af == 4)
	{
		//下
		m_Ax = hx;
		m_Ay = hy + (64 * m_Distance_max + m_A_dst_num);
	}
	else if (h_af == 6)
	{
		//左
		m_Ax = hx - (64 * m_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	
	
	
}

//ドロー
void CObjAiming::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//切り取り処理
	src.m_top = 10.0f;
	src.m_left = 435.0f;
	src.m_right = 505.0f;
	src.m_bottom = 90.0f;

	//描画処理
	dst.m_top = 0.0f + m_Ay;
	dst.m_left = 0.0f + m_Ax;
	dst.m_right = m_dst_size + m_Ax;
	dst.m_bottom = m_dst_size + m_Ay;
	Draw::Draw(12, &src, &dst, c, 0.0f);
}