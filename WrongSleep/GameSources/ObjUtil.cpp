#include "stdafx.h"
#include "Project.h"
#include "ObjUtil.h"
namespace basecross {

	void Vec3HalfSizes::GetFourEdge(const shared_ptr <Transform> &trans,const shared_ptr<AreaDraw> &draw) {
		auto ptrDraw = draw;
		auto ptrTrans = trans;
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		auto worldmat = ptrTrans->GetWorldMatrix();
		for each (auto verPos in verteces)
		{
			verPos.position *= worldmat;
			float maxx = verPos.position.getX();
			float maxy = verPos.position.getY();
			float maxz = verPos.position.getZ();

			float minx = verPos.position.getX();
			float miny = verPos.position.getY();
			float minz = verPos.position.getZ();
			if (maxx >= _xHalfSize) {
				_xHalfSize = maxx;
			}
			if (maxy >= _yHalfSize) {
				_yHalfSize = maxy;
			}
			if (maxz >= _zHalfSize) {
				_zHalfSize = maxz;
			}

			//’ê–Ê‚Åã‘‚«‚µ‚Ä‚¢‚­
			if (minx <= _xHalfSizeMin) {
				_xHalfSizeMin = minx;
			}
			if (miny <= _yHalfSizeMin) {
				_yHalfSizeMin = miny;
			}
			if (minz <= _zHalfSizeMin) {
				_zHalfSizeMin = minz;
			}

		}
	}

}