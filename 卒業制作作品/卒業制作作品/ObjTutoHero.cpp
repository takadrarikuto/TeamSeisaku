//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjTutoHero::CObjTutoHero(float x, float y)
{
	//位置情報登録(数値=位置調整)
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjTutoHero::Init()
{
	//初期化
	//位置把握
	m_px = m_x;
	m_py = m_y;
	//移動ベクトル
	m_vx = 0.0f;
	m_vy = 0.0f;

	//体力
	m_hero_hp = 200;

	//耐久力
	m_hero_en = 0;

	//移動ベクトル最大値
	m_v_max = 3.0f;
	//武器攻撃移動ベクトル最大値
	m_ga_vx_max = 5.0f;
	m_ga_vy_max = 5.0f;

	//足跡生成タイム
	m_Footprint_time = 10;
	//足跡生成フラグ
	m_Footprint_flg = false;

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_RightHit_flg = false; //右

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
	//グレネード投下処理
	m_Grenade_flg = false;

	//所持弾数(装備分)
	m_hg_pb = 10;//ハンドガン現在弾数用(上部表示用)
	m_sg_pb = 6;//ショットガン現在弾数用(上部表示用)//30
	m_ar_pb = 20;//アサルトライフル現在弾数用(上部表示用)//30
	m_sr_pb = 5;//スナイパーライフル現在弾数用(上部表示用)//5
	m_rl_pb = 1;//ロケットランチャー現在弾数用(上部表示用)
	m_rg_pb = 1;//レールガン現在弾数用(上部表示用)
	//所持弾数(計算用)
	m_sg_pb_c = 6;//ショットガン現在弾数用
	m_ar_pb_c = 20;//アサルトライフル現在弾数用
	m_sr_pb_c = 5;//スナイパーライフル現在弾数用
	m_rl_pb_c = 1;//ロケットランチャー現在弾数用
	m_rg_pb_c = 1;//レールガン現在弾数用

	m_sg_pb_cc = 0;//ショットガン現在弾数用
	m_ar_pb_cc = 0;//アサルトライフル現在弾数用
	m_sr_pb_cc = 0;//スナイパーライフル現在弾数用
	m_rl_pb_cc = 0;//ロケットランチャー現在弾数用
	m_rg_pb_cc = 0;//レールガン現在弾数用

	//メニュー表示用
	m_sg_pb_me = 60;//ショットガン
	m_ar_pb_me = 200;//アサルトライフル
	m_sr_pb_me = 30;//スナイパーライフル
	m_rl_pb_me = 2;//ロケットランチャー
	m_rg_pb_me = 1;//レールガン
	m_gre_pb_me = 3;//グレネード

	//リロード用
	m_sg_pb_r = 0;//ショットガン
	m_ar_pb_r = 0;//アサルトライフル
	m_sr_pb_r = 0;//スナイパーライフル
	m_rl_pb_r = 0;//ロケットランチャー
	m_rg_pb_r = 0;//レールガン
	m_gre_pb_r = 0;//グレネード

	//------------------------------------------(未使用)
	//最大所持弾数
	m_sg_pb_num = 80; //ショットガン(70)
	m_ar_pb_num = 300;//アサルトライフル(300)
	m_sr_pb_num = 50;//スナイパーライフル(50)
	m_rl_pb_num = 2;//ロケットランチャー(2)
	m_rg_pb_num = 1;//レールガン(1)
	m_gre_pb_num = 3;//グレネード(3)
	//------------------------------------------

	//描画サイズ
	m_dst_size = 64.0f;
	//当たり判定サイズ
	Hitbox_size = 64;
	//爆発用描画サイズ
	m_exp_blood_dst_size = 64;

	m_speed_power = 0.5f;//通常速度

	//無敵時間
	m_time_d = 0;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_TUTO_HERO, 8);
}

