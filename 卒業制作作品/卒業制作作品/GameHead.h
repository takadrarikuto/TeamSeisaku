#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,
	OBJ_PER_DECISION,
	OBJ_TIME,
	OBJ_GUNATTACK,
	OBJ_SHOTGUNATTACK,
	OBJ_ARATTACK,
	OBJ_SNIPERRIFLEATTACK,
	OBJ_ROCKETLAUNCHERATTACK,
	OBJ_RAILGUNATTACK,
	OBJ_GRENADEATTACK,
	OBJ_ENEMY,
	OBJ_FIRE_BIRD,
	OBJ_FIRE_LIZARD,
	OBJ_BAT_ENEMY,
	OBJ_SPHERE_TYPE_ENEMY,
	OBJ_MEME_MEDIUM_BOSS,
	OBJ_BOSS,
	OBJ_APPARATUS,
	OBJ_ENEMY_NEUTRALIZATION_DEVICE,
	OBJ_BLOOD_SPLASH,
	OBJ_EXPLOSION,
	OBJ_OBJECT,
	OBJ_TUTORIAL,
	OBJ_STAGE,
	OBJ_TITLE,
	OBJ_OP,
	OBJ_OPERATION,
	OBJ_CLEAR,
	OBJ_OVER,
	OBJ_ED,
	OBJ_MENU,
	OBJ_TOPBACK,
	OBJ_BACKGROUND,
	OBJ_AIMING,
	OBJ_HEAL,
	OBJ_EVENT,
	OBJ_SHOTGUN_ITEM,
	OBJ_AR_ITEM,
	OBJ_SNIPERRIFLE_ITEM,
	OBJ_ROCKETLAUNCHER_ITEM,
	OBJ_RAILGUN_ITEM,
	OBJ_GRENADE_ITEM,
	OBJ_ARMOR,
	OBJ_WALL,
	OBJ_TUTO_HERO,
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
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	//武器別ダメージ
	int Gun_Attack = 10;  //ハンドガン
	int SHG_Attack = 30;	//ショットガン
	int AR_Attack = 20; //アサルトライフル
	int SR_Attack = 50; //スナイパーライフル
	int RL_Attack = 150; //ロケットランチャー
	int RG_Attack = 200; //レールガン
	int GRE_Attack = 100;	//グレネード
	int EXP_Attack = 50; //爆発

};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--

extern int g_zombie_count_tu;//チュートリアル敵撃破数用

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

//ステージ
#include "ObjStage.h"

//設置物
#include "ObjGenerator.h"
#include "ObjGenerator2.h"
#include "ObjEnemy_Neutralization_Device.h"
#include "ObjEnemy_Neutralization_Device2.h"

//アイテム
#include "ObjHeal.h"//回復
#include "ObjShotGunItem.h"//ショットガン補充用
#include "ObjARItem.h"//アサルトライフル補充用
#include "ObjSniperRifleItem.h"//スナイパーライフル補充用
#include "ObjRocketLauncherItem.h"//ロケットランチャー補充用
#include "ObjRailGunItem.h"//レールガン補充用
#include "ObjGrenadeItem.h"//グレネード補充用
#include "ObjArmor.h"//アーマー

//イベント
#include "ObjEvent.h"

//タイトル
#include "ObjTitle.h"

//あらすじ
#include "ObjOP.h"

//操作説明
#include "ObjOperation.h"

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

