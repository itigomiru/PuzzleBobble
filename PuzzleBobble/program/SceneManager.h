#pragma once

#define SCREEN_W	960
#define SCREEN_H	544

#define VS_X 280
#define VS_Y 50
#define VS_W 400
#define	VS_H 400


void SceneManagerInit();	//	初期化処理
void SceneManagerUpdate();	//	更新処理
void SceneManagerRender();	//	描画処理
void SceneManagerExit();	//	終了処理

//	各シーンの番号
enum {
	SCENE_TITLE,	//	０：タイトル
	SCENE_STAGE,	//	１：ステージ
	SCENE_RESULT,	//	２：リザルト（結果表示画面）
};

//	いろんなファイルで使う変数なので外部参照宣言しています
extern int scene_next;
