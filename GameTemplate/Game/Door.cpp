#include "stdafx.h"
#include "Door.h"
#include "GimmickConstant.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsDoorConstant;

		Door::~Door()
		{
			DeleteGO(m_doorModel);
		}

		bool Door::Start()
		{
			m_doorModel = NewGO<SkinModelRender>(0);
			switch (m_doorColor)
			{
			case enDoorColor_Red:
				m_doorModel->Init("Assets/modelData/RedDoor.tkm");
				break;
			case enDoorColor_Blue:
				m_doorModel->Init("Assets/modelData/BlueDoor.tkm");
				break;
			case enDoorColor_Green:
				m_doorModel->Init("Assets/modelData/GreenDoor.tkm");
				break;
			case enDoorColor_Yellow:
				m_doorModel->Init("Assets/modelData/YellowDoor.tkm");
				break;
			case enDoorColor_Purple:
				m_doorModel->Init("Assets/modelData/PurpleDoor.tkm");
				break;
			case enDoorColor_White:
				m_doorModel->Init("Assets/modelData/WhiteDoor.tkm");
				break;
			default:
				m_doorModel->Init("Assets/modelData/Door.tkm");
				break;
			}
			//ステージのモデルの静的物理オブジェクトを作成       
			m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());
			//※静的物理オブジェクトを作成した後でモデルの座標や回転を設定しないと、ずれが生じる。
			//位置を設定
			m_doorModel->SetPosition(m_position);

			//回転を設定
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle);
			m_doorModel->SetRotation(m_qRot);

			//静的物理オブジェクトの位置と回転を設定
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			m_executeCannotOpenCount = INI_DOOR_CANNOTOPEN_EXECUTECOUNT;

			return true;
		}

		void Door::Update()
		{
			PlayerTargetSetting();

			if (m_unlockFlag == true)
			{
				//ドアの処理
				Execute();
			}
			else
			{
				CannotOpen();
			}
		}

		void Door::PlayerTargetSetting()
		{
			//ドアのセンター位置を求める
			Vector3 centerPos;
			if (m_openFlag == false)
				centerPos = m_position + Cross(m_direction, Vector3::AxisY) * 100.0f;
			else
			{
				if (m_isOpenFromForward)
					centerPos = m_position + m_direction * 100.0f;
				else 
					centerPos = m_position - m_direction * 100.0f;
			}

			centerPos.y += 200.0f;

			Vector3 dis = centerPos - m_player->GetPlayerCamera()->GetCameraPos();
			m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、ドアの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= 0.707f)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Door);
				m_player->GetPlayerTarget()->SetTargetDoor(this);
			}
		}

		//ドアの処理
		void Door::Execute()
		{
			//ドアが開閉していないとき
			if (m_moveFlag == false)
			{
				//プレイヤーのターゲットがこのドアで、Aボタンが押されたら、ドアが開閉
				if (g_pad[0]->IsTrigger(enButtonA)
					&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Door
					&& m_player->GetPlayerTarget()->GetTargetDoor() == this )
				{
					m_moveFlag = true;

					//ドアが開くとき
					if (m_openFlag == false)
					{
						//プレイヤーとの位置関係で、扉が前に開くか奥に開くかを決める
						float dot = Dot(m_direction, m_toPlayerDir);
						if (Dot(m_direction, m_toPlayerDir) >= 0)
						{
							m_isOpenFromForward = true;
						}
						else
						{
							m_isOpenFromForward = false;
						}
					}
				}
			}
			//ドアが開閉しているとき
			else
			{
				//ドアが開いているなら、閉じる
				if (m_openFlag)
				{
					Close();
				}
				//ドアが閉じているなら、開く。
				else
				{
					Open();
				}
			}
		}

		void Door::Open()
		{
			//前から開けられたとき
			if (m_isOpenFromForward)
			{
				if (m_addAngle < MAX_DOOR_OPNE_ANGLE)
				{
					m_addAngle += DOOR_OPEN_SPEED;

				}
				else
				{
					//m_addAngle = MAX_DOOR_OPNE_ANGLE;
					m_moveFlag = false;
					m_openFlag = true;
				}
			}
			//後ろから開けられたとき
			else
			{
				if (m_addAngle > -MAX_DOOR_OPNE_ANGLE)
				{
					m_addAngle -= DOOR_OPEN_SPEED;
				}
				else
				{
					//m_addAngle = -MAX_DOOR_OPNE_ANGLE;
					m_moveFlag = false;
					m_openFlag = true;
				}	
			}
			//回転を設定
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
			m_doorModel->SetRotation(m_qRot);
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);
		}

		void Door::Close()
		{
			//前から開けられているとき
			if (m_isOpenFromForward)
			{
				if (m_addAngle > 0.0f)
				{
					m_addAngle -= DOOR_OPEN_SPEED;
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			//後ろから開けられているとき
			else
			{
				if (m_addAngle < 0.0f)
				{
					m_addAngle += DOOR_OPEN_SPEED;
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			//回転を設定
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
			m_doorModel->SetRotation(m_qRot);
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);
		}

		void Door::CannotOpen()
		{
			//プレイヤーのターゲットがこのドアで、Aボタンが押されたら、フラグをtrueに。
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Door
				&& m_player->GetPlayerTarget()->GetTargetDoor() == this)
			{
				m_executeCannotOpenFlag = true;
			}

			//フラグがtrueなら、ガチャガチャする。
			if (m_executeCannotOpenFlag)
			{
				//ガチャガチャし続ける時間をカウント
				m_executeCannotOpenCount--;

				//前に動く
				if (m_cannotOpenMoveForward)
				{
					m_addAngle += DOOR_CANNOTOPNE_MOVESPEED;
					if (m_addAngle >= MAX_CANNOTOPEN_ADDANGLE)
					{
						m_cannotOpenMoveForward = false;
					}
				}
				//後ろに動く
				else
				{
					m_addAngle -= DOOR_CANNOTOPNE_MOVESPEED;
					if (m_addAngle <= -MAX_CANNOTOPEN_ADDANGLE)
					{
						m_cannotOpenMoveForward = true;
					}
				}

				//カウントが終わったらリセット
				if (m_executeCannotOpenCount <= 0)
				{
					m_executeCannotOpenCount = INI_DOOR_CANNOTOPEN_EXECUTECOUNT;
					m_executeCannotOpenFlag = false;
					m_cannotOpenMoveForward = false;
					m_addAngle = 0.0f;
				}

				//回転を設定
				m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
				m_doorModel->SetRotation(m_qRot);
			}
		}
	}
}