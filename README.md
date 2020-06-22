1. Mô tả bàn cờ Caro

_ Bàn cờ có kích thước là 18 x 18 có 2 chiều x nằm ngang và y nằm dọc. Điểm có tọa độ (1, 1) là ô nằm trên cùng bên trái.

2. Thuật toán Minimax

_ Ta sử dụng để quỵ để xét qua từng trạng thái của cây trò chơi.

_ Ở lớp Max điểm số trả về sẽ là điểm số lớn nhất ứng với nước đi có lợi nhất.

_ Ở lớp Min điểm số trả về sẽ là điểm số bé nhất ứng với nước đi có hại nhất (Nước đi có lợi nhất đối với đối phương).

3. Giải thích chức năng 1 số hàm
* Caro_Board: Constructor của class tạo ra một bàn cờ có thích thước là tham số được truyền vào.
* Display: Dùng để hiển thị bàn cờ và các quân cờ ở trên đó
* Tick_X: Đánh dấu nước đi của người chơi.
* Tick_O: Đánh dấu nước đi của AI.
* isEmpty: Kiểm tra xem ô trên bàn cờ có thể đi được hay không.
* get_size: Trả về kích thước của bàn cơ.
* Del: Xóa ô đã chơi đi (Undo)
* Cal_Point: Tính toán số điểm đạt được của trạng thái đang có.
* Class_Min: Lớp Min trên cây trò chơi.
* Class_Max: Lớp Max trên cây trò chơi.
* MiniMax: Dùng để đưa ra quyết định của AI.
* isWin: Kiểm tra xem AI đã thắng chưa ( Có 5 tick liên tiếp).
* isLose: Kiểm tra xem AI đã thua chưa ( Người chơi có 5 tick liên tiếp).
