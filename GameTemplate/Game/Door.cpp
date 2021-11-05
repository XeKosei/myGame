#include "stdafx.h"
#include "Door.h"
#include "GimmickConstant.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		bool Door::Start()
		{
			m_position = { 0.0f, 0.0f, 150.0f };
			m_direction = {-1.0f,0.0f,0.0f };
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, m_defaultAngle);

			m_doorModel = NewGO<SkinModelRender>(0);
			m_doorModel->Init("Assets/modelData/Door.tkm");
			m_doorModel->SetPosition(m_position);
			m_doorModel->SetRotation(qRot);
			//ステージのモデルの静的物理オブジェクトを作成       
			//m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());

			return true;
		}

		void Door::Update()
		{
			//ドアが動いていないとき
			if (m_moveFlag == false)
			{
				//ボタンが押されたら、ドアが動き始める。(開くか閉じるか)
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					m_moveFlag = true;
					
					//ドアが開くとき
					if (m_openFlag == false)
					{
						//プレイヤーへの向き
						Vector3 m_toPlayerDir = m_player->GetPlayerMove()->GetPosition() - m_position;
						m_toPlayerDir.Normalize();
						//プレイヤーとの位置関係で、扉が前に開くか奥に開くかを決める
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
			//ドアが動いているとき
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
			//前からあけられたとき
			if (m_isOpenFromForward)
			{
				if (m_addAngle > -3.14f / 2)
				{
					m_addAngle -= 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = true;
				}
			}
			else
			{
				if (m_addAngle < 3.14f / 2)
				{
					m_addAngle += 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = true;
				}	
			}
		}

		void Door::Close()
		{
			if (m_isOpenFromForward)
			{
				if (m_addAngle < 0.0f)
				{
					m_addAngle += 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			else
			{
				if (m_addAngle > 0.0f)
				{
					m_addAngle -= 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
		}
	}
}