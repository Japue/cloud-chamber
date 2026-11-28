#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "calibration.h"

int main(int argc, char* argv[]) {
	// calibration
	std::optional<cv::Rect> rect = calibrate();
	if (!rect) {
		std::cerr << "calibration failed";
		return -1;
	}
	cv::Range row_range(rect -> y, rect -> y + rect -> height);
	cv::Range col_range(rect -> x, rect -> x + rect -> width);

	// initialization
	cv::Mat frame;
	cv::VideoCapture cap;
	cap.open(0);
	cv::namedWindow("Feed");

	if (!cap.isOpened()) {
		std::cerr << "Unable to open camera\n";
        return -1;
    }

	std::cout << "Start grabbing" << '\n' << "Press q to terminate" << '\n';
	int k = 0;
	while(k != 'q') {
		cap.read(frame);
		if (frame.empty()) {
			std::cerr << "blank frame grabbed\n";
			cv::destroyWindow("Feed");
			return {};
    	}

		cv::Mat cropped = frame(row_range, col_range);
		cv::imshow("Feed", cropped);

		// event handling
		k = cv::waitKey(5);
	}
	cap.release();
	cv::destroyAllWindows();
	return 0;
}
