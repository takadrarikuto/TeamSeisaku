#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記	
	OBJ_HERO, //主人公
	OBJ_PER_DECISION,
	OBJ_FOOTPRINT,
	OBJ_TIME,
	OBJ_AIMING, //照準
	//銃
	OBJ_GUNATTACK,
	OBJ_SHOTGUNATTACK,
	OBJ_ARATTACK,
	OBJ_SNIPERRIFLEATTACK,
	OBJ_ROCKETLAUNCHERATTACK,
	OBJ_RAILGUNATTACK,
	OBJ_GRENADEATTACK,
	//敵
	OBJ_ENEMY,
	OBJ_FIRE_BIRD,
	OBJ_FIRE_LIZARD,
	OBJ_BAT_ENEMY,
	OBJ_SPHERE_TYPE_ENEMY,
	//中ボス
	OBJ_MEME_MEDIUM_BOSS,
	//ボス
	OBJ_BOSS,
	//装置
	OBJ_GENERATOR,
	OBJ_GENERATOR2,
	OBJ_ENEMY_NEUTRALIZATION_DEVICE,
	OBJ_ENEMY_NEUTRALIZATION_DEVICE2,
	OBJ_MEME_NEUTRALIZATION_DEVICE,
	//血しぶき、爆発エフェクト
	OBJ_BLOOD_SPLASH,
	OBJ_EXPLOSION,
	//ステージ、設置物
	OBJ_OBJECT,	
	OBJ_STAGE,
	OBJ_NET,
	OBJ_NET_V,
	OBJ_ARMOR,
	OBJ_WALL,
	OBJ_BARBED_WIRE,
	OBJ_BARBED_WIRE_V,
	OBJ_BARBED_WIRE_SMALL,
	//タイトル
	OBJ_TITLE,
	//難易度設定
	OBJ_LEVEL,
	//あらすじ
	OBJ_OP,
	//操作説明
	OBJ_OPERATION,
	//クリア
	OBJ_CLEAR,
	//ゲームオーバー
	OBJ_OVER,
	//エンディング
	OBJ_ED,
	//メニュー
	OBJ_MENU,
	//イベント
	OBJ_EVENT,
	//ドロップアイテム
	OBJ_SHOTGUN_ITEM,
	OBJ_AR_ITEM,
	OBJ_SNIPERRIFLE_ITEM,
	OBJ_ROCKETLAUNCHER_ITEM,
	OBJ_RAILGUN_ITEM,
	OBJ_GRENADE_ITEM,
	OBJ_AITEMDROP,
	OBJ_HEAL,
	//設置型アイテム
	OBJ_INSTALL_TYPE_SHG,
	OBJ_INSTALL_TYPE_AR,
	OBJ_INSTALL_TYPE_SR,
	OBJ_INSTALL_TYPE_RANDBOX,
	//チュートリアル系
	OBJ_TUTO_HERO,
	OBJ_TUTORIAL,
	OBJ_TOPBACK,
	//背景、フォント
	OBJ_BACKGROUND,
	OBJ_TOOLBOX,
	OBJ_AITEM_FONT,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_WALL,
	ELEMENT_WALL2,
	ELEMENT_FIELD2,
	ELEMENT_MEME_ND,
	ELEMENT_NET_V,
	ELEMENT_NET_S,
	ELEMENT_BARBED_V,
	ELEMENT_BARBED_S,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ

	//レベル別タイム設定
	int Level_Time = 0;

	//武器装填
	int SHG_load = 0;	//ショットガン
	int AR_load = 0; //アサルトライフル
	int SR_load = 0; //スナイパーライフル
	int RL_load = 0; //ロケットランチャー
	int RG_load = 0; //レールガン
	int GRE_load = 0; //グレネード

	//難易度変更
	int choose = 0;
	//イベント開始タイム
	int Event_Time = 0;
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
//HitBox接触後のベクトル変化
#define HitBox_V 0.15

//HitBoxFlg初期化タイム
#define HitBoxFlg_TIME 1; 

//移動確認タイム
//x軸
#define X_Move 60
//y軸
#define Y_Move 30

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------
//ベースデータ
#include "BaseStatus.h"

