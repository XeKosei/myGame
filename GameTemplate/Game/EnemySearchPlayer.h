#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer
		{
		public:
			enum EnSearchArea
			{
				enSearchArea_1,
				enSearchArea_2,
				enSearchArea_3,
				enSearchArea_4,
				enSearchArea_5,
				enSearchArea_6,
				enSearchArea_Last1,
				enSearchArea_Last2,
				enSearchArea_None,
				enSearchArea_num
			};

			~EnemySearchPlayer();
			void Init(Enemy* enemy);

			//初期探索範囲を設定
			void SetIniSearchArea(EnSearchArea area) { m_searchArea = area; };

			void ExecuteUpdate();

			void Search();
			void CalcNextSearchPos();

			/// @brief 徘徊して移動する位置を追加する。
			/// @param pos 追加する位置
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			void SetSearchPos(EnSearchArea searchArea);

			/// @brief 次に向かうsearchPosの番号を設定
			/// @param no 設定する番号
			void SetTargetSearchPosNo(int no) { m_targetSearchPosNo = no; }

			/// @brief　次に徘徊する目的地を取得
			/// @return 次の位置
			Vector3 GetTargetSearchPos() { return m_searchPos[m_targetSearchPosNo]; }
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