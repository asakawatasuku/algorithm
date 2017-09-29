/// <summary>
/// ウェイポイントナビゲーションクラス
/// </summary>

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include "MovingPattern.h"
#include "MathGroup.h"
#include <vector>

class WaypointNavigation :public MovingPattern
{
	// Unityより移植 ////////////////////////////
private:
	// ウェイポイント
	std::vector<DirectX::SimpleMath::Vector3> m_waypoints;
	int m_waypoint_num;
	int m_waypoint_last_num;
	float m_min_dist;
	float m_move_delay_time;
public:
	WaypointNavigation();
	~WaypointNavigation();

	void Initialize(Base* object, Base* target);
	void Update();
	void Finalize();
private:
	void Move();
	void Wait();

	//////////////////////////////////////////////////

	// Webより引用 ///////////////////////////////////

private:
	static const int WAY_POINT_MAX_NUM = 20;
	static const int INF_COST = 1 << 28;
	int m_edge_cost[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	int m_shortest_path[WAY_POINT_MAX_NUM][WAY_POINT_MAX_NUM];
	int m_target_index;
	DirectX::SimpleMath::Vector3 m_target_waypoint;
	std::vector<VECTOR> m_waypoints_;
public:
	//void Initialize(Base* object, Base* target);

	void CreateGraph();
	int GetNextNode(const int start, const int end);
	void Update(DirectX::SimpleMath::Vector3& now_pos, float now_dir,
		const float now_vel, const DirectX::SimpleMath::Vector3 target_pos);
	int SearchNearestPoint(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetWaypointPos(const int& index);

//////////////////////////////////////////////////
};