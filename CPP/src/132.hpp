#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool find132pattern_O3(vector<int>& nums) {
        size_t n = nums.size();
        for(size_t i = 0; i < n; i++)
            for(size_t j = i+1; j < n; j++)
                for(size_t k = j+1; k < n; k++)
                    if(nums[i] < nums[k] && nums[k] < nums[j])
                        return true;
        return false;
    }

    bool find132pattern_O2(vector<int>& nums) {
        size_t n = nums.size();
        int min_i = INT_MAX;
        for(size_t j = 0; j < n; j++)
        {   
            min_i = min(min_i, nums[j]);
            for(size_t k = j+1; k < n; k++)
            {
                if(min_i < nums[k] && nums[k] < nums[j])
                    return true;
            }
        }
        return false;
    }

    bool find132pattern_O1(vector<int>& nums) {
        size_t n = nums.size();
        int min_bf = nums[0];
        stack<pair<int,int>> st;
        for(int k = 1; k < n; ++k)
        {   
            while(!st.empty() && !(nums[k] < st.top().first))
                st.pop();

            if(!st.empty() && st.top().second < nums[k])
            {
                return true;
            }

            st.push({nums[k], min_bf});
            min_bf = min(min_bf, nums[k]);
        }
        return false;
    }

    bool find132pattern_O1_r(vector<int>& nums) {
        size_t n = nums.size();
        int max_af = INT_MIN;
        stack<int> st;
        for(int i = n-1; i >= 0; --i)
        {   
            if(!st.empty() /*nums[j] exists*/ && nums[i] < max_af /*nums[k]*/)
            {
                return true;
            }
            
            while(!st.empty() && nums[i] > st.top())
            {
                max_af = st.top() /*possible nums[k]*/; 
                st.pop();
            }

            st.push(nums[i] /*possible nums[j]*/);
        }
        return false;
    }
};
