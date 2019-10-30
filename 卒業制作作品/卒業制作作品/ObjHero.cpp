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

//死亡時動き停止フラグ
extern bool Dead_flg;

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

	//上下左右別当たり判定確認フラグ
	m_UpHit_flg = false;    //上
	m_DownHit_flg = false;	 //下
	m_LeftHit_flg = false;	 //左
	m_LightHit_flg = false; //右

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
	m_sg_pb = 8;//ショットガン現在弾数用(上部表示用)
	m_ar_pb = 30;//アサルトライフル現在弾数用(上部表示用)
	m_sr_pb = 5;//スナイパーライフル現在弾数用(上部表示用)
	m_rl_pb = 1;//ロケットランチャー現在弾数用(上部表示用)
	m_rg_pb = 1;//レールガン現在弾数用(上部表示用)

	//所持弾数(計算用)
	m_sg_pb_c = 8;//ショットガン現在弾数用
	m_ar_pb_c = 30;//アサルトライフル現在弾数用
	m_sr_pb_c = 5;//スナイパーライフル現在弾数用
	m_rl_pb_c = 1;//ロケットランチャー現在弾数用
	m_rg_pb_c = 1;//レールガン現在弾数用

	m_sg_pb_cc = 0;//ショットガン現在弾数用
	m_ar_pb_cc = 0;//アサルトライフル現在弾数用
	m_sr_pb_cc = 0;//スナイパーライフル現在弾数用
	m_rl_pb_cc = 0;//ロケットランチャー現在弾数用
	m_rg_pb_cc = 0;//レールガン現在弾数用

	//メニュー表示用
	m_sg_pb_me = 80;//ショットガン
	m_ar_pb_me = 300;//アサルトライフル
	m_sr_pb_me = 50;//スナイパーライフル
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


	//------------------------------------------
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

	//血しぶき表示停止フラグ
	m_blood_flg = false;

	m_del = false; //削除チェック用

	m_speed_power = 0.5f;//通常速度

	m_inputf = true;	// true = 入力可	false = 入力不可

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 8);
}

