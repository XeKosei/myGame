#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; class SecretRoom; }
	namespace nsEnemy { class Enemy; }
	namespace nsGimmick { class Chandelier; class Door; }
	namespace nsItem { class ItemKey; }

	class GameScene : public IGameObject
	{
	public:
		bool Start();
		void Update();

		void GameClear();//(仮)

	private:
		//ステージ
		nsBackGround::BackGround* m_backGround = nullptr;
		nsBackGround::SecretRoom* m_secretRoom = nullptr;
		//プレイヤー
		nsPlayer::Player* m_player = nullptr;
		//エネミー
		nsEnemy::Enemy* m_enemy = nullptr;
		//ディレクションライト
		DirectionLight* m_dirLig = nullptr;
		//シャンデリア
		nsGimmick::Chandelier* m_chandelier[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
		//ドア
		nsGimmick::Door* m_door[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
		//鍵
		nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
		//

		//クリアフォント(仮)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };

		Level m_level;
	};

}