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

			//血のスプライト
			m_bloodSprite = NewGO<SpriteRender>(1);
			m_bloodSprite->Init("Assets/Image/Hazy.DDS", 1280, 720);
			m_bloodSprite->SetMulColor(INI_BLOODSPRITE_COLOR);
			m_bloodSprite->SetScale({ 2.0f,2.0f,2.0f });


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
				BloodSpriteBlink();
			}

			if (m_HP <= 0)
			{
				GameOver();
			}
			
			if (g_pad[0]->IsTrigger(enButtonX))
			{
				m_HP = 100;
			}

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				Damage(5);
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

				//血のスプライトを設定
				SetBloodSprite();

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

		void PlayerHP::SetBloodSprite()
		{
			//プレイヤーの残体力によって血のスプライトを変化させる。
			if (m_HP > BIG_DAMAGE_LINE)
			{
				//スプライトの色は通常。
				m_bloodSprite->SetMulColor({ DAMAGED_BLOODSPRITE_COLOR });
			}
			else
			{
				//残HPの比率から、スプライトの色を決定
				float bloodColor = (1 - m_HP / MAX_PLAYER_HP);
				//Rだけ色を強めることで、ブルームを起こす。。
				m_bloodSprite->SetMulColor({ bloodColor, bloodColor, bloodColor, 1.0f });
			}

			//スプライトの大きさを設定する(1～2の範囲)
			float bloodScale = 1 + m_HP / MAX_PLAYER_HP;
			m_bloodSprite->SetScale({ bloodScale,bloodScale,bloodScale });
		}

		//画面端の血のスプライトの処理
		void PlayerHP::BloodSpriteBlink()
		{
			//スプライトの点滅
			if (m_addRedFlag == true)
			{
				m_addAlpha += ADD_ALPHA_SPEED;
				if (m_addAlpha >= MAX_ADD_ALPHA)
				{
					m_addRedFlag = false;
				}
			}
			else if (m_addRedFlag == false)
			{
				m_addAlpha -= ADD_ALPHA_SPEED;
				if (m_addAlpha <= MIN_ADD_ALPHA)
				{
					m_addRedFlag = true;
				}
			}

			//点滅分のa値を加算
			m_bloodColor = m_bloodSprite->GetMulColor();
			m_bloodColor.a += m_addAlpha;
			m_bloodSprite->SetMulColor(m_bloodColor);
		}

		void PlayerHP::GameOver()
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