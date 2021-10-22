#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerHPConstant;

		bool PlayerHP::Start()
		{
			//最大HPを設定
			m_HP = MAX_PLAYER_HP;
			m_bloodSprite = NewGO<SpriteRender>(1);
			m_bloodSprite->Init("Assets/Image/BloodBlur.DDS", 1280, 720);
			m_bloodSprite->SetMulColor(INI_BLOODSPRITE_COLOR);

			//デバッグ用
			f = NewGO<FontRender>(0);
			//f->SetText(std::to_wstring(m_HP));

			//ゲームオーバー用フォント(仮)
			m_gameOverFont = NewGO<FontRender>(2);
			m_gameOverFont->SetText(L"GAME OVER");
			m_gameOverFont->SetScale(3.0f);
			m_gameOverFont->SetPosition({ -300.0f, 50.0f });
			m_gameOverFont->SetColor({0.0f,0.0f,0.0f,0.0f});
			m_gameOverFont->SetShadowFlag(true);
			m_gameOverFont->SetShadowOffset(3.0f);
			m_gameOverFont->SetShadowColor({ 0.0f,0.0f,0.0f,0.0f });

			return true;
		}

		void PlayerHP::ExecuteUpdate()
		{
			//インターバルをカウント
			if (m_damageIntervalCount != 0)
			{
				m_damageIntervalCount--;
			}

			//HPが半分を切ったら
			if (m_HP <= MAX_PLAYER_HP / 2)
			{
				BloodSprite();
			}
			if (m_HP <= 0)
			{
				GameOver();
			}
					
		}

		/// @brief プレイヤーのダメージを指定した値だけ減らす。
		/// @param damageNum 与えるダメージ
		void PlayerHP::Damage(int damageNum)
		{
			if (m_player->GetPlayerState() != Player::enState_Dead)
			{
				//インターバルでなければ
				//if (m_damageIntervalCount == 0)
				//{
				m_HP -= damageNum;

				if (m_HP > MAX_PLAYER_HP / 3)
				{
					//プレイヤーの体力に合わせて、スプライトのr値とa値を上げる。
					float rgbColor = (1 - m_HP / MAX_PLAYER_HP) * 150.0f;
					float a = (1 - m_HP / MAX_PLAYER_HP) / 80.0f;
					m_bloodSprite->SetMulColor({ rgbColor, rgbColor / 10, rgbColor / 10, a });
				}
				else
				{
					float rgbColor = (1 - m_HP / MAX_PLAYER_HP) * 1000.0f;
					float a = (1 - m_HP / MAX_PLAYER_HP) / 80.0f;
					m_bloodSprite->SetMulColor({ rgbColor, rgbColor / 100, rgbColor / 100, a });
				}


				//体力が0になったら
				if (m_HP <= 0)
				{
					m_HP = 0;
					m_player->SetPlayerState(Player::enState_Dead);
				}
				//次にダメージを受けられるようになるまでのインターバルを設定。
				m_damageIntervalCount = DAMAGE_INTERVAL;
				//}

				//HP表示(仮)
				//f->SetText(std::to_wstring(m_HP));
			}
		}

		
		//画面端の血のスプライトの処理
		void PlayerHP::BloodSprite()
		{
			//死んだときの演出
			if (m_player->GetPlayerState() == Player::enState_Dead)
			{
				m_addRed += MAX_ADD_RED * 1;
			}
			//スプライトの点滅
			else if (m_addRedFlag == true)
			{
				m_addRed += ADD_RED_SPEED;
				if (m_addRed >= MAX_ADD_RED)
				{
					m_addRedFlag = false;
				}
			}
			else if (m_addRedFlag == false)
			{
				m_addRed -= ADD_RED_SPEED;
				if (m_addRed <= MIN_ADD_RED)
				{
					m_addRedFlag = true;
				}
			}

			//点滅分の赤色を加算
			m_bloodColor = m_bloodSprite->GetMulColor();
			m_bloodColor.a += m_addRed;
			m_bloodSprite->SetMulColor(m_bloodColor);
		}

		void PlayerHP::GameOver()
		{
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