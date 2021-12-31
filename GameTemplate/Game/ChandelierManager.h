#pragma once
#include "GimmickConstant.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		using namespace nsChandelierManagerConstant;
		class ChandelierManager : public IGameObject
		{
		public:
			~ChandelierManager();
			bool Start();
			void Update();
			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }
			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
		private:
			//プレイヤーとエネミー
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			//スポットライト(スポットライトカメラと同じ数を用意)
			SpotLight* m_spotLig[2] = { nullptr, nullptr };

			//シャンデリア
			nsGimmick::Chandelier* m_chandelier[CHANDELIER_NUM] = {
				nullptr,nullptr,nullptr,nullptr,
				nullptr,nullptr,nullptr,nullptr };

			//シャンデリアの位置
			Vector3 m_chandelierPos[CHANDELIER_NUM] = {
				{ 1000.0f, 800.0f, 0.0f},
				{-1400.0f, 800.0f, -3600.0f},
				{-1000.0f, 800.0f, 3400.0f},
				{-4800.0f, 800.0f, 2800.0f},
				{-9000.0f, 800.0f,6000.0f},
				{-4600.0f, 800.0f, 5000.0f},
				{2200.0f, 800.0f, 10000.0f,},
				{2200.0f, 800.0f, 8800.0f,}
			};
		};
	}
}