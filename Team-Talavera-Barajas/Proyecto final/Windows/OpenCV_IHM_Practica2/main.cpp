#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* temp_window = "Temp window";
int match_method = 4;
int index = 0;
bool _debug = true;

int h_bins = 50, s_bins = 60;
int histSize[] = { h_bins, s_bins };
int channels[] = { 0, 1 };
float h_ranges[] = { 0, 180 };
float s_ranges[] = { 0, 256 };
const float* ranges[] = { h_ranges, s_ranges };


class paths_images{
		int size = 0;
	public:
		double porcentange;
		Mat CompareFiles[3];
		MatND hist_template[3];
		string  Name;
		int priority = 0;

		paths_images::paths_images(){}

		paths_images::paths_images(double pPorcentaje){
			porcentange = pPorcentaje;
		}
		void paths_images::addString(string pPath){
			MatND _hist;

			CompareFiles[size] = imread(pPath, 1);
			calcHist(&CompareFiles[size], 1, channels, Mat(), _hist, 2, histSize, ranges, true, false);
			normalize(_hist, _hist, 0, 1, NORM_MINMAX, -1, Mat());
			hist_template[size] = _hist;
			size++;
		}
		int paths_images::Size(){
			return size;
		}
};


paths_images images_array[10];
/// Function Headers
void MatchingMethod(int, void*);

