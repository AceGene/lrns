// https://leetcode.com/problems/reverse-bits/
uint32_t reverseBits(uint32_t n) {
    n = n >> 16 | n << 16;
    n = (n >> 8) & 0b00000000111111110000000011111111 | (n & 0b00000000111111110000000011111111) << 8;
    n = (n >> 4) & 0b00001111000011110000111100001111 | (n & 0b00001111000011110000111100001111) << 4;
    n = (n >> 2) & 0b00110011001100110011001100110011 | (n & 0b00110011001100110011001100110011) << 2;
    n = (n >> 1) & 0b01010101010101010101010101010101 | (n & 0b01010101010101010101010101010101) << 1;
    return n;
}

// https://leetcode.com/problems/number-of-1-bits
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        // subtraction then & means the least significant 1 is removed
        n &= (n - 1);
        count++;
    }
    return count;
}

// https://leetcode.com/problems/minimum-bit-flips-to-convert-number/
int hammingWeight(int n) {
    int count = 0;
    while (n) {
        // subtraction then & means the least significant 1 is removed
        n &= (n - 1);
        count++;
    }
    return count;
}

int minBitFlips(int start, int goal) {
    return hammingWeight(start ^ goal);
}

// https://leetcode.com/problems/number-of-even-and-odd-bits/submissions/
vector<int> evenOddBit(int n) {
    vector<int> ret_val(2);
    while (n) {
        ret_val[0] += n & 0b1;
        ret_val[1] += (n >> 1) & 0b1;
        n >>= 2;
    }
    return ret_val;
}

// https://leetcode.com/problems/valid-parentheses
#include <unordered_map>

bool isValid(string s) {
    static std::unordered_map<char, char> close_to_open{{')', '('}, {'}', '{'}, {']', '['}};

    std::stack<char> unclosed_opening_braces{};
    for (const auto& c : s) {
        if (close_to_open.find(c) == close_to_open.end()) {
            unclosed_opening_braces.push(c);
        } else {
            if (unclosed_opening_braces.empty() || close_to_open[c] != unclosed_opening_braces.top()) {
                return false;
            }
            unclosed_opening_braces.pop();
        }
    }
    return unclosed_opening_braces.empty();
}

// bad
// https://leetcode.com/problems/merge-two-sorted-lists
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string
string removeDuplicates(string s) {
    while (true) {
        const auto found = std::adjacent_find(s.begin(), s.end());
        if (found == s.end()) {
            return s;
        }

        s.erase(found, found + 2);
    }
    return s;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array
int removeDuplicates(vector<int>& nums) {
    int index = 0;
    for (const auto& num : nums) {
        if (nums[index] < num) {
            nums[++index] = num;
        }
    }
    return ++index;
}

// https://leetcode.com/problems/longest-common-prefix/
string longestCommonPrefix(vector<string>& strs) {
    const auto min_length = std::min_element(strs.begin(), strs.end(), [](const auto& lhs, const auto& rhs) {
                                return lhs.length() < rhs.length();
                            })->length();

    std::string ret_val{};
    for (int i = 0; i < min_length; ++i) {
        const auto c = strs[0][i];
        const auto unmatched_char_iter
            = std::find_if(strs.begin() + 1, strs.end(), [i, c](const auto& str) { return str[i] != c; });
        if (unmatched_char_iter != strs.end()) {
            return ret_val;
        }
        ret_val.push_back(c);
    }

    return ret_val;
}

// https://leetcode.com/problems/search-insert-position/submissions/
int searchInsert(vector<int>& nums, int target) {
    // see std::lower_bound
    int l_bound = 0;
    int r_bound = nums.size();
    while (l_bound < r_bound) {
        int mid = l_bound + (r_bound - l_bound) / 2; // add then sub l_bound to prevent overflow
        if (nums[mid] < target) {
            l_bound = mid + 1;
        } else {
            r_bound = mid;
        }
    }
    return l_bound;
}

// https://leetcode.com/problems/length-of-last-word/submissions/
int lengthOfLastWord(string s) {
    int last_non_space = s.size() - 1;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] != ' ') {
            last_non_space = i;
            break;
        }
    }
    for (int i = last_non_space - 1; i >= 0; --i) {
        if (s[i] == ' ') {
            return last_non_space - i;
        }
    }
    return last_non_space + 1;
}

// https://leetcode.com/problems/plus-one/submissions/
vector<int> plusOne(vector<int>& digits) {
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 9) {
            digits[i] += 1;
            return digits;
        } else {
            digits[i] = 0;
        }
    }
    digits.insert(digits.begin(), 1); // ignored return value
    return digits;
}
