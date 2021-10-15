#include "stdafx.h"
#include "Player.h"
#include "PlayerMove.h"
#include "PlayerCamera.h"
#include "PlayerAction.h"
#include "PlayerHP.h"
#include "PlayerConstant.h"
#include "FlashLight.h"

namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerConstant;

		Player::~Player()
		{
			DeleteGO(m_playerModel);
			DeleteGO(m_playerMove);
			//DeleteGO(m_playerCamera);
		}
		bool Player::Start()
		{
			//プレイヤーの初期位置
			m_position = INI_PLAYER_POSITION;

			//プレイヤーのモデルを作成
			m_playerModel = NewGO<SkinModelRender>(0);
			m_playerModel->Init("Assets/modelData/unityChan.tkm", "Assets/modelData/unityChan.tks", animationClips, enAnimationClip_num);
			m_playerModel->SetPosition(m_position);
			m_playerModel->SetSpotLightCasterFlag(false);

			//キャラクターコントローラーを作成
			m_charaCon.Init(
				PLAYER_MODEL_WIDTH,	//半径
				PLAYER_MODEL_HEIGHT,	//高さ
				m_position//初期位置
			);

			//アニメーションをロード
			animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
			animationClips[enAnimationClip_Idle].SetLoopFlag(true);	//ループモーションにする。
			animationClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
			animationClips[enAnimationClip_walk].SetLoopFlag(true);	//ループモーションにする。

			//プレイヤー関係のインスタンスを作成
			m_playerMove = NewGO<PlayerMove>(0);
			m_playerMove->SetPlayer(this);
			m_playerCamera = NewGO<PlayerCamera>(0);
			m_playerCamera->SetPlayer(this);
			m_playerAction = NewGO<PlayerAction>(0);
			m_playerAction->SetPlayer(this);
			m_playerAction->SetPlayerCamera(m_playerCamera);
			m_playerAction->SetPlayerMove(m_playerMove);
			m_playerHP = NewGO<PlayerHP>(0);
			m_playerHP->SetPlayer(this);

			//懐中電灯を生成
			m_flashLight = NewGO<nsFlashLight::FlashLight>(0);
			m_flashLight->SetPlayer(this);

			return true;
		}

		void Player::Update()
		{
			//死んだら何もできない(仮)
			if (m_deadFlag == true)
				return;

			m_playerMove->ExecuteUpdate();
			m_playerAction->ExecuteUpdate();
			m_playerCamera->ExecuteUpdate();
		}
	}
}