#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"
#include "TknFile.h"
namespace nsHikageri
{
	namespace nsAI { class NaviMesh; class Path; class PathFinding; };
	namespace nsEnemy
	{
		class Enemy;
		class EnemyMove : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			void Move();
			//経路探索での移動処理
			void RouteSearchMove();

			void Turn();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			void SetPosition(Vector3 pos) { 
				m_position = pos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
				m_enemy->GetEnemyModel()->SetPosition(m_position);
			}

			/// @brief Enemyのm_positionを取得
			/// @return エネミーの位置
			Vector3 GetPosition() { return m_position; };

			/// @brief Enemyの向きを取得。
			/// @return エネミーの向き
			Vector3 GetDirection() { return m_direction; }

			/// @brief Enemyの移動速度を取得
			/// @return エネミーの移動速度
			Vector3 GetVelocity() { return m_velocity; }

			/// @brief エネミーが向かう位置を設定
			/// @param pos エネミーが向かう位置
			void SetTarget(Vector3 pos) { m_targetPos = pos; }

			/// @brief エネミーのターゲット位置を取得する。
			/// @return エネミーのターゲット位置
			Vector3 GetTarget() { return m_targetPos; }

			/// @brief エネミーの移動の速さを取得
			/// @param speed エネミーの移動の速さ
			void SetMoveSpeed(float speed) { m_moveSpeed = speed; };

			/// @brief 動きが遅くなっているかどうかのフラグを取得する
			/// @return 動きが遅くなっているかどうか
			bool GetSlowMoveFlag() { return m_slowMoveFlag; };
			/// @brief 動きが遅くなるかどうか
			/// @param flag true:遅くなる　false:遅くならない
			void SetSlowMoveFlag(bool flag) { m_slowMoveFlag = flag; }

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//位置
			Vector3 m_position = { Vector3::Zero };
			//エネミーが動く速さ
			float m_moveSpeed = 0.0f;
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//向き
			Vector3 m_direction = { 0.0f, 0.0f, 0.0f };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//エネミーが向かう位置
			Vector3 m_targetPos = { Vector3::Zero };

			//動きが遅くなるかどうかのフラグ
			bool m_slowMoveFlag = false;	

			//経路探索関連
			nsAI::NaviMesh m_nvmMesh;
			nsAI::Path m_path;
			nsAI::PathFinding m_pathFiding;
			TknFile m_tknFile;
			int m_pathFindingInterval = 0;
		};

	}
}