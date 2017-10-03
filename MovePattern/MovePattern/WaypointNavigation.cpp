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
/// �R���X�g���N�^
/// </summary>
WaypointNavigation::WaypointNavigation()
	: m_now_index(-1)
	, m_next_index(-1)
	, m_target_index(-1)
	, m_time(0.0f)
	, m_waiting_time(0)
{
}



/// <summary>
/// ����������
/// </summary>
/// <param name="object">�E�F�C�|�C���g����������I�u�W�F�N�g</param>
void WaypointNavigation::Initialize(Base* object)
{
	m_object = object;

	m_box.resize(WAY_POINT_MAX_NUM);
	for (auto itr = m_box.begin(); itr != m_box.end(); itr++)
	{
		(*itr) = make_unique<WaypointBox>();
		(*itr)->Initialize(L"waypoint_box");
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



void WaypointNavigation::Update()
{
	// �ڕW�̃E�F�C�|�C���g�����܂��ĂȂ�
	if (m_target_index < 0)
	{
		// ���݈ʒu�����ԋ߂��E�F�C�|�C���g��T��
		m_now_index = SearchNearestPoint(m_object->GetPos());
		m_now_waypoint = GetWaypointPos(m_now_index);

		if (m_object->GetPos() != m_now_waypoint)
		{
			m_time > 1.0f ? m_time = 1.0f : m_time += 0.01f;

			// �ŏ������߂��̃E�F�C�|�C���g�܂Ō�����
			Vector3 pos = Vector3::Lerp(m_object->GetPos(), m_now_waypoint, m_time);
			m_object->SetPos(pos);
		}
		else
		{
			// �����_���ȏꏊ�����ԋ߂��E�F�C�|�C���g��T��
			m_target_index = m_now_index;
			while (m_now_index == m_target_index)
			{
				Vector3 pos;
				pos.x = rand() % 10 - 5;
				pos.z = rand() % 10 - 5;
				m_target_index = SearchNearestPoint(pos);
				m_target_waypoint = GetWaypointPos(m_target_index);
			}

			// ���Ɉړ�����E�F�C�|�C���g��T��
			m_next_index = m_node_table[m_now_index][m_target_index];
			m_next_waypoint = GetWaypointPos(m_next_index);

			m_time = 0.0f;
		}
	}
	// �s���悪���܂��Ă���
	else
	{
		// �e�[�u�����g���Ĉړ�

		m_time += 0.01f;

		if (m_time >= 1.0f)
		{
			m_now_index = m_next_index;
			m_now_waypoint = m_next_waypoint;
			
			// �ړI�̃E�F�C�|�C���g�ɂ���
			if (m_now_index == m_target_index)
			{
				// �����̊ԑҋ@����
				m_waiting_time++;
				if (m_waiting_time >= 90)
				{
					m_target_index = -1;
					m_time = 0.0f;
					m_waiting_time = 0;
				}
			}
			else
			{
				m_waiting_time++;
				if (m_waiting_time >= 30)
				{
					// ���ɐi�ރE�F�C�|�C���g���X�V����
					m_next_index = m_node_table[m_now_index][m_target_index];
					m_next_waypoint = GetWaypointPos(m_next_index);

					m_time = 0.0f;
					m_waiting_time = 0;
				}
			}
		}

		// Lerp�ňړ�
		Vector3 pos = Vector3::Lerp(m_now_waypoint, m_next_waypoint, m_time);
		m_object->SetPos(pos);
	}

	for (auto itr = m_box.begin(); itr != m_box.end(); itr++)
	{
		(*itr)->Update();
	}
}



/// <summary>
/// �E�F�C�|�C���g�p�̃{�b�N�X��\������
/// </summary>
void WaypointNavigation::Render()
{
	for (int i = 0; i < m_waypoints.size(); i++)
	{
		m_box[i]->Render();
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

		// �E�F�C�|�C���g�p�̃{�b�N�X�̍��W��ݒ肷��
		m_box[m_waypoints.size() - 1]->SetPos(waypoint);
	}
}



/// <summary>
/// �������
/// </summary>
/// <param name="start_point">�n�_</param>
/// <param name="end_point">�I�_</param>
void WaypointNavigation::MakeRoad(int start_point, int end_point)
{
	m_node_table[start_point][end_point] = end_point;
	m_node_table[end_point][start_point] = start_point;
	m_node_num[start_point]++;
	m_node_num[end_point]++;
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
			// �m�[�h�ԍ���������Ȃ��ꍇ�A�m�[�h�ԍ��𑼂̏ꏊ�ɑ��
			if (m_node_num[i] == 2)
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

			if (m_node_num[num] == 3)
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
	Vector3 tmp(0.0f);

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
