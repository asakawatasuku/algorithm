#pragma once
#include <d3d11_1.h>
#include <memory>

class Node {
public:
	int x, z, cost; // costはこのノードにくるまでの最短パス上での累積和(f'(n))
	std::shared_ptr<Node> parent;
	Node(int x_, int z_, int cost_) 
	{
		x = x_; z = z_; cost = cost_;
	};
};