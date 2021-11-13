#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{
		class BackGround : public IGameObject
		{
		public:
			bool Start();
			void Update();

			SkinModelRender* GetStageModel() { return m_stageModel; }
		private:
			//�X�e�[�W�̃��f��
			SkinModelRender* m_stageModel = nullptr;
			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}