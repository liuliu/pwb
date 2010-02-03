#include <cv.h>
#include <highgui.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
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
	gsl_rng_env_setup();

	const gsl_rng_type* T = gsl_rng_default;
	gsl_rng* r = gsl_rng_alloc(T);
	gsl_rng_set(r, time(NULL));

	double sigma = 0.1 * ((image->width < image->height) ? image->width : image->height);

	CvPoint2D32f src[4], dst[4], rds[4];
	src[0].x = 0; src[0].y = 0;
	src[1].x = image->width; src[1].y = 0;
	src[2].x = image->width; src[2].y = image->height;
	src[3].x = 0; src[3].y = image->height;
	dst[0].x = -image->width / 2 + gsl_ran_gaussian(r, sigma); dst[0].y = -image->height / 2 + gsl_ran_gaussian(r, sigma);
	dst[1].x = image->width / 2 + gsl_ran_gaussian(r, sigma); dst[1].y = -image->height / 2 + gsl_ran_gaussian(r, sigma);
	dst[2].x = image->width / 2 + gsl_ran_gaussian(r, sigma); dst[2].y = image->height / 2 + gsl_ran_gaussian(r, sigma);
	dst[3].x = -image->width / 2 + gsl_ran_gaussian(r, sigma); dst[3].y = image->height / 2 + gsl_ran_gaussian(r, sigma);
	double radius = gsl_ran_gaussian(r, 3.1415926 / 8.0);
	double minx = 0, miny = 0, maxx = 0, maxy = 0;
	for (int i = 0; i < 4; i++)
	{
		rds[i].x = dst[i].x * cos(radius) - dst[i].y * sin(radius);
		rds[i].y = dst[i].x * sin(radius) + dst[i].y * cos(radius);
		if (rds[i].x < minx) minx = rds[i].x;
		if (rds[i].y < miny) miny = rds[i].y;
		if (rds[i].x > maxx) maxx = rds[i].x;
		if (rds[i].y > maxy) maxy = rds[i].y;
	}
	for (int i = 0; i < 4; i++)
	{
		rds[i].x -= minx;
		rds[i].y -= miny;
	}
	gsl_rng_free(r);
	float _m[9];
	CvMat m = cvMat(3, 3, CV_32FC1, _m);
	cvGetPerspectiveTransform(src, rds, &m);
	IplImage* transformed = cvCreateImage(cvSize(maxx - minx, maxy - miny), IPL_DEPTH_8U, 3);
	cvWarpPerspective(image, transformed, &m);
	cvShowImage("result", transformed);
	cvWaitKey(0);
	cvDestroyWindow("result");
	return 0;
}
