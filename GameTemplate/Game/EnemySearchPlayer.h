#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			void Search();
			void CalcNextSearchPos();

			/// @brief 徘徊して移動する位置を追加する。
			/// @param pos 追加する位置
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			std::vector<Vector3> m_searchPos;

			//レイを飛ばす間隔
			int m_calcLineHitModelConstant = 0;

			int m_targetPosNo = 0;
		};

	}
}