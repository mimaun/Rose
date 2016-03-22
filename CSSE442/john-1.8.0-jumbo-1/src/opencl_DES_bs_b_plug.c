/*
 * This software is Copyright (c) 2012 Sayantan Datta <std2048 at gmail dot com>
 * and it is hereby released to the general public under the following terms:
 * Redistribution and use in source and binary forms, with or without modification, are permitted.
 * Based on Solar Designer implementation of DES_bs_b.c in jtr-v1.7.9
 */

#ifdef HAVE_OPENCL

#include <assert.h>
#include <string.h>
#include <sys/time.h>

#include "options.h"
#include "opencl_DES_bs.h"
#include "memdbg.h"

#define LOG_SIZE 1024*16

typedef unsigned WORD vtype;

opencl_DES_bs_transfer *opencl_DES_bs_data;
DES_bs_vector *B;

static cl_kernel krnl[MAX_PLATFORMS * MAX_DEVICES_PER_PLATFORM][4096];
static cl_int err;
static cl_mem index768_gpu, index96_gpu, opencl_DES_bs_data_gpu, B_gpu, cmp_out_gpu, loaded_hash_gpu;
static int set_salt = 0;
static   WORD current_salt;
static int *loaded_hash;
static unsigned int *cmp_out, num_loaded_hash, min, max ;
static int benchmark = 1;

void DES_opencl_clean_all_buffer()
{
	int i;
	const char* errMsg = "Release Memory Object :Failed";
	MEM_FREE(opencl_DES_bs_all);
	MEM_FREE(opencl_DES_bs_data);
	MEM_FREE(B);
	MEM_FREE(loaded_hash);
	MEM_FREE(cmp_out);
	HANDLE_CLERROR(clReleaseMemObject(index768_gpu),errMsg);
	HANDLE_CLERROR(clReleaseMemObject(index96_gpu), errMsg);
	HANDLE_CLERROR(clReleaseMemObject(opencl_DES_bs_data_gpu), errMsg);
	HANDLE_CLERROR(clReleaseMemObject(B_gpu), errMsg);
	clReleaseMemObject(cmp_out_gpu);
	clReleaseMemObject(loaded_hash_gpu);
	for( i = 0; i < 4096; i++)
		if (krnl[gpu_id][i])
			clReleaseKernel(krnl[gpu_id][i]);
	HANDLE_CLERROR(clReleaseProgram(program[gpu_id]),
	               "Error releasing Program");
}

void opencl_DES_reset(struct db_main *db) {


	if(db) {
	MEM_FREE(loaded_hash);
	MEM_FREE(cmp_out);

	clReleaseMemObject(cmp_out_gpu);
	clReleaseMemObject(loaded_hash_gpu);

	loaded_hash = (int*)mem_alloc((db->password_count)*sizeof(int)*2);
	cmp_out     = (unsigned int*)mem_alloc((db->password_count)*sizeof(unsigned int));

	loaded_hash_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, (db->password_count)*sizeof(int)*2, NULL, &err);
	if(loaded_hash_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	cmp_out_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, (db->password_count)*sizeof(unsigned int), NULL, &err);
	if(cmp_out_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	benchmark = 0;

	}
}

void opencl_DES_bs_init_global_variables() {

	opencl_DES_bs_all = (opencl_DES_bs_combined*) mem_alloc (MULTIPLIER * sizeof(opencl_DES_bs_combined));
	opencl_DES_bs_data = (opencl_DES_bs_transfer*) mem_alloc (MULTIPLIER * sizeof(opencl_DES_bs_transfer));
	B = (DES_bs_vector*) mem_alloc (MULTIPLIER * 64 * sizeof(DES_bs_vector));
}


int opencl_DES_bs_cmp_all(WORD *binary, int count)
{
	return 1;
}

