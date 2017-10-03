/// <summary>
/// �E�F�C�|�C���g�i�r�Q�[�V�����N���X
/// </summary>

#include "WaypointNavigation.h"
#include "Graphics.h"
#include <ctime>
#include <memory>

using namespace std;
using namespace DirectX::SimpleMath;


/// <summary>
/// ����������
/// </summary>
/// <param name="object">�E�F�C�|�C���g����������I�u�W�F�N�g</param>
void WaypointNavigation::Initialize(Base* object)
{
	m_object = object;
	m_object->SetSpeed(Vector3::Forward * 0.1f);

	m_target_index = -1;

	// �G�b�W�̏�����
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

	for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
	{
		for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
		{
			if (i == j)
			{
				// �g��Ȃ�
				m_node_table[i][j] = -1;
				m_node_num[i] = 1;
			}
			else
			{
				// �����l�ݒ�
				m_node_table[i][j] = INF_COST;
			}
		}
	}
}



/// <summary>
/// �ʒu�X�V
/// </summary>
/// <param name="target_pos">�V�����ڕW���W</param>
void WaypointNavigation::Update(DirectX::SimpleMath::Vector3 target_pos)
{
	if (m_target_index < 0)
	{
		// �ŏ��̃E�F�C�|�C���g���������ĂȂ��̂ŁA���߂̃E�F�C�|�C���g��T��
		m_target_index = SearchNearestPoint(m_object->GetPos());
		m_target_waypoint = GetWaypointPos(m_target_index);
	}
	else
	{
		// �ڕW�̃E�F�C�|�C���g�͌������Ă���

		const float RANGE_MAX = 15.0f;
		if (LMath::IsCollisionCircle(m_target_waypoint, m_object->GetPos(), RANGE_MAX))
		{
			// ���łɓ������Ă���̂ŁA���̃E�F�C�|�C���g��T��
			const int object_point = SearchNearestPoint(target_pos);
			m_target_index = GetNextNode(m_target_index, object_point);
			m_target_waypoint = GetWaypointPos(m_target_index);
		}
	}

	if (m_target_waypoint.y >= 0.0f)
	{
		// �ڕW�n�_���L���Ȃ�A�����Ɍ�����

		Vector3 dir_vec = LMath::Normalize(m_object->GetPos(), m_target_waypoint);

		Vector3 dir = m_object->GetRot();
		dir.y = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));
		m_object->SetRot(dir);

		Vector3 pos = m_object->GetPos();
		Vector3 speed = m_object->GetSpeed();
		Matrix rot = Matrix::CreateRotationY(m_object->GetRot().y);
		speed =	Vector3::TransformNormal(speed, rot);
		//Vector3 speed = Vector3::TransformNormal(m_object->GetSpeed(), m_object->GetWorld());
		//pos.x += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * cosf(dir.y);
		//pos.z += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * -sinf(dir.y);
		//pos.x += Vector3::Distance(Vector3::Zero, speed) * cosf(dir.y);
		//pos.z += Vector3::Distance(Vector3::Zero, speed) * -sinf(dir.y);
		//pos.x += speed.y * cosf(dir.y);
		//pos.z += speed.y * -sinf(dir.y);
		pos += speed;
		m_object->SetPos(pos);
	}
}



void WaypointNavigation::Finalize()
{
}



/// <summary>
/// �E�F�C�|�C���g��ǉ�����
/// </summary>
/// <param name="waypoint">�E�F�C�|�C���g�̈ʒu</param>
void WaypointNavigation::AddWaypoint(const Vector3 waypoint)
{
	// �ő�l�𒴂��Ă��Ȃ���Βǉ�
	if (m_waypoints.size() < WAY_POINT_MAX_NUM)
	{
		m_waypoints.push_back(waypoint);
	}
}



/// <summary>
/// �G�b�W��ǉ����ăR�X�g��ݒ肷��
/// </summary>
/// <param name="start_point">�n�_</param>
/// <param name="end_point">�I�_</param>
/// <param name="cost">�R�X�g</param>
void WaypointNavigation::InsertEdge(int start_point, int end_point, int cost)
{
	// �G�b�W��ݒ�
	// �ʂ��ꏊ�̓_���m���q���B
	m_edge_cost[start_point][end_point] = m_edge_cost[end_point][start_point] = cost;

	m_node_table[start_point][end_point] = end_point;
	m_node_table[end_point][start_point] = start_point;
	m_node_num[start_point]++;
}



