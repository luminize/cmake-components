/************************************************************************
 * Demo of SMP_SAFE instantiated component in C++ class
 * 
 * ArcEye 2015  <arceyeATmgwareDOTcoDOTuk>
 * 
 * Adapted for use in machinekit_ros_control
 * Taken from src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
 * https://github.com/machinekit/machinekit/blob/master/src/hal/icomp-example/C%2B%2B_instantiated_comps/const-rtv2.cc
************************************************************************/ 

#ifndef BLOODY_DANGEROUS_FUNCTION_COMPONENT
#define BLOODY_DANGEROUS_FUNCTION_COMPONENT

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

RTAPI_TAG(HAL,HC_SMP_SAFE);

struct inst_data;

class BloodyDangerousFuntionComponent
{
public:
    BloodyDangerousFuntionComponent();
    ~BloodyDangerousFuntionComponent();

    static int export_bloodydangerousfuntioncomponent(struct inst_data *ip, const char *name);
    static void read_funct(void *arg, long period);
    static void update_funct(void *arg, long period);
    static void write_funct(void *arg, long period);
    
    struct inst_data *inst;
    static int comp_id;
    const char *cname;
};

#endif