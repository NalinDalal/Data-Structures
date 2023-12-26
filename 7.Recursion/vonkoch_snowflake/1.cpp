#include "1.h"

void CSnowflakeView::onDraw(CDC*pDC){
    CSnowflakeDoc* pDoc=GetDocument();
    ASSERT_VALID(pDoc);

    if(!pDoc)
        return;

    //ToDo:add draw code for native data here
    vonKoch(200,4,pDC).snowflake();
}
