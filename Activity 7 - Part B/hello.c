#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL");

int valueETX;
int cb_valueETX = 15;

module_param(valueETX, int, S_IRUSR|S_IWUSR);

int notify_param(const char *val, const struct kernel_param *kp)
{
        int res = param_set_int(val, kp); // Use helper for write variable
        if(res==0) {
                printk(KERN_INFO "Call back function called...\n");
                printk(KERN_INFO "New value of cb_valueETX = %d\n", cb_valueETX);
                return 0;
        }
        return -1;
}
 
const struct kernel_param_ops my_param_ops = 
{
        .set = &notify_param, // Use our setter ...
        .get = &param_get_int, // .. and standard getter
};
 
module_param_cb(cb_valueETX, &my_param_ops, &cb_valueETX, S_IRUGO|S_IWUSR );

static int hello_init(void){
    printk(KERN_ALERT "HELLO, AWESOME WORLD");
return 0;
}

static void hello_exit(void){
    printk(KERN_ALERT "GOODBYE, CRUEL WORLD");
    printk(KERN_INFO "ValueETX = %d  \n", valueETX);
}
module_init(hello_init);
module_exit(hello_exit);
