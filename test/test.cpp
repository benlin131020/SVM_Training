// test.cpp: 定義主控台應用程式的進入點。
//
//branch1
#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
using namespace cv::ml;

void train64() {
	HOGDescriptor hog(Size(64, 64), Size(16, 16), Size(8, 8), Size(8, 8), 9);//HOG检测器，用来计算HOG描述子的

	std::vector<std::vector<float>> trainHOG;
	std::vector<int> trainLabels;
	std::string filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_FACE64\\train (";
	for (int i = 1; i <= 4000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(1);
		cout << "\rFACE64:" << i << "/4000" << flush;
	}
	cout << endl;
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_HEAD64\\train (";
	for (int i = 4001; i <= 8000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(1);
		cout << "\rHEAD64:" << i << "/8000" << flush;
	}
	cout << endl;
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\NEG_64\\train (";
	for (int i = 1; i <= 11843; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(0);
		cout << "\rNEG64:" << i << "/11843" << flush;
	}
	cout << endl;
	cv::Mat trainMat(trainHOG.size(), trainHOG[0].size(), CV_32FC1);
	int descriptor_size = trainHOG[0].size();
	for (int i = 0; i < trainHOG.size(); i++) {
		for (int j = 0; j < descriptor_size; j++) {
			trainMat.at<float>(i, j) = trainHOG[i][j];
		}
	}

	Ptr<SVM> svm = SVM::create();
	svm->setGamma(0.50625);
	svm->setC(12.5);
	svm->setKernel(SVM::RBF);
	svm->setType(SVM::C_SVC);
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
	svm->trainAuto(td);
	svm->save("svm64.yml");
}

void trainNT() {
	HOGDescriptor hog(Size(32, 32), Size(16, 16), Size(8, 8), Size(8, 8), 9);//HOG检测器，用来计算HOG描述子的

	std::vector<std::vector<float>> trainHOG;
	std::vector<int> trainLabels;
	std::string filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_FACE\\train (";
	for (int i = 1; i <= 4000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(1);
	}
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_HEAD\\train (";
	for (int i = 4001; i <= 8000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(1);
	}
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\NEG_32\\train (";
	for (int i = 1; i <= 11843; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(0);
	}

	cv::Mat trainMat(trainHOG.size(), trainHOG[0].size(), CV_32FC1);
	int descriptor_size = trainHOG[0].size();
	for (int i = 0; i<trainHOG.size(); i++) {
		for (int j = 0; j<descriptor_size; j++) {
			trainMat.at<float>(i, j) = trainHOG[i][j];
		}
	}

	Ptr<SVM> svm = SVM::create();
	svm->setGamma(0.50625);
	svm->setC(12.5);
	svm->setKernel(SVM::RBF);
	svm->setType(SVM::C_SVC);
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
	svm->trainAuto(td);
	svm->save("testNT.yml");
}

void trainN_T() {
	HOGDescriptor hog(Size(32, 32), Size(16, 16), Size(8, 8), Size(8, 8), 9);//HOG检测器，用来计算HOG描述子的

	std::vector<std::vector<float>> trainHOG;
	std::vector<int> trainLabels;
	std::string filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_N\\train (";
	for (int i = 1; i <= 8000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(1);
	}
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_T\\train (";
	for (int i = 1; i <= 8000; i += 1) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(2);
	}
	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\NEG_T\\train (";
	for (int i = 1; i <= 11843; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		trainHOG.push_back(descriptors);
		trainLabels.push_back(0);
	}

	cv::Mat trainMat(trainHOG.size(), trainHOG[0].size(), CV_32FC1);
	int descriptor_size = trainHOG[0].size();
	for (int i = 0; i<trainHOG.size(); i++) {
		for (int j = 0; j<descriptor_size; j++) {
			trainMat.at<float>(i, j) = trainHOG[i][j];
		}
	}

	Ptr<SVM> svm = SVM::create();
	svm->setGamma(0.50625);
	svm->setC(12.5);
	svm->setKernel(SVM::RBF);
	svm->setType(SVM::C_SVC);
	Ptr<TrainData> td = TrainData::create(trainMat, ROW_SAMPLE, trainLabels);
	svm->trainAuto(td);
	svm->save("testN_T.yml");
}

void test() {
	int success = 0;
	int fault = 0;
	int total = 8000;
	HOGDescriptor hog(Size(64, 64), Size(16, 16), Size(8, 8), Size(8, 8), 9);//HOG检测器，用来计算HOG描述子的
	cv::Ptr<cv::ml::SVM> svm = cv::Algorithm::load<cv::ml::SVM>("C:\\Users\\User\\Desktop\\影像\\test\\test\\svm64.yml");

	std::string filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_FACE64\\train (";
	for (int i = 8001; i <= 10000; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		if (svm->predict(descriptors) == 0)fault++;
		else success++;
	}

	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\POS_HEAD64\\train (";
	for (int i = 10001; i <= 12000; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		hog.compute(src, descriptors);
		if (svm->predict(descriptors) == 0)fault++;
		else success++;
	}

	filename = "C:\\Users\\User\\Desktop\\影像\\DataSet\\NEG_64Test\\train (";
	for (int i = 1; i <= 4000; i++) {
		cv::Mat src = cv::imread(filename + std::to_string(i) + ").jpg");
		std::vector<float> descriptors;
		cv::resize(src, src, cv::Size(64, 64));
		hog.compute(src, descriptors);
		if (svm->predict(descriptors) == 1)fault++;
		else success++;
	}

	cout << "total:" << total << "	success:" << success << "	fault:" << fault << endl;
	cout << "success rate:" << float(success) / float(total) << endl;
	
}

int main()
{
	/*
	int t;
	cout << "1:training 2.test: ";
	cin >> t;
	if (t == 1) {
		trainN_T();
		trainNT();
	}
	else {
		test();
	}
	*/

	//train64();
	test();
	cout << "sucess";

	/*Ptr<SVM> svm = Algorithm::load<SVM>("test1.yml");
	Mat test = imread("C:\\Users\\User\\Desktop\\test.jpg");
	resize(test, test, Size(64, 64));
	std::vector<float> descriptors;
	hog.compute(test, descriptors);
	float response = svm->predict(descriptors);
	if (response == 1)cout << "face" << endl;
	else cout << "non-face" << endl;*/
	
	waitKey(0);
	system("pause");
	return 0;
}