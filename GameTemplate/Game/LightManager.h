#pragma once
#include <array>
#include "stdafx.h"
#include "DirectionLight.h"

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
		//PointLigData pointLight[POINTLIGHT_NUMBER_MAX];		//ポイントライトのデータの配列
		//SpotLigData spotLight[SPOTLIGHT_NUMBER_MAX];			//スポットライトのデータの配列
		Vector3 eyePos;					//カメラの位置
		int directionLightNum = 0;		//ディレクションライトの数
		int pointLightNum = 0;			//ポイントライトの数
		int spotLightNum = 0;			//スポットライトの数
	};
	LigDatas m_ligData;					//ライトのデータ
	int m_size = sizeof(m_ligData);		//ライトのデータのサイズ

	//何番目に作ったか記録
	int m_directionLigCreateNum = 0;
	int m_pointLigCreateNum = 0;
	int m_spotLigCreateNum = 0;

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

	//ライトの数を教える。
	int GetDirectionLigNum() { return m_ligData.directionLightNum; };
	int GetPointLigNum() { return m_ligData.pointLightNum; };
	int GetSpotLigNum() { return m_ligData.spotLightNum; };

	

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
	void SetLightCameraUpdateProjectionMatixFunc(Camera::EnUpdateProjMatrixFunc func)
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
		m_lightCamera.SetWidth(height);
		m_lightCamera.Update();
		m_ligCameraData.lightCameraProjectionMatrix = m_lightCamera.GetViewProjectionMatrix();
	}
};

