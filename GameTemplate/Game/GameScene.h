#pragma once
#include "GameSceneConstant.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsFlashLight { class FlashLight; }
	namespace nsBackGround { class BackGround; class SecretRoom; class DeadSkeleton; }
	namespace nsEnemy { class Enemy; }
	namespace nsGimmick { class ChandelierManager; class Door;  class EyeWall; }
	namespace nsItem { class ItemKey; class ItemFlashLightParts; class ItemTranquilizer; 
	class ItemBattery; class ItemMessagePaper;}

	namespace nsGameScene
	{
		class GameOver;
		class GameClear;

		using namespace nsGameSceneConstant;

		class GameScene : public IGameObject
		{
		public:
			enum EnGameSteps
			{
				enGameStep_01,
				enGameStep_02,
				enGameStep_03,
				enGameStep_04,
				enGameStep_05,
				enGameStep_06,
				enGameStep_07,
				enGameStep_08,
				enGameStep_09,
				enGameStep_GameOver,
				enGameStep_GameClear,
				enGameStep_num
			};

			~GameScene();
			bool Start();
			void Update();

			void GameManagement();

			//�G�ɒǂ��������Ă���Ƃ��̎���BGM
			void EnemyChaseBGM();

			void ExecuteUpdateStep01();
			void ExecuteUpdateStep02();
			void ExecuteUpdateStep03();
			void ExecuteUpdateStep04();
			void ExecuteUpdateStep05();
			void ExecuteUpdateStep06();
			void ExecuteUpdateStep07();
			void ExecuteUpdateStep08();
			void ExecuteUpdateStep09();

			/// @brief �Q�[���i�s�����֐i�߂邩�ǂ����̃t���O
			/// @param flag �i�߂�:true �i�߂Ȃ�:false
			void SetCanGoNextStepFlag(bool flag) { m_canGoNextStepFlag = flag; };

		private:
			//�Q�[���I�[�o�[�N���X
			GameOver* m_gameOver = nullptr;
			//�Q�[���N���A�N���X
			GameClear* m_gameClear = nullptr;

			//�X�e�[�W
			nsBackGround::BackGround* m_backGround = nullptr;
			nsBackGround::SecretRoom* m_secretRoom = nullptr;
			nsBackGround::DeadSkeleton* m_deadSkeleton = nullptr;
			//�v���C���[
			nsPlayer::Player* m_player = nullptr;
			//�����d��
			nsFlashLight::FlashLight* m_flashLight = nullptr;
			//�G�l�~�[
			nsEnemy::Enemy* m_enemy[ENEMY_NUM] = { nullptr, nullptr, nullptr };
			//�f�B���N�V�������C�g
			DirectionLight* m_dirLig = nullptr;

			//�V�����f���A
			nsGimmick::ChandelierManager* m_chandelierManager = nullptr;
			//�h�A
			nsGimmick::Door* m_door[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
			//�ڂ̕t������
			nsGimmick::EyeWall* m_eyeWall[3] = { nullptr, nullptr, nullptr };
			//��
			nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
			nsItem::ItemKey* m_lastKey = nullptr;
			//�����d���̃p�[�c
			nsItem::ItemFlashLightParts* m_flashLightParts[3] = { nullptr, nullptr, nullptr };
			//���_�����
			nsItem::ItemTranquilizer* m_tranquilizer[10] = {
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr };

			//�d�r
			nsItem::ItemBattery* m_battery[13] = {
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr };

			//���b�Z�[�W�y�[�p�[
			nsItem::ItemMessagePaper* m_messagePaper[8] = {
				nullptr, nullptr, nullptr, nullptr, nullptr,
				nullptr, nullptr, nullptr
			};

			//�E�o����ʘH�̐�̃|�C���g���C�g
			PointLight* m_pointLight = nullptr;

			//Level m_level;

			//�`�F�C�X����BGM
			SoundSource* m_chaseBGM = nullptr;
			bool m_isChaseBGMPlaying = false;
			bool m_chaseBGMDeleteFlag = false;
			float m_chaseBGMVolume = 1.0f;

			//�Q�[���̐i�s�i�K
			EnGameSteps m_gameStep = enGameStep_03;
			bool m_canGoNextStepFlag = false;
		};
	}
}