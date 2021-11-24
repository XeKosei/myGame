#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsFlashLight { class FlashLight; }
	namespace nsBackGround { class BackGround; class SecretRoom;}
	namespace nsEnemy { class Enemy; }
	namespace nsGimmick { class ChandelierManager; class Door;  class EyeWall; }
	namespace nsItem { class ItemKey; class ItemFlashLightParts; class ItemTranquilizer; 
	class ItemBattery; class ItemMessagePaper;}

	namespace nsGameScene
	{
		class GameOver;
		class GameClear;

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
				enGameStep_06,
				enGameStep_GameOver,
				enGameStep_GameClear,
				enGameStep_num
			};

			~GameScene();
			bool Start();
			void Update();

			void GameManagement();

			void ExecuteUpdateStep01();
			void ExecuteUpdateStep02();
			void ExecuteUpdateStep03();
			void ExecuteUpdateStep04();
			void ExecuteUpdateStep05();

			/// @brief ゲーム進行を次へ進めるかどうかのフラグ
			/// @param flag 進める:true 進めない:false
			void SetCanGoNextStepFlag(bool flag) { m_canGoNextStepFlag = flag; };

		private:
			//ゲームオーバークラス
			GameOver* m_gameOver = nullptr;
			//ゲームクリアクラス
			GameClear* m_gameClear = nullptr;

			//ステージ
			nsBackGround::BackGround* m_backGround = nullptr;
			nsBackGround::SecretRoom* m_secretRoom = nullptr;
			//プレイヤー
			nsPlayer::Player* m_player = nullptr;
			//懐中電灯
			nsFlashLight::FlashLight* m_flashLight = nullptr;
			//エネミー
			nsEnemy::Enemy* m_enemy = nullptr;
			//ディレクションライト
			DirectionLight* m_dirLig = nullptr;

			//シャンデリア
			nsGimmick::ChandelierManager* m_chandelierManager = nullptr;
			//ドア
			nsGimmick::Door* m_door[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
			//目の付いた壁
			nsGimmick::EyeWall* m_eyeWall[3] = { nullptr, nullptr, nullptr };
			//鍵
			nsItem::ItemKey* m_key[5] = { nullptr, nullptr, nullptr,nullptr, nullptr };
			//懐中電灯のパーツ
			nsItem::ItemFlashLightParts* m_flashLightParts[3] = { nullptr, nullptr, nullptr };
			//精神安定剤
			nsItem::ItemTranquilizer* m_tranquilizer[10] = {
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr };

			//電池
			nsItem::ItemBattery* m_battery[15] = {
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr,nullptr };

			//メッセージペーパー
			nsItem::ItemMessagePaper* m_messagePaper[1] = {
				nullptr
			};

			//脱出する通路の先のポイントライト
			PointLight* m_pointLight = nullptr;

			//Level m_level;

			//ゲームの進行段階
			EnGameSteps m_gameStep = enGameStep_num;
			bool m_canGoNextStepFlag = false;
		};
	}
}