//アクション
void CObjHero::Action()
{
	//HPが0以下の時にゲームオーバーに移行する
	if (m_del == false && m_hero_hp <= 0)
	{
		m_del = true;
		m_inputf = false;	//キー入力を制御
		m_time_dead = 20;	//死亡時間をセット
	}

	m_speed_power = 0.5f;

	//inputフラグがオンの場合入力を可能にする
	if (m_inputf == true)
	{
		//Eキーを押すとメニューを開く
		if (m_key_flag_menu == true)
		{
			if (Input::GetVKey('E') == true)
			{
				Menu_flg = true;
				m_key_flag_menu = false;
				//メニューオブジェクト作成
				CObjMenu* obj_m = new CObjMenu();
				Objs::InsertObj(obj_m, OBJ_MENU, 20);
			}
		}
	}

	//主人公位置固定
	m_x = 350.0f;
	m_y = 280.0f;

	//移動停止
	m_vx = 0.0f;
	m_vy = 0.0f;

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		if (Dead_flg == false)
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
				if (m_LightHit_flg == false)
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

			//HitBoxの内容を更新
			CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得
			hit_h->SetPos(m_x, m_y); //当たり判定の位置更新

			//設置物オブジェクト情報作成
			CObjGenerator* Gen = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
			float GenX = Gen->GetGenX();
			float GenY = Gen->GetGenY();

			//上下左右別当たり判定確認フラグ常時初期化
			m_UpHit_flg = false;    //上
			m_DownHit_flg = false;	 //下
			m_LeftHit_flg = false;	 //左
			m_LightHit_flg = false; //右

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_FIELD) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_FIELD);


				float r = hit_data[0]->r;

				//角度で上下左右を判定
				if (r > 0 && r < 45 || r >= 315)
				{
					m_LightHit_flg = true; //右
				}
				else if (r >= 45 && r < 136)
				{
					m_UpHit_flg = true;    //上
				}
				else if (r >= 135 && r <= 225)
				{
					m_LeftHit_flg = true;	 //左
				}
				else if (r > 225 && r < 316)
				{
					m_DownHit_flg = true;	 //下
				}

				if (hit_h->CheckObjNameHit(OBJ_APPARATUS) != nullptr)
				{
					if (m_LeftHit_flg == true)//左に当たり判定があった場合
					{
						m_x = GenX + 100;
					}
					else if (m_LightHit_flg == true)//右に当たり判定があった場合
					{
						m_x = GenX - m_dst_size;
					}
					else if (m_DownHit_flg == true)//下に当たり判定があった場合
					{
						m_y = GenY - m_dst_size;
					}
					else if (m_UpHit_flg == true)//上に当たり判定があった場合
					{
						m_y = GenY + 40;
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
					}
				}
				else if (m_Weapon_switching > 0)
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
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
					}
					//右
					else if (m_UDani_frame == 2)
					{
						//グレネードオブジェクト作成
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 32, m_y + 30, m_ga_vx_max, 0);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
					}
					//下
					else if (m_UDani_frame == 4)
					{
						//グレネードオブジェクト作成
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y + 32, 0, m_ga_vy_max);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
					}
					//左
					else if (m_UDani_frame == 6)
					{
						//グレネードオブジェクト作成
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x, m_y + 30, -m_ga_vx_max, 0);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
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

			//下キーを押すと弾をリロード
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//ハンドガン
				if (m_Weapon_switching == 0 && m_hg_pb >= 0)
				{
					m_hg_pb = 10;//弾数を10増やす
					/*if (m_hg_pb == 10)
						m_hg_pb = 10;*/
				}
				//ショットガン
				else if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
				{
					if (m_sg_flg == true)
					{
						//  8        10         2
						m_sg_pb_cc = m_sg_pb_c - m_sg_pb;//使った弾数分を全体の弾数から引く
						//  52       60         8
						m_sg_pb_me = m_sg_pb_me - m_sg_pb_cc;
						m_sg_pb = m_sg_pb + m_sg_pb_cc;
						m_sg_flg = false;
					}
				}
				//アサルト
				else if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
				{
					if (m_ar_flg == true)
					{
						//  8        10         2
						m_ar_pb_cc = m_ar_pb_c - m_ar_pb;//使った弾数分を全体の弾数から引く
						//  52       60         8
						m_ar_pb_me = m_ar_pb_me - m_ar_pb_cc;
						m_ar_pb = m_ar_pb + m_ar_pb_cc;
						m_ar_flg = false;
					}
				}
				//スナイパー
				else if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
				{
					if (m_sr_flg == true)
					{
						//  8        10         2
						m_sr_pb_cc = m_sr_pb_c - m_sr_pb;//使った弾数分を全体の弾数から引く
						//  52       60         8
						m_sr_pb_me = m_sr_pb_me - m_sr_pb_cc;
						m_sr_pb = m_sr_pb + m_sr_pb_cc;
						m_sr_flg = false;
					}
				}
				//ロケットランチャー
				else if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
				{
					if (m_rl_flg == true)
					{
						//  8        10         2
						m_rl_pb_cc = m_rl_pb_c - m_rl_pb;//使った弾数分を全体の弾数から引く
						//  52       60         8
						m_rl_pb_me = m_rl_pb_me - m_rl_pb_cc;
						m_rl_pb = m_rl_pb + m_rl_pb_cc;
						m_rl_flg = false;
					}
				}
				//レールガン
				else if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
				{
					if (m_rg_flg == true)
					{
						//  8        10         2
						m_rg_pb_cc = m_rg_pb_c - m_rg_pb;//使った弾数分を全体の弾数から引く
						//  52       60         8
						m_rg_pb_me = m_rg_pb_me - m_rg_pb_cc;
						m_rg_pb = m_rg_pb + m_rg_pb_cc;
						m_rg_flg = false;
					}
				}
			}
			else
			{
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


		//HitBoxの内容を更新
		CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得

		//メニューを開くと行動停止
		if (Menu_flg == false)
		{
			//当たり判定を行うオブジェクト情報群
			int data_base[3] =
			{
				ELEMENT_ENEMY,ELEMENT_MAGIC,
			};
			//オブジェクト情報群と当たり判定行い。当たっていればノックバック
			for (int i = 0; i < 3; i++)
			{
				if (hit_h->CheckElementHit(data_base[i]) == true)
				{
					HIT_DATA** hit_date;							//当たった時の細かな情報を入れるための構造体
					hit_date = hit_h->SearchElementHit(data_base[i]);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる

					float r = 0;
					for (int j = 0; j < 10; j++) {
						if (hit_date[j] != nullptr) {
							r = hit_date[j]->r;
						}
					}
					//角度で上下左右を判定
					//if ((r < 45 && r >= 0) || r > 315)
					//if (r > 90 && r < 270)
					//{
					//	m_vy = -5;		//右
					//	m_vx += 6;
					//}
					//else
					//{
					//	m_vy = -5;		//左
					//	m_vx -= 6;
					//}

					//Audio::Start(3);	//ダメージ音	
					hit_h->SetInvincibility(true);	//無敵オン

					if (hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr)
					{
						m_hero_hp -= 5;
						m_time_d = 80;		//無敵時間をセット
					}
					else if (hit_h->CheckObjNameHit(OBJ_BOSS) != nullptr)
					{
						m_hero_hp -= 2;
						m_time_d = 30;		//無敵時間をセット
					}
					else if (hit_h->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
					{
						CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
						int EXPDamage = EXPAttack->GetEXP();
						m_hero_hp -= EXPDamage;
						m_time_d = 80;		//無敵時間をセット
					}
					//敵の攻撃によってHPが0以下になった場合
					if (m_hero_hp <= 0)
						m_hero_hp = 0;	//HPを0にする					
				}
			}
		}

		if (m_hero_hp <= 0 && m_blood_flg == false)
		{
			hit_h->SetInvincibility(true);	//無敵にする
			Dead_flg = true;
			m_eff_flag = true;			//画像切り替え用フラグ
			m_speed_power = 0.0f;			//動きを止める	
			m_blood_flg = true; //血しぶき表示停止フラグ
			//血しぶきオブジェクト作成
			CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_blood_dst_size);
			Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
		}

		if (m_del == true)
		{
			hit_h->SetInvincibility(true);	//無敵にする
			m_eff_flag = true;			//画像切り替え用フラグ
			//m_speed_power = 0.0f;			//動きを止める

		}

		if (m_time_d > 0)
		{
			m_time_d--;
			if (m_time_d <= 0)
			{
				m_time_d = 0;
				hit_h->SetInvincibility(false);	//無敵オフ
			}
		}

		if (m_time_dead > 0)
		{
			m_time_dead--;
			if (m_time_dead <= 0)
			{
				Scene::SetScene(new CSceneOver());
				m_time_dead = 0;
				Dead_flg = false;
				this->SetStatus(false); //オブジェクト破棄
				Hits::DeleteHitBox(this); //主人公が所有するHitBoxを削除する
			}
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
}

//ドロー
void CObjHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

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

	if (m_time_d > 0) {
		Draw::Draw(8, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}
}