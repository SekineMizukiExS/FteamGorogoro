/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "ObjUtil.h"
#include <experimental/generator>



namespace basecross{



	//--------------------------------------------------------------------------------------
//	class Player : public GameObject;
//	用途: プレイヤー
//--------------------------------------------------------------------------------------
//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr), m_cntlNum(0)
	{}

	void Player::OnCreate() {

		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetFont(L"x8y12pxTheStrongGamer",24);
		ptrString->SetTextRect(Rect2D<float>(320.0f, 50.0f, 640.0f, 640.0f));


		auto ptr = AddComponent<Transform>();

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();

		//各パフォーマンスを得る
		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);

		//重力をつける
		auto ptrGra = AddComponent<basecross::Gravity>();
		
		//GetStage()->SetCollisionPerformanceActive(true);
		//GetStage()->SetUpdatePerformanceActive(true);
		//GetStage()->SetDrawPerformanceActive(true);

		ptr->SetScale(2.0f, 2.0f, 2.0f);	//直径225センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(8.5f, 7.5f, 0));
		//ptr->SetPivot(Vec3(0, 0, 0));
		ptr->SetQuaternion(Quat());

		
		
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		//ptrDraw->SetMeshResource(L"Player2_MD");
		//ptrDraw->SetMeshResource(L"Apple_MD");
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetFogEnabled(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"clearmat_TX");
		//SetAlphaActive(true);
		//ptrDraw->SetTextureResource(L"RedApple_TX");
		SetAlphaActive(true);
		ptrDraw->SetEmissive(Flt4(0.25f,0.25f,1,1));
		
		GetInFourEdge(true);
		Vec3 buttomPos = ptr->GetPosition();
		buttomPos.y = m_V3HS._yHalfSizeMin;
		m_Buttom = buttomPos;
		m_nowSize = ptr->GetScale();

