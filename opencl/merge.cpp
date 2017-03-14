#include <stdio.h>
#include <CL/cl.h>
#include<stdlib.h>
#define MAX_SOURCE_SIZE 0x1000000

int main(void)
{
	int i,j,n;
	printf("Enter the no of values");
	scanf("%d", &n);
	if (n % 2 != 0)
		printf("better luck next time");
	else {
		int * a = (int *)malloc(n*sizeof(int)); // input elements host buffer
		int *b = (int*)malloc((n / 2) * sizeof(int));  //odd position elements host buffer
		int *c = (int *)malloc((n / 2) * sizeof(int)); //even position elements host buffer
		for (i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);


		}
		for (i = 0, j = 0; i < n; i++)
		{
			if (i % 2 != 0)
			{
				b[j] = a[i];
				j++;
			}
		}  //Moving the elements to b

		for (i = 0, j = 0; i < n; i++)
		{
			if (i % 2 == 0) {
				c[j] = a[i];
				j++;
			}
		} //Moving the elements to c

		// Load the kernel source code into the array source_str
		FILE *fp, *fp1, *fp2, *fp3;
		char *source_str, *source_str1, *source_str2, *source_str3;
		size_t source_size, source_size1, source_size2, source_size3;
		fp = fopen("odd.cl", "r"); //odd transposition for  sublists
		if (!fp)
		{
			fprintf(stderr, "Failed to load odd1 kernel.\n");
			getchar();
			exit(1);
		}
		source_str = (char*)malloc(MAX_SOURCE_SIZE);
		source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
		fclose(fp);

		fp1 = fopen("even.cl", "r");   //even transposition for sublists
		if (!fp1)
		{
			fprintf(stderr, "Failed to load even1 kernel.\n");
			getchar();
			exit(1);
		}
		source_str1 = (char*)malloc(MAX_SOURCE_SIZE);
		source_size1 = fread(source_str1, 1, MAX_SOURCE_SIZE, fp1);
		fclose(fp1);

		fp2 = fopen("comp.cl", "r"); //odd transposition during merge
		if (!fp2)
		{
			fprintf(stderr, "Failed to load even1 kernel.\n");
			getchar();
			exit(1);
		}
		source_str2 = (char*)malloc(MAX_SOURCE_SIZE);
		source_size2 = fread(source_str2, 1, MAX_SOURCE_SIZE, fp2);
		fclose(fp2);

		fp3 = fopen("comp2.cl", "r"); //even transposition during merge
		if (!fp3)
		{
			fprintf(stderr, "Failed to load even1 kernel.\n");
			getchar();
			exit(1);
		}
		source_str3 = (char*)malloc(MAX_SOURCE_SIZE);
		source_size3 = fread(source_str3, 1, MAX_SOURCE_SIZE, fp3);
		fclose(fp3);
		// Get platform and device information
		cl_platform_id platform_id = NULL;
		cl_device_id device_id = NULL;
		//cl_uint ret_num_devices;
		//cl_uint ret_num_platforms;

		cl_int ret = clGetPlatformIDs(1, &platform_id, NULL);
		ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id,
			NULL);
		// Create an OpenCL context
		cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL,
			&ret);
		// Create a command queue
		cl_command_queue command_queue = clCreateCommandQueue(context,
			device_id,
			CL_QUEUE_PROFILING_ENABLE, &ret);
		// Create buffers
		cl_mem b_mem_obj = clCreateBuffer(context,
			CL_MEM_READ_WRITE, (n / 2) * sizeof(int), NULL, &ret);
		cl_mem c_mem_obj = clCreateBuffer(context,
			CL_MEM_READ_WRITE, (n / 2) * sizeof(int), NULL, &ret);

		//Write into buffer
		ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
			* sizeof(int), b, 0, NULL, NULL);
		ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
			* sizeof(int), c, 0, NULL, NULL);

		//step 7  4 program objects, 4 kernel objects
		cl_program program = clCreateProgramWithSource(context, 1, (const
			char**)&source_str, (const size_t *)&source_size, &ret);
		cl_program program1 = clCreateProgramWithSource(context, 1, (const
			char**)&source_str1, (const size_t *)&source_size1, &ret);
		cl_program program2 = clCreateProgramWithSource(context, 1, (const
			char**)&source_str2, (const size_t *)&source_size2, &ret);
		cl_program program3 = clCreateProgramWithSource(context, 1, (const
			char**)&source_str3, (const size_t *)&source_size3, &ret);

		// Build the program
		ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
		ret = clBuildProgram(program1, 1, &device_id, NULL, NULL, NULL);
		ret = clBuildProgram(program2, 1, &device_id, NULL, NULL, NULL);
		ret = clBuildProgram(program3, 1, &device_id, NULL, NULL, NULL);

		// Create the OpenCL kernel object
		cl_kernel kernel = clCreateKernel(program, "odd1", &ret);
		cl_kernel kernel1 = clCreateKernel(program1, "even1", &ret);
		cl_kernel kernel2 = clCreateKernel(program2, "comp1", &ret);
		cl_kernel kernel3 = clCreateKernel(program3, "comp3", &ret);

		//set kernel argumets
		ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&b_mem_obj);
		ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&c_mem_obj);
		ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void *)&b_mem_obj);
		ret = clSetKernelArg(kernel1, 1, sizeof(cl_mem), (void *)&c_mem_obj);
		ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&c_mem_obj);
		ret = clSetKernelArg(kernel3, 0, sizeof(cl_mem), (void *)&c_mem_obj);

		// Execute the OpenCL kernel on the array
		size_t global_item_size1[1];
		global_item_size1[0] = n / 2;

		//Execute the kernel on the device
		cl_event event; // odd even transposition sorting of sublists
		int m = n / 2;
		if (m % 2 == 0)
			m = (n / 2) + 1;
		for (i = 0; i < m; i++)
		{
			ret = clEnqueueNDRangeKernel(command_queue, kernel, 1,
				NULL, global_item_size1, NULL, 0, NULL, &event);
			ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), b, 0, NULL, NULL);
			ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), c, 0, NULL, NULL);
			ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), b, 0, NULL, NULL);
			ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), c, 0, NULL, NULL);
			ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1,
				NULL, global_item_size1, NULL, 0, NULL, &event);
			ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), b, 0, NULL, NULL);
			ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), c, 0, NULL, NULL);
			ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), b, 0, NULL, NULL);
			ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
				* sizeof(int), c, 0, NULL, NULL);

		}
		ret = clEnqueueReadBuffer(command_queue, b_mem_obj, CL_TRUE, 0, (n / 2)
			* sizeof(int), b, 0, NULL, NULL);
		ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
			* sizeof(int), c, 0, NULL, NULL);
		printf("printing b and c");
		for (int i = 0; i < (n / 2); i++)
		{
			printf("%d  ", b[i]);
		} printf("\n");
		for (int i = 0; i < (n / 2); i++)
			printf("%d  ", c[i]);
		printf("\n");
		printf("print2 ended");

		// swap elements of b and c ,and sort the second sublist when there is a swap
		int temp;
		for (int i = 0; i < (n / 2); i++)
		{
			for (int j = 0; j<(n / 2); j++) {
				if (b[i]>c[j])
				{
					temp = b[i];
					b[i] = c[j];
					c[j] = temp;
					for (int i = 0; i < (n / 2); i++)
						printf("Hi %d", c[i]);
					ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
						* sizeof(int), c, 0, NULL, NULL);
					int m = n / 2;
					if (m % 2 != 0)
						m = (n / 2) + 1;

					for (int k = 0; k < m; k++)
					{

						ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1,
							NULL, global_item_size1, NULL, 0, NULL, &event);
						ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
							* sizeof(int), c, 0, NULL, NULL);
						for (int l = 0; l < (n / 2); l++)
							printf(" odd%d ", c[l]);
						ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
							* sizeof(int), c, 0, NULL, NULL);
						ret = clEnqueueNDRangeKernel(command_queue, kernel3, 1,
							NULL, global_item_size1, NULL, 0, NULL, &event);
						ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
							* sizeof(int), c, 0, NULL, NULL);
						for (int l = 0; l < (n / 2); l++)
							printf("even %d ", c[l]);
						ret = clEnqueueWriteBuffer(command_queue, c_mem_obj, CL_TRUE, 0, (n / 2)
							* sizeof(int), c, 0, NULL, NULL);
						printf("intermediate");
						for (int l = 0; l < (n / 2); l++)
							printf("%d  ", b[l]);
						printf("\n");
						for (int l = 0; l < (n / 2); l++)
							printf("%d ", c[l]);
						printf("\n");
						printf("end of iteration %d", k);
					}
					break;
				}
				else break;
			}


		}
		ret = clFinish(command_queue);
		//calculate time
		cl_ulong time_start, time_end;
		double total_time;
		clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
		clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
		total_time = (double)time_end - time_start;

		printf("final");
		for (i = 0; i < (n / 2); i++)
			printf("%d  ", b[i]);
		for (int i = 0; i < (n / 2); i++)
			printf("%d ", c[i]);
		getchar();
		// Clean up
		//ret = clFlush(command_queue);
		ret = clReleaseKernel(kernel);
		ret = clReleaseProgram(program);

		//ret = clReleaseMemObject(d_mem_obj);
		ret = clReleaseMemObject(b_mem_obj);
		ret = clReleaseMemObject(c_mem_obj);
		ret = clReleaseCommandQueue(command_queue);
		ret = clReleaseContext(context);
		printf("the time is %f", total_time / 1000000);
		getchar();
		free(b);
		free(c);
	}
		
	return 0;
}