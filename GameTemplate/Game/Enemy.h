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

			//エネミーの状態
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

			void SetIniPos(Vector3 iniPos) { m_iniPos = iniPos; }

			SkinModelRender* GetEnemyModel() { return m_enemyModel; }

			/// @brief エネミーのキャラコンを取得する。(EnemyChaseクラスで利用)
			/// @return エネミーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief プレイヤーを設定
			/// @param pl プレイヤー
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief プレイヤーを取得
			/// @return プレイヤー
			nsPlayer::Player* GetPlayer() { return m_player; }

			/// @brief ステージを取得
			/// @return ステージ
			nsBackGround::BackGround* GetBackGround() { return m_backGround; }

			EnEnemyStates GetEnemyState() { return m_enemyState; };

			/// @brief エネミーの状態を設定する。
			/// @param enState エネミーの状態
			void SetEnemyState(EnEnemyStates enState) { if (m_enemyState != enState_Petrifaction) { m_enemyState = enState; } };

			/// @brief 透視の処理
			void ExecuteClairvoyance();

			//エネミー関係のインスタンスにアクセスする
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
			//初期位置
			Vector3 m_iniPos = Vector3::Zero;

			//モデル
			SkinModelRender* m_enemyModel = nullptr;
			SkinModelRenderEX* m_enemyModelEX = nullptr;
			//キャラコン
			CharacterController m_charaCon;

			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//ステージ
			nsBackGround::BackGround* m_backGround = nullptr;

			//エネミーの状態
			EnEnemyStates m_enemyState = enState_SearchPlayer;

			//エネミー関連
			EnemyMove m_enemyMove;
			EnemySearchPlayer m_enemySearchPlayer;
			EnemyChase m_enemyChase;
			EnemyAttack m_enemyAttack;
			EnemyScream m_enemyScream;
			EnemyFlinch m_enemyFlinch;
			EnemyStress m_enemyStress;
			EnemyVigilant m_enemyVigilant;
			EnemyAnim m_enemyAnim ;
			EnemyVoice m_enemyVoice;
		};
	}
}