#pragma once
class Test : public IGameObject
{
public:
	bool Start();

	void Update();

	void TestDirLig();
	void TestPointLig();
	void TestSpotLig();

private:
	SkinModelRender* m_skin = nullptr;
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


	enum {
		enAnimationClip_Idle,
		enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
	};

	AnimationClip animationClips[enAnimationClip_num];

};

