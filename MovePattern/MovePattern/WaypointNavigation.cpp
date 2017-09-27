/// <summary>
/// ウェイポイントナビゲーションクラス
/// </summary>

#include "WaypointNavigation.h"
#include <ctime>
#include <memory>


using namespace std;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
WaypointNavigation::WaypointNavigation()
	: m_waypoint_num(0)
	, m_waypoint_last_num(0)
	, m_min_dist(0.0f)
	, m_move_delay_time(0.0f)
{
	// ランダムの初期化
	srand(static_cast<unsigned int>(time(nullptr)));
}



/// <summary>
/// デストラクタ
/// </summary>
WaypointNavigation::~WaypointNavigation()
{
}



/// <summary>
/// 初期化処理
/// </summary>
/// <param name="object">ウェイポイントを実装するオブジェクト</param>
/// <param name="target">実装するオブジェクトの対象オブジェクト</param>
void WaypointNavigation::Initialize(shared_ptr<Base> object, shared_ptr<Base> target)
{
	m_object = object;
	m_target = nullptr;
}



/// <summary>
/// 更新処理
/// </summary>
void WaypointNavigation::Update()
{
	//float dist = Vector3::Distance(m_object->GetPos(), m_waypoints[m_waypoint_num]);

	//if (dist > m_min_dist)
	//{
	//	Move();
	//}
	//// その場で待機
	//else
	//{
	//	Wait();
	//}
}



/// <summary>
/// 移動する
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
/// 待機する
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
/// グラフ生成
/// </summary>
void WaypointNavigation::CreateGraph()
{
	// ウェイポイント生成
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

	// エッジを設定
	{
		// 初期化
		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			for (int j = 0; j < WAY_POINT_MAX_NUM; j++)
			{
				m_edge_cost[i][j] = INF_COST;
			}
		}

		// 自身へのコストはなし
		for (int i = 0; i < WAY_POINT_MAX_NUM; i++)
		{
			m_edge_cost[i][i] = 0;
		}

		// 手作業でエッジを設定
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

	// 全点対最短距離を求める
	{
		// エッジの状態をそのままコピー
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
/// 次に行くウェイポイントを取得
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <returns>-1以外:次のウェイポイント　-1:</returns>
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
/// 位置更新
/// </summary>
/// <param name="now_pos">現在座標</param>
/// <param name="now_dir"></param>
/// <param name="now_vel">現在の速度</param>
/// <param name="target_pos">目標座標</param>
void WaypointNavigation::Update(VECTOR& now_pos, float now_dir, const float now_vel, const VECTOR target_pos)
{
	if (m_target_index < 0)
	{
		// 最初のウェイポイントが見つかってないので、直近のウェイポイントを探す
		m_target_index = SearchNearestPoint(now_pos);
		m_target_waypoint = GetWaypointPos(m_target_index);
	}
	else
	{
		// 目標のウェイポイントは見つかっている

		const float RANGE_MAX = 15.0f;
		if (LMath::IsCollisionCircle(m_target_waypoint, now_pos, RANGE_MAX))
		{
			// すでに到着しているので、次のウェイポイントを探す
			const int object_point = SearchNearestPoint(target_pos);
			m_target_index = GetNextNode(m_target_index, object_point);
			m_target_waypoint = GetWaypointPos(m_target_index);
		}
	}

	if (m_target_waypoint.x >= 0.0f && m_target_waypoint.y >= 0.0f && m_target_waypoint.z >= 0.0f)
	{
		// 目標地点が有効なら、そこに向かう

		VECTOR dir_vec = LMath::Normalize(now_pos, m_target_waypoint);

		now_dir = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));

		now_pos.x += now_vel * cosf(now_dir);
		now_pos.z += now_vel * -sinf(now_dir);
	}

	m_object->SetPos(Vector3(now_pos.x, now_pos.y, now_pos.z));
}



/// <summary>
/// 指定位置から一番近いウェイポイントを探す
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
