#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		//透視能力(クレアボヤンス)
		class AbilityClairvoyance : public IGameObject
		{
		public:
			void ExecuteUpdate();
			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			
			bool m_isClairvoyanceActivate = false;
		};
	}
}