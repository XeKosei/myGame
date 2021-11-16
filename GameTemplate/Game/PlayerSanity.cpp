#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerSanityConstant;

		bool PlayerSanity::Start()
		{
			//最大HPを設定
			m_sanityValue = MAX_PLAYER_SANITY;

			//ダメージのスプライト
			m_hazySprite = NewGO<SpriteRender>(1);
			m_hazySprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_hazySprite->SetMulColor(INI_HAZYSPRITE_COLOR);
			m_hazySprite->SetScale({ 1.0f,1.0f,1.0f });

			//デバッグ用
			f = NewGO<FontRender>(3);
			f->SetText(L"SAN値:" + std::to_wstring(m_sanityValue));
			f->SetPosition({300.0f, 200.0f});

			//ゲームオーバー用フォント(仮)
			m_gameOverFont = NewGO<FontRender>(2);
			m_gameOverFont->SetText(L"GAME OVER");
			m_gameOverFont->SetScale(3.0f);
			m_gameOverFont->SetPosition({ -300.0f, 50.0f });
			m_gameOverFont->SetColor({ 0.0f,0.0f,0.0f,0.0f });
			m_gameOverFont->SetShadowFlag(true);
			m_gameOverFont->SetShadowOffset(3.0f);
			m_gameOverFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });

			return true;
		}

		void PlayerSanity::ExecuteUpdate()
		{
			if (m_reliefFlag == false)
			{
				Damage(DARKNESS_SANITY_DAMAGE_SPEED);
			}
			m_reliefFlag = false;

			//インターバルをカウント
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}

			//SAN値が半分を切ったら
			if (m_sanityValue <= MAX_PLAYER_SANITY / 2)
			{
				HazySpriteBlink();
			}

			if (m_sanityValue <= 0)
			{
				GameOver();
			}

			/*if (g_pad[0]->IsTrigger(enButtonX))
			{
				m_sanityValue = 100;
			}

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				Damage(5);
			}*/
		}

		/// @brief プレイヤーのSAN値を指定した値だけ減らす。
		/// @param damageNum 与えるダメージ
		void PlayerSanity::Damage(float damageNum)
		{
			if (m_player->GetPlayerState() != Player::enState_Dead)
			{
				//インターバルでなければ
				//if (m_damageIntervalCount == 0)
				//{
				m_sanityValue -= damageNum;	

				//体力が0になったら
				if (m_sanityValue <= 0)
				{
					m_sanityValue = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}

				//スプライトを設定
				SetHazySprite();

				//次にダメージを受けられるようになるまでのインターバルを設定。
				m_damageIntervalCount = DAMAGE_INTERVAL;
				//}

				//HP表示(仮)
				f->SetText(L"SAN値:" + std::to_wstring(m_sanityValue));
			}
		}

		void PlayerSanity::Recovery(int recoveryNum)
		{
			if (m_player->GetPlayerState() == Player::enState_Normal ||
				m_player->GetPlayerState() == Player::enState_Invincible)
			{
				m_sanityValue += recoveryNum;	

				//体力が最大になったら
				if (m_sanityValue >= MAX_PLAYER_SANITY)
				{
					m_sanityValue = MAX_PLAYER_SANITY;
				}

				//スプライトを設定
				SetHazySprite();

				//HP表示(仮)
				f->SetText(L"SAN値:" + std::to_wstring(m_sanityValue));
			}
		}

		void PlayerSanity::SetHazySprite()
		{	
			//残HPの比率から、スプライトの色を決定
			float color = (1 - m_sanityValue / MAX_PLAYER_SANITY) * 1.5f;
			//Rだけ色を強めることで、ブルームを起こす。。
			m_hazySprite->SetMulColor({ color, color, color, color });
			
			//スプライトの大きさを設定する(1～2の範囲)
			//float scale = 1 + m_sanityValue / MAX_PLAYER_SANITY;
			//m_hazySprite->SetScale({ scale,scale,scale });
		}

		//Hazyスプライトの点滅処理
		void PlayerSanity::HazySpriteBlink()
		{
			//スプライトの点滅
			if (m_addAlphaFlag == true)
			{
				m_addAlpha += ADD_ALPHA_SPEED;
				if (m_addAlpha >= MAX_ADD_ALPHA)
				{
					m_addAlphaFlag = false;
				}
			}
			else if (m_addAlphaFlag == false)
			{
				m_addAlpha -= ADD_ALPHA_SPEED;
				if (m_addAlpha <= MIN_ADD_ALPHA)
				{
					m_addAlphaFlag = true;
				}
			}

			//点滅分のa値を加算
			m_hazyColor = m_hazySprite->GetMulColor();
			m_hazyColor.a += m_addAlpha;
			m_hazySprite->SetMulColor(m_hazyColor);
		}

		void PlayerSanity::GameOver()
		{
			//死んだときの演出
			if (m_player->GetPlayerState() == Player::enState_Dead)
			{
				m_addAlpha += MAX_ADD_ALPHA * 1;
			}

			if (m_gameOverMoveCount > 0)
			{
				m_gameOverMoveCount--;
			}

			if (m_gameOverMoveCount <= 100 && m_gameOverMoveCount > 0)
			{
				m_gameOverFontColor.r += 0.01f;
				m_gameOverFontColor.a += 0.01f;
				m_gameOverFont->SetColor(m_gameOverFontColor);
				m_gameOverFontShadowColor.a += 0.01f;
				m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
			}
		}

	}
}