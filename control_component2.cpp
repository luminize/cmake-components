/************************************************************************
 * Demo of SMP_SAFE instantiated component in C++ class
 * 
 * ArcEye 2015  <arceyeATmgwareDOTcoDOTuk>
 * 
 * Adapted for use in machinekit_ros_control
 * Taken from src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
 * https://github.com/machinekit/machinekit/blob/master/src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
************************************************************************/ 


#include <control_component2.h>

namespace machinekit_ros_control
{

int ControlComponent2::comp_id = 0;
ControlComponent2 *cr;

struct inst_data
    {
    hal_float_t *out;
    hal_float_t *value;
    int local_argc;
    const char **local_argv;
    };

ControlComponent2::ControlComponent2()
{
    int retval = 0;
    cname = "control_component2";
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
	if ((retval = export_controlcomponent2(inst, cname))) {
	    hal_print_msg(RTAPI_MSG_ERR,
			    "%s: ERROR: export_controlcomponent2 failed\n", cname);
	    hal_exit(comp_id);
	    return;
	}

    hal_ready(comp_id);
}

ControlComponent2::~ControlComponent2()
{
    hal_exit(comp_id);
}

int ControlComponent2::export_controlcomponent2(struct inst_data *ip, const char *name)
{
    int retval = 0;
    
    // create pins
    if (((retval = hal_pin_float_newf(HAL_IN, &(ip->value), comp_id,
                "%s.value",  name))) ||
	    ((retval = hal_pin_float_newf(HAL_OUT, &(ip->out), comp_id,
				    "%s.out", name))))
    {
	    return retval;
    }

    // export the function
    if ((retval = hal_export_functf(dummy_funct,
                ip, 1, 0, comp_id, "%s.dummy_funct", name)) < 0) {
	return retval;
    }

    return retval;
}

extern "C" void ControlComponent2::dummy_funct(void *arg, long period)
{
    struct inst_data *ip  = (inst_data *) arg;
    *(ip->out) = *(ip->value);
}

extern "C" int rtapi_app_main(void)
{
    cr = new ControlComponent2();
    return 0;
}


extern "C" void rtapi_app_exit(void)
{
    delete(cr);
}

}  // namespace