#pragma once

namespace nsHikageri
{
	class BackGround;
	namespace nsPlayer { class Player; }
	class GameScene : public IGameObject
	{
	public:
		bool Start();
		void Update();

	private:
		//�X�e�[�W
		BackGround* m_backGround = nullptr;
		//�v���C���[
		nsPlayer::Player* m_player = nullptr;
		//�f�B���N�V�������C�g
		DirectionLight* m_dirLig = nullptr;

	};

}