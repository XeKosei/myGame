#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"
namespace nsHikageri
{
	namespace nsLMConstant
	{
		//各ライトの最大数　この数はmodel.fxのライト配列の数と一緒にしなければならない
		const int DIRECTIONLIGHT_NUMBER_MAX = 5;
		const int POINTLIGHT_NUMBER_MAX = 50;
		const int SPOTLIGHT_NUMBER_MAX = 20;
	}

	class LightManager
	{
	private:
		LightManager() = default;
		~LightManager() = default;

		static LightManager* m_instance;

		struct SpotLigCameraDatas
		{
			Matrix lightCameraProjectionMatrix;	//ライトビュープロジェクション行列
			Vector3 lightCameraPosition;	//ライトカメラの位置
			float lightCameraAngle;
			Vector3 lightCameraDirection;	//ライトカメラの向き	
			float isFlashLightSwitchOn;	//懐中電灯の電源がONかOFFか
		};

		struct LigDatas
		{
			SpotLigCameraDatas m_spotLigCameraData[3];
			DirLigData directionLight[nsLMConstant::DIRECTIONLIGHT_NUMBER_MAX];	//ディレクションライトのデータの配列	
			PointLigData pointLight[nsLMConstant::POINTLIGHT_NUMBER_MAX];		//ポイントライトのデータの配列
			SpotLigData spotLight[nsLMConstant::SPOTLIGHT_NUMBER_MAX];			//スポットライトのデータの配列
			Vector3 eyePos;					//カメラの位置
			int createdDirLigTotal = 0;		//ディレクションライトが作られた総数
			int createdPointLigTotal = 0;	//ポイントライトが作られた総数
			int createdSpotLigTotal = 0;	//スポットライトが作られた総数
		};
		LigDatas m_ligData;					//ライトのデータ
		int m_size = sizeof(m_ligData);		//ライトのデータのサイズ

		Camera m_spotLightCamera[3];	//スポットライトの光を描画する用のスポットライトの位置のカメラ

		struct LigCameraDatas
		{
			Matrix lightCameraProjectionMatrix;	//ライトビュープロジェクション行列
			Vector3 lightCameraPosition;	//ライトカメラの位置
			float pad;
			Vector3 lightCameraDirection;	//ライトカメラの向き
		};
		LigCameraDatas m_ligCameraData;
		int m_ligCameraDataSize = sizeof(m_ligCameraData);
		Camera m_lightCamera;	//シャドウマップ用のライトの位置のカメラ。テスト用
		
		//ライトの番号を管理するポインタ
		int* m_dirLigNum[nsLMConstant::DIRECTIONLIGHT_NUMBER_MAX] = { nullptr,nullptr, nullptr, nullptr, nullptr };
		int* m_pointLigNum[nsLMConstant::POINTLIGHT_NUMBER_MAX] = {
			nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr,
			nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr
		};
		int* m_spotLigNum[nsLMConstant::SPOTLIGHT_NUMBER_MAX] = {
			nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr,
			nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr
		};


	public:

		/// @brief ライトマネージャーのインスタンスを作成
		static void CreateInstance()
		{
			if (!m_instance)
			{
				m_instance = new LightManager;
			}
		}

		/// @brief ライトマネージャーのインスタンスを削除
		static void DeleteInstance()
		{
			delete m_instance;
			m_instance = nullptr;
		}

		/// @brief ライトマネージャーのインスタンスを取得する。
		static LightManager* GetInstance() { return m_instance; };

		/// @brief ライトのデータの塊を取得する(定数バッファに渡す用)
		/// @return 全ライトのデータ
		LigDatas* GetLigDatas() { return &m_ligData; };

		/// @brief ライトのデータの塊のサイズを取得する(定数バッファに渡す用)
		/// @return 全ライトのデータのサイズ
		int GetLigDataSize() { return m_size; };

		/// @brief カメラのポジションを更新する。
		void UpdateEyePos() { m_ligData.eyePos = g_camera3D->GetPosition(); };

		//新しく作られるライトに番号を与えるための関数。
		//与えたら番号を次に作られるライトに与える番号にする。
		int GetNewDirLigNum() { return m_ligData.createdDirLigTotal++; };
		int GetNewPointLigNum() { return m_ligData.createdPointLigTotal++; };
		int GetNewSpotLigNum() { return m_ligData.createdSpotLigTotal++; };