		//m_EfkPlay = GetTypeStage<GameStage>()->();


	}

	void Player::DebugLine()
	{
		Vec3 ExtAng = GetExtendingAngle();
		wstring ButtomVecX(L"ButtomVecX:\t");
		ButtomVecX += Util::FloatToWStr(ExtAng.x, 5);
		ButtomVecX += L"\n";

		wstring ButtomVecY(L"ButtomVecY:\t");
		ButtomVecY += Util::FloatToWStr(ExtAng.y, 5);
		ButtomVecY += L"\n";

		wstring ButtomVecZ(L"ButtomVecZ:\t");
		ButtomVecZ += Util::FloatToWStr(ExtAng.z, 5);
		ButtomVecZ += L"\n";


		auto ptrTrans = GetComponent<Transform>();
		auto worldmat = ptrTrans->GetWorldMatrix();
		float x;
		float y;
		float z;
		wstring Vertices(L"ButtomVertices:\t");
		int CC = 0;
		for each (auto verPos in m_ButtomVertexs)
		{
			CC++;
			Vec3 temp = verPos.position * worldmat;
			x = temp.getX();
			y = temp.getY();
			z = temp.getZ();

			Vertices += (L"x:");
		Vertices += Util::FloatToWStr(x, 1, Util::FloatModify::Fixed);
		Vertices += (L"y:");
		Vertices += Util::FloatToWStr(y, 1, Util::FloatModify::Fixed);
		Vertices += (L"z:");
		Vertices += Util::FloatToWStr(z, 1, Util::FloatModify::Fixed);
			if (CC % 2 == 1) {
				Vertices += L"\n";
			}
		}
		wstring VerticesC(L"ButtomVerticesCount:\t");
		VerticesC += Util::FloatToWStr(m_ButtomVertexs.size(), 5);
		VerticesC += L"\n";

		wstring counts(L"counts:\t");
		for each(int n in angleCount) {
			
			counts += Util::FloatToWStr(n, 5);
			counts += L",\n";
		}
		wstring HalfX(L"HalfX:\t");
		HalfX += Util::FloatToWStr(m_V3HS._xHalfSizeMin, 1, Util::FloatModify::Fixed) + L"***";
		HalfX += Util::FloatToWStr(m_V3HS._xHalfSize, 1, Util::FloatModify::Fixed);
		HalfX += L"\n";

		wstring HalfY(L"HalfY:\t");
		HalfY += Util::FloatToWStr(m_V3HS._yHalfSizeMin, 1, Util::FloatModify::Fixed) + L"***";
		HalfY += Util::FloatToWStr(m_V3HS._yHalfSize, 1, Util::FloatModify::Fixed);
		HalfY += L"\n";

		wstring HalfZ(L"HalfZ:\t");
		HalfZ += Util::FloatToWStr(m_V3HS._zHalfSizeMin, 1, Util::FloatModify::Fixed) + L"***";
		HalfZ += Util::FloatToWStr(m_V3HS._zHalfSize, 1, Util::FloatModify::Fixed);
		HalfZ += L"\n";

		wstring vCount(L"vCount:\t");
		vCount += Util::FloatToWStr(m_vCount, 5);
		vCount += L"\n";

		wstring Grounded(L"Grounded:\t");
		if (m_isGround) {
			Grounded += L"true";
			Grounded += L"\n";
		}
		wstring str = ButtomVecX + ButtomVecY + ButtomVecZ
			+ Vertices + VerticesC + counts + HalfX + HalfY + HalfZ + vCount + Grounded;

		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void Player::OnUpdate() {
		if (GetTypeStage<StageBase>()->GetCameraSelects() == SelectCamera::pEventCamera||GetTypeStage<StageBase>()->GetCameraSelects() == SelectCamera::pOpeningCamera)
			return;

		auto ptrGra = GetComponent<basecross::Gravity>();
		ptrGra->SetGravity(Vec3(0,-2.0f,0));
		ptrGra->SetGravityVerocity(Vec3(0, -2.0f, 0));

		//GetMoveVector();
		//MovePlayer();
		RotateMove();
		GetInFourEdge();
		BoxExtending();
		Gravity();
		DebugLine();
		//auto inPut = GetInputState();
		auto InputDevice = App::GetApp()->GetInputDevice();
		auto KeyState = InputDevice.GetKeyState();
		auto cntlVec = InputDevice.GetControlerVec()[0];
		WORD wButtons = cntlVec.wPressedButtons;
		if (KeyState.m_bPressedKeyTbl['F']|| wButtons ==XINPUT_GAMEPAD_Y) {
			if (m_usingSize > m_nowSize.y) {
				m_nowSize.y += 1.0f;
			}
		}
		if (KeyState.m_bPressedKeyTbl['X']|| wButtons == XINPUT_GAMEPAD_X) {
			m_nowSize.y -= 1.0f;
		}

		if (m_nowSize.y <= -5.0f) {
			m_nowSize.y = 1.0f;
		}

		auto transPtr = GetComponent<Transform>();
		auto nowPos = transPtr->GetPosition();

		//nowPos.x = round(nowPos.x);
		//nowPos.y = round(nowPos.y);
		//nowPos.z = round(nowPos.z);
		//transPtr->SetPosition(nowPos);

		if (nowPos.y < -0.5f) {
			//transPtr->SetPosition(nowPos.x, 0.5f, nowPos.z);
			transPtr->SetPosition(m_beforePos.x,5.0f, m_beforePos.z);
			if (GetTypeStage<MainGameStage>(false)) {}
				//PostEvent(0.0f, nullptr, App::GetApp()->GetScene<Scene>(), L"ToMainGameStage");
		}
		//wstring tempQtx(L"tempQ: ");
		//tempQtx += Util::FloatToWStr(tempQ.getW()) + L"\n";
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(tempQtx);

	}
	//================接触処理=========================
		//何かにヒットした時
	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {

		//ヒットしている物がコモンボックスなら *関数にできる
		auto obj = dynamic_pointer_cast<CommonBox>(other);
		if (obj) {
			//ヒット対象がAppleなら
			if (obj->FindTag(L"Apple")) {
				auto ptrTransform = GetComponent<Transform>();
				//bsm::Flt3 beforeWorldPosition = ptrTransform->GetBeforeWorldMatrix().transInMatrix();
				Vec3 HitPoint;
				m_usingSize += 1;
				//EfkPlay(L"Splash_EF", obj->GetComponent<Transform>()->GetPosition(), 0);
				auto stg = GetStage();
				auto teststg = dynamic_pointer_cast<StageBase>(stg);
				if (teststg) {
					teststg->Effectplay(L"Splash_EF", obj->GetComponent<Transform>()->GetPosition());
				}
				obj->SetUpdateActive(false);
				obj->SetDrawActive(false);
			}
			//ヒット対象がカギなら
			if (obj->FindTag(L"Key"))
			{
				//鍵取得時のエフェクト再生
				auto stg = GetStage();
				auto teststg = dynamic_pointer_cast<StageBase>(stg);
				if (teststg) {
					teststg->Effectplay(L"Splash_EF", obj->GetComponent<Transform>()->GetPosition());
				}
				//取得情報をマネージャーに送信
				GameManager::GetManager()->AddKeyNums(1);
				//オブジェクトを破棄
				obj->SetUpdateActive(false);
				obj->SetDrawActive(false);
			}
		}

		auto obj2 = dynamic_pointer_cast<EnemyBase>(other);
		if (obj2) {
			auto ptrTransform = GetComponent<Transform>();
			//bsm::Flt3 beforeWorldPosition = ptrTransform->GetBeforeWorldMatrix().transInMatrix();
			Vec3 HitPoint;
			//EfkPlay(L"Splash_EF", obj2->GetComponent<Transform>()->GetPosition(), 0);
			auto stg = GetStage();
			auto teststg = dynamic_pointer_cast<StageBase>(stg);
			if (teststg) {
				teststg->Effectplay(L"Splash_EF", obj2->GetComponent<Transform>()->GetPosition());
			}
			m_usingSize += 1;
			obj2->OnDestroy();

		}

		auto TransComp = GetComponent<Transform>();

		auto obj3 = dynamic_pointer_cast<MovingObject>(other);
		if (obj3)
		{
			auto otherforce = obj3->GetMoveForce();
			auto Pos = TransComp->GetPosition();
			TransComp->SetPosition(Pos + otherforce);
			return;
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& other)
	{
		auto TransComp = GetComponent<Transform>();

		auto obj = dynamic_pointer_cast<MovingObject>(other);
		if (obj)
		{
			auto otherforce = obj->GetMoveForce();
			auto Pos = TransComp->GetPosition();
			TransComp->SetPosition(Pos+otherforce);
			return;
		}
	}

	Vec3 Player::GetRotateVector() {
		Vec3 rotVec(-m_rotateAxis.z, m_rotateAxis.y, m_rotateAxis.x);
		return rotVec;
	}

	//=============四辺取得関数=====================
	void Player::GetInFourEdge() {
		auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		auto ptrTrans = GetComponent<Transform>();
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		
		m_V3HS._xHalfSize = -99999;
		m_V3HS._yHalfSize = -99999;
		m_V3HS._zHalfSize = -99999;
		m_V3HS._xHalfSizeMin = 99999;
		m_V3HS._yHalfSizeMin = 99999;
		m_V3HS._zHalfSizeMin = 99999;
		auto worldmat = ptrTrans->GetWorldMatrix();
		
		for each (auto verPos in verteces)
		{
			Vec3 tempver = verPos.position * worldmat;
			float maxx = tempver.x;
			float maxy = tempver.y;
			float maxz = tempver.z;
			float minx = tempver.x;
			float miny = tempver.y;
			float minz = tempver.z;
			if (maxx >= m_V3HS._xHalfSize) {
				m_V3HS._xHalfSize = maxx;
			}
			if (maxy >= m_V3HS._yHalfSize) {
				m_V3HS._yHalfSize = maxy;
			}
			if (maxz >= m_V3HS._zHalfSize) {
				m_V3HS._zHalfSize = maxz;
			}

			//底面で上書きしていく
			if (minx <= m_V3HS._xHalfSizeMin) {
				m_V3HS._xHalfSizeMin = minx;
			}
			if (miny <= m_V3HS._yHalfSizeMin) {
				m_V3HS._yHalfSizeMin = miny;
			}
			if (minz <= m_V3HS._zHalfSizeMin) {
				m_V3HS._zHalfSizeMin = minz;
			}	
		}
	}

	void Player::GetInFourEdge(bool bcheck) {
		auto ptrDraw = GetComponent<BcPNTStaticDraw>();
		auto ptrTrans = GetComponent<Transform>();
		auto mesh = ptrDraw->GetMeshResource();
		vector<VertexPosition> verteces = mesh->GetVerteces();
		m_vCount = mesh->GetNumVertices();

		m_V3HS._xHalfSize = -99999;
		m_V3HS._yHalfSize = -99999;
		m_V3HS._zHalfSize = -99999;
		m_V3HS._xHalfSizeMin = 99999;
		m_V3HS._yHalfSizeMin = 99999;
		m_V3HS._zHalfSizeMin = 99999;
		auto worldmat = ptrTrans->GetWorldMatrix();

		for each (auto verPos in verteces)
		{
			Vec3 tempver = verPos.position * worldmat;
			float maxx = tempver.x;
			float maxy = tempver.y;
			float maxz = tempver.z;
			float minx = tempver.x;
			float miny = tempver.y;
			float minz = tempver.z;

			//float maxx = verPos.position.getX();
			//float maxy = verPos.position.getY();
			//float maxz = verPos.position.getZ();

			//float minx = verPos.position.getX();
			//float miny = verPos.position.getY();
			//float minz = verPos.position.getZ();
			if (maxx >= m_V3HS._xHalfSize) {
				m_V3HS._xHalfSize = maxx;
			}
			if (maxy >= m_V3HS._yHalfSize) {
				m_V3HS._yHalfSize = maxy;
			}
			if (maxz >= m_V3HS._zHalfSize) {
				m_V3HS._zHalfSize = maxz;
			}

			//底面で上書きしていく
			if (minx <= m_V3HS._xHalfSizeMin) {
				m_V3HS._xHalfSizeMin = minx;
			}
			if (miny <= m_V3HS._yHalfSizeMin) {
				m_V3HS._yHalfSizeMin = miny;

			}
			if (minz <= m_V3HS._zHalfSizeMin) {
				m_V3HS._zHalfSizeMin = minz;
			}
		}
		if (bcheck) {
			m_ButtomVertexs.clear();
			for each (auto verPos in verteces)
			{
				bool flg = false;
				//verPos.position *= worldmat;
				Vec3 tempVer = verPos.position * worldmat;
				float miny = tempVer.getY();
				for each(auto ver2 in m_ButtomVertexs) {
					if (IsNearVecCheck(verPos.position, ver2.position)) {
						flg = true;
						break;
					}
				}
				if (!flg) {
					if (miny <= m_V3HS._yHalfSizeMin) {
						m_ButtomVertexs.push_back(verPos);
					}
				}
			}
		}
	}
	//=================箱が伸びる方向を取得=========
	Vec3 Player::GetExtendingAngle() {
		auto ptrTrans = GetComponent<Transform>();
		auto worldmat = ptrTrans->GetWorldMatrix();
		for (int i = 0; i < 7; i++) {
			angleCount[i] = 0;//0:前,1:奥,2:左,3;右,4;上,5;下,6:算出方向
		}
		for each (auto verPos in m_ButtomVertexs)
		{
			Vec3 tempver = verPos.position * worldmat;
			float maxx = m_V3HS._xHalfSize - tempver.x;
			float maxy = m_V3HS._yHalfSize - tempver.y;
			float maxz = m_V3HS._zHalfSize - tempver.z;
			float minx = tempver.x - m_V3HS._xHalfSizeMin;
			float miny = tempver.y - m_V3HS._yHalfSizeMin;
			float minz = tempver.z - m_V3HS._zHalfSizeMin;
			if (maxx < 0.1f) {
				angleCount[3] ++;
			}
			if (maxy < 0.1f) {
				angleCount[4] ++;
			}
			if (maxz < 0.1f) {
				angleCount[0] ++;
			}
			//底面で上書きしていく
			if (minx < 0.1f) {
				angleCount[2] ++;
			}
			if (miny < 0.1f) {
				angleCount[5] ++;

			}
			if (minz < 0.1f) {
				angleCount[1] ++;
			}
		}
		int tempnum = 0;
		for (int i = 0; i < 6; i++) {
			if (tempnum <= angleCount[i]) {
				tempnum = angleCount[i];
				angleCount[6] = i;
			}
		}
		Vec3 tempPos;
		switch (angleCount[6])
		{
			//0:前,1:奥,2:左,3;右,4;上,5;下,6:算出方向
		case 0:
			tempPos = Vec3(0, 0, 1);
			break;
		case 1:
			tempPos = Vec3(0,0 ,-1);
			break;
		case 2:
			tempPos = Vec3(1, 0, 0);
			break;
		case 3:
			tempPos = Vec3(-1,0, 0);
			break;
		case 4:
			tempPos = Vec3(0, -1, 0);
			break;
		case 5:
			tempPos = Vec3(0, 1, 0);
			break;
		default:
			break;
		}


		return tempPos;
	}

	//=================箱の伸縮処理==============
	void Player::BoxExtending() {
		auto ptr = AddComponent<Transform>();
		Vec3 tempVec = ptr->GetScale();
		Vec3 extAngle = GetExtendingAngle();//伸びる方向の取得
		Vec3 nowPos = ptr->GetPosition();
		//Vec3 nextPos = nowPos + (extAngle * 0.1f);
		//目標サイズと比較してまだ小さいならスケールを大きくする
		if (m_nowSize.y > tempVec.y) {
			if (m_nowSize.y - tempVec.y >= 0.1f) {
				ptr->SetScale(tempVec.x, tempVec.y + 0.1f, tempVec.z);
				ptr->SetPosition(nowPos + (extAngle * 0.1f));
			}
			else {
				ptr->SetScale(tempVec.x, m_nowSize.y, tempVec.z);
			}
		}else if (m_nowSize.y < tempVec.y) {//目標サイズより小さい場合はスケールを減らす。
			if (tempVec.y - m_nowSize.y >= 0.1f) {
				ptr->SetScale(tempVec.x, tempVec.y - 0.1f, tempVec.z);
				ptr->SetPosition(nowPos + (extAngle * -0.1f));
			}
			else {
				ptr->SetScale(tempVec.x, m_nowSize.y, tempVec.z);
			}
		}
		GetInFourEdge();
	}

	//回転移動処理
	void Player::RotateMove() {

		auto transptr = GetComponent<Transform>();
		auto drawptr = GetComponent<BcPNTStaticDraw>();

		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		Vec3 nowPos = transptr->GetPosition();
		float maxrot = 0.5f * XM_PI;
		GetInFourEdge();
		if (0.0f >= m_V3HS._yHalfSizeMin) {
			auto temppos = transptr->GetPosition();
			//transptr->SetPosition(temppos.x, m_V3HS._yHalfSizeMin + 0.3f,temppos.z);
		}

		//==========================Unity移植文========================
			//Debug.Log("hol:" + Input.GetAxis("Horizontal"));
			//回転中は入力を受け付けない
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (m_isRotate == true) {
			if (m_count < 5 * (1/m_speed)) {
				transptr->RotateAround(m_rotatePoint, m_rotateAxis, 0.1f * XM_PI * m_speed, nowPos);
				m_count += 1;
			}
			else {

				m_count = 0;
				m_isRotate = false;

				auto stg = GetStage();
				auto teststg = dynamic_pointer_cast<StageBase>(stg);
				if (teststg) {
					teststg->Effectplay(L"SideSplash_EF",Vec3(nowPos.x,0.5,nowPos.z));
					GameManager::GetManager()->MovedPlayer();
				}
			}

			//pivot = m_rotatePoint;
			//exam = m_rotateAxis;
			//transptr->RotateAround(pivot, exam, 0.25f * XM_2PI, nowPos);
			//m_isRotate = false;

		}
		else if(!m_isGround){

		}
		else if (moveX > 0)
		{
			GetInFourEdge();
			nowPos = transptr->GetWorldPosition();
			m_beforePos = transptr->GetWorldPosition();
			m_rotatePoint = Vec3(m_V3HS._xHalfSize, m_V3HS._yHalfSizeMin, nowPos.z);
			m_rotateAxis = Vec3(0, 0, 1);
			m_isRotate = true;


			//beforePos = transptr->GetPosition();
			//beforeQ = transptr->GetQuaternion();

		}
		else if (moveX < 0)
		{
			GetInFourEdge();
			nowPos = transptr->GetWorldPosition();
			m_beforePos = transptr->GetWorldPosition();
			m_rotatePoint = Vec3(m_V3HS._xHalfSizeMin, m_V3HS._yHalfSizeMin, nowPos.z);
			m_rotateAxis = Vec3(0, 0, -1);
			m_isRotate = true;
		}
		else if (moveZ > 0)
		{
			GetInFourEdge();
			nowPos = transptr->GetWorldPosition();
			m_beforePos = transptr->GetWorldPosition();
			m_rotatePoint = Vec3(nowPos.x, m_V3HS._yHalfSizeMin, m_V3HS._zHalfSize);
			m_rotateAxis = Vec3(-1, 0, 0);
			m_isRotate = true;
		}
		else if (moveZ < 0)
		{
			GetInFourEdge();
			nowPos = transptr->GetWorldPosition();
			m_beforePos = transptr->GetWorldPosition();
			m_rotatePoint = Vec3(nowPos.x, m_V3HS._yHalfSizeMin, m_V3HS._zHalfSizeMin);
			m_rotateAxis = Vec3(1, 0, 0);
			m_isRotate = true;
		}
		else {
			//nowPos = transptr->GetWorldPosition();
			//transptr->SetPosition(nowPos.x, 0.5f, nowPos.z);
			//m_isRotate = false;
		}
	}

	void Player::Gravity() {
		m_isGround;
		m_isGroundLower;//めり込み
//=======
//	void Player::Gravity2() {
//		float length = m_V3HS._yHalfSizeMin - 0.5f;
//
//>>>>>>> 94f1d0fed7e126ae35ba9595487e49bda932e98a
		auto transptr = GetComponent<Transform>();
		Vec3 nowPos = transptr->GetWorldPosition();
		Vec3 tempPos = transptr->GetWorldPosition();
		tempPos.y = m_V3HS._yHalfSizeMin;
		//Vec3 lowerPos = tempPos - Vec3(0, 0.1f, 0);

		Vec3 nowPositions[5] = {};
		nowPositions[0] = nowPos;
		nowPositions[1] = Vec3(m_V3HS._xHalfSize, nowPos.y, m_V3HS._zHalfSize);
		nowPositions[2] = Vec3(m_V3HS._xHalfSizeMin, nowPos.y, m_V3HS._zHalfSize);
		nowPositions[3] = Vec3(m_V3HS._xHalfSize, nowPos.y, m_V3HS._zHalfSizeMin);
		nowPositions[4] = Vec3(m_V3HS._xHalfSizeMin, nowPos.y, m_V3HS._zHalfSizeMin);

		Vec3 tempPositions[5] = {};
		tempPositions[0] = tempPos;
		tempPositions[1] = Vec3(m_V3HS._xHalfSize, tempPos.y, m_V3HS._zHalfSize);
		tempPositions[2] = Vec3(m_V3HS._xHalfSizeMin, tempPos.y, m_V3HS._zHalfSize);
		tempPositions[3] = Vec3(m_V3HS._xHalfSize, tempPos.y, m_V3HS._zHalfSizeMin);
		tempPositions[4] = Vec3(m_V3HS._xHalfSizeMin, tempPos.y, m_V3HS._zHalfSizeMin);

		for(int i = 0;i < 5; i++){

		m_isGround = RayCast(tempPositions[i], tempPositions[i]-Vec3(0,-0.1f,0));
		m_isGroundLower = RayCast(nowPositions[i], tempPositions[i]);
			if (m_isGround || m_isGroundLower) {
				break;
			}
		}
		float length = 0.1f;

		if (!m_isGroundLower) {
		}
		else {
			length = 0.1f;
			nowPos.y += length;
			transptr->SetWorldPosition(nowPos);
		}

	}

	bool Player::RayCast(Vec3 pos , Vec3 target) {
		auto stage = GetStage();
		auto transptr = GetComponent<Transform>();
		
		bool hit = false;

		for (auto& v : stage->GetGameObjectVec()) {

			auto PlayerPtr = dynamic_pointer_cast<Player>(v);
			if (!PlayerPtr) {
				auto PsPtr = dynamic_pointer_cast<GameObject>(v);
				if (PsPtr) {
					auto ColObb = PsPtr->GetComponent<CollisionObb>(false);
					auto ColSp = PsPtr->GetComponent<CollisionSphere>(false);
					auto ColCapsule = PsPtr->GetComponent<CollisionCapsule>(false);
					if (ColObb) {
						auto Obb = ColObb->GetObb();
						if (HitTest::SEGMENT_OBB(pos, target, Obb)) {
							hit = true;
							return hit;
						}
					}
					else if (ColSp) {
						auto Sp = ColSp->GetSphere();
						if (HitTest::SEGMENT_SPHERE(pos, target, Sp)) {
							hit = true;
							return hit;
						}
					}
					else if (ColCapsule) {
						auto Cap = ColCapsule->GetCapsule();
						if (HitTest::SEGMENT_CAPSULE(pos, target, Cap)) {
							hit = true;
							return hit;
						}
					}
				}
			}
		}
		return hit;
	}


	//=======================================================================
	//========================PlayerMarker===================================
	//=======================================================================
	PlayerMarker::PlayerMarker(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}


	shared_ptr<GameObject> PlayerMarker::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void PlayerMarker::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}


	void PlayerMarker::OnCreate() {
		auto ptr = AddComponent<Transform>();
	}

	void PlayerMarker::OnUpdate() {
		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			auto ptrTrans = GetComponent<Transform>();
			Vec3 tempPos(ptrTarget->GetComponent<Transform>()->GetPosition());
			ptrTrans->SetPosition(tempPos.x,3,tempPos.z);
		}
	}



