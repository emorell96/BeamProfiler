#pragma once

#include "json.hpp"
#include <uwebsockets/App.h>

#include "SmoothInfo.h"
#include "ResizeInfo.h"

#include <string>
#include <string_view>

#include "ImageHandler.h"
#include "FitParameters.h"
#include "BeamProfiler.h"





#include "FitOptions.h"
#include "FitResults.h"

//using json;

FitResults Fit(std::string filepath, SmoothInfo smoothInfo, ResizeInfo resizeInfo, FitParameters fitParameters)
{
	ImageHandler imageHandler;

	imageHandler.Process(filepath, smoothInfo, resizeInfo);

	BeamProfiler profiler(imageHandler, fitParameters);

	profiler.Fit();

	FitResults fitResults;

	fitResults.imageInformation = imageHandler.GetImageInformation();

	fitResults.finalParameters =  profiler.GetParameters();

	return fitResults;
}

class HttpParser {
public:
	void ParseData(std::string_view data, bool last, uWS::HttpResponse<false>* res) {
		//auto value = std::string(data);
		if (data.length() > 0) {
			buffer.append(data.data(), data.length());
		}
		

		if (last && buffer.length() > 0) {
			auto j = nlohmann::json::parse(std::string(buffer).c_str());
			
			FitOptions fitOptions = j.get<FitOptions>();

			auto results = Fit(fitOptions.filePath, SmoothInfo(fitOptions.imageOptions.smoothOptions), ResizeInfo(fitOptions.imageOptions.resizeOptions), fitOptions.fitParameters);
			
			json jfinal = results;
			std::string response = jfinal.dump();
			//res->write(j);
			res->tryEnd(response, response.length());
		}

	}
	std::string buffer = "";
};

void ListenToFit(uWS::HttpResponse<false>* res, uWS::HttpRequest* req, HttpParser& parser) {


	/* You can efficiently stream huge files too */
	res->writeHeader("Content-Type", "application/json; charset=utf-8");
	/* Allocate automatic, stack, variable as usual */
	//std::string buffer;
	res->onData([&](std::string_view data, bool last) {
			parser.ParseData(data, last, res);
		});
	res->onAborted([&]() {
		res->tryEnd("aborted");
		});
}

class server {
private:
	int portUsed = 9001;
	us_listen_socket_t* socket;

	int shutDown() {
		us_listen_socket_close(0, socket);
		return 0;
	}
public:

	int runServer(int port) {
		portUsed = port;

		uWS::App()
			.get("/close", [&](auto* res, auto* req) {
			res->end("Shutting down!");
			shutDown();
		})
			.post("/fit", [](auto* res, auto* req) {
			HttpParser parser;
		ListenToFit(res, req, parser);
				})
			.listen(port, [&](auto* listenSocket) {
					socket = listenSocket;
					if (listenSocket) {
						std::cout << "Listening on port " << port << std::endl;
					}
					else {
						std::cout << "Failed to load certs or to bind to port" << std::endl;
					}

				})
					.run();
				std::cout << "Shutting down!" << std::endl;
				return 0;
	}
};

extern "C" __declspec(dllexport) int runServer(int port) {
	server server;
	return server.runServer(port);
}




