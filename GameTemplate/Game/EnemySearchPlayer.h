#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			enum EnSearchArea
			{
				enSearchArea_1,
				enSearchArea_2,
				enSearchArea_3,
				enSearchArea_num
			};

			bool Start();
			void ExecuteUpdate();

			void Search();
			void CalcNextSearchPos();

			/// @brief 徘徊して移動する位置を追加する。
			/// @param pos 追加する位置
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			void SetSearchPos(EnSearchArea searchArea);

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			/// @brief 次に向かうsearchPosの番号を設定
			/// @param no 設定する番号
			void SetTargetSearchPosNo(int no) { m_targetSearchPosNo = no; }
		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			std::vector<Vector3> m_searchPos;

			//レイを飛ばす間隔
			int m_calcLineHitModelConstant = 0;

			int m_targetSearchPosNo = 0;

			EnSearchArea m_searchArea = enSearchArea_1;
		};

	}
}