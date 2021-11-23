#include "stdafx.h"
#include "GameSceneInclude.h"
namespace nsHikageri
{
	namespace nsGameScene
	{
		using namespace nsGameOverConstant;

		GameOver::~GameOver()
		{
			DeleteGO(m_gameOverFont);
		}

		bool GameOver::Start()
		{
			//�Q�[���I�[�o�[�p�t�H���g(��)
			m_gameOverFont = NewGO<FontRender>(2);
			m_gameOverFont->SetText(L"GAME OVER");
			m_gameOverFont->SetScale(3.0f);
			m_gameOverFont->SetPosition({ -300.0f, 50.0f });
			m_gameOverFont->SetColor(m_gameOverFontColor);
			m_gameOverFont->SetShadowFlag(true);
			m_gameOverFont->SetShadowOffset(3.0f);
			m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);

			m_gameOverExecuteCount = INI_GAMEOVER_EXECUTE_COUNT;

			return true;
		}

		void GameOver::Update()
		{
			if (m_gameOverExecuteCount > 0)
			{
				m_gameOverExecuteCount--;
			}

			//�J�E���g��0�ɂȂ�����A�I��
			if (m_gameOverExecuteCount <= 0)
			{
				DeleteGO(this);

				

			}
			else if (m_gameOverExecuteCount <= DELETE_SPRITE_TIMING)
			{
				//�X�v���C�g�����킶�����
				if (m_gameOverFontColor.a > 0.0f)
				{
					m_gameOverFontColor.r -= ADD_ALPHA_SPEED;
					m_gameOverFontColor.a -= ADD_ALPHA_SPEED;
					m_gameOverFont->SetColor(m_gameOverFontColor);
					m_gameOverFontShadowColor.a -= ADD_ALPHA_SPEED;
					m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
				}
			}
			//�Q�[���I�[�o�[�X�v���C�g���\������؂�����A�A
			else if (m_gameOverFontColor.a >= MAX_GAMEOVER_SPRITE_ALPHA)
			{
				//A�{�^���������ꂽ��A�X�v���C�g�������n�߂�B
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					m_gameOverExecuteCount = DELETE_SPRITE_TIMING;
				}
			}
			else if (m_gameOverExecuteCount <= DISPLAY_SPRITE_TIMING)
			{
				//�X�v���C�g�����킶��\��
				if (m_gameOverFontColor.a < MAX_GAMEOVER_SPRITE_ALPHA)
				{
					m_gameOverFontColor.r += ADD_ALPHA_SPEED;	//������r�l���ꏏ�ɉ��Z
					m_gameOverFontColor.a += ADD_ALPHA_SPEED;
					m_gameOverFont->SetColor(m_gameOverFontColor);
					m_gameOverFontShadowColor.a += ADD_ALPHA_SPEED;
					m_gameOverFont->SetShadowColor(m_gameOverFontShadowColor);
				}
			}
		}
	}
}