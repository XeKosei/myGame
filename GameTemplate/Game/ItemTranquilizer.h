#pragma once

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
			void ExecuteShineEffect();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			//入手されたとき
			void Got();

			//透視
			void ExecuteClairvoyance();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_tranquilizerModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			//光るエフェクト
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
			bool m_shineEffPlayingFlag = false;
		};
	}
}