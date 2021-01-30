#include <dirent.h>

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/core/utility.hpp>

#include "localization.hpp"
#include "utility.hpp"

using namespace cv;
using namespace std;
using namespace samples;

void displayDetected(Mat croppedEar)
{
    imshow("Ear detection", croppedEar);
    waitKey(0);
    destroyAllWindows();
}

int detect(Mat frame, CascadeClassifier &cascade, bool display)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    //equalizeHist( frame_gray, frame_gray );

    Mat croppedEar(frame);
    std::vector<Rect> ears;
    cascade.detectMultiScale(frame_gray, ears);
    for (Rect ear : ears)
    {
        //rectangle(frame, ears[i], Scalar( 255, 0, 255 ), 4); // display a rectangle
        if (!isValidROI(ear, croppedEar))
        {
            return 0;
        }
        croppedEar = croppedEar(ear);
    }
    cout << ears.size() << "\n"
         << flush;
    ;
    if (display)
    {
        displayDetected(croppedEar);
    }
    return ears.size();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << " Usage: " << argv[0] << " path to dataset" << endl;
        return -1;
    }

    int datasetSize = getDatasetSize(argv[1]);

    vector<string> imageNames = readDataset(argv[1]);

    // Function findFile always reminds us where it found these files, just annoying to see
    freopen("/dev/null", "w", stderr);
    String leftEarCascadeName = findFile("haarcascade_mcs_leftear.xml");
    String rightEarCascadeName = findFile("haarcascade_mcs_rightear.xml");
    freopen("/dev/null", "w", stderr);

    CascadeClassifier leftEarCascade;
    CascadeClassifier rightEarCascade;

    initializeCascade(leftEarCascade, leftEarCascadeName);
    initializeCascade(rightEarCascade, rightEarCascadeName);

    for (String imageName : imageNames)
    {

        ostringstream imgPath;
        imgPath << argv[1] << imageName;

        Mat image = imread(imgPath.str(), IMREAD_COLOR); // Read the file

        if (image.empty())
        { // Check for invalid input
            cout << "Could not open or find the image" << std::endl;
            return -1;
        }

        // Checking left ear
        if (detect(image, leftEarCascade, false) == 0)
        {
            // Checking right ear
            if (detect(image, rightEarCascade, false) > 0)
            {
                cout << "Right ear found !\n"
                     << endl;
            }
        }
        else
        {
            cout << "Left ear found !\n"
                 << endl;
        }
    }

    return 0;
}