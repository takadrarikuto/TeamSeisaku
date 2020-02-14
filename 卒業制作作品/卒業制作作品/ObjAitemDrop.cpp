//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include <time.h>

#include "GameHead.h"
#include "ObjAitemDrop.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjAitemDrop::Init()
{
//初期化
	//アイテムドロップフラグ
	m_Aitem_Drop_flg = false; 
	//アイテムランダム選択変数
	m_Aitem_Rand_num = 0; 

//どのエネミーからドロップするか確認するフラグ
	m_Zombie_Drop_flg = false; //ゾンビ
	m_Fire_Lizard_Drop_flg = false; //火トカゲ
	Bat_Drop_flg = false; //蝙蝠
//エネミー別で座標を記録する
	Z_X= 0.0f; //ゾンビ
	Z_Y= 0.0f;
	FL_X= 0.0f; //火トカゲ
	FL_Y= 0.0f;
	B_X= 0.0f; //蝙蝠
	B_Y= 0.0f;

}

//アクション
void CObjAitemDrop::Action()
{
	m_Aitem_Rand_num = rand() % 100; //ランダム処理

	//アイテムドロップ処理
	if (m_Aitem_Drop_flg == true)
	{
		if (m_Aitem_Rand_num < 80)
		{
			; //ドロップしない
		}
		//回復ドロップ
		else if (m_Aitem_Rand_num >= 85 && m_Aitem_Rand_num < 90)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//回復
				CObjHeal* Heal = new CObjHeal(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);
				
				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//回復
				CObjHeal* Heal = new CObjHeal(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//回復
				CObjHeal* Heal = new CObjHeal(B_X + 15, B_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		//アーマードロップ
		else if (m_Aitem_Rand_num >= 90 && m_Aitem_Rand_num < 95)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//アーマー
				CObjArmor* Armor = new CObjArmor(Z_X + 15, Z_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);				

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//アーマー
				CObjArmor* Armor = new CObjArmor(FL_X + 15, FL_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//アーマー
				CObjArmor* Armor = new CObjArmor(B_X + 15, B_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		//ショットガンの弾ドロップ
		else if (m_Aitem_Rand_num >= 95 && m_Aitem_Rand_num < 97)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//ショットガン弾補充
				CObjShotGunItem* SGi = new CObjShotGunItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);			

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//ショットガン弾補充
				CObjShotGunItem* SGi = new CObjShotGunItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{//ショットガン弾補充
				CObjShotGunItem* SGi = new CObjShotGunItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);


				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		//アサルトライフルの弾ドロップ
		else if (m_Aitem_Rand_num >= 97 && m_Aitem_Rand_num < 99)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//アサルトライフル弾補充
				CObjARItem* ARi = new CObjARItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);				

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//アサルトライフル弾補充
				CObjARItem* ARi = new CObjARItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//アサルトライフル弾補充
				CObjARItem* ARi = new CObjARItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		//スナイパーライフルの弾ドロップ
		else if (m_Aitem_Rand_num >= 99 && m_Aitem_Rand_num <= 100)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//スナイパーライフル弾補充
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				m_Zombie_Drop_flg = false;
			}
			if (m_Fire_Lizard_Drop_flg == true)
			{
				//スナイパーライフル弾補充
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(FL_X + 15, FL_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				m_Fire_Lizard_Drop_flg = false;
			}
			if (Bat_Drop_flg == true)
			{
				//スナイパーライフル弾補充
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(B_X + 15, B_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				Bat_Drop_flg = false;
			}
			m_Aitem_Rand_num = 0;
		}
		m_Aitem_Drop_flg = false;
	}
	
}

//ドロー
void CObjAitemDrop::Draw()
{


}