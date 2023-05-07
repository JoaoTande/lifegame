#ifndef CALLBACK_CPP
#define CALLBACK_CPP

#include <iostream>

class myButtonCallback{
public:
    myButtonCallback(){}
    virtual ~myButtonCallback(){}
	virtual void FuncCallBack(bool) = 0;
	virtual void resetAll(bool){};
	virtual void restoreScreenBackup(bool){};
	virtual void loadFunPatterns(bool){};
	virtual void saveFile(bool){};
	virtual void loadFile(bool){};
	virtual void NextSpeed(bool){};
	virtual void PrevSpeed(bool){};
	virtual void changeSize(bool){};

};

#endif
