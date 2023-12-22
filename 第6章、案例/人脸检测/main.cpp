#include <iostream>

#include <opencv2/core/utils/logger.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace dnn;
using namespace std;

int main(int argc, char const* argv[]) {
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);
	//�ļ���·��
	string pb_file_path = "./opencv_face_detector_uint8.pb";
	string pbtxt_file_path = "./opencv_face_detector.pbtxt";

	//��ȡ��TensorFlow��ܸ�ʽ�洢������ģ��
	Net net = readNetFromTensorflow(pb_file_path, pbtxt_file_path);

	if (net.empty()) {
		printf("could not load model����\n");
		return -1;
	}

	//������ͷ�����������
	VideoCapture capture(0);
	Mat frame;

	while (true) {
		capture.read(frame);//frameΪ�����read�ǽ����񵽵���Ƶһ֡һ֡�Ĵ���frame

		if (frame.empty()) {
			break;
		}

		flip(frame, frame, 1);//���ҷ�ת

		//׼�����ѧϰģ����Ҫ������ ��blob-�ߵ㣩
		Mat blob = blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);

		//�������
		Mat probs = net.forward();

		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//�������
		for (int i = 0; i < detectionMat.rows; i++) {
			float confidence = detectionMat.at<float>(i, 2);//������ֵ �÷�
			if (confidence > 0.5) {

				//��ΪԤ������ֵΪ[0,1]��Χ���������ǻ���Ҫ*ԭͼ��Ŀ�Ⱥͳ���
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}

		imshow("�������", frame);

		if (waitKey(1) == 27) {
			break;
		}
	}

	destroyAllWindows();

	return 0;
}
