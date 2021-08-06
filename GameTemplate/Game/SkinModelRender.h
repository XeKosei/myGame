#pragma once
class SkinModelRender : public IGameObject
{
public:
	//モデルの状態
	enum EModel {
		eModel,	//画面に描画されるモデル
		eModel_Shadow,	//影を描画する用モデル
		eModel_Num,		//モデルの状態の数
	};
	SkinModelRender() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
	~SkinModelRender();
	void Update();

	/// @brief モデルの情報を更新する。
	void UpdateModel();

	/// @brief モデルの描画
	/// @param rc レンダーコンテキスト
	/// @param camera 描画するカメラ
	void Render(RenderContext& rc, Camera* camera)override;


private:
	Skeleton m_skeleton;		//スケルトン
	Model m_model[eModel_Num];	//モデル
	Vector3 m_position;			//座標
	Quaternion m_qRot;			//回転
	Vector3 m_scale;			//拡大率
	AnimationClip* m_animationClips = nullptr;	//アニメーションクリップ
	int m_animationClipNum = 0;					//アニメーションクリップの数
	Animation m_animation;						//アニメーション
	bool m_isShadowCaster = false;				//このモデルは影を作るか
	float m_animation_speed = 1.0f;				//アニメーション速度
	float m_animationSpeed = 1.0f;				//アニメーション速度(何故二つあるんだ?)
};

