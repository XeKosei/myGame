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
			//ステージのモデル
			SkinModelRender* m_stageModel = nullptr;
			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}