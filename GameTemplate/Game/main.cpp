
#include "stdafx.h"
#include "system/system.h" 
#include "Test.h"

namespace
{
	const Vector3 LIGHTCAMERA_POSITION = { 0.0f, 600.0f,0.0f };
	const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
	const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
	const float LIGHTCAMERA_WIDTH = 10000.0f;
	const float LIGHTCAMERA_HEIGHT = 10000.0f;
	const int CAMERA_FAR = 100000;
}

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//���C�g�}�l�[�W���[�̃C���X�^���X���쐬
	LightManager::CreateInstance();
	LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
	LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
	LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
	LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);//enUpdateProjMatrixFunc_Perspective);
    //LightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
	//LightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);

	PostEffectManager::CreateInstance();
	//�u���[���t���O�A�V���h�E�t���O�̏���
	PostEffectManager::GetInstance()->Init(true, true);

	Test* testScene = NewGO<Test>(0, "testScene");

	// �V���h�E�}�b�v��\�����邽�߂̃X�v���C�g������������
	SpriteInitData spriteInitData;
	spriteInitData.m_textures[0] = &PostEffectManager::GetInstance()->GetShadowMap();
	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	spriteInitData.m_width = 256;
	spriteInitData.m_height = 256;

	Sprite sprite;
	sprite.Init(spriteInitData);

	g_camera3D->SetPosition({0.0f, 300.0f, -1500.0f});

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		//PostRender�̓X�v���C�g�A�t�H���g���A�G�t�F�N�g���󂯂Ȃ����̂�`�悷��
		GameObjectManager::GetInstance()->ExecutePostRender(renderContext);

		sprite.Update({ FRAME_BUFFER_W / -2.0f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
		sprite.Draw(renderContext);

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		LightManager::GetInstance()->UpdateEyePos();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

