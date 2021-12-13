#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyVoice
		{
		public:
			~EnemyVoice();
			void Init(Enemy* enemy);
			void ExecuteUpdate();

			void PlayVoice();

			void PetrifactionVoice();

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//声
			SoundSource* m_voiceSS = nullptr;

			bool m_canPlayVoiceSS = true;

			int m_oldEnemyState = 0;
		};
	}
}
