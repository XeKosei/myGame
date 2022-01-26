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
			Reset();
		}

		void AbilityStrobeFlash::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;

			m_backGround = FindGO<nsBackGround::BackGround>("backGround");

			//ストロボフラッシュの明るさを設定
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			//ストロボフラッシュのカウントを設定
			m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;

			//エフェクト
			m_chargingEff.Init(u"Assets/effect/StrobeFlashEff.efk");
			m_chargingEff.SetScale(INI_STROBEFLASH_EFF_SCALE);

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
				Reset();
			}
		}

		void AbilityStrobeFlash::Reset()
		{
			//チャージのカウントを初期値に
			m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
			//スポットライトのカラーを初期値に
			m_flashLight->GetSpotLight()->SetColor(nsFlashLightConstant::INI_FLASHLIGHT_COLOR);
			//ストロボフラッシュのカラーを初期値に
			m_strobeFlashColor = INI_STROBEFLASH_COLOR;
			//フラグを、アビリティを使っていない状態に。
			m_useAbility = false;
			//エフェクトを停止
			m_chargingEff.Stop();
			//SE
			if (m_chargeSS != nullptr)
			{
				DeleteGO(m_chargeSS);
				m_chargeSS = nullptr;
			}
			m_canPlayChargeSS = true;
			if (m_chargedSS != nullptr)
			{
				DeleteGO(m_chargedSS);
				m_chargedSS = nullptr;
			}
			m_canPlayChargedSS = true;
		}

		/// @brief ストロボフラッシュを発動する準備の処理
		void AbilityStrobeFlash::StrobeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				//チャージSE
				PlayChargeSE();

				//エフェクト
				if (m_chargingEff.IsPlay() == false)
				{
					m_chargingEff.Play();
				}
				m_chargingEff.SetPosition(m_flashLight->GetModelPos());
				m_chargingEff.Update();
				
				//カウントが終わるまでデクリメント
				if (m_strobeChargeCount > -20)
				{
					m_strobeChargeCount--;
				}
				//チャージ完了したら
				if (m_strobeChargeCount == -10)
				{
					SoundSource* ss = NewGO<SoundSource>(0);
					ss->Init(L"Assets/sound/StrobeFlashCharged.wav");
					ss->Play(false);
					//SE
					PlayChargedSE();
				}
			}
			else
			{
				//ボタンを放したときにカウントが終わっていたら
				if (m_strobeChargeCount <= 0)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_STROBEFLASH_BATTERY_COST);
					m_useAbility = true;
					//SE
					PlayChargedSE();			
				}
				//カウントをリセット
				m_strobeChargeCount = INI_STROBEFLASH_CHARGE_COUNT;
				//エフェクトを停止
				m_chargingEff.Stop();
				//チャージSEの停止
				if (m_chargeSS != nullptr)
				{
					DeleteGO(m_chargeSS);
					m_chargeSS = nullptr;
				}
			}
		}

		/// @brief ストロボフラッシュを発動する処理
		void AbilityStrobeFlash::StrobeFlash()
		{
			//懐中電灯の明るさを設定
			m_flashLight->GetSpotLight()->SetColor(m_strobeFlashColor);

			if (m_strobeFlashColor.x == INI_STROBEFLASH_COLOR.x)
			{
				//発射SE
				SoundSource* flashSS = NewGO<SoundSource>(0);
				flashSS->Init(L"Assets/sound/StrobeFlashShot.wav");
				flashSS->Play(false);

				//懐中電灯の向き
				Vector3 strobeDir = m_flashLight->GetFlashLightDir();
				strobeDir.Normalize();

				//エネミー
				//フラッシュがエネミーの正面に当たっているならば
				QueryGOs<nsEnemy::Enemy>("enemy", [this, strobeDir](nsEnemy::Enemy* enemy)->bool
					{
						if (Dot(strobeDir, enemy->GetEnemyMove()->GetDirection()) <= 0.0f)
						{
							//エネミーの頭がフラッシュの範囲だったかどうかを調べる。
							bool hitFlag = CheckHitFlash(enemy->GetEnemyModel()->GetWorldPosFromBoneName(L"Ghoul:Head"));

							//相手が噛みつき状態だったなら、
							if (enemy->GetEnemyState() == nsEnemy::Enemy::enState_Attack)
							{
								hitFlag = true;
								enemy->GetEnemyStress()->AddStress(30.0f);
							}
				
							//trueならばエネミーを怯ませる。
							if (hitFlag)
							{
								enemy->GetEnemyStress()->AddStress(35.0f);

								//相手は怯む。
								enemy->SetEnemyState(nsEnemy::Enemy::enState_Flinch);				
							}
						}
						return true;
					}
				);

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
				Reset();
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
		void AbilityStrobeFlash::PlayChargeSE()
		{
			if (m_canPlayChargeSS == true)
			{
				if (m_chargeSS != nullptr)
				{
					DeleteGO(m_chargeSS);
					m_chargeSS = nullptr;
				}

				m_chargeSS = NewGO<SoundSource>(0);
				m_chargeSS->Init(L"Assets/sound/StrobeFlashCharge.wav");
				m_chargeSS->Play(false);

				m_canPlayChargeSS = false;
			}
			else
			{
				if (m_strobeChargeCount == INI_STROBEFLASH_CHARGE_COUNT)
				{
					m_canPlayChargeSS = true;
				}
			}
		}

		void AbilityStrobeFlash::PlayChargedSE()
		{
			if (m_canPlayChargedSS == true)
			{
				if (m_chargedSS != nullptr)
				{
					DeleteGO(m_chargedSS);
					m_chargedSS = nullptr;
				}

				m_chargedSS = NewGO<SoundSource>(0);
				m_chargedSS->Init(L"Assets/sound/StrobeFlashWaitShot.wav");
				m_chargedSS->Play(false);

				m_canPlayChargedSS = false;
			}
			else
			{
				if (g_pad[0]->IsPress(enButtonRB2) == false)
				{
					m_canPlayChargedSS = true;

					if (m_chargedSS != nullptr)
					{
						DeleteGO(m_chargedSS);
						m_chargedSS = nullptr;
					}
				}
			}	
		}
	}
}