inline int opencl_DES_bs_cmp_one(void *binary, int index)
{
	int bit;
	int section = (index >> 5) ;

	if(benchmark) return opencl_DES_bs_cmp_one_b((WORD*)binary, 32, index);
	if(section < min) return 0;
	if(section > max) return 0;

	for(bit = 0; bit < num_loaded_hash; bit++)
		if(cmp_out[bit] == section) return opencl_DES_bs_cmp_one_b((WORD*)binary, 32, index);

	return 0;
}

int opencl_DES_bs_cmp_one_b(WORD *binary, int count, int index)
{
	int bit;
	DES_bs_vector *b;
	int depth;
	unsigned int sector;

	sector = index >> DES_BS_LOG2;
	index &= (DES_BS_DEPTH - 1);
	depth = index >> 3;
	index &= 7;

	b = (DES_bs_vector *)((unsigned char *)&B[sector * 64] + depth);

#define GET_BIT \
	((unsigned WORD)*(unsigned char *)&b[0] >> index)

	for (bit = 0; bit < 31; bit++, b++)
		if ((GET_BIT ^ (binary[0] >> bit)) & 1)
			return 0;

	for (; bit < count; bit++, b++)
		if ((GET_BIT ^ (binary[bit >> 5] >> (bit & 0x1F))) & 1)
			return 0;

#undef GET_BIT
	return 1;
}

static void find_best_gws(struct fmt_main *fmt)
{
	struct timeval start, end;
	double savetime;
	long int count = 64;
	double speed = 999999, diff;
	int ccount;

	gettimeofday(&start, NULL);
	ccount = count * local_work_size * DES_BS_DEPTH;
	opencl_DES_bs_crypt_25(&ccount, NULL);
	gettimeofday(&end, NULL);
	savetime = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.000;
	speed = ((double)count) / savetime;
	do {
		count *= 2;
		if ((count * local_work_size) > MULTIPLIER) {
			count = count >> 1;
			break;

		}
		gettimeofday(&start, NULL);
		ccount = count * local_work_size * DES_BS_DEPTH;
		opencl_DES_bs_crypt_25(&ccount, NULL);
		gettimeofday(&end, NULL);
		savetime = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.000;
		diff = (((double)count) / savetime) / speed;
		if (diff < 1) {
			count = count >> 1;
			break;
		}
		diff = diff - 1;
		diff = (diff < 0) ? (-diff) : diff;
		speed = ((double)count) / savetime;
	} while(diff > 0.01);

	fmt -> params.max_keys_per_crypt = count * local_work_size * DES_BS_DEPTH;
	fmt -> params.min_keys_per_crypt = local_work_size * DES_BS_DEPTH;

	if (options.verbosity > 2)
		fprintf(stderr, "Local worksize (LWS) %zu, Global worksize (GWS) %zu\n", local_work_size, count * local_work_size);
}

#if HARDCODE_SALT

	static WORD stored_salt[4096]= {0x7fffffff};

	//static char *kernel_source;

	//static int kernel_loaded;

	//static size_t program_size;
