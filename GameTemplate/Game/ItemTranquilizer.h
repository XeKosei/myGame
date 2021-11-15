#pragma once
#include "Door.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemBase;
		class ItemTranquilizer : public IGameObject
		{
		public:
			~ItemTranquilizer();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_tranquilizerModel = nullptr;

			Vector3 m_position = Vector3::Zero;
		};
	}
}