// pxCore CopyRight 2007-2015 John Robinson
// main.cpp

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "pxCore.h"
#include "pxEventLoop.h"
#include "pxWindow.h"
#include "pxViewWindow.h"

#include "rtLog.h"
#include "rtRefT.h"
#include "rtPathUtils.h"
#include "pxScene2d.h"

#include "testScene.h"

#include "pxFileDownloader.h"

extern pxScene2dRef scene;

pxEventLoop eventLoop;

class testWindow: public pxViewWindow
{
private:
   void onCloseRequest()
   {
      // When someone clicks the close box no policy is predefined.
      // so we need to explicitly tell the event loop to exit
      eventLoop.exit();
   }
};

int pxMain()
{
#if 1
   int width = 1280;
   int height = 720;
#else
   int width  = 800;
   int height = 400;
#endif

   testWindow win;
   win.init(10, 10, width, height);

   win.setTitle("pxCore!");
   win.setVisibility(true);
   win.setView(testScene());
   win.setAnimationFPS(60);

#if 0
   testWindow win2;

   win2.init(110, 110, width, height);

   win2.setTitle("pxCore! 2");
   win2.setVisibility(true);
   win2.setView(testScene());
   win2.setAnimationFPS(60);
#endif


   eventLoop.run();

   return 0;
}

void onDraw(pxSurfaceNative s)
{
   (void) s;

   scene->onDraw();
}
