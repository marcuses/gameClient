#include "AppDelegate.h"
#include "MainScene.h"
#include "LogInScene.h"
#include "NewLogIn.h"
#include "Splash.h"
#include "Standing.h"
#include <vector>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLViewImpl::create("Loli");
		director->setOpenGLView(glview);
	}
	glview->setFrameSize(960, 640);
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
	
	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	//auto scene = HelloWorld::createScene();
	srand(time(0)); //seed of rand
	std::vector<std::string> searchPath; 
	searchPath.push_back("StartScene"); 
	searchPath.push_back("Role"); 
	searchPath.push_back("GameOver");
	searchPath.push_back("WinScene");
	searchPath.push_back("NextScene");
	searchPath.push_back("image");
	searchPath.push_back("UI");
	searchPath.push_back("Map");
	searchPath.push_back("Bullet");
	searchPath.push_back("monsterAnimation\\Export\\NewAnimation");
	searchPath.push_back("sEffect");
	CCFileUtils::getInstance()->setSearchPaths(searchPath); 
	SimpleAudioEngine::getInstance()->preloadEffect("explode.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
	//auto scene = LogInScene::createScene();
	//auto scene = Standing::createScene();
	//auto scene = NewLogIn::createScene();
	auto scene = MainScene::createScene();
	//auto scene = Splash::createScene(); 

	// run
	director->runWithScene(scene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
