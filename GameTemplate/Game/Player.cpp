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
			//DeleteGO(m_playerCamera);
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
			m_playerHP = NewGO<PlayerHP>(0);
			m_playerHP->SetPlayer(this);
			m_playerBitten = NewGO<PlayerBitten>(0);
			m_playerBitten->SetPlayer(this);

			//懐中電灯を生成
			m_flashLight = NewGO<nsFlashLight::FlashLight>(0);
			m_flashLight->SetPlayer(this);

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
				m_playerHP->ExecuteUpdate();
				break;
			case enState_Bitten:
				m_playerBitten->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerHP->ExecuteUpdate();
				break;
			case enState_Dead:
				m_playerHP->ExecuteUpdate();
			case enState_Stop:			
				break;
			}	
		}
	}
}