#pragma once
class SkinModelRender : public IGameObject
{
public:
	//���f���̏��
	enum EModel {
		eModel,	//��ʂɕ`�悳��郂�f��
		eModel_Shadow,	//�e��`�悷��p���f��
		eModel_Num,		//���f���̏�Ԃ̐�
	};
	SkinModelRender() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
	~SkinModelRender();
	void Update();

	/// @brief ���f���̏����X�V����B
	void UpdateModel();

	/// @brief ���f���̕`��
	/// @param rc �����_�[�R���e�L�X�g
	/// @param camera �`�悷��J����
	void Render(RenderContext& rc, Camera* camera)override;


private:
	Skeleton m_skeleton;		//�X�P���g��
	Model m_model[eModel_Num];	//���f��
	Vector3 m_position;			//���W
	Quaternion m_qRot;			//��]
	Vector3 m_scale;			//�g�嗦
	AnimationClip* m_animationClips = nullptr;	//�A�j���[�V�����N���b�v
	int m_animationClipNum = 0;					//�A�j���[�V�����N���b�v�̐�
	Animation m_animation;						//�A�j���[�V����
	bool m_isShadowCaster = false;				//���̃��f���͉e����邩
	float m_animation_speed = 1.0f;				//�A�j���[�V�������x
	float m_animationSpeed = 1.0f;				//�A�j���[�V�������x(���̓�����?)
};

