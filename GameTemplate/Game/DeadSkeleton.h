#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{
		namespace nsDeadSkeletonConstant
		{
			static const int DEADSKELETON_MODEL_NUM = 8;	//ä[çúÇÃÉÇÉfÉãÇÃêî

			static const char* DEADSKELETON_FILEPATH[DEADSKELETON_MODEL_NUM] =
			{
				"Assets/modelData/DeadSkeleton01.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
				"Assets/modelData/DeadSkeleton01.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
				"Assets/modelData/DeadSkeleton02.tkm",
			};

			//ä[çúÇÃÉÇÉfÉãÇÃà íu
			static const Vector3 DEADSKELETON_MODEL_POS[DEADSKELETON_MODEL_NUM] = {
				{400.0f,0.0f,600.0f},
				{-1800.0f,0.0f,-400.0f},
				{-200.0f,0.0f,-2400.0f},
				{600.0f,0.0f,2000.0f},
				{-5000.0f,0.0f,2600.0f},
				{-2200.0f,0.0f,9200.0f},
				{2600.0f,0.0f,8800.0f},
				{4000,0.0f,5200.0f},
			};

			
		}

		using namespace nsDeadSkeletonConstant;

		class DeadSkeleton : public IGameObject
		{			
		public:
			~DeadSkeleton();
			bool Start();
			void Update();

		private:
			SkinModelRender* m_skeletonModel[DEADSKELETON_MODEL_NUM] = {
				nullptr,// nullptr, nullptr, nullptr, nullptr,
				//nullptr, nullptr, nullptr, nullptr, nullptr
			};

			
		};
	}
}

