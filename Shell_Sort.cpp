#include "iostream"

//数值交换
void SpecialSwap(int *right, int *left)
{
  int temp = *right;
  *right = *left;
  *left = temp;
}

//直接插入排序
void Insert_Sort(int *sample, int len)
{
  if (NULL == sample || len <= 1)
    return;

  for (int i = 1; i < len; ++i)
  {
    int m = i;
    for (int j = i - 1; j >= 0; --j)
    {
      if(sample[m] < sample[j])
      {
        SpecialSwap(sample+m, sample+j);
        m = j;
      }
    }
  }

  for (int n = 0; n < len; ++n)
  {
    std::cout << sample[n] << " ";
  }
  std::cout << std::endl;
}

//希尔排序
void ShellSort(int *sample, int len)
{
  if (NULL == sample || len <= 1)
    return;

  for (int step = len/2; step >= 1; step /= 2)
    for (int group = 0; group <= step; ++group)
    {
      for (int right = group; right < len-step; right += step)
        for (int left = right; left < len; left += step)
        {
          if (sample[right] > sample[left])
          {
            SpecialSwap(sample+right, sample+left);
          }
        }
    }

  for (int n = 0; n < len; ++n)
  {
    std::cout << sample[n] << " ";
  }
  std::cout << std::endl;
}

int main()
{
  int right = 5, left = 9;
  SpecialSwap(&right, &left);
  std::cout << "right: " << right << " - " << "left: " << left << std::endl;

  int sample[] = {9,3,1,4,6,8,5,2,7,0};
  for (int n = 0; n < 10; ++n)
  {
    std::cout << sample[n] << " ";
  }
  std::cout << std::endl;

  Insert_Sort(sample, 10);

  ShellSort(sample, 10);

  return 0;
}
