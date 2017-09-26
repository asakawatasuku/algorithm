#include "MovingPattern.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>

class WaypointNavigation :public MovingPattern
{
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

	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();
private:
	void Move();
	void Wait();
};