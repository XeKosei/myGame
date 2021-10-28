#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightConstant;

		FlashLight::~FlashLight()
		{
			//DeleteGO(m_flashLightModel);
			DeleteGO(m_spotLight);
		}

		bool FlashLight::Start()
		{
			//�����d���̃��f���𐶐�
			m_flashLightModel = NewGO<SkinModelRender>(0);
			m_flashLightModel->Init("Assets/modelData/FlashLight.tkm");
			m_flashLightModel->SetPosition(m_position);
			m_flashLightModel->SetSpotLightCasterFlag(false);

			//�X�|�b�g���C�g�𐶐�
			m_spotLight = NewGO<nsHikageri::SpotLight>(0);
			m_spotLight->SetPosition(m_player->GetPlayerMove()->GetPosition());
			m_spotLight->SetDirection(m_direction);
			m_spotLight->SetColor(INI_FLASHLIGHT_COLOR);
			m_spotLight->SetRange(0.0f);
			m_flashLightAngle = INI_FLASHLIGHT_ANGLE;	//�X�|�b�g���C�g�̎ˏo�p�x
			m_spotLight->SetAngle(m_flashLightAngle / 2);//(�X�|�b�g���C�g�ɑ���A���O���͔��a�Ȃ̂ŁA2�Ŋ���B

			//�X�|�b�g���C�g�J�����̃A���O����ݒ�
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle);

			//�����d���֌W�̃C���X�^���X���쐬
			m_flashLightAction = NewGO<FlashLightAction>(0);
			m_flashLightAction->SetFlashLight(this);
			m_abilityStrobeFlash = NewGO<AbilityStrobeFlash>(0);
			m_abilityStrobeFlash->SetFlashLight(this);
			m_flashLightBattery = NewGO<FlashLightBattery>(0);
			m_flashLightBattery->SetFlashLight(this);
			return true;
		}

		void FlashLight::Update()
		{
			//�����d���֌W�̏���
			if (m_player->GetPlayerState() == nsPlayer::Player::enState_Normal)
			{
				m_flashLightAction->ExecuteUpdate();
				m_abilityStrobeFlash->ExecuteUpdate();
				m_flashLightBattery->ExecuteUpdate();
			}

			//�܂������d�����J�����Ɠ����ʒu�ɐݒ�
			m_position = g_camera3D->GetPosition();
			//�����d���̈ʒu�����ɂ��炷�B
			m_position += g_camera3D->GetRight() * APPLY_FLASHLIGHT_POS_VALUE.x;
			//�����d���̈ʒu�����ɂ��炷�B
			m_position += g_camera3D->GetForward() * APPLY_FLASHLIGHT_POS_VALUE.z;

			//������ݒ�
			m_direction = g_camera3D->GetForward();
			m_direction.Normalize();
			Vector3 spotLigTarget = m_position + m_direction * TO_SPOTLIGHTCAMERA_TARGET_DIS;
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget);
			m_spotLight->SetDirection({ m_direction });

			//�����d���̃��f������]������B
			Quaternion qRotMat = Quaternion::Identity;
			qRotMat.SetRotation(g_camera3D->GetCameraRotation());
			m_flashLightModel->SetRotation(qRotMat);

			//�����d���̈ʒu���v�Z�B�������d���̈ʒu���c�ɂ��炷�̂́A��ł��Ȃ��ƃ��f���̉�]����肭�s���Ȃ��B
			m_position -= Cross(g_camera3D->GetForward(), g_camera3D->GetRight()) * APPLY_FLASHLIGHT_POS_VALUE.y;
			m_flashLightModel->SetPosition(m_position);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position);
		}
	}
}