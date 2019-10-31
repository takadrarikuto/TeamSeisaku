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
	bool GetEve() { return m_Event_num; } //イベント変数取得用

	void SetTStop(bool stop_t) { m_Stop_flg = stop_t; }  //時間停止フラグ更新用
	void SetTStart(bool start_t) { m_Start_flg = start_t; } //測定開始フラグ更新用

	void SetTimeFlag(bool b) { m_flag_time = b; } 
private:
	int m_time;		//時間
	bool m_flag_time;//時間計測スタートフラグ
	bool m_Stop_flg; //計測停止フラグ
	bool m_Start_flg; //測定開始フラグ
	bool m_Event_num;  //イベント変数

};
