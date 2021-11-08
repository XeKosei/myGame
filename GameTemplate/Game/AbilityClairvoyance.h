#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		//�����\��(�N���A�{�����X)
		class AbilityClairvoyance : public IGameObject
		{
		public:
			void ExecuteUpdate();
			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			
			bool m_isClairvoyanceActivate = false;
		};
	}
}