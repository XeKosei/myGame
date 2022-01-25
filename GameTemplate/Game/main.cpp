
#include "stdafx.h"
#include "system/system.h" 
#include "Test.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ResourceBankManager.h"
namespace
{
	//const Vector3 LIGHTCAMERA_POSITION = { 1000.0f, 1000.0f,1000.0f };
	//const Vector3 LIGHTCAMERA_TARGET = { 0,0,0 };
	//const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
	//const float LIGHTCAMERA_WIDTH = 3000.0f;
	//const float LIGHTCAMERA_HEIGHT = 3000.0f;
	//const int CAMERA_FAR = 5000000;
}

void PreLoad();
void LoadSound(const nsHikageri::WNameKey filePath);
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

	// �T�E���h�G���W���̃C���X�^���X���쐬����B
	nsHikageri::SoundEngine::CreateInstance();
	nsHikageri::SoundEngine::GetInstance()->Init();

	//���\�[�X�}�l�[�W���̃C���X�^���X���쐬
	ResourceBankManager::CreateInstance();
	PreLoad();

	//���C�g�}�l�[�W���[�̃C���X�^���X���쐬
	nsHikageri::LightManager::CreateInstance();

	//nsHikageri::LightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
	//nsHikageri::LightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
	//nsHikageri::LightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
	//nsHikageri::LightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);//enUpdateProjMatrixFunc_Perspective);
	//nsHikageri::LightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
	//nsHikageri::LightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);

	for (int no = 0; no < 3; no++)
	{
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition({ 0.0f,0.0f,100.0f }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget({ 0.0f,0.0f,0.0f }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraUp({ Vector3::AxisX }, no);
		nsHikageri::LightManager::GetInstance()->SetSpotLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective, no);//enUpdateProjMatrixFunc_Perspective);
		nsHikageri::LightManager::GetInstance()->SetIsFlashLightSwitchOn(false, no);
	}
	//�����d���̃X�|�b�g���C�g�J�����̕`�拗����ݒ�
	nsHikageri::LightManager::GetInstance()->SetSpotLightCameraFar(100000.0f, 0);

	nsHikageri::PostEffectManager::CreateInstance();
	//�u���[���t���O�A�V���h�E�t���O�̏���
	nsHikageri::PostEffectManager::GetInstance()->Init(true, true);

	//Test* testScene = NewGO<Test>(0, "testScene");
	nsHikageri::nsGameScene::GameScene* gameScene = NewGO<nsHikageri::nsGameScene::GameScene>(0, "gameScene");
	//nsHikageri::nsTitleScene::TitleScene* titleScene = NewGO<nsHikageri::nsTitleScene::TitleScene>(0, "titleScene");

	EffectEngine::CreateInstance();

	// �V���h�E�}�b�v��\�����邽�߂̃X�v���C�g������������
	//SpriteInitData shadowMapDipData;
	//shadowMapDipData.m_textures[0] = &nsHikageri::PostEffectManager::GetInstance()->GetSpotLightMap(2);
	//shadowMapDipData.m_fxFilePath = "Assets/shader/sprite.fx";
	//shadowMapDipData.m_width = 256;
	//shadowMapDipData.m_height = 256;
	//Sprite shadowMapDisp;
	//shadowMapDisp.Init(shadowMapDipData);
	
	g_camera3D->SetPosition({0.0f, 300.0f, -1500.0f});
	g_camera3D->SetFar(100000.0f);
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

		//shadowMapDisp.Update({ FRAME_BUFFER_W / -2.04f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
		//shadowMapDisp.Draw(renderContext);

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

	//Sound�̎��O���[�h
	LoadSound(L"Assets/sound/UseItemTranquilizer.wav");
	LoadSound(L"Assets/sound/UseItemKey.wav");
	LoadSound(L"Assets/sound/UseItemBattery.wav");
	LoadSound(L"Assets/sound/TitleGameStart.wav");
	LoadSound(L"Assets/sound/TitleDisp.wav");
	LoadSound(L"Assets/sound/TitleBGM.wav");
	LoadSound(L"Assets/sound/StrobeFlashWaitShot.wav");
	LoadSound(L"Assets/sound/StrobeFlashShot.wav");
	LoadSound(L"Assets/sound/StrobeFlashCharged.wav");
	LoadSound(L"Assets/sound/StrobeFlashCharge.wav");
	LoadSound(L"Assets/sound/ReadStart.wav");
	LoadSound(L"Assets/sound/ReadEnd.wav");
	LoadSound(L"Assets/sound/MedousaEyeWaitShot.wav");
	LoadSound(L"Assets/sound/MedousaEyeCharge.wav");
	LoadSound(L"Assets/sound/Heartbeat4.wav");
	LoadSound(L"Assets/sound/Heartbeat3.wav");
	LoadSound(L"Assets/sound/Heartbeat2.wav");
	LoadSound(L"Assets/sound/Heartbeat1.wav");
	LoadSound(L"Assets/sound/Heartbeat0.wav");
	LoadSound(L"Assets/sound/GetItemTranquilizer.wav");
	LoadSound(L"Assets/sound/GetItemKey.wav");
	LoadSound(L"Assets/sound/GetItemBattery.wav");
	LoadSound(L"Assets/sound/GetFlashLightParts.wav");
	LoadSound(L"Assets/sound/GameOver.wav");
	LoadSound(L"Assets/sound/GameClear.wav");
	LoadSound(L"Assets/sound/FootStep2.wav");
	LoadSound(L"Assets/sound/FootStep1.wav");
	LoadSound(L"Assets/sound/FootStep0.wav");
	LoadSound(L"Assets/sound/FlashLightSwitch.wav");
	LoadSound(L"Assets/sound/FlashLightBreak.wav");
	LoadSound(L"Assets/sound/EyeWall.wav");
	LoadSound(L"Assets/sound/EnemySuffer.wav");
	LoadSound(L"Assets/sound/EnemySlowMove.wav");
	LoadSound(L"Assets/sound/EnemyScream.wav");
	LoadSound(L"Assets/sound/EnemyFoundPlayer.wav");
	LoadSound(L"Assets/sound/EnemyFootStep.wav");
	LoadSound(L"Assets/sound/EnemyFlinch.wav");
	LoadSound(L"Assets/sound/EnemyDefault.wav");
	LoadSound(L"Assets/sound/EnemySuffer.wav");
	LoadSound(L"Assets/sound/EnemyChase.wav");
	LoadSound(L"Assets/sound/EnemyBite.wav");
	LoadSound(L"Assets/sound/EnemyAttack.wav");
	LoadSound(L"Assets/sound/EnemySuffer.wav");
	LoadSound(L"Assets/sound/DoorOpen.wav");
	LoadSound(L"Assets/sound/DoorLocked.wav");
	LoadSound(L"Assets/sound/DoorClose.wav");
	LoadSound(L"Assets/sound/Clairvoyance.wav");
	LoadSound(L"Assets/sound/ChaseBGM.wav");
}

//Sound�̃��[�h
void LoadSound(const nsHikageri::WNameKey filePath)
{
	nsHikageri::SoundSource* ss = NewGO<nsHikageri::SoundSource>(0);
	ss->Init(filePath);
	DeleteGO(ss);
}



