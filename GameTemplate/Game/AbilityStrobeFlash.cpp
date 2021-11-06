#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlashConstant;

		bool AbilityStrobeFlash::Start()
		{
			//ストロボフラッシュの明るさを設定
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			//懐中電灯がついているとき。
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag())
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
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_STROBEFLASH_BATTERY_COST);
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

			if (m_strobeFlashColor.x == INI_STROBEFLASH_COLOR.x)
			{
				QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
					{
						//懐中電灯の向き
						Vector3 strobeDir = m_flashLight->GetFlashLightDir();
						strobeDir.Normalize();

						//フラッシュがエネミーの正面に当たっているならば
						if (Dot(strobeDir, enemy->GetEnemyMove()->GetDirection()) <= 0.0f)
						{
							//敵の頭への向き
							Vector3 toHeadDir = enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head") - m_flashLight->GetFlashLightPos();
							toHeadDir.Normalize();

							//二つのベクトルの内積を算出
							float dot = Dot(toHeadDir, strobeDir);

							//懐中電灯の射出角度から、
							float flashLightAngle = m_flashLight->GetFlashLightAngle();
							flashLightAngle /= 2;	//半径の射出角度が欲しいので、2で割る
							flashLightAngle /= 3.141592;	//円周率で割ることで、0～1の範囲に。
							flashLightAngle = 1 - flashLightAngle;

							//内積が射出角度よりも内側ならば
							if (dot >= flashLightAngle)
							{
								enemy->SetEnemyState(nsEnemy::Enemy::enState_Flinch);
							}
						}
						return true;
					}
				);
			}

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