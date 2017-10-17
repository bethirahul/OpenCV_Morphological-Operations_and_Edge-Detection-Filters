// Computer Vision and Image Processing - Assignment 4
// Rahul Bethi
// A03972041
// rbethi@islander.tamucc.edu
// OpenCV 2.4.9 | Putty 0.65 | WinSCP 575 | Xming 6.9.0.13 | Notepad++ 6.8.3 | Windows 10 64bit

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int morphImage( int );
int boundaryExtraction();
int topHat( int );
int edgeDetection( int );
int displayImage( Mat );

int exit_flag = 0;					// This flag is used to retain in the program after the execution of a task.

int main()	// Main Program
{
	int choice = 0;
	
	while(exit_flag == 0)
	{
		choice = 0;
		cout << "\n>> ** Morphological Operations :-\n";
		cout << ">>     1 - Erode\n";
		cout << ">>     2 - Dilate\n";
		cout << ">>     3 - Open\n";
		cout << ">>     4 - Close\n";
		cout << ">>     5 - Boundary Extraction\n";
		cout << ">> ** TopHat Operations using :-\n";
		cout << ">>     6 - Threshold\n";
		cout << ">>     7 - Open   with Disk SE of radius 40\n";
		cout << ">>     8 - TopHat with Disk SE of radius 40\n";
		cout << ">>     9 - Thresholded TopHat\n";
		cout << ">> ** Edge Detection :-\n";
		cout << ">>    10 - Prewitt Filter\n";
		cout << ">>    11 - Soble Filter\n";
		cout << ">>    12 - Canny Filter\n";
		cout << ">> ** Any other option to exit\n\n";
		cout << "<< Enter your choice: ";
		cin >> choice;									// Input saved in interger variable choice
		
		if	   (choice > 0 && choice < 5)	morphImage( choice );			// functions are called according to the choice chosen.
		else if(choice == 5)				boundaryExtraction();
		else if(choice > 5 && choice < 10)	topHat( choice );
		else if(choice > 9 && choice < 13)	edgeDetection( choice );
		else
		{
			cout << "\n>> Error: Invalid input - Defalut action - Exit\n\n";
			exit_flag = 1;		// Exit flag is set to 1 to exit the program if anyone other input is given other than the options given.
		}
	}
	return 0;
}

int morphImage( int c )
{
	Mat in_img, out_img, k_element, tmp_img;
	int k_size = 1;
	
	in_img = imread("Fig0911(a)(noisy_fingerprint).tif", CV_LOAD_IMAGE_GRAYSCALE);
	if(in_img.empty())
	{
		cout << "\n>> Error : Image cannot be loaded..!!\n";
		return -1;
	}
	
	k_element = getStructuringElement( MORPH_RECT,
									   Size( (2*k_size)+1, (2*k_size)+1 ),
									   Point( k_size, k_size )			   );
	if(c == 1)
	{
		erode( in_img, out_img, k_element );
		imwrite("erode.tif", out_img);  // Output of erode is stored in this file.
	}
	else if(c == 2)
	{
		dilate( in_img, out_img, k_element );
		imwrite("dilate.tif", out_img);  // Output of dilate is stored in this file.
	}
	else if(c == 3)
	{
		morphologyEx(in_img, out_img, MORPH_OPEN, k_element);
		imwrite("open.tif", out_img);  // Output of open is stored in this file.
	}
	else
	{
		morphologyEx(in_img, out_img, MORPH_CLOSE, k_element);
		imwrite("close.tif", out_img);  // Output of close is stored in this file.
	}
	displayImage( out_img );
	
	return 0;
}

int boundaryExtraction()
{
	Mat in_img, out_img, k_element;
	int k_size = 1, r, c;
	
	in_img = imread("Fig0914(a)(licoln from penny).tif", CV_LOAD_IMAGE_GRAYSCALE);
	if(in_img.empty())
	{
		cout << "\n>> Error : Image cannot be loaded..!!\n";
		return -1;
	}
	
	k_element = getStructuringElement( MORPH_RECT,
									   Size( (2*k_size)+1, (2*k_size)+1 ),
									   Point( k_size, k_size )			   );
	erode( in_img, out_img, k_element );
	for(c = 0; c<in_img.cols; c++)
	{
		for(r = 0; r<in_img.rows; r++)
		{
			out_img.at<uchar>(r,c) = in_img.at<uchar>(r,c) - out_img.at<uchar>(r,c);
		}
	}
	imwrite("boundary_extraction.tif", out_img);  // Output of erode is stored in this file.
	displayImage( out_img );
	
	return 0;
}

