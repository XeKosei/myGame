#pragma once

struct DirLigData {
	Vector3 ligDir;	//���C�g�̕���
	float pad0;	//�p�f�B���O
	Vector3 ligColor;	//���C�g�̃J���[
	float pad1;
};

class DirectionLight : public IGameObject
{
	~DirectionLight();
	bool Start();
	void Update();

public:
	//�f�B���N�V�������C�g�̃f�[�^���擾
	DirLigData* GetLigData() { return &m_dirLigData; };
	//�f�B���N�V�������C�g�̃f�[�^�̃T�C�Y���擾
	int GetLigDataSize() { return sizeof(m_dirLigData); };

	//�f�B���N�V�������C�g�̌�����ݒ�
	void SetDirection(Vector3 dir) {
		m_dirLigData.ligDir= dir;
		m_dirLigData.ligDir.Normalize();
	}
	//�f�B���N�V�������C�g�̌������擾
	Vector3 GetDirection() { return m_dirLigData.ligDir; };

	//�f�B���N�V�������C�g�̐F��ݒ�
	void SetColor(Vector3 color) { m_dirLigData.ligColor = color; }
	//�f�B���N�V�������C�g�̐F���擾
	Vector3 GetColor() { return m_dirLigData.ligColor; };

	//�f�B���N�V�������C�g�̔ԍ����擾����B
	int GetDirLigNum() { return m_dirLigNum; };
	//�f�B���N�V�������C�g�̔ԍ����}�C�i�X����B
	void DirLigNumMinus() { m_dirLigNum--; };

private:
	DirLigData m_dirLigData;	//�f�B���N�V�������C�g�̃f�[�^
	int m_dirLigNum = 0;		//�f�B���N�V�������C�g�̔ԍ�(���ꂽ��)
};

