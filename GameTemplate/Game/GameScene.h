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
		//ステージ
		nsBackGround::BackGround* m_backGround = nullptr;
		//プレイヤー
		nsPlayer::Player* m_player = nullptr;
		//エネミー
		nsEnemy::Enemy* m_enemy = nullptr;
		//ディレクションライト
		DirectionLight* m_dirLig = nullptr;

	};

}