//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjOperation.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjOperation::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{

		//ロード
		Save::Open();//同フォルダ「UserData」からデータ取得

		init_point = true;
	}

	Save::Seve();//UserDataの情報フォルダ「UserData」を作成
}

//アクション
void CObjOperation::Action()
{
	//Enterキーで決定
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			Audio::Start(0);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//チュートリアルに移動
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			//Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneTutorial());
			Scene::SetScene(new CSceneDifficulty_Level());
		}
	}
}

//ドロー
void CObjOperation::Draw()
{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(3, &src, &dst, c, 0.0f);

	float b[4] = { 1,1,1,1 };

	Font::StrDraw(L"◆Enterで難易度選択へ", 350, 510, 35, b);
}