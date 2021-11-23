#pragma once
namespace nsHikageri
{
	namespace nsGameScene
	{
		class GameOver : public IGameObject
		{
		public:
			~GameOver();
			bool Start();
			void Update();
		private:
			FontRender* m_gameOverFont = nullptr;
			Vector4 m_gameOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
			Vector4 m_gameOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
			int m_gameOverExecuteCount = 0;
		};
	}
}