//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

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

//HP ONOFFフラグ
extern bool Hp_flg;

//耐久力ONOFFフラグ
extern bool En_flg;

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
	//位置把握
	m_px = m_x;
	m_py = m_y;
	//移動ベクトル
	m_vx = 0.0f;
	m_vy = 0.0f;

	//体力
	m_hero_hp = 100;

	//耐久力
	m_hero_en = 0;

	//移動ベクトル最大値
	m_v_max = 4.0f;
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
	m_sg_pb = ((UserData*)Save::GetData())->SHG_Number_of_Ammunition;//ショットガン現在弾数用(上部表示用)//30
	m_ar_pb = ((UserData*)Save::GetData())->AR_Number_of_Ammunition;//アサルトライフル現在弾数用(上部表示用)//30
	m_sr_pb = ((UserData*)Save::GetData())->SR_Number_of_Ammunition;//スナイパーライフル現在弾数用(上部表示用)//5
	m_rl_pb = ((UserData*)Save::GetData())->RL_Number_of_Ammunition;//ロケットランチャー現在弾数用(上部表示用)
	m_rg_pb = ((UserData*)Save::GetData())->RG_Number_of_Ammunition;//レールガン現在弾数用(上部表示用)

	//所持弾数(計算用)
	m_sg_pb_c = ((UserData*)Save::GetData())->SHG_Number_of_Ammunition;//ショットガン現在弾数用
	m_ar_pb_c = ((UserData*)Save::GetData())->AR_Number_of_Ammunition;//アサルトライフル現在弾数用
	m_sr_pb_c = ((UserData*)Save::GetData())->SR_Number_of_Ammunition;//スナイパーライフル現在弾数用
	m_rl_pb_c = ((UserData*)Save::GetData())->RL_Number_of_Ammunition;//ロケットランチャー現在弾数用
	m_rg_pb_c = ((UserData*)Save::GetData())->RG_Number_of_Ammunition;//レールガン現在弾数用

	m_sg_pb_cc = 0;//ショットガン現在弾数用
	m_ar_pb_cc = 0;//アサルトライフル現在弾数用
	m_sr_pb_cc = 0;//スナイパーライフル現在弾数用
	m_rl_pb_cc = 0;//ロケットランチャー現在弾数用
	m_rg_pb_cc = 0;//レールガン現在弾数用

	//メニュー表示用
	m_sg_pb_me = ((UserData*)Save::GetData())->SHG_Ammunition;//ショットガン
	m_ar_pb_me = ((UserData*)Save::GetData())->AR_Ammunition;//アサルトライフル
	m_sr_pb_me = ((UserData*)Save::GetData())->SR_Ammunition;//スナイパーライフル
	m_rl_pb_me = ((UserData*)Save::GetData())->RL_Ammunition;//ロケットランチャー
	m_rg_pb_me = ((UserData*)Save::GetData())->RG_Ammunition;//レールガン
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

	//ダメージ量
	((UserData*)Save::GetData())->BarbedWireSmall_Attack;

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
				Objs::InsertObj(obj_m, OBJ_MENU, 21);
			}
		}
	}

	//位置固定
	m_x = 368.0f;
	m_y = 268.0f;
	//移動停止
	m_vx = 0.0f;
	m_vy = 0.0f;

	//イベント情報取得
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//メニューを開く、イベント情報表示中は行動停止
	if (Menu_flg == false && Eve_Ins == 0)
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
				m_Footprint_flg = true;
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
				m_Footprint_flg = true;
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
				m_Footprint_flg = true;
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
				m_Footprint_flg = true;
			}
			//止まるとアニメーション、、上下切り替えフレーム足跡作成フラグ初期化
			else
			{
				m_ani_time = 0.0f;
				m_LRani_frame = 0;
				m_Footprint_flg = false;
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

			//HitBoxの内容を更新
			CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得
			
			//上下左右別当たり判定確認フラグ常時初期化
			m_UpHit_flg = false;    //上
			m_DownHit_flg = false;	 //下
			m_LeftHit_flg = false;	 //左
			m_RightHit_flg = false; //右

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_FIELD) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_FIELD);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 30) || r >= 330)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 30 && r < 150)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 150 && r <= 210)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 210 && r < 330)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
				//----------------------------------------ここ
				//当たり判定処理
				/*if (m_LeftHit_flg == true)//左に当たり判定があった場合
				{
					//発電機
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_x = GenX + GenHitX;
					}
					//敵無力化装置
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_x = EndX + EndHitX;
					}
				}
				else if (m_RightHit_flg == true)//右に当たり判定があった場合
				{
					//発電機
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_x = GenX - m_dst_size;
					}
					//敵無力化装置
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_x = EndX - m_dst_size;
					}
				}
				else if (m_DownHit_flg == true)//下に当たり判定があった場合
				{
					//発電機
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_y = GenY - m_dst_size;
					}
					//敵無力化装置
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_y = EndY - m_dst_size;
					}
				}
				else if (m_UpHit_flg == true)//上に当たり判定があった場合
				{
					//発電機
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_y = GenY + GenHitY;
					}
					//敵無力化装置
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_y = EndY + EndHitY;
					}
				}*/
				//--------------------------------------------
			}

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_FIELD2) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_FIELD2);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 45) || r >= 315)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 45 && r < 135)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 135 && r <= 225)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 225 && r < 315)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
			}

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_MEME_ND) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_MEME_ND);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 45) || r >= 315)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 45 && r < 135)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 135 && r <= 225)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 225 && r < 315)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
			}

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
						if ((r < 89 && r >= 0) || r > 271)
						{
							m_vx = -0.65f; //右
						}
						if (r > 89 && r < 91)
						{
							m_vy = 0.65f;//上
						}
						if (r > 91 && r < 269)
						{
							m_vx = 0.65f;//左
						}
						if (r > 269 && r < 271)
						{
							m_vy = -0.65f; //下
						}
					}
				}

				/*if (r > 0 && r < 45 || r >= 315)
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

				if (hit_h->CheckObjNameHit(OBJ_WALL) != nullptr)
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
				}*/
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
							m_vx = -0.65f; //右
						}
						if (r > 2 && r < 178)
						{
							m_vy = 0.65f;//上
						}
						if (r > 178 && r < 182)
						{
							m_vx = 0.65f;//左
						}
						if (r > 182 && r < 358)
						{
							m_vy = -0.65f; //下
						}
					}
				}
			}

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_NET_V) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_NET_V);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 25) || r >= 335)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 25 && r < 155)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 155 && r <= 205)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 205 && r < 335)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
			}

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_NET_S) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_NET_S);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 65) || r >= 295)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 65 && r < 115)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 115 && r <= 245)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 245 && r < 295)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
			}

			//主人公がステージの当たり判定に当たった時の処理（全ステージ対応）
			if (hit_h->CheckElementHit(ELEMENT_BARBED_V) == true)
			{
				//主人公と障害物がどの角度で当たっているか調べる
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_BARBED_V);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//角度で上下左右を判定
						if ((r > 0 && r < 65) || r >= 295)
						{
							m_RightHit_flg = true; //右
							m_vx = -0.65f;
						}
						else if (r >= 65 && r < 115)
						{
							m_UpHit_flg = true;    //上
							m_vy = 0.65f;
						}
						else if (r >= 115 && r <= 245)
						{
							m_LeftHit_flg = true;	 //左
							m_vx = 0.65f;
						}
						else if (r > 245 && r < 295)
						{
							m_DownHit_flg = true;	 //下
							m_vy = -0.65f;
						}
					}
				}
			}

			//位置情報更新
			m_px += m_vx;
			m_py += m_vy;

			hit_h->SetPos(m_x, m_y); //当たり判定の位置更新

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
						//Attack_flg = true; //Attackフラグtrue
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
						//Attack_flg = true; //Attackフラグtrue
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
						//Attack_flg = true; //Attackフラグtrue
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
						//Attack_flg = true; //Attackフラグtrue
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

			}						
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//ショットガン
				if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
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
			}
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//アサルト
				if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
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
			}		
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//スナイパー
				if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
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
			}			
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//ロケットランチャー
				if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
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
			}
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//レールガン
				if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
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
			//リロード時にリロード効果音を鳴らす
			if (m_Weapon_switching == 0 && m_hg_pb >= 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
			{
				//Audio::Start(13);
			}
	
			//弾の回復処理
			//ショットガン
			if (((UserData*)Save::GetData())->SHG_Ammunition > 0)
			{
				m_sg_pb_me += ((UserData*)Save::GetData())->SHG_Ammunition;
				//弾を回復した時上限を超えないようにする
				if (m_sg_pb_me > 60)
				{
					m_sg_pb_me = 60;
				}
			}
			//アサルトライフル
			if (((UserData*)Save::GetData())->AR_Ammunition > 0)
			{
				m_ar_pb_me += ((UserData*)Save::GetData())->AR_Ammunition;
				//弾を回復した時上限を超えないようにする
				if (m_ar_pb_me > 200)
				{
					m_ar_pb_me = 200;
				}
			}
			//スナイパーライフル
			if (((UserData*)Save::GetData())->SR_Ammunition > 0)
			{
				m_sr_pb_me += ((UserData*)Save::GetData())->SR_Ammunition;
				//弾を回復した時上限を超えないようにする
				if (m_sr_pb_me > 30)
				{
					m_sr_pb_me = 30;
				}
			}
			//ロケットランチャー
			if (((UserData*)Save::GetData())->RL_Ammunition > 0)
			{
				m_rl_pb_me += ((UserData*)Save::GetData())->RL_Ammunition;
				//弾を回復した時上限を超えないようにする
				if (m_rl_pb_me > 2)
				{
					m_rl_pb_me = 2;
				}
			}
			//レールガン
			if (((UserData*)Save::GetData())->RG_Ammunition > 0)
			{
				m_rg_pb_me += ((UserData*)Save::GetData())->RG_Ammunition;
				//弾を回復した時上限を超えないようにする
				if (m_rg_pb_me > 1)
				{
					m_rg_pb_me = 1;
				}
			}

			//弾獲得数初期化
			((UserData*)Save::GetData())->SHG_Ammunition = 0;
			((UserData*)Save::GetData())->AR_Ammunition = 0;
			((UserData*)Save::GetData())->SR_Ammunition = 0;
			((UserData*)Save::GetData())->RL_Ammunition = 0;
			((UserData*)Save::GetData())->RG_Ammunition = 0;
		}

		//HitBoxの内容を更新
		CHitBox* hit_h = Hits::GetHitBox(this); //当たり判定情報取得

		//ミーム実態(中ボス)情報取得
		CObjMeme_Medium_Boss* MMB = (CObjMeme_Medium_Boss*)Objs::GetObj(OBJ_MEME_MEDIUM_BOSS);
		float MMB_x;
		float MMB_y;

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
					HIT_DATA** hit_data;							//当たった時の細かな情報を入れるための構造体
					hit_data = hit_h->SearchElementHit(data_base[i]);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる

					float r = 0;
					for (int j = 0; j < 10; j++) {
						if (hit_data[j] != nullptr) {
							r = hit_data[j]->r;
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

					if (m_time_d <= 0)
					{
						//ゾンビ
						if (hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 15 +( 5 * (((UserData*)Save::GetData())->choose-1));
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= 20 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 80;		//無敵時間をセット
						}
						//コウモリ
						else if (hit_h->CheckObjNameHit(OBJ_BAT_ENEMY) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 5 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= 10 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 60;		//無敵時間をセット
						}
						//火トカゲ
						else if (hit_h->CheckObjNameHit(OBJ_FIRE_LIZARD) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 20 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= 25 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 60;		//無敵時間をセット
						}
						//火の鳥
						else if (hit_h->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 10 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= 2 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 20;		//無敵時間をセット
						}
						//球体型敵
						else if (hit_h->CheckObjNameHit(OBJ_SPHERE_TYPE_ENEMY) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage_En = EXPAttack->GetEXP();
								m_hero_en -= EXPDamage_En;
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage = EXPAttack->GetEXP();
								m_hero_hp -= EXPDamage;
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 90;		//無敵時間をセット
						}
						//ミーム実態(中ボス)本体ダメージ処理
						else if (hit_h->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
						{
							m_hero_hp -= 1;
							m_time_d = 5;		//無敵時間をセット
							Audio::Start(14);//ダメージ音
						}
						//ボス
						else if (hit_h->CheckObjNameHit(OBJ_BOSS) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 10 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= 10 + (5 * (((UserData*)Save::GetData())->choose - 1));
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 30;		//無敵時間をセット
						}
						//爆発
						else if (hit_h->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage_En = EXPAttack->GetEXP();
								m_hero_en -= EXPDamage_En;
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage = EXPAttack->GetEXP();
								m_hero_hp -= EXPDamage;
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 90;		//無敵時間をセット
						}
						//有刺鉄線(スモール)
						else if (hit_h->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
						{
							//耐久力フラグがオンの時、耐久力を減らす
							if (En_flg == true)
							{
								m_hero_en -= 1;
								Audio::Start(14);//ダメージ音
							}
							//体力フラグがオンの時(耐久力が0の場合)、HPを減らす
							if (Hp_flg == true)
							{
								m_hero_hp -= ((UserData*)Save::GetData())->BarbedWireSmall_Attack;
								Audio::Start(14);//ダメージ音
							}
							m_time_d = 30;		//無敵時間をセット
						}
					}
					//敵の攻撃によってHPが0以下になった場合
					if (m_hero_hp <= 0)
						m_hero_hp = 0;	//HPを0にする
					//体力0の場合、耐久力フラグをオン
					if (m_hero_hp == 0)
					{
						Hp_flg = true;
						En_flg = false;
					}

					//敵の攻撃によって耐久力が0以下になった場合
					if (m_hero_en <= 0)
						m_hero_en = 0;	//HPを0にする
					//耐久力0の場合、体力フラグをオン
					if (m_hero_en == 0)
					{
						Hp_flg = true;
						En_flg = false;
					}
				}
				
			}
		}
		if (m_time_d > 0)
		{
			m_time_d--;
		}
		if (m_hero_hp <= 0 && m_blood_flg == false)
		{
			Dead_flg = true;
			m_eff_flag = true;			//画像切り替え用フラグ
			m_speed_power = 0.0f;			//動きを止める	
			m_blood_flg = true; //血しぶき表示停止フラグ
			//血しぶきオブジェクト作成
			CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_blood_dst_size);
			Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
			Audio::Start(15);
		}

		if (m_del == true)
		{
			m_eff_flag = true;			//画像切り替え用フラグ
			//m_speed_power = 0.0f;			//動きを止める
		}

		if (m_time_dead > 0)
		{
			m_time_dead--;
			if (m_time_dead <= 0)
			{
				Scene::SetScene(new CSceneOver());
				m_time_dead = 0;
				g_zombie_count_tu = 0; //チュートリアル敵撃破数用
				Dead_flg = false;
				this->SetStatus(false); //オブジェクト破棄
				Hits::DeleteHitBox(this); //主人公が所有するHitBoxを削除する
			}
		}
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
	
	//ダメージを受けると赤く光る
	if (m_time_d > 0) {
		Draw::Draw(8, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}
}
