#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyAnim : public IGameObject
		{
		public:
			//アニメーション
			enum {
				enAnimationClip_Run,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};

			bool Start();
			void ExecuteUpdate();

			AnimationClip* GetAnimationClip() { return m_animationClips; };
			int GetAnimationClipNum() { return enAnimationClip_num; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//アニメーションクリップ
			AnimationClip m_animationClips[enAnimationClip_num];

		};
	}
}