#pragma once
#include "CBody.h"

/*
상체 종류:

1. 서있기
2. 오른쪽으로 걷기
3. 총쏘기
4. 위로 쏘기
5. 좌로 쏘기
6. 아래로 쏘기
7. 총선택후 방향 대로 쏘기
8. 칼질
*/



class CUpper :
    public CBody
{

private:
    CBody* m_pBodyOwner; //현재 body 소유자


public:

};

