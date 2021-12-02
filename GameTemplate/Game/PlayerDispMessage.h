#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerDispMessage : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			void SetMessage(std::wstring message);

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };
		private:
			//�v���C���[
			Player* m_player = nullptr;

			FontRender* m_messageFont = nullptr;

			Vector3 m_messageFontColor = Vector3::Zero;

			bool m_setMessageFlag = false;
		};
	}
}