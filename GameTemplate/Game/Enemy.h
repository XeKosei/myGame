#pragma once
#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy : public IGameObject
		{
		public:
			bool Start();
			void Update();

		private:
			//モデル
			SkinModelRender* m_enemyModel = nullptr;
			//アニメーション
			enum {
				enAnimationClip_Run,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};
			AnimationClip animationClips[enAnimationClip_num];
		};
	}
}