#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <string>

using namespace std;
using namespace cv;

int argNum = 30;

int main(int argc, char **argv)
{

    // Open the video
    VideoCapture vid("..\\..\\video\\flog.mpeg");
    if (!vid.isOpened())
    {
        std::cerr << "Error while opening the video" << std::endl;
        return -1;
    }

    // Read video frame by frame
    Mat frame;
    do{
        vid.read(frame); // Put one frame at a time
        if (frame.empty())
        {
            std::cout << "Video ended" << std::endl;
            break;
        }

        imshow("Video", frame); // Print frame
        if (waitKey(15) == 27)  // Each frame is displayed 25ms and escape if ESC key pressed
        {
            break;
        }

    } while (!frame.empty());

    vid.release();

    // Read it a second time but displaying feature points too

    VideoCapture vid2("..\\..\\video\\flog.mpeg");
    if (!vid2.isOpened())
    {
        std::cerr << "Error while opening the video" << std::endl;
        return -1;
    }

    // Save the video
    int frame_width = vid2.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = vid2.get(cv::CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("..\\..\\output\\flog.avi", cv::VideoWriter::fourcc('M','J','P','G'), 25, Size(frame_width,frame_height));

    // Feature points
    vector<KeyPoint> keypoints;
    Mat imFeatPt;

    do{
        vid2 >> frame; // Put one frame at a time
        if (frame.empty())
        {
            std::cout << "Video ended" << std::endl;
            break;
        }

        // Fast
        Ptr<FastFeatureDetector> fast = FastFeatureDetector ::create();
        fast->detect(frame, keypoints);

        drawKeypoints(frame, keypoints, imFeatPt);

        video.write(imFeatPt);

        imshow("Video with keypoints", imFeatPt);
        if (waitKey(10) == 27) // Each frame is displayed 25ms and escape if ESC key pressed
        {
            break;
        }
    } while (!frame.empty());



    // Destroy
    vid2.release();
    video.release();
    frame.release();
    imFeatPt.release();

    return 0;
}