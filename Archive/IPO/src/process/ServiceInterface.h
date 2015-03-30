/* IPO_Porcess Service Interface '(zhangpengpeng 2014/05/10)
 * Start or Stop the Porcess
 */
#ifndef _SERVICEINTERFACE_H_
#define _SERVICEINTERFACE_H_

int IPO_P_ServiceInit();
int IPO_P_ServiceFini();
int IPO_P_ServiceStart();
int IPO_P_ServiceStop();

#endif // _SERVICEINTERFACE_H_