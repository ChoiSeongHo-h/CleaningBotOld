#include "serial.cpp"
#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <cmath>
#include <string>

#define _USE_MATH_DEFINES
#define Length 0.5
#include <math.h>

using namespace cv;
using namespace std;

Mat H;
//Mat src;
//Mat dst;
vector<Point2f> sceneP(4);
double go = Length;
double turn = 0;
int f_pt = 3;
int p_pt = 3;//받아올 이동방향 값
float x = 0;
float y = 0;
float o = 0;

int row = 7; 
int col = 8; //25
int stack[10000001], top = -1;
int arr[300][300] = { 0 };
int a = 2; //1
int b = 2; //1
int m = 0;  // 초음파 읽어오는 변수 0~7
int be = 0;  // 이전 진행방향
int r_p = 0;   // 이전 행
int c_p = 0;   // 이전 열

void push(int x) {
   stack[++top] = x;
   cout << "이전 진행방향 : " << x << "\n";
   ::be = x;
}

int empty() {
   if (top < 0)
      return 1;
   else return 0;
}

void pop() {
   if (empty() == 1)
      cout << "-1" << "\n";
   else {
      //cout << stack[top] << "\n";

      if (stack[top] == 1)    // 되돌아가는 방향으로 가기
      {
         a = a + 1;
      }
      else if (stack[top] == 2)
      {
         b = b - 1;
      }
      else if (stack[top] == 3)
      {
         b = b + 1;
      }
      else if (stack[top] == 4)
      {
         a = a - 1;
      }
      stack[top--] = 0;

   }
}

void remap(int x) {
   if (x == 1) {       // 위쪽
      if (m == 0) {   // o o o
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
      }
      else if (m == 1) {  // x o o
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
      }
      else if (m == 2) {  // o x o
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
      }
      else if (m == 3) {  // o o x
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
      }
      else if (m == 4) {  // x x o
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
      }
      else if (m == 5) {  // x o x
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
      }
      else if (m == 6) {  // o x x
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
      }
      else if (m == 7) {  // x x x
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
      }
   }
   else if (x == 2) {      // 오른쪽
      if (m == 0) {   // o o o
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
      }
      else if (m == 1) {  // x o o
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
      }
      else if (m == 2) {  // o x o
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
      }
      else if (m == 3) {  // o o x
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
      }
      else if (m == 4) {  // x x o
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
      }
      else if (m == 5) {  // x o x
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
      }
      else if (m == 6) {  // o x x
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
      }
      else if (m == 7) {  // x x x
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
      }
   }
   else if (x == 3) {      // 왼쪽
      if (m == 0) {   // o o o
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
      }
      else if (m == 1) {  // x o o
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
      }
      else if (m == 2) {  // o x o
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
      }
      else if (m == 3) {  // o o x
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
      }
      else if (m == 4) {  // x x o
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 0;
      }
      else if (m == 5) {  // x o x
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
      }
      else if (m == 6) {  // o x x
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
      }
      else if (m == 7) {  // x x x
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
         if (arr[a - 1][b] == 0 || arr[a - 1][b] == 7)
            arr[a - 1][b] = 7;
      }
   }
   else if (x == 4) {      // 아래
      if (m == 0) {   // o o o
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
      }
      else if (m == 1) {  // x o o
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
      }
      else if (m == 2) {  // o x o
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
      }
      else if (m == 3) {  // o o x
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
      }
      else if (m == 4) {  // x x o
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 0;
      }
      else if (m == 5) {  // x o x
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 0;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
      }
      else if (m == 6) {  // o x x
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 0;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
      }
      else if (m == 7) {  // x x x
         if (arr[a][b + 1] == 0 || arr[a][b + 1] == 7)
            arr[a][b + 1] = 7;
         if (arr[a + 1][b] == 0 || arr[a + 1][b] == 7)
            arr[a + 1][b] = 7;
         if (arr[a][b - 1] == 0 || arr[a][b - 1] == 7)
            arr[a][b - 1] = 7;
      }
   }
}

