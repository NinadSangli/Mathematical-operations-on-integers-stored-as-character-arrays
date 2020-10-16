#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void merge(char **arr, int l, int m, int r);

char* intal_add(const char* intal1, const char* intal2)
{
  int length = (strlen(intal1) > strlen(intal2))?strlen(intal1)+1:strlen(intal2)+1;
  int lim = length;
  char* sum = (char*)malloc((length+1)*sizeof(char));
  sum[length] = '\0';
  int i,j,carry,a;
  carry = 0;
  for(i = strlen(intal1)-1,j = strlen(intal2)-1; (i >= 0 && j >= 0); i--,j--)
  {
    a = (int)(intal1[i]-'0') + (int)(intal2[j]-'0') + carry;
    carry = (a > 9)?1:0;
    sum[--length] = (a%10)+'0';
  }
  if(i == -1 && j >= 0)
  {
    while(j >= 0)
    {
      a = (int)(intal2[j] - '0') + carry;
      carry = (a > 9)?1:0;
      sum[--length] = (a%10)+'0';
      j--;
    }
    if(carry)
    {
      sum[--length] = '1';
      return sum;
    }
    else
    {
      char* newsum = (char*)malloc(sizeof(char)*(lim));
      for(int k = 0; k < lim; k++)
        newsum[k] = sum[k+1];
      free(sum);
      return newsum;
    }
  }
  else if(j == -1 && i >= 0)
  {
    while(i >= 0)
    {
      a = (int)(intal1[i] - '0') + carry;
      carry = (a > 9)?1:0;
      sum[--length] = (a%10)+'0';
      i--;
    }
    if(carry)
    {
      sum[--length] = '1';
      return sum;
    }
    else
    {
      char* newsum = (char*)malloc(sizeof(char)*(lim));
      for(int k = 0; k < lim; k++)
        newsum[k] = sum[k+1];
      free(sum);
      return newsum;
    }
  }
  else
  {
    if(carry)
    {
      sum[--length] = '1';
      return sum;
    }
    else
    {
      char* newsum = (char*)malloc(sizeof(char)*(lim));
      for(int k = 0; k < lim; k++)
        newsum[k] = sum[k+1];
      free(sum);
      return newsum;
    }
  }
}

int intal_compare(const char* intal1, const char* intal2)
{
  int l1 = strlen(intal1);
  int l2 = strlen(intal2);
  if(l1 > l2)
    return 1;
  else if(l2 > l1)
    return -1;
  else
  {
    for(int i = 0; i < l1; i++)
    {
      if(intal1[i] > intal2[i])
        return 1;
      else if(intal2[i] > intal1[i])
        return -1;
    }
    return 0;
  }
}

