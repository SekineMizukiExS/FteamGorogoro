#pragma once
#include "stdafx.h"

namespace basecross
{
	class EnemyBase;

	//----------------------------------------
	//エネミーの管理クラス
	//----------------------------------------
	//実装予定
	//1.エネミーの生成
	//2.巡回経路の一元管理
	//3.外部ファイルの読込
	//4.
	class EnemyManager:public ObjectInterface
	{
	public:
		EnemyManager();
		

		//----------------------------------------------------------------------------------
		/*!
		@brief エネミー生成用関数
		@paramf[in] stage　生成させるターゲットステージ EnemyDataPath エネミーの情報が入ったデータパス
		@return なし
		*/
		//----------------------------------------------------------------------------------
		void GenerateEnemyObject(const shared_ptr<Stage>&TargetStage, const wstring &EnemyDataPath);

		//----------------------------------------------------------------------------------
		/*!
		@brief イベント関数
		@paramf[in] event 送られてきたイベント
		@return なし
		*/
		//----------------------------------------------------------------------------------
		void OnEvent(const shared_ptr<Event>& event)override;

	private:
		//コピー禁止
		EnemyManager(const EnemyManager&) = delete;
		EnemyManager& operator=(const EnemyManager&) = delete;
		//ムーブ禁止
		EnemyManager(const EnemyManager&&) = delete;
		EnemyManager& operator=(const EnemyManager&&) = delete;

	};

	//オブジェクトビルダーをエネミー専用にして作成
	
	//エネミ-用引数構造体
	struct EnemyXMLDataIN
	{
		wstring XMLFileName;//XMLファイルパス
		wstring ObjectsPath;//エネミー配置パス
		wstring paramPath;	//パラメータパス
		wstring rootPointPath;//巡回経路パス
	};

	struct EnemyXMLDataOUT
	{
		IXMLDOMNodePtr InitData;	//初期化データ
		IXMLDOMNodePtr Param;		//パラメータ
		IXMLDOMNodePtr Point;		//巡回地点

		EnemyXMLDataOUT(const IXMLDOMNodePtr &InitData,const IXMLDOMNodePtr& Param,const IXMLDOMNodePtr Point)
			:InitData(InitData), Param(Param), Point(Point)
		{

		}
	};
	//--------------------------------------------------------------------------------------
	//	エネミー専用クリエータークラス(親)
	//--------------------------------------------------------------------------------------
	class EnemyXMLCreatorBase {
	protected:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		explicit EnemyXMLCreatorBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLCreatorBase() {}
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオブジェクトを作成する（純粋仮想関数）
		@param[in]	StagePtr	ステージ
		@param[in]	pNode	XMLノード
		@return	ゲームオブジェクトのポインタ
		*/
		//--------------------------------------------------------------------------------------
		virtual shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode) = 0;

		virtual shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode) = 0;
	};

	//----------------------------------------
	//エネミーXMLジェネレイト
	//----------------------------------------
	template<class EXEnemy>
	class EnemyXMLCreater :public EnemyXMLCreatorBase
	{
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		explicit EnemyXMLCreater() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLCreater() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ゲームオブジェクトを作成する（仮想関数）
		@param[in]	StagePtr	ステージ
		@param[in]	pNode	XMLノード
		@return	ゲームオブジェクトのポインタ
		*/
		//--------------------------------------------------------------------------------------
		shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode)override {
			return StagePtr->AddGameObject<T>(pNode);
		}

		shared_ptr<EnemyBase> Create(const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode)override {
			return StagePtr->AddGameObject<T>(pNode);
		}

	};

	//--------------------------------------------------------------------------------------
	//エネミー専用XMLビルダー
	//--------------------------------------------------------------------------------------
	class EnemyXMLBuilder {
		map<wstring, shared_ptr<EnemyXMLCreatorBase>>& GetCreatorMap() const;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		EnemyXMLBuilder();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EnemyXMLBuilder();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	クリエーターを登録する
		@tparam	T	登録する型（ゲームオブジェクトの派生）
		@param[in]	ClsName	型の識別名（通常は型名を文字列にしたもの）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		template<typename T>
		void Register(const wstring& ClsName) {
			GetCreatorMap()[ClsName] = shared_ptr<EnemyXMLCreater<T>>(new EnemyXMLCreater<T>());
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	型の識別名を使ってゲームオブジェクトを構築する
		@param[in]	ClsName	型の識別名（通常は型名を文字列にしたもの）
		@param[in]	StagePtr	所属するステージ
		@param[in]	pNode	XMLノード
		@return	作成したゲームオブジェクト
		*/
		//--------------------------------------------------------------------------------------
		void CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, IXMLDOMNodePtr pNode);

		void CreateFromXML(const wstring& ClsName, const shared_ptr<Stage>& StagePtr, EnemyXMLDataOUT pNode);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	XMLからゲームオブジェクトを構築する
		@param[in]	StagePtr	所属するステージ
		@param[in]	XMLFileName	XMLファイル名
		@param[in]	GameObjectsPath	ゲームオブジェクト(複数)のノードへのパス
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void Build(const shared_ptr<Stage>& StagePtr, const wstring& XMLFileName, const wstring& GameObjectsPath);

		void Build(const shared_ptr<Stage>& StagePtr, const EnemyXMLDataIN input);

		//EnemyXMLDataOUT CheckToNodeList(const IXMLDOMNodeListPtr& NodeList, const int &sortNum);
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};


	//----------------------------------------
	//エネミーの基底クラス
	//----------------------------------------
	/*!
	//----------------------------------------
	@brief
	//----------------------------------------
	*/
	//エレメントデータ構造体宣言
	struct ElemBase;

	class EnemyBase :public GameObject
	{
	public:
		EnemyBase(const shared_ptr<Stage>&stage);

		//初期処理
		virtual void OnCreate()override = 0;
		//更新処理
		virtual void OnUpdate()override = 0;
		
		virtual void SetElement(const ElemBase& Elem);

	protected:
		virtual ElemBase GetElement();
		
		friend GameManager;

		struct Impl;
		unique_ptr<Impl>pImpl;
	};


	//-----------------------------------------------------
	//ステートマシンベース
	//-----------------------------------------------------
	class TravelingState :public ObjState<EnemyBase>
	{
		TravelingState() {}
	public:
		DECLARE_SINGLETON_INSTANCE(TravelingState);
		virtual void Enter(const shared_ptr<EnemyBase>&obj)override;
		virtual void Execute(const shared_ptr<EnemyBase>&Obj)override;
		virtual void Exit(const shared_ptr<EnemyBase>&Obj)override;

	};
}