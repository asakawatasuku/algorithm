#pragma once
#include <d3d11_1.h>
#include <memory>

class Node {
public:
	int x, z, cost; // cost‚Í‚±‚Ìƒm[ƒh‚É‚­‚é‚Ü‚Å‚ÌÅ’ZƒpƒXã‚Å‚Ì—İÏ˜a(f'(n))
	std::shared_ptr<Node> parent;
	Node(int x_, int z_, int cost_) 
	{
		x = x_; z = z_; cost = cost_;
	};
};