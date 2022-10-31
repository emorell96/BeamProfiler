#pragma once
#include "SmoothInfo.h"
#include "ResizeInfo.h"
#include <string>
#include "ImageHandler.h"
#include "FitParameters.h"
#include "BeamProfiler.h"

//#include <uwebsockets/App.h>

FitParameters Fit(std::string filepath, SmoothInfo smoothInfo, ResizeInfo resizeInfo, FitParameters fitParameters)
{
	ImageHandler imageHandler;

	imageHandler.Process(filepath, smoothInfo, resizeInfo);

	BeamProfiler profiler(imageHandler, fitParameters);

	profiler.Fit();

	return profiler.GetParameters();
}

//void ListenToFit(uWS::HttpResponse<false>* res, uWS::HttpRequest* req) {
//
//	/* You can efficiently stream huge files too */
//	res->writeHeader("Content-Type", "text/html; charset=utf-8")->end("Hello HTTP!");
//
//}

int runServer() {
	/*uWS::App().post("/fit", [](auto* res, auto* req) {
		ListenToFit(res, req);
		})
		.run();*/
}



