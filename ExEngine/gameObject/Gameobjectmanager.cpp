/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//�C���X�^���X�����łɍ���Ă���B
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
	//���S�t���O�����Ă���Q�[���I�u�W�F�N�g��j������B
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
	//�����G���W���̃A�b�v�f�[�g���Ăяo���B
	PhysicsWorld::GetInstance()->Update(1.0f/60.0f);
}
void GameObjectManager::ExecuteRender(RenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B

	//TODO:�b�菈���A�t���O�܂ߕʂ̌`�ɂ�����(�炵��)
	//�e���ɕ`���Ă��烂�f���ɕ`�����e��`�������̂Ő�ɃV���h�E�}�b�v�����B
	//nsHikageri::PostEffectManager::GetInstance()->ShadowRender(rc);

	////shadow
	//if (nsHikageri::PostEffectManager::GetInstance()->GetShadowFlag())
	//{
	//	rc.SetStep(RenderContext::eStep_RenderShadowMap);
	//	//ShadowRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
	//	for (auto& goList : m_gameObjectListArray) {
	//		for (auto& go : goList) {
	//			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetLightCamera());
	//		}
	//	}
	//}
	//nsHikageri::PostEffectManager::GetInstance()->EndShadowRender(rc);

	//�X�|�b�g���C�g�p�̃��f����`���B
	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 0);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap00);
	//SpotLightRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(0));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 0);

	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 1);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap01);
	//SpotLightRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(1));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 1);

	nsHikageri::PostEffectManager::GetInstance()->SpotLightRender(rc, 2);
	rc.SetStep(RenderContext::eStep_RenderSpotLightMap02);
	//SpotLightRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, nsHikageri::LightManager::GetInstance()->GetSpotLightCamera(2));
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndSpotLightRender(rc, 2);
	//�����܂ŃX�|�b�g���C�g�p

	//�����p�̃��f����`��
	nsHikageri::PostEffectManager::GetInstance()->ClairvoyanceRender(rc);
	rc.SetStep(RenderContext::eStep_RenderClairvoyanceMap);
	//ClairvoyanceRender�Ńr���[�|�[�g��ݒ肵�Ă���̂ł����Ńr���[�|�[�g�ݒ肵�Ȃ���OK(���Ԃ�)
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, g_camera3D);
		}
	}
	nsHikageri::PostEffectManager::GetInstance()->EndClairvoyanceRender(rc);
	

	//�|�X�g�G�t�F�N�g�p�BRender�O�̏���
	nsHikageri::PostEffectManager::GetInstance()->BeforeRender(rc);

	nsHikageri::LightManager::GetInstance()->UpdateEyePos();

	rc.SetStep(RenderContext::eStep_Render);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc, g_camera3D);
		}
	}

	// 1��ʃI�����[�̃G�t�F�N�g�X�V
	//EffectEngine::GetInstance()->Update(GameTime::GetInstance().GetFrameDeltaTime());
	//1��ʃI�����[�̃G�t�F�N�g�`��
	//EffectEngine::GetInstance()->Draw();

	//Level2D�p�@
	//���x��2D�͑S���X�v���C�g�Ȃ̂�ExecuteRender�ɂ͂���Ȃ��̂ł�?
	//����viewport���Z�b�g���Ȃ��Ɖ�ʂ������̂܂܂Ȃ̂ŃZ�b�g�͂��Ă݂�B
	/*{
		g_camera2D->SetWidth(g_graphicsEngine->GetFrameBufferWidth());

		rc.SetStep(RenderContext::eStep_Render);

		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->RenderWrapper(rc, g_camera3D);
			}
		}
	}*/

	//�|�X�g�G�t�F�N�g�p�BRender��̏���
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
	//Level2D�p
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