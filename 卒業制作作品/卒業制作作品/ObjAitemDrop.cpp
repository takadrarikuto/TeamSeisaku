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
	m_Fire_Bird_Drop_flg = false; //火の鳥
	m_Fire_Lizard_Drop_flg = false; //火トカゲ
	Bat_Drop_flg = false; //蝙蝠
//エネミー別で座標を記録する
	Z_X= 0.0f; //ゾンビ
	Z_Y= 0.0f;
	FB_X= 0.0f; //火の鳥
	FB_Y= 0.0f;
	FL_X= 0.0f; //火トカゲ
	FL_Y= 0.0f;
	B_X= 0.0f; //蝙蝠
	B_Y= 0.0f;

}

//アクション
void CObjAitemDrop::Action()
{
	//敵位置取得
	CObjZombieEnemy* Zombie = (CObjZombieEnemy*)Objs::GetObj(OBJ_ENEMY); //ゾンビ
	//CObjFire_Bird* Fire_Bird = (CObjFire_Bird*)Objs::GetObj(OBJ_FIRE_BIRD); //火の鳥
	//CObjFire_Lizard* Fire_Lizard = (CObjFire_Lizard*)Objs::GetObj(OBJ_FIRE_LIZARD); //火トカゲ
	//CObjBat_Enemy* Bat = (CObjBat_Enemy*)Objs::GetObj(OBJ_BAT_ENEMY); //蝙蝠
	if (Zombie != nullptr)
	{
		Z_X = Zombie->GetX();
		Z_Y = Zombie->GetY();
	}

	if (m_Aitem_Drop_flg == true)
	{
		m_Aitem_Rand_num = rand() % 100;
		if (m_Aitem_Rand_num < 80)
		{
			; //ドロップしない
		}
		else if (m_Aitem_Rand_num >= 80 && m_Aitem_Rand_num < 85)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//回復
				CObjHeal* Heal = new CObjHeal(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);

				m_Zombie_Drop_flg = false;
			}			
		}
		else if (m_Aitem_Rand_num >= 85 && m_Aitem_Rand_num < 90)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//アーマー
				CObjArmor* Armor = new CObjArmor(Z_X + 15, Z_Y + 10);
				Objs::InsertObj(Armor, OBJ_ARMOR, 7);				

				m_Zombie_Drop_flg = false;
			}
		}
		else if (m_Aitem_Rand_num >= 90 && m_Aitem_Rand_num < 95)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//ショットガン弾補充
				CObjShotGunItem* SGi = new CObjShotGunItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);			

				m_Zombie_Drop_flg = false;
			}
		}
		else if (m_Aitem_Rand_num >= 95 && m_Aitem_Rand_num < 98)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//アサルトライフル弾補充
				CObjARItem* ARi = new CObjARItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);				

				m_Zombie_Drop_flg = false;
			}
		}
		else if (m_Aitem_Rand_num >= 98 && m_Aitem_Rand_num < 100)
		{
			if (m_Zombie_Drop_flg == true)
			{
				//スナイパーライフル弾補充
				CObjSniperRifleItem* SRi = new CObjSniperRifleItem(Z_X + 15, Z_Y + 20);
				Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);

				m_Zombie_Drop_flg = false;
			}
		}
		m_Aitem_Drop_flg = false;
	}
	else if (m_Aitem_Drop_flg == false)
	{
		m_Aitem_Rand_num = 0;
	}
}

//ドロー
void CObjAitemDrop::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };


}