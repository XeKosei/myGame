#pragma once
class Test : public IGameObject
{
public:
	bool Start();

	void Update();

	void TestDirLig();
	void TestPointLig();

private:
	SkinModelRender* m_skin = nullptr;
	DirectionLight* m_dirLig[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
	PointLight* m_pointLig[20] = { 
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr, 
		nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr, 
	};
	int m_dirLigNum = 0;
	int m_pointLigNum = 0;
	Vector3 m_pointLigPos = {Vector3::Zero};

	enum {
		enAnimationClip_Idle,
		enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
	};

	AnimationClip animationClips[enAnimationClip_num];

};

