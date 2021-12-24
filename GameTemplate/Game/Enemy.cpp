#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
#include "BackGround.h"
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
			//モデル生成より先に初期化が必要なクラス
			m_enemyAnim.Init(this);

			//モデルを作成
			m_enemyModel = NewGO<SkinModelRender>(0);
			m_enemyModel->SetMakeSkinModelRenderEX(true);
			m_enemyModel->Init("Assets/modelData/Enemy.tkm", "Assets/modelData/Enemy.tks", m_enemyAnim.GetAnimationClip(), m_enemyAnim.GetAnimationClipNum());
			//m_enemyModel->SetPosition(m_searchPos[0]);
			m_enemyModel->SetScale(INI_ENEMY_SCALE);

			//キャラコンを設定
			m_charaCon.Init(
				ENEMY_MODEL_WIDTH,	//半径
				ENEMY_MODEL_HEIGHT,	//高さ
				Vector3::Zero//初期位置
			);

			m_backGround = FindGO<nsBackGround::BackGround>("backGround");
			//エネミー関連のインスタンスを作成
			m_enemyMove.Init(this);
			m_enemySearchPlayer.Init(this);
			m_enemyChase.Init(this);
			m_enemyAttack.Init(this);
			m_enemyScream.Init(this);
			m_enemyFlinch.Init(this);
			m_enemyStress.Init(this);
			m_enemyVigilant.Init(this);
			m_enemyVoice.Init(this);

			//m_enemyStates = enState_SearchPlayer;

			return true;
		}
		void Enemy::Update()
		{
			//エネミー関連の処理
			switch (m_enemyState)
			{
			case enState_SearchPlayer:
				m_enemySearchPlayer.ExecuteUpdate();
				m_enemyStress.ExecuteUpdate();
				m_enemyMove.ExecuteUpdate();
				break;
			case enState_Chase:
				m_enemyChase.ExecuteUpdate();
				m_enemyStress.ExecuteUpdate();
				m_enemyMove.ExecuteUpdate();
				break;
			case enState_Attack:
				m_enemyAttack.ExecuteUpdate();
				break;
			case enState_Scream:
				m_enemyScream.ExecuteUpdate();
				m_enemyStress.ExecuteUpdate();
				break;
			case enState_Flinch:
				m_enemyFlinch.ExecuteUpdate();
				break;
			case enState_Petrifaction:
				m_enemyFlinch.Mineralization();
				break;
			case enState_Suffer:
				m_enemyStress.Suffer();
				break;
			case enState_Vigilant:
				m_enemyVigilant.ExecuteUpdate();
				break;
			default:
				break;
			}
			//アニメーション再生
			m_enemyAnim.ExecuteUpdate();
			//声
			m_enemyVoice.ExecuteUpdate();

			//透視の処理
			ExecuteClairvoyance();
		}

		//透視の処理
		void Enemy::ExecuteClairvoyance()
		{
			if (m_player->GetFlashLight()->GetAbilityClairvoyance()->GetUseAbilityFlag())
			{
				m_enemyModel->SetClairvoyanceCasterFlag(true);
			}
			else
			{
				m_enemyModel->SetClairvoyanceCasterFlag(false);
			}
		}
	}
}