#pragma once
namespace nsHikageri
{
	class SkinModelRenderEX : public IGameObject
	{
	public:
		//モデルの状態
		enum EModelEX {	
			eModelEX_Clairvoyance,	//透視用モデル
			eModelEX_Stone,	//石化用モデル
			eModelEX_Num,		//モデルの状態の最低の数
		};
		SkinModelRenderEX() :m_position(Vector3::Zero), m_qRot(g_quatIdentity), m_scale(Vector3::One) {}
		~SkinModelRenderEX();
		void Update();

		/// @brief モデルの情報を更新する。
		void UpdateModel();

		/// @brief モデルの描画
		/// @param rc レンダーコンテキスト
		/// @param camera 描画するカメラ
		void Render(RenderContext& rc, Camera* camera)override;

		/// @brief モデルの初期化関数　アニメーションつき
		/// @param modelPath モデルファイルのパス(.tkm)
		/// @param skeletonPath スケルトンファイルパス(.tks)
		/// @param animClips アニメーションクリップ配列
		/// @param animClipNum アニメーションクリップの数
		void Init(const char* modelPath, const char* skeletonPath, AnimationClip* animClips, int animClipNum);

		/// @brief モデルの初期化関数
		/// @param modelPath モデルファイルのパス(.tkm)
		/// @param skeletonPath スケルトンファイルパス(.tks)
		void Init(const char* modelPath, const char* skeletonPath);

		/// @brief モデルの初期化関数　モデルパスだけ版
		/// @param modelPath モデルファイルのパス(.tkm)
		void Init(const char* modelPath);

		/// @brief アニメーションの再生
		/// @param animationNo アニメーション番号
		/// @param interpolateTime アニメーションの補完時間
		void PlayAnimation(int animationNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animationNo, interpolateTime);
			m_animation.Progress(m_animationSpeed / 60.0f);
			UpdateModel();
		}

		/// @brief アニメーションを再生しているか?
		/// @return 再生している:true 再生していない:false
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// @brief アニメーションの再生速度を設定する。
		/// @param animSpeed 再生速度
		void SetAnimationSpeed(float animSpeed)
		{
			m_animationSpeed = animSpeed;
		}

		/// @brief モデルの座標を設定する
		/// @param pos 座標
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

		/// @brief モデルの回転を設定する。
		/// @param qRot 回転
		void SetRotation(Quaternion qRot)
		{
			m_qRot = qRot;
			UpdateModel();
		}

		/// @brief モデルの拡大率を設定する。
		/// @param scale 拡大率
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
			UpdateModel();
		}

		/// @brief モデルのワールド行列を直接セットする。
		/// @param world ワールド行列
		void SetMatrix(Matrix world)
		{
			for (auto& model : m_model) {
				model.UpdateWorldMatrix(world);
				m_skeleton.Update(world);
			}
		}

		/// @brief モデルが透視可能かどうか
		/// @param isClairvoyanceCaster 可能:true 不可能:false
		void SetClairvoyanceCasterFlag(bool isClairvoyanceCaster)
		{
			m_isClairvoyanceCaster = isClairvoyanceCaster;
		}

		/// @brief モデルを石化風描画に設定する。
		/// @param stoneRenderFlag 石化風描画する:true しない:false
		void SetStoneRenderFlag(bool stoneRenderFlag)
		{
			m_stoneRenderFlag = stoneRenderFlag;
		}

		/// @brief モデルの座標を取得
		/// @return 座標
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

		/// @brief モデルの回転を取得
		/// @return 回転
		Quaternion GetRotation()
		{
			return m_qRot;
		}

		/// @brief モデルの拡大率を取得
		/// @return 拡大率
		Vector3 GetScale()
		{
			return m_scale;
		}

		/// @brief モデルを取得
		/// @param model ビューポート番号(カメラ番号)
		/// @return 番号から取得したモデルへの参照
		Model& GetModel(EModelEX model = eModelEX_Clairvoyance)
		{
			return m_model[model];
		}

		/// @brief ボーンの名前からそのボーンのワールド行列を取得する。
		/// @param boneName ボーンの名前
		/// @return ボーンのワールド行列
		Matrix GetWorldMatrixFromBoneName(const wchar_t* boneName);

		/// @brief ボーンの名前からそのボーンのワールド座標を取得する。
		/// @param boneName ボーンの名前
		/// @return ボーンの位置
		Vector3 GetWorldPosFromBoneName(const wchar_t* boneName);

		static void PreLoadModel(const char* tkmFilePath);

	private:
		Skeleton m_skeleton;		//スケルトン
		Model m_model[eModelEX_Num];	//モデル
		Vector3 m_position;			//座標
		Quaternion m_qRot;			//回転
		Vector3 m_scale;			//拡大率
		AnimationClip* m_animationClips = nullptr;	//アニメーションクリップ
		int m_animationClipNum = 0;					//アニメーションクリップの数
		Animation m_animation;						//アニメーション
		float m_animation_speed = 1.0f;				//アニメーション速度
		float m_animationSpeed = 1.0f;				//アニメーション速度(何故二つあるんだ?)

		int m_modelNum = eModelEX_Num;	//モデルの数
		bool m_isClairvoyanceCaster = false;		//このモデルは、透視状態にするかどうか
		bool m_stoneRenderFlag = false;				//石化状態にするかどうか。
	};
}