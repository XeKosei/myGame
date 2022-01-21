
#include "stdafx.h"
#include "system/system.h" 
#include "Test.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResourceBankManager.h"
namespace
{
	const Vector3 LIGHTCAMERA_POSITION = { 1000.0f, 1000.0f,1000.0f };
	const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
	const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
	const float LIGHTCAMERA_WIDTH = 3000.0f;
	const float LIGHTCAMERA_HEIGHT = 3000.0f;
	const int CAMERA_FAR = 5000000;
}

void PreLoad();
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

	//���\�[�X�}�l�[�W���̃C���X�^���X���쐬
	ResourceBankManager::CreateInstance();
	PreLoad();

	//���C�g�}�l�[�W���[�̃C���X�^���X���쐬
	nsHikageri::LightManager::CreateInstance();
	nsHikageri::LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
	nsHikageri::LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
	nsHikageri::LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
	nsHikageri::LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);//enUpdateProjMatrixFunc_Perspective);
	nsHikageri::LightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
	nsHikageri::LightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);

	for (int no = 0; no < 3; no++)
	{
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition({ 0.0f,0.0f,100.0f }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget({ 0.0f,0.0f,0.0f }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraUp({ Vector3::AxisX }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective, no);//enUpdateProjMatrixFunc_Perspective);
		nsHikageri::LightManager::GetInstance()->SetIsFlashLightSwitchOn(false, no);
	}

	nsHikageri::PostEffectManager::CreateInstance();
	//�u���[���t���O�A�V���h�E�t���O�̏���
	nsHikageri::PostEffectManager::GetInstance()->Init(true, true);

	//Test* testScene = NewGO<Test>(0, "testScene");
	//nsHikageri::nsGameScene::GameScene* gameScene = NewGO<nsHikageri::nsGameScene::GameScene>(0, "gameScene");
	nsHikageri::nsTitleScene::TitleScene* titleScene = NewGO<nsHikageri::nsTitleScene::TitleScene>(0, "titleScene");

	// �T�E���h�G���W���̃C���X�^���X���쐬����B
	nsHikageri::SoundEngine::CreateInstance();
	nsHikageri::SoundEngine::GetInstance()->Init();

	EffectEngine::CreateInstance();

	// �V���h�E�}�b�v��\�����邽�߂̃X�v���C�g������������
	SpriteInitData spriteInitData;
	spriteInitData.m_textures[0] = &nsHikageri::PostEffectManager::GetInstance()->GetSpotLightMap(2);
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

		sprite.Update({ FRAME_BUFFER_W / -2.04f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
		//sprite.Draw(renderContext);

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		nsHikageri::LightManager::GetInstance()->UpdateEyePos();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

void PreLoad()
{
	//���f���̎��O���[�h
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/RedKey.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/BlueKey.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/GreenKey.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/YellowKey.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/PurpleKey.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/WhiteKey.tkm");

	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/RedDoor.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/BlueDoor.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/GreenDoor.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/YellowDoor.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/PurpleDoor.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/WhiteDoor.tkm");

	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/Enemy.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/FlashLight.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/FlashLightParts.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/Battery.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/Medicine.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/Paper.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/chandelier.tkm");

	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/StageTest.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/SecretRoom.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/EyeWall.tkm");
	nsHikageri::SkinModelRender::PreLoadModel("Assets/modelData/FakeWall.tkm");
}

