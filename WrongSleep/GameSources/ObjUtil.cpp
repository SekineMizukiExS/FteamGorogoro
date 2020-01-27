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

			//底面で上書きしていく
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

	bool IsNearVecCheck(const Vec3& v1, const Vec3& v2){
		if (abs(v1.x - v2.x) < 0.01f && abs(v1.y - v2.y) < 0.01 && abs(v1.z - v2.z) < 0.01f) {
			return true;
		}
	return false;
	}

	//------------------------------------------------------
	//セーブデータ入出力クラス
	//------------------------------------------------------
	void DataBinaryIO::WriteDataFile(const wstring& SelectNode)
	{
		//wstring MediaPath;
		//App::GetApp()->GetDataDirectory(MediaPath);
		//MediaPath = MediaPath + FilePath;
		//ofstream ifs(MediaPath,ios::binary|ios::out);
		//if (!ifs.bad())
		//{
		//	//m_Data.LastMapName = L"TTSTSTSTS";
		//	//m_Data.LastLoadBlock = L"jihs";
		//	//m_Data.CumulativeTime = m_Time;
		//	//m_XMLFileName = L"LLLPS";
		//	//m_LoadFileName = L"MEMIN";
		//	//m_Time = 2.0f;
		//	//ifs.write((const wchar_t*)&m_Data, sizeof(m_Data));
		//	DataHeader FileName;
		//	ZeroMemory(&FileName, sizeof(DataHeader));
		//	FileName.Type = DataType::FileName;
		//	auto Size = ((UINT)m_XMLFileName.size()+1 *sizeof(wchar_t));
		//	FileName.Size = Size;
		//	ifs.write((const char*)&FileName, sizeof(DataHeader));
		//	ifs.write((const char*)m_XMLFileName.c_str(), Size);

		//	DataHeader LoadName;
		//	ZeroMemory(&LoadName, sizeof(DataHeader));
		//	LoadName.Type = DataType::PointName;
		//	auto Size1 = ((UINT)m_LoadFileName.size()+1 * sizeof(wchar_t));
		//	LoadName.Size = Size1;
		//	ifs.write((const char*)&LoadName, sizeof(DataHeader));
		//	ifs.write((const char*)m_LoadFileName.c_str(), Size1);

		//	DataHeader TimeName;
		//	ZeroMemory(&TimeName, sizeof(DataHeader));
		//	TimeName.Type = DataType::Time;
		//	auto Size2 = (UINT)sizeof(float);
		//	TimeName.Size = Size2;
		//	ifs.write((const char*)&TimeName, sizeof(DataHeader));
		//	ifs.write((const char*)&m_Time, Size2);
		//	//ifs.write(m_LoadFileName.c_str(),m_LoadFileName.size()+1);
		//	//ifs.write((wchar_t*)&m_Time, sizeof(m_Time));

		//	//読み込み

		//	//終了
		//	ifs.close();
		//}
		//else
		//{
		//	MessageBox(0, L"FALED:LOADFILE", 0, 0);
		//}

		//XML
		wstring MediaPath;
		App::GetApp()->GetDataDirectory(MediaPath);
		const wstring SaveDataFile = MediaPath + L"SaveDatas/SaveFile.xml";
		auto XMLWriter = new XmlDoc(SaveDataFile);

		IXMLDOMNodePtr Node;
		Node = XMLWriter->GetSelectSingleNode(SelectNode.c_str());
		XMLWriter->SetAttribute(Node, L"MapDataFile", m_XMLFileName.c_str());

		XMLWriter->SetAttribute(Node, L"LoadBlockData", m_LoadFileName.c_str());
		auto TimeStr = Util::FloatToWStr(m_Time, 3, Util::Fixed);
		XMLWriter->SetAttribute(Node, L"AllTime", TimeStr.c_str());
		XMLWriter->Save(SaveDataFile);
	}

	SaveData DataBinaryIO::ReadDataFile(const wstring& SelectNode)
	{
		wstring MediaPath;
		App::GetApp()->GetDataDirectory(MediaPath);
		const wstring SaveDataFile = MediaPath + L"SaveDatas/SaveFile.xml";

		auto XMLRead = new XmlDocReader(SaveDataFile);
		auto Node = XMLRead->GetSelectSingleNode(SelectNode.c_str());

		m_XMLFileName = XmlDocReader::GetAttribute(Node, L"MapDataFile");
		m_LoadFileName = XmlDocReader::GetAttribute(Node, L"LoadBlockData");
		auto TimeStr = XmlDocReader::GetAttribute(Node, L"AllTime");

		m_Time = (float)_wtof(TimeStr.c_str());

		SaveData result(m_XMLFileName, m_LoadFileName, m_Time);
		return result;
	}
}