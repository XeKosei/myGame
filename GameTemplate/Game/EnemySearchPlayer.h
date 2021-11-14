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

			/// @brief �p�j���Ĉړ�����ʒu��ǉ�����B
			/// @param pos �ǉ�����ʒu
			void PushSearchPos(Vector3 pos) { m_searchPos.push_back(pos); }

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;

			bool m_searchFlag = false;

			std::vector<Vector3> m_searchPos;
			FontRender* m_fontTest = nullptr;

			int m_targetPosNo = 0;
		};

	}
}