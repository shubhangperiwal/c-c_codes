__kernel void linear1(__global int *A, int ele, __global int *B)
{
int tid=get_global_id(0);
if(A[tid]==ele)
B[0]=B[0]|1;   //Even if one occurrence is found, B[0] will be 1 because of bitwise OR
}