/*
static char *include_source(char *pathname, int dev_id, char *options)
{
	static char include[PATH_BUFFER_SIZE];

	sprintf(include, "-I %s %s %s%d %s %s", path_expand(pathname),
	        get_device_type(gpu_id) == CL_DEVICE_TYPE_CPU ?
	        "-DDEVICE_IS_CPU" : "",
	        "-DDEVICE_INFO=", device_info[gpu_id],
#ifdef __APPLE__
	        "-DAPPLE",
#else
	        gpu_nvidia(device_info[gpu_id]) ? "-cl-nv-verbose" : "",
#endif
	        OPENCLBUILDOPTIONS);

	if (options) {
		strcat(include, " ");
		strcat(include, options);
	}

	//fprintf(stderr, "Options used: %s\n", include);
	return include;
}

static void opencl_read_source(char *kernel_filename)
{
	char *kernel_path = path_expand(kernel_filename);
	FILE *fp = fopen(kernel_path, "r");
	size_t source_size, read_size;

	if (!fp)
		fp = fopen(kernel_path, "rb");

	if (!fp)
		HANDLE_CLERROR(!CL_SUCCESS, "Source kernel not found!");

	fseek(fp, 0, SEEK_END);
	source_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	MEM_FREE(kernel_source);
	kernel_source = mem_calloc(source_size + 1);
	read_size = fread(kernel_source, sizeof(char), source_size, fp);
	if (read_size != source_size)
		fprintf(stderr,
		    "Error reading source: expected %zu, got %zu bytes.\n",
		    source_size, read_size);
	fclose(fp);
	program_size = source_size;
	kernel_loaded = 1;
}
*/
/*
static void build_kernel_exp(int dev_id, char *options)
{
	//cl_int build_code;
        //char * build_log; size_t log_size;
	const char *srcptr[] = { kernel_source };
	assert(kernel_loaded);
	program[gpu_id] =
	    clCreateProgramWithSource(context[gpu_id], 1, srcptr, NULL,
	    &ret_code);

	HANDLE_CLERROR(ret_code, "Error while creating program");

	if(gpu_nvidia(device_info[gpu_id]))
	   options = "";

	//build_code =
	clBuildProgram(program[gpu_id], 0, NULL,
		include_source("$JOHN/kernels/", gpu_id, options), NULL, NULL);
*/
	/*
        HANDLE_CLERROR(clGetProgramBuildInfo(program[gpu_id], devices[gpu_id],
                CL_PROGRAM_BUILD_LOG, 0, NULL,
                &log_size), "Error while getting build info I");
        build_log = (char *) mem_alloc((log_size + 1));

	HANDLE_CLERROR(clGetProgramBuildInfo(program[gpu_id], devices[gpu_id],
		CL_PROGRAM_BUILD_LOG, log_size + 1, (void *) build_log,
		NULL), "Error while getting build info");

	///Report build errors and warnings
	if (build_code != CL_SUCCESS) {
		//Give us much info about error and exit
		fprintf(stderr, "Compilation log: %s\n", build_log);
		fprintf(stderr, "Error building kernel. Returned build code: %d. DEVICE_INFO=%d\n", build_code, device_info[gpu_id]);
		HANDLE_CLERROR (build_code, "clBuildProgram failed.");
	}
#ifdef REPORT_OPENCL_WARNINGS
	else if (strlen(build_log) > 1) // Nvidia may return a single '\n' which is not that interesting
		fprintf(stderr, "Compilation log: %s\n", build_log);
#endif
        MEM_FREE(build_log);
#if 0
	FILE *file;
	size_t source_size;
	char *source;

	HANDLE_CLERROR(clGetProgramInfo(program[gpu_id],
		CL_PROGRAM_BINARY_SIZES,
		sizeof(size_t), &source_size, NULL), "error");
	fprintf(stderr, "source size %zu\n", source_size);
	source = mem_alloc(source_size);

	HANDLE_CLERROR(clGetProgramInfo(program[gpu_id],
		CL_PROGRAM_BINARIES, sizeof(char *), &source, NULL), "error");

	file = fopen("program.bin", "w");
	if (file == NULL)
		fprintf(stderr, "Error opening binary file\n");
	else if (fwrite(source, source_size, 1, file) != 1)
		fprintf(stderr, "error writing binary\n");
	fclose(file);
	MEM_FREE(source);
#endif
*/
//}

static void init_dev()
{
	opencl_prepare_dev(gpu_id);

	opencl_DES_bs_data_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, MULTIPLIER * sizeof(opencl_DES_bs_transfer), NULL, &err);
	if(opencl_DES_bs_data_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	index768_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 768 * sizeof(unsigned int), NULL, &err);
	if(index768_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	index96_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 96 * sizeof(unsigned int), NULL, &err);
	if(index96_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	B_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 64 * MULTIPLIER * sizeof(DES_bs_vector), NULL, &err);
	if(B_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, "Create Buffer FAILED\n");

	HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], index768_gpu, CL_TRUE, 0, 768 * sizeof(unsigned int), index768, 0, NULL, NULL ), "Failed Copy data to gpu");

	opencl_read_source("$JOHN/kernels/DES_bs_kernel.cl") ;
}

