#pragma once
namespace nsHikageri
{
	class SkinModelRender : public IGameObject
	{
	public:
		//���f���̏��
		enum EModel {
			eModel,	//��ʂɕ`�悳��郂�f��
			eModel_Shadow,	//�e��`�悷��p���f��
			eModel_SpotLight,	//�X�|�b�g���C�g�}�b�v�Ɏg�p���郂�f��
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

		/// @brief ���f���̏������֐��@�A�j���[�V������
		/// @param modelPath ���f���t�@�C���̃p�X(.tkm)
		/// @param skeletonPath �X�P���g���t�@�C���p�X(.tks)
		/// @param animClips �A�j���[�V�����N���b�v�z��
		/// @param animClipNum �A�j���[�V�����N���b�v�̐�
		void Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum);

		/// @brief ���f���̏������֐�
		/// @param modelPath ���f���t�@�C���̃p�X(.tkm)
		/// @param skeletonPath �X�P���g���t�@�C���p�X(.tks)
		void Init(const char* modelPath, const char* skeletonPath);

		/// @brief ���f���̏������֐��@���f���p�X������
		/// @param modelPath ���f���t�@�C���̃p�X(.tkm)
		void Init(const char* modelPath);

		/// @brief �A�j���[�V�����̍Đ�
		/// @param animationNo �A�j���[�V�����ԍ�
		/// @param interpolateTime �A�j���[�V�����̕⊮����
		void PlayAnimation(int animationNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animationNo, interpolateTime);
			m_animation.Progress(m_animationSpeed / 60.0f);
			UpdateModel();
		}

		/// @brief �A�j���[�V�������Đ����Ă��邩?
		/// @return �Đ����Ă���:true �Đ����Ă��Ȃ�:false
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// @brief �A�j���[�V�����̍Đ����x��ݒ肷��B
		/// @param animSpeed �Đ����x
		void SetAnimationSpeed(float animSpeed)
		{
			m_animationSpeed = animSpeed;
		}

		/// @brief ���f���̍��W��ݒ肷��
		/// @param pos ���W
		void SetPosition(Vector3 pos)
		{
			m_position = pos;
			UpdateModel();
		}
		void SetPositionX(float posX)
		{
			m_position.x = posX;
			UpdateModel();
		}
		void SetPositionZ(float posZ)
		{
			m_position.z = posZ;
			UpdateModel();
		}

		/// @brief ���f���̉�]��ݒ肷��B
		/// @param qRot ��]
		void SetRotation(Quaternion qRot)
		{
			m_qRot = qRot;
			UpdateModel();
		}

		/// @brief ���f���̊g�嗦��ݒ肷��B
		/// @param scale �g�嗦
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
			UpdateModel();
		}

		/// @brief ���f���̃��[���h�s��𒼐ڃZ�b�g����B
		/// @param world ���[���h�s��
		void SetMatrix(Matrix world)
		{
			for (auto& model : m_model) {
				model.UpdateWorldMatrix(world);
				m_skeleton.Update(world);
			}
		}

		/// @brief ���f�����e����邩�ǂ�����ݒ肷��B
		/// @param isShadowCaster ���:true ���Ȃ�:false
		void SetShadowCasterFlag(bool isShadowCaster)
		{
			m_isShadowCaster = isShadowCaster;
		}

		/// @brief ���f�����X�|�b�g���C�g�̌����󂯂邩�ǂ���
		/// @param isSpotLightCaster �󂯂�:true �󂯂Ȃ�:false
		void SetSpotLightCasterFlag(bool isSpotLightCaster)
		{
			m_isSpotLightCaster = isSpotLightCaster;
		}

		/// @brief ���f���̍��W���擾
		/// @return ���W
		Vector3 GetPosition()
		{
			return m_position;
		}
		float GetPositionX()
		{
			return m_position.x;
		}
		float GetPositionY()
		{
			return m_position.y;
		}
		float GetPositionZ()
		{
			return m_position.z;
		}

		/// @brief ���f���̉�]���擾
		/// @return ��]
		Quaternion GetRotation()
		{
			return m_qRot;
		}

		/// @brief ���f���̊g�嗦���擾
		/// @return �g�嗦
		Vector3 GetScale()
		{
			return m_scale;
		}

		/// @brief ���f�����擾
		/// @param model �r���[�|�[�g�ԍ�(�J�����ԍ�)
		/// @return �ԍ�����擾�������f���ւ̎Q��
		Model& GetModel(EModel model = eModel)
		{
			return m_model[model];
		}

		/// @brief �{�[���̖��O���炻�̃{�[���̃��[���h�s����擾����(�炵��)�B
		/// @param boneName �{�[���̖��O
		/// @return �{�[���̃��[���h�s��
		Matrix GetWorldMatrixFromBoneName(const wchar_t* boneName);

		static void PreLoadModel(const char* tkmFilePath);

	private:
		Skeleton m_skeleton;		//�X�P���g��
		Model m_model[eModel_Num];	//���f��
		Vector3 m_position;			//���W
		Quaternion m_qRot;			//��]
		Vector3 m_scale;			//�g�嗦
		AnimationClip* m_animationClips = nullptr;	//�A�j���[�V�����N���b�v
		int m_animationClipNum = 0;					//�A�j���[�V�����N���b�v�̐�
		Animation m_animation;						//�A�j���[�V����
		bool m_isShadowCaster = true;				//���̃��f���͉e����邩
		float m_animation_speed = 1.0f;				//�A�j���[�V�������x
		float m_animationSpeed = 1.0f;				//�A�j���[�V�������x(���̓�����?)
		bool m_isSpotLightCaster = true;			//���̃��f���̓X�|�b�g���C�g�̌����󂯂邩�ǂ���
	};

}