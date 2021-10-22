#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; }
	namespace nsEnemy { class Enemy; }

	class GameScene : public IGameObject
	{
	public:
		bool Start();
		void Update();

		void GameClear();//(��)

	private:
		//�X�e�[�W
		nsBackGround::BackGround* m_backGround = nullptr;
		//�v���C���[
		nsPlayer::Player* m_player = nullptr;
		//�G�l�~�[
		nsEnemy::Enemy* m_enemy[3] = { nullptr, nullptr, nullptr };
		//�f�B���N�V�������C�g
		DirectionLight* m_dirLig = nullptr;

		//�N���A�t�H���g(��)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
	};

}