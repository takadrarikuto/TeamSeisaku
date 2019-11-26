#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：タイム
class CObjTime :public CObj
{
public:
	CObjTime() {};
	~CObjTime() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	bool GetTStop() { return m_Stop_flg; } //時間停止フラグ取得用
	bool GetTStart() { return m_Start_flg; } //測定開始フラグ取得用

	bool GetGenFlg() { return m_Gen_flg; } //発電機起動フラグ取得用
	bool GetENDFlg() { return m_END_flg; } //敵無力化装置フラグ取得用
	bool GetMNDFlg() { return m_MND_flg; } //ミーム実態無力化装置フラグ取得用

	void SetTStop(bool stop_t) { m_Stop_flg = stop_t; }  //時間停止フラグ設定用
	void SetTStart(bool start_t) { m_Start_flg = start_t; } //測定開始フラグ設定用

	void SetGenFlg(bool gen_f) { m_Gen_flg = gen_f; } //発電機起動フラグ設定用
	void SetENDFlg(bool end_f) { m_END_flg = end_f; } //敵無力化装置フラグ設定用
	void SetMNDFlg(bool mnd_f) { m_MND_flg = mnd_f; } //ミーム実態無力化装置フラグ設定用

	void SetTimeFlag(bool b) { m_flag_time = b; } 
private:
	int m_time;		//時間
	int m_time_event; //イベント開始時間
	int m_Event_Rand_num; //イベントランダム変数

	bool m_flag_time;//時間計測スタートフラグ
	bool m_Stop_flg; //計測停止フラグ
	bool m_Start_flg; //測定開始フラグ

	bool m_Gen_flg; //発電機起動フラグ
	bool m_END_flg; //敵無力化装置フラグ
	bool m_MND_flg; //ミーム実態無力化装置フラグ
	 
	int m_Time_CutBack_num; //タイム減少量
	int m_Time_CutBack_Gen_num_max; //タイム減少量(発電気イベント)最大値

};
