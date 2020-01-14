/*!
@brief UI関連
*/
#include"stdafx.h"
#include "Project.h"

namespace basecross
{

	//-------------------------------------------------------------------------
	///スプライト
	//-------------------------------------------------------------------------
	Sprite::Sprite(
		const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		bool trace,
		const Vec2& startScale,
		const Vec3& startPos,
		const Vec2& SizeVec
	) :
		GameObject(stagePtr),
		m_textureKey(textureKey),
		m_trace(trace),
		m_startScale(startScale),
		m_startPos(startPos),
		m_SizeVec(SizeVec)
	{
		float Sizex = m_SizeVec.x / 2.0f;
		float Sizey = m_SizeVec.y / 2.0f;

		vertices.push_back(VertexPositionColorTexture(Vec3(-Sizex, Sizey, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(Sizex, Sizey, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(-Sizex, -Sizey, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)));
		vertices.push_back(VertexPositionColorTexture(Vec3(Sizex, -Sizey, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)));
	}

	void Sprite::OnCreate()
	{
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//頂点配列（縦横５個ずつ表示）
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, m_startPos.z);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
	}
	//-------------------------------------------------------------------------
	//タイトルUI
	//-------------------------------------------------------------------------
	TitleUI::TitleUI(const shared_ptr<Stage>&Stage, const wstring& textureKey, bool trace, const Vec2& startScale, const Vec3& startPos,
		const Vec2& halfSize)
		:Sprite(Stage, textureKey, trace, startScale, startPos, halfSize)
	{

	}

	void TitleUI::OnCreate()
	{
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//頂点配列（縦横５個ずつ表示）
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, m_startPos.z);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<SPDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
		ptrDraw->SetBlendMapTextureResource(L"clearmat_TX");
	}

	void TitleUI::OnUpdate()
	{

	}

	//-------------------------------------------------------------------------
	//アニメーションスプライト
	//-------------------------------------------------------------------------
	AnimationSprite::AnimationSprite(const shared_ptr<Stage>&Stage, const wstring& textureKey,bool trace,const Vec2& startScale,const Vec3& startPos,
		const Vec2& halfSize,
		const float AnimationSpeed,const AnimationType AnimType)
		:Sprite(Stage,textureKey,trace,startScale,startPos,halfSize),_AnimationSpeed(AnimationSpeed), _AType(AnimType),_TotalTime(0.0f)
	{

	}

	void AnimationSprite::OnCreate()
	{
		Sprite::OnCreate();
	}

