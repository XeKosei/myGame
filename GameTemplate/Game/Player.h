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
		class PlayerBitten;

		class Player : public IGameObject
		{
		public:
			enum EnPlayerStates
			{
				enState_Normal,
				enState_Bitten,
				enState_Dead,
				enStatesNum
			};


			~Player();
			bool Start();
			void Update();

			/// @brief プレイヤーのモデルのインスタンスを取得する。
			/// @return プレイヤーのモデルのインスタンス
			SkinModelRender* GetPlayerModel() { return m_playerModel; }

			/// @brief プレイヤーのキャラコンを取得する。(PlayerMoveクラスで利用)
			/// @return プレイヤーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };

			//プレイヤーの状態を設定
			void SetPlayerState(EnPlayerStates plState) { m_playerState = plState; }
			//プレイヤーの状態を取得
			EnPlayerStates GetPlayerState() { return m_playerState; }


			//プレイヤー関係のインスタンスにアクセスする
			PlayerMove* GetPlayerMove() { return m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return m_playerCamera; };
			PlayerAction* nsPlayerActionConstant() { return m_playerAction; };
			PlayerHP* GetPlayerHP() { return m_playerHP; };
			PlayerBitten* GetPlayerBitten() { return m_playerBitten; }
		private:
			//モデル
			SkinModelRender* m_playerModel = nullptr;
			//プレイヤーのキャラコン
			CharacterController m_charaCon;

			//プレイヤー関係のクラス
			PlayerMove* m_playerMove = nullptr;
			PlayerCamera* m_playerCamera = nullptr;
			PlayerAction* m_playerAction = nullptr;
			PlayerHP* m_playerHP = nullptr;
			PlayerBitten* m_playerBitten = nullptr;

			EnPlayerStates m_playerState = enState_Normal;

			//懐中電灯
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}