#pragma once

#include <memory>

class PhysicsWorld
{
	static PhysicsWorld* m_instance;	//�B��̃C���X�^���X�B
	std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;
	std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;	//!<�Փˉ��������B
	std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//!<���[���h�B
#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
	CPhysicsDebugDraw									 m_debugDraw;
#endif

public:
	struct MyRayResultCallback : public btCollisionWorld::RayResultCallback
	{
		Vector3 hitPos;
		Vector3 rayStart;
		Vector3 rayEnd;
		bool isHit = false;
		float hitFraction = 1.0f;
		btScalar	addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{
			if (rayResult.m_hitFraction < hitFraction) {
				// ������̕����߂��B
				hitPos.Lerp(rayResult.m_hitFraction, rayStart, rayEnd);
			}
			isHit = true;
			return rayResult.m_hitFraction;
		}
	};
	struct ResultConvexSweepTest : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;
		btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) override
		{
			isHit = true;
			return 0.0f;
		}
	};

	static void CreateInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new PhysicsWorld();
		}
	}
	static PhysicsWorld* GetInstance()
	{
		return m_instance;
	}
	static void DeleteInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}
	
	void Update(float deltaTime);
	void DebubDrawWorld(RenderContext& rc);
	void Release();
	/*!
	* @brief	�d�͂�ݒ�B�B
	*/
	void SetGravity(Vector3 g)
	{
		m_dynamicWorld->setGravity(btVector3(g.x, g.y, g.z));
	}
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return m_dynamicWorld.get();
	}

	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb)
	{
		m_dynamicWorld->addRigidBody(rb.GetBody());
	}

	bool RayTest(const Vector3& rayStart, const Vector3& rayEnd, Vector3& hitPos) const
	{
		btVector3 start, end;
		start.setValue(rayStart.x, rayStart.y, rayStart.z);
		end.setValue(rayEnd.x, rayEnd.y, rayEnd.z);
		MyRayResultCallback cb;
		cb.rayStart = rayStart;
		cb.rayEnd = rayEnd;
		m_dynamicWorld->rayTest(start, end, cb);
		if (cb.isHit) {
			hitPos = cb.hitPos;
		}
		return cb.isHit;
	}
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb)
	{
		m_dynamicWorld->removeRigidBody(rb.GetBody());
	}
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	bool ConvexSweepTest(ICollider& collider, const Vector3& rayStart, const Vector3& rayEnd);

	
#if 0
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		m_dynamicWorld->addCollisionObject(&colliObj);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		m_dynamicWorld->removeCollisionObject(&colliObj);
	}
	
	void ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		CRigidBody& rb,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
		
	void ContactTest(
		CCharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
#endif		
private:
	PhysicsWorld();
	~PhysicsWorld();
	void Init();
};
	
