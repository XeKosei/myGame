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
		bool Door::Start()
		{
			//仮の位置と回転
			m_position = { 0.0f, 0.0f, 150.0f };
			m_direction = {-1.0f,0.0f,0.0f };

			m_doorModel = NewGO<SkinModelRender>(0);
			m_doorModel->Init("Assets/modelData/Door.tkm");

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
			
			return true;
		}

		void Door::Update()
		{
			//ドアの処理を開始
			Execute();
		}
		//ドアの処理
		void Door::Execute()
		{
			//ドアが開閉していないとき
			if (m_moveFlag == false)
			{
				//プレイヤーへの向き
				Vector3 dis = m_position - m_player->GetPlayerMove()->GetPosition();
				Vector3 toPlayerDir = dis;
				toPlayerDir.Normalize();

				//プレイヤーとの距離が近く、ドアの方を向いていて、ボタンが押されたら、ドアが開閉し始める
				if (g_pad[0]->IsTrigger(enButtonA)
					&& dis.Length() <= 500.0f
					&& Dot(m_player->GetPlayerCamera()->GetDirection(), toPlayerDir) >= 0.5f )
				{
					m_moveFlag = true;

					//ドアが開くとき
					if (m_openFlag == false)
					{
						//プレイヤーとの位置関係で、扉が前に開くか奥に開くかを決める
						float dot = Dot(m_direction, toPlayerDir);
						if (Dot(m_direction, toPlayerDir) >= 0)
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
	}
}