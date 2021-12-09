#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyChaseConstant;
		using namespace nsEnemyConstant;

		EnemyChase::~EnemyChase()
		{

		}

		void EnemyChase::Init(Enemy* enemy)
		{
			m_enemy = enemy;
			m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;
		}

		//Enemy.cpp��Update()�ŌĂяo������
		void EnemyChase::ExecuteUpdate()
		{
			if (m_isPlayerHidden == false)
			{
				Chase();
			}
			else
			{
				GoHiddenPos();
			}
			//���������ȓ��܂ŏk�܂�����A�U���Ɉڍs�B
			if ((m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= ENEMY_CAN_ATTACK_DIS
				&& m_enemy->GetPlayer()->GetPlayerState() == nsPlayer::Player::enState_Normal
				&& m_isPlayerHidden == false)
			{
				//�G�l�~�[�����݂���Ԃɂ���		
				m_enemy->SetEnemyState(Enemy::enState_Attack);
				//�v���C���[�����݂����Ԃɂ���
				m_enemy->GetPlayer()->SetPlayerState(nsPlayer::Player::enState_Bitten);
				//�v���C���[�����݂���Ă��鑊����A���̃G�l�~�[�ɐݒ�
				m_enemy->GetPlayer()->GetPlayerBitten()->SetEnemy(m_enemy);
				m_enemy->GetEnemyAttack()->Reset();
			}
		}

		void EnemyChase::Chase()
		{
			//�ړ����x���w��
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_DASH_SPEED);
			m_enemy->GetEnemyMove()->SetTargetPos(m_enemy->GetPlayer()->GetPlayerMove()->GetPosition());
			m_calcLineHitModelConstant--;

			if (m_calcLineHitModelConstant <= 0)
			{
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;

				Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();

				Vector3 startPos = m_enemy->GetEnemyMove()->GetPosition();
				startPos.y += 10.0f;	//�n�ʂƂ̐ڐG���Ȃ������߂ɏ�����������
				Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
				endPos.y += 10.0f;
				Vector3 hitPos = Vector3::Zero;

				//�v���C���[�����E�ɓ����Ă���Ȃ��
				if (toPlayerDis.Length() <= ENEMY_SEARCH_DIS && m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
				{
					startPos.y -= 10.0f;
					endPos.y -= 10.0f;
					m_enemy->GetEnemyMove()->SetTargetPos(endPos);
				}
				//�����Ă��Ȃ��Ȃ�o�H�T��
				else
				{
					startPos.y -= 10.0f;
					endPos.y -= 10.0f;
					m_enemy->GetEnemyMove()->RouteSearch(m_enemy->GetEnemyMove()->GetPosition(), endPos);
					m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_RouteSearch);
					m_isPlayerHidden = true;
				}
			}				
		}	

		void EnemyChase::GoHiddenPos()
		{
			m_calcLineHitModelConstant--;

			if (m_calcLineHitModelConstant <= 0)
			{
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;

				Vector3 startPos = m_enemy->GetEnemyMove()->GetPosition();
				startPos.y += 10.0f;	//�n�ʂƂ̐ڐG���Ȃ������߂ɏ�����������
				Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
				endPos.y += 10.0f;
				Vector3 hitPos = Vector3::Zero;

				//�v���C���[�����E�ɓ����Ă���Ȃ�΁A�Ăђǐ�
				if (m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
				{
					startPos.y -= 10.0f;
					endPos.y -= 10.0f;
					m_enemy->GetEnemyMove()->SetTargetPos(endPos);
					m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_Straight);
					m_isPlayerHidden = false;
				}
			}

			//�T���ꏊ�Ƃقړ����ʒu�ɕt������
			if ((m_enemy->GetEnemyMove()->GetTargetPos() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= 5.0f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Vigilant);
				m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_RouteSearch);
				m_isPlayerHidden = false;
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;
			}
		}
	}
}