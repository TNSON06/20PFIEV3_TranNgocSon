/*Thuật toán tham ăn (Greedy Algorithm) là một trong những kỹ thuật được sử dụng để giải quyết Bài toán du lịch (Travelling Salesman Problem). 
Ý tưởng của thuật toán này là chọn các thành phố theo thứ tự gần nhất với điểm xuất phát, sau đó chọn các thành phố còn lại với khoảng cách nhỏ nhất đến thành phố hiện tại.
*/
#include<iostream>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

const int maxn = 20;
const int INF = 0x3f3f3f3f;

int n, g[maxn][maxn], vis[maxn], ans = INF; // khởi tạo biến

/*Đây là khai báo và khởi tạo các biến cần thiết trong chương trình, bao gồm số lượng thành phố `n`, ma trận khoảng cách giữa các thành phố `g`, 
mảng `vis` để đánh dấu các thành phố đã được thăm, và biến `ans` để lưu chi phí đường đi ngắn nhất.*/

void Greedy_TSP(int st) {
    int dis = 0; // khởi tạo không đường đi
    vis[st] = 1; // đánh dấu thành phố đã được đi qua
    for (int i = 1; i < n; i++) {
        int nxt = -1, minDis = INF; // khởi tạo tìm đường đi ngắn nhất
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && g[st][j] < minDis) { // nếu chưa đi qua và có đường đi ngắn hơn
                nxt = j; // cập nhật thành phố tiếp theo
                minDis = g[st][j]; // cập nhật khoảng cách ngắn nhất
            }
        }
        if (nxt == -1) return; // nếu không thể đến thành phố kế tiếp thì kết thúc
        vis[nxt] = 1; // đánh dấu lại thành phố đã đi qua
        dis += minDis; // cộng vào chi phí đường đi
        st = nxt; // cập nhật thành phố hiện tại bằng thành phố tiếp theo
    }
    ans = min(ans, dis + g[st][1]); // lưu vào chi phí nhỏ nhất
}
/*Hàm `Greedy_TSP` chính là thuật toán tham ăn được áp dụng để giải quyết Bài toán du lịch. Thuật toán này tìm đường đi ngắn nhất giữa các 
thành phố bằng cách chọn các thành phố theo thứ tự gần nhất với thành phố hiện tại.
Việc tìm thành phố gần nhất được thực hiện trong vòng lặp bên trong vòng lặp chính, sử dụng câu lệnh `if` để kiểm tra thành phố đó đã được
 thăm trước đó chưa và xác định thành phố có khoảng cách nhỏ nhất đến thành phố hiện tại. Nếu không tìm được thành phố nào thỏa mãn, chương
  trình sẽ trả về.
Sau khi tìm được thành phố gần nhất, chúng ta đánh dấu thành phố đó đã được thăm, cộng vào chi phí đường đi (biến `dis`) và cập nhật lại thành 
phố hiện tại bằng thành phố mới tìm được.
Cuối cùng, các chi phí đường đi được lưu vào `ans`, hàm sẽ trả về giá trị của `ans`.*/
   void print_distance_matrix() {
    cout << "Ma tran khoang cach:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    cout << "Nhap vao so luong thanh pho: ";
    cin >> n;
    cout << "Nhap vao ma tran khoang cach: " << endl; 
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            int distance;
            cout<< "Khoang cach tu thanh pho " <<i<<" den thanh pho "<<j<<endl;
            cin >> distance;
            g[i][j] = distance;
            g[j][i] = distance;


        }
    }
    //chúng ta khởi tạo mảng `vis` bằng 0, và gọi hàm `Greedy_TSP` với thành phố đầu tiên là thành phố số 1
    memset(vis, 0, sizeof(vis)); // khởi tạo mảng vis bằng 0

      print_distance_matrix();
      // Lấy thời gian hiện tại
    auto start_time = high_resolution_clock::now();

    Greedy_TSP(1); // bắt đầu đi tìm
    
 // Lấy thời gian sau khi hàm đã thực hiện xong
    auto end_time = high_resolution_clock::now();

    // Tính thời gian đã trôi qua
     auto elapsed_time_ns = duration_cast<nanoseconds>(end_time - start_time);
    double elapsed_time_ms = elapsed_time_ns.count() / 1000000.0;


    // In ra thời gian đã trôi qua
     cout << std::fixed << std::setprecision(3) << "Thoi gian thuc hien: " << elapsed_time_ms << "ms" <<endl;


    cout << "Chi phi nho nhat la: " << ans << endl; // in ra kết quả
    return 0;

}       