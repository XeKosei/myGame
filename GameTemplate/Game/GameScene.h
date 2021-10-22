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

		void GameClear();//(仮)

	private:
		//ステージ
		nsBackGround::BackGround* m_backGround = nullptr;
		//プレイヤー
		nsPlayer::Player* m_player = nullptr;
		//エネミー
		nsEnemy::Enemy* m_enemy[3] = { nullptr, nullptr, nullptr };
		//ディレクションライト
		DirectionLight* m_dirLig = nullptr;

		//クリアフォント(仮)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };
	};

}