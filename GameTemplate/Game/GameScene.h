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

	private:
		//�X�e�[�W
		nsBackGround::BackGround* m_backGround = nullptr;
		//�v���C���[
		nsPlayer::Player* m_player = nullptr;
		//�G�l�~�[
		nsEnemy::Enemy* m_enemy = nullptr;
		//�f�B���N�V�������C�g
		DirectionLight* m_dirLig = nullptr;

	};

}