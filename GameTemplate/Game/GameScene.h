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
		//ステージ
		BackGround* m_backGround = nullptr;
		//プレイヤー
		nsPlayer::Player* m_player = nullptr;
		//ディレクションライト
		DirectionLight* m_dirLig = nullptr;

	};

}