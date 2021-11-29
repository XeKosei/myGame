#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightConstant;

		FlashLight::~FlashLight()
		{
			DeleteGO(m_flashLightModel);
			DeleteGO(m_spotLight);
			DeleteGO(m_flashLightAction);
			DeleteGO(m_flashLightBattery);
			DeleteGO(m_abilityManager);
			DeleteGO(m_abilityStrobeFlash);
			DeleteGO(m_abilityClairvoyance);
			DeleteGO(m_abilityMedousaEye);
		}

		bool FlashLight::Start()
		{
			//�����d���̃��f���𐶐�
			m_flashLightModel = NewGO<SkinModelRender>(0);
			m_flashLightModel->Init("Assets/modelData/FlashLight.tkm");
			m_flashLightModel->SetPosition(m_position);
			m_flashLightModel->SetScale(INI_FLASHLIGHT_MODEL_SCALE);
			m_flashLightModel->SetSpotLightCasterFlag(false);

			//�X�|�b�g���C�g�𐶐�
			m_spotLight = NewGO<nsHikageri::SpotLight>(0);//�V�����f���A�̃X�|�b�g���C�g����ɍ�肽���̂ŁA�D�揇�ʂ�0�ɂ���B
			m_spotLight->SetPosition(m_player->GetPlayerMove()->GetPosition());
			m_spotLight->SetDirection(m_direction);
			m_spotLight->SetColor(INI_FLASHLIGHT_COLOR);
			m_spotLight->SetRange(0.0f);
			m_flashLightAngle = INI_FLASHLIGHT_ANGLE;	//�X�|�b�g���C�g�̎ˏo�p�x
			m_spotLight->SetAngle(m_flashLightAngle / 2);//(�X�|�b�g���C�g�ɑ���A���O���͔��a�Ȃ̂ŁA2�Ŋ���B

			//�X�|�b�g���C�g�J�����̐ݒ�
			LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle, 0);
			//LightManager::GetInstance()->SetSpotLightCameraFar(INI_FLASHLIGHT_RANGE);
			//�����d���֌W�̃C���X�^���X���쐬
			m_flashLightAction = NewGO<FlashLightAction>(0);
			m_flashLightAction->SetFlashLight(this);
			m_flashLightBattery = NewGO<FlashLightBattery>(0);
			m_flashLightBattery->SetFlashLight(this);

			//�A�r���e�B�֘A
			m_abilityManager = NewGO<AbilityManager>(0);
			m_abilityManager->SetFlashLight(this);
			m_abilityStrobeFlash = NewGO<AbilityStrobeFlash>(0);
			m_abilityStrobeFlash->SetFlashLight(this);
			m_abilityStrobeFlash->SetAbilityManager(m_abilityManager);
			m_abilityClairvoyance = NewGO<AbilityClairvoyance>(0);
			m_abilityClairvoyance->SetFlashLight(this);
			m_abilityClairvoyance->SetAbilityManager(m_abilityManager);
			m_abilityMedousaEye = NewGO<AbilityMedousaEye>(0);
			m_abilityMedousaEye->SetFlashLight(this);
			m_abilityMedousaEye->SetAbilityManager(m_abilityManager);

			return true;
		}

		void FlashLight::Update()
		{
			//�����d���֌W�̏���
			//if (m_player->GetPlayerState() == nsPlayer::Player::enState_Normal ||
			//	m_player->GetPlayerState() == nsPlayer::Player::enState_Invincible )
			{
				m_flashLightAction->ExecuteUpdate();
				m_flashLightBattery->ExecuteUpdate();
				m_abilityStrobeFlash->ExecuteUpdate();
				m_abilityClairvoyance->ExecuteUpdate();
				m_abilityMedousaEye->ExecuteUpdate();
			}

			// ���f���p�̉R���W���v�Z����
			Vector3 spotLightUp = Cross(g_camera3D->GetForward(), g_camera3D->GetRight());
			Vector3 modelPos;
			modelPos = g_camera3D->GetPosition();
			modelPos += g_camera3D->GetRight() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.x;
			modelPos += g_camera3D->GetForward() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.z;
			modelPos += spotLightUp * FLASHLIGHT_MODEL_POS_APPLY_VALUE.y;

			//���ۂ̉����d���̍��W

			//�܂������d�����J�����Ɠ����ʒu�ɐݒ�
			m_position = g_camera3D->GetPosition();
			//�����d���̈ʒu�����ɂ��炷�B
			m_position += g_camera3D->GetRight() * FLASHLIGHT_POS_APPLY_VALUE.x;
			//�����d���̈ʒu���c�ɂ��炷
			m_position += spotLightUp * FLASHLIGHT_POS_APPLY_VALUE.y;
	
			//������ݒ�
			m_direction = g_camera3D->GetForward();
			m_direction.Normalize();
			Vector3 spotLigTarget = m_position + m_direction * TO_SPOTLIGHTCAMERA_TARGET_DIS;
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget, 0);
			m_spotLight->SetDirection({ m_direction });

			//�����d���̃��f������]������B
			Quaternion qRotMat = Quaternion::Identity;
			qRotMat.SetRotation(g_camera3D->GetCameraRotation());
			m_flashLightModel->SetRotation(qRotMat);

			//�����d���̈ʒu���v�Z�B�������d���̈ʒu�����炷�̂́A��ł��Ȃ��ƃ��f���̉�]����肭�s���Ȃ��B
			m_flashLightModel->SetPosition(modelPos);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position, 0);
		}
	}
}