		/// @brief ライトの番号に参照できるように、アドレスを格納する処理。
		/// @param num 
		void SetDirLigNum(int* num) { m_dirLigNum[*num] = num; };
		void SetPointLigNum(int* num) { m_pointLigNum[*num] = num; };
		void SetSpotLigNum(int* num) { m_spotLigNum[*num] = num; };

		//ディレクションライト用/////////////////////////////////////////////////////////////////////////////////

		/// @brief 新しくディレクションライトが作られた際の処理
		/// @param newDirLig 新しく作られたディレクションライト
		void AddNewDirectionLight(DirLigData* newDirLigData)
		{
			//ライトの数が最初に決めた数以上ならthrowする(いっぱい作るとふつうに起こる)
			if (m_ligData.createdDirLigTotal >= nsLMConstant::DIRECTIONLIGHT_NUMBER_MAX)
			{
				MessageBoxA(nullptr, "ディレクションライトの数が最大数を超えています。\n", "エラー", MB_OK);
			}

			//新しく作られたディレクションライトのデータを配列の空きの先頭に格納する。
			m_ligData.directionLight[m_ligData.createdDirLigTotal] = *newDirLigData;
		}

		/// @brief ディレクションライトの情報を更新する。
		/// @param dirLigNum 更新したいライトの番号
		/// @param dirLigData 更新したいライトの新しいライトデータ
		void UpdateDirectionLight(int dirLigNum, DirLigData* dirLigData)
		{
			m_ligData.directionLight[dirLigNum] = *dirLigData;
		}

		/// @brief ライトを削除する時に行う処理
		/// @param num 削除するライトの番号
		void RemoveDirectionLight(int num)
		{
			DirectionLightNumMinus();

			//ライトの配列を、消すライトの位置から一つずつ詰めていく。
			for (int i = num; i < m_ligData.createdDirLigTotal - 1; i++)
			{
				m_ligData.directionLight[i] = m_ligData.directionLight[i + 1];

				//ライトの番号も一つずつ詰めていく。
				*m_dirLigNum[num + 1]--;
				m_dirLigNum[num + 1] = nullptr;
			}
		}

		/// @brief ライトが削除されたとき、作られたライトの数を減らすための関数
		void DirectionLightNumMinus()
		{
			m_ligData.createdDirLigTotal--;
			//ライトの数が0以下になる時はおかしくなっているのでthrowする(起こり得ないと信じたい)
			if (m_ligData.createdDirLigTotal < 0)
			{
				MessageBoxA(nullptr, "ディレクションライトの数がマイナスになっています。\n", "エラー", MB_OK);
			}
		}

		//ポイントライト用/////////////////////////////////////////////////////////////////////////////////

		/// @brief 新しくポイントライトが作られた際の処理
		/// @param newDirLig 新しく作られたディレクションライト
		void AddNewPointLight(PointLigData* newPointLigData)
		{
			//ライトの数が最初に決めた数以上ならthrowする(いっぱい作るとふつうに起こる)
			if (m_ligData.createdPointLigTotal >= nsLMConstant::POINTLIGHT_NUMBER_MAX)
			{
				MessageBoxA(nullptr, "ポイントライトの数が最大数を超えています。\n", "エラー", MB_OK);
			}

			//新しく作られたポイントライトのデータを配列の空きの先頭に格納する。
			m_ligData.pointLight[m_ligData.createdPointLigTotal] = *newPointLigData;
		}

		/// @brief ポイントライトの情報を更新する。
		/// @param dirLigNum 更新したいライトの番号
		/// @param dirLigData 更新したいライトの新しいライトデータ
		void UpdatePointLight(int pointLigNum, PointLigData* pointLigData)
		{
			m_ligData.pointLight[pointLigNum] = *pointLigData;
		}

		/// @brief ライトを削除する時に行う処理
		/// @param num 削除するライトの番号
		void RemovePointLight(int num)
		{
			PointLightNumMinus();

			//ライトの配列を、消すライトの位置から一つずつ詰めていく。
			for (int i = num; i < m_ligData.createdPointLigTotal - 1; i++)
			{
				m_ligData.pointLight[i] = m_ligData.pointLight[i + 1];

				//ライトの番号も一つずつ詰めていく。
				*m_pointLigNum[num + 1]--;
				m_pointLigNum[num + 1] = nullptr;
			}
		}

