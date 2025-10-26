#include <bits/stdc++.h>
using namespace std;
void isPalindromeHelper(const string &s, int left, int right, bool &result) {
    if (left >= right) {
        return;
    }
    if (s[left] != s[right]) {
        result = false;
        return;
    }
    isPalindromeHelper(s, left + 1, right - 1, result);
}
int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;
    bool result = true;
    isPalindromeHelper(s, 0, s.length() - 1, result);
    if (result) {
        cout << s << " is a palindrome." << endl;
    } else {
        cout << s << " is not a palindrome." << endl;
    }
    return 0;
}