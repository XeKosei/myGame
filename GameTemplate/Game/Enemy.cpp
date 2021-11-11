#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

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
			m_enemyMove = NewGO<EnemyMove>(0);
			m_enemyMove->SetEnemy(this);
			m_enemySearchPlayer = NewGO<EnemySearchPlayer>(0);
			m_enemySearchPlayer->SetEnemy(this);
			m_enemySearchPlayer->SetMovePos(m_searchPos[0], m_searchPos[1]);//仮
			m_enemyChase = NewGO<EnemyChase>(0);
			m_enemyChase->SetEnemy(this);
			m_enemyAttack = NewGO<EnemyAttack>(0);
			m_enemyAttack->SetEnemy(this);
			m_enemyScream = NewGO<EnemyScream>(0);
			m_enemyScream->SetEnemy(this);
			m_enemyFlinch = NewGO<EnemyFlinch>(0);
			m_enemyFlinch->SetEnemy(this);
			m_enemyStress = NewGO<EnemyStress>(0);
			m_enemyStress->SetEnemy(this);
			m_enemyAnim = NewGO<EnemyAnim>(0);
			m_enemyAnim->SetEnemy(this);

			//m_enemyStates = enState_SearchPlayer;
			
			//モデルを作成
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->SetMakeSkinModelRenderEX(true);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks",m_enemyAnim->GetAnimationClip(), m_enemyAnim->GetAnimationClipNum());
			m_enemyModel->SetPosition(m_searchPos[0]);
			m_enemyModel->SetScale(INI_ENEMY_SCALE);

			return true;
		}
		void Enemy::Update()
		{
			//エネミー関連の処理
			switch (m_enemyState)
			{
			case enState_SearchPlayer:
				m_enemySearchPlayer->ExecuteUpdate();
				m_enemyMove->ExecuteUpdate();
				break;
			case enState_Chase:
				m_enemyChase->ExecuteUpdate();
				m_enemyMove->ExecuteUpdate();
				m_enemyStress->ExecuteUpdate();
				break;
			case enState_Attack:
				m_enemyAttack->ExecuteUpdate();
				break;
			case enState_Scream:
				m_enemyScream->ExecuteUpdate();
				break;
			case enState_Flinch:
				m_enemyFlinch->ExecuteUpdate();
				break;
			case enState_Suffer:
				m_enemyStress->Suffer();
				break;
			default:
				break;
			}
			//アニメーション再生
			m_enemyAnim->ExecuteUpdate();
		}
	}
}