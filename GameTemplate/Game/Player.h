#pragma once
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{
		class PlayerMove;
		class PlayerCamera;		
		class PlayerAction;
		class PlayerHP;
		//class PlayerConstant;

		class Player : public IGameObject
		{
		public:
			~Player();
			bool Start();
			void Update();

			/// @brief プレイヤーのモデルの位置を設定する。(PlayerMoveクラスで利用)
			/// @param pos 設定する位置
			void SetPosition(Vector3 pos) { m_position = pos; m_playerModel->SetPosition(m_position); };
	
			/// @brief プレイヤーのモデルの位置を取得
			/// @return プレイヤーの位置
			Vector3 GetPosition() { return m_position; };

			/// @brief プレイヤーのモデルの回転を設定する。(PlayerMoveクラスで利用)
			/// @param qRot 設定する回転
			void SetRotation(Quaternion qRot) { m_playerModel->SetRotation(qRot); };

			void SetScale(Vector3  scale) { m_playerModel->SetScale(scale); };

			/// @brief プレイヤーのキャラコンを取得する。(PlayerMoveクラスで利用)
			/// @return プレイヤーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };

			//死んだかどうか(仮)
			void SetDeadFlag(bool isDead) { m_deadFlag = isDead; }

			PlayerMove* GetPlayerMove() { return m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return m_playerCamera; };
			PlayerAction* nsPlayerActionConstant() { return m_playerAction; };
			PlayerHP* GetPlayerHP() { return m_playerHP; };

		private:
			bool m_deadFlag = false;
			//プレイヤーの位置
			Vector3 m_position = { Vector3::Zero };

			//モデル
			SkinModelRender* m_playerModel = nullptr;
			//プレイヤーのキャラコン
			CharacterController m_charaCon;

			//アニメーション関連
			enum {
				enAnimationClip_Idle,
				enAnimationClip_walk,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};
			AnimationClip animationClips[enAnimationClip_num];

			//プレイヤー関係のクラス
			PlayerMove* m_playerMove = nullptr;
			PlayerCamera* m_playerCamera = nullptr;
			PlayerAction* m_playerAction = nullptr;
			PlayerHP* m_playerHP = nullptr;

			//懐中電灯
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}