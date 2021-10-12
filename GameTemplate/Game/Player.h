#pragma once
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{
		class PlayerMove;
		class PlayerCamera;		
		//class PlayerConstant;

		class Player : public IGameObject
		{
		public:
			~Player();
			bool Start();
			void Update();

			/// @brief プレイヤーのモデルの位置を設定する。(PlayerMoveクラスで利用)
			/// @param pos 設定する位置
			void SetPosition(Vector3 pos) { m_position = pos; m_playerModel->SetPosition(m_position); };

			Vector3 GetPosition() { return m_position; };
			/// @brief プレイヤーのモデルの回転を設定する。(PlayerMoveクラスで利用)
			/// @param qRot 設定する回転
			void SetRotation(Quaternion qRot) { m_playerModel->SetRotation(qRot); };

			/// @brief プレイヤーのキャラコンを取得する。(PlayerMoveクラスで利用)
			/// @return プレイヤーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };
		private:
			//プレイヤーの位置
			Vector3 m_position = { Vector3::Zero };

			//モデル
			SkinModelRender* m_playerModel = nullptr;
			//プレイヤーのキャラコン
			CharacterController m_charaCon;

			//アニメーション関連
			enum {
				enAnimationClip_Idle,
				enAnimationClip_walk,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};
			AnimationClip animationClips[enAnimationClip_num];

			//プレイヤー関係のクラス
			PlayerMove* m_playerMove = nullptr;
			PlayerCamera* m_playerCamera = nullptr;

			//懐中電灯
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}