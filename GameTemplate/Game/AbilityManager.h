#pragma once
namespace nsHikageri
{
	namespace nsBackGround { class SecretRoom; }
	namespace nsEnemy { class Enemy; }

	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager
		{
		public:
			~AbilityManager();
			void Init(FlashLight* flashLight);

			nsEnemy::Enemy* GetEnemy() { return m_enemy; }
			nsBackGround::SecretRoom* GetSecretRoom() { return m_secretRoom; }

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			nsEnemy::Enemy* m_enemy = nullptr;
			nsBackGround::SecretRoom* m_secretRoom = nullptr;

		};
	}
}

