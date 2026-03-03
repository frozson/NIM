
#include <nim.h>


int main()
{
	cv::Mat image = cv::imread(fullpath("sample assets/Frozson.jpg"), cv::IMREAD_COLOR);
	if (image.empty())
	{
		printf("Unable to read Image\n");
		return 1;
	}
	cv::Mat canny, dx, dy;
	cv::resize(image, image, { 400, 400 });
	//cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
	try
	{
		cv::Canny(image, canny, 0.5, 0.8);
		cv::imshow("canny", canny);
		cv::imshow("Image", image);

		printf("Press Any Key to exit\n");
		cv::waitKey(0);

		cv::destroyAllWindows();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	
	return 0;
}