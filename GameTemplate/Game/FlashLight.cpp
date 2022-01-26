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
			LightManager::GetInstance()->SetIsFlashLightSwitchOn(false, 0);
			//LightManager::GetInstance()->SetSpotLightCameraFar(INI_FLASHLIGHT_RANGE);
			//�����d���֌W�̃N���X�̏�����
			m_flashLightAction.Init(this);
			m_flashLightBattery.Init(this);

			//�A�r���e�B�֘A
			m_abilityStrobeFlash.Init(this);
			m_abilityClairvoyance.Init(this);
			m_abilityMedousaEye.Init(this);

			//���鏈���̃J�E���g
			m_breakMoveCount = INI_BREAKMOVE_COUNT;

			return true;
		}

		void FlashLight::Update()
		{
			//�v���C���[������ł���Ȃ�A�������Ȃ�
			if (m_player->GetPlayerState() == nsPlayer::Player::enState_Dead)
				return;

			// ���f���p�̉R���W���v�Z����
			Vector3 spotLightUp = Cross(g_camera3D->GetForward(), g_camera3D->GetRight());

			m_modelPos = g_camera3D->GetPosition();
			m_modelPos += g_camera3D->GetRight() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.x;
			m_modelPos += g_camera3D->GetForward() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.z;
			m_modelPos += Cross(g_camera3D->GetForward(), g_camera3D->GetRight()) * FLASHLIGHT_MODEL_POS_APPLY_VALUE.y;

			//���ۂ̉����d���̍��W

			//�܂������d�����J�����Ɠ����ʒu�ɐݒ�
			m_position = g_camera3D->GetPosition();
			//�����d���̈ʒu�����ɂ��炷�B
			m_position += g_camera3D->GetRight() * FLASHLIGHT_POS_APPLY_VALUE.x;
			//�����d���̈ʒu���c�ɂ��炷
			m_position += spotLightUp * FLASHLIGHT_POS_APPLY_VALUE.y;
			m_position += g_camera3D->GetForward() * FLASHLIGHT_POS_APPLY_VALUE.z;

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
			m_flashLightModel->SetPosition(m_modelPos);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position, 0);

			//���Ă���Ȃ��
			if (m_isBreak)
			{
				BreakMove();
				return;
			}

			//�����d���֌W�̏���
			//if (m_player->GetPlayerState() == nsPlayer::Player::enState_Normal ||
			//	m_player->GetPlayerState() == nsPlayer::Player::enState_Invincible )
			{
				m_flashLightAction.ExecuteUpdate();
				m_flashLightBattery.ExecuteUpdate();
				m_abilityStrobeFlash.ExecuteUpdate();
				m_abilityClairvoyance.ExecuteUpdate();
				m_abilityMedousaEye.ExecuteUpdate();
			}
		}

		//���鏈��
		void FlashLight::BreakMove()
		{
			if (m_breakMoveCount > 0)
			{
				m_breakMoveCount--;

				if (m_breakMoveCount == 99)
				{
					m_abilityStrobeFlash.Reset();
					m_abilityClairvoyance.Reset();
					m_abilityMedousaEye.Reset();

					SpotLightGoOut();
					m_player->GetPlayerUI()->SetBatteryUIDeleteFlag(true);
					SoundSource* breakSS = NewGO<SoundSource>(0);
					breakSS->Init(L"Assets/sound/FlashLightBreak.wav");
					breakSS->Play(false);
				}
				else if (m_breakMoveCount == 98)
					SpotLightOn();
				else if (m_breakMoveCount == 75)
					SpotLightGoOut();
				else if (m_breakMoveCount == 74)
					SpotLightOn();
				else if (m_breakMoveCount == 70)
					SpotLightGoOut();
				else if (m_breakMoveCount == 69)
					SpotLightOn();
				else if (m_breakMoveCount == 50)
					SpotLightGoOut();
				else if (m_breakMoveCount == 45)
					SpotLightOn();
				else if (m_breakMoveCount == 35)
					SpotLightGoOut();
				else if (m_breakMoveCount == 25)
					SpotLightOn();
				else if (m_breakMoveCount == 12)
					SpotLightGoOut();
				else if (m_breakMoveCount == 1)
					SpotLightOn();
				else if (m_breakMoveCount == 0)
					SpotLightGoOut();

			}
		}

	}
}