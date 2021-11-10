#pragma once
namespace nsHikageri
{
	namespace nsBackGround { class SecretRoom; }
	namespace nsEnemy { class Enemy; }

	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager : public IGameObject
		{
		public:
			bool Start();
			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
					/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			nsEnemy::Enemy* GetEnemy() { return m_enemy; }
			nsBackGround::SecretRoom* GetSecretRoom() { return m_secretRoom; }

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			nsEnemy::Enemy* m_enemy = nullptr;
			nsBackGround::SecretRoom* m_secretRoom = nullptr;
		};
	}
}

