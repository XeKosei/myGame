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

		void GameClear();//(��)

	private:
		//�X�e�[�W
		nsBackGround::BackGround* m_backGround = nullptr;
		nsBackGround::SecretRoom* m_secretRoom = nullptr;
		//�v���C���[
		nsPlayer::Player* m_player = nullptr;
		//�G�l�~�[
		nsEnemy::Enemy* m_enemy = nullptr;
		//�f�B���N�V�������C�g
		DirectionLight* m_dirLig = nullptr;
		//�V�����f���A
		nsGimmick::Chandelier* m_chandelier[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
		//�h�A
		nsGimmick::Door* m_door[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
		//��
		nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
		//

		//�N���A�t�H���g(��)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };

		Level m_level;
	};

}