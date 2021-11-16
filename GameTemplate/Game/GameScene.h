#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; class SecretRoom;}
	namespace nsEnemy { class Enemy; }
	namespace nsGimmick { class Chandelier; class Door;  class EyeWall;}
	namespace nsItem { class ItemKey; class ItemFlashLightParts; class ItemTranquilizer; class ItemBattery; }

	class GameScene : public IGameObject
	{
	public:
		enum EnGameSteps
		{
			enGameStep_01,
			enGameStep_02,
			enGameStep_03,
			enGameStep_04,
			enGameStep_05,
			enGameStep_num
		};

		bool Start();
		void Update();

		void ExecuteUpdateStep01();
		void ExecuteUpdateStep02();
		void ExecuteUpdateStep03();
		void ExecuteUpdateStep04();
		void ExecuteUpdateStep05();

		void GameClear();//(��)

		/// @brief �Q�[���i�s�����֐i�߂邩�ǂ����̃t���O
		/// @param flag �i�߂�:true �i�߂Ȃ�:false
		void SetCanGoNextStepFlag(bool flag) { m_canGoNextStepFlag = flag; };

	private:
		//�Q�[���̐i�s�i�K
		EnGameSteps m_gameStep = enGameStep_num;
		bool m_canGoNextStepFlag = false;

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
		nsGimmick::Chandelier* m_chandelier[10] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };
		//�h�A
		nsGimmick::Door* m_door[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
		//�ڂ̕t������
		nsGimmick::EyeWall* m_eyeWall[3] = { nullptr, nullptr, nullptr };
		//��
		nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
		//�����d���̃p�[�c
		nsItem::ItemFlashLightParts* m_flashLightParts[3] = {nullptr, nullptr, nullptr};
		//���_�����
		nsItem::ItemTranquilizer* m_tranquilizer[10] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };

		//�d�r
		nsItem::ItemBattery* m_battery[15] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };

		//�N���A�t�H���g(��)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };

		Level m_level;
	};

}