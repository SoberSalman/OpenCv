#pragma once
#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

void bubbleSort(int arr[], int n) {


    int i, j;
    for (i = 0; i < n - 1; i++)
    {

        // Last i elements are already
        // in place
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

int remove_duplicate_elements(int arr[], int n)
{

    if (n == 0 || n == 1)
        return n;

    int* temp = new int[n];

    int j = 0;
    int i;
    for (i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];
    temp[j++] = arr[n - 1];

    for (i = 0; i < j; i++)
        arr[i] = temp[i];

    return j;
}

int no_of_labels(int n)
{
    return n;
}


int** connectedcomponents(Mat img)
{

    int** imagearray = new int* [img.rows];
    for (int i = 0; i < img.rows; i++)
    {
        imagearray[i] = new int[img.cols];
    }

    for (int j = 0; j < img.rows; j++)
    {
        for (int k = 0; k < img.cols; k++)
        {
            imagearray[j][k] = img.at<uint8_t>(j, k);

        }
    }

    for (int i = 0; i < img.cols; i++)
    {
        imagearray[0][i] = 0;                                         
        imagearray[img.rows - 1][i] = 0; 
    }

    for (int j = 0; j < img.rows; j++)
    {
        imagearray[j][0] = 0;
        imagearray[j][img.cols - 1] = 0;
    }

    int* equivalencearray = new int[100000000];
    int* equivalencearray2 = new int[100000000];
    int equvalence_counter = 0;

    int count = 1;
    for (int i = 1; i < img.rows - 1; i++)
    {
        for (int j = 1; j < img.cols - 1; j++)
        {
            if (imagearray[i][j] != 0)
            {
                // 0000 all neighbours are zero
                if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] == 0)
                {
                    imagearray[i][j] = count++;
                }

                // concidering 1 is white and 0 is black
                // case 2 // if anyone is white
                //1000
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] == 0)
                {
                    imagearray[i][j] = imagearray[i][j - 1];

                }
                //0100
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] == 0)
                {
                    imagearray[i][j] = imagearray[i - 1][j - 1];
                }
                //0010
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] == 0)
                {
                    imagearray[i][j] = imagearray[i - 1][j];
                }
                //0001
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] != 0)
                {
                    imagearray[i][j] = imagearray[i - 1][j + 1];
                }

                // case 3 if more than one neighbour is black
                // 0011
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i - 1][j] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i - 1][j];
                        temparr[1] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 2); // bubble sort to find the lowest label and assign it to the pixel


                        // using two parallel arrays and putting the labels in them to match equivalency
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0]; 
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;
                    }
                }
                // 0101
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i - 1][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j + 1];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i - 1][j - 1];
                        temparr[1] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 2);
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0];
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;

                    }
                }
                // 0110
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] == 0)
                {
                    if (imagearray[i - 1][j] == imagearray[i - 1][j - 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j - 1];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i - 1][j];
                        temparr[1] = imagearray[i - 1][j - 1];
                        bubbleSort(temparr, 2);
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0];
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;

                    }
                }
                // 1001
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j + 1];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 2);
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0];
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;

                    }
                }
                // 1010
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] == 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j])
                    {
                        imagearray[i][j] = imagearray[i - 1][j];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j];
                        bubbleSort(temparr, 2);
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0];
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;

                    }
                }
                // 1100
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] == 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j - 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j - 1];
                    }
                    else
                    {
                        int temparr[2];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j - 1];
                        bubbleSort(temparr, 2);
                        imagearray[i][j] = temparr[0];
                        equivalencearray[equvalence_counter] = temparr[0];
                        equivalencearray2[equvalence_counter] = temparr[1];
                        equvalence_counter++;

                    }
                }
                // 0111
                else if (imagearray[i][j - 1] == 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i - 1][j - 1] == imagearray[i - 1][j] && imagearray[i - 1][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i - 1][j - 1];
                    }
                    else
                    {
                        int temparr[3];
                        temparr[0] = imagearray[i - 1][j - 1];
                        temparr[1] = imagearray[i - 1][j];
                        temparr[2] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 3);
                        imagearray[i][j] = temparr[0];
                        int size = remove_duplicate_elements(temparr, 3);   



                        for (int i = 0; i < size; i++)
                        {
                            equivalencearray[equvalence_counter] = temparr[0];
                            equivalencearray2[equvalence_counter] = temparr[i];
                            equvalence_counter++;
                        }
                    }
                }
                // 1011
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] == 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j] && imagearray[i][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i][j - 1];
                    }
                    else
                    {
                        int temparr[3];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j];
                        temparr[2] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 3);
                        imagearray[i][j] = temparr[0];
                        int size = remove_duplicate_elements(temparr, 3);



                        for (int i = 0; i < size; i++)
                        {
                            equivalencearray[equvalence_counter] = temparr[0];
                            equivalencearray2[equvalence_counter] = temparr[i];
                            equvalence_counter++;
                        }
                    }
                }
                // 1101
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] == 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j - 1] && imagearray[i][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i][j - 1];
                    }
                    else
                    {
                        int temparr[3];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j - 1];
                        temparr[2] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 3);
                        imagearray[i][j] = temparr[0];
                        int size = remove_duplicate_elements(temparr, 3);



                        for (int i = 0; i < size; i++)
                        {
                            equivalencearray[equvalence_counter] = temparr[0];
                            equivalencearray2[equvalence_counter] = temparr[i];
                            equvalence_counter++;
                        }
                    }
                }
                //1110
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] == 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j - 1] && imagearray[i][j - 1] == imagearray[i - 1][j])
                    {
                        imagearray[i][j] = imagearray[i][j - 1];
                    }
                    else
                    {
                        int temparr[3];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j - 1];
                        temparr[2] = imagearray[i - 1][j];
                        bubbleSort(temparr, 3);
                        imagearray[i][j] = temparr[0];
                        int size = remove_duplicate_elements(temparr, 3);



                        for (int i = 0; i < size; i++)
                        {
                            equivalencearray[equvalence_counter] = temparr[0];
                            equivalencearray2[equvalence_counter] = temparr[i];
                            equvalence_counter++;
                        }
                    }
                }
                // 1111
                else if (imagearray[i][j - 1] != 0 && imagearray[i - 1][j - 1] != 0 && imagearray[i - 1][j] != 0 && imagearray[i - 1][j + 1] != 0)
                {
                    if (imagearray[i][j - 1] == imagearray[i - 1][j - 1] && imagearray[i][j - 1] == imagearray[i - 1][j] && imagearray[i][j - 1] == imagearray[i - 1][j + 1])
                    {
                        imagearray[i][j] = imagearray[i][j - 1];
                    }
                    else
                    {
                        int temparr[4];
                        temparr[0] = imagearray[i][j - 1];
                        temparr[1] = imagearray[i - 1][j - 1];
                        temparr[2] = imagearray[i - 1][j];
                        temparr[3] = imagearray[i - 1][j + 1];
                        bubbleSort(temparr, 4);
                        imagearray[i][j] = temparr[0];
                        int size = remove_duplicate_elements(temparr, 3);



                        for (int i = 0; i < size; i++)
                        {
                            equivalencearray[equvalence_counter] = temparr[0];
                            equivalencearray2[equvalence_counter] = temparr[i];
                            equvalence_counter++;
                        }
                    }
                }
            }
        }
    }

    imagearray[0][0] = count;



    // assing equvalent labels
    for (int i = 1; i < img.rows - 1; i++) {

        for (int j = 1; j < img.cols - 1; j++) {

            for (int k = equvalence_counter; k >= 0; k--) {

                if (imagearray[i][j] == equivalencearray2[k]) {

                    imagearray[i][j] = equivalencearray[k];

                }

            }

        }

    }





    delete[] equivalencearray;
    delete[] equivalencearray2;




    return imagearray;





}



