#pragma once
namespace nsHikageri
{
	namespace nsGimmick{ class Door; }
	namespace nsItem { class ItemKey; class ItemFlashLightParts; }
	namespace nsPlayer
	{
		class Player;

		class PlayerTarget : public IGameObject
		{
		public:
			void ExecuteUpdate();

			enum EnTarget
			{
				enTarget_None,
				enTarget_Door,
				enTarget_Key,
				enTarget_FlashLightParts,
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

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[�����ڂ��Ă���Ώ�
			EnTarget m_target = enTarget_None;

			//�h�A
			nsGimmick::Door* m_targetDoor = nullptr;
			nsItem::ItemKey* m_targetKey = nullptr;
			nsItem::ItemFlashLightParts* m_targetFlashLightParts = nullptr;
		};
	}
}