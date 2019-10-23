/*!
@file ProjectShader.h
@brief プロジェクトで使用するシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	struct AreaCB
	{
		Mat4x4 World;
		Mat4x4 View;
		Mat4x4 Projection;
		Col4 Emissive;
		Col4 Diffuse;
		Vec4 LightDir;
		AreaCB() {
			memset(this, 0, sizeof(AreaCB));
			Diffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};

	};

}
//end basecross

