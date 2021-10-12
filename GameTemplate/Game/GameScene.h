#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; }
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
		//�f�B���N�V�������C�g
		DirectionLight* m_dirLig = nullptr;

	};

}