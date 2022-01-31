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

			//入手されたとき
			void Got();

			//透視の処理
			void ExecuteClairvoyance();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_batteryModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			//光るエフェクト
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
			bool m_shineEffPlayingFlag = false;
		};
	}
}