void modify_src() {

	  int i = 53, j = 1, tmp;
	  static char digits[10] = {'0','1','2','3','4','5','6','7','8','9'} ;
	  static unsigned int  index[48]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,
					     24,25,26,27,28,29,30,31,32,33,34,35,
					     48,49,50,51,52,53,54,55,56,57,58,59,
					     72,73,74,75,76,77,78,79,80,81,82,83 } ;
	  for (j = 1; j <= 48; j++) {
		tmp = index96[index[j - 1]] / 10;
		if (tmp == 0)
			kernel_source[i + j * 17] = ' ' ;
		else
			kernel_source[i + j * 17] = digits[tmp];
		tmp = index96[index[j - 1]] % 10;
	     ++i;
	     kernel_source[i + j * 17 ] = digits[tmp];
	     ++i;
	  }
}

void DES_bs_select_device(struct fmt_main *fmt)
{
	init_dev();

	if (!local_work_size)
		local_work_size = WORK_GROUP_SIZE;

	if (!global_work_size)
		find_best_gws(fmt);
	else {
		if (options.verbosity > 2)
			fprintf(stderr, "Local worksize (LWS) %zu, Global worksize (GWS) %zu\n", local_work_size, global_work_size);
		fmt -> params.max_keys_per_crypt = global_work_size * DES_BS_DEPTH;
		fmt -> params.min_keys_per_crypt = local_work_size * DES_BS_DEPTH;
	}
}
#else

void DES_bs_select_device(struct fmt_main *fmt)
{
	const char *errMsg;

	if (!local_work_size)
		local_work_size = WORK_GROUP_SIZE;

	opencl_init("$JOHN/kernels/DES_bs_kernel.cl", gpu_id, NULL);

	krnl[gpu_id][0] = clCreateKernel(program[gpu_id], "DES_bs_25_b", &err) ;
	if (err) {
		fprintf(stderr, "Create Kernel DES_bs_25_b FAILED\n");
		return ;
	}

	/* Cap LWS at kernel limit */
	if (local_work_size >
	    get_kernel_max_lws(gpu_id, krnl[gpu_id][0]))
		local_work_size =
			get_kernel_max_lws(gpu_id, krnl[gpu_id][0]);


	/* ...but ensure GWS is still a multiple of LWS */
	global_work_size = ((global_work_size + local_work_size - 1) /
	                    local_work_size) * local_work_size;

	errMsg = "Create Buffer FAILED.";
	opencl_DES_bs_data_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, MULTIPLIER * sizeof(opencl_DES_bs_transfer), NULL, &err);
	if (opencl_DES_bs_data_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	index768_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 768 * sizeof(unsigned int), NULL, &err);
	if (index768_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	index96_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 96 * sizeof(unsigned int), NULL, &err);
	if (index96_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	B_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, 64 * MULTIPLIER * sizeof(DES_bs_vector), NULL, &err);
	if (B_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	loaded_hash_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, sizeof(int), NULL, &err);
	if(loaded_hash_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	cmp_out_gpu = clCreateBuffer(context[gpu_id], CL_MEM_READ_WRITE, sizeof(unsigned int), NULL, &err);
	if(cmp_out_gpu == (cl_mem)0)
		HANDLE_CLERROR(err, errMsg);

	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 0, sizeof(cl_mem), &index768_gpu), "Set Kernel Arg FAILED arg0\n");
	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 1, sizeof(cl_mem), &index96_gpu), "Set Kernel Arg FAILED arg1\n");
	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 2, sizeof(cl_mem), &opencl_DES_bs_data_gpu), "Set Kernel Arg FAILED arg2\n");
	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 3, sizeof(cl_mem), &B_gpu), "Set Kernel Arg FAILED arg4\n");
	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 4, sizeof(cl_mem), &loaded_hash_gpu), "Set Kernel krnl Arg 4 :FAILED") ;
	HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 6, sizeof(cl_mem), &cmp_out_gpu), "Set Kernel Arg krnl FAILED arg6\n");


	HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], index768_gpu, CL_TRUE, 0, 768*sizeof(unsigned int), index768, 0, NULL, NULL ), "Failed Copy data to gpu");

	if (!global_work_size)
		find_best_gws(fmt);
	else {
		if (options.verbosity > 2)
			fprintf(stderr, "Local worksize (LWS) %zu, Global worksize (GWS) %zu\n", local_work_size, global_work_size);
		fmt -> params.max_keys_per_crypt = global_work_size * DES_BS_DEPTH;
		fmt -> params.min_keys_per_crypt = local_work_size * DES_BS_DEPTH;
	}
}
#endif

