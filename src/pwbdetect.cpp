#include <cv.h>
#include <highgui.h>
#include <cstdio>

int main()
{
	CvCapture* capture = 0;
	IplImage *frame, *frame_copy = 0;
	IplImage *image = 0;

	capture = cvCreateCameraCapture( 0 );

	if( capture )
	{
		cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
		for(;;)
		{
			frame = cvQueryFrame( capture );
			if ( !frame )
				break;
			if ( !frame_copy )
				frame_copy = cvCreateImage( cvSize(frame->width, frame->height),
											IPL_DEPTH_8U, frame->nChannels );
			if ( !image )
				image = cvCreateImage( cvSize(320, 240), IPL_DEPTH_8U, frame->nChannels );

			if ( frame->origin == IPL_ORIGIN_TL )
				cvCopy( frame, frame_copy, 0 );
			else
				cvFlip( frame, frame_copy, 0 );
			cvResize( frame_copy, image, CV_INTER_AREA );

			cvShowImage("result", image);

			if( cvWaitKey( 10 ) >= 0 )
				goto _cleanup_;
		}
_cleanup_:
		cvReleaseImage( &image );
		cvReleaseImage( &frame_copy );
		cvReleaseCapture( &capture );
	}

	return 0;
}

