#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsFlashLight
	{	
		//�����d��
		class FlashLight : public IGameObject
		{
		public:
			~FlashLight();
			bool Start();
			void Update();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

		private:
			SkinModelRender* m_flashLightModel = nullptr;
			//�X�|�b�g���C�g
			SpotLight* m_spotLight = nullptr;
			//����
			Vector3 m_direction = { 0.0f, 0.0f, 0.0 };
			//�ʒu
			Vector3 m_position = Vector3::Zero;
			//�v���C���[
			nsPlayer::Player* m_player = nullptr;
		};
	}
}
