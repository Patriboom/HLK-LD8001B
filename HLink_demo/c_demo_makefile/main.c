/** 
 * ***************************************************************** 
 * @file    main.c
 * @author  Home(zhhuang@andartechs.com.cn) 
 * @version 1.0.0 
 * @date    2022-02-07
 * @brief    
 *  
 *                 Copyright (c) 2022, Andar Technologies Inc. 
 *                           www.andartechs.com 
 *  
 * ***************************************************************** 
 */
#include "TinyFrame.h"

#include <stdio.h>

#define PRO         0


static TinyFrameRx          s_rxStr;
static verStatusTypedef     s_verStatus;

static void rx_and_parse_data(void);


/** 
 * @brief   The entry point of the program. 
 * @param   None. 
 * @return  int: 
 * @note 
 */
int main(void)
{
    uint8 tx_arr[4] = {0x01, 0x01, 0x00, 0x00};
    tinyFramefTx(0xFFFF, (uint8 *)tx_arr, sizeof(tx_arr) / sizeof(uint8));
    rx_and_parse_data();
    return 0;
}


/** 
 * @brief   Monitor, receive, analyze, obtain the corresponding type, 、
 *          prepare to send data packets and send data.
 * @param   None. 
 * @return  None.
 * @note 
 */
static void rx_and_parse_data(void)
{
    s_rxStr = tinyFramefRx();

    if(s_rxStr.receiveType == 0xFFFF)
    {
    #ifdef GUI
        printf("Successfully received TF frame data and parsed the type to obtain version information.\n");
    #endif // GUI
        s_verStatus.project = PRO;
        s_verStatus.version_major = 1;
        s_verStatus.version_minor = 0;
        s_verStatus.version_patch = 0;

    #ifdef GUI
        printf("Return data.\n");
    #endif // GUI
        tinyFramefTx(s_rxStr.receiveType, (uint8 *)(&s_verStatus), sizeof(s_verStatus));
    }
}
