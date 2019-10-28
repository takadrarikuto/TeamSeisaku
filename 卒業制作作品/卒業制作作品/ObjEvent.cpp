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
	m_Evwnt_time = 0;		
	//イベントランダム変数
	m_rand_num = 0;

}

//アクション
void CObjEvent::Action()
{
	//タイム情報取得
	CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	bool ST_flg = time->GetTS();

	if (ST_flg == true)
	{

	}
}

//ドロー
void CObjEvent::Draw()
{
	
}