//=======================================================================
//========================PlayerModel====================================
//=======================================================================
	PlayerModel::PlayerModel(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}


	shared_ptr<GameObject> PlayerModel::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void PlayerModel::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}


	void PlayerModel::OnCreate() {
		auto ptr = AddComponent<Transform>();
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"Player2_MD");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Player2_MD");
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"Player002_TX");
		SetAlphaActive(true);
		ptrDraw->SetEmissive(Flt4(0.25f, 0.25f, 1, 1));

	}

	void PlayerModel::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {

			Vec3 tempPos(ptrTarget->GetComponent<Transform>()->GetPosition());
			
			ptrTrans->SetPosition(tempPos.x, tempPos.y-0.85f, tempPos.z);
			


			auto obj = dynamic_pointer_cast<Player>(ptrTarget);
			if (obj) {
				Vec3 bottomPos = obj->GetExtendingAngle();//プレイヤーの底面を取得
				//ptrTrans->SetPosition(tempPos + bottomPos);
				
				Vec3 MAngle = obj->GetRotateVector();

				MAngle.y = 0;
				MAngle.normalize();
				//進行方向向きからの角度を算出
				float frontAngle = atan2(MAngle.z, MAngle.x);

				//トータルの角度を算出
				float totalAngle = frontAngle;
				Vec3 angle(0, 0, 0);
				//角度からベクトルを作成
				angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
				//正規化する
				angle.normalize();

				auto utilPtr = GetBehavior<UtilBehavior>();
				utilPtr->RotToHead(angle, 1.0f);
			}
		}


	}

}





//end basecross

