/* LLCONFIG.H -- Link Layer Configuration and Routing API */

#ifndef __LLCONFIG_H
#define __LLCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int                                /*   returns 0=ok, else=error number    */
ll_config(                         /* "ifconfig" (call once for ea network)*/
char *devname,                     /*   "pend","ptnd","slip0","ppp0","cman" */
u32 ipaddr,                        /*   IP address for this host on network*/
u32 netmask,                       /*   inet_addr("255.255.255.0")=class C */
unsigned mtu);                     /*   max transmission unit, e.g. 1006   */

int                                /*   returns 0=ok, else=error number    */
ll_route(                          /*"route" (call 0 or once after ll_config()*/
char *devname,                     /*   "pend","ptnd","slip0","ppp0","cman" */
u32 gateway,                       /*   gateway or destination IP address  */
int hops);                         /*   max hops to gateway, e.g. 1        */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __LLCONFIG_H
