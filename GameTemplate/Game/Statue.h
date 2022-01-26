#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{	
		class Statue : public IGameObject
		{
		public:
			//�A�j���[�V����
			enum EnStatueAnimClip {
				enStatueAnimClip_Idle,
				enStatueAnimClip_PreBite,
				enStatueAnimClip_SlowWalk,
				enStatueAnimClip_Scream,
				enStatueAnimClip_Bite,
				enStatueAnimClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};

			bool Start();
			void Update();
			~Statue();

			void SetPosition(Vector3 pos) { m_position = pos; }
			void SetDirection(Vector3 dir) { dir.Normalize(); m_direction = dir; }

			void SetStatueAnimClip(EnStatueAnimClip animClip) { m_statueAnimClip = animClip; }
		private:

			SkinModelRender* m_skinModel = nullptr;
			//�A�j���[�V�����N���b�v
			AnimationClip m_animationClips[enStatueAnimClip_num];
			EnStatueAnimClip m_statueAnimClip = enStatueAnimClip_Idle;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = { 1.0f,0.0f,0.0f };

			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;

		};
	}
}

