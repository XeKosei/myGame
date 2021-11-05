#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		class Door : public IGameObject
		{
		public:
			bool Start();
			void Update();

			void Open();
			void Close();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };
			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
		private:
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			SkinModelRender* m_doorModel = nullptr;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;

			//ドアが開いているかどうか
			bool m_openFlag = false;

			//ドアが(開いたり閉じたりして)動いているかどうか
			bool m_moveFlag = false;

			//ドアが前から開けられたか、後ろから開けられたか
			bool m_isOpenFromForward = false;

			float m_defaultAngle = 0.0f;

			float m_addAngle = 0.0f;

			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}
