#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{	
		class Statue : public IGameObject
		{
		public:
			bool Start();
			void Update();
			~Statue();

			void SetPosition(Vector3 pos) { m_position = pos; }
			void SetDirection(Vector3 dir) { dir.Normalize(); m_direction = dir; }
		private:
			//アニメーション
			enum {
				enAnimationClip_Idle,
				enAnimationClip_Run,
				enAnimationClip_SlowWalk,
				enAnimationClip_Scream,
				enAnimationClip_Bite,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};

			SkinModelRender* m_skinModel = nullptr;
			//アニメーションクリップ
			AnimationClip m_animationClips[enAnimationClip_num];

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = { 1.0f,0.0f,0.0f };

			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;


		};
	}
}

