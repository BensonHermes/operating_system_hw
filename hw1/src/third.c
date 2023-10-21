/* 
 * third_example.c - Demonstrates command line argument passing to a module. 
 *
 * Example code of  kernel module
 * 
 * Modified by 108307041@nccu.edu.tw
 * This code is from https://sysprog21.github.io/lkmpg/
 */

#include <linux/init.h> 
#include <linux/kernel.h> /* for ARRAY_SIZE() */ 
#include <linux/module.h> 
#include <linux/moduleparam.h> 
#include <linux/printk.h> 
#include <linux/stat.h> 
 
MODULE_LICENSE("GPL"); 
 
static int myage = 1; 
static char *myname = "ben"; 
static int mybirthday[2] = { 9, 1};
static int arr_argc = 0;
/* module_param(foo, int, 0000) 
 * The first param is the parameters name. 
 * The second param is its data type. 
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non-zero) at a later stage. 
 */ 
module_param(myage, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); 
MODULE_PARM_DESC(myage, "An integer"); 
module_param(myname, charp, 0000); 
MODULE_PARM_DESC(myname, "A character string"); 

/* module_param_array(name, type, num, perm); 
 * The first param is the parameter's (in this case the array's) name. 
 * The second param is the data type of the elements of the array. 
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time. 
 * The fourth argument is the permission bits. 
 */
module_param_array(mybirthday, int, &arr_argc, 0000);
MODULE_PARM_DESC(mybirthday, "An array of month and date for borthda");
 
static int __init proc_init(void) 
{ 
 
    pr_info("Hello, world\n"); 
    pr_info("my age is: %d\n", myage); 
    pr_info("my name is: %s\n", myname); 
    
    pr_info("my birthday is: %d/%d\n", mybirthday[0], mybirthday[1]);
 
    return 0; 
} 
 
static void __exit proc_exit(void) 
{ 
    pr_info("Goodbye, world\n");
} 
 
module_init(proc_init); 
module_exit(proc_exit);
