#pragma once

#define SCREEN_W	640
#define SCREEN_H	448

#define VS_W 256
#define	VS_H 400
#define VS_X ((SCREEN_W - VS_W) / 2) // 画面中央になるように自動計算 (192)
#define VS_Y 48


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

