#pragma once
class Test : public IGameObject
{
public:
	bool Start();

	void Update();

	void TestDirLig();
	void TestPointLig();
	void TestSpotLig();

	void Move();
	void Turn();
	void CameraMove();
	void SpotLightMove();

private:
	SkinModelRender* m_skin = nullptr;
	Vector3 m_skinPos = { 0.0f,0.0f,0.0f};
	Vector3 m_skinMoveSpeed = { 0.0f,0.0f,1.0f };
	Quaternion m_skinQRot = { 1.0f,0.0f,0.0f, 0.0f };

	Vector3 m_cameraPos = {0.0f, 200.0f, -1500.0f};
	Vector3 m_toCameraPos = {0.0f, 200.0f, 100.0f};
	Vector3 m_cameraDir = {0.0f,0.0f,1.0f};

	DirectionLight* m_dirLig[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
	PointLight* m_pointLig[20] = { 
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr, 
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr, 
	};
	SpotLight* m_spotLig[20] = {
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
	};
	int m_dirLigNum = 0;
	int m_pointLigNum = 0;
	int m_spotLigNum = 0;
	Vector3 m_ligPos = {Vector3::Zero};

	Vector3 m_spotLigDir = {-1.0f, 0.0f, 0.0};
	Vector3 m_spotLigPos = {Vector3::Zero};

	enum {
		enAnimationClip_Idle,
		enAnimationClip_walk,
		enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
	};

	AnimationClip animationClips[enAnimationClip_num];

};

