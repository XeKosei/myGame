#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{	
		class Statue : public IGameObject
		{
		public:
			//アニメーション
			enum EnStatueAnimClip {
				enStatueAnimClip_Idle,
				enStatueAnimClip_PreBite,
				enStatueAnimClip_SlowWalk,
				enStatueAnimClip_Scream,
				enStatueAnimClip_Bite,
				enStatueAnimClip_num,  //列挙内で使う要素の数を表すダミー
			};

			bool Start();
			void Update();
			~Statue();

			void SetPosition(Vector3 pos) { m_position = pos; }
			void SetDirection(Vector3 dir) { dir.Normalize(); m_direction = dir; }

			void SetStatueAnimClip(EnStatueAnimClip animClip) { m_statueAnimClip = animClip; }
		private:

			SkinModelRender* m_skinModel = nullptr;
			//アニメーションクリップ
			AnimationClip m_animationClips[enStatueAnimClip_num];
			EnStatueAnimClip m_statueAnimClip = enStatueAnimClip_Idle;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = { 1.0f,0.0f,0.0f };

			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;

		};
	}
}

