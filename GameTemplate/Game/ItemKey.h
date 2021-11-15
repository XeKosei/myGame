#pragma once
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsGimmcik { class Door; }

	namespace nsItem
	{
		class ItemBase;
		class ItemKey : public IGameObject
		{
		public:
			~ItemKey();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

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
		};
	}
}