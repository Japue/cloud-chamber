#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
	cv::Mat frame;
	cv::VideoCapture cap;
	cap.open(2);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
	std::cout << "Start grabbing" << '\n' << "Press any key to terminate" << '\n';
	for(;;) {
		cap.read(frame);
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
    	}
		cv::imshow("Image", frame);
        if (cv::waitKey(5) >= 0)
            break;
	}	
	return 0;
}
