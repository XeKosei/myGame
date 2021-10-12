#pragma once
#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy : public IGameObject
		{
		public:
			bool Start();
			void Update();

		private:
			//���f��
			SkinModelRender* m_enemyModel = nullptr;
			//�A�j���[�V����
			enum {
				enAnimationClip_Run,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};
			AnimationClip animationClips[enAnimationClip_num];
		};
	}
}