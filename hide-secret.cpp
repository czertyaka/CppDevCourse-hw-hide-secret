#include <vector>

void hide_secret(char* const text, const char* const secret) {
    if (text == nullptr || secret == nullptr){
        return;
    }

    int m = 0;
    const char* temp = secret;
    while (*temp != '\0') {
        m++;
        temp++;
    }
    
    if (m == 0) {
        return;
    }

    std::vector<int> lps(m);
    
    int len = 0;
    lps[0] = 0;
    
    int i = 1;
    while (i < m) {
        if (secret[i] == secret[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    int j = 0;
    i = 0;
    
    while (text[i] != '\0') {
        if (secret[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == m) {
            for (int k = i - j; k < i; k++) {
                text[k] = 'x';
            }
            j = lps[j - 1];
        } else if (text[i] != '\0' && secret[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}