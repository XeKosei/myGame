#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsItem
	{
		class ItemBase;
		class ItemKey : public IGameObject
		{
		public:
			//���̐F�̎��
			enum EnKeyColor
			{
				enKeyColor_Red,
				enKeyColor_Blue,
				enKeyColor_Green,
				enKeyColor_Yellow,
				enKeyColor_Purple,
				enKeyColor_num
			};

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
			void SetKeyColor(EnKeyColor color) { m_keyColor = color; }
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_keyModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnKeyColor m_keyColor = enKeyColor_Red;
		};
	}
}