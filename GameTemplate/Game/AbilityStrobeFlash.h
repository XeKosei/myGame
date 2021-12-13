#pragma once
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsBackGround { class BachGround; }
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//ストロボのようなフラッシュ
		class AbilityStrobeFlash
		{
		public:
			~AbilityStrobeFlash();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			void Reset();

			/// @brief ストロボフラッシュを発動する準備の処理
			void StrobeFlashPrepare();

			/// @brief ストロボフラッシュを発動する処理
			void StrobeFlash();

			/// @brief 懐中電灯のフラッシュが当たっているかどうかを調べる。
			/// @param chackPos 当たっているか調べたい位置
			/// @return 当たっていたかどうか
			bool CheckHitFlash(Vector3 chackPos);

			/// @brief チャージSEの再生
			void PlayChargeSE();

			/// @brief チャージ完了後のSE
			void PlayChargedSE();

			/// @brief アビリティマネージャーを設定
			/// @param abilityManager アビリティマネージャー
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief ストロボフラッシュのチャージが完了しているかどうかを取得
			/// @return チャージ完了:true 未完了:false
			bool GetIsFinishStrobeCharge() { if (m_strobeChargeCount <= 0) { return true; } else { return false; } }
		
			/// @brief アビリティが解放されているかどうかを設定する。
			/// @param flag 解放するかどうか
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }
		private:
			nsBackGround::BackGround* m_backGround = nullptr;
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//ストロボフラッシュをチャージするカウント
			int m_strobeChargeCount = 0;

			//ストロボフラッシュのカラー(明るさ)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };

			//ストロボフラッシュを発動するフラグ
			bool m_useAbility = false;
			
			//エフェクト
			Effect m_chargingEff;

			//チャージSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;

			//アビリティが解放されているかどうか
			bool m_abilityAcitveFlag = false;
		};
	}
}