//이미지 회전 변환 함수
void rotate(Mat& srcImage1, int p_pt)
{
   Point2f pt(srcImage1.cols / 2., srcImage1.rows / 2.);

   if (p_pt == 1)  //절대좌표 상 직진
      return;
   else if (p_pt == 2)  //절대좌표 상 오른쪽으로 회전
   {
      Mat r = getRotationMatrix2D(pt, -90, 1.0);
      warpAffine(srcImage1, srcImage1, r, Size(srcImage1.cols, srcImage1.rows));
   }
   else if (p_pt == 3)  //절대좌표 상 왼쪽으로 회전
   {
      Mat r = getRotationMatrix2D(pt, 90, 1.0);
      warpAffine(srcImage1, srcImage1, r, Size(srcImage1.cols, srcImage1.rows));
   }
   else  //절대좌표 상 후진
   {
      Mat r = getRotationMatrix2D(pt, 180, 1.0);
      warpAffine(srcImage1, srcImage1, r, Size(srcImage1.cols, srcImage1.rows));
   }
}

//이미지 매칭 함수
int Image_Matching(Mat& srcImage1, Mat& srcImage2)
{
   //Step 1, 2 : detect the keypoints & descriptors
   vector<KeyPoint> keypoints1, keypoints2;
   Mat descriptors1, descriptors2;


   //방법2::BRISK
   Ptr<BRISK> briskF = BRISK::create();
   briskF->detectAndCompute(srcImage1, noArray(), keypoints1, descriptors1);
   briskF->detectAndCompute(srcImage2, noArray(), keypoints2, descriptors2);

   //Step 3 : Matching descriptor vectors
   vector<DMatch> matches;
   BFMatcher matcher(NORM_HAMMING);
   matcher.match(descriptors1, descriptors2, matches);

   if (matches.size() < 4)
   {
      cout << "err1" << endl;
      return 0;
   }

   //find goodMatches such that matches[i].distance <= 4 * minDist
   double minDist, maxDist;
   minDist = maxDist = matches[0].distance;
   for (int i = 1; i < matches.size(); i++)
   {
      double dist = matches[i].distance;
      if (dist < minDist) minDist = dist;
      if (dist > maxDist) maxDist = dist;
   }

   vector<DMatch>goodMatches;
   double fTh = 5 * minDist;
   for (int i = 0; i < matches.size(); i++)
   {
      if (matches[i].distance <= max(fTh, 0.02))
         goodMatches.push_back(matches[i]);
   }

   if (goodMatches.size() < 3)
   {
      cout << "err2" << endl;
      return 0;
   }

   //find Homography between keypoints1 and keypoints2
   vector<Point2f>obj;
   vector<Point2f>scene;
   for (int i = 0; i < goodMatches.size(); i++)
   {
      //Get the keypoints from the good matches
      obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
      scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
   }

   H = findHomography(obj, scene, RANSAC);

   vector<Point2f>objP(4);
   objP[0] = Point2f(0, 0);
   objP[1] = Point2f(srcImage1.cols, 0);
   objP[2] = Point2f(srcImage1.cols, srcImage1.rows);
   objP[3] = Point2f(0, srcImage1.rows);

   //vector<Point2f> sceneP(4);
   perspectiveTransform(objP, sceneP, H);

   for (int i = 0; i < 4; i++)
      line(srcImage2, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);
}

//이미지 매칭 오류 확인 위한 cos값 확인 함수
float H_matrix_cos(Mat H)
{
   double n1_x, n2_x, n1_y, n2_y;

   n1_x = H.at<double>(0, 0);
   n1_y = H.at<double>(0, 1);
   n2_x = H.at<double>(1, 0);
   n2_y = H.at<double>(1, 1);

   float cs = ((n1_x * n2_x) + (n1_y * n2_y)) / (sqrt(pow(n1_x, 2) + pow(n1_y, 2)) * sqrt(pow(n2_x, 2) + pow(n2_y, 2)));

   cout << "\n\ncos= " << cs << "\n" << endl;
   cout << "H_ex =  " << H << endl;

   return cs;
}

