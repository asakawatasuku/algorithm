#include "WaypointNavigation.h"
#include <memory>


using namespace std;
using namespace DirectX::SimpleMath;


WaypointNavigation::WaypointNavigation()
	: m_waypoint_num(0)
	, m_waypoint_last_num(0)
	, m_min_dist(0.0f)
	, m_move_delay_time(0.0f)
{
	srand(static_cast<unsigned int>time(nullptr));
}



WaypointNavigation::~WaypointNavigation()
{
}



void WaypointNavigation::Initialize(shared_ptr<Base> object, shared_ptr<Base> target)
{
	m_object = object;
	m_target = nullptr;
}



void WaypointNavigation::Update()
{
	float dist = Vector3::Distance(m_object gameObject.transform.position, waypoints[num].transform.position);

	if (dist > minDist)
	{
		Move();
	}
	// ‚»‚Ìê‚Å‘Ò‹@
	else
	{
		Wait();
	}
}



void WaypointNavigation::Move()
{
	if (!navMeshAgent.isStopped)
	{
		navMeshAgent.SetDestination(waypoints[num].transform.position);
		m_waypoint_last_num = num;
	}
}



void WaypointNavigation::Wait()
{
	m_moveDelayTime++;
	
	if (m_moveDelayTime > 3 * 60.0f)
	{
		m_moveDelayTime = 0;
		m_waypoint_num = rand() % m_waypoints.size();
	}
}
