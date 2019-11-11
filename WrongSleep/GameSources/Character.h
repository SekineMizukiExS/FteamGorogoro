/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class FixedObject :public GameObject
	{
	public:
		FixedObject(const shared_ptr<Stage>&stage, IXMLDOMNodePtr pNode);

		void OnCreate()override;

	private:
		wstring _MeshKey;
		Vec3 _Pos;
		Vec3 _Scal;
		Vec3 _Rot;
		wstring _TexKey;
	};

}
//end basecross
