//Yunus Polat
//24.05.2024
/*
Görüntü işleme projesinde  öncelikle bir ROI (İlgilenilen Bölge) belirledim ve 
bu bölgede kenar tespiti için Canny fonksiyonunu kullandım. Daha sonra, 
kenarları daha iyi belirlemek için genişletme işlemi uyguladım. Ardından, 
genişletilmiş kenarların konturunu tespit etmek için OpenCV'nin findContours fonksiyonunu kullandım.
Konturların en alt noktalarını bulup bu noktaların 20 piksel üstlerine iki adet nokta koyarak,
bu noktalar arasına bir çizgi çizdim. Noktalar mesafeyi hesaplayarak, bu mesafeyi çizgiye putText fonksiyonu yardımıyla yazdırdım ve 
programın toplam çalışma süresini hesapladım. Kısacası bu program bir gripper tarafınfan tutulan kapasitörün
bacakları arasındaki mesafeyi px cinsinden ölçmektedir.  
 */

#include <opencv2/opencv.hpp>
#include <cmath>
#include <chrono> 

using namespace cv;
using namespace std;

/*ROI görüntüsünde kenar tespiti ve genişletme işlemleri uygulayarak,
 belirli bir bölgenin kenarlarını belirler.*/
void convert_operations(Mat& roiImage, Mat& dilatedEdges) {
    Mat edges;
    Canny(roiImage, edges, 10, 150);
    dilate(edges, dilatedEdges, Mat(), Point(-1, -1), 2);
}

/*genişletilmiş kenar görüntüsünden şekillerin sınırlarını bulmak için kullanılır,
 findContours fonksiyonu aracılığıyla konturları tespit eder.*/
void find_Contours(Mat& dilatedEdges, vector<vector<Point>>& contours, vector<Vec4i>& hierarchy) {
    
    findContours(dilatedEdges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}

/*konturların alt noktalarına daireler çizerek, bu daireler arasındaki farkları hesaplar ve 
 görüntü üzerine yazı ekler; ayrıca, kontur alanı belirli bir eşik değerinden küçükse işlem yapmaz.*/
void drawCirclesAndComputeDifferences(const vector<vector<Point>>& contours, Mat& roiImage) {
   
    vector<int> xCoordinates;

    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        
        Point bottomMost = *max_element(contours[i].begin(), contours[i].end(), 
            [](const Point& a, const Point& b) {
                return a.y < b.y;
            });

        int x = bottomMost.x;
        int y = bottomMost.y - 20;//20 px üstünden işlem yapılıyor.
        
        xCoordinates.push_back(x);

        circle(roiImage, Point(x, y), 2, Scalar(0, 0, 255), -1);

        if (i > 0) {//İlk daire oluştuktan sonra diğer daireye uzaklık ölçümü 
            int prevX = xCoordinates[i - 1];
            line(roiImage, Point(prevX, y), Point(x, y), Scalar(255, 0, 0), 2);

            int diff = xCoordinates[i] - xCoordinates[i - 1];//x koordinatındaki fark hesaplanıyor ve uzaklık bulunuyor.
            string diffStr = to_string(-diff) + " px";
            putText(roiImage, diffStr, Point((prevX + x) / 2, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0 , 255), 2);
        }
    }
}

int main() {
   
    auto start_time = chrono::system_clock::now();
    Mat image = imread("IP1_Cap.jpg");

    Rect roi(0, 480, 1600, 200);
    Mat roiImage = image(roi);


    Mat dilatedEdges;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    
    convert_operations(roiImage, dilatedEdges);
    find_Contours(dilatedEdges, contours, hierarchy);
    drawCirclesAndComputeDifferences(contours, roiImage);

    //auto end_time = chrono::system_clock::now();
   
    imshow("Result", roiImage);
    
    auto end_time = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    cout << "Toplam çalışma süresi: " << elapsed_seconds.count()*1000 << " ms\n";
    
    waitKey(0);
    
    
    return 0;
}