//배율 조절 함수
void scale_control(Mat H)
{
   double c_rad, s_rad, a;

   c_rad = (H.at<double>(0, 0) + H.at<double>(1, 1)) / 2;
   s_rad = (H.at<double>(0, 1) + (-(H.at<double>(1, 0)))) / 2;
   a = sqrt(pow(c_rad, 2) + pow(s_rad, 2));

   cout << "\na= " << a << endl;

   H = H / a;

   for (int i = 0; i < 2; i++)
   {
      for (int j = 0; j < 2; j++)
      {
         if (H.at<double>(i, j) > 1)
            H.at<double>(i, j) = 0.9999;
         else if (H.at<double>(i, j) < -1)
            H.at<double>(i, j) = -0.9999;
      }
   }

   cout << "\nH_re = " << H << endl;
}

/*
//X_err값 함수
float get_x(vector<Point2f>& sceneP) //x 이동거리 구하기 함수
{
   return (160 - (sceneP.at(0).x + sceneP.at(1).x + sceneP.at(2).x + sceneP.at(3).x) / 4) / 45 * 0.225;   //160 -> w/2, 45 -> px, 0.225 -> m
}

//Y_err값 함수
float get_y(vector<Point2f>& sceneP) //y 이동거리 구하기 함수
{
   return ((sceneP.at(0).y + sceneP.at(1).y + sceneP.at(2).y + sceneP.at(3).y) / 4 - 120) / 45 * 0.225;   //160 -> w/2, 45 -> px, 0.225 -> m
}

//O_err값 함수
double get_o(Mat H)
{
   double c_rad, s_rad, rad;

   c_rad = (acos(H.at<double>(0, 0)) + acos(H.at<double>(1, 1))) / 2;
   s_rad = (asin(H.at<double>(0, 1)) + asin(-(H.at<double>(1, 0)))) / 2;

   //cos, sin값 부호에 따른 범위 -PI ~ PI 값으로 설정
   if (0 <= H.at<double>(0, 1) && 0 <= H.at<double>(0, 0)) //1사분면::0 ~ PI/2
      ;
   else if (0 <= H.at<double>(0, 1) && H.at<double>(0, 0) < 0) //2사분면::PI/2 ~ PI
      s_rad = M_PI - s_rad;

   else if (H.at<double>(0, 1) < 0 && 0 <= H.at<double>(0, 0)) //4사분면::-PI/2 ~ 0
      c_rad = -c_rad;

   else  //3사분면::-PI ~ -PI/2
   {
      s_rad = -M_PI - s_rad;
      c_rad = -c_rad;
   }

   rad = (c_rad + s_rad) / 2;

   cout << "\nc_rad= " << c_rad << ", " << "s_rad= " << s_rad << endl;
   cout << "rad= " << rad << "\n" << endl;

   return rad;
}
*/
//이동방향에 따른 회전 및 기준좌표 set함수
void p_err(double* x, double* y, double* o) {
   double tmp;

   if (f_pt == p_pt) //직진
      return;
   else if ((f_pt == 1 && p_pt == 2) || (f_pt == 2 && p_pt == 4) || (f_pt == 4 && p_pt == 3) || (f_pt == 3 && p_pt == 1)) //오른쪽 회전
   {
      *o += M_PI / 2;
      tmp = *x;
      *x = -(*y);
      *y = tmp;
   }
   else if ((f_pt == 1 && p_pt == 4) || (f_pt == 2 && p_pt == 3) || (f_pt == 4 && p_pt == 1) || (f_pt == 3 && p_pt == 2)) //후진
   {
      *o += M_PI;
      *x = -(*x);
      *y = -(*y);
   }
   else //왼쪽 회전
   {
      *o -= M_PI / 2;
      tmp = -(*x);
      *x = *y;
      *y = tmp;
   }


   // +-180도 사이에서 회전하도록 함
   if ((float)*o > (float)M_PI)
      *o -= (2 * M_PI);
   else if ((float)*o < (float)(-M_PI))
      *o += 2 * M_PI;

}