		/// @brief ライトが削除されたとき、作られたライトの数を減らすための関数
		void PointLightNumMinus()
		{
			m_ligData.createdPointLigTotal--;
			//ライトの数が0以下になる時はおかしくなっているのでthrowする(起こり得ないと信じたい)
			if (m_ligData.createdPointLigTotal < 0)
			{
				MessageBoxA(nullptr, "ポイントライトの数がマイナスになっています。\n", "エラー", MB_OK);
			}
		}

		//スポットライト用/////////////////////////////////////////////////////////////////////////////////

		/// @brief 新しくスポットライが作られた際の処理
		/// @param newDirLig 新しく作られたディレクションライト
		void AddNewSpotLight(SpotLigData* newSpotLigData)
		{
			//ライトの数が最初に決めた数以上ならthrowする(いっぱい作るとふつうに起こる)
			if (m_ligData.createdSpotLigTotal >= nsLMConstant::SPOTLIGHT_NUMBER_MAX)
			{
				MessageBoxA(nullptr, "スポットライトの数が最大数を超えています。\n", "エラー", MB_OK);
			}

			//新しく作られたポイントライトのデータを配列の空きの先頭に格納する。
			m_ligData.spotLight[m_ligData.createdSpotLigTotal] = *newSpotLigData;
		}

		/// @brief スポットライトの情報を更新する。
		/// @param dirLigNum 更新したいライトの番号
		/// @param dirLigData 更新したいライトの新しいライトデータ
		void UpdateSpotLight(int spotLigNum, SpotLigData* spotLigData)
		{
			m_ligData.spotLight[spotLigNum] = *spotLigData;
		}

		/// @brief ライトを削除する時に行う処理
		/// @param num 削除するライトの番号
		void RemoveSpotLight(int num)
		{
			SpotLightNumMinus();

			//ライトの配列を、消すライトの位置から一つずつ詰めていく。
			for (int i = num; i < m_ligData.createdSpotLigTotal - 1; i++)
			{
				m_ligData.spotLight[i] = m_ligData.spotLight[i + 1];

				//ライトの番号も一つずつ詰めていく。
				*m_spotLigNum[num + 1]--;
				m_spotLigNum[num + 1] = nullptr;
			}
		}

		/// @brief ライトが削除されたとき、作られたライトの数を減らすための関数
		void SpotLightNumMinus()
		{
			m_ligData.createdSpotLigTotal--;
			//ライトの数が0以下になる時はおかしくなっているのでthrowする(起こり得ないと信じたい)
			if (m_ligData.createdSpotLigTotal < 0)
			{
				MessageBoxA(nullptr, "スポットライトの数がマイナスになっています。\n", "エラー", MB_OK);
			}
		}

		//影用//////////////////////////////////////////////////////////////////////////////////////////////////

		/// @brief 影の描画に使用するライトカメラのデータの塊を取得する(定数バッファに渡す用)
		/// @return ライトカメラのデータ
		LigCameraDatas* GetLigCameraDatas() { return &m_ligCameraData; };

		/// @brief 影の描画に使用するライトカメラのデータの塊のサイズを取得する(定数バッファに渡す用)
		/// @return 
		int GetLigCameraDataSize() { return m_ligCameraDataSize; };

		/// @brief 影の描画に使用するライトカメラを取得
		/// @return ライトカメラ
		Camera* GetLightCamera()
		{
			return &m_lightCamera;
		}

		/// @brief 影の描画に使用するライトカメラの座標を指定する。
		/// @param pos ライトカメラの座標
		void SetLightCameraPosition(const Vector3& pos)
		{
			m_lightCamera.SetPosition(pos);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraPosition = pos;
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

			m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
			m_ligCameraData.lightCameraDirection.Normalize();
		}

		/// @brief 影の描画に使用するライトカメラのターゲットの座標を指定する。
		/// @param targetPos ライトカメラのターゲットの座標
		void SetLightCameraTarget(const Vector3& targetPos)
		{
			m_lightCamera.SetTarget(targetPos);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();

			m_ligCameraData.lightCameraDirection = m_lightCamera.GetTarget() - m_lightCamera.GetPosition();
			m_ligCameraData.lightCameraDirection.Normalize();
		}

		/// @brief 影の描画に使用するライトカメラの上方向を指定する。
		/// @param up カメラの上方向のベクトル
		void SetLightCameraUp(const Vector3& up)
		{
			m_lightCamera.SetUp(up);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
		}

		/// @brief 影の描画に使用するライトカメラの射影行列の更新方法を設定する。
		/// @param func 射影行列の更新方法
		void SetLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func)
		{
			m_lightCamera.SetUpdateProjMatrixFunc(func);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
		}

