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

			//�����T���͈͂�ݒ�
			void SetIniSearchArea(EnSearchArea area) { m_searchArea = area; };

			void ExecuteUpdate();

			void Search();
			void CalcNextSearchPos();

			/// @brief �p�j���Ĉړ�����ʒu��ǉ�����B
			/// @param pos �ǉ�����ʒu
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			void SetSearchPos(EnSearchArea searchArea);

			/// @brief ���Ɍ�����searchPos�̔ԍ���ݒ�
			/// @param no �ݒ肷��ԍ�
			void SetTargetSearchPosNo(int no) { m_targetSearchPosNo = no; }

			/// @brief�@���ɜp�j����ړI�n���擾
			/// @return ���̈ʒu
			Vector3 GetTargetSearchPos() { return m_searchPos[m_targetSearchPosNo]; }
		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;

			std::vector<Vector3> m_searchPos;

			//���C���΂��Ԋu
			int m_calcLineHitModelConstant = 0;

			int m_targetSearchPosNo = 0;

			EnSearchArea m_searchArea = enSearchArea_1;
		};

	}
}