//로봇의 이동 및 회전 명령 함수
void err(double x, double y, double o) {   // x, y 각각의 오차는 += Length 보다 작을 경우로 가정
   ::turn = 0;

   // 로봇 청소기가 뒤쪽을 향하면 앞을 향하도록 회전
   if ((float)(o < -(M_PI / 2)) || (float)(o > M_PI / 2)) {
      ::turn += M_PI;
      if (o > -(M_PI / 2)) o -= M_PI;
      else o += M_PI;
   }

   // 현재 로봇의 위치를, y축을 기준으로 분류
   if (x > 0) {            // 오른쪽으로 잘못 이동한 경우
      if ((float)o == (float)(M_PI / 2 - atan((Length - y) / x)))
         ::turn += 0;
      else if ((float)o > (float)(M_PI / 2 - atan((Length - y) / x)))
         ::turn -= (o - atan(x / (Length - y)));
      else {
         if (o >= 0)
            ::turn += (M_PI / 2 - atan((Length - y) / x) - o);
         else
            ::turn -= (o - atan(x / (Length - y)));
      }
   }

   else if (x < 0) {         // 왼쪽으로 잘못 이동한 경우
      if ((float)(M_PI / 2 + o) == (float)(atan((Length - y) / abs(x))))
         ::turn += 0;
      else if ((float)(M_PI / 2 + o) == (float)(atan((Length - y) / abs(x))))
         ::turn -= (o - atan(x / (Length - y)));
      else {
         if (o <= 0)
            ::turn -= (M_PI / 2 + atan((Length - y) / x) + o);
         else
            ::turn -= (o - atan(x / (Length - y)));
      }
   }

   else {      // 수직으로만 잘못 이동한 경우
      ::turn -= o;
   }

   // +-180도 사이에서 회전하도록 함
   if ((float)::turn > (float)M_PI)
      ::turn -= (2 * M_PI);
   else if ((float)::turn < (float)(-M_PI))
      ::turn += 2 * M_PI;

   ::go = sqrt(x * x + (Length - y) * (Length - y));

   cout << "turn : " << ::turn << " , go  : " << ::go << endl;

}


