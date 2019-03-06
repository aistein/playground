#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<list>
#include<unordered_map>

#define SIZE 1000000

using namespace std;

class Solution {
public:
    /* twoSum - brute force nested loop
     * O(n^2) time-complexity
     * O(1) extra-complexity
     */
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i,j};
                }
            }
        }
        return {-1, -1};
    }

    /* twoSumBetter - by sorting and using binary search
     * O(nlogn) time-complexity
     * O(n) extra-space
     */
    vector<int> twoSumBetter(vector<int>& nums, int target) {
        /* create tuple-vector of original values paired with their original indices (n) */
        vector<pair<int,int>> nums_with_idx;
        for (int i = 0; i < nums.size(); i++) {
            nums_with_idx.emplace_back(nums[i], i);
        }
        /* sort the tuple-vector by increasing value (nlogn) */
        struct SortComp
        {
            bool operator() ( const pair<int,int> &a, const pair<int,int> &b ) const { return a.first < b.first; }
        };
        sort(nums_with_idx.begin(), nums_with_idx.end(), SortComp{});
        /* binary-search for remainder value (nlogn) */
        struct BinSearchComp
        {
            bool operator() ( const pair<int,int> &t, int e ) const { return t.first < e; }
            bool operator() ( int e, const pair<int,int> &t ) const { return e < t.first; }
        };
        for (auto it = nums_with_idx.begin(); it != nums_with_idx.end(); ++it) {
            int rem = target - it->first;
            auto r = equal_range(next(it,1), nums_with_idx.end(), rem, BinSearchComp{});
            if (r.first != nums_with_idx.end() && (r.first)->first == rem) {
                return {it->second, (r.first)->second};
            }
        }
        /* default return value */
        return {-1, -1};
    }

    /* twoSumEvenBetter - by using a hashmap
     * Theta(n) time-complexity
     * Theta(n) extra-space
     */
    vector<int> twoSumEvenBetter(vector<int> &nums, int target) {
        /* create a hash-map */
        unordered_map<int,list<int>> idxs_by_value;
        for (int i = 0; i < nums.size(); i++) {
            idxs_by_value[nums[i]].push_back(i);
        }
        /* for each num, look in the hash map for its 'complement' */
        for (auto p : idxs_by_value) {
            int complement = target - p.first;
            int sidx = p.second.front();
            auto cit = idxs_by_value.find(complement);
            /* does the complement value exist in the map */
            if (cit == idxs_by_value.end()) {
                continue;
            }
            auto cidxs = cit->second;
            /* is the complement value the same as the source value */
            if (cidxs.front() == p.first) {
                if (cidxs.size() == 1) {
                    /* can't use the same element twice */
                    continue;
                }
                /* return the index of the next satisfying element that's not the source */
                return {sidx, cidxs.back()};
            }
            /* the complement exists and isn't the same as the source value */
            return {sidx, cidxs.front()};

        }
        /* default return value */
        return {-1, -1};
    }

    /* twoSumBest - hashmap in a single pass
     * O(n) time-complexity
     * O(n) extra-space
     * 
     * No need to check for "same element" as we dont insert into the map
     * until after checking for the existence of the complement.
     */
    vector<int> twoSumBest(vector<int> &nums, int target) {
        unordered_map<int,int> idx_by_value;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            auto c_pair = idx_by_value.find(complement);
            if (c_pair != idx_by_value.end()) {
                return {i, c_pair->second};
            }
            idx_by_value[nums[i]] = i;
        }
        return {-1, -1};
    }
    
};

int main(int argc, char* argv[]) {
    /* which implementation to use */
    string implementation = argv[1];

    /* inputs */
    int arr[SIZE+1];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }
    arr[SIZE] = 1;
    int len = SIZE+1;
    int target = SIZE + SIZE - 1;

    /* solution */
    Solution S;
    vector<int> v = vector<int>(arr, arr + len); 
    random_shuffle(v.begin(), v.end());
    vector<int> result;
    if (implementation == "naive") {
        result = S.twoSum(v, target);
    }
    if (implementation == "better") {
        result = S.twoSumBetter(v, target);
    }
    if (implementation == "evenbetter") {
        result = S.twoSumEvenBetter(v, target);
    }
    if (implementation == "best") {
        result = S.twoSumBest(v, target);
    }
    cout << "solution indices: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