char* intal_diff(const char* intal1, const char* intal2)
{
  int length = (strlen(intal1) > strlen(intal2))?strlen(intal1):strlen(intal2);
  int lim = length;
  int small = strlen(intal1) + strlen(intal2) - length;
  char* n1 = (char*)malloc(sizeof(char)*(length+1));
  char* n2 = (char*)malloc(sizeof(char)*(small+1));
  if(intal_compare(intal1,intal2) == 1)
  {
    strcpy(n1,intal1);
    strcpy(n2,intal2);
  }
  else if(intal_compare(intal1,intal2) == -1)
  {
    strcpy(n1,intal2);
    strcpy(n2,intal1);
  }
  else
  {
    free(n1);
    free(n2);
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    return zero;
  }
  char* diff = (char*)malloc((length+1)*sizeof(char));
  diff[length] = '\0';
  int i,j,carry,a;
  carry = 0;
  for(i = length-1,j = small-1; i >= 0; i--,j--)
  {
    if(j >= 0)
    {
      a = (int)(n1[i]-'0') - (int)(n2[j]-'0') - carry;
      carry = 0;
      if(a < 0)
      {
        a+=10;
        carry = 1;
      }
      diff[--length] = a+'0';
    }
    else
    {
      a = (int)(n1[i]-'0') - carry;
      carry = 0;
      if(a < 0)
      {
        a+=10;
        carry = 1;
      }
      diff[--length] = a+'0';
    }
  }
  free(n1);
  free(n2);

  if(diff[0] != '0')
    return diff;

  int start;
    for(start = 0; start < lim;start++)
      if(diff[start] != '0')
        break;
  if(start == 0)
    lim = start -1;
  char* newdiff = (char*)malloc(sizeof(char)*(lim-start+1));
  for(int k = 0; k < lim-start+1; k++)
    newdiff[k] = diff[k+start];
  free(diff);
  return newdiff;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
  if(intal1[0] == '0' || intal2[0] == '0')
  {
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    return zero;
  }
  int l1 = (strlen(intal1) > strlen(intal2))?strlen(intal1):strlen(intal2);
  int lim = l1;
  int l2 = strlen(intal1) + strlen(intal2) - l1;
  char* n1 = (char*)malloc(sizeof(char)*(l1+1));
  char* n2 = (char*)malloc(sizeof(char)*(l2+1));
  if(intal_compare(intal1,intal2) == 1)
  {
    strcpy(n1,intal1);
    strcpy(n2,intal2);
  }
  else
  {
    strcpy(n1,intal2);
    strcpy(n2,intal1);
  }
  char* product = (char*)malloc(sizeof(char)*1001);

  strcpy(product,"0");
  int linelength = 0;
  for(int i = l2-1; i >= 0; i--)
  {
    int multiplier = n2[i] - '0';
    int c = 0;
    char* line = (char*)malloc(sizeof(char)*(l1+linelength+1));
    for(int j = l1-1; j >= 0; j--)
    {
      int num = n1[j] - '0';
      int p1 = (num*multiplier)+c;
      int s = (p1%10);
      line[j] = s+'0';
      c = (p1/10)%10;
    }
    int counter = l2-1-i;
    char* carry = (char*)malloc(sizeof(char)*(l1+linelength+2));
    carry[l1+linelength+1] = '\0';
    for(int k = 0; k < l1+linelength+1;k++)
      carry[k] = '0';
    for(int k = l1; k < l1+linelength; k++)
      line[k] = '0';
    line[l1+linelength] = '\0';
    carry[0] = c+'0';
    char* temp;
    if(carry[0] != '0')
    {
      char* tempsum = intal_add(product,line);
      temp = intal_add(tempsum,carry);
      free(tempsum);
    }
    else
      temp = intal_add(product,line);
    strcpy(product,temp);
    free(carry);
    free(line);
    free(temp);
    linelength++;
  }
  free(n2);
  free(n1);
  char* finalproduct = (char*)malloc(sizeof(char)*(strlen(product)+1));
  strcpy(finalproduct,product);
  free(product);
  return finalproduct;
}

char* intal_mod(const char* intal1, const char* intal2)
{
  if(intal_compare(intal1,intal2) == -1)
  {
    char* result = (char*)malloc((strlen(intal1) + 1) * sizeof(char));
    strcpy(result, intal1);
    return result;
  }
  else if((intal_compare(intal1,intal2) == 0) || (intal_compare(intal2,"0") == 0))
  {
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    return zero;
  }
  int l1 = strlen(intal1);
  int l2 = strlen(intal2);
  char* i1 = (char*)malloc(sizeof(char)*(strlen(intal1)+1));
  char* sum = (char*)malloc(sizeof(char)*(l1+1));
  strcpy(sum,intal2);
  strcpy(i1,intal1);
  char* diff = intal_diff(sum,i1);
  while(intal_compare(diff,intal2) == 1)
  {
    free(diff);
    l1 = strlen(i1);
    for(int i = strlen(sum); i < l1; i++)
      sum[i] = '0';
    sum[l1] = '\0';
    if(intal_compare(sum,i1) == 1)
      sum[l1-1] = '\0';
    diff = intal_diff(sum,i1);
    strcpy(i1,diff);
  }
  free(i1);
  free(sum);
  if(intal_compare(diff,intal2) == 0)
  {
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    free(diff);
    return zero;
  }
  return diff;
}

