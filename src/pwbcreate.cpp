#include <cv.h>
#include <highgui.h>
#include <gsl/gsl_qrng.h>

int main(int argc, char** argv)
{
	IplImage* image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR); // cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
/*
	gsl_qrng* q = gsl_qrng_alloc(gsl_qrng_halton, 2);
	for (int i = 0; i < 64; i++)
	{
		double v[2];
		gsl_qrng_get(q, v);
		int x = (int)(v[0] * 319), y = (int)(v[1] * 239);
		image->imageData[x * 3 + y * image->widthStep] = image->imageData[x * 3 + 1 + y * image->widthStep] = image->imageData[x * 3 + 2 + y * image->widthStep] = 255;
	}
	gsl_qrng_free(q);
*/
	CvPoint2D32f src[4], dst[4];
	src[0].x = 0; src[0].y = 0;
	src[1].x = image->width; src[1].y = 0;
	src[2].x = image->width; src[2].y = image->height;
	src[3].x = 0; src[3].y = image->height;
	dst[0].x = -20; dst[0].y = -20;
	dst[1].x = image->width; dst[1].y = 0;
	dst[2].x = image->width; dst[2].y = image->height;
	dst[3].x = 0; dst[3].y = image->height;
	float _m[9];
	CvMat m = cvMat(3, 3, CV_32FC1, _m);
	cvGetPerspectiveTransform(src, dst, &m);
	IplImage* transformed = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvWarpPerspective(image, transformed, &m);
	cvShowImage("result", transformed);
	cvWaitKey(0);
	cvDestroyWindow("result");
	return 0;
}
