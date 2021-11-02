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
				enAnimationClip_Idle,
				enAnimationClip_Walk,
				enAnimationClip_Run,
				enAnimationClip_SlowWalk,
				enAnimationClip_Attack,
				enAnimationClip_Scream,
				enAnimationClip_Flinch,
				enAnimationClip_Suffer,
				enAnimationClip_PreBite,
				enAnimationClip_Bite,
				enAnimationClip_EndBite,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};

			bool Start();
			void ExecuteUpdate();

			//アニメーションクリップに関する情報を取得する関数
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