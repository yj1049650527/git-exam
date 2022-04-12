#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct record{
  int val;
  string name;
};
struct re_hash{
  size_t operator()(const record &r)const
  {
    return hash<int>()(r.val)^hash<string>()(r.name);
  }
};
struct re_equal{
 bool operator()(const record& r1, const record& r2)const
 {
     return r1.name==r2.name && r1.val==r2.val;
 }
};
void quick_sort(vector<int> &nums, int l, int r);
void mergearray(vector<int> &nums, int left, int mid, int right, vector<int> &merge);
void merge_sort(vector<int> &nums, int left, int right, vector<int>& merge);
int main()
{
  vector<int> a{3, 5, 6, 3, 2, 6, 8, 4, 2, 0};
  vector<int> temp(a.size());
  int size=a.size();
  merge_sort(a, 0, a.size() - 1, temp);
  for (int i = 0; i < a.size(); i++)
    cout << a[i];
  unordered_set<record,re_hash,re_equal> hash_t{{1,"yaojun"},{2,"yuanye"},{3,"yunhao"}};
  for(auto r:hash_t)
   cout<<r.val<<r.name<<endl;
    hash_t.max_load_factor(0.7);
  hash_t.reserve(1000);
}

void quick_sort(vector<int> &nums, int l, int r)
{
  if (l >= r)
    return;
  int i = l, j = r;
  int value = nums[l];
  while (i < j)
  {
    while (i < j && nums[j] > value)
      j--;
    if (i < j)
      nums[i++] = nums[j];

    while (i < j && nums[i] < value)
      i++;
    if (i < j)
      nums[j--] = nums[i];
  }
  nums[i] = value;
  quick_sort(nums, l, i - 1);
  quick_sort(nums, i + 1, r);
}

void mergearray(vector<int> &nums, int left, int mid, int right, vector<int> &merge)
{
  int i = left, j = mid + 1, k = 0;
  while (i <= mid && j <= right)
  {
    while (i <= mid && nums[i] <= nums[j])
      merge[k++] = nums[i++];

    while (j <= right && nums[j] <= nums[i])
      merge[k++] = nums[j++];
  }
  while(i <= mid)
    merge[k++]=nums[i++]; 

  while(j <= right)
    merge[k++]=nums[j++];

  for(int i=0; i<k; i++)
    nums[left+i]=merge[i];  
} 

void merge_sort(vector<int> &nums, int left, int right, vector<int>& merge)
{
  if (left < right)
  {
    int mid = (left + right) / 2;
    merge_sort(nums, left, mid, merge);
    merge_sort(nums, mid + 1, right, merge);
    mergearray(nums, left, mid, right, merge);
  }
}
