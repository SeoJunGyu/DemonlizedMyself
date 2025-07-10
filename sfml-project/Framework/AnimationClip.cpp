#include "stdafx.h"
#include "AnimationClip.h"
#include "rapidcsv.h"

//상대경로로 호출된다.
bool AnimationClip::loadFromFile(const std::string& filePath)
{
	//rapidcsv.h 로 깃허브에서 사용할 수 있는 기능이다.
	//rapidcsv -> resourceMgr Load 에서 사용한다.
	rapidcsv::Document doc(filePath); //기본값 ; 최상단(밑의 내용 헤더)를 제외한 그 밑의 인덱스부터 0, 0으로 판단한다.

	//열 인덱스, 행 인덱스
	id = doc.GetCell<std::string>(0, 0);
	fps = doc.GetCell<int>(1, 0);	
	loopType = (AnimationLoopTypes)doc.GetCell<int>(2, 0);

	frames.clear();

	//열이 3부터 시작하는 이유 : 경로부터 값이 있는 셀만 순회하기 위해서이다.
	for (int i = 3; i < doc.GetRowCount(); ++i)
	{
		auto row = doc.GetRow<std::string>(i);
		frames.push_back(
			{ 
				row[0], 
				{ //좌부터 높이까지의 값은 '문자열'로 저장되있고, 그것을 int 형으로 바꾸는 것이다.
				std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]) }
			});
	}

	return true;
}
