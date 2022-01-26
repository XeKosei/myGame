#pragma once
#include "Door.h"
#include "ItemConstant.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsGimmcik { class Door; }

	namespace nsItem
	{
		using namespace nsItemConstant;

		class ItemBase;
		class ItemKey : public IGameObject
		{
		public:
			~ItemKey();
			bool Start();
			void Update();
			Vector3 GetPosition() { return m_position; }

			//入手されたとき
			void Got();

			/// @brief モデルの位置を設定
			/// @param pos モデルの位置
			void SetPosition(Vector3 pos) { 
				m_position = pos; 
				if (m_keyModel != nullptr)
				{
					m_keyModel->SetPosition(pos);
					m_shineEffPos = pos;
					m_shineEffPos.y += SHINE_EFF_HEIGHT;
					m_shineEff.SetPosition(m_shineEffPos);
				}
			}

			//透視
			void ExecuteClairvoyance();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief 鍵の色を設定
			/// @param color 鍵の色
			void SetKeyColor(nsGimmick::Door::EnDoorColor color) { m_keyColor = color; }
		
		private:
			nsPlayer::Player* m_player = nullptr;
			SkinModelRender* m_keyModel = nullptr;

			Vector3 m_position = Vector3::Zero;

			nsGimmick::Door::EnDoorColor m_keyColor = nsGimmick::Door::enDoorColor_Red;

			//光るエフェクト
			Effect m_shineEff;
			Vector3 m_shineEffPos = Vector3::Zero;
		};
	}
}