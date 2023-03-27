/* Bài toán yêu cầu tìm đường đi ngắn nhất qua tất cả các thành phố trên bản đồ và quay về thành phố xuất phát
 Phương pháp Brute Force.
 Để áp dụng bài toán du lịch vào thực tế, chúng ta có thể xây dựng ứng dụng để đưa ra lời khuyên du lịch cho người dùng. 
 Ứng dụng có thể lấy dữ liệu địa điểm cần quan tâm từ người dùng và sử dụng thuật toán tìm đường đi ngắn nhất để xác định một
  hành trình du lịch hợp lý và tiết kiệm chi phí nhất.
 */
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;
const int INF = 0x3f3f3f3f;
/*n là số lượng thành phố, g là một ma trận để lưu khoảng cách giữa các thành phố, vis là một mảng để kiểm tra xem một thành phố đã được đánh dấu
 trên đường đi hay chưa, d là một mảng để lưu trữ thứ tự các thành phố và ans là biến để lưu trữ chi phí ngắn nhất hiện tại để đi từ thành phố 1,
  thăm tất cả các thành phố khác và quay trở lại thành phố 1.*/
int n, g[maxn][maxn], d[maxn], vis[maxn], ans = INF; // khởi tạo biến
vector<int> p; // mảng p để lưu trữ lộ trình du lịch
/*Hàm DFS() là hàm chính để tìm kiếm đường đi ngắn nhất. Để tạo ra các nút con của một nút trên cây trạng thái, chúng ta sử dụng kỹ thuật 
backtracking để đổi chỗ hai thành phố và tạo nút con mới. Khi đã tìm kiếm xong một nút con, chúng ta đảo ngược trạng thái để quay về trạng 
thái ban đầu.
Nếu chi phí hiện tại vượt quá giá trị tốt nhất hiện tại (được lưu trữ trong biến ans) thì ta quay trở lại và không tiếp tục tìm kiếm. Nếu đã 
đi qua tất cả các thành phố, ta tính toán chi phí để quay trở lại thành phố ban đầu và cập nhật giá trị chi phí nhỏ nhất.*/
void DFS(int x, int cost) {
    if (cost >= ans) return; // nếu chi phí > hoặc = chi phí nhỏ nhất đã tìm thì kết thúc.
    if (x == n) { // nếu tất cả thành phố đã được thăm
      if (cost + g[d[n-1]][d[n]] < ans) { // nếu có một đường đi ngắn hơn, lưu lại lộ trình mới
            ans = cost + g[d[n-1]][d[n]];
            p.clear();
            for (int i = 0; i <= n; i++) {
                p.push_back(d[i]);
            }
        }
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1; // đánh dấu là đã thăm
            d[x] = i; // lưu địa danh
            DFS(x+1, cost + g[d[x-1]][d[x]]); // tiếp tục thăm thành phố tiếp theo
            vis[i] = 0; // hoàn trả lại trạng thái trước đó
        }
    }
}

int main(){
    cout << "Nhap vao so luong thanh pho: ";
    cin >> n;
    cout << "Nhap vao ma tran khoang cach: " << endl; 
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            int distance;
    cout << "Khoang cach tu thanh pho "<<i<<" den thanh pho "<<j<< endl; 
 
             cin >> distance;
            g[i][j] = distance;
            g[j][i] = distance;
        }
    }
    memset(vis, 0, sizeof(vis)); // khởi tạo mảng vis bằng 0
    d[0] = 1; // khởi tạo địa danh ban đầu
    vis[1] = 1; // đánh dấu thành phố đầu tiên đã thăm
      // Lấy thời gian hiện tại
    auto start_time = high_resolution_clock::now();
    DFS(1, 0); // bắt đầu đi tìm
    // Lấy thời gian sau khi hàm đã thực hiện xong
    auto end_time = high_resolution_clock::now();

    // Tính thời gian đã trôi qua
     auto elapsed_time_ns = duration_cast<nanoseconds>(end_time - start_time);
    double elapsed_time_ms = elapsed_time_ns.count() / 1000000.0;
      // In ra thời gian đã trôi qua
     cout << std::fixed << std::setprecision(3) << "Thoi gian thuc hien: " << elapsed_time_ms << "ms" <<endl;
    cout << "Chi phi nho nhat la: " << ans << endl; // in ra kết quả
     cout << "Lộ trình đi qua các thành phố: ";
    for (int i = 0; i <= n; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    return 0;
}