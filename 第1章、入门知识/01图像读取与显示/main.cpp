#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);

	// ����1 ͼƬ·��
	// ����2 ɫ�ʱ�־��Ĭ��Ϊ1������ɫͼ��
	// IMREAD_COLOR    ��ɫͼ��
	// IMREAD_GRAYSCALE �Ҷ�ͼ
	// IMREAD_UNCHANGED ͸��ͨ
	Mat src = imread("image.jpg", IMREAD_COLOR);

	if (src.empty()) {
		printf("could not load image����\n");
		return -1;
	}

	namedWindow("���봰��", WINDOW_FREERATIO);

	// ����1 ��������
	// ����2 �������
	imshow("���봰��", src);

	//����1 �ȴ�ʱ�䣨ms���涨0Ϊ��Զ
	waitKey(0);

	// �������д���
	destroyAllWindows();

	return 0;
}
