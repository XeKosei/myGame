#pragma once
namespace nsHikageri
{
	struct DirLigData {
		Vector3 ligDir = { Vector3::Zero };		//ライトの方向
		float pad0 = 0.0f;			//パディング
		Vector3 ligColor = { Vector3::Zero };	//ライトのカラー
		float pad1 = 0.0f;			//パディング
	};

	class DirectionLight : public IGameObject
	{
		~DirectionLight();
		bool Start();
		void Update();

	public:
		//ディレクションライトのデータを取得
		DirLigData* GetLigData() { return &m_dirLigData; };
		//ディレクションライトのデータのサイズを取得
		int GetLigDataSize() { return sizeof(m_dirLigData); };

		//ディレクションライトの向きを設定
		void SetDirection(Vector3 dir) {
			m_dirLigData.ligDir = dir;
			m_dirLigData.ligDir.Normalize();
		}
		//ディレクションライトの向きを取得
		Vector3 GetDirection() { return m_dirLigData.ligDir; };

		//ディレクションライトの色を設定
		void SetColor(Vector3 color) { m_dirLigData.ligColor = color; }
		//ディレクションライトの色を取得
		Vector3 GetColor() { return m_dirLigData.ligColor; };

		//ディレクションライトの番号を取得する。
		int GetDirLigNum() { return m_dirLigNum; };

	private:
		DirLigData m_dirLigData;	//ディレクションライトのデータ
		int m_dirLigNum = 0;		//ディレクションライトの番号(作られた順)
	};

}