void opencl_DES_bs_set_salt(WORD salt)
{
	unsigned int new = salt, section = 0;
	unsigned int old;
	int dst;

	for (section = 0; section < MAX_KEYS_PER_CRYPT / DES_BS_DEPTH; section++) {
	new = salt;
	old = opencl_DES_bs_all[section].salt;
	opencl_DES_bs_all[section].salt = new;
	}
	section = 0;
	current_salt = salt ;
	for (dst = 0; dst < 24; dst++) {
		if ((new ^ old) & 1) {
			DES_bs_vector *sp1, *sp2;
			int src1 = dst;
			int src2 = dst + 24;
			if (new & 1) {
				src1 = src2;
				src2 = dst;
			}
			sp1 = opencl_DES_bs_all[section].Ens[src1];
			sp2 = opencl_DES_bs_all[section].Ens[src2];

			index96[dst] = (WORD *)sp1 - (WORD *)B;
			index96[dst + 24] = (WORD *)sp2 - (WORD *)B;
			index96[dst + 48] = (WORD *)(sp1 + 32) - (WORD *)B;
			index96[dst + 72] = (WORD *)(sp2 + 32) - (WORD *)B;
		}
		new >>= 1;
		old >>= 1;
		if (new == old)
			break;
	}

	set_salt = 1;
}

#if HARDCODE_SALT

