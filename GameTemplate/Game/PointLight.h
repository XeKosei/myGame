#pragma once
namespace nsHikageri
{
	struct PointLigData {
		Vector3 ligPos = { Vector3::Zero };		//ライトの位置
		float pad0 = 0.0f;			//パディング
		Vector3 ligColor = { Vector3::Zero };	//ライトのカラー
		float ligRange = 0.0f;		//ライトの範囲の半径
	};

	class PointLight : public IGameObject
	{
		~PointLight();
		bool Start();
		void Update();

	public:
		//ポイントライトのデータを取得
		PointLigData* GetLigData() { return &m_pointLigData; };
		//ポイントライトのデータのサイズを取得
		int GetLigDataSize() { return sizeof(m_pointLigData); };

		//ポイントライトの位置を設定
		void SetPosition(Vector3 pos) { m_pointLigData.ligPos = pos; };
		//ポイントライトの位置を取得
		Vector3 GetPosition() { return m_pointLigData.ligPos; };

		//ポイントライトの色を設定
		void SetColor(Vector3 color) { m_pointLigData.ligColor = color; }
		//ポイントライトの色を取得
		Vector3 GetColor() { return m_pointLigData.ligColor; };

		//ポイントライトの影響範囲を設定
		void SetRange(float range) { m_pointLigData.ligRange = range; };
		//ポイントライトの影響範囲を取得
		float GetRange() { return m_pointLigData.ligRange; };

		//ポイントライトの番号を取得する。
		int GetPointLigNum() { return m_pointLigNum; };

	private:
		PointLigData m_pointLigData;	//ポイントライトのデータ
		int m_pointLigNum = 0;		//ポイントライトの番号(作られた順)
	};
}