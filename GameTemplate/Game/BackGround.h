#pragma once
namespace nsHikageri
{
	//BackGround�N���X�ŗ��p����萔
	namespace nsBGConstant
	{
		
	}

	class BackGround : public IGameObject
	{
	public:
		bool Start();
		void Update();

	private:
		SkinModelRender* m_stageModel = nullptr;
	};
}