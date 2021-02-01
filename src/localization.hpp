#include <dirent.h>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>

#include "opencv2/imgproc.hpp"
#include "utility.hpp"

using namespace cv;
using namespace cv::dnn;
using namespace std;
using namespace samples;

vector<vector<Rect>> cropAndFlipImages(char *datasetPath, vector<string> imageNames,
                       bool debugFlag = false);

void initializeCascade(CascadeClassifier &, String);

bool isValidROI(Rect, Mat);

void displayDetected(Mat croppedEar);

bool detectROI(Mat frame, CascadeClassifier &cascade,
               vector<vector<Rect>> &ROI, bool rightClassifier,
               String imageName);

void detectLandmarks(Mat img, vector<Point2d> &ldmk);
