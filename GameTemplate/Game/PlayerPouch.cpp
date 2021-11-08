#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerPouchConstant;

		bool PlayerPouch::Start()
		{
			//��ʕ\��
			m_itemFont = NewGO<FontRender>(2);
			m_itemFont->SetText(ITEM_NAME[m_choseItem]);
			m_itemFont->SetScale(1.0f);
			m_itemFont->SetPosition({ -600.0f, -200.0f });
			m_itemFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemFont->SetShadowFlag(true);
			m_itemFont->SetShadowOffset(1.0f);
			m_itemFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			m_itemNumFont = NewGO<FontRender>(2);
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_itemNumFont->SetScale(1.0f);
			m_itemNumFont->SetPosition({ -500.0f, -250.0f });
			m_itemNumFont->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			m_itemNumFont->SetShadowFlag(true);
			m_itemNumFont->SetShadowOffset(1.0f);
			m_itemNumFont->SetShadowColor({ 0.0f,0.0f,0.0f,1.0f });

			/*m_itemUsedFont = NewGO<FontRender>(2);
			m_itemUsedFont->SetText(L"�g�p�ł��Ȃ��B");
			m_itemUsedFont->SetScale(1.0f);
			m_itemUsedFont->SetPosition({ -200.0f, -225.0f });
			m_itemUsedFontColor = {1.0f,1.0f,1.0f,0.0f};
			m_itemUsedFont->SetColor(m_itemUsedFontColor);
			m_itemUsedFont->SetShadowFlag(true);
			m_itemUsedFont->SetShadowOffset(1.0f);
			m_itemUsedFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });
			m_itemUsedFontCount = 300;*/

			return true;
		}

		void PlayerPouch::ExecuteUpdate()
		{
			SelectItem();

			if (g_pad[0]->IsTrigger(enButtonX))
			{
				UseItem();
			}
		}

		void PlayerPouch::UseItem()
		{
			//�A�C�e����1�ȏ㎝���Ă���Ȃ��
			if (m_haveItemNum[m_choseItem] > 0)
			{
				switch (m_choseItem)
				{
				case enItem_Battery:
					UseBattery();
					break;
				case enItem_Tranquilizer:
					UseTranquilizar();
					break;
				case enItem_RedKey:
					UseKey();
					break;
				case enItem_BlueKey:
					UseKey();
					break;
				case enItem_GreenKey:
					UseKey();
					break;
				case enItem_YellowKey:
					UseKey();
					break;
				case enItem_PurpleKey:
					UseKey();
					break;
				default:
					break;
				}
			}
		}

		//�A�C�e����I������
		void PlayerPouch::SelectItem() 
		{
			//�E�{�^����������
			if (g_pad[0]->IsTrigger(enButtonRight))
			{
				for (int i = 0; i < enItem_num; i++)
				{
					m_choseItem++;
					//�A�C�e���̔ԍ����ő�ɂȂ�����A�ԍ���0�ɖ߂��B
					if (m_choseItem >= enItem_num)
					{
						m_choseItem = 0;
					}
					//�������Ă��Ȃ��A�C�e���͔�΂�
					if (m_haveItemNum[m_choseItem] > 0)
					{
						break;
					}
				}
		
				//�e�L�X�g��ݒ�
				m_itemFont->SetText(ITEM_NAME[m_choseItem]);
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));		
			}
			//���{�^����������
			if (g_pad[0]->IsTrigger(enButtonLeft))
			{
				for (int i = 0; i < enItem_num; i++)
				{
					m_choseItem--;
					//�A�C�e���̔ԍ���0�ȉ��ɂȂ�����A�ԍ����ő�ɂ���B
					if (m_choseItem < 0)
					{
						m_choseItem = enItem_num - 1;
					}

					//�������Ă��Ȃ��A�C�e���͔�΂�
					if (m_haveItemNum[m_choseItem] > 0)
					{
						break;
					}
				}

				//�e�L�X�g��ݒ�
				m_itemFont->SetText(ITEM_NAME[m_choseItem]);
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));		
			}
		}
		//�d�r���g�p�����Ƃ��̏���
		void PlayerPouch::UseBattery()
		{
			//�A�C�e���̐���1���炷
			m_haveItemNum[m_choseItem]--;
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_player->GetFlashLight()->GetFlashLightBattery()->SetBatteryLevel(nsFlashLight::nsFlashLightBatteryConstant::MAX_BATTERY_LEVEL);
		}

		//���_����܂��g�p�����Ƃ�
		void PlayerPouch::UseTranquilizar()
		{
			//�A�C�e���̐���1���炷
			m_haveItemNum[m_choseItem]--;
			m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
			m_player->GetPlayerSanity()->Recovery(TRANQUILIZER_RECOVERY_NUM);
		}

		void PlayerPouch::UseKey()
		{
			//�h�A�̃J�M���J���邩�ǂ����̃t���O
			bool unlockFlag = false;

			//���̐F�ƃh�A�̐F����v���Ă��邩���Ǘ�
			switch (m_choseItem)
			{		
			case enItem_RedKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Red)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_BlueKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Blue)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_GreenKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Green)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_YellowKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Yellow)
					{
						unlockFlag = true;
					}
				}
				break;
			case enItem_PurpleKey:
				if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
				{
					if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_Purple)
					{
						unlockFlag = true;
					}
				}
				break;
			default:
				break;
			}

			if (unlockFlag)
			{
				//�A�C�e���̐���1���炷
				m_haveItemNum[m_choseItem]--;
				m_itemNumFont->SetText(std::to_wstring(m_haveItemNum[m_choseItem]));
				//��������
				m_player->GetPlayerTarget()->GetTargetDoor()->SetUnlockFlag(true);
			}
		}

		//void PlayerPouch::CannotUse()
		//{
		//	if (m_itemUsedFontCount == 300)
		//	{
		//		m_itemUsedFontColor.a = 1.0f;
		//	}
		//	if (m_itemUsedFontCount > 0)
		//	{
		//		m_itemUsedFontCount--;
		//	}

		//	if (m_itemUsedFontCount <= 100 && m_itemUsedFontCount > 0)
		//	{
		//		m_itemUsedFontColor.a -= 0.01f;
		//		m_itemUsedFont->SetColor(m_itemUsedFontColor);
		//		//m_gameOverFontShadowColor.a += 0.01f;
		//		//m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
		//	}
		//}
	}
}