char* intal_pow(const char* intal1, unsigned int n)
{
  int exp = 1;
  if(n == 0)
  {
    char* one = (char*)malloc(sizeof(char)*2);
    strcpy(one,"1");
    return one;
  }
  char* ans = (char*)malloc(sizeof(char)*1001);
  strcpy(ans,intal1);
  while(1)
  {
    if(exp*2 > n)
      break;
    else
      exp*=2;
    char* temp = intal_multiply(ans,ans);
    strcpy(ans,temp);
    free(temp);
  }
  while(exp < n)
  {
    char* temp = intal_multiply(ans,intal1);
    strcpy(ans,temp);
    free(temp);
    exp++;
  }
  char* finalans = (char*)malloc(sizeof(char)*(strlen(ans)+1));
  strcpy(finalans,ans);
  free(ans);
  return finalans;
}

char* intal_gcd(const char* intal1, const char* intal2)
{
  int length = (strlen(intal1) > strlen(intal2))?strlen(intal1):strlen(intal2);
  int lim = length;
  int small = strlen(intal1) + strlen(intal2) - length;
  char* n1 = (char*)malloc(sizeof(char)*(length+1));
  char* n2 = (char*)malloc(sizeof(char)*(small+1));
  if(intal_compare(intal1,intal2) == 1)
  {
    strcpy(n1,intal1);
    strcpy(n2,intal2);
  }
  else if(intal_compare(intal1,intal2) == -1)
  {
    strcpy(n1,intal2);
    strcpy(n2,intal1);
  }
  else
  {
    free(n1);
    strcpy(n2,intal1);
    return n2;
  }
  if(intal_compare(n2,"0") == 0)
  {
    free(n2);
    return n1;
  } 
  char* temp;
  while(1)
  {
    temp = intal_mod(n1,n2);
    free(n1);
    n1 = n2;
    n2 = temp;
    if(intal_compare(n2,"0") == 0)
    {
      free(n2);
      return n1;
    }
  }
  
}

char* intal_fibonacci(unsigned int n)
{
  if(n == 0)
  {
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    return zero;
  }
  else if(n == 1)
  {
    char* one = (char*)malloc(sizeof(char)*2);
    strcpy(one,"1");
    return one;
  }

  char* a = (char*)malloc(sizeof(char)*1001);
  char* b = (char*)malloc(sizeof(char)*1001);
  strcpy(a,"0");
  strcpy(b,"1");
  char* c = (char*)malloc(sizeof(char));
  for(int i = 1; i < n; i++)
  {
    free(c);
    c = intal_add(a,b);
    strcpy(a,b);
    strcpy(b,c);
  }
  free(a);
  free(b);
  return c;
}

char* intal_factorial(unsigned int n)
{
  char* soln = (char*)malloc(sizeof(char)*1001);
  char* num = (char*)malloc(sizeof(char)*1001);
  strcpy(soln,"1");
  while(n > 0)
  {
    sprintf(num, "%d", n);
    char* temp = intal_multiply(soln,num);
    strcpy(soln,temp);
    free(temp);
    n--;
  }
  free(num);
  return soln;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
  if(n < k)
  {
    char* zero = (char*)malloc(sizeof(char)*2);
    strcpy(zero,"0");
    return zero;
  }
  if( (n-k) < k)
      k = n-k;

  char** C = (char**)malloc((k+1) * sizeof(char*));
  int i;
  for(i = 1; i < k + 1; ++i) {
    C[i] = (char*)malloc(2 * sizeof(char));
    strcpy(C[i],"0\0");
  }
  C[0] = (char*)malloc(2*sizeof(char));
  strcpy(C[0],"1\0");;
  for(int i = 1; i < n + 1;i++)
  {
    // int j = (i > k)? k: i;
    for(int j = (i > k)? k: i; j > 0; j--)
    {
      char* tmp = C[j];
      C[j] = intal_add(C[j], C[j - 1]);
      free(tmp);
    }
  }

  char* result = (char*)malloc((strlen(C[k]) + 1) * sizeof(char));
  strcpy(result, C[k]);

  for(int i = 0; i < k + 1; i++)
    free(C[i]);
  free(C);
  return result;
}

