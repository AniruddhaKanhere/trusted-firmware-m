/*
 * Copyright (c) 2022-2024, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "cmsis.h"
#include "dma350_checker_layer.h"
#include "platform_svc_numbers.h"
#include "tfm_hal_platform.h"
#include "tfm_platform_system.h"
#ifdef RSE_USE_SDS_LIB
#include "sds.h"
#endif /* RSE_USE_SDS_LIB */

int32_t platform_svc_handlers(uint8_t svc_num, uint32_t *svc_args,
                                uint32_t lr)
{
    (void) lr;

    int32_t retval;

    switch (svc_num) {
        case TFM_SVC_PLATFORM_DMA350_CONFIG:
            retval = (int32_t)config_dma350_for_unprivileged_actor(
                    (enum dma350_config_type_t)svc_args[0], (uint8_t)svc_args[1],
                    (void *)svc_args[2]);
            break;

#ifdef RSE_USE_SDS_LIB
        case TFM_SVC_PLATFORM_SDS_STRUCT_ADD:
            retval = (int32_t)sds_struct_add((void *)svc_args[0]);
            break;
#endif /* RSE_USE_SDS_LIB */

        default:
            retval = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return retval;
}