int topHat( int c )
{
	Mat in_img, out_img, tmp_img, k_element;
	int t_value = 133, k_size = 1, row, col;
	
	in_img = imread("Fig0940(a)(rice_image_with_intensity_gradient).tif", CV_LOAD_IMAGE_GRAYSCALE);
	if(in_img.empty())
	{
		cout << "\n>> Error : Image cannot be loaded..!!\n";
		return -1;
	}
	
	if(c == 6)
	{
		t_value = 133;
		out_img = in_img.clone();
		for(col = 0; col<in_img.cols; col++)
		{
			for(row = 0; row<in_img.rows; row++)
			{
				if(in_img.at<uchar>(row,col) < t_value)
				{
					out_img.at<uchar>(row,col) = 0;
				}
			}
		}
		imwrite("threshold.tif", out_img);  // Output of thresholded is stored in this file.
	}
	else if(c == 7)
	{
		k_element = getStructuringElement( MORPH_ELLIPSE,
										   Size( 80, 80 ),
										   Point( k_size, k_size ));
		morphologyEx( in_img, out_img, MORPH_OPEN, k_element );
		imwrite("OpenDiskSE40.tif", out_img);  // Output of Opened disk SE is stored in this file.
	}
	else if(c == 8)
	{
		k_element = getStructuringElement( MORPH_ELLIPSE,
										   Size( 80, 80 ),
										   Point( k_size, k_size ));
		morphologyEx(in_img, out_img, MORPH_TOPHAT, k_element);
		imwrite("topHat.tif", out_img);  // Output of Top Hat is stored in this file.
	}
	else
	{
		t_value = 133;
		tmp_img = in_img.clone();
		for(col = 0; col<in_img.cols; col++)
		{
			for(row = 0; row<in_img.rows; row++)
			{
				if(in_img.at<uchar>(row,col) < t_value)
				{
					tmp_img.at<uchar>(row,col) = 0;
				}
			}
		}
		k_element = getStructuringElement( MORPH_ELLIPSE,
										   Size( 80, 80 ),
										   Point( k_size, k_size ));
		morphologyEx(tmp_img, out_img, MORPH_TOPHAT, k_element);
		imwrite("thresholdedTopHat.tif", out_img);  // Output of Thresholded Top Hat is stored in this file.
	}
	displayImage( out_img );
	
	return 0;
}

int edgeDetection( int c )
{
	Mat in_img, out_img, tmp_img, k_element;
	int row, col, k_size = 3;
	double d = 0, s = 1, a, b;
	
	in_img = imread("Fig1016(a)(building_original).tif", CV_LOAD_IMAGE_GRAYSCALE);
	if(in_img.empty())
	{
		cout << "\n>> Error : Image cannot be loaded..!!\n";
		return -1;
	}
	
	if(c == 10)
	{
		k_element.create(k_size, k_size, CV_8S);
		k_element = (Mat_<char>(3,3)<< -1,0,1,-1,0,1,-1,0,1);
		filter2D(in_img, tmp_img, in_img.depth(), k_element, Point(-1,-1), d, BORDER_DEFAULT);
		imwrite("prewitt_vertical.tif", tmp_img);  // Output of Prewitt Vertical Filter is stored in this file.
		k_element = (Mat_<char>(3,3)<< -1,-1,-1,0,0,0,1,1,1);
		filter2D(in_img, out_img, in_img.depth(), k_element, Point(-1,-1), d, BORDER_DEFAULT);
		imwrite("prewitt_horizontal.tif", out_img);  // Output of Prewitt Horizontal Filter is stored in this file.
		for(col = 0; col<in_img.cols; col++)
		{
			for(row = 0; row<in_img.rows; row++)
			{
				a = out_img.at<uchar>(row,col);
				b = tmp_img.at<uchar>(row,col);
				a = a + b;
				if(a > 255) a = 255;
				out_img.at<uchar>(row,col) = a;
			}
		}
		imwrite("prewitt.tif", out_img);  // Output of Prewitt Filter is stored in this file.
	}
	else if(c == 11)
	{
		Sobel(in_img, out_img, in_img.depth(), 1, 1, k_size, s, d, BORDER_DEFAULT);
		imwrite("sobel.tif", out_img);  // Output of Sobel Filter is stored in this file.
	}
	else
	{
		Canny( in_img, out_img, 75, 175, k_size );
		imwrite("canny.tif", out_img);  // Output of Canny Filter is stored in this file.
	}
	displayImage( out_img );
	
	return 0;
}

int displayImage( Mat img )
{
	namedWindow("OutputImage", CV_WINDOW_AUTOSIZE);
	startWindowThread();
	imshow("OutputImage", img);
	waitKey(0);
	destroyWindow("OutputImage");
}