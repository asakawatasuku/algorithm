/// <summary>
/// ウェイポイントナビゲーションクラス
/// </summary>

#pragma once

#include "Base.h"
#include "MathGroup.h"
#include <memory>
#include <Model.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>

class WaypointNavigation
{
private:
	Base* m_object;

	static const int WAY_POINT_MAX_NUM = 20;
	static const int INF_COST = 1 << 28;

	int m_edge_cost[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	int m_shortest_path[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	int m_target_index;
	DirectX::SimpleMath::Vector3 m_target_waypoint;
	std::vector<DirectX::SimpleMath::Vector3> m_waypoints;

	int m_node_table[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	// ノードがいくつ入っているか格納する
	int m_node_num[WAY_POINT_MAX_NUM];
public:
	void Initialize(Base* object);
	void Update(DirectX::SimpleMath::Vector3 target_pos);
	void Finalize();

	void AddWaypoint(const DirectX::SimpleMath::Vector3 waypoint);
	void InsertEdge(int start_point, int end_point, int cost = 1);
	void CreateGraph();

	void RegisterTable();
private:
	int GetNextNode(const int start, const int end);
	int SearchNearestPoint(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetWaypointPos(const int& index);
};