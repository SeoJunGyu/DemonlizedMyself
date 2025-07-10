#include "stdafx.h"
#include "AnimationClip.h"
#include "rapidcsv.h"

//����η� ȣ��ȴ�.
bool AnimationClip::loadFromFile(const std::string& filePath)
{
	//rapidcsv.h �� ����꿡�� ����� �� �ִ� ����̴�.
	//rapidcsv -> resourceMgr Load ���� ����Ѵ�.
	rapidcsv::Document doc(filePath); //�⺻�� ; �ֻ��(���� ���� ���)�� ������ �� ���� �ε������� 0, 0���� �Ǵ��Ѵ�.

	//�� �ε���, �� �ε���
	id = doc.GetCell<std::string>(0, 0);
	fps = doc.GetCell<int>(1, 0);	
	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	frames.clear();

	//���� 3���� �����ϴ� ���� : ��κ��� ���� �ִ� ���� ��ȸ�ϱ� ���ؼ��̴�.
	for (int i = 3; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		frames.push_back(
			{ 
				row[0], 
				{ //�º��� ���̱����� ���� '���ڿ�'�� ������ְ�, �װ��� int ������ �ٲٴ� ���̴�.
				std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]) }
			});
	}

	return true;
}