	void AnimationSprite::OnUpdate()
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		_TotalTime += ElapsedTime * 5.0f;
		if (_TotalTime >= XM_2PI) {
			_TotalTime = 0;
		}
		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0, 1.0, 1.0, 1.0);
		col.w = sin(_TotalTime) * 0.5f + 0.5f;
		PtrDraw->SetDiffuse(col);

	}
	//-------------------------------------------------------------------------
	///可変長スプライト
	//-------------------------------------------------------------------------
	VariableSprite::VariableSprite(
		const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		bool trace,
		const Vec3& startPos,
		const float halfSizeX,
		const float halfSizeY,
		const bool porigonMode
	) :
		GameObject(stagePtr),
		m_textureKey(textureKey),
		m_trace(trace),
		m_startScale(Vec2(1, 1)),
		m_startPos(startPos),
		m_halfSizeX(halfSizeX),
		m_halfSizeY(halfSizeY),
		m_fillAmount(1),
		m_porigonMode(porigonMode)
	{}


	//
	void VariableSprite::OnCreate()
	{

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);

		if (m_porigonMode)
		{


			//インデックスを作成するための配列
			vector<uint16_t> indices;
			vector<VertexPositionNormalTexture> vertices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);
			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_textureKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
			DrawComp->CreateOriginalMesh(new_vertices, indices);
			DrawComp->SetOriginalMeshUse(true);
		}
		else {

			//頂点とインデックスを指定してスプライト作成
			auto ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
			ptrDraw->SetSamplerState(SamplerState::LinearWrap);
			ptrDraw->SetTextureResource(m_textureKey);
		}
	}
	void VariableSprite::OnUpdate()
	{
		fillUpdate();
	}

	void VariableSprite::fillUpdate() {

		if (m_porigonMode)
		{
			//fillの値で長さを調節します
			float fillRightLonger = m_halfSizeX + ((m_halfSizeX * 2 * m_fillAmount) - (m_halfSizeX * 2));
			vector<VertexPositionColorTexture> tempVertices = {
				{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),m_color, Vec2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(fillRightLonger, m_halfSizeY, 0), m_color, Vec2(m_fillAmount, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vec3(fillRightLonger, -m_halfSizeY, 0),m_color, Vec2(m_fillAmount, 1.0f)) },
			};
			auto ptrDraw = GetComponent<PCTStaticDraw>();

			auto PtrTransform = GetComponent<Transform>();
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

			ptrDraw->UpdateVertices(tempVertices);
		}
		else {
			float fillRightLonger = m_halfSizeX + ((m_halfSizeX * 2 * m_fillAmount) - (m_halfSizeX * 2));
			vector<VertexPositionColorTexture> tempVertices = {
				{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),m_color, Vec2(0.0f, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(fillRightLonger, m_halfSizeY, 0), m_color, Vec2(m_fillAmount, 0.0f)) },
				{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), m_color, Vec2(0.0f, 1.0f)) },
				{ VertexPositionColorTexture(Vec3(fillRightLonger, -m_halfSizeY, 0), m_color, Vec2(m_fillAmount, 1.0f)) },
			};
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->UpdateVertices(tempVertices);
		}

	}

	void VariableSprite::Setfill(float n) {
		m_fillAmount = n;
	}

	float VariableSprite::Getfill() {
		return m_fillAmount;
	}

	void VariableSprite::SetColor(float r, float g, float b, float a) {
		m_color = Col4(r, g, b, a);
	}

	SelectSprite::SelectSprite(
		const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		bool trace,
		const Vec2& startScale,
		const Vec3& startPos,
		const float halfSize,
		const int num
	) :
		GameObject(stagePtr),
		m_trace(trace),
		m_startScale(startScale),
		m_startPos(startPos),
		m_textureKey(textureKey),
		m_halfSize(halfSize),
		m_num(num),
		m_TotalTime(0),
		m_Select(Select::Off)
	{}

	void SelectSprite::OnCreate() {
		vertices = {
			{VertexPositionColorTexture(Vec3(-m_halfSize, m_halfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f))},
			{VertexPositionColorTexture(Vec3(m_halfSize, m_halfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 0.0f))},
			{VertexPositionColorTexture(Vec3(-m_halfSize, -m_halfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f))},
			{VertexPositionColorTexture(Vec3(m_halfSize, -m_halfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f))},
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, m_startPos.z);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
	}
	void SelectSprite::OnUpdate()
	{
		switch (m_Select)
		{
		case Select::On:
			Blink();
			break;

		case Select::Off:
			Wait();
			break;

		case Select::Decision:
			Flash();
			break;
		}

	}

	void SelectSprite::Blink() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 2.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0f, 1.0f, 1.0f, 1.0f);
		col.w = sin(m_TotalTime) * 0.5f + 0.5f;
		ptrDraw->SetDiffuse(col);
	}

	void SelectSprite::Wait() {
		auto PtrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0f, 1.0f, 1.0f, 1.0f);
		PtrDraw->SetDiffuse(col);
	}

	void SelectSprite::Flash() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime * 50.0f;
		if (m_TotalTime >= XM_2PI) {
			m_TotalTime = 0;
		}
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		Col4 col(1.0f, 1.0f, 1.0f, 1.0f);
		col.w = sin(m_TotalTime) * 0.5f + 0.5f;
		ptrDraw->SetDiffuse(col);
	}

	//-------------------------------------------------------------------------
	///数字スプライト
	//-------------------------------------------------------------------------
	NumberSprite::NumberSprite(
		const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		bool trace,
		const Vec3& startPos,
		const float halfSizeX,
		const float halfSizeY,
		const int m_drawNumber
	) :
		GameObject(stagePtr),
		m_textureKey(textureKey),
		m_trace(trace),
		m_startScale(Vec2(1.0f)),
		m_startPos(startPos),
		m_halfSizeX(halfSizeX),
		m_halfSizeY(halfSizeY)
	{}

	void NumberSprite::OnCreate()
	{

		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_trace);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_startScale.x, m_startScale.y, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_startPos.x, m_startPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_textureKey);
	}
	void NumberSprite::OnUpdate()
	{
		float UVx_left = 0 + (float)m_drawNumber / 10.0f;
		float UVx_right = 0.1f + (float)m_drawNumber / 10.0f;
		vector<VertexPositionColorTexture> tempVertices = {
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, m_halfSizeY, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(UVx_left, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(UVx_right, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-m_halfSizeX, -m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(UVx_left, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(m_halfSizeX, -m_halfSizeY, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(UVx_right, 1.0f)) },
		};
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(tempVertices);
	}

}
