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
			//�v���C���[�̃��f�����쐬
			m_playerModel = NewGO<SkinModelRender>(0);
			m_playerModel->Init("Assets/modelData/unityChan.tkm");
			m_playerModel->SetPosition(INI_PLAYER_POSITION);
			m_playerModel->SetSpotLightCasterFlag(false);

			//�L�����N�^�[�R���g���[���[���쐬
			m_charaCon.Init(
				PLAYER_MODEL_WIDTH,	//���a
				PLAYER_MODEL_HEIGHT,	//����
				INI_PLAYER_POSITION//�����ʒu
			);

			//�v���C���[�֌W�̃C���X�^���X���쐬
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
			//�����d���𐶐�
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
				m_playerSanity->ExecuteUpdate();
				m_playerPouch->ExecuteUpdate();
				m_playerTarget->ExecuteUpdate();
				break;
			case enState_Bitten:
				m_playerBitten->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerSanity->ExecuteUpdate();
				break;
			case enState_Dead:
				m_playerSanity->ExecuteUpdate();
			case enState_Stop:			
				break;
			case enState_Invincible:
				m_playerMove->ExecuteUpdate();
				m_playerAction->ExecuteUpdate();
				m_playerCamera->ExecuteUpdate();
				m_playerSanity->ExecuteUpdate();
				m_playerPouch->ExecuteUpdate();
				m_playerTarget->ExecuteUpdate();
				Invincible();
				break;
			}		
		}

		//���G����(��)
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