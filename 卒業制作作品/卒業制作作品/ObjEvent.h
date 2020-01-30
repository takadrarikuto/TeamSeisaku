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

	bool GetEveMiss() { return m_EveMiss_flg; } //時間停止フラグ取得用
	bool GetEveSuc() { return m_EveSuccess_flg; } //イベント成功フラグ取得用

	bool GetEveTimPena() { return m_Event_TimePenalty; } //イベントタイムペナルティ取得用
	bool GetEvePena_Enemy() { return m_EventPenalty_Enemy_flg; } //イベントペナルティ(球体型敵)フラグ取得用
	bool GetEvePena_Meme() { return m_EventPenalty_Meme_flg; } //イベントペナルティ(ミーム実態)フラグ

	int GetApp_Rand() { return m_App_Rand_Flg; } //装置故障イベント時の装置ランダム選択取得用
	int GetEveIns() { return m_Event_Instruction_time; } //イベント指示表示タイム取得用

	void SetEveTimPena(bool T_P) { m_Event_TimePenalty = T_P; } //イベントタイムペナルティ設定用
	void SetApp_Rand(int app_r_f) { m_App_Rand_Flg = app_r_f; } //装置故障イベント時の装置ランダム選択設定用
	void SetEvePena_Enemy(bool P_E) { m_EventPenalty_Enemy_flg = P_E; } //イベントペナルティ(球体型敵)フラグ設定用
	void SetEvePena_Meme(bool P_M) { m_EventPenalty_Meme_flg = P_M; } //イベントペナルティ(ミーム実態)フラグ設定用

	void SetEveMiss(bool EveMiss) { m_EveMiss_flg = EveMiss; } //時間停止フラグ設定用
	void SetEveSuc(bool EveSucc) { m_EveSuccess_flg = EveSucc; } //イベント成功フラグ設定用
private:
	int m_Event_time;	//イベント時間
	bool m_Event_TimePenalty; //イベントタイムペナルティ
	bool m_Event_time_flg; //イベントフラグ
	bool m_EveMiss_flg;
	bool m_EveSuccess_flg; //イベント成功フラグ
	int m_Event_Instruction_time; //イベント指示表示タイム

	bool m_EventPenalty_Enemy_flg; //イベントペナルティ(球体型敵)フラグ
	bool m_EventPenalty_Meme_flg; //イベントペナルティ(ミーム実態)フラグ

	int m_App_Rand_Flg; //装置故障イベント時の装置ランダム選択

};