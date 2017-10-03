#include "A_star.h"

using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="start"></param>
/// <param name="goal"></param>
/// <param name="cost_"></param>
/// <param name="heuristic_"></param>
A_Star::A_Star(pair<int, int> start, pair<int, int> goal, int **cost_, int **heuristic_) 
{
	// ���W.�R�X�g.����.���擾���Đݒ�
	m_start_pos_x = start.first; 
	m_start_pos_z = start.second;
	m_goal_pos_x = goal.first;
	m_goal_pos_z = goal.second;
	m_cost = cost_;
	m_heuristic = heuristic_;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="object"></param>
/// <param name="target"></param>
void A_Star::Initialize(Base* object, Base* target)
{
	m_object = object;
	m_target = target;
}


/// <summary>
/// ��r�֐�
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
bool A_Star::Compare(const shared_ptr<Node>& a, const shared_ptr<Node>& b)
{
	return a->cost + m_heuristic[a->x][a->z] < b->cost + m_heuristic[b->x][b->z];
}

/// <summary>
/// �S�[����
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
bool A_Star::is_goal_node(shared_ptr<Node> node)
{
	return node->x == m_goal_pos_x && node->z == m_goal_pos_z;
}

/// <summary>
/// �C���N���[�h����Ă��邩
/// </summary>
/// <param name="list"></param>
/// <param name="node"></param>
/// <returns></returns>
bool A_Star::is_included_in(vector<shared_ptr<Node>> list, shared_ptr<Node> node)
{
	for (vector<shared_ptr<Node>>::iterator it = list.begin(); it != list.end(); ++it) 
	{
		if (node->x == (*it)->x && node->z == (*it)->z)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// �m�[�h�̐�������
/// </summary>
/// <param name="source_node"></param>
/// <param name="target_x"></param>
/// <param name="target_z"></param>
/// <returns></returns>
shared_ptr<Node> A_Star::get_node(shared_ptr<Node> source_node, int target_x, int target_z)
{
	shared_ptr<Node> node = shared_ptr<Node>(new Node(target_x, target_z, source_node->cost + m_cost[target_x][target_z]));

	if (is_included_in(L1, node)) 
	{
		for (vector<shared_ptr<Node>>::iterator it = L1.begin(); it != L1.end(); ++it) 
		{
			if (target_x == (*it)->x && target_z == (*it)->z) return *it;
		}
	}
	else if (is_included_in(L2, node)) 
	{
		for (vector<shared_ptr<Node>>::iterator it = L2.begin(); it != L2.end(); ++it) 
		{
			if (target_x == (*it)->x && target_z == (*it)->z) return *it;
		}
	}
	else 
	{
		// not generated yet...
	}
	return node;
}

vector<shared_ptr<Node>> A_Star::expand(shared_ptr<Node> node)
{
	vector<shared_ptr<Node>> result;
	// �m�[�h���擾���Đݒ�
	int x = node->x; int z = node->z;
	// �ォ�玞�v���(x�̂ق����c�Az�̂ق�����)
	int x1 = -1; int z1 = 0;	// ��
	int x2 = 0;  int z2 = 1;	// �E
	int x3 = 1;  int z3 = 0;	// ��
	int x4 = 0;  int z4 = -1;	// ��

	// ��
	if (0 <= node->x + x1) 
	{ 
		result.push_back(get_node(node, x + x1, z + z1));
	}
	// �E
	if (z + z2 <= 4) 
	{ 
		result.push_back(get_node(node, x + x2, z + z2));
	}
	// ��
	if (x + x3 <= 4) 
	{
		result.push_back(get_node(node, x + x3, z + z3));
	}
	// ��
	if (0 <= z + z4)
	{ 
		result.push_back(get_node(node, x + x4, z + z4));
	}
	return result;
}

/// <summary>
/// �T������
/// </summary>
void A_Star::search()
{
	// �T���̏����_��L1�ɓ����
	L1.push_back(shared_ptr<Node>(new Node(m_start_pos_x, m_start_pos_z,m_cost[m_start_pos_x][m_start_pos_z])));
	while (true) 
	{
		// L1����̏ꍇ
		if (L1.empty()) 
		{
			cout << "Search failed..." << endl;
			break;
		}
		else 
		{
			// ���X�gL1�̐擪�̐ߓ_n�Ǝ�菜���A���X�gL2�ɓ����
			shared_ptr<Node> n = L1.front();
			L2.push_back(n);
			vector<shared_ptr<Node>>::iterator it = L1.begin();
			L1.erase(it);

			// �S�[�����Ă��邩
			if (is_goal_node(n))
			{
				break;
			}

			vector<shared_ptr<Node>> expanded_nodes = expand(n);

			cout << "Target Node x: " << n->x << ", z: " << n->z << ", cost: " << n->cost << "(" << n->cost + m_heuristic[n->x][n->z] << ")" << endl;

			for (it = expanded_nodes.begin(); it != expanded_nodes.end(); ++it) 
			{
				shared_ptr<Node> n_i = (*it);

				cout << "\tExpanded Node x: " << n_i->x << ", z: " << n_i->z << ", cost: " << n_i->cost << "(" << n_i->cost + m_heuristic[n_i->x][n_i->z] << ")" << endl;

				int f_prime = n->cost + m_cost[n_i->x][n_i->z];
				// n_i��L1�ɂ�L2�ɂ��܂܂�Ȃ�
				if (!is_included_in(L1, n_i) && !is_included_in(L2, n_i)) 
				{ 
					cout << "\tCase 1" << endl;
					n_i->cost = f_prime;
					n_i->parent = n;
					L1.push_back(n_i);
				}
				// n_i��L1�Ɋ܂܂�Ă���
				else if (is_included_in(L1, n_i)) 
				{ 
					if (f_prime < n_i->cost) 
					{
						cout << "\tCase 2(" << f_prime << ", " << n_i->cost << ")" << endl;
						n_i->cost = f_prime;
						n_i->parent = n;
					}
				}
				// n_i��L2�Ɋ܂܂�Ă���
				else if (is_included_in(L2, n_i)) 
				{
					if (f_prime < n_i->cost) 
					{
						cout << "\tCase 3(" << f_prime << ", " << n_i->cost << ")" << endl;
						n_i->cost = f_prime;
						// n_i��L2�����菜��
						int index = 0;
						for (int i = 0; i < (int)L2.size(); ++i) 
						{
							shared_ptr<Node> tmp = L2.at(i);
							if (n_i->x == tmp->x && n_i->z == tmp->z) 
							{
								index = i;
								L1.push_back(tmp);
							}
						}
						vector<shared_ptr<Node>>::iterator tmp = L2.begin();
						L2.erase(tmp + index);
					}
				}
				else 
				{
					// do nothing
				}
				sort(L1.begin(), L1.end(), bind(&A_Star::Compare, this, placeholders::_1, placeholders::_2));
			}
		}
	}
}

/// <summary>
/// ��߂菈��
/// </summary>
void A_Star::back_track()
{
	vector<shared_ptr<Node>> path;
	shared_ptr<Node> node = L2.back();
	shared_ptr<Node> parent = node->parent;

	path.push_back(node);
	// Goal����o�b�N�g���b�N
	while (parent != NULL)
	{
		node = parent;
		parent = node->parent;
		path.push_back(node);
	}

	reverse(path.begin(), path.end()); // Start����o�͂��������̂ŁA�t������
	for (vector<shared_ptr<Node>>::iterator it = path.begin(); it != path.end(); ++it)
	{
		cout << "(" << (*it)->x << ", " << (*it)->z << ") " << (*it)->cost << endl;
	}
}


////////////* main *////////////
/// <summary>
/// �X�V����
/// </summary>
void A_Star::Update()
{
	//{
	//	//���H�R�X�g
	//	int *maze_cost_array[5];
	//	int maze_cost_array0[5] = { 6, 5, 8, 9, 0 };
	//	int maze_cost_array1[5] = { 3, 1, 3, 9, 2 };
	//	int maze_cost_array2[5] = { 0, 2, 2, 2, 3 };
	//	int maze_cost_array3[5] = { 1, 3, 1, 2, 4 };
	//	int maze_cost_array4[5] = { 0, 0, 4, 2, 1 };

	//	maze_cost_array[0] = maze_cost_array0;
	//	maze_cost_array[1] = maze_cost_array1;
	//	maze_cost_array[2] = maze_cost_array2;
	//	maze_cost_array[3] = maze_cost_array3;
	//	maze_cost_array[4] = maze_cost_array4;

	//	int *manhattanma_distance[5];
	//	int manhattanma_distance0[5] = { 4, 3, 2, 1, 0 };
	//	int manhattanma_distance1[5] = { 5, 4, 3, 2, 1 };
	//	int manhattanma_distance2[5] = { 6, 5, 4, 3, 2 };
	//	int manhattanma_distance3[5] = { 7, 6, 5, 4, 3 };
	//	int manhattanma_distance4[5] = { 8, 7, 6, 5, 4 };

	//	manhattanma_distance[0] = manhattanma_distance0;
	//	manhattanma_distance[1] = manhattanma_distance1;
	//	manhattanma_distance[2] = manhattanma_distance2;
	//	manhattanma_distance[3] = manhattanma_distance3;
	//	manhattanma_distance[4] = manhattanma_distance4;

	//	A_Star a_star(pair<int, int>(4, 0), pair<int, int>(0, 4), maze_cost_array, manhattanma_distance);
	//	a_star.search();
	//	a_star.back_track();
	//}

	//{
	//	int *maze_cost_array[5];
	//	int maze_cost_array0[5] = { 0, 0, 2, 0, 0 };
	//	int maze_cost_array1[5] = { 3, 10, 3, 900, 200 };
	//	int maze_cost_array2[5] = { 10, 1, 2, 2, 3 };
	//	int maze_cost_array3[5] = { 1, 2, 1, 2, 4 };
	//	int maze_cost_array4[5] = { 0, 3, 6, 2, 1 };

	//	maze_cost_array[0] = maze_cost_array0;
	//	maze_cost_array[1] = maze_cost_array1;
	//	maze_cost_array[2] = maze_cost_array2;
	//	maze_cost_array[3] = maze_cost_array3;
	//	maze_cost_array[4] = maze_cost_array4;

	//	int *manhattanma_distance[5];
	//	int manhattanma_distance0[5] = { 4, 3, 2, 1, 0 };
	//	int manhattanma_distance1[5] = { 5, 4, 3, 2, 100 };
	//	int manhattanma_distance2[5] = { 11, 6, 50, 4, 3 };
	//	int manhattanma_distance3[5] = { 11, 6, 50, 4, 3 };
	//	int manhattanma_distance4[5] = { 8, 5, 3, 50, 4 };

	//	manhattanma_distance[0] = manhattanma_distance0;
	//	manhattanma_distance[1] = manhattanma_distance1;
	//	manhattanma_distance[2] = manhattanma_distance2;
	//	manhattanma_distance[3] = manhattanma_distance3;
	//	manhattanma_distance[4] = manhattanma_distance4;

	//	A_Star a_star(pair<int, int>(4, 0), pair<int, int>(0, 4), maze_cost_array, manhattanma_distance);
	//	a_star.search();
	//	a_star.back_track();
	//}

}

/// <summary>
/// �I������
/// </summary>
void A_Star::Finalize()
{
	delete m_cost;
	delete m_heuristic;
}