int main(int argc,char** argv){
	using namespace std;
	Serial arduino("/dev/ttyACM0",9600);
	char buf[1];
	memset(buf,1,0);
	char input;
	int mode = 0;
   
   
        Mat src;// = imread(path2, IMREAD_GRAYSCALE);
        VideoCapture cap(0, CAP_DSHOW);
        cap.open(0);
        cap.set(CAP_PROP_FRAME_WIDTH, 320);
        cap.set(CAP_PROP_FRAME_HEIGHT, 240);
   ////////////////////////벽 설정//////////////////////

   //가장자리 벽
   for (int r = 0; r < 8; r++)
   {
      arr[r][0] = 9;
      arr[r][6] = 9;
   }

   for (int c = 0; c < 7; c++)
   {
      arr[0][c] = 9;
      arr[7][c] = 9;
   }
   
   //테이블
   for (int wall_r = 3; wall_r < 7; wall_r++)
   {
      for (int wall_c = 1; wall_c < 5; wall_c++)
         arr[wall_r][wall_c] = 9;
   }

   //초기위치
   arr[1][1] = 1;

   // 벽 출력
   for (int i = 0; i < row; i++)
   {
      for (int j = 0; j < col; j++)
      {
         std::cout << "  " << arr[i][j];
      }
      std::cout << "\n";
   }
   std::cout << "\n\n\n";



   //////////////////////////////////////////////////// arr[1][1] 부터 청소시작

   int x = 0;
   int count = 0;
   
   
   
   
   
	while(m % 9 != 8){
		cout<<"Pls type alpha : ";
		switch(mode)
		{
			case 0:
      {
                  r_p = a;
      c_p = b;

      cout << "초음파가 인식된 번호를 써주세요 0 ~ 7 (x : 벽, o : 빈 곳)" << "\n";
      cout << "o o o : 0,     x o o : 1,     o x o : 2,     o o x : 3" << "\n";
      cout << "x x o : 4,     x o x : 5,     o x x : 6,     x x x : 7" << "\n";

      cin >> m;          // 초음파 스캔
      

         //while(!arduino.sread(buf,sizeof(char))){}
         //cout<<"ok : "<<buf[0]<<endl;
         //m = buf[0];
      
      count++;
      
      //////////////////////////////////////////////////////////////////////  알고리즘

      if (arr[a][b + 1] == 0 || arr[a][b - 1] == 0 || arr[a + 1][b] == 0 || arr[a - 1][b] == 0) // 0이 하나라도 있는경우
      {

         if (arr[a - 1][b] == 0) // 위쪽
         {
            remap(1);

            a = a - 1;
            push(1);

         }
         else if (arr[a][b + 1] == 0)    // 오른쪽
         {
            remap(2);

            b = b + 1;
            push(2);
         }
         else if (arr[a][b - 1] == 0)    // 왼쪽
         {
            remap(3);

            b = b - 1;
            push(3);
         }
         else if (arr[a + 1][b] == 0)    // 아래쪽
         {
            remap(4);

            a = a + 1;
            push(4);
         }
      }
      else // 0이 하나도 없는경우
      {
         pop();
         cout << "뒤로가기" << "\n";
      }


      if (arr[a][b] < 7) {
         arr[a][b] += 1;
      }
      else {
         pop();
      }

      /////////////////////////////////////////////////////////////////////

      //다음에 갈 방향 예측하기

      if (arr[a][b + 1] == 0 || arr[a][b - 1] == 0 || arr[a + 1][b] == 0 || arr[a - 1][b] == 0) // 0이 하나라도 있는경우
      {

         if (arr[a - 1][b] == 0) // 위쪽
         {
            if (be == 2)
               cout << "좌회전" << "\n";

            else if (be == 3)
               cout << "우회전" << "\n";

            else if (be == 4)
               cout << "180도 턴" << "\n";

            a = a - 1;
            cout << "위쪽보기" << "\n";
            a = a + 1;

         }
         else if (arr[a][b + 1] == 0)    // 오른쪽
         {
            if (be == 4)
               cout << "좌회전" << "\n";
            
            else if (be == 1)
               cout << "우회전" << "\n";
            
            else if (be == 3)
               cout << "180도 턴" << "\n";
            
            b = b + 1;
            cout << "오른쪽 보기" << "\n";
            b = b - 1;
         }
         else if (arr[a][b - 1] == 0)    // 왼쪽
         {
            if (be == 1) 
               cout << "좌회전" << "\n";
            
            else if (be == 4) 
               cout << "우회전" << "\n";
            
            else if (be == 2) 
               cout << "180도 턴" << "\n";

            b = b - 1;
            cout << "왼쪽 보기" << "\n";
            b = b + 1;
         }
         else if (arr[a + 1][b] == 0)    // 아래쪽
         {
            if (be == 3)
               cout << "좌회전" << "\n";
         
            else if (be == 2) 
               cout << "우회전" << "\n";
            
            else if (be == 1) 
               cout << "180도 턴" << "\n";

            a = a + 1;
            cout << "아래쪽 보기" << "\n";
            a = a - 1;
         }
      }


      ////////////////////////////////////////////////////////////////////////

      for (int i = 0; i < row; i++)   // 벽 출력 - 한번씩 확인할 수 있습니다
      {
         for (int j = 0; j < col; j++)
         {
            cout << arr[i][j];
         }
         cout << "\n";
      }
      cout << "이전위치 : " << r_p << " " << c_p << "\n";
      cout << "현재위치 : " << a << " " << b << " " << "\n" << "반복횟수 : " << count << "\n";

      int i = 0;
      int j = 0;
      int p = 0;

      for (i = 0; i < row; i++)   // 청소확인
      {
         for (j = 0; j < col; j++)
         {
            if (arr[i][j] == 0)
            {
               p++;
            }
         }
      }
      if (arr[a][b + 1] != 0 && arr[a][b - 1] != 0 && arr[a + 1][b] != 0 && arr[a - 1][b] != 0) // 0이 하나도 없는경우
      {
         double h = double(p) / (row * col) * 100;
         if (h < 1)
         {
            for (int i = 0; i < row; i++)   // 벽 출력
            {
               for (int j = 0; j < col; j++)
               {
                  cout << "" << arr[i][j];
               }
               cout << "\n";
            }
            cout << a << " " << b << " " << "\n" << "이동횟수 : " << count << "\n"; //////

            cout << "청소완료 !!!!!\n" << "청소안한 구간 개수 : " << p << "    청소율 : " << 100 - h << "%\n";
            break;
         }
      }

      /////////////////////////////////////////////////////////////////////////////////////////////[영상처리]
        /*
      string path1 = to_string(::r_p) + "-" + to_string(::c_p) + ".jpg";
      Mat srcImage1 = imread(path1, IMREAD_GRAYSCALE); //input 이미지
      rotate(srcImage1, be);

      string path2 = to_string(r_p) + "_" + to_string(c_p) + ".jpg";
      Mat srcImage2 = imread(path2, IMREAD_GRAYSCALE);;
      /*
      Mat frame;

      VideoCapture cap(1);

      if (!cap.isOpened())
         cerr << "카메라를 열 수 없습니다." << endl;

       cap.read(frame);

       if (frame.empty())
         cerr << "캡쳐 실패" << endl;

       Mat srcImage2;
       cvtColor(frame, srcImage2, COLOR_BGR2GRAY);
      

      if (srcImage1.empty() || srcImage2.empty())  //이미지 로드 확인
      {
         cerr << "이미지 로드 실패!" << endl;
         return -1;
      }

      Image_Matching(srcImage1, srcImage2);  //이미지 매칭

      float cos = H_matrix_cos(H);  //이미지 매칭 오류 확인

      scale_control(H);  //이미지 배율 조절
      */



        if (!cap.isOpened())
        {
            cerr << "카메라를 열 수 없습니다." << endl;
            return -1;
        }
        Mat abc;
        cap.read(src);
        abc = src.clone();
        cvtColor(src, src, COLOR_BGR2GRAY);
        threshold(src, src, 70, 0, THRESH_TRUNC);

      
      GaussianBlur(src, src, Size(7, 7), 0);
      adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
      medianBlur(src, src, 9);
      src = ~src(Rect(110, 70, 100, 100));


      vector<vector<Point>> contours;
      findContours(src, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

      int max_size = -1;
      int max_i = -1;
      for (int i = 0; i < contours.size(); i++)
      {
         if (int(contours[i].size()) > max_size)
         {
            max_size = contours[i].size();
            max_i = i;
         }
      }

      Mat dst;
      cvtColor(src, dst, COLOR_GRAY2BGR);

      vector<Point2f> triangle;
      minEnclosingTriangle(contours[max_i], triangle);
      for (int i = 0; i < 3; i++)
      {
         line(dst, triangle[i], triangle[(i + 1) % 3], Scalar(0, 255, 0), 2);
      }

      float center_x = (triangle[0].x + triangle[1].x + triangle[2].x) / 3;
      float center_y = (triangle[0].y + triangle[1].y + triangle[2].y) / 3;

      int min_len = 2100000000;
      int min_i = -1;
      for (int i = 0; i < 3; i++)
      {
         int len = pow((triangle[i].x - triangle[(i + 1) % 3].x), 2) + pow((triangle[i].y - triangle[(i + 1) % 3].y), 2);
         if (len < min_len)
         {
            min_len = len;
            min_i = (i + 2) % 3;
         }
      }

      float rad = 0;
      if (triangle[min_i].x > center_x)               //1, 4 q
         rad = (-CV_PI / 2 - atan((triangle[min_i].y - center_y) / (triangle[min_i].x - center_x)));
      else if ((triangle[min_i].x == center_x) && (center_y > triangle[min_i].y))   //90
         rad = 0;
      else if ((triangle[min_i].x == center_x) && (center_y < triangle[min_i].y))   //-90
         rad = CV_PI;
      else if (center_y > triangle[min_i].y)            //2 q
         rad = (CV_PI / 2 - atan((triangle[min_i].y - center_y) / (triangle[min_i].x - center_x)));
      else if (center_y < triangle[min_i].y)            // 3 q
         rad = (CV_PI / 2 - atan((triangle[min_i].y - center_y) / (triangle[min_i].x - center_x)));

      cout << center_x - 160 << ", " << 120 - center_y << endl;
      cout << rad * 180 / CV_PI << endl;

      x = (center_x - 50) / 45 * 0.225;
      y = (50 - center_y) / 45 * 0.225;
      o = rad;

      if (0 <= o && o < M_PI / 2)
      {
         if (be == 1)
            ;
         else if (be == 2)
            o = o + M_PI / 2;
         else if (be == 3)
            o = o - M_PI / 2;
         else
            o = o - M_PI;
      }
      else if (M_PI / 2 <= o && o <= M_PI)
      {
         if (be == 1)
            ;
         else if (be == 2)
            o = o - M_PI / 2 * 3;
         else if (be == 3)
            o = o - M_PI / 2;
         else
            o = o - M_PI;
      }
      else if (-(M_PI / 2) <= o && o < 0)
      {
         if (be == 1)
            ;
         else if (be == 2)
            o = o + M_PI / 2;
         else if (be == 3)
            o = o - M_PI / 2;
         else
            o = o + M_PI;
      }
      else
      {
         if (be == 1)
            ;
         else if (be == 2)
            o = o + M_PI / 2;
         else if (be == 3)
            o = o + M_PI / 2 * 3;
         else
            o = o + M_PI;
      }


      double X = x;  //X_err값 로드
      double Y = y;  //Y_err값 로드
      double O = o;       //O_err값 로드

      ::f_pt = ::p_pt;
      ::p_pt = be;

      cout << "f_pt= " << f_pt << ", p_pt= " << p_pt << endl;
      /*
      if (abs(cos) > 0.35)  //이미지 매칭이 오류를 범할 시 오차조정값 0으로 초기화
      {
         X = 0;
         Y = 0;
         O = 0;
      }
      */
      cout << "\nX= " << X << ",  Y= " << Y << ",  O= " << O << endl;

      p_err(&X, &Y, &O);  //이동방향 고려 오차(x, y, o)조정
      err(X, Y, O);       //이동 및 회전 최종 조정

      cout << "\n---------------------------------------------------------------------- " << "\n" << endl;

      
      
      
      for (int i = 0; i < 3; i++)
      {
         line(abc, Point(triangle[i].x+110, triangle[i].y+70), Point(triangle[(i + 1) % 3].x+110, triangle[(i + 1) % 3].y+70), Scalar(0, 255, 0), 2);
      }
      imshow("result", abc);
      waitKey();




				input = int((turn+3.14)*127.5/3.14);
				cout<<int(input)<<endl;
				memset(buf,1,0);
				arduino.swrite(&input,sizeof(char));
            while(1)
            {
               while(!arduino.sread(buf,sizeof(char))){}
               cout<<"ok : "<<buf[0]<<endl;
               if(buf[0] == 'R')
               {
                  mode = 1;
                  break;
               }
            }
				
				break;
      }
			case 1:
         {
				//dist
				input = int(go*100);
				cout<<int(input)<<endl;
				memset(buf,1,0);
				arduino.swrite(&input,sizeof(char));
				while(!arduino.sread(buf,sizeof(char))){}
				cout<<"scan : "<<buf[0]<<endl;
				//renew();
				mode = 0;
            break;
         }
         default:
            break;
		}
	}
	return 0;
}


