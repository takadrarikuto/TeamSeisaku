#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト :背景
class CObjTutoBg : public CObj
{
public:
	CObjTutoBg() {};
	~CObjTutoBg() {};

	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー


private:

};