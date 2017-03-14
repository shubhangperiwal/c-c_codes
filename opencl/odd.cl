__kernel void odd1(__global int *b, __global int *c)
{
int idx=get_global_id(0);
int size=get_global_size(0);
int temp;
if((idx%2!=0) && ((idx+1)<size))
{
if(b[idx]>b[idx+1])
{
temp=b[idx];
b[idx]=b[idx+1];
b[idx+1]=temp;
} 
if(c[idx]>c[idx+1])
{
temp=c[idx];
c[idx]=c[idx+1];
c[idx+1]=temp;
}}
}