int opencl_DES_bs_crypt_25(int *pcount, struct db_salt *salt)
{
	int keys_count = *pcount;
	unsigned int section = 0, keys_count_multiple;
	static unsigned int pos ;
	cl_event evnt;
	size_t N,M;

	if (keys_count%DES_BS_DEPTH == 0)
		keys_count_multiple = keys_count;
	else
		keys_count_multiple = (keys_count / DES_BS_DEPTH + 1) * DES_BS_DEPTH;

	section = keys_count_multiple / DES_BS_DEPTH;

	M = local_work_size;

	if (section % local_work_size != 0)
		N = (section / local_work_size + 1) * local_work_size ;
	else
		N = section;

	if (set_salt == 1) {
		unsigned int found = 0;
		if (stored_salt[current_salt] == current_salt) {
			found = 1;
			pos = current_salt;
		}

		if (found == 0) {
			pos = current_salt;
			modify_src();
			clReleaseProgram(program[gpu_id]);
			//build_kernel( gpu_id, "-fno-bin-amdil -fno-bin-source -fbin-exe") ;
			opencl_build(gpu_id, "-fno-bin-amdil -fno-bin-source -fbin-exe", 0, NULL, 1);
			krnl[gpu_id][pos] = clCreateKernel(program[gpu_id], "DES_bs_25", &err) ;
			if (err) {
				fprintf(stderr, "Create Kernel DES_bs_25 FAILED\n");
				return 0;
			}

			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 0, sizeof(cl_mem), &index768_gpu), "Set Kernel Arg FAILED arg0\n");
			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 1, sizeof(cl_mem), &index96_gpu), "Set Kernel Arg FAILED arg1\n");
			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 2, sizeof(cl_mem), &opencl_DES_bs_data_gpu), "Set Kernel Arg FAILED arg2\n");
			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 3, sizeof(cl_mem),&B_gpu), "Set Kernel Arg FAILED arg3\n");
			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 4, sizeof(cl_mem), &loaded_hash_gpu), "Set Kernel krnl Arg 4 :FAILED") ;
			HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 6, sizeof(cl_mem),&cmp_out_gpu), "Set Kernel Arg krnl FAILED arg6\n");

			stored_salt[current_salt] = current_salt;
		}
		//HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id],index96_gpu,CL_TRUE,0,96*sizeof(unsigned int),index96,0,NULL,NULL ), "Failed Copy data to gpu");
		set_salt = 0;
	}

	HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id],opencl_DES_bs_data_gpu,CL_TRUE,0,MULTIPLIER*sizeof(opencl_DES_bs_transfer),opencl_DES_bs_data,0,NULL,NULL ), "Failed Copy data to gpu");

	if(salt) {
		struct db_password *pw;
		int i = 0, *bin;

		pw = salt -> list;
		do {
			  bin = (int *)pw -> binary;
			  loaded_hash[i] = bin[0] ;
			  loaded_hash[i + salt -> count] = bin[1];
			  i++ ;
			  //  printf("%d %d\n", i++, bin[0]);
		} while ((pw = pw -> next)) ;
		num_loaded_hash = (salt -> count);
		//printf("%d\n",loaded_hash[salt->count-1]);
		HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], loaded_hash_gpu, CL_TRUE, 0, (salt -> count) * sizeof(int) * 2, loaded_hash, 0, NULL, NULL ), "Failed Copy data to gpu");
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 5, sizeof(int), &(salt->count)), "Set Kernel krnl Arg 5 :FAILED") ;

	}

	else {
		int tmp = 0;
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][pos], 5, sizeof(int), &tmp), "Set Kernel krnl Arg 5 :FAILED") ;
	}

	err = clEnqueueNDRangeKernel(queue[gpu_id], krnl[gpu_id][pos], 1, NULL, &N, &M, 0, NULL, &evnt);
	HANDLE_CLERROR(err, "Enque Kernel Failed");
	clWaitForEvents(1, &evnt);
	clReleaseEvent(evnt);

	if (salt) {
		int i;
		max = 0;
		min = MULTIPLIER ;

		HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], cmp_out_gpu, CL_TRUE, 0, (salt -> count) * sizeof(unsigned int), cmp_out, 0, NULL, NULL),"Write FAILED\n");

		for (i = 0; i < salt->count; i++) {
			if (!cmp_out[i]) {
				cmp_out[i] = ~(unsigned int)0;
				continue;
			}
			if (cmp_out[i] > max)
				max = cmp_out[i];
			cmp_out[i]--;
			if (cmp_out[i] < min)
				min = cmp_out[i];
		}

		if (max--) {
			HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], B_gpu,CL_TRUE, 0, MULTIPLIER * 64 * sizeof(DES_bs_vector), B, 0, NULL, NULL),"Write FAILED\n");
			clFinish(queue[gpu_id]);
			return (max + 1) * DES_BS_DEPTH;
		} else
			return 0;

	}

	else {

		HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], B_gpu, CL_TRUE, 0, MULTIPLIER * 64 * sizeof(DES_bs_vector), B, 0, NULL, NULL),"Write FAILED\n");
		clFinish(queue[gpu_id]);
		return keys_count;
	}
}

#else

