#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerSanity
		{
		public:
			~PlayerSanity();
			void Init(Player* pl);
			void ExecuteUpdate();	

			//�S��
			void Heartbeat();

			/// @brief �v���C���[��SAN�l���w�肵���l�������炷�B
			/// @param damageNum �^����_���[�W
			void Damage(float damageNum);

			/// @brief �v���C���[��SAN�l���w�肵���l�����񕜂���B
			/// @param recoveryNum �񕜗�
			void Recovery(int recoveryNum);

			/// @brief �v���C���[�����S�ł����Ԃ���ݒ�
			/// @param flag ���S�ł���:true �ł��Ȃ�:false
			void SetReliefFlag(bool flag) { m_reliefFlag = flag; }

			/// @brief SAN�l���擾
			/// @return ���݂�SAN�l
			float GetSanityValue() { return m_sanityValue; }
		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[��SAN�l
			float m_sanityValue = 0.0f;
			//���Ƀ_���[�W���󂯂邱�Ƃ��ł���悤�ɂȂ�܂ł̊Ԋu
			int m_damageIntervalCount = 0;	
			//���S�ł��邩�ǂ����B
			bool m_reliefFlag = false;

			//HP�\��(�f�o�b�O�p)
			FontRender* f = nullptr;

			//�S���֘A
			int m_heartbeatInterval = 0;
			int m_heartbeatIntervalCount = 0;
		};
	}
}