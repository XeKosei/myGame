#pragma once
class Test : public IGameObject
{
public:
	bool Start();

	void Update();

private:
	SkinModelRender* m_skin = nullptr;
	DirectionLight* m_dirLig[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};

	int m_dirLigNum = 0;
};

