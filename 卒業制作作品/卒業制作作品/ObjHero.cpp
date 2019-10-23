//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//メニューONOFFフラグ
extern bool Menu_flg;

//メニューキー制御用フラグ
extern bool m_key_flag_menu;

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
	m_hero_hp = 100;

	//移動ベクトル最大値
	m_v_max = 3.0f;
	//武器攻撃移動ベクトル最大値
	m_ga_vx_max = 5.0f;
	m_ga_vy_max = 5.0f;

	m_ani_time = 0; //アニメーションフレーム動作間隔
	m_UDani_frame = 4; //静止フレームを初期にする
	m_LRani_frame = 1; //静止フレームを初期にする

	//攻撃頻度
	m_bt = 0;
	//攻撃頻度最大値
	m_bt_max = 30;
	//武器切り替え
	m_Weapon_switching = 0;
	//武器切り替えフラグ
	m_Weapon_switching_flg = false; 

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//アクション
void CObjHero::Action()
{
	//メニューを開く
	if (m_key_flag_menu == true)
	{
		if (Input::GetVKey('R') == true)
		{
			Menu_flg = true;
			m_key_flag_menu = false;
			//メニューオブジェクト作成
			CObjMenu* obj_m = new CObjMenu();
			Objs::InsertObj(obj_m, OBJ_MENU, 5);
		}
	}

	//移動停止
	m_vx = 0.0f;
	m_vy = 0.0f;

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//移動処理
		//'W'を押すと上に移動
		if (Input::GetVKey('W') == true)
		{
			m_vy -= m_v_max;
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//'S'を押すと下に移動
		else if (Input::GetVKey('S') == true)
		{
			m_vy += m_v_max;
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//'A'を押すと左に移動
		else if (Input::GetVKey('A') == true)
		{
			m_vx -= m_v_max;
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//'D'を押すと右移動
		else if (Input::GetVKey('D') == true)
		{
			m_vx += m_v_max;
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

		//武器切り替え処理
		if (Input::GetVKey(VK_LEFT) == true)
		{
			if (m_Weapon_switching == 0)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching = 5;
					m_Weapon_switching_flg = false;
					m_bt = 0; //攻撃頻度初期化
				}
			}
			else if(m_Weapon_switching > 0)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching -= 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //攻撃頻度初期化
				}				
			}					
		}
		else if (Input::GetVKey(VK_RIGHT) == true)
		{
			if (m_Weapon_switching == 5)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching = 0;
					m_Weapon_switching_flg = false;
					m_bt = 0; //攻撃頻度初期化
				}
			}
			else if (m_Weapon_switching < 5)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching += 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //攻撃頻度初期化
				}
			}									
		}
		else
		{
			m_Weapon_switching_flg = true;
		}

		//攻撃処理
		//スペースキーを押すと弾を発射
		if (Input::GetVKey(VK_SPACE) == true)
		{
			m_bt += 1;
			//ハンドガン
			if (m_Weapon_switching == 0)
			{
				m_bt_max = 30;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//ハンドガンアタックオブジェクト作成
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//ハンドガンアタックオブジェクト作成
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//ハンドガンアタックオブジェクト作成
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//ハンドガンアタックオブジェクト作成
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//ショットガン
			else if (m_Weapon_switching == 1)
			{
				m_bt_max = 60;
				float i = 0.0f;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//ショットガンアタックオブジェクト作成
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, -m_ga_vx_max, -m_ga_vy_max, 150.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);	
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, m_ga_vx_max, -m_ga_vy_max, 210.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//ショットガンアタックオブジェクト作成
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, -m_ga_vy_max, 60.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, m_ga_vy_max, 120.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//ショットガンアタックオブジェクト作成
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, -m_ga_vx_max, m_ga_vy_max, -30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, m_ga_vx_max, m_ga_vy_max, 30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//ショットガンアタックオブジェクト作成
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, m_ga_vy_max, 240.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, -m_ga_vy_max, 300.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//アサルト
			else if(m_Weapon_switching == 2)
			{
				m_bt_max = 20;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//アサルトアタックオブジェクト作成
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//アサルトアタックオブジェクト作成
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//アサルトアタックオブジェクト作成
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//アサルトアタックオブジェクト作成
						CObjARAttack* obj_ara = new CObjARAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//スナイパー
			else if (m_Weapon_switching == 3)
			{
				m_bt_max = 120;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//スナイパーアタックオブジェクト作成
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//スナイパーアタックオブジェクト作成
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 50, m_y + 20, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//スナイパーアタックオブジェクト作成
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//スナイパーアタックオブジェクト作成
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x - 10, m_y + 20, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//ロケットランチャー
			else if (m_Weapon_switching == 4)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//ロケットランチャーアタックオブジェクト作成
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//ロケットランチャーアタックオブジェクト作成
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//ロケットランチャーアタックオブジェクト作成
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//ロケットランチャーアタックオブジェクト作成
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//レールガン
			else if (m_Weapon_switching == 5)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
					//上
					if (m_UDani_frame == 0)
					{
						//レールガンアタックオブジェクト作成
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//レールガンアタックオブジェクト作成
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 50, m_y + 20, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//レールガンアタックオブジェクト作成
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//レールガンアタックオブジェクト作成
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x - 10, m_y + 20, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//Attack_flg = true; //Attackフラグtrue
				}
				//攻撃間隔
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
		}
		else
		{
			m_bt = 0;
		}

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

	if (hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		m_hero_hp -= 1;
	}
	if (m_hero_hp <= 0)
	{
		//血しぶきオブジェクト作成
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);				

		this->SetStatus(false); //オブジェクト破棄
		Hits::DeleteHitBox(this); //弾が所有するHitBoxを削除する
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

	//スクロール
	C0bjBackground * b = (C0bjBackground*)Objs::GetObj(OBJ_BACKGROUND);

	//左のスクロールライン
	{
		m_x = 0;
		b->SetScrollX(b->GetScrollX());
	}
	//右のスクロールライン
	{
		m_x = 350;
		b->SetScrollX(b->GetScrollX());
	}
	//上のスクロールライン
	{
		m_y = 0;
		b->SetScrollY(b->GetScrollY());
	}
	//下のスクロールライン
	{
		m_y = 300;
		b->SetScrollY(b->GetScrollY());
	}

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
	src.m_left = 145.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_bottom = 34.0f + m_UDani_frame * 16.0f;
	//描画処理
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = m_dst_size + m_x;
	dst.m_bottom = m_dst_size + m_y;
	Draw::Draw(2, &src, &dst, c, 0.0f);
}