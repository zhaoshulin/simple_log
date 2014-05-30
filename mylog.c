#include <stdlib.h>
#include <stdio.h>
#include "mylog.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>


int log_line_parse(void * _buf);
int log_read_by_loglevel(int log_level);
int log_write(int log_level, int status);
int log_del(void);


int log_write(int log_level, int status)
{
//	printf("Enter into log_write()...\n");
	char buf[18];
	memset(buf, 0x00, sizeof(buf));
//	printf("memset succeed.\n");
	// time...
	time_t seconds = time((time_t *)NULL);
//	printf("seconds is %ld\n", seconds);
	sprintf(buf, "%ld ", seconds);
	
	int bufLen = strlen(buf);
	FILE * fp = NULL;
	fp = fopen(log_file_path_and_name, "ab+");
	if(NULL == fp)
	{
		printf("Error: fopen failed!\n");
		return -1;
	}
	fwrite(buf, bufLen, 1, fp);
	fclose(fp);
//	writeFile(log_file_path_and_name, seconds, sizeof(seconds));
//	printf("log_level is %d, status is %d.\n", log_level, status);
	sprintf(buf, "%d %d\n", log_level, status);
	bufLen = strlen(buf);
	fp = fopen(log_file_path_and_name, "ab+");
	if(NULL == fp)
	{
		printf("Error: fopen failed!\n");
		return -1;
	}
	fwrite(buf, bufLen, 1, fp);
	fclose(fp);
//	writeFile(log_file_path_and_name, buf, bufLen);	
	return 0;
}


int log_line_parse(void * _buf)
{
//	printf("Enter into log_line_parse...\n");
	time_t time;
	int log_level;
	int status;
	int ret;
	struct tm * timeptr;

	ret = sscanf(_buf, "%ld %d %d\0", &time, &log_level, &status);
	if(ret != 3)
	{
		printf("sscanf return != 3, exit!\n");
		return -1;
	}
//	printf("ret is %d, time is %ld, log_level is %d, status is %d\n", ret, time, log_level, status);
	timeptr = gmtime(&time);
	printf("TIME: %slog_level: %d, status: %d.\n \n", asctime(timeptr), log_level, status);	
	
	return 0;
}

int log_read_by_loglevel(int log_level)
{
	//printf("Enter into log_read_by_loglevel...\n");
	char buf[18];
	char tmp[2];
	FILE * fp;
	memset(buf, 0x00, sizeof(buf));
	memset(tmp, 0x00, sizeof(tmp));
	fp = fopen(log_file_path_and_name, "ab+");	
	if(NULL == fp)
		return -1;

	long offset = 0.0;
	long length = 0.0;
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
while(length > 16*offset){	
	fread(buf, 16, 1, fp);
	sprintf(tmp, " %d ", log_level);//convert log_level from int to string
	if(NULL == strstr(buf, tmp))
	{
//		printf("The log_level is NOT included in this line.\n");
		offset ++;
		fseek(fp, 16*offset, SEEK_SET);
	}
	else
	{
//		printf("The log_level is included in this line.\n");
//		printf("%s", buf);
		log_line_parse(buf);
		offset ++;
		fseek(fp, 16*offset, SEEK_SET);
	}
}
	return 0;
}

int log_read_by_status(int status)
{
	char buf[18];
	char tmp[2];
	FILE * fp;
	memset(buf, 0x00, sizeof(buf));
	memset(tmp, 0x00, sizeof(tmp));
	fp = fopen(log_file_path_and_name, "ab+");
	if(NULL == fp)
		return -1;
	
	long offset = 0.0;
	long length = 0.0;
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	while(length > 16*offset)
	{
		fread(buf, 16, 1, fp);
		sprintf(tmp, " %d", status);//convert status from int to srting
		if(NULL == strstr(buf, tmp))
		{
			offset ++;
			fseek(fp, 16*offset, SEEK_SET);
		}
		else
		{
			log_line_parse(buf);
			offset ++;
			fseek(fp, 16*offset, SEEK_SET);
		}
	}
	return 0;
}

int log_del(void)
{
	printf("Enter into log_del()...\n");
	if(remove(log_file_path_and_name) < 0)
	{
		printf("Error: remove failed!\n");
		return -1;
	}
	return 0;
}




int main(void)
{
	int i = 0;
//	printf("Enter into main()...\n");
	log_write(LOG_ERR, READ_HIT);
	for(i=0; i<5; i++){
	sleep(1);
	log_write(LOG_ALERT, WRITE_MISS);}
//	log_read(LOG_ALERT, WRITE_MISS);
	printf("log_read_by_loglevel: LOG_ALERT...\n"); 
	log_read_by_loglevel(LOG_ALERT);
	printf("log_read_by_status: READ_HIT...\n");
	log_read_by_status(READ_HIT);
	printf("log_read_by_status: WRITE_MISS...\n");
	log_read_by_status(WRITE_MISS);
//	log_del();
	return 0;
	}




	