//アクション
void CObjTutoHero::Action()
{
	//チュートリアル情報取得
	CObjTutorial* Tuto = (CObjTutorial*)Objs::GetObj(OBJ_TUTORIAL);
	bool Tuto_flg = Tuto->GetTuto_flg();

	m_speed_power = 0.5f;

	//位置固定
	m_x = 368.0f;
	m_y = 268.0f;
	//移動停止
	m_vx = 0.0f;
	m_vy = 0.0f;

	if (Tuto_flg == true)
	{
		//移動処理
		//当たり判定にあたっていない時に移動できる
		//'W'を押すと上に移動
		if (Input::GetVKey('W') == true)
		{
			if (m_UpHit_flg == false)
			{
				m_vy -= m_v_max;
			}
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//'S'を押すと下に移動
		else if (Input::GetVKey('S') == true)
		{
			if (m_DownHit_flg == false)
			{
				m_vy += m_v_max;
			}
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//'A'を押すと左に移動
		else if (Input::GetVKey('A') == true)
		{
			if (m_LeftHit_flg == false)
			{
				m_vx -= m_v_max;
			}
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//'D'を押すと右移動
		else if (Input::GetVKey('D') == true)
		{
			if (m_RightHit_flg == false)
			{
				m_vx += m_v_max;
			}
			m_UDani_frame = 2;
			m_ani_time += 1;
		}
		else
		{
			m_ani_time = 0.0f;
			m_LRani_frame = 0;
		}
	}
	else
	{
		//位置固定
		m_x = 368.0f;
		m_y = 268.0f;
		//移動停止
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	//足跡生成処理
	if (m_Footprint_flg == true)
	{
		m_Footprint_time--; //足跡生成タイム減少
							//足跡生成タイムが0以下になると足跡生成
		if (m_Footprint_time <= 0)
		{
			//上下を向いていると縦向き
			if (m_UDani_frame == 0 || m_UDani_frame == 4)
			{
				CObjFootprint* Foot = new CObjFootprint(m_x + 20, m_y + 20, 0.0f);
				Objs::InsertObj(Foot, OBJ_FOOTPRINT, 2);
			}
			//左右を向いていると横向き
			else if (m_UDani_frame == 6 || m_UDani_frame == 2)
			{
				CObjFootprint* Foot = new CObjFootprint(m_x + 20, m_y + 20, 90.0f);
				Objs::InsertObj(Foot, OBJ_FOOTPRINT, 2);
			}

			m_Footprint_time = 10; //足跡生成タイム初期化
		}
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

	//位置情報更新
	m_px += m_vx;
	m_py += m_vy;

	//HitBoxの内容を更新
	CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得
	hit_h->SetPos(m_x, m_y); //当たり判定の位置更新

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_h->CheckElementHit(ELEMENT_WALL) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_h->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_h->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_vx = -0.15f; //右
				}
				if (r > 88 && r < 92)
				{
					m_vy = 0.15f;//上
				}
				if (r > 92 && r < 268)
				{
					m_vx = 0.15f;//左
				}
				if (r > 268 && r < 292)
				{
					m_vy = -0.15f; //下
				}
			}
		}
	}

	//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
	if (hit_h->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//主人公と障害物がどの角度で当たっているか調べる
		HIT_DATA** hit_data;
		hit_data = hit_h->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_h->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//角度で上下左右を判定
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_vx = -0.15f; //右
				}
				if (r > 2 && r < 178)
				{
					m_vy = 0.15f;//上
				}
				if (r > 178 && r < 182)
				{
					m_vx = 0.15f;//左
				}
				if (r > 182 && r < 358)
				{
					m_vy = -0.15f; //下
				}
			}
		}
	}

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
				Audio::Start(1);
			}
		}
		else if (m_Weapon_switching > 0)
		{
			if (m_Weapon_switching_flg == true)
			{
				m_Weapon_switching -= 1;
				m_Weapon_switching_flg = false;
				m_bt = 0; //攻撃頻度初期化
				Audio::Start(1);
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
				Audio::Start(1);
			}
		}
		else if (m_Weapon_switching < 5)
		{
			if (m_Weapon_switching_flg == true)
			{
				m_Weapon_switching += 1;
				m_Weapon_switching_flg = false;
				m_bt = 0; //攻撃頻度初期化
				Audio::Start(1);
			}
		}
	}
	else
	{
		m_Weapon_switching_flg = true;
	}

	//攻撃処理
	//グレネード
	if (Input::GetVKey('Q') == true)
	{
		if (m_Grenade_flg == true && m_gre_pb_me > 0)
		{
			m_gre_pb_me -= 1;//弾数を1減らす
								//上
			if (m_UDani_frame == 0)
			{
				//グレネードオブジェクト作成
				CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y - 10, 0, -m_ga_vy_max);
				Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
			}
			//右
			else if (m_UDani_frame == 2)
			{
				//グレネードオブジェクト作成
				CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 32, m_y + 30, m_ga_vx_max, 0);
				Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
			}
			//下
			else if (m_UDani_frame == 4)
			{
				//グレネードオブジェクト作成
				CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y + 32, 0, m_ga_vy_max);
				Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
			}
			//左
			else if (m_UDani_frame == 6)
			{
				//グレネードオブジェクト作成
				CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x, m_y + 30, -m_ga_vx_max, 0);
				Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
			}
			m_Grenade_flg = false;
		}
	}
	else
	{
		m_Grenade_flg = true;
	}
	//上キーを押すと弾を発射
	if (Input::GetVKey(VK_UP) == true)
	{
		m_bt += 1;
		//ハンドガン
		if (m_Weapon_switching == 0 && m_hg_pb > 0)
		{
			m_bt_max = 30;
			if (m_bt == 1)
			{
				m_hg_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//ハンドガンアタックオブジェクト作成
					CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
					Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//ハンドガンアタックオブジェクト作成
					CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
					Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//ハンドガンアタックオブジェクト作成
					CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
					Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//ハンドガンアタックオブジェクト作成
					CObjGunAttack* obj_ga = new CObjGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
					Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
				}
				Audio::Start(3);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//ショットガン
		else if (m_Weapon_switching == 1 && m_sg_pb > 0)
		{
			m_bt_max = 60;
			float i = 0.0f;
			if (m_bt == 1)
			{
				m_sg_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//ショットガンアタックオブジェクト作成
					CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, -m_ga_vx_max / 3, -m_ga_vy_max, 150.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 180.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, m_ga_vx_max / 3, -m_ga_vy_max, 210.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//ショットガンアタックオブジェクト作成
					CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, -m_ga_vy_max / 3, 60.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, m_ga_vy_max / 3, 120.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//ショットガンアタックオブジェクト作成
					CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, -m_ga_vx_max / 3, m_ga_vy_max, -30.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 0.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, m_ga_vx_max / 3, m_ga_vy_max, 30.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//ショットガンアタックオブジェクト作成
					CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, m_ga_vy_max / 3, 240.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
					obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, -m_ga_vy_max / 3, 300.0f);
					Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
				}
				Audio::Start(4);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//アサルト
		else if (m_Weapon_switching == 2 && m_ar_pb > 0)
		{
			m_bt_max = 20;
			if (m_bt == 1)
			{
				m_ar_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//アサルトアタックオブジェクト作成
					CObjARAttack* obj_ara = new CObjARAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
					Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//アサルトアタックオブジェクト作成
					CObjARAttack* obj_ara = new CObjARAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
					Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//アサルトアタックオブジェクト作成
					CObjARAttack* obj_ara = new CObjARAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
					Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//アサルトアタックオブジェクト作成
					CObjARAttack* obj_ara = new CObjARAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
					Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
				}
				Audio::Start(3);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//スナイパー
		else if (m_Weapon_switching == 3 && m_sr_pb > 0)
		{
			m_bt_max = 120;
			if (m_bt == 1)
			{
				m_sr_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//スナイパーアタックオブジェクト作成
					CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max * 2, 0.0f);
					Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//スナイパーアタックオブジェクト作成
					CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 50, m_y + 20, m_ga_vx_max * 2, 0, 270.0f);
					Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//スナイパーアタックオブジェクト作成
					CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max * 2, 180.0f);
					Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//スナイパーアタックオブジェクト作成
					CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x - 10, m_y + 20, -m_ga_vx_max * 2, 0, 90.0f);
					Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
				}
				Audio::Start(5);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//ロケットランチャー
		else if (m_Weapon_switching == 4 && m_rl_pb > 0)
		{
			m_bt_max = 150;
			if (m_bt == 1)
			{
				m_rl_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//ロケットランチャーアタックオブジェクト作成
					CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, -m_ga_vy_max, 0.0f);
					Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//ロケットランチャーアタックオブジェクト作成
					CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, m_ga_vx_max, 0, 270.0f);
					Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//ロケットランチャーアタックオブジェクト作成
					CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, m_ga_vy_max, 180.0f);
					Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//ロケットランチャーアタックオブジェクト作成
					CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, -m_ga_vx_max, 0, 90.0f);
					Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
				}
				Audio::Start(6);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//レールガン
		else if (m_Weapon_switching == 5 && m_rg_pb > 0)
		{
			m_bt_max = 150;
			if (m_bt == 1)
			{
				m_rg_pb -= 1;//弾数を1減らす
				//上
				if (m_UDani_frame == 0)
				{
					//レールガンアタックオブジェクト作成
					CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max * 2, 0.0f);
					Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
				}
				//右
				else if (m_UDani_frame == 2)
				{
					//レールガンアタックオブジェクト作成
					CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 50, m_y + 20, m_ga_vx_max * 2, 0, 270.0f);
					Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
				}
				//下
				else if (m_UDani_frame == 4)
				{
					//レールガンアタックオブジェクト作成
					CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max * 2, 180.0f);
					Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
				}
				//左
				else if (m_UDani_frame == 6)
				{
					//レールガンアタックオブジェクト作成
					CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x - 10, m_y + 20, -m_ga_vx_max * 2, 0, 90.0f);
					Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
				}
				Audio::Start(7);
			}
			//攻撃間隔
			else if (m_bt == m_bt_max)
			{
				m_bt = 0;
			}
		}
		//弾切れの時に弾切れ効果音を鳴らす
		if (m_bt == 1)
		{
			if (m_Weapon_switching == 0 && m_hg_pb <= 0)
			{
				Audio::Start(10);
			}
			if (m_Weapon_switching == 1 && m_sg_pb <= 0)
			{
				Audio::Start(10);
			}
			if (m_Weapon_switching == 2 && m_ar_pb <= 0)
			{
				Audio::Start(10);
			}
			if (m_Weapon_switching == 3 && m_sr_pb <= 0)
			{
				Audio::Start(10);
			}
			if (m_Weapon_switching == 4 && m_rl_pb <= 0)
			{
				Audio::Start(10);
			}
			if (m_Weapon_switching == 5 && m_rg_pb <= 0)
			{
				Audio::Start(10);
			}
		}
	}
	else
	{
		m_bt = 0;
	}

	//下キーを押すと弾をリロード
	if (Input::GetVKey(VK_DOWN) == true)
	{
		//ハンドガン
		if (m_Weapon_switching == 0 && m_hg_pb >= 0)
		{
			if (m_hg_flg == true)
			{
				m_hg_pb = 10;//弾数を10増やす
				Audio::Start(13);
				m_hg_flg = false;
			}
		}
			
		//ショットガン
		else if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
		{
			if (m_sg_flg == true)
			{
				//【計算1】
				//打った数 = 初期弾数(リロード分) - 現在残り弾数(リロード分)
				m_sg_pb_cc = m_sg_pb_c - m_sg_pb;

				//全体初期弾数が打った数より大きいと計算2へ
				if (m_sg_pb_me > m_sg_pb_cc)
				{
					//【計算2】
					//計算後 = 全体初期弾数 - 打った数
					m_sg_pb_me = m_sg_pb_me - m_sg_pb_cc;
				}
				//全体初期弾数が打った数より小さいと計算3へ
				else if (m_sg_pb_me <= m_sg_pb_cc)
				{
					//【計算3】								
					m_sg_pb_cc = m_sg_pb_me; //打った数と全体初期弾数を合わせる							
					m_sg_pb_me = 0; //全体初期弾数を0にする
				}

				//計算後 = 現在残り弾数 + 打った数
				m_sg_pb = m_sg_pb + m_sg_pb_cc;
				Audio::Start(13);
				m_sg_flg = false;
			}
		}
			
		//アサルト
		else if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
		{
			if (m_ar_flg == true)
			{
				//【計算1】
				//打った数 = 初期弾数(リロード分) - 現在残り弾数(リロード分)
				m_ar_pb_cc = m_ar_pb_c - m_ar_pb;

				//全体初期弾数が打った数より大きいと計算2へ
				if (m_ar_pb_me > m_ar_pb_cc)
				{
					//【計算2】
					//計算後 = 全体初期弾数 - 打った数
					m_ar_pb_me = m_ar_pb_me - m_ar_pb_cc;
				}
				//全体初期弾数が打った数より小さいと計算3へ
				else if (m_ar_pb_me <= m_ar_pb_cc)
				{
					//【計算3】								
					m_ar_pb_cc = m_ar_pb_me; //打った数と全体初期弾数を合わせる							
					m_ar_pb_me = 0; //全体初期弾数を0にする
				}

				//計算後 = 現在残り弾数 + 打った数
				m_ar_pb = m_ar_pb + m_ar_pb_cc;
				Audio::Start(13);
				m_ar_flg = false;
			}
		}
			
		//スナイパー
		else if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
		{
			if (m_sr_flg == true)
			{
				//【計算1】
				//打った数 = 初期弾数(リロード分) - 現在残り弾数(リロード分)
				m_sr_pb_cc = m_sr_pb_c - m_sr_pb;

				//全体初期弾数が打った数より大きいと計算2へ
				if (m_sr_pb_me > m_sr_pb_cc)
				{
					//【計算2】
					//計算後 = 全体初期弾数 - 打った数
					m_sr_pb_me = m_sr_pb_me - m_sr_pb_cc;
				}
				//全体初期弾数が打った数より小さいと計算3へ
				else if (m_sr_pb_me <= m_sr_pb_cc)
				{
					//【計算3】								
					m_sr_pb_cc = m_sr_pb_me; //打った数と全体初期弾数を合わせる
					m_sr_pb_me = 0; //全体初期弾数を0にする
				}

				//計算後 = 現在残り弾数 + 打った数
				m_sr_pb = m_sr_pb + m_sr_pb_cc;
				Audio::Start(13);
				m_sr_flg = false;
			}
		}
			
		//ロケットランチャー
		else if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
		{
			if (m_rl_flg == true)
			{
				//【計算1】
				//打った数 = 初期弾数(リロード分) - 現在残り弾数(リロード分)
				m_rl_pb_cc = m_rl_pb_c - m_rl_pb;

				//【計算2】
				//全体初期弾数が打った数より大きいと計算2へ
				if (m_rl_pb_me > m_rl_pb_cc)
				{
					//【計算2】
					//計算後 = 全体初期弾数 - 打った数
					m_rl_pb_me = m_rl_pb_me - m_rl_pb_cc;
				}
				else if (m_rl_pb_me <= m_sr_pb_cc)
				{
					//【計算3】							
					m_rl_pb_cc = m_rl_pb_me; //打った数と全体初期弾数を合わせる
					m_rl_pb_me = 0; //全体初期弾数を0にする
				}

				//計算後 = 現在残り弾数 + 打った数
				m_rl_pb = m_rl_pb + m_rl_pb_cc;
				Audio::Start(13);
				m_rl_flg = false;
			}
		}
			
		//レールガン
		else if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
		{
			if (m_rg_flg == true)
			{
				//【計算1】
				//打った数 = 初期弾数(リロード分) - 現在残り弾数(リロード分)
				m_rg_pb_cc = m_rg_pb_c - m_rg_pb;

				//全体初期弾数が打った数より大きいと計算2へ
				if (m_rg_pb_me > m_ar_pb_cc)
				{
					//【計算2】
					//計算後 = 全体初期弾数 - 打った数
					m_rg_pb_me = m_rg_pb_me - m_rg_pb_cc;
				}
				//全体初期弾数が打った数より小さいと計算3へ
				else if (m_rg_pb_me <= m_rg_pb_cc)
				{
					//【計算3】								
					m_rg_pb_cc = m_rg_pb_me; //打った数と全体初期弾数を合わせる							
					m_rg_pb_me = 0; //全体初期弾数を0にする
				}
				//計算後 = 現在残り弾数 + 打った数
				m_rg_pb = m_rg_pb + m_rg_pb_cc;
				Audio::Start(13);
				m_rg_flg = false;
			}
		}
	}
	else
	{
		m_hg_flg = true;
		m_sg_flg = true;
		m_ar_flg = true;
		m_sr_flg = true;
		m_rl_flg = true;
		m_rg_flg = true;
		m_sg_pb_cc = 0;
		m_ar_pb_cc = 0;
		m_sr_pb_cc = 0;
		m_rl_pb_cc = 0;
		m_rg_pb_cc = 0;
	}
	
}

//ドロー
void CObjTutoHero::Draw()
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

	Draw::Draw(8, &src, &dst, c, 0.0f);
	
}