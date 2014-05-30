
/*
* Define where this log is saved.
*/
const char * log_file_path_and_name = "./log.bin";

/*
* Define max buffer size.
*/
#define MAX_BUFFER_SIZE 1024

/*
* Define Log_level.
*/
#define LOG_EMERG	0
#define LOG_ALERT	1
#define LOG_CRIT	2
#define LOG_ERR		3
#define LOG_WARNING	4
#define LOG_NOTICE	5
#define LOG_INFO	6
#define LOG_DEBUG	7

/*
* Define status.
*/
#define READ_HIT	10
#define READ_MISS	11
#define WRITE_HIT	12
#define WRITE_MISS	13
#define WRITE_BACK	14

/*
* log_write(): write a piece of information into log, which is a binary file.
* @log_level: defined as before.
* @status: defined as before.
*/
int log_write(int log_level, int status);
















//static void hc_log(int priority,int state);

//void hc_info(int state);
//void hc_warning(int state);
//void hc_error(int state);
//void hc_debug(int state);

//void hc_log_set_time(void);
//void hc_log_get_time(void);


//void hc_log_clear(void);

/*
 *  0 -- all print
 */
//void hc_log_print(int priority=0,int time=0);

//char * hc_log_parse(void);

