#pragma once

struct SpotLigData {
	Vector3 ligPos = {Vector3::Zero};		//ライトの位置
	float pad0 = 0.0f;			//パディング
	Vector3 ligColor = {Vector3::Zero};	//ライトのカラー
	float ligRange = 0.0f;		//ライトの範囲の半径
	Vector3 ligDir = {Vector3::Zero};//射出方向
	float ligAngle = 0.0f;		//射出角度
};

class SpotLight : public IGameObject
{
	~SpotLight();
	bool Start();
	void Update();

public:
	//スポットライトのデータを取得
	SpotLigData* GetLigData() { return &m_spotLigData; };
	//スポットライトのデータのサイズを取得
	int GetLigDataSize() { return sizeof(m_spotLigData); };

	//スポットライトの位置を設定
	void SetPosition(Vector3 pos) { 
		m_spotLigData.ligPos = pos; 
	};
	//スポットライトの位置を取得
	Vector3 GetPosition() { return m_spotLigData.ligPos; };

	//スポットライトの色を設定
	void SetColor(Vector3 color) { m_spotLigData.ligColor = color; }
	//スポットライトの色を取得
	Vector3 GetColor() { return m_spotLigData.ligColor; };

	//スポットライトの影響範囲を設定
	void SetRange(float range) { m_spotLigData.ligRange = range; };
	//スポットライトの影響範囲を取得
	float GetRange() { return m_spotLigData.ligRange; };

	//スポットライトの射出方向を設定
	void SetDirection(Vector3 dir) {
		m_spotLigData.ligDir = dir;
		m_spotLigData.ligDir.Normalize();
	}
	//スポットライトの射出方向を取得
	Vector3 GetDirection() { return m_spotLigData.ligDir; };

	//スポットライトの射出角度を設定(ラジアン単位)
	void SetAngle(float angle) { m_spotLigData.ligAngle = angle; };
	//スポットライトの射出角度を取得(ラジアン単位)
	float GetAngle() { return m_spotLigData.ligAngle; };

	//スポットライトの射出角度を設定(デグリー単位)
	void SetAngleDeg(float angleDeg) { m_spotLigData.ligAngle = Math::DegToRad(angleDeg); };
	//スポットライトの射出角度を取得(デグリー単位)
	float GetAngleDeg() { return Math::RadToDeg(m_spotLigData.ligAngle); };

	//スポットライトの番号を取得する。
	int GetSpotLigNum() { return m_spotLigNum; };

private:
	SpotLigData m_spotLigData;	//ポイントライトのデータ
	int m_spotLigNum = 0;		//ポイントライトの番号(作られた順)
};

