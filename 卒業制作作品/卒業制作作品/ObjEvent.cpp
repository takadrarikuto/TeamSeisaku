//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEvent.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjEvent::Init()
{
	//初期化
	//イベント時間
	m_Evwnt_time = 1800;		
	//測定スタートフラグ
	m_Start_flg = false;

}

//アクション
void CObjEvent::Action()
{
	////発電機情報取得
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();

	/*if (ST_flg == true)
	{
		m_Evwnt_time--;
	}
	if (m_Evwnt_time == 0)
	{
		ST_flg = false;
		m_Start_flg = true;
		m_Evwnt_time = 1800;
	}*/
}

//ドロー
void CObjEvent::Draw()
{
	
}