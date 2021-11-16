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

		void GameClear();//(仮)

		/// @brief ゲーム進行を次へ進めるかどうかのフラグ
		/// @param flag 進める:true 進めない:false
		void SetCanGoNextStepFlag(bool flag) { m_canGoNextStepFlag = flag; };

	private:
		//ゲームの進行段階
		EnGameSteps m_gameStep = enGameStep_num;
		bool m_canGoNextStepFlag = false;

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
		nsGimmick::Chandelier* m_chandelier[10] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };
		//ドア
		nsGimmick::Door* m_door[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
		//目の付いた壁
		nsGimmick::EyeWall* m_eyeWall[3] = { nullptr, nullptr, nullptr };
		//鍵
		nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
		//懐中電灯のパーツ
		nsItem::ItemFlashLightParts* m_flashLightParts[3] = {nullptr, nullptr, nullptr};
		//精神安定剤
		nsItem::ItemTranquilizer* m_tranquilizer[10] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };

		//電池
		nsItem::ItemBattery* m_battery[15] = {
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr,
			nullptr,nullptr,nullptr,nullptr,nullptr };

		//クリアフォント(仮)
		FontRender* m_clearFont = nullptr;
		int m_clearFontMoveCount = 100;
		Vector4 m_clearOverFontColor = { 0.0f,0.0f,0.0f,0.0f };
		Vector4 m_clearOverFontShadowColor = { 0.0f,0.0f,0.0f,0.0f };

		Level m_level;
	};

}