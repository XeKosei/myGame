#include "stdafx.h"
#include "Model.h"
#include "Material.h"

void Model::Init(ModelInitData& initData)
{
	MY_ASSERT(
		initData.m_fxFilePath, 
		"error : initData.m_fxFilePath���w�肳��Ă��܂���B"
	);
	MY_ASSERT(
		initData.m_tkmFilePath,
		"error : initData.m_tkmFilePath���w�肳��Ă��܂���B"
	);
	//�����̃V�F�[�_�[�����[�h���鏈�������߂Ă���̂�
	//wchar_t�^�̕�����Ȃ̂ŁA�����ŕϊ����Ă����B
	wchar_t wfxFilePath[256] = {L""};
	if (initData.m_fxFilePath != nullptr) {
		//MessageBoxA(nullptr, "fx�t�@�C���p�X���w�肳��Ă��܂���B", "�G���[", MB_OK);
		//std::abort();
		mbstowcs(wfxFilePath, initData.m_fxFilePath, 256);
	}
	
	if (initData.m_skeleton != nullptr) {
		//�X�P���g�����w�肳��Ă���B
		m_meshParts.BindSkeleton(*initData.m_skeleton);
	}
	
	m_modelUpAxis = initData.m_modelUpAxis;

	m_tkmFile.Load(initData.m_tkmFilePath);
	m_meshParts.InitFromTkmFile(
		m_tkmFile, 
		wfxFilePath, 
		initData.m_vsEntryPointFunc,
		initData.m_vsSkinEntryPointFunc,
		initData.m_psEntryPointFunc,
		initData.m_expandConstantBuffer,
		initData.m_expandConstantBufferSize,
		initData.m_expandShaderResoruceView,
		initData.m_colorBufferFormat
	);

	UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
	
}

void Model::UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
{
	Matrix mBias;
	if (m_modelUpAxis == enModelUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(Math::PI * -0.5f);
	}
	Matrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world = mBias * mScale * mRot * mTrans;
}

void Model::UpdateWorldMatrix(Matrix world)
{
	m_world = world;
}

void Model::ChangeAlbedoMap(const char* materialName, Texture& albedoMap)
{
	m_meshParts.QueryMeshs([&](const SMesh& mesh) {
		//todo �}�e���A������tkm�t�@�C���ɏo�͂����Ȃ������E�E�E�B
		//todo ���͑S�}�e���A�������ւ��܂�
		for (Material* material : mesh.m_materials) {
			material->GetAlbedoMap().InitFromD3DResource(albedoMap.Get());
		}
	});
	//�f�B�X�N���v�^�q�[�v�̍č쐬�B
	m_meshParts.CreateDescriptorHeaps();
	
}
void Model::Draw(RenderContext& rc, Camera* camera)
{
	m_meshParts.Draw(
		rc, 
		m_world, 
		camera->GetViewMatrix(), 
		camera->GetProjectionMatrix()
	);
}

bool Model::isLineHitModel(const Vector3& start, const Vector3& end, Vector3& minCrossPoint)
{
	const auto& meshParts = m_tkmFile.GetMeshParts();

	bool isHit = false;
	float distance = FLT_MAX;

	for (const auto& mesh : meshParts)
	{
		//�܂���16�r�b�g�ł���B
		for (const auto& indexBuffer : mesh.indexBuffer16Array)
		{
			//�C���f�b�N�X�̐�����|���S���̐����v�Z����B
			int numPolygon = indexBuffer.indices.size() / 3;
			for (int polygonNo = 0;polygonNo < numPolygon;polygonNo++)
			{
				Vector3 vertexPosition[3];
				//�|���S�����\�����钸�_�ԍ����C���f�b�N�X�o�b�t�@����擾����B
				int vertexNo_0 = indexBuffer.indices[polygonNo * 3 + 0];
				int vertexNo_1 = indexBuffer.indices[polygonNo * 3 + 1];
				int vertexNo_2 = indexBuffer.indices[polygonNo * 3 + 2];

				vertexPosition[0] = mesh.vertexBuffer[vertexNo_0].pos;
				vertexPosition[1] = mesh.vertexBuffer[vertexNo_1].pos;
				vertexPosition[2] = mesh.vertexBuffer[vertexNo_2].pos;

				m_world.Apply(vertexPosition[0]);
				m_world.Apply(vertexPosition[1]);
				m_world.Apply(vertexPosition[2]);


				//����������Ƃ̐ڐG����
				//1.�|���S�����܂ޖ������ʂƂ̌�������

				//3�̒��_����m_vertex[0]����L�т�@�������߂�
				Vector3 v1 = vertexPosition[1] - vertexPosition[0];
				Vector3 v2 = vertexPosition[2] - vertexPosition[0];

				Vector3 normal;
				normal.Cross(v1, v2);
				normal.Normalize();

				//�@���ƁAm_vertex[0]���画�肷������̊J�n�n�_�ƏI���n�_�œ��ς��Ƃ�B
				Vector3 toStart = start - vertexPosition[0];
				toStart.Normalize();

				Vector3 toEnd = end - vertexPosition[0];
				toEnd.Normalize();

				//���ς̌��ʂ�0�ȏ�Ȃ�������Ă��Ȃ��̂Ŏ��̃��[�v�ցB
				if (normal.Dot(toStart) * normal.Dot(toEnd) > 0)
				{
					continue;
				}

				//2.�������Ă�����W�����߂�
				toStart = start - vertexPosition[0];

				toEnd = end - vertexPosition[0];

				Vector3 test = start - end;

				float a = normal.Dot(toStart);

				normal *= -1;

				float b = normal.Dot(toEnd);

				Vector3 crossPoint = toStart - toEnd;
				crossPoint *= b / (a + b);
				crossPoint += end;

				//3.��_���O�p�`�̒��ɂ��邩�ǂ����̔���

				Vector3 vA = vertexPosition[1] - vertexPosition[0];
				Vector3 vB = vertexPosition[2] - vertexPosition[1];
				Vector3 vC = vertexPosition[0] - vertexPosition[2];
				Vector3 vD = crossPoint - vertexPosition[0];
				Vector3 vE = crossPoint - vertexPosition[1];
				Vector3 vF = crossPoint - vertexPosition[2];

				vA.Cross(vD);
				vA.Normalize();
				vB.Cross(vE);
				vB.Normalize();
				vC.Cross(vF);
				vC.Normalize();

				if (vA.Dot(vB) > 0 && vA.Dot(vC) > 0)
				{
					//1��ł��ڐG���Ă���B
					isHit = true;

					//�ڐG���Ă���̂ŁA�X�^�[�g�Ƃ̋��������߂�
					Vector3 dist = crossPoint - start;

					//���݂̍Œ����������Z���Ȃ�X�V�B
					if (dist.Length() < distance)
					{
						minCrossPoint = crossPoint;
						distance = dist.Length();
					}
				}
				else
				{
					//��_���O�p�`�̒��ɂȂ��B
					continue;
				}
			}
		}
	}
	return isHit;
}
