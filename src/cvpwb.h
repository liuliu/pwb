#ifndef _GUARD_cvpwb_h_
#define _GUARD_cvpwb_h_

#include <cv.h>
#include <gsl/gsl_qrng.h>

typedef struct {
	int size;
	int px[CV_SGF_POINT_MAX];
	int py[CV_SGF_POINT_MAX];
	int pz[CV_SGF_POINT_MAX];
	int nx[CV_SGF_POINT_MAX];
	int ny[CV_SGF_POINT_MAX];
	int nz[CV_SGF_POINT_MAX];
} CvSGFeature;

typedef struct {
	int count;
	CvSGFeature* feature;
	double* vector;
} CvPWBStageClassifier;

typedef struct {
	int count;
	CvSize size;
	CvPWBStageClassifier* stage_classifier;
} CvPWBClassifierCascade;

typedef struct {
} CvPWBKeypoint;

typedef struct {
	int layer;
	int feature_number;
} CvPWBTrainParams;

void cvCreatePWBClassifierCascade(char** files, int fnum);

#endif
