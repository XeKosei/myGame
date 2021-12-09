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

		//Enemy.cppのUpdate()で呼び出す処理
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
			//距離が一定以内まで縮まったら、攻撃に移行。
			if ((m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= ENEMY_CAN_ATTACK_DIS
				&& m_enemy->GetPlayer()->GetPlayerState() == nsPlayer::Player::enState_Normal
				&& m_isPlayerHidden == false)
			{
				//エネミーを噛みつき状態にする		
				m_enemy->SetEnemyState(Enemy::enState_Attack);
				//プレイヤーを噛みつかれ状態にする
				m_enemy->GetPlayer()->SetPlayerState(nsPlayer::Player::enState_Bitten);
				//プレイヤーが噛みつかれている相手を、このエネミーに設定
				m_enemy->GetPlayer()->GetPlayerBitten()->SetEnemy(m_enemy);
				m_enemy->GetEnemyAttack()->Reset();
			}
		}

		void EnemyChase::Chase()
		{
			//移動速度を指定
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_DASH_SPEED);
			m_enemy->GetEnemyMove()->SetTargetPos(m_enemy->GetPlayer()->GetPlayerMove()->GetPosition());
			m_calcLineHitModelConstant--;

			if (m_calcLineHitModelConstant <= 0)
			{
				m_calcLineHitModelConstant = CALC_LINEHITMODEL_INTERVAL;

				Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();

				Vector3 startPos = m_enemy->GetEnemyMove()->GetPosition();
				startPos.y += 10.0f;	//地面との接触をなくすために少し浮かせる
				Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
				endPos.y += 10.0f;
				Vector3 hitPos = Vector3::Zero;

				//プレイヤーが視界に入っているならば
				if (toPlayerDis.Length() <= ENEMY_SEARCH_DIS && m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
				{
					startPos.y -= 10.0f;
					endPos.y -= 10.0f;
					m_enemy->GetEnemyMove()->SetTargetPos(endPos);
				}
				//入っていないなら経路探索
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
				startPos.y += 10.0f;	//地面との接触をなくすために少し浮かせる
				Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
				endPos.y += 10.0f;
				Vector3 hitPos = Vector3::Zero;

				//プレイヤーが視界に入っているならば、再び追跡
				if (m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
				{
					startPos.y -= 10.0f;
					endPos.y -= 10.0f;
					m_enemy->GetEnemyMove()->SetTargetPos(endPos);
					m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_Straight);
					m_isPlayerHidden = false;
				}
			}

			//探す場所とほぼ同じ位置に付いたら
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