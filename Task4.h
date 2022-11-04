#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


class NODE
{
private:
    int data = 0;
    NODE* next = NULL;
public:

    NODE()
    {
    }

    NODE(int n)
    {
        data = n;
    }

    void setdata(int n)
    {
        data = n;
    }

    int getdata()
    {
        return data;
    }

    void setnode(NODE* node)
    {
        next = node;
    }

    NODE* getnode()
    {
        return next;
    }
};


class RLC_Linked_List
{
    NODE* head = NULL;

public:

    RLC_Linked_List() {}

    bool insert(int d)
    {
        if (head == NULL)
        {
            NODE* newnode = new NODE();
            newnode->setdata(d);
            newnode->setnode(NULL);
            head = newnode;

            return true;

        }
        else
        {

            NODE* newnode = head;

            while (newnode->getnode() != NULL)
            {
                newnode = newnode->getnode();
            }

            NODE* temp = new NODE(d);

            newnode->setnode(temp);
            return true;
        }

    }

    void PrintList()
    {
        while (head != NULL)
        {

            cout << head->getdata() << "  ";
            if (head->getdata() < 0)
            {
                cout << endl;
            }
            head = head->getnode();

        }
    }
};




void RLC()
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

    for (int j = 0; j < img.rows; j++)
    {
        for (int k = 0; k < img.cols; k++)
        {
            imagearray[j][k] = img.at<uint8_t>(j, k);

        }
    }

    RLC_Linked_List R;







    R.insert(img.rows);
    R.insert(img.cols);
    cout << endl;
    R.insert(-1);



    int blackstart = 0;
    int blackend = 0;
    bool found = false;

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            int x = imagearray[i][j];

            if (x == 255 && found == false)
            {
                blackstart = j;
                found = true;
                if (found == true && j == img.cols - 1)
                {
                    blackend = j;
                    found = false;
                    /*cout << blackstart << " " << blackend << " ";*/
                    R.insert(blackstart);
                    R.insert(blackend);
                }
            }
            else if (found == true && x != 255)
            {
                blackend = j - 1;
                found = false;
                R.insert(blackstart);
                R.insert(blackend);
                //   cout << blackstart << " " << blackend << " ";
            }
            else if (found == true and j == img.cols - 1)
            {
                blackend = j;
                found = false;

                R.insert(blackstart);
                R.insert(blackend);
            }
        }
        R.insert(-1);

    }





    R.PrintList();



    cv::waitKey(0);
    cv::destroyAllWindows();
    return ;
}