#pragma once
namespace nsHikageri
{
	//BackGroundƒNƒ‰ƒX‚Å—˜—p‚·‚é’è”
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