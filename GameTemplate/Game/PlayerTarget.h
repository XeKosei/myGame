#pragma once
namespace nsHikageri
{
	namespace nsGimmick{ class Door; }
	namespace nsItem { class ItemKey; class ItemFlashLightParts; 
	class ItemTranquilizer; class ItemBattery; class ItemMessagePaper; }

	namespace nsPlayer
	{
		class Player;

		class PlayerTarget
		{
		public:
			~PlayerTarget();
			void Init(Player* pl);
			void ExecuteUpdate();

			enum EnTarget
			{
				enTarget_None,
				enTarget_Door,	//�h�A
				enTarget_Key,	//��
				enTarget_FlashLightParts,	//�����d���̃p�[�c
				enTarget_Tranquilizer,		//���_�����
				enTarget_Battery,	//�d�r
				enTarget_Paper,		//��
				enTarget_num
			};

			enum EnCommand
			{
				enCommand_None,
				enCommand_Get,	//���肷��
				enCommand_Open, //�J��
				enCommand_Close,//����
				enCommand_Read,	//�ǂ�
				enCommand_num
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

			void SetTargetMessagePaper(nsItem::ItemMessagePaper* messagePaper) { m_targetMessagePaper = messagePaper; };
			nsItem::ItemMessagePaper* GetTargetMessagePaper() { return m_targetMessagePaper; }

		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[�����ڂ��Ă���Ώ�
			EnTarget m_target = enTarget_None;

			//�A�C�e�����̕\��
			FontRender* m_itemNameFont = nullptr;
			//�R�}���h�̕\��
			FontRender* m_commandFont = nullptr;
			//�h�A
			nsGimmick::Door* m_targetDoor = nullptr;
			nsItem::ItemKey* m_targetKey = nullptr;
			nsItem::ItemFlashLightParts* m_targetFlashLightParts = nullptr;
			nsItem::ItemTranquilizer* m_targetTranquilizer = nullptr;
			nsItem::ItemBattery* m_targetBattery = nullptr;
			nsItem::ItemMessagePaper* m_targetMessagePaper = nullptr;
		};
	}
}