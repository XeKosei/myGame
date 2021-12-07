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
			//ドアの色の種類
			enum EnDoorColor
			{
				enDoorColor_Red,
				enDoorColor_Blue,
				enDoorColor_Green,
				enDoorColor_Yellow,
				enDoorColor_Purple,
				enDoorColor_White,
				enDoorColor_num
			};

			//ドアのSEの種類
			enum EnDoorSounds
			{
				enDoorSound_Locked,
				enDoorSound_Open,
				enDoorSound_Close,
				enDoorSound_num
			};

			~Door();
			bool Start();
			void Update();

			void Execute();

			void SEManage(EnDoorSounds soundKind);

			void PlayerTargetSetting();

			//開かないとき
			void CannotOpen();

			//開閉
			void Open();
			void Close();

			//位置を取得
			Vector3 GetPosition() { return m_position; };

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };
			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
			/// @brief ドアの色を設定
			/// @param color ドアの色
			void SetDoorColor(EnDoorColor color) { m_doorColor = color; }
			/// @brief ドアの色を取得
			/// @return ドアの色
			EnDoorColor GetDoorColor() { return m_doorColor; }

			/// @brief 鍵が開いているかどうかを設定
			/// @param unlockFlag 鍵か開いているかどうか。
			void SetUnlockFlag(bool unlockFlag) { m_unlockFlag = unlockFlag; }

			/// @brief 鍵が開いているかどうかを取得
			/// @return 鍵か開いているかどうか
			bool GetUnlockFlag() { return m_unlockFlag; }

			/// @brief ドアが開いているかどうかを取得
			/// @return 開いている:true 開いていない:false
			bool GetOpenFlag() { return m_openFlag; }

			void SetPosition(Vector3 pos) { m_position = pos; };
			void SetDirection(Vector3 dir) { dir.Normalize(); m_direction = dir; };
		private:
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			SkinModelRender* m_doorModel = nullptr;

			//ドアの色
			EnDoorColor m_doorColor = enDoorColor_Red;

			//鍵が開いているかどうか
			bool m_unlockFlag = false;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;
			Quaternion m_qRot = Quaternion::Identity;

			//プレイヤーへの向き
			Vector3 m_toPlayerDir = Vector3::Zero;

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

			//開けられない処理を実行するフラグ
			bool m_executeCannotOpenFlag = false;
			//開けられない処理を実行する時間
			int m_executeCannotOpenCount = 0;
			//開けられない処理中のドアのガチャガチャする動き(前に動くか後ろに動くか)
			bool m_cannotOpenMoveForward = false;

			//SE
			SoundSource* m_ss = nullptr;
			bool m_canPlaySS = true;
		};
	}
}
