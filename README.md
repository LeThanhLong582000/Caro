1. Mô tả bàn cờ Caro
* Bàn cờ có kích thước là 18 x 18 có 2 chiều x nằm ngang và y nằm dọc. Điểm có tọa độ (1, 1) là ô nằm trên cùng bên trái.
2. Thuật toán Minimax
* Ta sử dụng để quỵ để xét qua từng trạng thái của cây trò chơi.
* Ở lớp Max điểm số trả về sẽ là điểm số lớn nhất ứng với nước đi có lợi nhất.
* Ở lớp Min điểm số trả về sẽ là điểm số bé nhất ứng với nước đi có hại nhất (Nước đi có lợi nhất đối với đối phương).
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
4. Hướng dẫn chạy chương trình
* Để chạy được chương trình bạn cần cài đặt SFML và liên kết các thư viện.
* Sau đây mình sẽ hướng dẫn các bạn chạy chương trình sử dụng Code Block.
* Trước hết bạn cần tải và cài đặt Code Block.
* Link tải Code Block: http://www.codeblocks.org/downloads/26
* Sau đó bạn cần tải SFML và liên kết vào Code Block ( Do trong project đã có sẵn các file dll của SFML nên các bạn không cần phải copy lại các file dll của SFML vào project nữa :)) )
* Để liên kết SFML vào Code Block các bạn làm theo các bước sau:
+ Mở file Caro.cbp bằng Code Block khi đó các bạn đã mở được project Caro bằng Code Block
+ Trên thanh công cụ của Code Block các bạn chon Project -> Build options sau đó chọn phần Linker settings trong cửa sổ hiện lên.
+ Sau đó các bạn add thêm các thư viện sau vào phần Link libraries: sfml-graphics, sfml-network, sfml-audio, sfml-system, sfml-window nếu các bạn đang chọn ở phần Release.
+ Đối với phần Debug các bạn chỉ cần thêm -d vào cuối mỗi thư viện (sfml-graphics-d, ...)
+ Sau đó các bạn chọn phần Search directories, chọn Complier sau đó add director là đường dẫn đến file include của SFML
+ Cũng ở phần Search directories các bạn chọn Linker sau đó add director là đường dẫn đến file lib của SFML
+ Như vậy các bạn đã liên kết thành công SFML vào Code Block.
+ Việc cuối cùng các bạn cần làm là chạy chương trình. Các bạn chỉ việc ấn vào nút build and run trên thanh công cụ của Code Block hoặc nhấn F9 để chạy chương trình và tận hưởng trò chơi.

* Ngoài ra các bạn có thể xem thêm video hướng dẫn cách cài SFML cho Code Block. Đây là đường link dẫn tới 1 video như vậy https://www.youtube.com/watch?v=fcZFaiGFIMA&t=464s.
