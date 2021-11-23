#pragma once
namespace nsHikageri
{
	namespace nsGimmick{ class Door; }
	namespace nsItem { class ItemKey; class ItemFlashLightParts; class ItemTranquilizer; class ItemBattery; }
	namespace nsPlayer
	{
		class Player;

		class PlayerTarget : public IGameObject
		{
		public:
			~PlayerTarget();
			void ExecuteUpdate();

			enum EnTarget
			{
				enTarget_None,
				enTarget_Door,
				enTarget_Key,
				enTarget_FlashLightParts,
				enTarget_Tranquilizer,
				enTarget_Battery,
				enTarget_num
			};

			void SetTarget(EnTarget target) { m_target = target; };

			EnTarget GetTarget() { return m_target; };

			void SetTargetDoor(nsGimmick::Door* door) { m_targetDoor = door; };
			nsGimmick::Door* GetTargetDoor() { return m_targetDoor; }

			void SetTargetKey(nsItem::ItemKey* key) { m_targetKey = key; };
			nsItem::ItemKey* GetTargetKey() { return m_targetKey; }

			void SetTargetFlashLightParts(nsItem::ItemFlashLightParts* parts) { m_targetFlashLightParts = parts; };
			nsItem::ItemFlashLightParts* GetTargetFlashLightParts() { return m_targetFlashLightParts; }

			void SetTargetTranquilizer(nsItem::ItemTranquilizer* tranquilizer) { m_targetTranquilizer = tranquilizer; };
			nsItem::ItemTranquilizer* GetTargetTranquilizer() { return m_targetTranquilizer; }

			void SetTargetBattery(nsItem::ItemBattery* battery) { m_targetBattery = battery; };
			nsItem::ItemBattery* GetTargetBattery() { return m_targetBattery; }


			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//プレイヤー
			Player* m_player = nullptr;
			//プレイヤーが注目している対象
			EnTarget m_target = enTarget_None;

			//ドア
			nsGimmick::Door* m_targetDoor = nullptr;
			nsItem::ItemKey* m_targetKey = nullptr;
			nsItem::ItemFlashLightParts* m_targetFlashLightParts = nullptr;
			nsItem::ItemTranquilizer* m_targetTranquilizer = nullptr;
			nsItem::ItemBattery* m_targetBattery = nullptr;
		};
	}
}