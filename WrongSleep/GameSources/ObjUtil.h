#pragma once
#include "stdafx.h"
#include "Project.h"
namespace basecross {
	struct Vec3HalfSizes {
		float _xHalfSize = -99999;
		float _yHalfSize = -99999;
		float _zHalfSize = -99999;
		float _xHalfSizeMin = 99999;
		float _yHalfSizeMin = 99999;
		float _zHalfSizeMin = 99999;
	};

	Vec3HalfSizes GetFourEdge(shared_ptr <Transform> trans, shared_ptr<BcPNTStaticDraw> draw);
}