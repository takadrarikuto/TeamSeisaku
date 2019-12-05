#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//使用するGameLヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include"GameL\DrawFont.h"
#include "GameL\Audio.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CSceneStage::CSceneStage()
{

}

//テストラクタ
CSceneStage::~CSceneStage()
{

}

//初期化メソッド
void CSceneStage::InitScene()
{
	//Font作成
	//グラフィック読み込み
	Draw::LoadImage(L"ステージ.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"銃弾まとめ.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"血の池.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"エネミーまとめ.png", 4, TEX_SIZE_512);
	Draw::LoadImage(L"壁.png", 5, TEX_SIZE_512);
	Draw::LoadImage(L"装置・設置物.png", 6, TEX_SIZE_512);
	Draw::LoadImage(L"アイテム・設置物.png", 7, TEX_SIZE_512);
	Draw::LoadImage(L"兵士・軍人.png", 8, TEX_SIZE_512);
	Draw::LoadImage(L"爆発.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"血しぶきアニメーション.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"武器表示用.png", 11, TEX_SIZE_512);
	Draw::LoadImage(L"照準.png", 12, TEX_SIZE_512);
	Draw::LoadImage(L"機材・武器.png", 29, TEX_SIZE_512);
	Draw::LoadImage(L"image.png", 30, TEX_SIZE_512);
	Draw::LoadImage(L"image2.png", 31, TEX_SIZE_512);
	Draw::LoadImage(L"image3.png", 32, TEX_SIZE_512);
	Draw::LoadImage(L"操作説明.png", 33, TEX_SIZE_1024);

	//音楽情報読み込み 
	Audio::LoadAudio(0, L"ステージBGM.wav", SOUND_TYPE::BACK_MUSIC);
	//音楽情報の読み込み
	Audio::LoadAudio(1, L"選択音.wav", EFFECT);
	Audio::LoadAudio(2, L"決定音.wav", EFFECT);
	Audio::LoadAudio(3, L"ハンドガン銃声.wav", EFFECT);
	Audio::LoadAudio(4, L"ショットガン銃声.wav", EFFECT);
	Audio::LoadAudio(5, L"スナイパーライフル銃声.wav", EFFECT);
	//6
	//7
	//8
	Audio::LoadAudio(9, L"爆発音.wav", EFFECT);
	Audio::LoadAudio(10, L"弾切れ.wav", EFFECT);
	Audio::LoadAudio(11, L"ゾンビ1.wav", EFFECT);
	Audio::LoadAudio(12, L"アイテム獲得音.wav", EFFECT);
	Audio::LoadAudio(13, L"リロード音.wav", EFFECT);

	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(-0.3);
	Audio::Start(0); //音楽スタート

	//エネミー出現タイム初期化
	e_time = 0;
	//アイテム出現タイム初期化
	i_time = 0;
	//アイテム出現位置初期化
	i_x = 0.0f;
	//アイテム出現位置
	i_x = 0.0f;
	i_y = 0.0f;

	//シーン切り替えタイム
	Scene_time = 0;
	//ゲームオーバー移動時間
	GameOver_time = 0;

	//主人公機オブジェクト作成
	CObjHero* obj_h = new CObjHero(368.0f, 268.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 8);

	//照準オブジェクト作成
	CObjAiming* obj_ai = new CObjAiming();
	Objs::InsertObj(obj_ai, OBJ_AIMING, 12);

	//背景オブジェクト作成
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);

	//ボスオブジェクト作成 
	CObjBoss*obj_boss = new CObjBoss(272, 350);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 2);	

	//発電機オブジェクト作成	
	CObjGenerator* Gen = new CObjGenerator(-300, -400);
	Objs::InsertObj(Gen, OBJ_GENERATOR, 2);

	CObjGenerator2* Gen2 = new CObjGenerator2(1100, 900);
	Objs::InsertObj(Gen2, OBJ_GENERATOR, 2);

	//敵無力化装置オブジェクト作成
	CObjEnemy_Neutralization_Device* END = new CObjEnemy_Neutralization_Device(1100, -400);//(400,200)
	Objs::InsertObj(END, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	CObjEnemy_Neutralization_Device2* END2 = new CObjEnemy_Neutralization_Device2(-300, 900);//(700,200)
	Objs::InsertObj(END2, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	//ミーム実態無力化装置オブジェクト作成
	CObjMeme_Neutralization_Device* MND = new CObjMeme_Neutralization_Device(375, -500);
	Objs::InsertObj(MND, OBJ_MEME_NEUTRALIZATION_DEVICE, 2);

	//有刺鉄線オブジェクト作成 x=202 y=72(横)
	CObjBarbedWire* Barbed;
	//左上
	for (int x = -402; x < 0; x += 202)
	{
		Barbed = new CObjBarbedWire(x, -300);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = -400; x < -103; x += 101)
	{
		Barbed = new CObjBarbedWire(x, -500);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//左下
	for (int x = -425; x < -23; x += 202)
	{
		Barbed = new CObjBarbedWire(x, 800);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = -427; x < -130; x += 101)
	{
		Barbed = new CObjBarbedWire(x, 1000);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//右上
	for (int x = 973; x < 1375; x += 202)
	{
		Barbed = new CObjBarbedWire(x, -300);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = 975; x < 1278; x += 101)
	{
		Barbed = new CObjBarbedWire(x, -500);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	//右下
	for (int x = 998; x < 1400; x += 202)
	{
		Barbed = new CObjBarbedWire(x, 800);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}
	for (int x = 1000; x < 1303; x += 101)
	{
		Barbed = new CObjBarbedWire(x, 1000);
		Objs::InsertObj(Barbed, OBJ_BARBED_WIRE, 3);
	}

	//有刺鉄線オブジェクト作成 x=72 y=202(縦)
	CObjBarbedWireV* BarbedV;
	//左上
	BarbedV = new CObjBarbedWireV(-400, -430, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(-170, -430, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	//左下
	BarbedV = new CObjBarbedWireV(-425, 872, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(-195, 872, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	//右上
	BarbedV = new CObjBarbedWireV(975, -430, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(1207, -430, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);	
	//右下
	BarbedV = new CObjBarbedWireV(998, 872, false);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	BarbedV = new CObjBarbedWireV(1229, 872, true);
	Objs::InsertObj(BarbedV, OBJ_BARBED_WIRE_V, 3);
	

	//有刺鉄線(ミニ)オブジェクト作成 x=68 y=53
	CObjBarbedWireSmall* BarbedS = new CObjBarbedWireSmall(200, 200);
	//左内
	for (int y = 120; y < 650; y += 53)
	{
		BarbedS = new CObjBarbedWireSmall(-25, y);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//左外
	for (int y = -30; y < 500; y += 53)
	{
		BarbedS = new CObjBarbedWireSmall(-425, y);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//右内
	for (int y = -30; y < 500; y += 53)
	{
		BarbedS = new CObjBarbedWireSmall(775, y);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//右外
	for (int y = 120; y < 650; y += 53)
	{
		BarbedS = new CObjBarbedWireSmall(1175, y);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//上
	for (int x = 302; x < 504; x += 68)
	{
		BarbedS = new CObjBarbedWireSmall(x, -225);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}
	//下
	for (int x = 302; x < 504; x += 68)
	{
		BarbedS = new CObjBarbedWireSmall(x, 800);
		Objs::InsertObj(BarbedS, OBJ_BARBED_WIRE_SMALL, 3);
	}

	//網オブジェクト作成(横) x=202 y=72
	CObjNet* Net = new CObjNet(0, 0);
	//横---------------------------------------
	//左上
	for (int x = -602; x < 206; x += 202)
	{
		Net = new CObjNet(x, -100);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//左下
	for (int x = -602; x < 206; x += 202)
	{
		Net = new CObjNet(x, 650);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//右上
	for (int x = 602; x < 1408; x += 202)
	{
		Net = new CObjNet(x, -100);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//右下
	for (int x = 602; x < 1408; x += 202)
	{
		Net = new CObjNet(x, 650);
		Objs::InsertObj(Net, OBJ_NET, 3);
	}
	//------------------------------------------

	//網オブジェクト作成(縦) x=72 y=202
	CObjNetV* NetV = new CObjNetV(800, 200);
	//縦----------------------------------------
	//左上
	for (int y = -302; y < -100; y += 202)
	{
		NetV = new CObjNetV(134, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//左下
	for (int y = 722; y < 924; y += 202)
	{
		NetV = new CObjNetV(134, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//右上
	for (int y = -302; y < -100; y += 202)
	{
		NetV = new CObjNetV(602, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//右下
	for (int y = 722; y < 924; y += 202)
	{
		NetV = new CObjNetV(602, y);
		Objs::InsertObj(NetV, OBJ_NET, 3);
	}
	//------------------------------------------
	
	//アイテムオブジェクト作成	
	//ロケットランチャー弾補充
	CObjRocketLauncherItem* RLi = new CObjRocketLauncherItem(50, -150);
	Objs::InsertObj(RLi, OBJ_ROCKETLAUNCHER_ITEM, 4);
	//レールガン弾補充
	CObjRailGunItem* RGi = new CObjRailGunItem(700, -150);
	Objs::InsertObj(RGi, OBJ_RAILGUN_ITEM, 4);
	//グレネード補充
	CObjGrenadeItem* GREi = new CObjGrenadeItem(70, 730);
	Objs::InsertObj(GREi, OBJ_GRENADE_ITEM, 4);
	//回復
	CObjHeal* Heal = new CObjHeal(700, 730);
	Objs::InsertObj(Heal, OBJ_HEAL, 4);
	//アーマー
	CObjArmor* Armor = new CObjArmor(381.0f, 150.0f);
	Objs::InsertObj(Armor, OBJ_ARMOR, 4);
	

	//アイテムドロップオブジェクト作成	
	CObjAitemDrop* obj_ad = new CObjAitemDrop();
	Objs::InsertObj(obj_ad, OBJ_AITEMDROP, 8);

	//設置型ショットガン弾補充
	CObjInstallation_Type_ShotGun* obj_it_shg = new CObjInstallation_Type_ShotGun(-300, -640);
	Objs::InsertObj(obj_it_shg, OBJ_INSTALL_TYPE_SHG, 8);
	//設置型アサルトライフル弾補充
	CObjInstallation_Type_AR* obj_it_ar = new CObjInstallation_Type_AR(1075, -640);
	Objs::InsertObj(obj_it_ar, OBJ_INSTALL_TYPE_AR, 8);
	//設置型スナイパーライフル弾補充
	CObjInstallation_Type_SR* obj_it_sr = new CObjInstallation_Type_SR(-293, 670);
	Objs::InsertObj(obj_it_sr, OBJ_INSTALL_TYPE_SR, 8);
	//設置型ランダムアイテムボックス
	CObjInstallation_Type_RandBox* obj_it_rb = new CObjInstallation_Type_RandBox(1130, 720);
	Objs::InsertObj(obj_it_rb, OBJ_INSTALL_TYPE_RANDBOX, 8);

	//壁オブジェクト作成
	//左
	CObjWall* Wall = new CObjWall(200, 200);
	Objs::InsertObj(Wall, OBJ_WALL, 6);
	//右
	CObjWall2* Wall2 = new CObjWall2(200, 200);
	Objs::InsertObj(Wall2, OBJ_WALL, 6);
	//上
	CObjWall3* Wall3 = new CObjWall3(200, 200);
	Objs::InsertObj(Wall3, OBJ_WALL, 6);
	//下
	CObjWall4* Wall4 = new CObjWall4(200, 200);
	Objs::InsertObj(Wall4, OBJ_WALL, 6);

	//フォント
	//アイテム獲得フォントオブジェクト作成
	CObjAitemFont* obj_af = new CObjAitemFont();
	Objs::InsertObj(obj_af, OBJ_AITEM_FONT, 19);

	//ステージ上部背景オブジェクト作成
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);

	//ステージオブジェクト作成
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//タイムオブジェクト作成
	CObjTime*objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 20);

	//イベントタイムオブジェクト作成
	CObjEvent*objev = new CObjEvent();
	Objs::InsertObj(objev, OBJ_EVENT, 20);

	//音楽情報読み込み 
	//Audio::LoadAudio(0, L"ステージBGM.wav",BACK_MUSIC);

	//バックミュージックスタート
	//ボリュームを0.6にする
	//float v = Audio::VolumeMaster(0.6);

	//Audio::Start(0); //音楽スタート
	
}

void CSceneStage::Scene()
{
	//ゲームオーバーシーン移動処理
	//if (GameOver_flg == true)
	//{
	//	GameOver_time++;
	//}
	//if (GameOver_time == 60)
	//{
	//	//フラグ・タイム初期化
	//	GameOver_flg = false;
	//	GameOver_time = 0;
	//	//ゲームオーバー画面移動
	//	Scene::SetScene(new CSceneGameOver());
	//}
	//メニュー画面閲覧時行動停止処理
	if (Menu_flg == false)
	{
		//ボスを倒したら少し時間を空けてからシーン移動する
		/*if (boss_count == 1)
		{
			Scene_time++;
		}*/
		if (Scene_time == 60)
		{
			//ボスカウント・シーンタイム初期化
			//boss_count = 0;
			Scene_time = 0;
		}

		//e_time++;
		//if (e_time == 90)
		//{
		//	e_x = rand() % 736;
		//	e_y = rand() % 536;
		//	//敵機オブジェクト作成
		//	CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y);
		//	Objs::InsertObj(obj_ze, OBJ_ENEMY, 4);
		//}		

	//メニュー画面閲覧時行動停止処理
	//if (Menu_flg == false)
	//{
		//各タイム増加
		//e_time++;
		//i_time++;

		////敵機オブジェクト作成
		//CObjEnemy* obj_e;
		////連結敵機オブジェクト作成
		//CObjLinkingEnemy* obj_le;
		////カーブ敵機オブジェクト生成
		//CObjCurveEnemy* obj_ce;
		////拡散敵機オブジェクト生成
		//CObjDiffusionEnemy* obj_de;
		////爆弾オブジェクト作成
		//CObjBomd* obj_b;

		//敵出現処理
		//if (e_time == 90)
		//{
		//	//敵機オブジェクト作成
		//	obj_e = new CObjEnemy(378.0f, -32.0f);
		//	Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	if (Usually_flg == true)
		//	{
		//		//敵機オブジェクト作成
		//		obj_e = new CObjEnemy(178.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//		obj_e = new CObjEnemy(578.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	}
		//}

		//i_x = rand() % 770;

		//if (i_time == 600)
		//{
		//	//HP回復アイテムオブジェクト作成
		//	CObjHPupItem* obj_hi = new CObjHPupItem(i_x, -30.0f);
		//	Objs::InsertObj(obj_hi, OBJ_ITEM, 2);

		//	srand(time(NULL)); // ランダム情報を初期化
		//	i_time = 0;
		//}
	}

}