void MatchingMethod_priority(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	int index_array = 0;
	//initialize the class for all the images and Paths
	//Limite 50 km
	images_array[index_array] = paths_images(0.58);
	images_array[index_array].Name = "Se�al de 50KM";
	images_array[index_array].priority = 0;
	images_array[index_array].addString("openCV\\50limit.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen parada
	images_array[index_array] = paths_images(0.53);
	images_array[index_array].Name = "Se�al Parada de Autobus";
	images_array[index_array].addString("openCV\\parada.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen peaton
	images_array[index_array] = paths_images(0.815);
	images_array[index_array].Name = "Se�al de peaton";
	images_array[index_array].addString("openCV\\pea.jpg");
	images_array[index_array].addString("openCV\\NPEA.jpg");
	//images_array[2].addString("C:\\Users\\edgar\\Pictures\\openCV\\peaton.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen rampa
	images_array[index_array] = paths_images(0.81);
	images_array[index_array].Name = "Se�al de rampa";
	images_array[index_array].priority = 0;
	images_array[index_array].addString("openCV\\RA2.jpg");
	images_array[index_array].addString("openCV\\NRP1.jpg");
	images_array[index_array].addString("openCV\\NRP2.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen bici
	images_array[index_array] = paths_images(0.6);
	images_array[index_array].Name = "Se�al de Bici";
	images_array[index_array].priority = 1;
	images_array[index_array].addString("openCV\\BI1.jpg");
	images_array[index_array].addString("openCV\\BISIN1.jpg");
	images_array[index_array].addString("openCV\\NBIT1.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen cedaelpaso
	images_array[index_array] = paths_images(0.79);
	images_array[index_array].Name = "Se�al de Ceda el Paso";
	images_array[index_array].addString("openCV\\cedaelpaso.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen izq
	images_array[index_array] = paths_images(0.65);
	images_array[index_array].Name = "Se�al de Vuelta a la Izq";
	images_array[index_array].addString("openCV\\izq.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen semaforo
	images_array[index_array] = paths_images(0.8);
	images_array[index_array].Name = "Se�al de Semaforo";
	//images_array[index_array].addString("C:\\Users\\edgar\\Pictures\\openCV\\m.jpg");
	images_array[index_array].addString("openCV\\SComplejo.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen uturn
	images_array[index_array] = paths_images(0.75);
	images_array[index_array].Name = "Se�al de Uturn";
	images_array[index_array].addString("openCV\\U1.jpg");
	index_array++;

	//initialize the class for all the images and Paths
	//Imagen der
	images_array[index_array] = paths_images(0.7);
	images_array[index_array].Name = "Se�al de vuelta der";
	images_array[index_array].addString("openCV\\der.jpg");
	

	///Open the video
	VideoCapture cap("VID_20160604_141531.avi");
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);     
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240); 
	if (!cap.isOpened())
		return -1;     

	/// Create windows
	namedWindow(image_window, CV_WINDOW_AUTOSIZE);
#ifdef DEBUG
	namedWindow(temp_window, CV_WINDOW_AUTOSIZE);
#endif
	while (true){
		cap >> img;
		if (!img.data)
			continue;

		MatchingMethod(0, 0);

		MatchingMethod_priority(0, 0);

		int key = waitKey(1) & 0xFF;
		if (key == 'q')
			break;
		if (_debug){
			if (key == 'm'){
				while (true){
					int key = waitKey(5) & 0xFF;
					if (key == 'q')
						break;

					if (key == '5')
					{
						printf("Missing 50 km \n");
						break;
					}
					if (key == 'n')
					{
						printf("Missing no-parking \n");
						break;
					}
					if (key == 's')
					{
						printf("Missing semaforo \n");
						break;
					}
					if (key == 'f')
					{
						printf("Missing fotoinfraccion \n");
						break;
					}
					if (key == 'p')
					{
						printf("Missing parada \n");
						break;
					}
					if (key == 'c')
					{
						printf("Missing peaton \n");
						break;
					}
					if (key == 'r')
					{
						printf("Missing rampa \n");
						break;
					}
					if (key == 'u')
					{
						printf("Missing uvuelta \n");
						break;
					}
					if (key == 'b')
					{
						printf("Missing bici \n");
						break;
					}
				}
			}
		}
	}
	
	return 0;
}
/**
* @function MatchingMethod
* @brief Trackbar callback
*/
void MatchingMethod(int, void*)
{
	Mat img_display;
	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	
	MatND hist_cropImage;
	MatND hist_template;

	/// Source image to display
	img.copyTo(img_display);

	if (index > (sizeof(images_array) / sizeof(paths_images)) - 1)
		index = 0;

	//for (int index = 0; index < (sizeof(images_array) / sizeof(paths_images)) - 1; index++){
		//Here is where we need to add the for in each template
		for (int ind = 0; ind < images_array[index].Size(); ind++){
			//Add the template
			templ = images_array[index].CompareFiles[ind];
			hist_template = images_array[index].hist_template[ind];

			/// Create the result matrix
			int result_cols = img.cols - templ.cols + 1;
			int result_rows = img.rows - templ.rows + 1;
			result.create(result_rows, result_cols, CV_32FC1);

			/// Do the Matching and Normalize
			matchTemplate(img, templ, result, match_method);
			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
			minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

			/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. Forall the other methods, the higher the better
			if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
			{
				matchLoc = minLoc;
			}
			else
			{
				matchLoc = maxLoc;
			}

			if (matchLoc.x > img_display.cols || matchLoc.y > img_display.rows)
				//continue;
				return;

			Mat subImage(img_display, Rect(matchLoc.x, matchLoc.y, templ.cols, templ.rows));
			if (_debug){
				imshow(temp_window, subImage);
			}
			calcHist(&subImage, 1, channels, Mat(), hist_cropImage, 2, histSize, ranges, true, false);
			normalize(hist_cropImage, hist_cropImage, 0, 1, NORM_MINMAX, -1, Mat());
			double porcentaje = compareHist(hist_cropImage, hist_template, 0);
			if (porcentaje > images_array[index].porcentange)
			{
				rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
				//rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
				string deb = "Detected Image:" + images_array[index].Name;
				if (!_debug){
					deb += "\n";
				}
				putText(img_display, deb, Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2);
				printf(deb.c_str());
				if (_debug){
					printf("----- Value: %f ", porcentaje);
					imshow(image_window, img_display);
					while (true){
						int key = waitKey(5) & 0xFF;
						if (key == 'g')
						{
							printf("-----(GOOD) \n");
							break;
						}
						if (key == 'b')
						{
							printf("-----(BAD) \n");
							break;
						}
					}
				}
			}
		}
	//}
	imshow(image_window, img_display);
	index++;
	
	return;
}

/**
* @function MatchingMethod
* @brief Trackbar callback
*/
void MatchingMethod_priority(int, void*)
{
	Mat img_display;
	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	MatND hist_cropImage;
	MatND hist_template;

	/// Source image to display
	img.copyTo(img_display);

	//if (index > (sizeof(images_array) / sizeof(paths_images)) - 1)
	//	index = 0;

	for (int lindex = 0; lindex < (sizeof(images_array) / sizeof(paths_images)) - 1; lindex++){
		//Review if this template is high priority
		if (images_array[lindex].priority == 0)
			continue;
		//Here is where we need to add the for in each template
		for (int ind = 0; ind < images_array[lindex].Size(); ind++){
		//Add the template
			templ = images_array[lindex].CompareFiles[ind];
			hist_template = images_array[lindex].hist_template[ind];

			/// Create the result matrix
			int result_cols = img.cols - templ.cols + 1;
			int result_rows = img.rows - templ.rows + 1;
			result.create(result_rows, result_cols, CV_32FC1);

			/// Do the Matching and Normalize
			matchTemplate(img, templ, result, match_method);
			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
			minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

			/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. Forall the other methods, the higher the better
			if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
			{
				matchLoc = minLoc;
			}
			else
			{
				matchLoc = maxLoc;
			}

			if (matchLoc.x > img_display.cols || matchLoc.y > img_display.rows)
				//continue;
				return;

			Mat subImage(img_display, Rect(matchLoc.x, matchLoc.y, templ.cols, templ.rows));
			if (_debug){
				imshow(temp_window, subImage);
			}
			calcHist(&subImage, 1, channels, Mat(), hist_cropImage, 2, histSize, ranges, true, false);
			normalize(hist_cropImage, hist_cropImage, 0, 1, NORM_MINMAX, -1, Mat());
			double porcentaje = compareHist(hist_cropImage, hist_template, 0);

			if (porcentaje > images_array[lindex].porcentange){
				rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
				//rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
				string deb = "Detected in priority Image:" + images_array[lindex].Name;
				putText(img_display, deb, Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2);
				printf(deb.c_str());
				if (_debug){
					printf("----- Value: %f ", porcentaje);
					imshow(image_window, img_display);
					while (true){
						int key = waitKey(5) & 0xFF;
						if (key == 'g')
						{
							printf("-----(GOOD) \n");
							break;
						}
						if (key == 'b')
						{
							printf("-----(BAD) \n");
							break;
						}
					}
				}
			}
		}
	}
	imshow(image_window, img_display);
	//index++;

	return;
}


