/*
 * date.x - Specification of remote date, time, date and time service.
 */
/*
 * Define 1 procedure :
 * date_1() accepts a long and returns a string.
 */
program DATE_PROG {
	version DATE_VERS {
		string	DATE(long) = 1;/* procedure number = 1 */
		string  CPU_USAGE(long) = 2;/* procedure number = 2 */
		string  MEMORY_USAGE(long) = 3;/* procedure number = 3 */
		string  LOAD_PROC_PER_MINUTE(long) = 4;/* procedure number = 4 */
	} = 1; /* version number = 1*/
} = 0x31234567;/* program number */
