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
				enAnimationClip_Suffer,
				enAnimationClip_PreBite,
				enAnimationClip_Bite,
				enAnimationClip_EndBite,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};

			bool Start();
			void ExecuteUpdate();

			//�A�j���[�V�����N���b�v�Ɋւ�������擾����֐�
			AnimationClip* GetAnimationClip() { return m_animationClips; };
			int GetAnimationClipNum() { return enAnimationClip_num; };

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//�A�j���[�V�����N���b�v
			AnimationClip m_animationClips[enAnimationClip_num];

		};
	}
}