#include "stdafx.h"
#include "PlayerInclude.h"
#include "FlashLightInclude.h"
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerPouchConstant;

		PlayerPouch::~PlayerPouch()
		{
			
		}

		void PlayerPouch::Init(Player* pl)
		{
			m_player = pl;
		}

		void PlayerPouch::ExecuteUpdate()
		{
			SelectItem();
		
			UseItem();

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
				case enItem_LastKey:
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
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
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
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
			}
		}

		//�A�C�e���̒ǉ�
		void PlayerPouch::AddItem(EnPlayerItems item)
		{ 
			m_choseItem = item;
			//�A�C�e���̐��𑝂₷
			m_haveItemNum[m_choseItem]++;
			//UI�X�V
			m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
		}

		//�d�r���g�p�����Ƃ��̏���
		void PlayerPouch::UseBattery()
		{
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				//�A�C�e���̐���1���炷
				m_haveItemNum[m_choseItem]--;
				//UI�̍X�V
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
				//�o�b�e���[��
				m_player->GetFlashLight()->GetFlashLightBattery()->SetBatteryLevel(nsFlashLight::nsFlashLightBatteryConstant::MAX_BATTERY_LEVEL);
				//SE
				UseItemSE(enUseItemSounds_Battery);
			}
		}

		//���_����܂��g�p�����Ƃ�
		void PlayerPouch::UseTranquilizar()
		{
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				//�A�C�e���̐���1���炷
				m_haveItemNum[m_choseItem]--;
				//UI�̍X�V
				m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
				//SAN�l��
				m_player->GetPlayerSanity()->Recovery(TRANQUILIZER_RECOVERY_NUM);
				//SE
				UseItemSE(enUseItemSounds_Tranquilizer);
			}
		}

		void PlayerPouch::UseKey()
		{
			if (g_pad[0]->IsTrigger(enButtonX) || g_pad[0]->IsTrigger(enButtonA) )
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
				case enItem_LastKey:
					if (m_player->GetPlayerTarget()->GetTarget() == PlayerTarget::enTarget_Door)
					{
						if (m_player->GetPlayerTarget()->GetTargetDoor()->GetDoorColor() == nsGimmick::Door::enDoorColor_White)
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
					//UI�X�V
					m_player->GetPlayerUI()->SetItemFont(m_choseItem, m_haveItemNum[m_choseItem]);
					//��������
					m_player->GetPlayerTarget()->GetTargetDoor()->SetUnlockFlag(true);
					//SE
					UseItemSE(enUseItemSounds_Key);
				}
			}
		}

		void PlayerPouch::UseItemSE(EnUseItemSounds soundKind)
		{
			if (m_useItemSS != nullptr)
			{
				DeleteGO(m_useItemSS);
				m_useItemSS = nullptr;
			}

			switch (soundKind)
			{
			case enUseItemSounds_Battery:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemBattery.wav");
				m_useItemSS->Play(false);
				break;
			case enUseItemSounds_Tranquilizer:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemTranquilizer.wav");
				m_useItemSS->Play(false);
				break;
			case enUseItemSounds_Key:
				m_useItemSS = NewGO<SoundSource>(0);
				m_useItemSS->Init(L"Assets/sound/UseItemKey.wav");
				m_useItemSS->Play(false);
				break;
			}
		}
	}
}