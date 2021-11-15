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

			/// @brief �p�j���Ĉړ�����ʒu��ǉ�����B
			/// @param pos �ǉ�����ʒu
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			void SetSearchPos(EnSearchArea searchArea);

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;

			std::vector<Vector3> m_searchPos;

			//���C���΂��Ԋu
			int m_calcLineHitModelConstant = 0;

			int m_targetPosNo = 0;

			EnSearchArea m_searchArea = enSearchArea_1;
		};

	}
}