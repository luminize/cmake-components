#include <string>
#include <bloody_dangerous_function_comp.h>

int BloodyDangerousFuntionComponent::comp_id = 0;
BloodyDangerousFuntionComponent *cr;

struct inst_data
{
    hal_u64_t *read_func_addr;
    hal_u64_t *update_func_addr;
    hal_u64_t *write_func_addr;
    hal_bit_t *enable;
};

BloodyDangerousFuntionComponent::BloodyDangerousFuntionComponent()
{
    int retval = 0;
    cname = "dangerous";
    comp_id = hal_init(cname);
    if (comp_id < 0)
        {
        hal_print_msg(RTAPI_MSG_DBG,"Component creation ABORTED");
        exit(-1);
        }
    
    // allocate memory
    if ((inst = (inst_data *) hal_malloc(sizeof(inst_data))) == NULL) {
	    hal_print_msg(RTAPI_MSG_ERR,
			    "%s: ERROR: hal_malloc failed\n", cname);
        return;
    }

    // export pins and functions
	if ((retval = export_bloodydangerousfuntioncomponent(inst, cname))) {
	    hal_print_msg(RTAPI_MSG_ERR,
			    "%s: ERROR: export_bloodydangerousfuntioncomponent failed\n", cname);
	    hal_exit(comp_id);
	    return;
	}

    hal_ready(comp_id);
}

BloodyDangerousFuntionComponent::~BloodyDangerousFuntionComponent()
{
    hal_exit(comp_id);
}

int BloodyDangerousFuntionComponent::export_bloodydangerousfuntioncomponent(struct inst_data *ip, const char *name)
{
    int retval = 0;
    
    // create pins
    if (((retval = hal_pin_u64_newf(HAL_IN, &(ip->read_func_addr), comp_id,
                    "%s.r",  name))) ||
	    ((retval = hal_pin_u64_newf(HAL_IN, &(ip->update_func_addr), comp_id,
				    "%s.u", name))) ||
	    ((retval = hal_pin_u64_newf(HAL_IN, &(ip->write_func_addr), comp_id,
				    "%s.w", name))) ||
        ((retval = hal_pin_bit_newf(HAL_IN, &(ip->enable), comp_id,
                    "%s.enable", name))))
    {
	    return retval;
    }

    // set all adresses all to 0, meaning these will become null pointers
    *(ip->read_func_addr) = 0;
    *(ip->update_func_addr) = 0;
    *(ip->write_func_addr) = 0;
    *(ip->write_func_addr) = 0;

    // export the function
    hal_print_msg(RTAPI_MSG_DBG,"export_funct &ip : %p", &ip);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct ip : %p", ip);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct read_funct %p", read_funct);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct update_funct %p", update_funct);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct write_funct %p", write_funct);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct comp_id %i", comp_id);
    hal_print_msg(RTAPI_MSG_DBG,"export_funct name %s", name);

    if ((retval = hal_export_functf(read_funct,
                ip, 1, 0, comp_id, "%s.read_funct", name)) < 0) {
	return retval;
    }
    if ((retval = hal_export_functf(update_funct,
            ip, 1, 0, comp_id, "%s.update_funct", name)) < 0) {
	return retval;
    }
    if ((retval = hal_export_functf(write_funct,
            ip, 1, 0, comp_id, "%s.write_funct", name)) < 0) {
	return retval;
    }

    return retval;
}

void BloodyDangerousFuntionComponent::read_funct(void *arg, long period)
{
    struct inst_data *ip  = (inst_data *) arg;
    // check to see if the enable bit is high
    if (*(ip->enable) == 1) {
        // create a void pointer and set it by casting u32 as void*
        // google-fu
        void (*f_adr)(std::string baz) = (void (*)(std::string baz))(*ip->write_func_addr);
        // print the adress for checking
        if (f_adr != NULL)
        {
            hal_print_msg(RTAPI_MSG_DBG,"read_funct f_addr %p", f_adr);
            // now call the function, see expose_functs.cpp
            f_adr("message from HAL, read by calling a write function");
        }
        else
        {
            // null pointer detected
            hal_print_msg(RTAPI_MSG_DBG,"read_funct f_addr %p is a null ptr", f_adr);
        }
    }

}

void BloodyDangerousFuntionComponent::update_funct(void *arg, long period)
{
    struct inst_data *ip  = (inst_data *) arg;
    // check to see if the enable bit is high
    if (*(ip->enable) == 1) {
    }
}

void BloodyDangerousFuntionComponent::write_funct(void *arg, long period)
{
    struct inst_data *ip  = (inst_data *) arg;
    // check to see if the enable bit is high
    if (*(ip->enable) == 1) {
    }
}


extern "C" int rtapi_app_main(void)
{
    cr = new BloodyDangerousFuntionComponent();
    return 0;
}


extern "C" void rtapi_app_exit(void)
{
    delete(cr);
}
