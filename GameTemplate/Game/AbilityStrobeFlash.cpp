#include "stdafx.h"
#include "AbilityStrobeFlash.h"
#include "FlashLight.h"
#include "FlashLightConstant.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlash;

		bool AbilityStrobeFlash::Start()
		{
			//ストロボフラッシュの明るさを設定
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			//懐中電灯がついているとき。
			if (m_flashLight->GetFlashFlag())
			{
				//ストロボフラッシュのチャージ
				StrobeFlashPrepare();

				//フラグがtrueならばストロボフラッシュ発動
				if (m_strobeFlashFlag == true)
				{
					StrobeFlash();
				}
			}
			//懐中電灯が消えたらリセット
			else
			{
				m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
				m_flashLight->GetSpotLight()->SetColor(nsFlashLightConstant::INI_FLASHLIGHT_COLOR);
				m_strobeFlashColor = INI_STROBEFLASH_COLOR;
				m_strobeFlashFlag = false;
			}
		}

		/// @brief ストロボフラッシュを発動する準備の処理
		void AbilityStrobeFlash::StrobeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				//カウントが終わるまでデクリメント
				if (m_strobeChargeCount > 0)
				{
					m_strobeChargeCount--;
				}
			}
			else
			{
				//ボタンを放したときにカウントが終わっていたら
				if (m_strobeChargeCount <= 0)
				{
					m_strobeFlashFlag = true;
				}
				//カウントをリセット
				m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
			}
		}

		/// @brief ストロボフラッシュを発動する処理
		void AbilityStrobeFlash::StrobeFlash()
		{
			//懐中電灯の明るさを設定
			m_flashLight->GetSpotLight()->SetColor(m_strobeFlashColor);
			//段々明るさを減衰
			m_strobeFlashColor -= STROBEFLASH_COLOR_DECREASE_SPEED;

			//カラーが初期値に戻ったら、ストロボフラッシュの処理を終了
			if (m_strobeFlashColor.x <= nsFlashLightConstant::INI_FLASHLIGHT_COLOR.x)
			{
				m_flashLight->GetSpotLight()->SetColor(nsFlashLightConstant::INI_FLASHLIGHT_COLOR);
				m_strobeFlashColor = INI_STROBEFLASH_COLOR;
				m_strobeFlashFlag = false;		
			}
		}

	}
}