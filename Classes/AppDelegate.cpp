#include "AppDelegate.h"
#include "MainScene.h"
#include "LogInScene.h"
#include "NewLogIn.h"
#include "Splash.h"
#include "StartScene.h"
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
	searchPath.push_back("StartScene");
	searchPath.push_back("NextScene");
	searchPath.push_back("image");
	searchPath.push_back("UI");
	searchPath.push_back("Map");
	searchPath.push_back("Bullet");
	searchPath.push_back("monster1Animation");
	searchPath.push_back("sEffect");
	CCFileUtils::getInstance()->setSearchPaths(searchPath); 
	SimpleAudioEngine::getInstance()->preloadEffect("explode.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("hit.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Monster1Animation/NewAnimation0.png",
		"Monster1Animation/NewAnimation0.plist","Monster1Animation/NewAnimation.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Monster1/Monster10.png",
		"Monster1/Monster10.plist","Monster1/Monster1.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Monster2/Monster20.png",
		"Monster2/Monster20.plist","Monster2/Monster2.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Monster3/Monster30.png",
		"Monster3/Monster30.plist","Monster3/Monster3.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Monster4/Monster40.png",
		"Monster4/Monster40.plist","Monster4/Monster4.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("boss2/boss20.png",
		"boss2/boss20.plist","boss2/boss2.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("boss3/boss30.png",
		"boss3/boss30.plist","boss3/boss3.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet1/bullet10.png",
		"bullet1/bullet10.plist","bullet1/bullet1.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet2/bullet20.png",
		"bullet2/bullet20.plist","bullet2/bullet2.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet3/bullet30.png",
		"bullet3/bullet30.plist","bullet3/bullet3.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet4/bullet40.png",
		"bullet4/bullet40.plist","bullet4/bullet4.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet5/bullet50.png",
		"bullet5/bullet50.plist","bullet5/bullet5.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("bullet10/bullet100.png",
		"bullet10/bullet100.plist","bullet10/bullet10.ExportJson");
	//auto scene = StartScene::createScene();
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