int opencl_DES_bs_crypt_25(int *pcount, struct db_salt *salt)
{
	int keys_count = *pcount;
	unsigned int section = 0, keys_count_multiple;
	cl_event evnt;
	size_t N, M;

	if (keys_count % DES_BS_DEPTH == 0)
		keys_count_multiple = keys_count;
	else
		keys_count_multiple = (keys_count / DES_BS_DEPTH + 1) * DES_BS_DEPTH;

	section = keys_count_multiple / DES_BS_DEPTH;
	M = local_work_size;

	if (section % local_work_size != 0)
		N = (section / local_work_size + 1) * local_work_size ;
	else
		N = section;

	if (set_salt == 1) {
		HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], index96_gpu, CL_TRUE, 0, 96 * sizeof(unsigned int), index96, 0, NULL, NULL), "Failed Copy data to gpu");
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 4, sizeof(cl_mem), &loaded_hash_gpu), "Set Kernel krnl Arg 4 :FAILED");
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 6, sizeof(cl_mem), &cmp_out_gpu), "Set Kernel Arg krnl FAILED arg6\n");
		set_salt = 0;
	}

	HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], opencl_DES_bs_data_gpu, CL_TRUE, 0, MULTIPLIER * sizeof(opencl_DES_bs_transfer), opencl_DES_bs_data, 0, NULL, NULL ), "Failed Copy data to gpu");

	if(salt) {
		int i = 0, *bin;
		struct db_password *pw;

		pw = salt -> list;
		do {
			  bin = (int *)pw -> binary;
			  loaded_hash[i] = bin[0] ;
			  loaded_hash[i + salt -> count] = bin[1];
			  i++ ;
			  //printf("%d %d\n", i++, bin[0]);
		} while ((pw = pw -> next)) ;
		num_loaded_hash = (salt -> count);
		//printf("%d\n",loaded_hash[salt->count-1 + salt -> count]);
		HANDLE_CLERROR(clEnqueueWriteBuffer(queue[gpu_id], loaded_hash_gpu, CL_TRUE, 0, (salt -> count) * sizeof(int) * 2, loaded_hash, 0, NULL, NULL ), "Failed Copy data to gpu");
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 5, sizeof(int), &(salt->count)), "Set Kernel krnl Arg 5 :FAILED") ;

	}

	else {
		int tmp = 0;
		HANDLE_CLERROR(clSetKernelArg(krnl[gpu_id][0], 5, sizeof(int), &tmp), "Set Kernel krnl Arg 5 :FAILED") ;
	}


	err = clEnqueueNDRangeKernel(queue[gpu_id], krnl[gpu_id][0], 1, NULL, &N, &M, 0, NULL, &evnt);
	HANDLE_CLERROR(err, "Enque Kernel Failed");

	clWaitForEvents(1, &evnt);
	clReleaseEvent(evnt);

	if (salt) {
		int i;
		max = 0;
		min = MULTIPLIER ;

		HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], cmp_out_gpu, CL_TRUE, 0, (salt->count) * sizeof(unsigned int), cmp_out, 0, NULL, NULL), "Write FAILED\n");

		for (i = 0; i < salt->count; i++) {
			if (!cmp_out[i]) {
				cmp_out[i] = ~(unsigned int)0;
				continue;
			}
			if (cmp_out[i] > max)
				max = cmp_out[i];
			cmp_out[i]--;
			if (cmp_out[i] < min)
				min = cmp_out[i];
		}

		if (max--) {
			HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], B_gpu, CL_TRUE, 0, MULTIPLIER * 64 * sizeof(DES_bs_vector), B, 0, NULL, NULL), "Write FAILED\n");
			clFinish(queue[gpu_id]);
			return (max + 1) * DES_BS_DEPTH;
		} else
			return 0;

	}

	else {

		HANDLE_CLERROR(clEnqueueReadBuffer(queue[gpu_id], B_gpu, CL_TRUE, 0, MULTIPLIER * 64 * sizeof(DES_bs_vector), B, 0, NULL, NULL), "Write FAILED\n");
		clFinish(queue[gpu_id]);
		return keys_count;
	}
}
#endif

#endif /* HAVE_OPENCL */
