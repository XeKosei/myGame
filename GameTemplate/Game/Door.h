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

			void Execute();
			//開閉
			void Open();
			void Close();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };
			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };

			void SetPosition(Vector3 pos) { m_position = pos; };
			void SetDirection(Vector3 dir) { m_direction = dir; };
		private:
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			SkinModelRender* m_doorModel = nullptr;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;
			Quaternion m_qRot = Quaternion::Identity;

			//ドアが開いているかどうか
			bool m_openFlag = false;

			//ドアが(開いたり閉じたりして)動いているかどうか
			bool m_moveFlag = false;

			//ドアが前から開けられたか、後ろから開けられたか
			bool m_isOpenFromForward = false;

			//デフォルトのドアの角度
			float m_defaultAngle = 0.0f;
			//開閉時にデフォルトの角度に加える角度
			float m_addAngle = 0.0f;

			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}