		/// @brief 影の描画に使用するライトカメラの横幅を指定する(並行投影限定)
		/// @param width ライトカメラの横幅
		void SetLightCameraWidth(const float& width)
		{
			m_lightCamera.SetWidth(width);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
		}

		/// @brief 影の描画に使用するライトカメラの高さを指定する(並行投影限定)
		/// @param height ライトカメラの高さ
		void SetLightCameraHeight(const float& height)
		{
			m_lightCamera.SetHeight(height);
			m_lightCamera.Update();
			m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
		}

		//スポットライトのカメラ用//////////////////////////////////////////////////////////////////////////////////////////////////

		/// @brief スポットライトに使用するライトカメラのデータの塊を取得する(定数バッファに渡す用)
		/// @return ライトカメラのデータ
		SpotLigCameraDatas* GetSpotLigCameraDatas(int no) { return &m_ligData.m_spotLigCameraData[no]; };

		/// @brief スポットライトに使用するライトカメラのデータの塊のサイズを取得する(定数バッファに渡す用)
		/// @return 
		int GetSpotLigCameraDataSize(int no) { return sizeof(m_ligData.m_spotLigCameraData[no]); };

		/// @brief スポットライトに使用するライトカメラを取得
		/// @return ライトカメラ
		Camera* GetSpotLightCamera(int no)
		{
			return &m_spotLightCamera[no];
		}

		/// @brief スポットライトに使用するライトカメラの座標を指定する。
		/// @param pos ライトカメラの座標
		void SetSpotLightCameraPosition(const Vector3& pos, int no)
		{
			m_spotLightCamera[no].SetPosition(pos);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraPosition = pos;
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();

			m_ligData.m_spotLigCameraData[no].lightCameraDirection = m_spotLightCamera[no].GetTarget() - m_spotLightCamera[no].GetPosition();
			m_ligData.m_spotLigCameraData[no].lightCameraDirection.Normalize();
		}

		/// @briefスポットライトに使用するライトカメラのターゲットの座標を指定する。
		/// @param targetPos ライトカメラのターゲットの座標
		void SetSpotLightCameraTarget(const Vector3& targetPos, int no)
		{
			m_spotLightCamera[no].SetTarget(targetPos);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();

			m_ligData.m_spotLigCameraData[no].lightCameraDirection = m_spotLightCamera[no].GetTarget() - m_spotLightCamera[no].GetPosition();
			m_ligData.m_spotLigCameraData[no].lightCameraDirection.Normalize();
		}

		void SetSpotLightCameraFar(const float& farNum, int no)
		{
			m_spotLightCamera[no].SetFar(farNum);
			m_spotLightCamera[no].Update(1.0f);
		}

		void SetSpotLightCameraAngle(const float& angle, int no)
		{

			m_spotLightCamera[no].SetViewAngle(angle);

			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();
		
			m_ligData.m_spotLigCameraData[no].lightCameraAngle = angle;
		}

		/// @brief スポットライトに使用するライトカメラの上方向を指定する。
		/// @param up カメラの上方向のベクトル
		void SetSpotLightCameraUp(const Vector3& up, int no)
		{
			m_spotLightCamera[no].SetUp(up);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();
		}

		/// @brief スポットライトに使用するライトカメラの射影行列の更新方法を設定する。
		/// @param func 射影行列の更新方法
		void SetSpotLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func, int no)
		{
			m_spotLightCamera[no].SetUpdateProjMatrixFunc(func);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();
		}

		void SetIsFlashLightSwitchOn(const bool& switchOn, int no)
		{
			m_ligData.m_spotLigCameraData[no].isFlashLightSwitchOn = switchOn;
		}

		/// @brief スポットライトに使用するライトカメラの横幅を指定する(並行投影限定)
		/// @param width ライトカメラの横幅
		void SetSpotLightCameraWidth(const float& width, int no)
		{
			m_spotLightCamera[no].SetWidth(width);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();
		}

		/// @brief 影の描画に使用するライトカメラの高さを指定する(並行投影限定)
		/// @param height ライトカメラの高さ
		void SetSpotLightCameraHeight(const float& height, int no)
		{
			m_spotLightCamera[no].SetHeight(height);
			m_spotLightCamera[no].Update(1.0f);
			m_ligData.m_spotLigCameraData[no].lightCameraProjectionMatrix = m_spotLightCamera[no].GetViewProjectionMatrix();
		}

	};
}