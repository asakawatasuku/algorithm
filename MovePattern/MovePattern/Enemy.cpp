/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#include "Enemy.h"
#include "BreadCrumb.h"
#include "Pursuit.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	m_scale = Vector3(1.0f);
	m_pos = Vector3(5.0f, 0.0f, 0.0f);

	m_moving_pattern = std::make_unique<BreadCrumb>();
	m_waypoint = std::make_unique<WaypointNavigation>();
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize(const std::wstring& file_name)
{
	Base::Initialize(file_name);

	//m_moving_pattern->Initialize(this, m_target);

	m_waypoint->Initialize(this);
	// �E�F�C�|�C���g��ݒ肷��
	m_waypoint->AddWaypoint(Vector3(-5, 0, 3));
	m_waypoint->AddWaypoint(Vector3(-1, 0, 5));
	m_waypoint->AddWaypoint(Vector3(-4, 0, -5));
	m_waypoint->AddWaypoint(Vector3(5, 0, 3));
	m_waypoint->AddWaypoint(Vector3(1, 0, 5));
	m_waypoint->AddWaypoint(Vector3(4, 0, -5));
	m_waypoint->AddWaypoint(Vector3(4, 0, 5));
	// �G�b�W��ݒ肷��
	m_waypoint->InsertEdge(0, 1);
	m_waypoint->InsertEdge(1, 2);
	m_waypoint->InsertEdge(2, 3);
	m_waypoint->InsertEdge(2, 4);
	m_waypoint->InsertEdge(4, 5);
	m_waypoint->InsertEdge(5, 6);
	// �G�b�W����Ƀe�[�u�����쐬
	m_waypoint->RegisterTable();
	m_waypoint->CreateGraph();
}



/// <summary>
/// �X�V����
/// </summary>
void Enemy::Update()
{
	//m_moving_pattern->DropBreadCrumb();
	//m_moving_pattern->Update();

	Vector3 pos;
	pos.x = rand() % 10 - 5;
	pos.z = rand() % 10 - 5;
	m_waypoint->Update(pos);



	Base::Update();
}



/// <summary>
/// �������
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
	m_waypoint->Finalize();
}