/// <summary>
/// �O���t����
/// </summary>
void WaypointNavigation::CreateGraph()
{
	// �E�F�C�|�C���g����
	//{
	//	vector<Vector3> waypoint_array = m_waypoints;
	//	const int waypoint_num = m_waypoints.size();
	//	const int POINT_NUM = 4;
	//	for (int i = 0; i < waypoint_num; i++)
	//	{
	//		Vector3 pos;
	//		pos.x = 50.0f + (100.0f * (float)(i % POINT_NUM));
	//		pos.z = 50.0f + (100.0f * (float)(i / POINT_NUM));
	//		waypoint_array[i] = pos;
	//	}
	//}

	//// �G�b�W��ݒ�
	//{
	//	// ���ƂŃG�b�W��ݒ�
	//	// �ʂ��ꏊ�̓_���m���q���B
	//	m_edge_cost[0][1] = m_edge_cost[1][0] = 1;
	//	m_edge_cost[1][2] = m_edge_cost[2][1] = 1;
	//	m_edge_cost[2][3] = m_edge_cost[3][2] = 2;

	//	m_edge_cost[0][4] = m_edge_cost[4][0] = 1;
	//	m_edge_cost[1][5] = m_edge_cost[5][1] = 2;
	//	m_edge_cost[2][6] = m_edge_cost[6][2] = 1;
	//	m_edge_cost[3][7] = m_edge_cost[7][3] = 1;

	//	m_edge_cost[4][5] = m_edge_cost[5][4] = 1;
	//	m_edge_cost[5][6] = m_edge_cost[6][5] = 2;
	//	m_edge_cost[6][7] = m_edge_cost[7][6] = 1;

	//	m_edge_cost[4][8] = m_edge_cost[8][4] = 1;
	//	m_edge_cost[5][9] = m_edge_cost[9][5] = 2;
	//	m_edge_cost[6][10] = m_edge_cost[10][6] = 1;
	//	m_edge_cost[7][11] = m_edge_cost[11][7] = 1;

	//	m_edge_cost[8][9] = m_edge_cost[9][8] = 2;
	//	m_edge_cost[9][10] = m_edge_cost[10][9] = 1;
	//	m_edge_cost[10][11] = m_edge_cost[11][10] = 3;

	//	m_edge_cost[8][12] = m_edge_cost[12][8] = 1;
	//	m_edge_cost[9][13] = m_edge_cost[13][9] = 1;
	//	m_edge_cost[10][14] = m_edge_cost[14][10] = 3;
	//	m_edge_cost[11][15] = m_edge_cost[15][11] = 1;

	//	m_edge_cost[12][13] = m_edge_cost[13][12] = 1;
	//	m_edge_cost[13][14] = m_edge_cost[14][13] = 1;
	//	m_edge_cost[14][15] = m_edge_cost[15][14] = 1;
	//}

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
/// �e�[�u��������������
/// </summary>
void WaypointNavigation::RegisterTable()
{
	const int waypoint_num = m_waypoints.size();
	for (int i = 0; i < waypoint_num; i++)
	{
		// �e�[�u�����ɓ����Ă���ԍ�
		int num = 0;
		// ���ɐݒ�ς݂̃m�[�h�̐�
		int node_num = 0;
		for (int j = 0; j < waypoint_num; j++)
		{
			//if (m_node_table[i][j] > -1 && m_node_table[i][j] < waypoint_num)
			//{
			//	num = m_node_table[i][j];
			//	node_num++;
			//}
			// �m�[�h�ԍ���������Ȃ��ꍇ�A�m�[�h�ԍ��𑼂̏ꏊ�ɑ��
			if (m_node_num[i] == 1)
			{
				if (m_node_table[i][j] > -1 && m_node_table[i][j] < waypoint_num)
				{
					num = m_node_table[i][j];
					node_num++;
				}
			}
			else
			{
				break;
			}
		}
		if (node_num == 1)
		{
			for (int j = 0; j < waypoint_num; j++)
			{
				if (m_node_table[i][j] > waypoint_num)
				{
					m_node_table[i][j] = num;
					m_node_num[i]++;
				}
			}

			if (m_node_num[num] == 2)
			{
				int other_num = 0;
				// ���̔ԍ���T��
				for (int j = 0; j < waypoint_num; j++)
				{
					if (m_node_table[num][j] > -1 && m_node_table[num][j] < waypoint_num && m_node_table[num][j] != i)
					{
						other_num = m_node_table[num][j];
						break;
					}
				}
				// ���̔ԍ���������Ă��Ȃ��ꏊ�ɑ��
				for (int j = 0; j < waypoint_num; j++)
				{
					if (m_node_table[num][j] > waypoint_num)
					{
						m_node_table[num][j] = other_num;
						m_node_num[num]++;
					}
				}
			}
		}
	}

	for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
	{
		if (m_node_num[i] == WAY_POINT_MAX_NUM)
			continue;

		for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
		{
			// �܂��ݒ肳��Ă��Ȃ����
			if (m_node_table[i][j] > waypoint_num)
			{
				// �Y�������t�ɂ�����̒l����
				int num = m_node_table[j][i];
				int tmp = j;
				while (num == m_node_table[tmp][i])
				{
					for (int k = 0; k < WAY_POINT_MAX_NUM; k++)
					{
						if (m_node_table[i][k] == num)
						{
							m_node_table[i][j] = num;
							num = -1;
							break;
						}
					}
					if (num == m_node_table[tmp][i])
					{
						tmp = m_node_table[tmp][i];
						num = m_node_table[tmp][i];
					}
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
/// <returns>-1�ȊO:���̃E�F�C�|�C���g�@-1:������Ȃ�����</returns>
int WaypointNavigation::GetNextNode(const int start, const int end)
{
	for (int i = 0; i < m_waypoints.size(); i++)
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
/// �w��ʒu�����ԋ߂��E�F�C�|�C���g��T��
/// </summary>
/// <param name="pos">���W</param>
/// <returns>��ԋ߂��E�F�C�|�C���g�̔ԍ�</returns>
int WaypointNavigation::SearchNearestPoint(const Vector3& pos)
{
	vector<Vector3> waypoint_array = m_waypoints;
	const int waypoint_num = m_waypoints.size();
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
/// <param name="index">�E�F�C�|�C���g�̔ԍ�</param>
/// <returns>�E�F�C�|�C���g�̈ʒu</returns>
Vector3 WaypointNavigation::GetWaypointPos(const int& index)
{
	Vector3 tmp(-1.0f);

	vector<Vector3> waypoint_array = m_waypoints;
	const int waypoint_num = m_waypoints.size();
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
