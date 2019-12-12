#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

#define EVENT_INSTRUCTION 180

class CObjEvent :public CObj, public CBaseStatus
{
public:
	CObjEvent() {};
	~CObjEvent() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	bool GetEveTimPena() { return m_Event_TimePenalty; } //イベントタイムペナルティ取得用
	int GetApp_Rand() { return m_App_Rand_Flg; } //装置故障イベント時の装置ランダム選択取得用
	int GetEveIns() { return m_Event_Instruction_time; } //イベント指示表示タイム取得用

	void SetEveTimPena(bool T_P) { m_Event_TimePenalty = T_P; } //イベントタイムペナルティ設定用

private:
	int m_Event_time;	//イベント時間
	bool m_Event_TimePenalty; //イベントタイムペナルティ
	bool m_Event_time_flg; //イベントフラグ
	int m_Event_Instruction_time; //イベント指示表示タイム

	int m_App_Rand_Flg; //装置故障イベント時の装置ランダム選択

};