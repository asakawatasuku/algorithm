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
	// �E�F�C�|�C���g����
	{
		vector<VECTOR> waypoint_array = m_waypoints_;
		const int waypoint_num = m_waypoints_.size();
		const int POINT_NUM = 4;
		for (int i = 0; i < waypoint_num; i++)
		{
			VECTOR pos;
			pos.x = 50.0f + (100.0f * (float)(i % POINT_NUM));
			pos.z = 50.0f + (100.0f * (float)(i / POINT_NUM));
			waypoint_array[i] = pos;
		}
	}

	// �G�b�W��ݒ�
	{
		// ������
		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
			{
				m_edge_cost[i][j] = INF_COST;
			}
		}

		// ���g�ւ̃R�X�g�͂Ȃ�
		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			m_edge_cost[i][i] = 0;
		}

		// ���ƂŃG�b�W��ݒ�
		m_edge_cost[0][1] = m_edge_cost[1][0] = 1;
		m_edge_cost[1][2] = m_edge_cost[2][1] = 1;
		m_edge_cost[2][3] = m_edge_cost[3][2] = 2;

		m_edge_cost[0][4] = m_edge_cost[4][0] = 1;
		m_edge_cost[1][5] = m_edge_cost[5][1] = 2;
		m_edge_cost[2][6] = m_edge_cost[6][2] = 1;
		m_edge_cost[3][7] = m_edge_cost[7][3] = 1;

		m_edge_cost[4][5] = m_edge_cost[5][4] = 1;
		m_edge_cost[5][6] = m_edge_cost[6][5] = 2;
		m_edge_cost[6][7] = m_edge_cost[7][6] = 1;

		m_edge_cost[4][8] = m_edge_cost[8][4] = 1;
		m_edge_cost[5][9] = m_edge_cost[9][5] = 2;
		m_edge_cost[6][10] = m_edge_cost[10][6] = 1;
		m_edge_cost[7][11] = m_edge_cost[11][7] = 1;

		m_edge_cost[8][9] = m_edge_cost[9][8] = 2;
		m_edge_cost[9][10] = m_edge_cost[10][9] = 1;
		m_edge_cost[10][11] = m_edge_cost[11][10] = 3;

		m_edge_cost[8][12] = m_edge_cost[12][8] = 1;
		m_edge_cost[9][13] = m_edge_cost[13][9] = 1;
		m_edge_cost[10][14] = m_edge_cost[14][10] = 3;
		m_edge_cost[11][15] = m_edge_cost[15][11] = 1;

		m_edge_cost[12][13] = m_edge_cost[13][12] = 1;
		m_edge_cost[13][14] = m_edge_cost[14][13] = 1;
		m_edge_cost[14][15] = m_edge_cost[15][14] = 1;
	}

	// �S�_�΍ŒZ���������߂�
	{
		// �G�b�W�̏�Ԃ����̂܂܃R�s�[
		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
			{
				m_shortest_path[i][j] = m_edge_cost[i][j];
			}
		}

		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
			{
				for (int k = 0; k < WAY_POINT_MAX_NUM; k++)
				{
					const int new_value = m_shortest_path[j][i] + m_shortest_path[i][k];
					m_shortest_path[j][k] = min(m_shortest_path[j][k], new_value);
				}
			}
		}
	}
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
/// <param name="now_vel">���݂̑��x</param>
/// <param name="target_pos">�ڕW���W</param>
void WaypointNavigation::Update(VECTOR& now_pos, float now_dir, const float now_vel, const VECTOR target_pos)
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
		if (LMath::IsCollisionCircle(m_target_waypoint, now_pos, RANGE_MAX))
		{
			// ���łɓ������Ă���̂ŁA���̃E�F�C�|�C���g��T��
			const int object_point = SearchNearestPoint(target_pos);
			m_target_index = GetNextNode(m_target_index, object_point);
			m_target_waypoint = GetWaypointPos(m_target_index);
		}
	}

	if (m_target_waypoint.x >= 0.0f && m_target_waypoint.y >= 0.0f && m_target_waypoint.z >= 0.0f)
	{
		// �ڕW�n�_���L���Ȃ�A�����Ɍ�����

		VECTOR dir_vec = LMath::Normalize(now_pos, m_target_waypoint);

		now_dir = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));

		now_pos.x += now_vel * cosf(now_dir);
		now_pos.z += now_vel * -sinf(now_dir);
	}

	m_object->SetPos(Vector3(now_pos.x, now_pos.y, now_pos.z));
}



/// <summary>
/// �w��ʒu�����ԋ߂��E�F�C�|�C���g��T��
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
int WaypointNavigation::SearchNearestPoint(const VECTOR& pos)
{
	vector<VECTOR> waypoint_array = m_waypoints_;
	const int waypoint_num = m_waypoints_.size();
	if (!(!waypoint_array.empty() && (waypoint_num > 0)))
	{
		return -1;
	}

	// �����Œ��߂��ǂ������f
	int next_point = -1;
	float min_distance = (float)(1 << 30);
	for (int i = 0; i < waypoint_num; i++)
	{
		const float distance = LMath::GetScalar(waypoint_array[i] - pos);
		if (distance > min_distance)
		{
			continue;
		}
		min_distance = distance;
		next_point = i;
	}

	return next_point;
}



/// <summary>
/// �E�F�C�|�C���g�̈ʒu���擾
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
VECTOR WaypointNavigation::GetWaypointPos(const int& index)
{
	VECTOR tmp;
	tmp.x = tmp.y = tmp.z = -1.0f;

	vector<VECTOR> waypoint_array = m_waypoints_;
	const int waypoint_num = m_waypoints_.size();
	if (!(!waypoint_array.empty() && (waypoint_num > 0)))
	{
		return tmp;
	}

	if (0 > index || index >= waypoint_num)
	{
		return tmp;
	}

	return waypoint_array[index];
}
