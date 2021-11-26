/*!
 *@brief	CGameObjectのマネージャ
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//インスタンスがすでに作られている。
		std::abort();
	}
	m_instance = this;
}
GameObjectManager::~GameObjectManager()
{
	m_instance = nullptr;
}
void GameObjectManager::ExecuteUpdate()
{	
	//死亡フラグがついているゲームオブジェクトを破棄する。
	for (auto& goList : m_gameObjectListArray) {
		goList.remove_if([&](IGameObject* go) {	
			if (go->IsDead()) {
				delete go;
				return true;
			}
			return false;	 
		});
	}

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->StartWrapper();
		}
	}


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->UpdateWrapper();
		}
	}
	//物理エンジンのアップデートを呼び出す。
	PhysicsWorld::GetInstance()->Update(1.0f/60.0f);
}
void GameObjectManager::ExecuteRender(RenderContext& rc)
{
	//レンダラーを変更するならここを改造していくと良い。

	//TODO:暫定処理、フラグ含め別の形にしたい(らしい)
	//影を先に描いてからモデルに描いた影を描き足すので先にシャドウマップを作る。
	//nsHikageri::PostEffectManager::GetInstance()->ShadowRender(rc);

	////shadow
	//if (nsHikageri::PostEffectManager::GetInstance()->GetShadowFlag())
	//{
	//	rc.SetStep(RenderContext::eStep_RenderShadowMap);
	//	//ShadowRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
	//	for (auto& goList : m_gameObjectListArray) {
	//		for (auto& go : goList) {
	//			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetLightCamera());
	//		}
	//	}
	//}
	//nsHikageri::PostEffectManager::GetInstance()->EndShadowRender(rc);

	//スポットライト用のモデルを描く。
	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 0);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap00);
	//SpotLightRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(0));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 0);

	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 1);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap01);
	//SpotLightRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(1));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 1);

	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 2);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap02);
	//SpotLightRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(2));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 2);
	//ここまでスポットライト用

	//透視用のモデルを描く
	nsHikageri::PostEffectManager::GetInstance()->ClairvoyanceRender(rc);
	rc.SetStep(RenderContext::eStep_RenderClairvoyanceMap);
	//ClairvoyanceRenderでビューポートを設定しているのでここでビューポート設定しなくてOK(たぶん)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, g_camera3D);
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndClairvoyanceRender(rc);
	

	//ポストエフェクト用。Render前の処理
	nsHikageri::PostEffectManager::GetInstance()->BeforeRender(rc);

	nsHikageri::LightManager::GetInstance()->UpdateEyePos();

	rc.SetStep(RenderContext::eStep_Render);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, g_camera3D);
		}
	}

	// 1画面オンリーのエフェクト更新
	//EffectEngine::GetInstance()->Update(GameTime::GetInstance().GetFrameDeltaTime());
	//1画面オンリーのエフェクト描画
	//EffectEngine::GetInstance()->Draw();

	//Level2D用　
	//レベル2Dは全部スプライトなのでExecuteRenderにはいらないのでは?
	//だがviewportをセットしないと画面が半分のままなのでセットはしてみる。
	/*{
		g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

		rc.SetStep(RenderContext::eStep_Render);

		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->RenderWrapper(rc, g_camera3D);
			}
		}
	}*/

	//ポストエフェクト用。Render後の処理
	nsHikageri::PostEffectManager::GetInstance()->AfterRender(rc);
}

void GameObjectManager::ExecutePostRender(RenderContext& rc)
{
	if (m_rc == nullptr) {
		m_rc = &rc;
	}

	rc.SetStep(RenderContext::eStep_Render);

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->PostRenderWrapper(rc);
		}
	}
	//Level2D用
	{
		g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

		rc.SetStep(RenderContext::eStep_Render);

		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->PostRenderWrapper(rc);
			}
		}
	}
}