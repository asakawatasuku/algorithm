/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#include "Enemy.h"
#include "Pursuit.h"

using namespace std;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	m_scale = Vector3(1.0f);
	m_pos = Vector3(5.0f, 0.0f, 0.0f);

	m_moving_pattern = make_unique<Pursuit>();
	m_bread_crumb = make_unique<BreadCrumb>();
	m_waypoint = make_unique<WaypointNavigation>();
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
void Enemy::Initialize(const wstring& file_name)
{
	Base::Initialize(file_name);

	m_moving_pattern->Initialize(this, m_target);

	m_bread_crumb->Initialize(this, m_target);

	m_waypoint->Initialize(this);
	// �E�F�C�|�C���g��ݒ肷��
	m_waypoint->AddWaypoint(Vector3(-4, 0, -5));
	m_waypoint->AddWaypoint(Vector3(-2, 0, -3));
	m_waypoint->AddWaypoint(Vector3( 1, 0, -2));
	m_waypoint->AddWaypoint(Vector3( 4, 0, -4));
	m_waypoint->AddWaypoint(Vector3( 4, 0,  3));
	m_waypoint->AddWaypoint(Vector3( 1, 0,  1));
	m_waypoint->AddWaypoint(Vector3(-4, 0,  4));
	// �������
	m_waypoint->MakeRoad(0, 1);
	m_waypoint->MakeRoad(1, 2);
	m_waypoint->MakeRoad(2, 3);
	m_waypoint->MakeRoad(2, 4);
	m_waypoint->MakeRoad(4, 5);
	m_waypoint->MakeRoad(5, 6);
	// ������Ƀe�[�u�����쐬
	m_waypoint->RegisterTable();
}



/// <summary>
/// �X�V����
/// </summary>
void Enemy::Update()
{
	m_moving_pattern->Update();

	//m_a_star->Update();

	//m_bread_crumb->Update();

	//m_waypoint->Update();
	
	Base::Update();
}



/// <summary>
/// �`�揈��
/// </summary>
void Enemy::Render()
{
	Base::Render();

	//m_waypoint->Render();
}



/// <summary>
/// �������
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
	m_bread_crumb->Finalize();
	m_waypoint->Finalize();
}
