#pragma once
#include "PlayerAction.h"
#include "PlayerMove.h"
#include "PlayerCamera.h"
#include "PlayerSanity.h"
#include "PlayerBitten.h"
#include "PlayerPouch.h"
#include "PlayerTarget.h"
#include "PlayerRead.h"
#include "PlayerUI.h"
#include "PlayerDispMessage.h"
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{	
		class Player : public IGameObject
		{
		public:
			enum EnPlayerStates
			{
				enState_Normal,
				enState_Bitten,
				enState_Dead,
				enState_Stop,
				enState_Read,
				enStatesNum,
				enState_Invincible,
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

			/// @brief 無敵時間を設定(仮)
			/// @param time 設定する時間
			void SetInvincible(int time) { m_playerState = enState_Invincible; m_invincibleTime = time; }

			//無敵中の処理
			void Invincible();

			/// @brief 懐中電灯を設定
			/// @param flashLight 懐中電灯
			void SetFlashLight(nsFlashLight::FlashLight* flashLight) { m_flashLight = flashLight; }

			/// @brief 懐中電灯を取得
			/// @return 懐中電灯
			nsFlashLight::FlashLight* GetFlashLight() { return m_flashLight; }

			//プレイヤー関係のインスタンスにアクセスする
			PlayerMove* GetPlayerMove() { return &m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return &m_playerCamera; };
			PlayerAction* GetPlayerAction() { return &m_playerAction; };
			PlayerSanity* GetPlayerSanity() { return &m_playerSanity; };
			PlayerBitten* GetPlayerBitten() { return &m_playerBitten; }
			PlayerPouch* GetPlayerPouch() { return &m_playerPouch; }
			PlayerTarget* GetPlayerTarget() { return &m_playerTarget; };
			PlayerRead* GetPlayerRead() { return &m_playerRead; }
			PlayerUI* GetPlayerUI() { return &m_playerUI; }
			PlayerDispMessage* GetPlayerDispMessage() { return &m_playerDispMessage; }
		private:
			//モデル
			SkinModelRender* m_playerModel = nullptr;
			//プレイヤーのキャラコン
			CharacterController m_charaCon;

			//無敵時間
			int m_invincibleTime = 0;

			//プレイヤー関係のクラス
			PlayerMove m_playerMove;
			PlayerCamera m_playerCamera;
			PlayerAction m_playerAction;
			PlayerSanity m_playerSanity;
			PlayerBitten m_playerBitten;
			PlayerPouch m_playerPouch;
			PlayerTarget m_playerTarget;
			PlayerRead m_playerRead;
			PlayerUI m_playerUI;
			PlayerDispMessage m_playerDispMessage;

			EnPlayerStates m_playerState = enState_Normal;

			//懐中電灯
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}