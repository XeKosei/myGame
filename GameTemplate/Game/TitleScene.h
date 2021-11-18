#pragma once
namespace nsHikageri
{
	namespace nsGameScene { class GameScene; }

	class TitleScene : public IGameObject
	{
	public:
		~TitleScene();
		bool Start();

		void Update();

	private:
		//タイトル画面のスプライト
		SpriteRender* m_titleSprite = nullptr;

		//ゲームシーン
		nsGameScene::GameScene* m_gameScene = nullptr;
	};
}
