// 정수 배열 nums와 목표값 target이 주어진다.
// 더해서 target이 되는 두 수의 인덱스를 반환하라. (답은 하나만 존재한다고 가정)

// 예: nums = [2, 7, 11, 15], target = 9 → [0, 1] (nums[0]+nums[1] = 2+7 = 9)

#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> map;

    for (size_t i=0 ; i<nums.size() ;i++) {
        int pair = target - nums[i];
        if (map.count(pair)) {
            return {map[pair], int(i)};
        }
        map[nums[i]] = i;
    }

    return {};
}

int main(){
    std::vector<int> nums = {2,7,11,15};
    auto result = twoSum(nums, 9);
    std::cout <<result[0] << ", " << result[1] << "\n";

    return 0;
}