void detectlesion()
{


    cv::Mat img = cv::imread("A:/Segmented Outputs/mIMD063.bmp", IMREAD_GRAYSCALE);
    namedWindow("2nd OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("2nd OpenCV Application", img);
    cv::moveWindow("2nd OpenCV Application", 0, 45);

    int** imagearray = new int* [img.rows];
    for (int i = 0; i < img.rows; i++)
    {
        imagearray[i] = new int[img.cols];
    }
   imagearray = connectedcomponents(img);


    int maximum_lablel_counter = 0;
    int max = 0;

    int count = imagearray[0][0];

    imagearray[0][0] = 0;


    int* array = new int[count];

    for (int i = 0; i < count; i++) {

        array[i] = 0;

    }

    // using an all 0 array of the size of our number of labels 
    // and assigning the values of our image arrays in out labelarray.

    for (int i = 1; i < img.rows - 1; i++) {

        for (int j = 1; j < img.cols - 1; j++) {

            array[imagearray[i][j]]++;

        }

    }

    // finding the maximum label in our array and storing it an variable

    for (int i = 1; i < count; i++) {

        if (array[i] > maximum_lablel_counter) {

            maximum_lablel_counter = array[i];
            max = i;

        }

    }

    // writing the image for our biggest lesion 

    for (int i = 1; i < img.rows - 1; i++) {

        for (int j = 1; j < img.cols - 1; j++) {

            if (imagearray[i][j] == max) {

                imagearray[i][j] = 255;

            }
            else
            {
                imagearray[i][j] = 0;
            }

        }

    }

    for (int i = 0; i < img.rows; i++) {

        for (int j = 0; j < img.cols; j++) {

            img.at<uint8_t>(i, j) = imagearray[i][j];

        }

    }


    imwrite("TASK1.png", img);

    for (int i = 0; i < img.rows; i++) {
        delete[] imagearray[i];
        imagearray[i] = NULL;
    }
    delete[] imagearray;
    imagearray = NULL;

    cv::waitKey(0);
    cv::destroyAllWindows();









    return;
}