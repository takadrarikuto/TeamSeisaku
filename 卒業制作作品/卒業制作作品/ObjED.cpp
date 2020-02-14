//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjED.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjED::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//アクション
void CObjED::Action()
{


}
//ドロー
void CObjED::Draw()
{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };//白
	float bl[4] = { 0.6f,0.6f,0.6f,1.0f };//黒
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤

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

	if (m_y > -1300)
	{
		m_y -= 0.6f;
	}
		
	
	//0イージー1ノーマル2ハード
	//難易度によって見れる文章を分ける
	if (((UserData*)Save::GetData())->choose >= 0)
	{
		Font::StrDraw(L"文書354-i 事案報告書", GAME_ED_X, GAME_ED_Y + m_y + 400, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"[データ削除済]の夜、エリア354から救援信号を受信し連絡を", GAME_ED_X, GAME_ED_Y + m_y + 450, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"試みました。しかしエリア354からの応答はありませんでした。", GAME_ED_X, GAME_ED_Y + m_y + 500, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"この収容違反に対処するために機動部隊[編集済み]を派遣し", GAME_ED_X, GAME_ED_Y + m_y + 550, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"職員の救出と制圧を命令されました。", GAME_ED_X, GAME_ED_Y + m_y + 600, GAME_ED_FONT_SIZE, p);
		if (((UserData*)Save::GetData())->choose >= 1)
		{
			Font::StrDraw(L"しかし機動部隊がエリア354へ到着した2時間後全職員からの連絡が", GAME_ED_X, GAME_ED_Y + m_y + 700, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"途絶えました。その後、エリア354の電力システムの回復を確認し、", GAME_ED_X, GAME_ED_Y + m_y + 750, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"エリア354に再度連絡を試みました。", GAME_ED_X, GAME_ED_Y + m_y + 800, GAME_ED_FONT_SIZE, p);
			if (((UserData*)Save::GetData())->choose == 2)
			{
				Font::StrDraw(L"連絡を行った直後にエリア354からのすべての通信は喪失しました。", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"その後の調査によってエリア354の核弾頭が起爆したことが", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"確認されました。", GAME_ED_X, GAME_ED_Y + m_y + 1000, GAME_ED_FONT_SIZE, p);

				Font::StrDraw(L"これによりエリア354の職員及び機動部隊の全滅、施設の全破壊", GAME_ED_X, GAME_ED_Y + m_y + 1100, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"という結果に終わった。またオブジェクトは不活性化しており", GAME_ED_X, GAME_ED_Y + m_y + 1150, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"エンティティを排出しなくなった。", GAME_ED_X, GAME_ED_Y + m_y + 1200, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"最後のエンティティが水溜まりから出てきてから現在まで", GAME_ED_X, GAME_ED_Y + m_y + 1250, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"[データ削除済]が経過した。", GAME_ED_X, GAME_ED_Y + m_y + 1300, GAME_ED_FONT_SIZE, p);
			}
			else if (((UserData*)Save::GetData())->choose < 2)
			{
				Font::StrDraw(L"[要レベル4クリアランス]", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, r);
				Font::StrDraw(L"※ハードステージクリアで閲覧可能", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, r);
			}
		}
		else if(((UserData*)Save::GetData())->choose < 1)
		{
			Font::StrDraw(L"[要レベル3クリアランス]", GAME_ED_X, GAME_ED_Y + m_y + 700, GAME_ED_FONT_SIZE, r);
			Font::StrDraw(L"※ノーマルステージクリアで閲覧可能", GAME_ED_X, GAME_ED_Y + m_y + 750, GAME_ED_FONT_SIZE, r);
			Font::StrDraw(L"[要レベル4クリアランス]", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, r);
			Font::StrDraw(L"※ハードステージクリアで閲覧可能", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, r);
		}
	}
	

	Font::StrDraw(L"閲覧終了", GAME_ED_X, GAME_ED_Y + m_y + 1400, GAME_ED_FONT_SIZE, p);

	Font::StrDraw(L"※Enterでタイトルへ", GAME_ED_X, GAME_ED_Y + m_y + 1500, GAME_ED_FONT_SIZE, p);

	Font::StrDraw(L"「SCP-354 事案報告書」は「Dave Rapp」作「SCP-354」に基づきます。", GAME_ED_X, GAME_ED_Y + m_y + 1600, GAME_CC_FONT_SIZE, p);
	Font::StrDraw(L"本家(英文) http://scp-wiki.net/scp-354", GAME_ED_X, GAME_ED_Y + m_y + 1630, GAME_CC_FONT_SIZE, p);
	Font::StrDraw(L"日本語訳版 http://ja.scp-wiki.net/scp-354", GAME_ED_X, GAME_ED_Y + m_y + 1660, GAME_CC_FONT_SIZE, p);
	Font::StrDraw(L"このゲームはCC BY-SA 3.03.0ライセンスの下で提供されている", GAME_ED_X, GAME_ED_Y + m_y + 1685, GAME_CC_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}