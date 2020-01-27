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

		void GetFourEdge(const shared_ptr <Transform> &trans, const shared_ptr<AreaDraw> &draw);
	};

	Vec3HalfSizes GetFourEdge(shared_ptr <Transform> trans, shared_ptr<BcPNTStaticDraw> draw);

	bool IsNearVecCheck(const Vec3& v1, const Vec3& v2);	

	//------------------------------------------------------
	//セーブデータ入出力クラス
	//------------------------------------------------------
	enum DataType
	{
		FileName,
		PointName,
		Time
	};
	struct DataHeader
	{
		DataType Type;
		UINT Size;
	};

	class DataBinaryIO
	{
	public:
		DataBinaryIO()
		{
		}

		//書き出し
		void WriteDataFile(const wstring& SelectNode);
		//読込
		SaveData ReadDataFile(const wstring& SelectNode);

		void Test(const wstring& FilePath, const wstring& LoadName)
		{
			SaveData n = {};

			n.LastMapName = m_XMLFileName;
			n.LastLoadBlock = m_LoadFileName;
			n.CumulativeTime = m_Time;


			fstream file;
			//file.open(FilePath, ios::binary | ios::out);
			file.open(FilePath, ios::binary | ios::in);

			// 書き込む
			//file.write((char*)&n, sizeof(n));

			
			// 読み込む
			//SaveData K = {};
			//auto size = sizeof(K);
			//file.read((char*)&K, size);			

			// 閉じる
			file.close();
		}

		const SaveData GetCurrntSaveData()const { return m_Data; }

		void SetSaveParam(const wstring& XMLFileName, const wstring& LoadName, const float &times)
		{
			m_XMLFileName = XMLFileName;
			m_LoadFileName = LoadName;
			m_Time = times;
		}

		SaveData m_Data;
		wstring m_XMLFileName;
		wstring m_LoadFileName;
		float m_Time;
	};
}