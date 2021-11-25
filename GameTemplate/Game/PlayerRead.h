#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerRead : public IGameObject
		{
		public:
			~PlayerRead();
			bool Start();
			void ExecuteUpdate();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief �e�L�X�g��ݒ�
			/// @param message �e�L�X�g
			void SetMessage(std::wstring message) { m_message = message; }

		private:
			//�v���C���[
			Player* m_player = nullptr;

			FontRender* m_messageFont = nullptr;

			std::wstring m_message = L"";

			SpriteRender* m_blackSprite = nullptr;
			Vector4 m_blackSpriteColor = {0.0f,0.0f,0.0f,0.0f};
			//��ʂ��Â�����t���O
			bool m_blackOutFlag = false;
		};

	}
}