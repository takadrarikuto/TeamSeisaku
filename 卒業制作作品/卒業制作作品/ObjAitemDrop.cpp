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

}

//アクション
void CObjAitemDrop::Action()
{
	//敵位置取得
	//CObjZombieEnemy* Zombie = (CObjZombieEnemy*)Objs::GetObj(OBJ_ENEMY); //ゾンビ
	//CObjFire_Bird* Fire_Bird = (CObjFire_Bird*)Objs::GetObj(OBJ_FIRE_BIRD); //火の鳥
	//CObjFire_Lizard* Fire_Lizard = (CObjFire_Lizard*)Objs::GetObj(OBJ_FIRE_LIZARD); //火トカゲ
	//CObjBat_Enemy* Bat = (CObjBat_Enemy*)Objs::GetObj(OBJ_BAT_ENEMY); //蝙蝠

	if (m_Aitem_Drop_flg == true)
	{
		/*m_Aitem_Rand_num = rand() % 100;*/
		m_Aitem_Rand_num = 1;
		if (m_Aitem_Rand_num == 0)
		{
			;
		}
		else if (m_Aitem_Rand_num == 1)
		{

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