#include <stdio.h>
#include <string.h>


// physical port
 typedef struct{
char portName[15]; //configurable portName
 int speed; // speed in bytes
int mode; // full or half duplex
int switchport_mode; // 0 - access port, 1 - trunkport 
int Vlan; // Vlan
 int status; // 0 - administratively down, 1 - administratively enabled,
}port;
// MAC row table
typedef struct{
int port;
char MAC[12];
int Vlan;
int type;
}mac_row;
// initialize default port configuration
 void init_port(port *portname, char name[5], int speed);
//check if MAC address exists in the MAC table
int check_ifMACExists(char MAC[50], mac_row *MAC_table);
// create a entry on the MAC table
// identify incoming port and create the entry
void create_MAC_entry(int portNum, mac_row table[], char MAC[7]){
//check if the MAC exists on the MAC table
if(check_ifMACExists(MAC, table) == 0){
  return;
  }
strcpy(table[portNum].MAC, MAC);
}
 void main()
{
port gigabit_one = {0};
char ports[6][15] = {"G0/0", "G0/1", "F0/1", "F0/2", "F0/3", "F0/4"};
mac_row MAC_table[6];
int i ;
for(i = 0; i < 6; i ++){
MAC_table[i] = (mac_row){0};
}
init_port(&gigabit_one, "G0/0", 500);
 create_MAC_entry(1, MAC_table, "23DE43");
 printf("MAC table\n");
 for(i = 0; i < 6; i ++){
 printf("%d", MAC_table[i].port);
 printf("%s\n", MAC_table[i].MAC);
 }
printf("MAC address of the port 1 is:%s\n", MAC_table[1].MAC);
 printf("The name of the port is %s and has a speed of %d\n",gigabit_one.portName, gigabit_one.speed);
}
 void init_port(port *portname, char name[5], int speed){
 strcpy(portname->portName, name);
 portname->speed = speed;
 portname->mode = 1;
 portname->switchport_mode = 1;
 portname->Vlan = 1;
 portname->status = 1;
 }

 int check_ifMACExists(char MAC[50], mac_row *MAC_table){
 for(int i = 0; i < 6; i++){
 if(strcmp(MAC_table[i].MAC, MAC) == 0)
return 0;
 }
 return 1;
}

