#include "stdafx.h"
#include "DeadSkeleton.h"
namespace nsHikageri
{
	namespace nsBackGround
	{
		DeadSkeleton::~DeadSkeleton()
		{
			//骸骨のモデルを消す
			for (int no = 0; no < DEADSKELETON_MODEL_NUM; no++)
			{
				DeleteGO(m_skeletonModel[no]);
			}
		}

		bool DeadSkeleton::Start()
		{
			//骸骨のモデルを生成
			for (int no = 0; no < DEADSKELETON_MODEL_NUM; no++)
			{
				m_skeletonModel[no] = NewGO<SkinModelRender>(0);
				m_skeletonModel[no]->Init(DEADSKELETON_FILEPATH[no]);
				m_skeletonModel[no]->SetPosition(DEADSKELETON_MODEL_POS[no]);
			}

			return true;
		}

		void DeadSkeleton::Update()
		{

		}
	}
}