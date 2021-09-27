#pragma once

struct SpotLigData {
	Vector3 ligPos = {Vector3::Zero};		//���C�g�̈ʒu
	float pad0 = 0.0f;			//�p�f�B���O
	Vector3 ligColor = {Vector3::Zero};	//���C�g�̃J���[
	float ligRange = 0.0f;		//���C�g�͈̔͂̔��a
	Vector3 ligDir = {Vector3::Zero};//�ˏo����
	float ligAngle = 0.0f;		//�ˏo�p�x
};

class SpotLight : public IGameObject
{
	~SpotLight();
	bool Start();
	void Update();

public:
	//�X�|�b�g���C�g�̃f�[�^���擾
	SpotLigData* GetLigData() { return &m_spotLigData; };
	//�X�|�b�g���C�g�̃f�[�^�̃T�C�Y���擾
	int GetLigDataSize() { return sizeof(m_spotLigData); };

	//�X�|�b�g���C�g�̈ʒu��ݒ�
	void SetPosition(Vector3 pos) { 
		m_spotLigData.ligPos = pos; 
	};
	//�X�|�b�g���C�g�̈ʒu���擾
	Vector3 GetPosition() { return m_spotLigData.ligPos; };

	//�X�|�b�g���C�g�̐F��ݒ�
	void SetColor(Vector3 color) { m_spotLigData.ligColor = color; }
	//�X�|�b�g���C�g�̐F���擾
	Vector3 GetColor() { return m_spotLigData.ligColor; };

	//�X�|�b�g���C�g�̉e���͈͂�ݒ�
	void SetRange(float range) { m_spotLigData.ligRange = range; };
	//�X�|�b�g���C�g�̉e���͈͂��擾
	float GetRange() { return m_spotLigData.ligRange; };

	//�X�|�b�g���C�g�̎ˏo������ݒ�
	void SetDirection(Vector3 dir) {
		m_spotLigData.ligDir = dir;
		m_spotLigData.ligDir.Normalize();
	}
	//�X�|�b�g���C�g�̎ˏo�������擾
	Vector3 GetDirection() { return m_spotLigData.ligDir; };

	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�(���W�A���P��)
	void SetAngle(float angle) { m_spotLigData.ligAngle = angle; };
	//�X�|�b�g���C�g�̎ˏo�p�x���擾(���W�A���P��)
	float GetAngle() { return m_spotLigData.ligAngle; };

	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�(�f�O���[�P��)
	void SetAngleDeg(float angleDeg) { m_spotLigData.ligAngle = Math::DegToRad(angleDeg); };
	//�X�|�b�g���C�g�̎ˏo�p�x���擾(�f�O���[�P��)
	float GetAngleDeg() { return Math::RadToDeg(m_spotLigData.ligAngle); };

	//�X�|�b�g���C�g�̔ԍ����擾����B
	int GetSpotLigNum() { return m_spotLigNum; };

private:
	SpotLigData m_spotLigData;	//�|�C���g���C�g�̃f�[�^
	int m_spotLigNum = 0;		//�|�C���g���C�g�̔ԍ�(���ꂽ��)
};

