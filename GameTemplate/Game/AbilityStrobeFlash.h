#pragma once

namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//ストロボのようなフラッシュ
		class AbilityStrobeFlash : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief ストロボフラッシュを発動する準備の処理
			void StrobeFlashPrepare();

			/// @brief ストロボフラッシュを発動する処理
			void StrobeFlash();

			/// @brief 懐中電灯のフラッシュが当たっているかどうかを調べる。
			/// @param chackPos 当たっているか調べたい位置
			/// @return 当たっていたかどうか
			bool CheckHitFlash(Vector3 chackPos);

			/// @brief アビリティマネージャーを設定
			/// @param abilityManager アビリティマネージャー
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief ストロボフラッシュのチャージが完了しているかどうかを取得
			/// @return チャージ完了:true 未完了:false
			bool GetIsFinishStrobeCharge() { if (m_strobeChargeCount <= 0) { return true; } else { return false; } }
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//ストロボフラッシュをチャージするカウント
			int m_strobeChargeCount = 0;

			//ストロボフラッシュのカラー(明るさ)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };

			//ストロボフラッシュを発動するフラグ
			bool m_strobeFlashFlag = false;

		};
	}
}

