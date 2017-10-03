#pragma once
#include <iostream>
#include <d3d11_1.h>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include "Base.h"
#include "Node.h"

class A_Star
{
private:
	Base* m_object;
	Base* m_target;

	int m_start_pos_x;						// スタート座標x
	int m_start_pos_z;						// スタート座標z
	int m_goal_pos_x;						// ゴール座標x
	int m_goal_pos_z;						// ゴール座標z
	int **m_cost;							// コスト
	int **m_heuristic;						// 推測
	std::vector<std::shared_ptr<Node>> L1;	// リスト1
	std::vector<std::shared_ptr<Node>> L2;	// リスト2

public:
	A_Star(std::pair<int, int> start, std::pair<int, int> goal, int **cost_, int **heuristic_);
	// 初期化関数
	void Initialize(Base* object, Base* target);
	// 更新処理
	void Update();
	// 終了処理
	void Finalize();
	// 比較関数
	bool Compare(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);
	// ゴール
	bool is_goal_node(std::shared_ptr<Node> node);
	bool is_included_in(std::vector<std::shared_ptr<Node>> list, std::shared_ptr<Node> node);
	// ノードの取得
	std::shared_ptr<Node> get_node(std::shared_ptr<Node> source_node, int target_x, int target_z);
	std::vector<std::shared_ptr<Node>> expand(std::shared_ptr<Node> node);
	// 探索処理
	void search();
	// 後戻り処理
	void back_track();
};
