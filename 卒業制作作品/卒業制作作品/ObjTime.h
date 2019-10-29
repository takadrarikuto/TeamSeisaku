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

	bool GetTS() { return m_Stop_flg; } //時間停止フラグ取得用

	void SetTimeFlag(bool b) { m_flag_time = b; } 
private:
	int m_time;		//時間
	bool m_flag_time;//時間計測スタートフラグ
	bool m_Stop_flg; //計測停止フラグ
	bool m_Start_num;  //計測開始変数

};
