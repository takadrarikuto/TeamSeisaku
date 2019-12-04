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

//距離測定変数
	//X方向
	int m_Gene_distance_X; //発電機距離測定変数
	int m_END_distance_X; //敵無力化装置距離測定変数
	int m_Gene2_distance_X; //発電機2距離測定変数
	int m_END2_distance_X; //敵無力化装置2距離測定変数
	int m_MND_distance_X; //対ミーム実態無力化装置距離測定変数
	int m_Tool_distance_X; //ツールボックス距離測定変数
	//Y方向
	int m_Gene_distance_Y; //発電機距離測定変数
	int m_END_distance_Y; //敵無力化装置距離測定変数
	int m_Gene2_distance_Y; //発電機2距離測定変数
	int m_END2_distance_Y; //敵無力化装置2距離測定変数
	int m_MND_distance_Y; //対ミーム実態無力化装置距離測定変数
	int m_Tool_distance_Y; //ツールボックス距離測定変数
	//斜め方向
	int m_Gene_distance_r; //発電機距離測定変数
	int m_END_distance_r; //敵無力化装置距離測定変数
	int m_Gene2_distance_r; //発電機2距離測定変数
	int m_END2_distance_r; //敵無力化装置2距離測定変数
	int m_MND_distance_r; //対ミーム実態無力化装置距離測定変数
	int m_Tool_distance_r; //ツールボックス距離測定変数

};