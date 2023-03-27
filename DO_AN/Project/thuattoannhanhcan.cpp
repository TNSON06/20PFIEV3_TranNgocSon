/*Thuật toán nhánh cận (Branch and Bound) cũng là một trong những kỹ thuật được sử dụng để giải quyết Bài toán du lịch (Travelling Salesman Problem).
 Thuật toán này dựa trên ý tưởng tìm kiếm trên cây trạng thái của bài toán. Mỗi nút trên cây biểu diễn một địa điểm trên bản đồ và tập hợp các nút con
  của một nút biểu thị các địa điểm khác có thể được đi qua tiếp theo.
Để áp dụng thuật toán nhánh cận vào bài toán du lịch, ta cần xác định một hàm chi phí để tính toán chi phí đường đi ngắn nhất giữa các nút trên cây.
 Sau đó, ta sử dụng kỹ thuật backtracking để tạo các nút con của mỗi nút trên cây để tìm đường đi ngắn nhất.
*/
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;
const int INF = 0x3f3f3f3f;
/*n là số lượng thành phố, 
g là một ma trận để lưu khoảng cách giữa các thành phố,
vis là một mảng để kiểm tra xem một thành phố đã được đánh dấu trên đường đi hay chưa
d là một mảng để lưu trữ thứ tự các thành phố 
ans là biến để lưu trữ chi phí ngắn nhất hiện tại để đi từ thành phố 1, thăm tất cả các thành phố khác và quay trở lại thành phố 1.*/
int n, g[maxn][maxn], vis[maxn], d[maxn], ans = INF; // khởi tạo biến
/*Hàm Branch_and_Bound_TSP() là hàm chính để tìm kiếm đường đi ngắn nhất. Để tạo ra các nút con của một nút trên cây trạng thái, chúng ta sử dụng kỹ
 thuật backtracking để đổi chỗ hai thành phố và tạo nút con mới. Khi đã tìm kiếm xong một nút con, chúng ta đảo ngược trạng thái để quay về trạng 
 thái ban đầu.
Nếu chi phí hiện tại vượt quá giá trị tốt nhất hiện tại (được lưu trữ trong biến ans) thì ta quay trở lại và không tiếp tục tìm kiếm. Nếu đã đi 
qua tất cả các thành phố, ta tính toán chi phí để quay trở lại thành phố ban đầu và cập nhật giá trị chi phí nhỏ nhất.*/
void Branch_and_Bound_TSP(int u, int cost) {
    if (cost >= ans) return; // nếu chi phí > hoặc = chi phí nhỏ nhất đã tìm thì kết thúc.
    if (u == n) { // nếu tất cả thành phố đã được thăm
        ans = min(ans, cost + g[d[n-1]][d[n]]); // lưu vào chi phí nhỏ nhất
        return;
    }
    for (int i = u+1; i <= n; i++) {
        swap(d[u+1], d[i]); // đổi chỗ 2 thành phố để tạo nút con mới
        Branch_and_Bound_TSP(u+1, cost + g[d[u]][d[u+1]]); // tiếp tục tìm kiếm với nút con mới
        swap(d[u+1], d[i]); // hoàn trả lại trạng thái trước đó
    }
}
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
   
    for (int i = 1; i <= n; i++) {
        for (int j =i+ 1; j <= n; j++) {
             int distance;
    cout << "Khoang cach tu thanh pho "<<i<<" den thanh pho "<<j<< endl; 
 
             cin >> distance;
            g[i][j] = distance;
            g[j][i] = distance;

        }
    }
    print_distance_matrix();
    memset(vis, 0, sizeof(vis)); // khởi tạo mảng vis bằng 0
    d[0] = 1; // khởi tạo địa danh ban đầu
    Branch_and_Bound_TSP(0, 0); // bắt đầu đi tìm
    cout << "Chi phi nho nhat la: " << ans << endl; // in ra kết quả
    return 0;
}