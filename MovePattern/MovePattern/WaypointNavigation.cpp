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
/// <param name="now_vel"></param>
/// <param name="target_pos">目標座標</param>
void WaypointNavigation::Update(Vector3& now_pos, const float now_dir, const float now_vel, const Vector3 target_pos)
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
