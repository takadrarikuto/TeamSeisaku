#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEvent :public CObj, public CBaseStatus
{
public:
	CObjEvent() {};
	~CObjEvent() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	bool GetEveTimPena() { return m_Event_TimePenalty; } //イベントタイムペナルティ取得用

	void SetEveTimPena(bool E_TP) { m_Event_TimePenalty = E_TP; } //イベントタイムペナルティ設定用

private:
	int m_Event_time;	//イベント時間
	bool m_Event_TimePenalty; //イベントタイムペナルティ
	bool m_Event_time_flg; //イベントフラグ

};