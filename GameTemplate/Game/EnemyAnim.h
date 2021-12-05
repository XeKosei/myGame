#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyAnim : public IGameObject
		{
		public:
			//�A�j���[�V����
			enum {
				enAnimationClip_Idle,
				enAnimationClip_Walk,
				enAnimationClip_Run,
				enAnimationClip_SlowWalk,
				enAnimationClip_Attack,
				enAnimationClip_Scream,
				enAnimationClip_Flinch,
				enAnimationClip_Petrifaction,
				enAnimationClip_Suffer,
				enAnimationClip_PreBite,
				enAnimationClip_Bite,
				enAnimationClip_EndBite,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};

			~EnemyAnim();
			void Init(Enemy* enemy);
			void ExecuteUpdate();

			//�A�j���[�V�����N���b�v�Ɋւ�������擾����֐�
			AnimationClip* GetAnimationClip() { return m_animationClips; };
			int GetAnimationClipNum() { return enAnimationClip_num; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//�A�j���[�V�����N���b�v
			AnimationClip m_animationClips[enAnimationClip_num];

		};
	}
}