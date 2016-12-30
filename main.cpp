// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iterator>

// class solution {
//   public:
//     std::vector<int> largestDivisibleSubset(const std::vector<int> & nums) {
//         auto sorted = nums;
//         std::sort(sorted.begin(), sorted.end());

//         std::vector<std::vector<size_t>> paths = getPaths(sorted, std::vector<size_t>());
//         std::for_each(paths.begin(), paths.end(),
//                       [&](const std::vector<size_t> & vec){
//                           std::for_each(vec.begin(), vec.end(),
//                                         [&](size_t id){std::cout << sorted[id] << " ";});
//                           std::cout << std::endl;
//                       });
        
//         auto it = std::max_element(paths.begin(), paths.end(),
//                                  [](const std::vector<size_t> & v1, const std::vector<size_t> & v2){
//                                      return v1.size() < v2.size();
//                                  });

//         std::vector<int> result;
//         std::transform(it->begin(), it->end(), std::inserter(result, result.end()),
//                        [&](size_t idx){return sorted[idx];});
//         return result;
//     }

//   private:
//     std::vector<std::vector<size_t>> getPaths(const std::vector<int> & nums, const std::vector<size_t> & curr) {
//         std::vector<std::vector<size_t>> result;
//         std::vector<size_t> next = getNext(nums, curr);
//         if (next.empty())
//             result.push_back(curr);
//         else {
//             for (auto nx : next) {
//                 auto cpy = curr;
//                 cpy.push_back(nx);
//                 auto temp = getPaths(nums, cpy);
//                 std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
//             }
//         }
//         return result;
//     }

//     std::vector<size_t> getNext(const std::vector<int> & nums, const std::vector<size_t> & curr) {
//         std::vector<size_t> next;
//         if (curr.empty()) {
//             size_t i = 0;
//             std::generate_n(std::inserter(next,next.begin()), nums.size(), [&](){return i++;});
//             // std::copy(next.begin(), next.end(), std::ostream_iterator<size_t>(std::cout," "));
//             // std::cout << std::endl;
//         }
//         else {
//             for (size_t i = curr.back()+1; i < nums.size(); i++)
//                 if (nums[i]%nums[curr.back()] == 0)
//                     next.push_back(i);
//         }
        
//         return next;
//     }
// };

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class solution {
  public:
    std::vector<int> largestDivisibleSubset(const std::vector<int> & nums) {
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        std::vector<std::vector<int>> subsets;
        for (auto n : sorted) {
            if (subsets.empty())
                subsets.push_back(std::vector<int>{n});
            else {
                auto it = std::find_if(subsets.rbegin(), subsets.rend(),
                                       [&](const std::vector<int> & vec){return n%vec.back() == 0;});
                if (it == subsets.rend())
                    subsets.push_back(std::vector<int>{n});
                else {
                    auto cpy = *it;
                    cpy.push_back(n);
                    subsets.push_back(cpy);
                }
            }
        }

        std::for_each(subsets.begin(), subsets.end(),
                      [](const std::vector<int> & vec){
                          std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
                          std::cout << std::endl;
                      });

        return *std::max_element(subsets.begin(), subsets.end(),
                                 [](const std::vector<int> & v1, const std::vector<int> & v2){
                                     return v1.size() < v2.size();
                                 });
    }
};

int main() {
    std::vector<int> nums{2,3,4,6,8,9,12,24};

    solution soln;
    auto subset = soln.largestDivisibleSubset(nums);
    std::cout << "The largest divisible subset is:\n";
    std::copy(subset.begin(), subset.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
