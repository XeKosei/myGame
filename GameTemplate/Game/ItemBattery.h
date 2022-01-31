#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemBase;
		class ItemBattery : public IGameObject
		{
		public:
			~ItemBattery();
			bool Start();
			void Update();
			void ExecuteShineEffect();

			//���肳�ꂽ�Ƃ�
			void Got();

			//�����̏���
			void ExecuteClairvoyance();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_batteryModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			//����G�t�F�N�g
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
			bool m_shineEffPlayingFlag = false;
		};
	}
}