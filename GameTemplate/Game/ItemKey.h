#pragma once
#include "Door.h"
#include "ItemConstant.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsGimmcik { class Door; }

	namespace nsItem
	{
		using namespace nsItemConstant;

		class ItemBase;
		class ItemKey : public IGameObject
		{
		public:
			~ItemKey();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }

			//���肳�ꂽ�Ƃ�
			void Got();

			/// @brief ���f���̈ʒu��ݒ�
			/// @param pos ���f���̈ʒu
			void SetPosition(Vector3 pos) { 
				m_position = pos; 
				if (m_keyModel != nullptr)
				{
					m_keyModel->SetPosition(pos);
					m_shineEffPos = pos;
					m_shineEffPos.y += SHINE_EFF_HEIGHT;
					m_shineEff.SetPosition(m_shineEffPos);
				}
			}

			//����
			void ExecuteClairvoyance();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief ���̐F��ݒ�
			/// @param color ���̐F
			void SetKeyColor(nsGimmick::Door::EnDoorColor color) { m_keyColor = color; }
		
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_keyModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			nsGimmick::Door::EnDoorColor m_keyColor = nsGimmick::Door::enDoorColor_Red;

			//����G�t�F�N�g
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
		};
	}
}