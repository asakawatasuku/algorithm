/// <summary>
/// エネミークラス
/// </summary>

#include "Enemy.h"
#include "BreadCrumb.h"
#include "Pursuit.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_scale = Vector3(1.0f);
	m_pos = Vector3(5.0f, 0.0f, 0.0f);

	m_moving_pattern = std::make_unique<BreadCrumb>();
	m_waypoint = std::make_unique<WaypointNavigation>();
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
void Enemy::Initialize(const std::wstring& file_name)
{
	Base::Initialize(file_name);

	//m_moving_pattern->Initialize(this, m_target);

	m_waypoint->Initialize(this);
	// ウェイポイントを設定する
	m_waypoint->AddWaypoint(Vector3(-4, 0, -5));
	m_waypoint->AddWaypoint(Vector3(-2, 0, -3));
	m_waypoint->AddWaypoint(Vector3( 1, 0, -2));
	m_waypoint->AddWaypoint(Vector3( 4, 0, -4));
	m_waypoint->AddWaypoint(Vector3( 4, 0,  3));
	m_waypoint->AddWaypoint(Vector3( 1, 0,  1));
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
	//m_waypoint->CreateGraph();
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	//m_moving_pattern->DropBreadCrumb();
<<<<<<< HEAD
	m_moving_pattern->Update();
=======
	//m_moving_pattern->Update();

	m_waypoint->Update();
	
	Base::Update();
}


>>>>>>> f73c651ff33588c05d3f5ee515fb0c76e9469f80

/// <summary>
/// 描画処理
/// </summary>
void Enemy::Render()
{
	Base::Render();

	m_waypoint->Render();
}



/// <summary>
/// 解放処理
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
	m_waypoint->Finalize();
}
