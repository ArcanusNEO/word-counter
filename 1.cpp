    #include <iostream>
    #include <fstream>
    using namespace std;
    int main()
    {
        //打开 in.txt 文件，等待读取
        ifstream fin("in.txt");
        //打开 out.txt 文件，等待写入
        ofstream fout("out.txt");
        streambuf *oldcin;
        streambuf *oldcout;
        char a[100];
        //用 rdbuf() 重新定向，返回旧输入流缓冲区指针
        oldcin = cin.rdbuf(fin.rdbuf());
        //从input.txt文件读入
        cin >> a;
        //用 rdbuf() 重新定向，返回旧输出流缓冲区指针
        oldcout = cout.rdbuf(fout.rdbuf());
        //写入 out.txt
        cout << a << endl;
        //还原标准输入输出流
        cin.rdbuf(oldcin); // 恢复键盘输入
        cout.rdbuf(oldcout); //恢复屏幕输出
        //打开的文件，最终需要手动关闭
        fin.close();
        fout.close();
        return 0;
    }