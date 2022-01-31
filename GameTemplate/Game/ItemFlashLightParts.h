#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsItem
	{
		class ItemFlashLightParts : public IGameObject
		{
		public:
			enum EnFlashLightPartsTypes
			{
				enFlashLightPartsTypes_StrobeFlash,
				enFlashLightPartsTypes_Clairvoyance,
				enFlashLightPartsTypes_MedousaEye,
				enFlashLightPartsTypes_num
			};

			~ItemFlashLightParts();
			bool Start();
			void Update();
			void ExecuteShineEffect();

			//入手されたとき
			void Got();

			//透視
			void ExecuteClairvoyance();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief パーツの種類を設定
			/// @param color パーツの種類
			void SetPartsType(EnFlashLightPartsTypes partsType) { m_partsType = partsType; }
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_partsModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			EnFlashLightPartsTypes m_partsType = enFlashLightPartsTypes_StrobeFlash;

			//光るエフェクト
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
			bool m_shineEffPlayingFlag = false;
		};
	}
}