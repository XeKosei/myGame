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
			//m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());
			//※静的物理オブジェクトを作成した後でモデルの座標や回転を設定しないと、ずれが生じる。
			//位置を設定
			m_doorModel->SetPosition(m_position);

			//回転を設定
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle);
			m_doorModel->SetRotation(m_qRot);

			//静的物理オブジェクトの位置と回転を設定
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//phisicsStaticObjectだと、キャラコンと重なった時におかしな挙動をするので、
			//急遽キャラコンに変更
			//キャラコンを設定
			m_charaCon.Init(
				DOOR_CHARACON_WIDTH,	//半径
				DOOR_CHARACON_HEIGHT,	//高さ
				m_centerPos//初期位置
			);

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
			if (m_openFlag == false)
				m_centerPos = m_position + Cross(m_direction, Vector3::AxisY) * DOOR_CENTER_POS_X;
			else
			{
				if (m_isOpenFromForward)
					m_centerPos = m_position + m_direction * DOOR_CENTER_POS_X;
				else 
					m_centerPos = m_position - m_direction * DOOR_CENTER_POS_X;
			}

			m_centerPos.y += DOOR_CENTER_POS_Y;

			Vector3 dis = m_centerPos - m_player->GetPlayerCamera()->GetCameraPos();
			m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//プレイヤーとの距離が近く、ドアの方を向いていたら
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= DOOR_CATCH_EYE_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Door);
				m_player->GetPlayerTarget()->SetTargetDoor(this);
			}

			m_charaCon.SetPosition(m_centerPos);
		}

		//ドアの処理
		void Door::Execute()
		{
			//ドアが開閉していないとき
			if (m_moveFlag == false)
			{
				//ドアが開くとき
				if (m_openFlag == false)
				{
					//エネミーが近くに来ると、扉が開く。
					QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
						{
							float dis = (m_position - enemy->GetEnemyMove()->GetPosition()).Length();
							if (dis <= 200.0f)
							{
								m_moveFlag = true;

								//エネミーとの位置関係で、扉が前に開くか奥に開くかを決める
								Vector3 toEnemyDir = m_centerPos - enemy->GetEnemyMove()->GetPosition();
								toEnemyDir.Normalize();
								float dot = Dot(m_direction, toEnemyDir);
								if (dot >= 0)
								{
									m_isOpenFromForward = true;
								}
								else
								{
									m_isOpenFromForward = false;
								}
							}
							return true;
						}
					);
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
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//SE
			SEManage(enDoorSound_Open);
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
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//SE
			SEManage(enDoorSound_Close);
		}

		void Door::CannotOpen()
		{
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

				//SE
				SEManage(enDoorSound_Locked);
			}
		}

		void Door::SEManage(EnDoorSounds soundKind)
		{
			if (m_canPlaySS == true)
			{
				if (m_ss != nullptr)
				{
					DeleteGO(m_ss);
					m_ss = nullptr;
				}
				switch (soundKind)
				{
				case enDoorSound_Locked:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorLocked.wav");
					m_ss->Play(false);
					m_canPlaySS = false;
					break;
				case enDoorSound_Open:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorOpen.wav");
					m_ss->Play(false);
					m_canPlaySS = false;
					break;
				case enDoorSound_Close:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorClose.wav");
					m_ss->Play(false);
					m_canPlaySS = false;				
					break;
				default:
					break;
				}
			}
			else
			{
				switch (soundKind)
				{
				case enDoorSound_Locked:
					if (m_executeCannotOpenFlag == false)
						m_canPlaySS = true;
					break;
				case enDoorSound_Open:
					if (m_openFlag == true)
						m_canPlaySS = true;
					break;
				case enDoorSound_Close:
					if (m_openFlag == false)
						m_canPlaySS = true;
					break;
				default:
					break;
				}
			}
		}

		void Door::PlayerTouchDoor()
		{
			//鍵がかかっているならば、ガチャガチャする処理を行う。
			if (m_unlockFlag == false)
			{
				m_executeCannotOpenFlag = true;
			}
			else if (m_moveFlag == false)
			{
				m_moveFlag = true;

				//ドアが開くとき
				if (m_openFlag == false)
				{
					//プレイヤーとの位置関係で、扉が前に開くか奥に開くかを決める
					float dot = Dot(m_direction, m_toPlayerDir);
					if (dot >= 0)
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
	}
}