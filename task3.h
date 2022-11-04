#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


void DiceCoefficient()
{
    Mat GroundTruthImage = imread("A:/Ground Truths/IMD063_lesion.bmp", IMREAD_GRAYSCALE);
    Mat MY_image = imread("C:/Users/salma/Desktop/ass1/TASK1.png", IMREAD_GRAYSCALE);





    int** Ground_Truth_image = new int* [GroundTruthImage.rows];
    for (int i = 0; i < GroundTruthImage.rows; i++)
    {
        Ground_Truth_image[i] = new int[GroundTruthImage.cols];
    }

    int** MY_IMAGE = new int* [MY_image.rows];
    for (int i = 0; i < MY_image.rows; i++)
    {
        MY_IMAGE[i] = new int[MY_image.cols];
    }

    for (int j = 0; j < GroundTruthImage.rows; j++)
    {
        for (int k = 0; k < GroundTruthImage.cols; k++)
        {
            Ground_Truth_image[j][k] = int(GroundTruthImage.at<uint8_t>(j, k));

        }
    }

    for (int j = 0; j < MY_image.rows; j++)
    {
        for (int k = 0; k < MY_image.cols; k++)
        {
            MY_IMAGE[j][k] = int(MY_image.at<uint8_t>(j, k));

        }
    }

    int TP = 0;
    int FP = 0;
    int FN = 0;


    for (int i = 0; i < GroundTruthImage.rows; i++)
    {
        for (int j = 0; j < GroundTruthImage.cols; j++)
        {
            if (Ground_Truth_image[i][j] != 0)
            {
                if (Ground_Truth_image[i][j] == MY_IMAGE[i][j])
                {
                    TP++;
                }
            }
        }
    }

    for (int i = 0; i < GroundTruthImage.rows; i++)
    {
        for (int j = 0; j < GroundTruthImage.cols; j++)
        {
            if (MY_IMAGE[i][j] != 0)
            {
                if (Ground_Truth_image[i][j] != MY_IMAGE[i][j])
                {
                    FP++;
                }
            }
        }
    }

    for (int i = 0; i < GroundTruthImage.rows; i++)
    {
        for (int j = 0; j < GroundTruthImage.cols; j++)
        {
            if (MY_IMAGE[i][j] == 0)
            {
                if (Ground_Truth_image[i][j] != MY_IMAGE[i][j])
                {
                    FN++;
                }
            }
        }
    }

    double Dice_Coff = ((2.0 * TP) / (FN + FP + (2.0 * TP)));



    cout << "DICE COEFFICIENT : " << Dice_Coff << endl;
}