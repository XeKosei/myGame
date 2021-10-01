#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"

namespace
{
	//各ライトの最大数　この数はmodel.fxのライト配列の数と一緒にしなければならない
	const int DIRECTIONLIGHT_NUMBER_MAX = 5;
	const int POINTLIGHT_NUMBER_MAX = 20;
	const int SPOTLIGHT_NUMBER_MAX = 20;
}

class LightManager
{
private:
	LightManager() = default;
	~LightManager() = default;

	static LightManager* m_instance;

	struct LigDatas
	{
		DirLigData directionLight[DIRECTIONLIGHT_NUMBER_MAX];	//ディレクションライトのデータの配列	
		PointLigData pointLight[POINTLIGHT_NUMBER_MAX];		//ポイントライトのデータの配列
		SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];			//スポットライトのデータの配列
		Vector3 eyePos;					//カメラの位置
		int createdDirLigTotal = 0;		//ディレクションライトが作られた総数
		int createdPointLigTotal = 0;	//ポイントライトが作られた総数
		int createdSpotLigTotal = 0;	//スポットライトが作られた総数
	};
	LigDatas m_ligData;					//ライトのデータ
	int m_size = sizeof(m_ligData);		//ライトのデータのサイズ

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

	LigCameraDatas m_spotLigCameraData;
	int m_spotLigCameraDataSize = sizeof(m_spotLigCameraData);
	Camera m_spotLightCamera;	//スポットライトの光を描画する用のスポットライトの位置のカメラ

	//ライトの番号を管理するポインタ
	int* m_dirLigNum[DIRECTIONLIGHT_NUMBER_MAX] = { nullptr,nullptr, nullptr, nullptr, nullptr };
	int* m_pointLigNum[POINTLIGHT_NUMBER_MAX] = {
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr,
		nullptr,nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr, nullptr, nullptr
	};
	int* m_spotLigNum[SPOTLIGHT_NUMBER_MAX] = {
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
		if (m_ligData.createdDirLigTotal >= DIRECTIONLIGHT_NUMBER_MAX)
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
		if (m_ligData.createdPointLigTotal >= POINTLIGHT_NUMBER_MAX)
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
		if (m_ligData.createdSpotLigTotal >= SPOTLIGHT_NUMBER_MAX)
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
	LigCameraDatas* GetSpotLigCameraDatas() { return &m_spotLigCameraData; };

	/// @brief スポットライトに使用するライトカメラのデータの塊のサイズを取得する(定数バッファに渡す用)
	/// @return 
	int GetSpotLigCameraDataSize() { return m_spotLigCameraDataSize; };

	/// @brief スポットライトに使用するライトカメラを取得
	/// @return ライトカメラ
	Camera* GetSpotLightCamera()
	{
		return &m_spotLightCamera;
	}

	/// @brief スポットライトに使用するライトカメラの座標を指定する。
	/// @param pos ライトカメラの座標
	void SetSpotLightCameraPosition(const Vector3& pos)
	{
		m_spotLightCamera.SetPosition(pos);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraPosition = pos;
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();

		m_spotLigCameraData.lightCameraDirection = m_spotLightCamera.GetTarget() - m_spotLightCamera.GetPosition();
		m_spotLigCameraData.lightCameraDirection.Normalize();
	}

	/// @briefスポットライトに使用するライトカメラのターゲットの座標を指定する。
	/// @param targetPos ライトカメラのターゲットの座標
	void SetSpotLightCameraTarget(const Vector3& targetPos)
	{
		m_spotLightCamera.SetTarget(targetPos);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();

		m_spotLigCameraData.lightCameraDirection = m_spotLightCamera.GetTarget() - m_spotLightCamera.GetPosition();
		m_spotLigCameraData.lightCameraDirection.Normalize();
	}

	void SetSpotLightCameraAngle(const float angle)
	{

		m_spotLightCamera.SetViewAngle(angle);

		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief スポットライトに使用するライトカメラの上方向を指定する。
	/// @param up カメラの上方向のベクトル
	void SetSpotLightCameraUp(const Vector3& up)
	{
		m_spotLightCamera.SetUp(up);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief スポットライトに使用するライトカメラの射影行列の更新方法を設定する。
	/// @param func 射影行列の更新方法
	void SetSpotLightCameraUpdateProjMatrixFunc(Camera::EnUpdateProjMatrixFunc func)
	{
		m_spotLightCamera.SetUpdateProjMatrixFunc(func);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief スポットライトに使用するライトカメラの横幅を指定する(並行投影限定)
	/// @param width ライトカメラの横幅
	void SetSpotLightCameraWidth(const float& width)
	{
		m_spotLightCamera.SetWidth(width);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

	/// @brief 影の描画に使用するライトカメラの高さを指定する(並行投影限定)
	/// @param height ライトカメラの高さ
	void SetSpotLightCameraHeight(const float& height)
	{
		m_spotLightCamera.SetHeight(height);
		m_spotLightCamera.Update(1.0f);
		m_spotLigCameraData.lightCameraProjectionMatrix = m_spotLightCamera.GetViewProjectionMatrix();
	}

};