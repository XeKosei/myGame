#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLight.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerConstant;

		Player::~Player()
		{
			DeleteGO(m_playerModel);
			DeleteGO(m_playerMove);
			DeleteGO(m_playerCamera);
			DeleteGO(m_playerAction);
			DeleteGO(m_playerSanity);
			DeleteGO(m_playerBitten);
			DeleteGO(m_playerPouch);
			DeleteGO(m_playerTarget);
			DeleteGO(m_playerRead);
			DeleteGO(m_playerUI);
		}
		bool Player::Start()
		{
			//プレイヤーのモデルを作成
			m_playerModel = NewGO<SkinModelRender>(0);
			m_playerModel->Init("Assets/modelData/unityChan.tkm");
			m_playerModel->SetPosition(INI_PLAYER_POSITION);
			m_playerModel->SetSpotLightCasterFlag(false);

			//キャラクターコントローラーを作成
			m_charaCon.Init(
				PLAYER_MODEL_WIDTH,	//半径
				PLAYER_MODEL_HEIGHT,	//高さ
				INI_PLAYER_POSITION//初期位置
			);

			//プレイヤー関係のインスタンスを作成
			m_playerMove = NewGO<PlayerMove>(0);
			m_playerMove->SetPlayer(this);
			m_playerCamera = NewGO<PlayerCamera>(0);
			m_playerCamera->SetPlayer(this);
			m_playerAction = NewGO<PlayerAction>(0);
			m_playerAction->SetPlayer(this);
			m_playerSanity = NewGO<PlayerSanity>(0);
			m_playerSanity->SetPlayer(this);
			m_playerBitten = NewGO<PlayerBitten>(0);
			m_playerBitten->SetPlayer(this);
			m_playerPouch = NewGO<PlayerPouch>(0);
			m_playerPouch->SetPlayer(this);
			m_playerTarget = NewGO<PlayerTarget>(0);
			m_playerTarget->SetPlayer(this);
			m_playerRead = NewGO<PlayerRead>(0);
			m_playerRead->SetPlayer(this);
			m_playerUI = NewGO<PlayerUI>(0);
			m_playerUI->SetPlayer(this);
			return true;
		}

		void Player::Update()
		{				
			switch (m_playerState)
			{
			case enState_Normal:
				m_playerMove->ExecuteUpdate();
				m_playerAction->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerSanity->ExecuteUpdate();
				m_playerPouch->ExecuteUpdate();
				m_playerTarget->ExecuteUpdate();
				m_playerUI->ExecuteUpdate();
				break;
			case enState_Bitten:
				m_playerBitten->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerSanity->ExecuteUpdate();
				m_playerUI->ExecuteUpdate();
				break;
			case enState_Dead:
				m_playerUI->ExecuteUpdate();
			case enState_Stop:			
				break;
			case enState_Read:
				m_playerRead->ExecuteUpdate();
				break;
			case enState_Invincible:
				m_playerMove->ExecuteUpdate();
				m_playerAction->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerSanity->ExecuteUpdate();
				m_playerPouch->ExecuteUpdate();
				m_playerTarget->ExecuteUpdate();
				m_playerUI->ExecuteUpdate();
				Invincible();
				break;
			}		
		}

		//無敵時間(仮)
		void Player::Invincible()
		{
			if (m_invincibleTime != 0)
			{
				m_invincibleTime--;
				
			}
			else
			{
				m_playerState = enState_Normal;
			}
		}
	}
}