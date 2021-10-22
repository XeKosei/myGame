#include "stdafx.h"
#include "EnemyInclude.h"
#include "Player.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyConstant;

		Enemy::~Enemy()
		{
			DeleteGO(m_enemyModel);
		}
		bool Enemy::Start()
		{		
			//キャラコンを設定
			m_charaCon.Init(
				ENEMY_MODEL_WIDTH,	//半径
				ENEMY_MODEL_HEIGHT,	//高さ
				m_searchPos[0]//初期位置
			);		

			//エネミー関連のインスタンスを作成
			m_enemySearchPlayer = NewGO<EnemySearchPlayer>(0);
			m_enemySearchPlayer->SetEnemy(this);
			m_enemySearchPlayer->SetMovePos(m_searchPos[0], m_searchPos[1]);
			m_enemyChase = NewGO<EnemyChase>(0);
			m_enemyChase->SetEnemy(this);
			m_enemyAttack = NewGO<EnemyAttack>(0);
			m_enemyAttack->SetEnemy(this);
			m_enemyAnim = NewGO<EnemyAnim>(0);
			m_enemyAnim->SetEnemy(this);

			//m_enemyStates = enState_SearchPlayer;
			
			//モデルを作成
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks",m_enemyAnim->GetAnimationClip(), m_enemyAnim->GetAnimationClipNum());
			m_enemyModel->SetPosition(m_searchPos[0]);

			return true;
		}
		void Enemy::Update()
		{
			//エネミー関連の処理
			switch (m_enemyState)
			{
			case enState_SearchPlayer:
				m_enemySearchPlayer->ExecuteUpdate();
				break;
			case enState_Chase:
				m_enemyChase->ExecuteUpdate();
				break;
			case enState_Attack:
				m_enemyAttack->ExecuteUpdate();
				break;
			default:
				break;
			}
			//アニメーション再生
			m_enemyAnim->ExecuteUpdate();

		}
	}
}