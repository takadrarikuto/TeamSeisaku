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
	OBJ_ENEMY,
	OBJ_BLOOD_SPLASH,
	OBJ_OBJECT,
	OBJ_TITLE,
	OBJ_OP,
	OBJ_OPERATION,
	OBJ_CLEAR,
	OBJ_OVER,
	OBJ_ED,
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
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--



//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------
//ベースデータ
#include "BaseStatus.h"

//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
//主人公
#include "ObjHero.h"

//主人公用攻撃
//エネミー
//中ボス
//ボス
//エネミー・中ボス・ボス用攻撃
//死亡エフェクト
#include "ObjBlood_splash.h"

//ステージ

//タイトル
#include "ObjTitle.h"

//あらすじ
#include "ObjOP.h"

//操作説明
#include "ObjOperation.h"

//ゲームオーバー
#include "ObjOver.h"

//クリア
#include "ObjClear.h"

//エンディング
#include "ObjED.h"

//メニュー
#include "ObjMenu.h"

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

//ゲームオーバー
#include "SceneOver.h"

//クリア
#include "SceneClear.h"

//エンディング
#include "SceneED.h"

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
//#define SET_GAME_START  CSceneStage

//デバッグ用
#define SET_GAME_START  CSceneOver
//-----------------------------------------------