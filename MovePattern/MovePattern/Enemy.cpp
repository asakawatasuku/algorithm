/// <summary>
/// エネミークラス
/// </summary>

#include "Enemy.h"
#include "Pursuit.h"
#include "Getaway.h"
#include "Interception.h"
#include "Keyboard.h"

using namespace std;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_scale = Vector3(1.0f);
	m_pos = Vector3(3.0f, 0.0f, 0.0f);

	m_moving_pattern = make_unique<Pursuit>();
	m_bread_crumb = make_unique<BreadCrumb>();
	m_waypoint = make_unique<WaypointNavigation>();

	m_pattern_num = PATTERN_KIND::PURSUIT;
}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize(const wstring& file_name)
{
	Base::Initialize(file_name);

	m_moving_pattern->Initialize(this, m_target);

	//m_bread_crumb->Initialize(this, m_target);

	m_waypoint->Initialize(this);
	// ウェイポイントを設定する
	m_waypoint->AddWaypoint(Vector3(-4, 0, -5));
	m_waypoint->AddWaypoint(Vector3(-2, 0, -3));
	m_waypoint->AddWaypoint(Vector3( 1, 0, -2));
	m_waypoint->AddWaypoint(Vector3( 4, 0, -4));
	m_waypoint->AddWaypoint(Vector3( 4, 0,  3));
	m_waypoint->AddWaypoint(Vector3( 0, 0,  2));
	m_waypoint->AddWaypoint(Vector3(-4, 0,  4));
	// 道を作る
	m_waypoint->MakeRoad(0, 1);
	m_waypoint->MakeRoad(1, 2);
	m_waypoint->MakeRoad(2, 3);
	m_waypoint->MakeRoad(2, 4);
	m_waypoint->MakeRoad(4, 5);
	m_waypoint->MakeRoad(5, 6);
	// 道を基にテーブルを作成
	m_waypoint->RegisterTable();
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	if (m_keyboard->IsTriggered(DirectX::Keyboard::Keys::Space))
	{
		m_pos = Vector3(3.0f, 0.0f, 0.0f);
		m_speed = Vector3::Zero;

		m_pattern_num = (m_pattern_num + 1) % PATTERN_KIND::PATTERN_KIND_NUM;
		
		if (m_pattern_num == PATTERN_KIND::PURSUIT)
		{
			m_moving_pattern = make_unique<Pursuit>();
			m_moving_pattern->Initialize(this, m_target);
		}
		else if (m_pattern_num == PATTERN_KIND::GETAWAY)
		{
			m_moving_pattern = make_unique<Getaway>();
			m_moving_pattern->Initialize(this, m_target);
		}
		else if (m_pattern_num == PATTERN_KIND::INTERCEPTION)
		{
			m_moving_pattern = make_unique<Interception>();
			m_moving_pattern->Initialize(this, m_target);
		}
	}

	switch (m_pattern_num)
	{
	case PATTERN_KIND::PURSUIT:
	case PATTERN_KIND::GETAWAY:
	case PATTERN_KIND::INTERCEPTION:
		m_moving_pattern->Update();
		break;
	case PATTERN_KIND::WAYPOINT_NAVIGATION:
	case PATTERN_KIND::WAYPOINT_NAVIGATION_RENDER:
		m_waypoint->Update();
		break;
	default:
		break;
	}

	//m_a_star->Update();

	//m_bread_crumb->Update();
	
	Base::Update();
}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Render()
{
	Base::Render();

	wstring str = L"Now Moving Pattern:";
	switch (m_pattern_num)
	{
	case PATTERN_KIND::PURSUIT:
		str += L"Pursuit";
		break;
	case PATTERN_KIND::GETAWAY:
		str += L"Getaway";
		break;
	case PATTERN_KIND::INTERCEPTION:
		str += L"Interception";
		break;
	case PATTERN_KIND::WAYPOINT_NAVIGATION:
		str += L"Waypoint Navigation";
		break;
	case PATTERN_KIND::WAYPOINT_NAVIGATION_RENDER:
		str += L"Waypoint Navigation  Render Box Version";
		m_waypoint->Render();
		break;
	default:
		break;
	}

	m_font->DrawString(m_batch, str.c_str(), Vector2(0, 0));
}



/// <summary>
/// 解放処理
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
	m_bread_crumb->Finalize();
	m_waypoint->Finalize();
}
