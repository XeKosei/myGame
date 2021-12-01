#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
#include "EyeWall.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using  namespace nsAbilityStrobeFlashConstant;

		AbilityStrobeFlash::~AbilityStrobeFlash()
		{

		}

		bool AbilityStrobeFlash::Start()
		{
			m_backGround = FindGO<nsBackGround::BackGround>("backGround");

			//ストロボフラッシュの明るさを設定
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			//ストロボフラッシュのカウントを設定
			m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;

			m_chargingEff.Init(u"Assets/effect/StrobeFlashEff.efk");
			m_chargingEff.SetScale({ 0.7f,0.7f,0.7f });

			return true;
		}

		void AbilityStrobeFlash::ExecuteUpdate()
		{
			if(m_abilityAcitveFlag == false) 
				return;

			//懐中電灯がついているとき。
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
				//ストロボフラッシュのチャージ
				StrobeFlashPrepare();

				//フラグがtrueならばストロボフラッシュ発動
				if (m_useAbility == true)
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
				m_useAbility = false;
			}
		}

		/// @brief ストロボフラッシュを発動する準備の処理
		void AbilityStrobeFlash::StrobeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				if (g_pad[0]->IsTrigger(enButtonRB2))
				{
					m_chargingEff.Play();
				}
				m_chargingEff.SetPosition(m_flashLight->GetModelPos());
				m_chargingEff.Update();
				
				//カウントが終わるまでデクリメント
				if (m_strobeChargeCount > 0)
				{
					m_strobeChargeCount--;
				}
			}
			else
			{
				m_chargingEff.Stop();
				//ボタンを放したときにカウントが終わっていたら
				if (m_strobeChargeCount <= 0)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_STROBEFLASH_BATTERY_COST);
					m_useAbility = true;
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
				//懐中電灯の向き
				Vector3 strobeDir = m_flashLight->GetFlashLightDir();
				strobeDir.Normalize();

				//エネミー
				//フラッシュがエネミーの正面に当たっているならば
				if (Dot(strobeDir, m_abilityManager->GetEnemy()->GetEnemyMove()->GetDirection()) <= 0.0f)
				{
					//エネミーの頭がフラッシュの範囲だったかどうかを調べる。
					bool hitFlag = CheckHitFlash(m_abilityManager->GetEnemy()->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head"));
					//trueならばエネミーを怯ませる。
					if (hitFlag)
					{
						//相手が噛みつき状態だったなら、
						if (m_abilityManager->GetEnemy()->GetEnemyState() == nsEnemy::Enemy::enState_Attack)
						{
							m_abilityManager->GetEnemy()->GetEnemyStress()->AddStress(600.0f);
						}

						//相手は怯む。
						m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Flinch);				
					}
				}
				//目の壁
				QueryGOs<nsGimmick::EyeWall>("eyeWall", [this, strobeDir](nsGimmick::EyeWall* eyeWall)->bool
					{
						if (Dot(strobeDir, eyeWall->GetDirection()) <= 0.0f)
						{
							//目の壁の目の位置がフラッシュの範囲だったかどうかを調べる。
							bool hitFlag = CheckHitFlash(eyeWall->GetPosition());
							if (hitFlag)
							{
								eyeWall->SetDisapperFlag(true);
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
				m_useAbility = false;
			}
		}

		/// @brief 懐中電灯のフラッシュが当たっているかどうかを調べる。
		/// @param chackPos 当たっているか調べたい位置
		/// @return 当たっていたかどうか
		bool AbilityStrobeFlash::CheckHitFlash(Vector3 checkPos)
		{		
			//間に遮蔽物がないかを調べる。
			Vector3 hitPos = Vector3::Zero;
			Vector3 startPos = m_flashLight->GetPosition();
			Vector3 endPos = checkPos;
			if (m_backGround->GetStageModel()->isLineHitModel(startPos, endPos, hitPos))
			{
				return false;
			}			
			
			//懐中電灯の向き
			Vector3 strobeDir = m_flashLight->GetFlashLightDir();
			strobeDir.Normalize();

			//調べる位置への向き
			Vector3 toCheckPosDir = checkPos - m_flashLight->GetFlashLightPos();
			toCheckPosDir.Normalize();

			//二つのベクトルの内積から、ラジアン角度を算出する。
			float angle = Dot(toCheckPosDir, strobeDir);
			angle = acos(angle);
			angle = fabsf(angle);

			//懐中電灯の射出角度と比較する
			float flashLightAngle = m_flashLight->GetFlashLightAngle();
			flashLightAngle /= 2;	//半径の値が欲しいので、2で割る

			//内積が射出角度よりも内側ならば
			if (angle <= flashLightAngle)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}