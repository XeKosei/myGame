#pragma once
namespace nsHikageri
{
	struct PointLigData {
		Vector3 ligPos = { Vector3::Zero };		//���C�g�̈ʒu
		float pad0 = 0.0f;			//�p�f�B���O
		Vector3 ligColor = { Vector3::Zero };	//���C�g�̃J���[
		float ligRange = 0.0f;		//���C�g�͈̔͂̔��a
	};

	class PointLight : public IGameObject
	{
		~PointLight();
		bool Start();
		void Update();

	public:
		//�|�C���g���C�g�̃f�[�^���擾
		PointLigData* GetLigData() { return &m_pointLigData; };
		//�|�C���g���C�g�̃f�[�^�̃T�C�Y���擾
		int GetLigDataSize() { return sizeof(m_pointLigData); };

		//�|�C���g���C�g�̈ʒu��ݒ�
		void SetPosition(Vector3 pos) { m_pointLigData.ligPos = pos; };
		//�|�C���g���C�g�̈ʒu���擾
		Vector3 GetPosition() { return m_pointLigData.ligPos; };

		//�|�C���g���C�g�̐F��ݒ�
		void SetColor(Vector3 color) { m_pointLigData.ligColor = color; }
		//�|�C���g���C�g�̐F���擾
		Vector3 GetColor() { return m_pointLigData.ligColor; };

		//�|�C���g���C�g�̉e���͈͂�ݒ�
		void SetRange(float range) { m_pointLigData.ligRange = range; };
		//�|�C���g���C�g�̉e���͈͂��擾
		float GetRange() { return m_pointLigData.ligRange; };

		//�|�C���g���C�g�̔ԍ����擾����B
		int GetPointLigNum() { return m_pointLigNum; };

	private:
		PointLigData m_pointLigData;	//�|�C���g���C�g�̃f�[�^
		int m_pointLigNum = 0;		//�|�C���g���C�g�̔ԍ�(���ꂽ��)
	};
}