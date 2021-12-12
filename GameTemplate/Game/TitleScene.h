#pragma once
namespace nsHikageri
{
	namespace nsTitleScene
	{
		class TitleScene : public IGameObject
		{
		public:
			~TitleScene();
			bool Start();

			void Update();

			void FirstMove();
			void SecondMove();
			void Blinking();
			void DeleteMove();

			void Synopsis();

			void GameStart();

		private:
			//タイトル画面のスプライト
			SpriteRender* m_titleSprite = nullptr;
			Vector4 m_titleSpriteColor = { 0.0f,0.0f,0.0f,0.0f };
			bool m_firstMoveFlag = false;
			bool m_secondMoveFlag = false;
			int m_secondMoveInterval = 0;
			bool m_blinkingFlag = false;
			bool m_blinkingAddColorFlag = false;

			bool m_deleteMoveFlag = false;
			bool m_synopsisFlag = false;
			bool m_synopsisDeleteFlag = false;
			bool m_gameStartMoveFlag = false;

			FontRender* m_titleFont = nullptr;
			Vector4 m_titleFontColor = { 0.0f,0.0f,0.0f,0.0f };

			FontRender* m_synopsisFont = nullptr;
			Vector4 m_synopsisFontColor = {0.0f,0.0f,0.0f,0.0f};
			int m_synopsisFontInterval = 0;

			SpriteRender* m_blackSprite = nullptr;
			Vector4 m_blackSpriteColor = {1.0f,1.0f,1.0f,1.0f};
		};
	}
}
