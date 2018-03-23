/************************************************************************
 * Demo of SMP_SAFE instantiated component in C++ class
 * 
 * ArcEye 2015  <arceyeATmgwareDOTcoDOTuk>
 * 
 * Adapted for use in machinekit_ros_control
 * Taken from src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
 * https://github.com/machinekit/machinekit/blob/master/src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
************************************************************************/ 

#ifndef CONTROL_COMPONENT_2_H
#define CONTROL_COMPONENT_2_H

#define _CORRECT_ISO_CPP_STRING_H_PROTO

// Std C / C++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>   /* Standard types */

#include <rtapi.h>
#include "rtapi_app.h"
#include "rtapi_string.h"
#include <hal.h>
#include <hal_priv.h>
#include <hal_accessor.h>
#include "hal_internal.h"

// Can't rely on bool working otherwise
#undef TRUE
#define TRUE (1)
#undef FALSE
#define FALSE (0)
#undef true
#define true (1)
#undef false
#define false (0)

#ifdef MODULE_INFO
MODULE_INFO(machinekit, "component:constant:Use a parameter to set the value of a pin");
MODULE_INFO(machinekit, "pin:out:float:None:out::None");
MODULE_INFO(machinekit, "pin:value:float:None:io::None");
MODULE_INFO(machinekit, "funct:_:1:");
MODULE_INFO(machinekit, "license:GPL");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO

RTAPI_TAG(HAL,HC_SMP_SAFE);

namespace machinekit_ros_control
{

struct inst_data;

class ControlComponent2
{
public:
    ControlComponent2();
    ~ControlComponent2();

    static int export_controlcomponent2(struct inst_data *ip, const char *name);
    static void dummy_funct(void *arg, long period);
    
    struct inst_data *inst;
    static int comp_id;
    const char *cname;
};

}  // namespace

#endif