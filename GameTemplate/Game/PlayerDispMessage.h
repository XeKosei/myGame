#pragma once

namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerDispMessage : public IGameObject
		{
		public:
			void Init(Player* pl);
			void ExecuteUpdate();

			void SetMessage(std::wstring message);

		private:
			//ÉvÉåÉCÉÑÅ[
			Player* m_player = nullptr;

			FontRender* m_messageFont = nullptr;

			Vector3 m_messageFontColor = Vector3::Zero;

			bool m_setMessageFlag = false;
		};
	}
}