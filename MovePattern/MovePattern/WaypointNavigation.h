/// <summary>
/// ウェイポイントナビゲーションクラス
/// </summary>

#pragma once

#include "Base.h"
#include "MathGroup.h"
#include "WaypointBox.h"
#include <memory>
#include <Model.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>

class WaypointNavigation
{
private:
	Base* m_object;
	std::vector<std::unique_ptr<WaypointBox>> m_box;

	static const int WAY_POINT_MAX_NUM = 20;
	static const int INF_COST = 1 << 28;

	std::vector<DirectX::SimpleMath::Vector3> m_waypoints;
	int m_node_table[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	// ノードがいくつ入っているか格納する
	int m_node_num[WAY_POINT_MAX_NUM];
	int m_now_index;
	DirectX::SimpleMath::Vector3 m_now_waypoint;
	int m_next_index;
	DirectX::SimpleMath::Vector3 m_next_waypoint;
	int m_target_index;
	DirectX::SimpleMath::Vector3 m_target_waypoint;
	// Lerp用
	float m_time;
	int m_waiting_time;
public:
	WaypointNavigation();

	void Initialize(Base* object);
	void Update();
	void Render();
	void Finalize();

	void AddWaypoint(const DirectX::SimpleMath::Vector3 waypoint);
	void MakeRoad(int start_point, int end_point);

	void RegisterTable();
private:
	int SearchNearestPoint(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetWaypointPos(const int& index);
};