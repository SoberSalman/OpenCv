#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


int CalcMean(int array[], int n) {

    int sum = 0;

    for (int i = 0; i < n; i++) {

        sum += array[i];

    }


    return sum / n;

}

int Calc_Distance(int coordinates[3], int centroid[3]) {

    int distance = sqrt(pow(coordinates[0] - centroid[0], 2) + pow(coordinates[1] - centroid[1], 2) + pow(coordinates[2] - centroid[2], 2));

    return distance;
}

void kMeansClustering() {

    Mat img;
    img = cv::imread("A:/Original Images/IMD063.bmp", IMREAD_COLOR);

    int** RGB_RED = new int* [img.rows];
    int** RGB_GREEN = new int* [img.rows];
    int** RGB_BLUE = new int* [img.rows];

    for (int i = 0; i < img.rows; i++) {

        RGB_RED[i] = new int[img.cols];
        RGB_GREEN[i] = new int[img.cols];
        RGB_BLUE[i] = new int[img.cols];

    }

    for (int i = 0; i < img.rows; i++) {

        for (int j = 0; j < img.cols; j++) {

            RGB_BLUE[i][j] = int(img.at<Vec3b>(i, j)[0]);
            RGB_RED[i][j] = int(img.at<Vec3b>(i, j)[2]);
            RGB_GREEN[i][j] = int(img.at<Vec3b>(i, j)[1]);

        }

    }


    int prev_Centroid_K1[3] = { 0,0,0 };
    int prev_Centroid_K2[3] = { 0,0,0 };
    int Centroid_K1[3] = { 50,50,50 };
    int Centroid_K2[3] = { 130,130,130 };

    int* RED_K1 = new int[5000000];
    int* GREEN_K1 = new int[5000000];
    int* BLUE_K1 = new int[5000000];
    int K1_SIZE = 0;
    int* K1_INDEX_i = new int[5000000];
    int* k1_INDEX_J = new int[5000000];


    int* RED_K2 = new int[5000000];
    int* GREEN_K2 = new int[5000000];
    int* BLUE_K2 = new int[5000000];
    int K2_SIZE = 0;
    int* K2_INDEX_i = new int[5000000];
    int* K2_INDEX_j = new int[5000000];

    int K1_distance = 0;
    int K2_distance = 0;

    int *coordinates = new int[3];

  


    for (int z = 0; z < 50; z++) {

        K1_SIZE = 0;
        K2_SIZE = 0;

        for (int i = 0; i < img.rows; i++) {

            for (int j = 0; j < img.cols; j++) {

                coordinates[0] = RGB_BLUE[i][j];
                coordinates[1] = RGB_RED[i][j];
                coordinates[2] = RGB_GREEN[i][j];

                K1_distance = Calc_Distance(coordinates, Centroid_K1);
                K2_distance = Calc_Distance(coordinates, Centroid_K2);

                if (K1_distance < K2_distance) {

                    BLUE_K1[K1_SIZE] = coordinates[0];
                    RED_K1[K1_SIZE] = coordinates[1];
                    GREEN_K1[K1_SIZE] = coordinates[2];
                    K1_INDEX_i[K1_SIZE] = i;
                    k1_INDEX_J[K1_SIZE++] = j;

                }

                else {

                    BLUE_K2[K2_SIZE] = coordinates[0];
                    RED_K2[K2_SIZE] = coordinates[1];
                    GREEN_K2[K2_SIZE] = coordinates[2];
                    K2_INDEX_i[K2_SIZE] = i;
                    K2_INDEX_j[K2_SIZE++] = j;

                }

            }

        }


            prev_Centroid_K1[0] = Centroid_K1[0];
            prev_Centroid_K2[0] = Centroid_K2[0];

            prev_Centroid_K1[1] = Centroid_K1[1];
            prev_Centroid_K2[1] = Centroid_K2[1];

            prev_Centroid_K1[2] = Centroid_K1[2];
            prev_Centroid_K2[2] = Centroid_K2[2];


        

        Centroid_K1[0] = CalcMean(BLUE_K1, K1_SIZE);
        Centroid_K1[1] = CalcMean(RED_K1, K1_SIZE);
        Centroid_K1[2] = CalcMean(GREEN_K1, K1_SIZE);

        Centroid_K2[0] = CalcMean(BLUE_K2, K2_SIZE);
        Centroid_K2[1] = CalcMean(RED_K2, K2_SIZE);
        Centroid_K2[2] = CalcMean(GREEN_K2, K2_SIZE);

    }

  

    for (int i = 0; i < K1_SIZE; i++) {


        RGB_BLUE[K1_INDEX_i[i]][k1_INDEX_J[i]] = 255;
        RGB_RED[K1_INDEX_i[i]][k1_INDEX_J[i]] = 255;
        RGB_GREEN[K1_INDEX_i[i]][k1_INDEX_J[i]] = 255;

    }

    for (int i = 0; i < K2_SIZE; i++) {


        RGB_BLUE[K2_INDEX_i[i]][K2_INDEX_j[i]] = 0;
        RGB_RED[K2_INDEX_i[i]][K2_INDEX_j[i]] = 0;
        RGB_GREEN[K2_INDEX_i[i]][K2_INDEX_j[i]] = 0;

    }

   

    for (int i = 0; i < img.rows; i++) {

        for (int j = 0; j < img.cols; j++) {

            if (i <= img.rows / 3 && j <= img.cols / 5 && ((i + j) < 250)) {

                RGB_BLUE[i][j] = 0;
                RGB_RED[i][j] = 0;
                RGB_GREEN[i][j] = 0;

            }

            if (i <= img.rows / 3 && j >= 3 * (img.cols / 4) && (abs(i - j) > 530)) {

                RGB_BLUE[i][j] = 0;
                RGB_RED[i][j] = 0;
                RGB_GREEN[i][j] = 0;

            }

            if (i >= 3 * (img.rows / 4) && j <= img.cols / 5 && j < 500 - i) {

                RGB_BLUE[i][j] = 0;
                RGB_RED[i][j] = 0;
                RGB_GREEN[i][j] = 0;

            }

            if (i >= 3 * (img.rows / 4) && j >= 3 * (img.cols / 4)) {

                RGB_BLUE[i][j] = 0;
                RGB_RED[i][j] = 0;
                RGB_GREEN[i][j] = 0;

            }

        }

    }




    for (int i = 0; i < img.rows; i++) {

        for (int j = 0; j < img.cols; j++) {

            img.at<Vec3b>(i, j)[0] = RGB_BLUE[i][j];
            img.at<Vec3b>(i, j)[1] = RGB_RED[i][j];
            img.at<Vec3b>(i, j)[2] = RGB_GREEN[i][j];

        }

    }

    imwrite("TASK2.png", img);


}




