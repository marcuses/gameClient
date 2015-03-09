#include "MyTextFieldTTF.h"
USING_NS_CC;
using namespace std;
MyTextFieldTTF::MyTextFieldTTF():TextFieldTTF(){
	_isChlicked = false;
}
MyTextFieldTTF::~MyTextFieldTTF(){
	
}
void MyTextFieldTTF::setType(int t){
	_myTextFieldType = t;
}
int MyTextFieldTTF::getType(){
	return _myTextFieldType;
}
void MyTextFieldTTF::setOn(bool isChlicked){
	_isChlicked = isChlicked;
}
void MyTextFieldTTF::setPlaceHolder(const std::string& text)
{
	_placeHolder = text;
    if (0 == _inputText.length()){
        Label::setTextColor(_colorSpaceHolder);
        if(!_isChlicked)	Label::setString(_placeHolder);
		else				Label::setString("");
    }
}
MyTextFieldTTF* MyTextFieldTTF::myTextFieldWithPlaceHolder(int t,const std::string& placeholder, const std::string& fontName, float fontSize){
	 MyTextFieldTTF *ret = new (std::nothrow) MyTextFieldTTF();
	 ret->setType(t);
	 if(ret && ret->initWithPlaceHolder("", fontName, fontSize)){
        ret->autorelease();
        if (placeholder.size()>0){
            ret->setPlaceHolder(placeholder);
        }
        return ret;
    }
	CC_SAFE_DELETE(ret);
    return nullptr;
}

bool MyTextFieldTTF::attachWithIME()
{
	log("haha");
	setOn(true);
	setPlaceHolder(_placeHolder);
    bool ret = IMEDelegate::attachWithIME();
    if (ret)
    {
        // open keyboard
        auto pGlView = Director::getInstance()->getOpenGLView();
        if (pGlView)
        {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8 && CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
            pGlView->setIMEKeyboardState(true);
#else
            pGlView->setIMEKeyboardState(true, _inputText);
#endif
        }
    }
    return ret;
}

bool MyTextFieldTTF::detachWithIME()
{
	log("hehe");
	setOn(false);
	setPlaceHolder(_placeHolder);
    bool ret = IMEDelegate::detachWithIME();
    if (ret)
    {
        // close keyboard
        auto glView = Director::getInstance()->getOpenGLView();
        if (glView)
        {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8 && CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
            glView->setIMEKeyboardState(false);
#else
            glView->setIMEKeyboardState(false, "");
#endif
        }
    }
    return ret;
}

void MyTextFieldTTF::setString(const std::string &text)
{
    static char bulletString[] = {(char)0xe2, (char)0x80, (char)0xa2, (char)0x00};
    std::string displayText;
    size_t length;

    if (text.length()>0)
    {
        _inputText = text;
        displayText = _inputText;
        if (_secureTextEntry)
        {
            displayText = "";
            length = _inputText.length();
            while (length)
            {
                displayText.append(bulletString);
                --length;
            }
        }
    }
    else
    {
        _inputText = "";
    }

    // if there is no input text, display placeholder instead
    if (0 == _inputText.length())
    {
        Label::setTextColor(_colorSpaceHolder);
        Label::setString(_placeHolder);
    }
    else
    {
        Label::setTextColor(_colorText);
        if(1==getType())	Label::setString(displayText);
		else				Label::setString(string(displayText.size(),'*'));
    }
    _charCount = _inputText.size();
}
