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
			//�A�j���[�V����
			enum {
				enAnimationClip_Idle,
				enAnimationClip_Run,
				enAnimationClip_SlowWalk,
				enAnimationClip_Scream,
				enAnimationClip_Bite,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};

			SkinModelRender* m_skinModel = nullptr;
			//�A�j���[�V�����N���b�v
			AnimationClip m_animationClips[enAnimationClip_num];

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = { 1.0f,0.0f,0.0f };

			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;


		};
	}
}

