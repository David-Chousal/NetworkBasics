/*
* Name: David Chousal
* Date: 09/30/2025 (the day you have lab)
* Title: Lab2 – FilesThreads.c	
* Description: This program computes the file transfers using multiple threads 
*/

// COEN 146L : Lab 2 - template to use for creating multiple thread to make file transfers (step 4)
#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	FILE* src = fopen(src_filename, "rb");	// open for reading (binary)
	if (src == NULL) {
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		return -1;
	}
	FILE* dst = fopen(dst_filename, "wb");	// open for writing; truncate/create
	if (dst == NULL) {
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		fclose(src);
		return -1;
	}

	void* buf = malloc((size_t)BUF_SIZE);
	if (buf == NULL) {
		fprintf(stderr, "malloc failed\n");
		fclose(src);
		fclose(dst);
		return -1;
	}

	size_t bytes_read = 0;
	while ((bytes_read = fread(buf, 1, BUF_SIZE, src)) > 0) {
		fwrite(buf, 1, bytes_read, dst);
	}

	fclose(src);
	fclose(dst);
	free(buf);
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	//call file copy function
	func_copy(params.src_filename, params.dst_filename);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	// usage: program n src1 dst1 ... srcN dstN
	if (argc < 2) {
		fprintf(stderr, "usage: %s <n> <src1> <dst1> ... <srcN> <dstN>\n", argv[0]);
		return 1;
	}

	int num_threads = atoi(argv[1]);
	if (num_threads <= 0) {
		fprintf(stderr, "n must be > 0\n");
		return 1;
	}
	int expected_argc = 2 + 2 * num_threads;
	if (argc != expected_argc) {
		fprintf(stderr, "usage: %s <n> <src1> <dst1> ... <srcN> <dstN>\n", argv[0]);
		return 1;
	}

	pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (size_t)num_threads);
	struct copy_struct* thread_params = (struct copy_struct*)malloc(sizeof(struct copy_struct) * (size_t)num_threads);
	if (threads == NULL || thread_params == NULL) {
		fprintf(stderr, "allocation failed\n");
		free(threads);
		free(thread_params);
		return 1;
	}

	int i;
	for (i = 0; i < num_threads; i++) {
		int arg_index = 2 + i * 2;
		thread_params[i].thread_id = i;
		thread_params[i].src_filename = argv[arg_index];
		thread_params[i].dst_filename = argv[arg_index + 1];
		pthread_create(&threads[i], NULL, copy_thread, (void*)&thread_params[i]);
	}

	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	free(threads);
	free(thread_params);
	return 0;
}