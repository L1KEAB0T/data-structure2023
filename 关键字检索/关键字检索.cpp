#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MAXFILENAME 20
#define MAXTEXT 1000
#define MAXKEY 1000

class KeywordSearch {
private:
    char FileName[MAXFILENAME];
    char txt[MAXTEXT];
    char pat[MAXKEY];
    int* kmp_num;

    void kmp_next() {
        int len = 0;
        int i = 1;
        kmp_num[0] = 0;
        while (pat[i] != 0) {
            if (pat[len] == pat[i]) {
                len++;
                kmp_num[i] = len;
                i++;
            }
            else if (len > 0) {
                len = kmp_num[len - 1];
            }
            else {
                kmp_num[i] = len;
                i++;
            }
        }
    }

public:
    KeywordSearch() {
        kmp_num = nullptr;
    }

    ~KeywordSearch() {
        delete[] kmp_num;
    }

    void getInput() {
        cout << "关键字检索系统\n";
        cout << "请输入文件名：\n";
        cin >> FileName;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        ofstream ofs(FileName, ios::out);
        cout << "\n请输入一段英文：\n";
        cin.getline(txt, MAXTEXT);

        ofs << txt;
        cout << "本段文字已保存在文本文件" << FileName << "中\n";
        ofs.close();

        cout << "请输入要检索的关键字:\n";
        cin >> pat;
    }

    void searchKeyword() {
        int txt_len = strlen(txt);
        int pat_len = strlen(pat);

        kmp_num = new int[pat_len];
        kmp_next();

        int num = 0, txt_pos = 0, pat_pos = 0;
        while (txt_pos != txt_len) {
            if (txt[txt_pos] != pat[pat_pos]) {
                txt_pos++;
                txt_pos += kmp_num[pat_pos];
                pat_pos = kmp_num[pat_pos];
            }
            else if (pat_pos == pat_len - 1) {
                txt_pos++;
                pat_pos = 0;
                num++;
            }
            else {
                txt_pos++;
                pat_pos++;
            }
        }

        cout << "在源文件中检索到 " << num << " 处关键字" << endl;
    }
};

int main() {
    KeywordSearch searchSystem;
    searchSystem.getInput();
    searchSystem.searchKeyword();

    return 0;
}
