/// <summary>
/// ウェイポイントナビゲーションクラス
/// </summary>

#include "WaypointNavigation.h"
#include "Graphics.h"
#include <ctime>
#include <memory>

using namespace std;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
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
/// 初期化処理
/// </summary>
/// <param name="object">ウェイポイントを実装するオブジェクト</param>
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
				// 使わない
				m_node_table[i][j] = -1;
				m_node_num[i] = 1;
			}
			else
			{
				// 初期値設定
				m_node_table[i][j] = INF_COST;
			}
		}
	}
}



void WaypointNavigation::Update()
{
	// 目標のウェイポイントが決まってない
	if (m_target_index < 0)
	{
		// 現在位置から一番近いウェイポイントを探す
		m_now_index = SearchNearestPoint(m_object->GetPos());
		m_now_waypoint = GetWaypointPos(m_now_index);

		if (m_object->GetPos() != m_now_waypoint)
		{
			m_time > 1.0f ? m_time = 1.0f : m_time += 0.01f;

			// 最初だけ近くのウェイポイントまで向かう
			Vector3 pos = Vector3::Lerp(m_object->GetPos(), m_now_waypoint, m_time);
			m_object->SetPos(pos);
		}
		else
		{
			// ランダムな場所から一番近いウェイポイントを探す
			m_target_index = m_now_index;
			while (m_now_index == m_target_index)
			{
				Vector3 pos;
				pos.x = rand() % 10 - 5;
				pos.z = rand() % 10 - 5;
				m_target_index = SearchNearestPoint(pos);
				m_target_waypoint = GetWaypointPos(m_target_index);
			}

			// 次に移動するウェイポイントを探す
			m_next_index = m_node_table[m_now_index][m_target_index];
			m_next_waypoint = GetWaypointPos(m_next_index);

			m_time = 0.0f;
		}
	}
	// 行き先が決まっている
	else
	{
		// テーブルを使って移動

		m_time += 0.01f;

		if (m_time >= 1.0f)
		{
			m_now_index = m_next_index;
			m_now_waypoint = m_next_waypoint;
			
			// 目的のウェイポイントについた
			if (m_now_index == m_target_index)
			{
				// 少しの間待機する
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
					// 次に進むウェイポイントを更新する
					m_next_index = m_node_table[m_now_index][m_target_index];
					m_next_waypoint = GetWaypointPos(m_next_index);

					m_time = 0.0f;
					m_waiting_time = 0;
				}
			}
		}

		// Lerpで移動
		Vector3 pos = Vector3::Lerp(m_now_waypoint, m_next_waypoint, m_time);
		m_object->SetPos(pos);
	}

	for (auto itr = m_box.begin(); itr != m_box.end(); itr++)
	{
		(*itr)->Update();
	}
}



/// <summary>
/// ウェイポイント用のボックスを表示する
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
/// ウェイポイントを追加する
/// </summary>
/// <param name="waypoint">ウェイポイントの位置</param>
void WaypointNavigation::AddWaypoint(const Vector3 waypoint)
{
	// 最大値を超えていなければ追加
	if (m_waypoints.size() < WAY_POINT_MAX_NUM)
	{
		m_waypoints.push_back(waypoint);

		// ウェイポイント用のボックスの座標を設定する
		m_box[m_waypoints.size() - 1]->SetPos(waypoint);
	}
}



/// <summary>
/// 道を作る
/// </summary>
/// <param name="start_point">始点</param>
/// <param name="end_point">終点</param>
void WaypointNavigation::MakeRoad(int start_point, int end_point)
{
	m_node_table[start_point][end_point] = end_point;
	m_node_table[end_point][start_point] = start_point;
	m_node_num[start_point]++;
	m_node_num[end_point]++;
}



/// <summary>
/// テーブルを完成させる
/// </summary>
void WaypointNavigation::RegisterTable()
{
	const int waypoint_num = m_waypoints.size();
	for (int i = 0; i < waypoint_num; i++)
	{
		// テーブル内に入っている番号
		int num = 0;
		// 既に設定済みのノードの数
		int node_num = 0;
		for (int j = 0; j < waypoint_num; j++)
		{
			// ノード番号が二つしかない場合、ノード番号を他の場所に代入
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
				// 他の番号を探す
				for (int j = 0; j < waypoint_num; j++)
				{
					if (m_node_table[num][j] > -1 && m_node_table[num][j] < waypoint_num && m_node_table[num][j] != i)
					{
						other_num = m_node_table[num][j];
						break;
					}
				}
				// 他の番号を代入されていない場所に代入
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
			// まだ設定されていなければ
			if (m_node_table[i][j] > waypoint_num)
			{
				// 添え字を逆にした先の値を代入
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
/// 指定位置から一番近いウェイポイントを探す
/// </summary>
/// <param name="pos">座標</param>
/// <returns>一番近いウェイポイントの番号</returns>
int WaypointNavigation::SearchNearestPoint(const Vector3& pos)
{
	vector<Vector3> waypoint_array = m_waypoints;
	const int waypoint_num = m_waypoints.size();
	if (!(!waypoint_array.empty() && (waypoint_num > 0)))
	{
		return -1;
	}

	// 距離で直近かどうか判断
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
/// ウェイポイントの位置を取得
/// </summary>
/// <param name="index">ウェイポイントの番号</param>
/// <returns>ウェイポイントの位置</returns>
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
