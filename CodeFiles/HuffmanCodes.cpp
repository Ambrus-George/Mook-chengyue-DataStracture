#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// ������������ı�׼WPL
int calcHuffmanWPL(vector<int>& freqs) {
    priority_queue<int, vector<int>, greater<int>> pq; // ��С��
    for (int f : freqs) {
        pq.push(f);
    }

    int wpl = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int sum = a + b;
        wpl += sum;
        pq.push(sum);
    }
    return wpl;
}

// ���ѧ���ύ�ı����Ƿ�Ϊ��Чǰ׺��
bool isPrefixFree(vector<string>& codes) {
    // �����볤������
    sort(codes.begin(), codes.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
        });

    for (int i = 0; i < codes.size(); i++) {
        for (int j = i + 1; j < codes.size(); j++) {
            // ����Ƿ���ǰ׺��ϵ
            if (codes[i] == codes[j].substr(0, codes[i].length())) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int N, M;
    cin >> N;

    // ��ȡ�ַ���Ƶ��
    map<char, int> freqMap;
    vector<int> freqs;
    for (int i = 0; i < N; i++) {
        char c;
        int f;
        cin >> c >> f;
        freqMap[c] = f;
        freqs.push_back(f);
    }

    // �����׼������WPL
    int huffmanWPL = calcHuffmanWPL(freqs);

    cin >> M; // ��ȡѧ������

    // ����ÿ��ѧ�����ύ
    for (int i = 0; i < M; i++) {
        vector<pair<char, string>> submissions;
        vector<string> studentCodes;
        bool validPrefix = true;
        int studentWPL = 0;

        // ��ȡѧ���ύ�ı���
        for (int j = 0; j < N; j++) {
            char c;
            string code;
            cin >> c >> code;
            submissions.push_back({ c, code });
            studentCodes.push_back(code);

            // ����ñ����WPL����
            if (freqMap.find(c) != freqMap.end()) {
                studentWPL += freqMap[c] * code.length();
            }
        }

        // ����Ƿ�Ϊ��Чǰ׺��
        validPrefix = isPrefixFree(studentCodes);

        // ��֤�����ǰ׺��Ч��WPL���ڹ�����WPL
        if (validPrefix && studentWPL == huffmanWPL) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }

    return 0;
}