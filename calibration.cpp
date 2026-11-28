#include "calibration.h"

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <optional>


struct Drag {
	cv::Point start, current;
	bool dragging = false;
	cv::Rect rect;
};

void on_mouse(int action, int x, int y, int flags, void* userdata) {
	auto* d = static_cast<Drag*>(userdata);

	if (action == cv::EVENT_LBUTTONDOWN) {
		d -> start = d-> current = {x, y};
		d -> dragging = true;
		d -> rect = cv::Rect();
	} else if (action == cv::EVENT_MOUSEMOVE && d -> dragging) {
		d -> current = {x, y};
	} else if (action == cv::EVENT_LBUTTONUP && d -> dragging) {
		d -> dragging = false;
		d -> rect = cv::Rect(d -> start, cv::Point(x, y));
	}
}


std::optional<cv::Rect> calibrate() {
	// initialization
	cv::Mat frame;
	cv::VideoCapture cap;
	cv::namedWindow("Calibration");
	Drag drag;
	cv::Scalar green(0, 255, 0);
	cap.open(0);

	if (!cap.isOpened()) {
		std::cerr << "Unable to open camera\n";
		cv::destroyWindow("Calibration");
        return {};
    }

	//add the mouse callback for drawing the rectangle
	cv::setMouseCallback("Calibration", on_mouse, &drag);

	//start the loop
	std::cout << "Start grabbing" << '\n' << "Press q to quit, Esc to cancel and drag with LMB for rectangle" << '\n';
	int k = 0;
	while(k != 'q') {
		cap.read(frame);
		if (frame.empty()) {
			std::cerr << "blank frame grabbed\n";
			cv::destroyWindow("Calibration");
			return {};
    	}

		//retangle while dragging and one case where we use the result
		if (drag.dragging) {
			cv::rectangle(frame, drag.start, drag.current, green, 2);
		} else if (!drag.rect.empty()) {
			cv::rectangle(frame, drag.rect, green, 2);
		}

		cv::imshow("Calibration", frame);

		// event handling
		k = cv::waitKey(5);
		// Escape key
		if (k == 27) {
			cv::destroyWindow("Calibration");
			return {};
		}
	}	
	cv::destroyWindow("Calibration");
	if (drag.rect.empty()) {
		return {};
	} else {
		return drag.rect;
	}
}
