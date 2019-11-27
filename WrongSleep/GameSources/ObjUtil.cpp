#include "stdafx.h"
#include "Project.h"
#include "ObjUtil.h"
namespace basecross {

	Vec3HalfSizes GetFourEdge(shared_ptr <Transform> trans,shared_ptr<BcPNTStaticDraw> draw) {
		auto ptrDraw = draw;
		auto ptrTrans = trans;
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		Vec3HalfSizes V3HS;
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
			if (maxx >= V3HS._xHalfSize) {
				V3HS._xHalfSize = maxx;
			}
			if (maxy >= V3HS._xHalfSize) {
				V3HS._yHalfSize = maxy;
			}
			if (maxz >= V3HS._zHalfSize) {
				V3HS._zHalfSize = maxz;
			}

			//’ê–Ê‚Åã‘‚«‚µ‚Ä‚¢‚­
			if (minx <= V3HS._xHalfSizeMin) {
				V3HS._xHalfSizeMin = minx;
			}
			if (miny <= V3HS._yHalfSizeMin) {
				V3HS._yHalfSizeMin = miny;
			}
			if (minz <= V3HS._zHalfSizeMin) {
				V3HS._zHalfSizeMin = minz;
			}

		}
		return V3HS;
	}

	bool IsNearVecCheck(const Vec3& v1, const Vec3& v2){
		if (abs(v1.x - v2.x) < 0.01f && abs(v1.y - v2.y) < 0.01 && abs(v1.z - v2.z) < 0.01f) {
			return true;
		}
	return false;
}

}