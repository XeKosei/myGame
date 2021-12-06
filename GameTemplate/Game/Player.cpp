#include "stdafx.h"
#include "FlashLight.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerConstant;

		Player::~Player()
		{
			DeleteGO(m_playerModel);
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

			//プレイヤー関係のクラスの初期化
			m_playerMove.Init(this);
			m_playerCamera.Init(this);
			m_playerAction.Init(this);
			m_playerSanity.Init(this);
			m_playerBitten.Init(this);
			m_playerPouch.Init(this);
			m_playerTarget.Init(this);
			m_playerRead.Init(this);
			m_playerUI.Init(this);
			m_playerDispMessage.Init(this);

			return true;
		}

		void Player::Update()
		{		
			switch (m_playerState)
			{
			case enState_Normal:
				m_playerMove.ExecuteUpdate();
				m_playerAction.ExecuteUpdate();
				m_playerCamera.ExecuteUpdate();
				m_playerSanity.ExecuteUpdate();
				m_playerPouch.ExecuteUpdate();
				m_playerTarget.ExecuteUpdate();
				m_playerUI.ExecuteUpdate();
				m_playerDispMessage.ExecuteUpdate();
				break;
			case enState_Bitten:
				m_playerBitten.ExecuteUpdate();
				m_playerCamera.ExecuteUpdate();
				m_playerSanity.ExecuteUpdate();
				m_playerUI.ExecuteUpdate();
				break;
			case enState_Dead:
				m_playerUI.ExecuteUpdate();
			case enState_Stop:			
				break;
			case enState_Read:
				m_playerRead.ExecuteUpdate();
				break;
			case enState_Invincible:
				m_playerMove.ExecuteUpdate();
				m_playerAction.ExecuteUpdate();
				m_playerCamera.ExecuteUpdate();
				m_playerSanity.ExecuteUpdate();
				m_playerPouch.ExecuteUpdate();
				m_playerTarget.ExecuteUpdate();
				m_playerUI.ExecuteUpdate();
				m_playerDispMessage.ExecuteUpdate();
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