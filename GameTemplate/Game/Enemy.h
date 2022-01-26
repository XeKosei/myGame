#pragma once
#include "EnemyMove.h"
#include "EnemySearchPlayer.h"
#include "EnemyChase.h"
#include "EnemyAttack.h"
#include "EnemyAnim.h"
#include "EnemyScream.h"
#include "EnemyFlinch.h"
#include "EnemyStress.h"
#include "EnemyVigilant.h"
#include "EnemyVoice.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; }

	namespace nsEnemy
	{
		class Enemy : public IGameObject
		{
		public:
			~Enemy();
			bool Start();
			void Update();

			//�G�l�~�[�̏��
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enState_Scream,
				enState_Flinch,
				enState_Petrifaction,
				enState_Suffer,
				enState_Vigilant,
				enStatesNum
			};

			/// @brief �����T���͈͂�ݒ�
			/// @param area �ݒ肷��͈�
			void SetIniSearchPos(EnemySearchPlayer::EnSearchArea area) { m_iniArea = area; }

			SkinModelRender* GetEnemyModel() { return m_enemyModel; }

			/// @brief �G�l�~�[�̃L�����R�����擾����B(EnemyChase�N���X�ŗ��p)
			/// @return �G�l�~�[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief �v���C���[��ݒ�
			/// @param pl �v���C���[
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief �v���C���[���擾
			/// @return �v���C���[
			nsPlayer::Player* GetPlayer() { return m_player; }

			/// @brief �X�e�[�W���擾
			/// @return �X�e�[�W
			nsBackGround::BackGround* GetBackGround() { return m_backGround; }

			EnEnemyStates GetEnemyState() { return m_enemyState; };

			/// @brief �G�l�~�[�̏�Ԃ�ݒ肷��B
			/// @param enState �G�l�~�[�̏��
			void SetEnemyState(EnEnemyStates enState) { if (m_enemyState != enState_Petrifaction) { m_enemyState = enState; } };

			/// @brief �����̏���
			void ExecuteClairvoyance();

			/// @brief �G�l�~�[�̍s���̏������~�߂邩�ǂ�����ݒ�
			/// @param flag true:�������~�߂� false:�~�߂Ȃ�
			void SetStopExecuteFlag(bool flag) { m_stopExecuteFlag = flag; }

			/// @brief �������~�߂Ă��邩�ǂ������擾
			/// @return �������~�߂Ă��邩�ǂ���
			bool GetStopExecuteFlag() { return m_stopExecuteFlag; }

			//�G�l�~�[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			EnemyMove* GetEnemyMove() { return &m_enemyMove; }
			EnemySearchPlayer* GetEnemySearchPlayer() { return &m_enemySearchPlayer; };
			EnemyChase* GetEnemyChase() { return &m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return &m_enemyAttack; };
			EnemyScream* GetEnemyScream() { return &m_enemyScream; }
			EnemyFlinch* GetEnemyFlinch() { return &m_enemyFlinch; }
			EnemyStress* GetEnemyStress() { return &m_enemyStress; }
			EnemyVigilant* GetEnemyVigilant() { return &m_enemyVigilant; }
			EnemyAnim* GetEnemyAnim() { return &m_enemyAnim; };
			EnemyVoice* GetEnemyVoice() { return &m_enemyVoice; }
		private:
			//�����ʒu
			Vector3 m_iniPos = Vector3::Zero;

			//���f��
			SkinModelRender* m_enemyModel = nullptr;
			SkinModelRenderEX* m_enemyModelEX = nullptr;
			//�L�����R��
			CharacterController m_charaCon;

			//�v���C���[
			nsPlayer::Player* m_player = nullptr;

			//�X�e�[�W
			nsBackGround::BackGround* m_backGround = nullptr;

			//�G�l�~�[�̏��
			EnEnemyStates m_enemyState = enState_SearchPlayer;

			//�G�l�~�[�̏����T���G���A
			EnemySearchPlayer::EnSearchArea m_iniArea = EnemySearchPlayer::enSearchArea_1;

			//�G�l�~�[�֘A
			EnemyMove m_enemyMove;
			EnemySearchPlayer m_enemySearchPlayer;
			EnemyChase m_enemyChase;
			EnemyAttack m_enemyAttack;
			EnemyScream m_enemyScream;
			EnemyFlinch m_enemyFlinch;
			EnemyStress m_enemyStress;
			EnemyVigilant m_enemyVigilant;
			EnemyAnim m_enemyAnim;
			EnemyVoice m_enemyVoice;

			//�������~�߂�t���O
			bool m_stopExecuteFlag = false;
		};
	}
}