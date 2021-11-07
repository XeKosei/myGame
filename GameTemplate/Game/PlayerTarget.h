#pragma once
namespace nsHikageri
{
	namespace nsGimmick{ class Door; }
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
				enTarget_num
			};

			void SetTarget(EnTarget target) { m_target = target; };

			EnTarget GetTarget() { return m_target; };

			void SetTargetDoor(nsGimmick::Door* door) { m_targetDoor = door; };
			nsGimmick::Door* GetTargetDoor() { return m_targetDoor; }


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
		};
	}
}