//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneStage.h"

#include "GameHead.h"
#include "ObjOP.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjOP::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//アクション
void CObjOP::Action()
{


}
//ドロー
void CObjOP::Draw()
{
	//描写カラー情報
	float bl[4] = { 0.6f,0.6f,0.6f,1.0f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 640.0f;
	src.m_bottom = 490.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	float p[4] = { 1,1,1,1 };

	if (m_y > -600)
	{
		m_y -= 0.6f;
	}	
	
	Font::StrDraw(L"～あらすじ～", GAME_OP_X, GAME_OP_Y + m_y + 400, 40, p);
	Font::StrDraw(L"　財団の機動部隊の一員である主人公は、SCP-354を収容する", GAME_OP_X, GAME_OP_Y + m_y + 500, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"ためにエリア３５４に送られました。", GAME_OP_X, GAME_OP_Y + m_y + 550, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"　だがそこは、SCP-354の収容違反が発生し施設が壊滅して", GAME_OP_X, GAME_OP_Y + m_y + 650, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"いました。主人公はある機械を起動させ、オブジェクトを", GAME_OP_X, GAME_OP_Y + m_y + 700, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"鎮静化、または無力化するために発電機を起動します。", GAME_OP_X, GAME_OP_Y + m_y + 750, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"　ですがオブジェクトからは数々の妨害を与えてきます。", GAME_OP_X, GAME_OP_Y + m_y + 850, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"主人公は無事機械が発動するまで生き残れるのか・・・", GAME_OP_X, GAME_OP_Y + m_y + 900, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"※Enterで次へ", GAME_OP_X, GAME_OP_Y + m_y + 1000, GAME_OP_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneOperation());
		//Scene::SetScene(new CSceneStage());
	}
}