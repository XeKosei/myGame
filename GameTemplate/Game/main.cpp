
#include "stdafx.h"
#include "system/system.h" 
#include "Test.h"

namespace
{
	const Vector3 LIGHTCAMERA_POSITION = { 0.0f, 2000.0f,0.0f };
	const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
	const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
	const float LIGHTCAMERA_WIDTH = 2000.0f;
	const float LIGHTCAMERA_HEIGHT = 2000.0f;
	const int CAMERA_FAR = 100000;
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//ライトマネージャーのインスタンスを作成
	LightManager::CreateInstance();
	LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
	LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
	LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
	LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective); //enUpdateProjMatrixFunc_Ortho
    LightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
	LightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);

	PostEffectManager::CreateInstance();
	//ブルームフラグ、シャドウフラグの順番
	PostEffectManager::GetInstance()->Init(true, true);

	Test* testScene = NewGO<Test>(0, "testScene");

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		//PostRenderはスプライト、フォント等、エフェクトを受けないものを描画する
		GameObjectManager::GetInstance()->ExecutePostRender(renderContext);

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		
		LightManager::GetInstance()->UpdateEyePos();

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

