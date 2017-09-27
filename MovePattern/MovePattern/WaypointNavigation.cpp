/// <summary>
/// �E�F�C�|�C���g�i�r�Q�[�V�����N���X
/// </summary>

#include "WaypointNavigation.h"
#include <ctime>
#include <memory>


using namespace std;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
WaypointNavigation::WaypointNavigation()
	: m_waypoint_num(0)
	, m_waypoint_last_num(0)
	, m_min_dist(0.0f)
	, m_move_delay_time(0.0f)
{
	// �����_���̏�����
	srand(static_cast<unsigned int>(time(nullptr)));
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
WaypointNavigation::~WaypointNavigation()
{
}



/// <summary>
/// ����������
/// </summary>
/// <param name="object">�E�F�C�|�C���g����������I�u�W�F�N�g</param>
/// <param name="target">��������I�u�W�F�N�g�̑ΏۃI�u�W�F�N�g</param>
void WaypointNavigation::Initialize(shared_ptr<Base> object, shared_ptr<Base> target)
{
	m_object = object;
	m_target = nullptr;
}



/// <summary>
/// �X�V����
/// </summary>
void WaypointNavigation::Update()
{
	//float dist = Vector3::Distance(m_object->GetPos(), m_waypoints[m_waypoint_num]);

	//if (dist > m_min_dist)
	//{
	//	Move();
	//}
	//// ���̏�őҋ@
	//else
	//{
	//	Wait();
	//}
}



/// <summary>
/// �ړ�����
/// </summary>
void WaypointNavigation::Move()
{
	//if (!navMeshAgent.isStopped)
	//{
	//	navMeshAgent.SetDestination(m_waypoints[m_waypoint_num]);
	//	m_waypoint_last_num = m_waypoint_num;
	//}
}



/// <summary>
/// �ҋ@����
/// </summary>
void WaypointNavigation::Wait()
{
	//m_move_delay_time++;
	//
	//if (m_move_delay_time > 3 * 60.0f)
	//{
	//	m_move_delay_time = 0;
	//	m_waypoint_num = rand() % m_waypoints.size();
	//}
}



/// <summary>
/// �O���t����
/// </summary>
void WaypointNavigation::CreateGraph()
{
}



/// <summary>
/// ���ɍs���E�F�C�|�C���g���擾
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <returns>-1�ȊO:���̃E�F�C�|�C���g�@-1:</returns>
int WaypointNavigation::GetNextNode(const int start, const int end)
{
	for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
	{
		if (i == start)
		{
			continue;
		}

		if (m_edge_cost[start][i] + m_shortest_path[i][end] == m_shortest_path[start][end])
		{
			return i;
		}
	}

	return -1;
}



/// <summary>
/// �ʒu�X�V
/// </summary>
/// <param name="now_pos">���ݍ��W</param>
/// <param name="now_dir"></param>
/// <param name="now_vel"></param>
/// <param name="target_pos">�ڕW���W</param>
void WaypointNavigation::Update(Vector3& now_pos, const float now_dir, const float now_vel, const Vector3 target_pos)
{
	if (m_target_index < 0)
	{
		// �ŏ��̃E�F�C�|�C���g���������ĂȂ��̂ŁA���߂̃E�F�C�|�C���g��T��
		m_target_index = SearchNearestPoint(now_pos);
		m_target_waypoint = GetWaypointPos(m_target_index);
	}
	else
	{
		// �ڕW�̃E�F�C�|�C���g�͌������Ă���

		const float RANGE_MAX = 15.0f;
		if()
	}
}



int WaypointNavigation::SearchNearestPoint(const Vector3& pos)
{
	return 0;
}



Vector3 WaypointNavigation::GetWaypointPos(const int& index)
{
	return DirectX::SimpleMath::Vector3();
}
