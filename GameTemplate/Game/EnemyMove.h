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
		class EnemyMove
		{
		public:
			enum EnMoveStates
			{
				enMoveState_Straight,
				enMoveState_RouteSearch,
				enMoveState_num
			};

			~EnemyMove();
			void Init(Enemy* enemy);
			void ExecuteUpdate();



			void Move();
			/// @brief 経路探索で道を検索する処理
			/// @param pos 開始座標
			/// @param targetPos 移動目標座標
			void RouteSearch(Vector3 pos, Vector3 targetPos);
			//経路探索での移動処理
			void RouteSearchMove();

			void Turn();

			void FootStepsSE();	//足音

			void SetPosition(Vector3 pos);

			/// @brief Enemyのm_positionを取得
			/// @return エネミーの位置
			Vector3 GetPosition() { return m_position; };

			Vector3 GetOldPos() { return m_oldPos; }

			/// @brief Enemyの向きを取得。
			/// @return エネミーの向き
			Vector3 GetDirection() { return m_direction; }

			/// @brief Enemyの移動速度を取得
			/// @return エネミーの移動速度
			Vector3 GetVelocity() { return m_velocity; }

			/// @brief 速度をリセット
			void ResetVelocity() { m_velocity = Vector3::Zero; }

			/// @brief エネミーが向かう位置を設定
			/// @param pos エネミーが向かう位置
			void SetTargetPos(Vector3 pos) { m_targetPos = pos; }

			/// @brief エネミーのターゲット位置を取得する。
			/// @return エネミーのターゲット位置
			Vector3 GetTargetPos() { return m_targetPos; }

			/// @brief エネミーの移動の速さを設定
			/// @param speed エネミーの移動の速さ
			void SetMoveSpeed(float speed) { m_moveSpeed = speed; };

			/// @brief 動きが遅くなっているかどうかのフラグを取得する
			/// @return 動きが遅くなっているかどうか
			bool GetSlowMoveFlag() { return m_slowMoveFlag; };
			/// @brief 動きが遅くなるかどうか
			/// @param flag true:遅くなる　false:遅くならない
			void SetSlowMoveFlag(bool flag) { m_slowMoveFlag = flag; }

			void SetMoveState(EnMoveStates moveState) { m_moveState = moveState; }

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//移動の仕方
			EnMoveStates m_moveState = enMoveState_RouteSearch;
			//位置
			Vector3 m_position = { Vector3::Zero };
			Vector3 m_oldPos = Vector3::Zero;
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

			//足音
			int m_footStepInterval = 0;
			float m_footStepVolume = 0.0f;
		};

	}
}