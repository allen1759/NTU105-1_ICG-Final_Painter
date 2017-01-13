#include <iostream>
#include <cstdlib>
#include <ctime>
#include <opencv2/opencv.hpp>
#include "GA.h"

int main()
{
	srand(time(NULL));

	GA mona;
	if (!mona.initial("ml.jpg")) return 1;
	mona.Start();

	cvWaitKey(0);

	return 0;
}
