#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;
		using namespace nsEnemyConstant;

		bool EnemySearchPlayer::Start()
		{
			SetSearchPos(enSearchArea_2);

			CalcNextSearchPos();

			int m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;

			//初期位置を指定
			m_enemy->GetEnemyMove()->SetPosition(m_searchPos[0]);

			return true;
		}

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//移動処理(仮)
			Search();

			//エネミーの位置からプレイヤーの位置へのベクトルを求める
			Vector3 toPlayerDis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			
			if (toPlayerDis.Length() <= ENEMY_SEARCH_DIS)
			{
				m_calcLineHitModelConstant--;

				if (m_calcLineHitModelConstant <= 0)
				{
					m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;

					Vector3 toPlayerDir = toPlayerDis;
					toPlayerDir.Normalize();

					Vector3 startPos = m_enemy->GetEnemyMove()->GetPosition();
					startPos.y += 10.0f;	//地面との接触をなくすために少し浮かせる
					Vector3 endPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
					endPos.y += 10.0f;
					Vector3 hitPos = Vector3::Zero;

					//エネミーの向きとの内積が一定以上なら、プレイヤーを追いかけ始める。
					if (Dot(toPlayerDir, m_enemy->GetEnemyMove()->GetDirection()) >= 0.7f
						&& m_enemy->GetBackGround()->GetStageModel()->isLineHitModel(startPos, endPos, hitPos) == false)
					{
						m_calcLineHitModelConstant = CALC_LINEHITMODEL_COSNTANT;

						startPos.y -= 10.0f;
						endPos.y -= 10.0f;
						m_enemy->SetEnemyState(Enemy::enState_Scream);
						m_enemy->GetEnemyMove()->RouteSearch(startPos, endPos);
						m_enemy->GetEnemyMove()->SetMoveState(EnemyMove::enMoveState_Straight);
					}
				}
			}
		}

		void EnemySearchPlayer::Search()
		{
			//指定した二か所の位置を往復する処理

			//エネミーの移動の速さを設定
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_WALK_SPEED);

			//エネミーの位置がほぼターゲットと一緒になったら、
			if ((m_enemy->GetEnemyMove()->GetTarget() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= 5.0f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Vigilant);
			}
		}

		void EnemySearchPlayer::CalcNextSearchPos()
		{
			//乱数から、次のターゲット位置を決める。
			int nextTargetSearchPosNo = rand() % (m_searchPos.size() - 1);
			if (nextTargetSearchPosNo >= m_targetSearchPosNo)
			{
				nextTargetSearchPosNo++;
			}

			m_enemy->GetEnemyMove()->RouteSearch(m_searchPos[m_targetSearchPosNo], m_searchPos[nextTargetSearchPosNo]);

			m_targetSearchPosNo = nextTargetSearchPosNo;
		}
		void EnemySearchPlayer::SetSearchPos(EnSearchArea searchArea)
		{
			m_searchArea = searchArea;

			std::vector<Vector3>::iterator it;
			while(m_searchPos.size() > 0)
			{
				it = m_searchPos.begin(),			
				m_searchPos.erase(it);
			}

			switch (m_searchArea)
			{
			case enSearchArea_1:
				PushSearchPos({ -2600.0f,0.0f,2400.0f });
				PushSearchPos({ -3400.0f,0.0f,2400.0f });
				PushSearchPos({ -2600.0f,0.0f,1600.0f });
				PushSearchPos({ -3400.0f,0.0f,800.0f });
				PushSearchPos({ -1400.0f,0.0f,-2000.0f });
				break;
			case enSearchArea_2:
				PushSearchPos({ -9400.0f,0.0f,0.0f });
				PushSearchPos({ -9400.0f,0.0f,3200.0f });
				PushSearchPos({ -6200.0f,0.0f,3200.0f });
				PushSearchPos({ -6200.0f,0.0f,0.0f });
				PushSearchPos({ -7000.0f,0.0f,2400.0f });
				PushSearchPos({ -8600.0f,0.0f,2400.0f });
				PushSearchPos({ -7000.0f,0.0f,800.0f });
				PushSearchPos({ -8600.0f,0.0f,800.0f });
				PushSearchPos({ -9400.0f,0.0f,4800.0f });
				PushSearchPos({ -6600.0f,0.0f,4800.0f });
				PushSearchPos({ -6200.0f,0.0f,4400.0f });
				break;
			case enSearchArea_3:
				PushSearchPos({ -4600,0.0f,6000.0f });
				PushSearchPos({ -4600,0.0f,7200.0f });
				PushSearchPos({ -1400,0.0f,6000.0f });
				PushSearchPos({ -1400,0.0f,7200.0f });
				PushSearchPos({ -3000,0.0f,6600.0f });
				break;
			default:
				break;
			}
			m_enemy->GetEnemyMove()->SetPosition(m_searchPos[0]);
			SetTargetSearchPosNo(0);	//次に向かうSearchPosをリセット
		}
	}
}