//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
//主人公
#include "ObjHero.h"

//主人公用攻撃
#include "ObjGunAttack.h"
#include "ObjShotGunAttack.h"
#include "ObjARAttack.h"
#include "ObjSniperRifleAttack.h"
#include "ObjRocketLauncherAttack.h"
#include "ObjRailGunAttack.h"
#include "ObjGrenadeAttack.h"

//標準
#include "ObjAiming.h"

//エネミー
#include "ObjZombieEnemy.h"
#include "ObjFire_Bird.h"
#include "ObjFire_Lizard.h"
#include "ObjBat_Enemy.h"
#include "ObjSphere_Type_Enemy.h"

//中ボス
#include "ObjMeme_Medium_Boss.h"

//ボス
#include "ObjBoss.h"

//エネミー・中ボス・ボス用攻撃
//死亡エフェクト
#include "ObjBlood_splash.h"

//爆発
#include "ObjExplosion.h"

//足跡
#include "ObjFootprint.h"

//ステージ
#include "ObjStage.h"

//設置物
#include "ObjGenerator.h"
#include "ObjGenerator2.h"
#include "ObjEnemy_Neutralization_Device.h"
#include "ObjEnemy_Neutralization_Device2.h"
#include "ObjMeme_Neutralization_Device.h"
#include "ObjBarbedWire.h"
#include "ObjBarbedWireV.h"
#include "ObjBarbedWireSmall.h"
#include "ObjNet.h"
#include "ObjNetV.h"

//アイテム
#include "ObjHeal.h"//回復
#include "ObjShotGunItem.h"//ショットガン補充用
#include "ObjARItem.h"//アサルトライフル補充用
#include "ObjSniperRifleItem.h"//スナイパーライフル補充用
#include "ObjRocketLauncherItem.h"//ロケットランチャー補充用
#include "ObjRailGunItem.h"//レールガン補充用
#include "ObjGrenadeItem.h"//グレネード補充用
#include "ObjArmor.h"//アーマー
#include "ObjToolBox.h"//工具箱
#include "ObjAitemDrop.h" //アイテムドロップ
#include "ObjInstallation_Type_ShotGun.h" //設置型ショットガン補充用
#include "ObjInstallation_Type_AR.h" //設置型アサルトライフル補充用
#include "ObjInstallation_Type_SR.h" //設置型スナイパーライフル補充用
#include "ObjInstallation_Type_RandBox.h" //設置型ランダムアイテムボックス

//イベント
#include "ObjEvent.h"

//タイトル
#include "ObjTitle.h"

//難易度
#include "ObjDifficulty_Level.h"

//あらすじ
#include "ObjOP.h"

//操作説明
#include "ObjOperation.h"

//フォント
#include "ObjAitemFont.h"

//チュートリアル
#include "ObjTutorial.h"
//チュートリアル用
#include "ObjTutoHero.h"
#include "ObjTutoBg.h"
#include "ObjTutoTopback.h"
#include "ObjTutoZombieEnemy.h"
#include "ObjTutoWall.h"
#include "ObjTutoWall2.h"
#include "ObjTutoWall3.h"
#include "ObjTutoWall4.h"

//ゲームオーバー
#include "ObjOver.h"

//クリア
#include "ObjClear.h"

//エンディング
#include "ObjED.h"

//メニュー
#include "ObjMenu.h"

//タイム
#include "ObjTime.h"

//ステージ上部UI背景
#include "ObjTopback.h"

//背景
#include "ObjBackground.h"

//壁
#include "ObjWall.h"//左
#include "ObjWall2.h"//右
#include "ObjWall3.h"//上
#include "ObjWall4.h"//下

//ベース設定
#include "GameHead.h"


//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
//ステージ
#include "SceneStage.h"

//タイトル
#include "SceneTitle.h"

//難易度
#include "SceneDifficulty_Level.h"

//あらすじ
#include "SceneOP.h"

//操作説明
#include "SceneOperation.h"

//チュートリアル
#include "SceneTutorial.h"

//ゲームオーバー
#include "SceneOver.h"

//クリア
#include "SceneClear.h"

//エンディング
#include "SceneED.h"

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録

#define SET_GAME_START  CSceneTitle
