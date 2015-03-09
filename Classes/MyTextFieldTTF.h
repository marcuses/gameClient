#ifndef __MYTEXTFIELDTTF_H__
#define __MYTEXTFIELDTTF_H__
#include "cocos2d.h"
#include <string>
class MyTextFieldTTF : public cocos2d::TextFieldTTF {
public:
	void setType(int t);
	int getType();
	void setOn(bool isChlicked);
	MyTextFieldTTF();
	~MyTextFieldTTF();
	void setString(const std::string &text) override;
	static MyTextFieldTTF* myTextFieldWithPlaceHolder(int t,const std::string& placeholder, const std::string& fontName, float fontSize);
	virtual void setPlaceHolder(const std::string& text) override;
	virtual bool attachWithIME() override;
	virtual bool detachWithIME() override;
private:
	int _myTextFieldType;
	bool _isChlicked;
};

#endif