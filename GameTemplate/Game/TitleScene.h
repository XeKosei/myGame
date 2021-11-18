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
		//�^�C�g����ʂ̃X�v���C�g
		SpriteRender* m_titleSprite = nullptr;

		//�Q�[���V�[��
		nsGameScene::GameScene* m_gameScene = nullptr;
	};
}
