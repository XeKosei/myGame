#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerSanityConstant;

		PlayerSanity::~PlayerSanity()
		{
			DeleteGO(f);
		}

		void PlayerSanity::Init(Player* pl)
		{
			m_player = pl;

			//最大HPを設定
			m_sanityValue = MAX_PLAYER_SANITY;

			//デバッグ用
			f = NewGO<FontRender>(3);
			f->SetText(L"SAN値:" + std::to_wstring(m_sanityValue));
			f->SetPosition({300.0f, 200.0f});
			f->SetScale(0.0f);

		}

		void PlayerSanity::ExecuteUpdate()
		{
			//安心できない状況ならば、SAN値減少
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
				m_player->GetPlayerUI()->SetHazySprite();

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
				m_player->GetPlayerUI()->SetHazySprite();

				//HP表示(仮)
				f->SetText(L"SAN値:" + std::to_wstring(m_sanityValue));
			}
		}
	}
}