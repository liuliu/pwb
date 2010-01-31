#include <cv.h>
#include <highgui.h>
#include <gsl/gsl_qrng.h>

int main(int argc, char** argv)
{
	gsl_qrng* q = gsl_qrng_alloc(gsl_qrng_halton, 2);
	IplImage* image = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
	for (int i = 0; i < 64; i++)
	{
		double v[2];
		gsl_qrng_get(q, v);
		int x = (int)(v[0] * 319), y = (int)(v[1] * 239);
		image->imageData[x * 3 + y * image->widthStep] = image->imageData[x * 3 + 1 + y * image->widthStep] = image->imageData[x * 3 + 2 + y * image->widthStep] = 255;
	}
	cvShowImage("result", image);
	cvWaitKey(0);
	gsl_qrng_free(q);
	cvDestroyWindow("result");
	return 0;
}