int intal_max(char **arr, int n)
{
  char* num;
  num = arr[0];
  int max = 0;
  for(int i = 1; i < n; i++)
  {
    if(intal_compare(num,arr[i]) == -1)
    {
      num = arr[i];
      max = i;
    }
  }
  return max;
}

int intal_min(char **arr, int n)
{
  char* num;
  num = arr[0];
  int min = 0;
  for(int i = 1; i < n; i++)
  {
    if(intal_compare(num,arr[i]) == 1)
    {
      num = arr[i];
      min = i;
    }
  }
  return min;
}

int intal_search(char **arr, int n, const char* key)
{
  for(int i = 0; i < n; i++)
    if(intal_compare(key,arr[i]) == 0)
      return i;
  return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
  int l = 0;
  int r = n-1;
  while (l <= r)
  {
        int m = l + (r - l) / 2;
        if(intal_compare(arr[m],key) == 0)
        {
          while (m >= 0 && intal_compare(arr[m],key) == 0)
            m--;
          return m+1;
        }

        if(intal_compare(arr[m],key) == -1)
          l = m + 1;
        else
          r = m - 1;
    }
    return -1;
}

static void merge(char **arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    char** L = (char**) malloc(n1 * sizeof(char*));
    char** R = (char**) malloc(n2 * sizeof(char*));
    for (i = 0; i < n1; i++)
    {
      L[i] = (char*) malloc(1001 * sizeof(char));
      strcpy(L[i],arr[l+i]);
    }
    for (j = 0; j < n2; j++)
    {
      R[j] = (char*) malloc(1001 * sizeof(char));
      strcpy(R[j],arr[m+1+j]);
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if(intal_compare(L[i],R[j]) <= 0)
        {
            strcpy(arr[k],L[i]);
            i++;
        }
        else
        {
            strcpy(arr[k],R[j]);
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        strcpy(arr[k],L[i]);
        i++;
        k++;
    }
    while (j < n2)
    {
        strcpy(arr[k],R[j]);
        j++;
        k++;
    }
    for (i = 0; i < n1; i++)
      free(L[i]);
    for (j = 0; j < n2; j++)
      free(R[j]);
    free(L);
    free(R);
}

void intal_sort(char **arr, int n)
{
  int curr_size,left_start;
  for (curr_size = 1; curr_size <= n-1; curr_size = 2*curr_size)
  {
      for (left_start = 0; left_start < n-1; left_start += 2*curr_size)
      {
          int mid = (left_start+curr_size-1 < n-1)?left_start+curr_size-1:n-1;
          int right_end = (left_start + 2*curr_size - 1 < n-1)?left_start + 2*curr_size - 1:n-1;
          merge(arr, left_start, mid, right_end);
      }
  }
}

char* coin_row_problem(char **arr, int n)
{
  if(n == 0)
    return 0;
  char* prev = (char*)malloc(sizeof(char)*1001);
  strcpy(prev,"0");
  char* cur = (char*)malloc(sizeof(char)*1001);
  strcpy(cur,arr[0]);
  char* next = (char*)malloc(sizeof(char)*1001);
  for(int i = 2; i <= n; i++)
  {
    char* temp = intal_add(prev,arr[i-1]);
    strcpy(next,(intal_compare(temp,cur) == 1)?temp:cur);
    strcpy(prev,cur);
    strcpy(cur,next);
    free(temp);
  }
  free(prev);
  free(next);
  return cur;
}